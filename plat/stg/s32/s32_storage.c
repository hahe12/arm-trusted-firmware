/*
 * Copyright 2019-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <common/bl_common.h>
#include <common/desc_image_load.h>
#include <drivers/io/io_driver.h>
#include <drivers/mmc.h>
#include <drivers/nxp/s32/io/io_mmc.h>
#include <drivers/io/io_memmap.h>
#include <drivers/io/io_fip.h>
#include <drivers/nxp/s32/mmc/s32_mmc.h>
#include <assert.h>
#include <tools_share/firmware_image_package.h>
#include <lib/mmio.h>
#include <libfdt.h>
#include <platform.h>
#include <common/fdt_wrappers.h>

#include "s32_storage.h"
#include "s32_bl_common.h"
#include "s32_dt.h"

#ifdef SPD_opteed
#define FIP_BACKEND_MEMMAP_ID	(BL32_EXTRA1_IMAGE_ID + 1)
#else
#define FIP_BACKEND_MEMMAP_ID	(BL33_IMAGE_ID + 1)
#endif

static const io_dev_connector_t *s32_mmc_io_conn;
static uintptr_t s32_mmc_dev_handle;

static const io_dev_connector_t *s32_memmap_io_conn;
static uintptr_t s32_memmap_dev_handle;

static int s32_check_mmc_dev(const uintptr_t spec);
static int s32_check_memmap_dev(const uintptr_t spec);

static const io_block_spec_t fip_memmap_spec = {
	/* Dummy data */
	.offset = 0x0,
	.length = ROUND_TO_MMC_BLOCK_SIZE(FIP_HEADER_SIZE),
};

struct image_storage_info {
	uuid_t uuid;
	unsigned int image_id;
	io_block_spec_t io_spec;
};

static struct image_storage_info images_info[] = {
	{
		.image_id = BL31_IMAGE_ID,
		.uuid = UUID_EL3_RUNTIME_FIRMWARE_BL31,

		/* The offset and length for the specs will be dynamically
		 * adjusted after reading FIP header. This is done after
		 * reading FIP header in SRAM, before loading any other
		 * image from FIP, by calling set_image_spec() function
		 * */
	},
#ifdef SPD_opteed
	{
		.image_id = BL32_IMAGE_ID,
		.uuid = UUID_SECURE_PAYLOAD_BL32,
	},
	{
		.image_id = BL32_EXTRA1_IMAGE_ID,
		.uuid = UUID_SECURE_PAYLOAD_BL32_EXTRA1,
	},
#endif
	{
		.image_id = BL33_IMAGE_ID,
		.uuid = UUID_NON_TRUSTED_FIRMWARE_BL33,
	},
};

static struct plat_io_policy s32_policies[] = {
	[FIP_BACKEND_MEMMAP_ID] = {
		&s32_memmap_dev_handle,
		(uintptr_t)&fip_memmap_spec,
		s32_check_memmap_dev
	},
};

static int s32_check_mmc_dev(const uintptr_t spec)
{
	uintptr_t local_handle;
	int ret;

	ret = io_open(s32_mmc_dev_handle, spec, &local_handle);
	if (ret)
		return ret;
	/* must be closed, as load_image() will do another io_open() */
	io_close(local_handle);

	return 0;
}

static int s32_check_memmap_dev(const uintptr_t spec)
{
	uintptr_t local_handle;
	int ret;

	ret = io_open(s32_memmap_dev_handle, spec, &local_handle);
	if (ret)
		return ret;
	/* must be closed, as load_image() will do another io_open() */
	io_close(local_handle);

	return 0;
}

static bool is_mmc_boot_source(void)
{
	return !!fip_mmc_offset;
}

static unsigned long get_fip_offset(void)
{
	if (fip_mmc_offset)
		return fip_mmc_offset;

	if (fip_qspi_offset)
		return fip_qspi_offset;

	return fip_mem_offset;
}

static io_block_spec_t *get_image_spec_source(struct image_storage_info *info)
{
	if (info == NULL)
		return NULL;

	return &info->io_spec;
}

static io_block_spec_t * get_image_spec_from_id(unsigned int image_id)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(images_info); i++) {
		if (images_info[i].image_id == image_id)
			return get_image_spec_source(&images_info[i]);
	}

	return NULL;
}

static io_block_spec_t * get_image_spec_from_uuid(const uuid_t *uuid)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(images_info); i++) {
		if (compare_uuids(&images_info[i].uuid, uuid) == 0)
			return get_image_spec_source(&images_info[i]);
	}

	return NULL;
}

size_t get_image_max_offset(void)
{
	unsigned int i;
	size_t off, offset;

	bl2_platform_setup();

	offset = 0;

	for (i = 0; i < ARRAY_SIZE(images_info); i++) {
		off = images_info[i].io_spec.offset +
		    images_info[i].io_spec.length;
		if (off > offset)
			offset = off;
	}

	return offset;
}

/* This function is called after reading the FIP header and before loading
 * any other image from FIP.
 * The size and offset parameters are read from the FIP header
 * */
void set_image_spec(const uuid_t *uuid, uint64_t size, uint64_t offset)
{
	io_block_spec_t *spec = get_image_spec_from_uuid(uuid);

	if (spec == NULL)
		return;

	if (is_mmc_boot_source())
		spec->length = ROUND_TO_MMC_BLOCK_SIZE(size);
	else
		spec->length = size;

	/* In FIP header the offset is relative to the FIP header start.
	 * The real offset of the image is computed by adding the offset
	 * from the FIP header to the real FIP offset
	 * */
	spec->offset = get_fip_offset() + offset;
}

void dump_images_spec(void)
{
	size_t i;

	for (i = 0; i < ARRAY_SIZE(images_info); i++) {
		INFO("Image %u spec: offset=0x%lx length=0x%lx\n",
		     images_info[i].image_id, images_info[i].io_spec.offset,
		     images_info[i].io_spec.length);
	}
}

/* Before loading each image (e.g. load_image), this function is called from
 * plat_get_image_source() and performs the following actions:
 * - For the other images in FIP (e.g. BL31, BL32, BL33) this function is
 *   is called after the FIP header is parsed and the right offset and length
 *   for each image in the FIP header are set.
 *   When the function is called, it just passes the spec source (mmc, qspi or
 *   mem) that should have been already updated.
 * */
static void set_img_source(struct plat_io_policy *policy,
			       unsigned int image_id)
{
	io_block_spec_t *crt_spec = get_image_spec_from_id(image_id);

	if (crt_spec == NULL)
		return;

	policy->image_spec = (uintptr_t)crt_spec;

	if (is_mmc_boot_source()) {
		policy->dev_handle = &s32_mmc_dev_handle;
		policy->check = s32_check_mmc_dev;
	} else {
		policy->dev_handle = &s32_memmap_dev_handle;
		policy->check = s32_check_memmap_dev;
	}
}


int plat_get_image_source(unsigned int image_id, uintptr_t *dev_handle,
			  uintptr_t *image_spec)
{
	const struct plat_io_policy *policy;
	int ret;

	assert(image_id < ARRAY_SIZE(s32_policies));

	set_img_source(&s32_policies[image_id], image_id);

	policy = &s32_policies[image_id];
	assert(policy && policy->check);
	ret = policy->check(policy->image_spec);
	if (ret) {
		*dev_handle = (uintptr_t)NULL;
		*image_spec = (uintptr_t)NULL;
		return ret;
	}

	*dev_handle = *(policy->dev_handle);
	*image_spec = policy->image_spec;

	return 0;
}

void s32_io_setup(void)
{
	INFO("BL2: FIP offset = 0x%lx\n", get_fip_offset());

	if (register_io_dev_memmap(&s32_memmap_io_conn))
		goto err;
	if (io_dev_open(s32_memmap_io_conn, (uintptr_t)&fip_memmap_spec,
			&s32_memmap_dev_handle))
		goto err;
	if (io_dev_init(s32_memmap_dev_handle,
			(uintptr_t)FIP_BACKEND_MEMMAP_ID))
		goto err;

	if (!fip_mmc_offset)
		return;

	if (s32_mmc_register())
		goto err;
	if (register_io_dev_mmc(&s32_mmc_io_conn))
		goto err;

	/* Initialize MMC dev handle */
	if (io_dev_open(s32_mmc_io_conn,
			(uintptr_t)get_image_spec_from_id(BL2_IMAGE_ID),
			&s32_mmc_dev_handle))
		goto err;

	return;
err:
	ERROR("Error: %s failed\n", __func__);
	panic();
}

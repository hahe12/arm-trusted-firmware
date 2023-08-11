/*
 * Copyright 2019-2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef S32_STORAGE_H
#define S32_STORAGE_H

#include <tools_share/uuid.h>
#include <string.h>

#define FIP_HEADER_SIZE		(0x200)

struct plat_io_policy {
	uintptr_t *dev_handle;
	uintptr_t image_spec;
	int (*check)(const uintptr_t spec);
};

void s32_io_setup(void);

/* Return 0 for equal uuids. */
static inline int compare_uuids(const uuid_t *uuid1, const uuid_t *uuid2)
{
	return memcmp(uuid1, uuid2, sizeof(uuid_t));
}

void set_image_spec(const uuid_t *uuid, uint64_t size, uint64_t offset);
void dump_images_spec(void);
size_t get_image_max_offset(void);

#endif /* S32_STORAGE_H */

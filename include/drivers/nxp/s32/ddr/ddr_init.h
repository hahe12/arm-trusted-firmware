/*
 * Copyright 2020-2022 NXP
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DDR_INIT_H_
#define DDR_INIT_H_

#include <stdlib.h>
#include "ddr_utils.h"

#define APBONLY_MICRORESET   0x40380420U
#define MASTER_PLLCTRL1      0x403816f0U
#define MASTER_PLLTESTMODE   0x40381708U
#define MASTER_PLLCTRL4      0x4038171cU
#define MASTER_PLLCTRL2      0x403816dcU

#define MASTER_CALOFFSET     0x40381514U
#define MASTER_CALMISC2      0x40381660U

#define CALDRV               ((uint32_t)0x9U)
#define CALDRV_OFFSET        0x6U
#define CALDRV2_OFFSET       0xAU
#define CALDRV_MASK          ~(0x3FC0U)

#define CALMISC2             ((uint32_t)0x1U)
#define CALMISC2_OFFSET      0xDU

#define MICROCONT_MUX_SEL 0x40380400
#define LOCK_CSR_ACCESS   0x00000001
#define UNLOCK_CSR_ACCESS 0x00000000

#define APBONLY_RESET_TO_MICRO_MASK		0x00000008U
#define APBONLY_STALL_TO_MICRO_MASK		0x00000001U
#define APBONLY_RESET_STALL_MASK	APBONLY_RESET_TO_MICRO_MASK | \
	APBONLY_STALL_TO_MICRO_MASK
#define APBONLY_MICRORESET_CLR_MASK	0x00000000

#define PLLCTRL1_VALUE		0x00000021
#define PLLTESTMODE_VALUE	0x00000024
#define PLLCTRL4_VALUE		0x0000017F
#define PLLCTRL2_VALUE		0x00000019

#define FIRMWARE_VERSION "2020_06_SP2"

/* Enum for DRAM Type */
enum dram_type {
	DDR3L = 1,
	LPDDR4
};

struct regconf {
	uint32_t addr;
	uint32_t data;
};

struct regconf_16 {
	uint32_t addr;
	uint16_t data;
};

struct dqconf {
	uint32_t addr;
	uint8_t data;
};

struct ddrss_config {
	uint8_t memory_type;
	struct regconf *ddrc;
	size_t ddrc_size;
	struct dqconf *dq_swap;
	size_t dq_swap_size;
	struct regconf_16 *phy;
	size_t phy_size;
	uint16_t *imem_1d;
	size_t imem_1d_size;
	uint16_t *dmem_1d;
	size_t dmem_1d_size;
	uint16_t *imem_2d;
	size_t imem_2d_size;
	uint16_t *dmem_2d;
	size_t dmem_2d_size;
	struct regconf_16 *pie;
	size_t pie_size;
};

extern struct regconf ddrc_cfg[];
extern size_t ddrc_cfg_size;
extern struct dqconf dq_swap_cfg[];
extern size_t dq_swap_cfg_size;
extern struct regconf_16 phy_cfg[];
extern size_t phy_cfg_size;
extern uint16_t imem_1d_cfg[];
extern size_t imem_1d_cfg_size;
extern uint16_t dmem_1d_cfg[];
extern size_t dmem_1d_cfg_size;
extern uint16_t imem_2d_cfg[];
extern size_t imem_2d_cfg_size;
extern uint16_t dmem_2d_cfg[];
extern size_t dmem_2d_cfg_size;
extern struct regconf_16 pie_cfg[];
extern size_t pie_cfg_size;
extern struct ddrss_config configs[];
extern size_t ddrss_config_size;

/*
 * Full initialization of DDR SubSystem.
 * @return - error code, 0 if init succeeds, non-zero on error.
 */
uint32_t ddr_init(void);

/* Set initial sizes for all configuration images. */
void init_image_sizes(void);

/*
 * Writes the data associated for each address.
 *
 * @param size - size of the array, number of elements
 * @param cfg - array of configuration elements
 * @return - error code, 0 if init succeeds, non-zero on error.
 */
uint32_t load_register_cfg(size_t size, const struct regconf cfg[]);

/*
 * Writes the data associated for each address. Similar to
 * @load_register_cfg but uses 16bit data elements for memory
 * usage optimization.
 *
 * @param size - size of the array, number of elements
 * @param cfg - array of configuration elements
 * @return - error code, 0 if init succeeds, non-zero on error.
 */
uint32_t load_register_cfg_16(size_t size, const struct regconf_16 cfg[]);

/*
 * Writes the data associated for each address. Similar to
 * @load_register_cfg but uses 8bit data elements for memory
 * usage optimization.
 *
 * @param size - size of the array, number of elements
 * @param cfg - array of configuration elements
 * @return - error code, 0 if init succeeds, non-zero on error.
 */
uint32_t load_dq_cfg(size_t size, const struct dqconf cfg[]);

/* Updates PHY internal PLL settings. */
void set_optimal_pll(void);

#endif /* DDR_INIT_H */

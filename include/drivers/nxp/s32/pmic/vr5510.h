// SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause
/*
 * Copyright 2020-2022 NXP
 */
#ifndef VR5510_PMIC_H
#define VR5510_PMIC_H

#include <lib/utils_def.h>
#include "i2c/s32_i2c.h"

#define VR5510_MU_NAME		"vr5510"
#define VR5510_FSU_NAME		"vr5510_fsu"

#define VR5510_M_FLAG		0

#define VR5510_M_MODE		1
#define VR5510_MODE_PWRON1DIS	BIT(1)

/* Main Unit */
#define VR5510_M_SM_CTRL1	2
#define VR5510_CTRL1_GOTO_OFF		BIT(0)
#define VR5510_CTRL1_STBY_TIMER_EN	BIT(10)
#define VR5510_CTRL1_TIMER_STBY_WIN(N)	((N) << 12)
#define VR5510_CTRL1_TIMER_16MS		VR5510_CTRL1_TIMER_STBY_WIN(0)
#define VR5510_CTRL1_TIMER_32MS		VR5510_CTRL1_TIMER_STBY_WIN(1)
#define VR5510_CTRL1_TIMER_128MS	VR5510_CTRL1_TIMER_STBY_WIN(2)
#define VR5510_CTRL1_TIMER_512MS	VR5510_CTRL1_TIMER_STBY_WIN(3)
#define VR5510_CTRL1_TIMER_1024MS	VR5510_CTRL1_TIMER_STBY_WIN(4)
#define VR5510_CTRL1_TIMER_4096MS	VR5510_CTRL1_TIMER_STBY_WIN(5)

#define VR5510_M_REG_CTRL1	3
#define VR5510_M_REG_CTRL2	4

#define VR5510_M_REG_CTRL3	5
#define VR5510_CTRL3_BUCK1_STBY		BIT(0)
#define VR5510_CTRL3_BUCK2_STBY		BIT(2)
#define VR5510_CTRL3_BUCK3_STBY		BIT(4)
#define VR5510_CTRL3_VPREV_STBY		BIT(6)
#define VR5510_CTRL3_HVLDO_STBY		BIT(8)
#define VR5510_CTRL3_LDO1_STBY		BIT(10)
#define VR5510_CTRL3_LDO2_STBY		BIT(12)
#define VR5510_CTRL3_LDO3_STBY		BIT(14)

#define VR5510_M_TSD_CFG	6
#define VR5510_M_AMUX		7
#define VR5510_M_CLOCK1		8

#define VR5510_M_CLOCK2		9
#define VR5510_M_CLOCK2_100KHZ	0
#define VR5510_M_CLOCK2_300KHZ	2
#define VR5510_M_CLOCK2_600KHZ	3

#define VR5510_M_INT_MASK1	10
#define VR5510_M_INT_MASK2	11

#define VR5510_M_FLAG1		12
#define VR5510_FLAG1_ALL_FLAGS	0xBFFF

#define VR5510_M_FLAG2		13
#define VR5510_FLAG2_ALL_FLAGS	0xFFFF

#define VR5510_M_FLAG3		14
#define VR5510_FLAG3_I2C_M_REQ		BIT(0)
#define VR5510_FLAG3_I2C_M_CRC		BIT(1)

#define VR5510_M_VMON_REGX	15
#define VR5510_M_LVB1_SVS	16
#define VR5510_M_LVB1_STBY_DVS	17
#define VR5510_M_MEMORY0	41
#define VR5510_M_MEMORY1	42
#define VR5510_M_DEVICEID	43

/* Fail Safe unit */

/* Used for all FS_I_NOT_* registers */
#define VR5510_FS_I_NOT_VALUE(V)		(~(V) & 0xFFU)

#define VR5510_FS_GRL_FLAGS			0
#define VR5510_GRL_FLAGS_I2C_FS_REQ		BIT(5)
#define VR5510_GRL_FLAGS_I2C_FS_CRC		BIT(6)

#define VR5510_FS_I_OVUV_SAFE_REACTION1		1
#define VR5510_FS_I_NOT_OVUV_SAFE_REACTION1	2
#define VR5510_FS_I_OVUV_SAFE_REACTION2		3
#define VR5510_FS_I_NOT_OVUV_SAFE_REACTION2	4
#define VR5510_FS_I_ABIST2_CTRL			5
#define VR5510_FS_I_NOT_ABIST2_CTRL		6
#define VR5510_FS_I_WD_CFG			7
#define VR5510_ERR_CNT_MASK			0xF
#define VR5510_ERR_CNT(V)			((V) & VR5510_ERR_CNT_MASK)
#define VR5510_FS_I_NOT_WD_CFG			8

#define VR5510_FS_I_SAFE_INPUTS			9
#define VR5510_FCCU_CFG_OFFSET			14
#define VR5510_FCCU_CFG_MASK			(3 << VR5510_FCCU_CFG_OFFSET)
#define VR5510_FCCU_CFG(V)			((V) & VR5510_FCCU_CFG_MASK >>\
						 VR5510_FCCU_CFG_OFFSET)
#define VR5510_SAFE_INPUTS_TW_STBY_60US		0x4
#define VR5510_SAFE_INPUTS_TW_STBY_80US		0x5
#define VR5510_SAFE_INPUTS_TW_STBY_100US	0x6
#define VR5510_SAFE_INPUTS_TW_STBY_200US	0x7
#define VR5510_SAFE_INPUTS_TW_STBY_300US	0x8
#define VR5510_SAFE_INPUTS_TW_STBY_500US	0x9
#define VR5510_SAFE_INPUTS_TW_STBY_1MS		0xA
#define VR5510_SAFE_INPUTS_TW_STBY_2MS		0xB
#define VR5510_SAFE_INPUTS_TW_STBY_3MS		0xC
#define VR5510_SAFE_INPUTS_TW_STBY_5MS		0xD
#define VR5510_SAFE_INPUTS_TW_STBY_8MS		0xE
#define VR5510_SAFE_INPUTS_TW_STBY_10MS		0xF

#define VR5510_FS_I_NOT_SAFE_INPUTS		10
#define VR5510_FS_I_FSSM			11
#define VR5510_FS_I_NOT_FSSM			12
#define VR5510_FS_I_SVS				13
#define VR5510_FS_I_SVS_SVS_OFFSET		10
#define VR5510_FS_I_NOT_SVS			14
#define VR5510_FS_WD_WINDOW			15
#define VR5510_WD_WINDOW_OFFSET			12
#define VR5510_WD_WINDOW_MASK			0xF000
#define VR5510_FS_NOT_WD_WINDOW			16
#define VR5510_FS_WD_SEED			17
#define VR5510_FS_WD_ANSWER			18
#define VR5510_FS_OVUVREG_STATUS		19
#define VR5510_FS_RELEASE_FS0B			20

#define VR5510_FS_SAFE_IOS			21
#define VR5510_SAFE_IOS_STBY_REQ		BIT(1)
#define VR5510_SAFE_IOS_GOTO_INITFS		BIT(2)

#define VR5510_FS_DIAG_SAFETY			22
#define VR5510_ABIST1_OK_OFFSET			10
#define VR5510_ABIST1_OK_MASK			BIT(VR5510_ABIST1_OK_OFFSET)
#define VR5510_ABIST1_OK(V)			((V) & VR5510_ABIST1_OK_MASK >>\
						 VR5510_ABIST1_OK_OFFSET)
#define VR5510_FS_INTB_MASK			23
#define VR5510_FS_STATES			24
#define VR5510_STATE_MASK			0x1FU
#define VR5510_STATE_OFFSET			0
#define VR5510_STATE(V)				(((V) & VR5510_STATE_MASK) >>\
						 VR5510_STATE_OFFSET)

enum fs_states {
	INIT_FS = 6,
	WAIT_ABIST2,
	ABIST2,
	ASSERT_FS0B,
	NORMAL_FS,
};

struct vr5510_inst;
typedef struct vr5510_inst *vr5510_t;

int vr5510_register_instance(void *fdt, int fdt_offset,
			     struct s32_i2c_bus *bus);

int vr5510_get_inst(const char *name, vr5510_t *inst);
int vr5510_read(vr5510_t dev, uint8_t reg, uint8_t *buff, int len);
int vr5510_write(vr5510_t dev, uint8_t reg,
		 const uint8_t *buff, int len);

#endif

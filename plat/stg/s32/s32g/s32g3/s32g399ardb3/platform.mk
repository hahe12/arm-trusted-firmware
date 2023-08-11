#
# Copyright 2022-2023 NXP
#
# SPDX-License-Identifier: BSD-3-Clause
#

include plat/stg/s32/s32g/s32g3/s32g3.mk

S32_BOARD_PATH		:= ${PLAT_SOC_PATH}/s32g399ardb3

PLAT_INCLUDES		+= -I${S32_BOARD_PATH}/include \

DTB_FILE_NAME		?= s32g399a-rdb3.dtb

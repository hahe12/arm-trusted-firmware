/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright 2020-2021, 2023 NXP
 */
#ifndef __DT_BINDINGS_SCMI_CLOCK_S32G274A_H
#define __DT_BINDINGS_SCMI_CLOCK_S32G274A_H

#include <dt-bindings/clock/s32gen1-scmi-clock.h>

/* USB */
#define S32G_SCMI_CLK_USB_MEM		S32GEN1_PLAT_SCMI_CLK(0)
#define S32G_SCMI_CLK_USB_LOW		S32GEN1_PLAT_SCMI_CLK(1)

/* PFE 0 */
/* SGMII RX: PFE_MAC_0_RX_CLK -> SERDES_1_LANE_0_CDR_CLK */
#define S32G_SCMI_CLK_PFE0_RX_SGMII		S32GEN1_PLAT_SCMI_CLK(2)
/* SGMII TX: PFE_MAC_0_TX_CLK -> SERDES_1_LANE_0_TX_CLK  */
#define S32G_SCMI_CLK_PFE0_TX_SGMII		S32GEN1_PLAT_SCMI_CLK(3)
/* RGMII RX: PFE_MAC_0_RX_CLK -> PFE_MAC0_RX_CLK_I */
#define S32G_SCMI_CLK_PFE0_RX_RGMII		S32GEN1_PLAT_SCMI_CLK(4)
/* RGMII TX: PFE_MAC_0_TX_CLK -> PERIPH_PLL_PHI5_CLK */
#define S32G_SCMI_CLK_PFE0_TX_RGMII		S32GEN1_PLAT_SCMI_CLK(5)
#define S32G_SCMI_CLK_PFE0_RX_RMII		S32GEN1_PLAT_SCMI_CLK(6)
#define S32G_SCMI_CLK_PFE0_TX_RMII		S32GEN1_PLAT_SCMI_CLK(7)
#define S32G_SCMI_CLK_PFE0_RX_MII		S32GEN1_PLAT_SCMI_CLK(8)
#define S32G_SCMI_CLK_PFE0_TX_MII		S32GEN1_PLAT_SCMI_CLK(9)

/* PFE 1 */
/* SGMII RX: PFE_MAC_1_RX_CLK -> SERDES_1_LANE_1_CDR_CLK */
#define S32G_SCMI_CLK_PFE1_RX_SGMII		S32GEN1_PLAT_SCMI_CLK(10)
/* SGMII TX: PFE_MAC_1_TX_CLK -> SERDES_1_LANE_1_TX_CLK  */
#define S32G_SCMI_CLK_PFE1_TX_SGMII		S32GEN1_PLAT_SCMI_CLK(11)
/* RGMII RX: PFE_MAC_1_RX_CLK ->  PFE_MAC1_RX_CLK_I */
#define S32G_SCMI_CLK_PFE1_RX_RGMII		S32GEN1_PLAT_SCMI_CLK(12)
/* RGMII TX: PFE_MAC_1_TX_CLK ->  PERIPH_PLL_PHI5_CLK */
#define S32G_SCMI_CLK_PFE1_TX_RGMII		S32GEN1_PLAT_SCMI_CLK(13)
#define S32G_SCMI_CLK_PFE1_RX_RMII		S32GEN1_PLAT_SCMI_CLK(14)
#define S32G_SCMI_CLK_PFE1_TX_RMII		S32GEN1_PLAT_SCMI_CLK(15)
#define S32G_SCMI_CLK_PFE1_RX_MII		S32GEN1_PLAT_SCMI_CLK(16)
#define S32G_SCMI_CLK_PFE1_TX_MII		S32GEN1_PLAT_SCMI_CLK(17)

/* PFE 2 */
/* SGMII RX: PFE_MAC_2_RX_CLK -> SERDES_0_LANE_1_CDR_CLK */
#define S32G_SCMI_CLK_PFE2_RX_SGMII		S32GEN1_PLAT_SCMI_CLK(18)
/* SGMII TX: PFE_MAC_2_TX_CLK -> SERDES_0_LANE_1_TX_CLK  */
#define S32G_SCMI_CLK_PFE2_TX_SGMII		S32GEN1_PLAT_SCMI_CLK(19)
/* RGMII RX: PFE_MAC_2_RX_CLK ->  PFE_MAC2_RX_CLK_I */
#define S32G_SCMI_CLK_PFE2_RX_RGMII		S32GEN1_PLAT_SCMI_CLK(20)
/* RGMII TX: PFE_MAC_2_TX_CLK ->  PERIPH_PLL_PHI5_CLK */
#define S32G_SCMI_CLK_PFE2_TX_RGMII		S32GEN1_PLAT_SCMI_CLK(21)
#define S32G_SCMI_CLK_PFE2_RX_RMII		S32GEN1_PLAT_SCMI_CLK(22)
#define S32G_SCMI_CLK_PFE2_TX_RMII		S32GEN1_PLAT_SCMI_CLK(23)
#define S32G_SCMI_CLK_PFE2_RX_MII		S32GEN1_PLAT_SCMI_CLK(24)
#define S32G_SCMI_CLK_PFE2_TX_MII		S32GEN1_PLAT_SCMI_CLK(25)

/* PFE system clocks */
#define S32G_SCMI_CLK_PFE_AXI		S32GEN1_PLAT_SCMI_CLK(26)
#define S32G_SCMI_CLK_PFE_APB		S32GEN1_PLAT_SCMI_CLK(27)
#define S32G_SCMI_CLK_PFE_PE		S32GEN1_PLAT_SCMI_CLK(28)
#define S32G_SCMI_CLK_PFE_TS		S32GEN1_PLAT_SCMI_CLK(29)

/* LLCE */
#define S32G_SCMI_CLK_LLCE_CAN_PE	S32GEN1_PLAT_SCMI_CLK(30)
#define S32G_SCMI_CLK_LLCE_SYS		S32GEN1_PLAT_SCMI_CLK(31)

#define S32G_SCMI_CLK_MAX_ID		S32GEN1_PLAT_SCMI_CLK(32)

#if S32GEN1_SCMI_CLK_MAX_ID < S32G_SCMI_CLK_MAX_ID
#error Please increase the value of S32GEN1_SCMI_CLK_MAX_ID
#endif

#endif

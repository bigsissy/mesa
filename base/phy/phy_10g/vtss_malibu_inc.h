// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#if defined(VTSS_CHIP_10G_PHY)
#include "vtss_api.h"
#include "../../ail/vtss_state.h"
#include "../../ail/vtss_common.h"
#include "../common/vtss_phy_common.h"
#include "../../ail/vtss_sd10g65_procs.h"
#include "../../ail/vtss_sd10g65_apc_procs.h"
#include "../../ail/vtss_pll5g_procs.h"
#include "vtss_phy_10g.h"

#ifndef _MAL_IO_VAR
#define _MAL_IO_VAR
ioreg_blk mal_io_var;
#endif

#if defined(VTSS_IOREG)
#undef VTSS_IOREG
#endif

#define VTSS_IOREG(dev, is32, off)  _ioreg(&mal_io_var, (dev), (is32), (off))
#include "chips/malibu/vtss_malibu_regs.h"

/* some of the register definitions which are missing in register files */

#define VTSS_HOST_KR_DEV7_LD_adv_KR_7x0011_ADV_1G VTSS_BIT(5)
#define VTSS_HOST_KR_DEV7_LD_adv_KR_7x0011_ADV_10G VTSS_BIT(7)

#define VTSS_HOST_KR_DEV7_LD_adv_KR_7x0012_FEC_ABILITY VTSS_BIT(14)
#define VTSS_HOST_KR_DEV7_LD_adv_KR_7x0012_FEC_REQUEST VTSS_BIT(15)

#define VTSS_LINE_KR_DEV7_LD_adv_KR_7x0011_ADV_1G VTSS_BIT(5)
#define VTSS_LINE_KR_DEV7_LD_adv_KR_7x0011_ADV_10G VTSS_BIT(7)

#define VTSS_LINE_KR_DEV7_LD_adv_KR_7x0012_FEC_ABILITY VTSS_BIT(14)
#define VTSS_LINE_KR_DEV7_LD_adv_KR_7x0012_FEC_REQUEST VTSS_BIT(15)

#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_GAIN_ADJ_S  VTSS_BIT(15)
#define VTSS_F2DF_DF2F_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG VTSS_IOREG(0x1e, 1, 0xf014)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_EN VTSS_BIT(0)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_SPEED_SEL(x) VTSS_ENCODE_BITFIELD(x,1,2)
#define VTSS_M_F2DF_DF2F_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_SPEED_SEL VTSS_ENCODE_BITMASK(1,2)

#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_SPARE_POOL(x) VTSS_ENCODE_BITFIELD(x,26,4)
#define VTSS_M_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_SPARE_POOL VTSS_ENCODE_BITMASK(26,4)

#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA(x) VTSS_ENCODE_BITFIELD(x,18,5)
#define VTSS_M_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA VTSS_ENCODE_BITMASK(18,5)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_DIR VTSS_BIT(9)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_DIR VTSS_BIT(6)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CONV_ENA VTSS_BIT(1)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_ENA_SYNC_UNIT VTSS_BIT(2)

#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3_SYNTH_FREQM_0(x) VTSS_ENCODE_BITFIELD(x,0,31)
#define VTSS_M_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3_SYNTH_FREQM_0 VTSS_ENCODE_BITMASK(0,31)

#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4_SYNTH_FREQN_0(x) VTSS_ENCODE_BITFIELD(x,0,31)
#define VTSS_M_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4_SYNTH_FREQN_0 VTSS_ENCODE_BITMASK(0,31)

#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI(x) VTSS_ENCODE_BITFIELD(x,22,4)
#define VTSS_M_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI VTSS_ENCODE_BITMASK(22,4)


#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_OOR_RECAL_ENA VTSS_BIT(6)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_LOOP_ENA VTSS_BIT(10)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_LOOP_CTRL_ENA VTSS_BIT(11)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_SYN_CLK_ENA VTSS_BIT(15)

#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VREG18(x) VTSS_ENCODE_BITFIELD(x,20,4)
#define VTSS_M_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VREG18 VTSS_ENCODE_BITMASK(20, 4)

#define VTSS_M_F2DF_DF2F_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_SPARE_POOL VTSS_ENCODE_BITMASK(16,4)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_SPARE_POOL(x) VTSS_ENCODE_BITFIELD(x,16,4)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define VTSS_M_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA VTSS_ENCODE_BITMASK(18,4)
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_OOR_RECAL_ENA  VTSS_BIT(6)
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_LOOP_ENA  VTSS_BIT(10)
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_LOOP_CTRL_ENA  VTSS_BIT(11)
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_SYN_CLK_ENA  VTSS_BIT(15)
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VREG18(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_F2DF_DF2F_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VREG18     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VCO_CUR(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_F2DF_DF2F_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VCO_CUR     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_CONV_ENA  VTSS_BIT(1)
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI(x)  VTSS_ENCODE_BITFIELD(x,22,4)
#define  VTSS_M_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI     VTSS_ENCODE_BITMASK(22,4)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG3_SYNTH_FREQM_0(x) VTSS_ENCODE_BITFIELD(x,0,31)
#define VTSS_M_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG3_SYNTH_FREQM_0 VTSS_ENCODE_BITMASK(0,31)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG4_SYNTH_FREQN_0(x) VTSS_ENCODE_BITFIELD(x,0,31)
#define VTSS_M_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG4_SYNTH_FREQN_0 VTSS_ENCODE_BITMASK(0,31)
#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_SPARE_POOL(x) VTSS_ENCODE_BITFIELD(x,22,8)
#define VTSS_M_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_SPARE_POOL VTSS_ENCODE_BITMASK(22,8)

#define VTSS_F_LINE_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI(x) VTSS_ENCODE_BITFIELD(x,22,4)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI VTSS_ENCODE_BITMASK(22,4)


#define VTSS_F_LINE_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_SPARE_POOL(x) VTSS_ENCODE_BITFIELD(x,22,8) 
#define VTSS_M_LINE_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_SPARE_POOL VTSS_ENCODE_BITMASK(22,8)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_SYN_CLK_ENA VTSS_BIT(15)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_LOOP_CTRL_ENA VTSS_BIT(11)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_LOOP_ENA VTSS_BIT(10)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_OOR_RECAL_ENA VTSS_BIT(6)

#define VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA VTSS_ENCODE_BITMASK(18,4)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA(x)  VTSS_ENCODE_BITFIELD(x,18,4)
#define VTSS_M_LINE_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA VTSS_ENCODE_BITMASK(18,4)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_SKIP_CAL VTSS_BIT(9)

#define VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_F2DF_CFG_STAT_F2DF_STICKY_CLR VTSS_BIT(2)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA(x) VTSS_ENCODE_BITFIELD(x,18,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA VTSS_ENCODE_BITMASK(18,5)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_CAL_VSC_OFFSET_TGT  VTSS_BIT(15)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_THR_CAL_VAL  VTSS_BIT(14)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_COMMON_CFG0_SKIP_CAL  VTSS_BIT(9)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_OOR_RECAL_ENA  VTSS_BIT(6)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_LOOP_ENA  VTSS_BIT(10)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_LOOP_CTRL_ENA  VTSS_BIT(11)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG0_PLLF_SYN_CLK_ENA  VTSS_BIT(15)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VREG18(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VREG18     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VCO_CUR(x) VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VCO_CUR VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_CONV_ENA  VTSS_BIT(1)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI(x)  VTSS_ENCODE_BITFIELD(x,22,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI     VTSS_ENCODE_BITMASK(22,4)
#define VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG3_SYNTH_FREQM_0(x) VTSS_ENCODE_BITFIELD(x,0,31)
#define VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG3_SYNTH_FREQM_0 VTSS_ENCODE_BITMASK(0,31)
#define VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG4_SYNTH_FREQN_0(x) VTSS_ENCODE_BITFIELD(x,0,31)
#define VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG4_SYNTH_FREQN_0 VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_SPARE_POOL(x)  VTSS_ENCODE_BITFIELD(x,22,8)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_SPARE_POOL     VTSS_ENCODE_BITMASK(22,8)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_OOR_RECAL_ENA  VTSS_BIT(6)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_LOOP_ENA  VTSS_BIT(10)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_LOOP_CTRL_ENA  VTSS_BIT(11)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_SYN_CLK_ENA  VTSS_BIT(15)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VREG18(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VREG18     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VCO_CUR(x) VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VCO_CUR VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_DIR  VTSS_BIT(9)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_DIR  VTSS_BIT(6)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CONV_ENA  VTSS_BIT(1)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_ENA_SYNC_UNIT  VTSS_BIT(2)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI(x)  VTSS_ENCODE_BITFIELD(x,22,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI     VTSS_ENCODE_BITMASK(22,4)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3_SYNTH_FREQM_0(x) VTSS_ENCODE_BITFIELD(x,0,31)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3_SYNTH_FREQM_0 VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4_SYNTH_FREQN_0(x) VTSS_ENCODE_BITFIELD(x,0,31)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4_SYNTH_FREQN_0 VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_SPARE_POOL(x)  VTSS_ENCODE_BITFIELD(x,26,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_SPARE_POOL     VTSS_ENCODE_BITMASK(26,4)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_SPEED_SEL     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_EN  VTSS_BIT(0)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_APC_APC_IS_CAL_CFG1_CAL_VSC_OFFSET_TGT  VTSS_BIT(15)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_THR_CAL_VAL  VTSS_BIT(14)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VREG18(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VREG18     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VCO_CUR(x) VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_CFG2_PLL_VCO_CUR VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG0_SYNTH_CONV_ENA  VTSS_BIT(1)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG3_SYNTH_FREQM_0(x) VTSS_ENCODE_BITFIELD(x,0,31)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG3_SYNTH_FREQM_0 VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG4_SYNTH_FREQN_0(x) VTSS_ENCODE_BITFIELD(x,0,31)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG4_SYNTH_FREQN_0 VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_LOOP_ENA  VTSS_BIT(10)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_OOR_RECAL_ENA  VTSS_BIT(6)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_LOOP_CTRL_ENA  VTSS_BIT(11)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG0_PLLF_SYN_CLK_ENA  VTSS_BIT(15)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VREG18(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VREG18     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VCO_CUR(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VCO_CUR VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_LS_DIR  VTSS_BIT(9)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_DS_DIR  VTSS_BIT(6)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CONV_ENA  VTSS_BIT(1)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_ENA_SYNC_UNIT  VTSS_BIT(2)
#define VTSS_LINE_PMA_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG VTSS_IOREG(0x01, 1, 0xf114)
#define VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG VTSS_IOREG(0x09, 1, 0xf114)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_SPARE_POOL(x)  VTSS_ENCODE_BITFIELD(x,26,4)
#define VTSS_M_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_SPARE_POOL     VTSS_ENCODE_BITMASK(26,4)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA(x)  VTSS_ENCODE_BITFIELD(x,18,5)
#define VTSS_M_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_OFF_COMP_ENA     VTSS_ENCODE_BITMASK(18,5)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_EN  VTSS_BIT(0)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_SPEED_SEL(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define VTSS_M_LINE_PMA_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG_SBUS_BIAS_SPEED_SEL     VTSS_ENCODE_BITMASK(1,2)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3_SYNTH_FREQM_0(x) VTSS_ENCODE_BITFIELD(x,0,31)
#define VTSS_M_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG3_SYNTH_FREQM_0 VTSS_ENCODE_BITMASK(0,31)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4_SYNTH_FREQN_0(x) VTSS_ENCODE_BITFIELD(x,0,31)
#define VTSS_M_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG4_SYNTH_FREQN_0 VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI(x)  VTSS_ENCODE_BITFIELD(x,22,4)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_HI     VTSS_ENCODE_BITMASK(22,4)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CS_SPEED(x)  VTSS_ENCODE_BITFIELD(x,11,3)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG0_SYNTH_CS_SPEED     VTSS_ENCODE_BITMASK(11,3)


//register definitions required for REV B
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_BYP  VTSS_BIT(26)
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_BYP  VTSS_BIT(26)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_BYP  VTSS_BIT(26)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_BYP  VTSS_BIT(26)

/** 
 * \brief APC LC softcontrol configuration register
 *
 * \details
 * Configuration register 0 for the LC-Softcontrol logic block. The L and C
 * paramters can be controlled depending on DFE1 and DFE2 and EQZ_AGC
 * parameters instead of pattern matching.
 *
 * Register: \a LINE_PMA_32BIT:SD10G65_APC:APC_LC_SOFTCTRL_CFG
 */
#define VTSS_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG  VTSS_IOREG(0x01, 1, 0xf02a)

/** 
 * \brief
 * Operation timer configuration: L/C-control operates in every
 * 2^(2*LC_SC_TIMER)-th clock cycle.
 *
 * \details 
 * 0: Operate every clock cycle
 * 1: Operate every 4th clock cycle
 * 2: Operate every 16th clock cycle
 * ...
 *
 * Field: VTSS_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG . LC_SC_TIMER
 */
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_TIMER(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_TIMER     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,28,4)

/** 
 * \brief
 * DFE1/2 and EQZ_AGC averaging behavior. DFE/AGC parameters are averaged
 * over 2^(8+LC_SC_AVGSHFT) input values.
 *
 * \details 
 * 0: Average over 256 values
 * 1: Average over 512 values
 * ...
 *
 * Field: VTSS_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG . LC_SC_AVGSHFT
 */
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_AVGSHFT(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_AVGSHFT     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_AVGSHFT(x)  VTSS_EXTRACT_BITFIELD(x,24,4)

/** 
 * \brief
 * DFE1 comparison threshold for L-control used in mode 2. EQZ_L is
 * increased/decreased if DFE1 differs from neutral value by more than
 * LC_SC_DFE1_THRESHOLD.
 *
 * \details 
 * Field: VTSS_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG . LC_SC_DFE1_THRESHOLD
 */
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DFE1_THRESHOLD(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DFE1_THRESHOLD     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DFE1_THRESHOLD(x)  VTSS_EXTRACT_BITFIELD(x,20,4)

/** 
 * \brief
 * DFE2 comparison threshold for C-control used in mode 2. EQZ_C is
 * increased/decreased if DFE1 differs from neutral value by more than
 * LC_SC_DFE2_THRESHOLD.
 *
 * \details 
 * Field: VTSS_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG . LC_SC_DFE2_THRESHOLD
 */
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DFE2_THRESHOLD(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DFE2_THRESHOLD     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DFE2_THRESHOLD(x)  VTSS_EXTRACT_BITFIELD(x,16,4)

/** 
 * \brief
 * EQZ_AGC threshold for mandatory increase of L and C. If EQZ_AGC >
 * (128+LC_SC_AGC_THRESHOLD) then L and C control values are increased.
 *
 * \details 
 * 0: 128
 * 1: 129
 * ...
 * 127: 255
 *
 * Field: VTSS_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG . LC_SC_AGC_THRESHOLD
 */
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_AGC_THRESHOLD(x)  VTSS_ENCODE_BITFIELD(x,9,7)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_AGC_THRESHOLD     VTSS_ENCODE_BITMASK(9,7)
#define  VTSS_X_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_AGC_THRESHOLD(x)  VTSS_EXTRACT_BITFIELD(x,9,7)

/** 
 * \brief
 * Define DFE2 comparison parameter for EQZ_C control in mode 1
 *
 * \details 
 * 0: EQZ_L
 * 1: EQZ_C
 *
 * Field: VTSS_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG . LC_SC_DIV_C_SEL
 */
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_C_SEL  VTSS_BIT(8)

/** 
 * \brief
 * Select divider for L-control used in mode 1 (Divider = 4+LC_SC_DIV_L)
 *
 * \details 
 * 0: Divide by 4
 * 1: Devide by 5
 * ...
 * 7: Devide by 11
 *
 * Field: VTSS_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG . LC_SC_DIV_L
 */
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_L(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_L     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_L(x)  VTSS_EXTRACT_BITFIELD(x,5,3)

/** 
 * \brief
 * Select divider for C-control used in mode 1 (Divider = 4+LC_SC_DIV_C)
 *
 * \details 
 * 0: Divide by 4
 * 1: Devide by 5
 * ...
 * 7: Devide by 11
 *
 * Field: VTSS_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG . LC_SC_DIV_C
 */
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_C(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_C     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_C(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/** 
 * \brief
 * Select LC soft-control mode. LC soft-control modes must be enabled first
 * after INI/MIN/MAX values of all parameters have been programmed.
 *
 * \details 
 * 0: Disabled
 * 1: Mode 1
 * 2: Mode 2
 * 3: Reserved
 *
 * Field: VTSS_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG . LC_SC_MODE
 */
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/** 
 * \brief APC LC softcontrol configuration register 1
 *
 * \details
 * Configuration register 1 for the LC-Softcontrol logic block.
 *
 * Register: \a LINE_PMA_32BIT:SD10G65_APC:APC_LC_SOFTCTRL_CFG1
 */
#define VTSS_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1  VTSS_IOREG(0x01, 1, 0xf02b)

/** 
 * \brief
 * Target value for DFE2 during L/C-control operation
 *
 * \details 
 * Field: VTSS_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1 . LC_SC_DFE2_TARGET
 */
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1_LC_SC_DFE2_TARGET(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1_LC_SC_DFE2_TARGET     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1_LC_SC_DFE2_TARGET(x)  VTSS_EXTRACT_BITFIELD(x,8,6)

/** 
 * \brief
 * Target value for DFE1 during L/C-control operation
 *
 * \details 
 * Field: VTSS_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1 . LC_SC_DFE1_TARGET
 */
#define  VTSS_F_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1_LC_SC_DFE1_TARGET(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1_LC_SC_DFE1_TARGET     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_LINE_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1_LC_SC_DFE1_TARGET(x)  VTSS_EXTRACT_BITFIELD(x,0,7)

//description same as above set of register for line side.
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG  VTSS_IOREG(0x09, 1, 0xf02a)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_TIMER(x)  VTSS_ENCODE_BITFIELD(x,28,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_TIMER     VTSS_ENCODE_BITMASK(28,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,28,4)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_AVGSHFT(x)  VTSS_ENCODE_BITFIELD(x,24,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_AVGSHFT     VTSS_ENCODE_BITMASK(24,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_AVGSHFT(x)  VTSS_EXTRACT_BITFIELD(x,24,4)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DFE1_THRESHOLD(x)  VTSS_ENCODE_BITFIELD(x,20,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DFE1_THRESHOLD     VTSS_ENCODE_BITMASK(20,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DFE1_THRESHOLD(x)  VTSS_EXTRACT_BITFIELD(x,20,4)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DFE2_THRESHOLD(x)  VTSS_ENCODE_BITFIELD(x,16,4)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DFE2_THRESHOLD     VTSS_ENCODE_BITMASK(16,4)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DFE2_THRESHOLD(x)  VTSS_EXTRACT_BITFIELD(x,16,4)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_AGC_THRESHOLD(x)  VTSS_ENCODE_BITFIELD(x,9,7)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_AGC_THRESHOLD     VTSS_ENCODE_BITMASK(9,7)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_AGC_THRESHOLD(x)  VTSS_EXTRACT_BITFIELD(x,9,7)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_C_SEL  VTSS_BIT(8)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_L(x)  VTSS_ENCODE_BITFIELD(x,5,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_L     VTSS_ENCODE_BITMASK(5,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_L(x)  VTSS_EXTRACT_BITFIELD(x,5,3)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_C(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_C     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_DIV_C(x)  VTSS_EXTRACT_BITFIELD(x,2,3)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_MODE(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_MODE     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG_LC_SC_MODE(x)  VTSS_EXTRACT_BITFIELD(x,0,2)
#define VTSS_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1  VTSS_IOREG(0x09, 1, 0xf02b)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1_LC_SC_DFE2_TARGET(x)  VTSS_ENCODE_BITFIELD(x,8,6)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1_LC_SC_DFE2_TARGET     VTSS_ENCODE_BITMASK(8,6)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1_LC_SC_DFE2_TARGET(x)  VTSS_EXTRACT_BITFIELD(x,8,6)
#define  VTSS_F_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1_LC_SC_DFE1_TARGET(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1_LC_SC_DFE1_TARGET     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_HOST_PMA_32BIT_SD10G65_APC_APC_LC_SOFTCTRL_CFG1_LC_SC_DFE1_TARGET(x)  VTSS_EXTRACT_BITFIELD(x,0,7)
#define VTSS_LINE_PMA_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG VTSS_IOREG(0x01, 1, 0xf114)
#define VTSS_HOST_PMA_32BIT_SD10G65_OB_SD10G65_SBUS_TX_CFG VTSS_IOREG(0x09, 1, 0xf114)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_GAIN_ADJ_S  VTSS_BIT(15)
#define VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_IB_CFG7_IB_DFE_GAIN_ADJ_S  VTSS_BIT(15)
#define VTSS_M_LINE_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_SPARE_POOL VTSS_ENCODE_BITMASK(16,4)
#define VTSS_F_LINE_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_SPARE_POOL(x) VTSS_ENCODE_BITFIELD(x,16,4)
#define VTSS_M_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_SPARE_POOL VTSS_ENCODE_BITMASK(16,4)
#define VTSS_F_HOST_PMA_32BIT_SD10G65_IB_SD10G65_SBUS_RX_CFG_SBUS_SPARE_POOL(x) VTSS_ENCODE_BITFIELD(x,16,4)
#define VTSS_X_HOST_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_FSM_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)
#define VTSS_X_HOST_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_FSM_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)
#define VTSS_X_LINE_PMA_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_FSM_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)
#define VTSS_X_LINE_PMA_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_FSM_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

/**
 * \brief
 * Invert calibration value coming from the calibration FSM for IS
 * threshold calibration.
 *
 * \details
 * Field: VTSS_F2DF_DF2F_32BIT_SD10G65_IB_SD10G65_IB_CFG8 . IB_INV_THR_CAL_VAL
 */
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_IB_SD10G65_IB_CFG8_IB_INV_THR_CAL_VAL  VTSS_BIT(14)



/**
 * \brief
 * Controls the offset calibration target of the VScope FFs. Coding: 0:
 * calibration target is zero, 1: calibration target is the programmed
 * VScope threshold.
 *
 * \details
 * Field: VTSS_F2DF_DF2F_32BIT_SD10G65_ACC_APC_IS_CAL_CFG1 . CAL_VSC_OFFSET_TGT
 */
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_ACC_APC_IS_CAL_CFG1_CAL_VSC_OFFSET_TGT  VTSS_BIT(15)



/**
 * \brief
 * frequency multiplier decoder bypass
 *
 * \details
 * Field: VTSS_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1 . SYNTH_FREQ_MULT_BYP
 */
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_SYNTH_SD10G65_TX_SYNTH_CFG1_SYNTH_FREQ_MULT_BYP  VTSS_BIT(26)


/**
 * \brief
 * Select vco current,
 *
 * \details
 * 0: lowest current
 * 31: highest current
 *
 * Field: VTSS_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2 . PLL_VCO_CUR
 */
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VCO_CUR(x)  VTSS_ENCODE_BITFIELD(x,2,5)
#define  VTSS_M_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VCO_CUR     VTSS_ENCODE_BITMASK(2,5)
#define  VTSS_X_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_CFG2_PLL_VCO_CUR(x)  VTSS_EXTRACT_BITFIELD(x,2,5)

/**
 * \brief
 * Actual value of the FSM stage,
 *
 * \details
 * 0: reset state
 * 1: init state after reset
 * 3: ramp up state checks for the counters and ramps up the frequency
 * 6: additional wait state for internal BIAS settling
 * 8: additional wait state 1
 * 9: additional wait state 2
 * 10; additional wait state 3
 * 11: additional wait state 4
 * 12: 1st locking state enables dynamic locking
 * 13: final locking state checks for out of lock and overrun condition
 * 14: error state low frequency
 * 15: error state high frequency
 *
 * Field: VTSS_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1 . PLLF_FSM_STAT
 */
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_FSM_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_FSM_STAT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_F2DF_DF2F_32BIT_SD10G65_TX_RCPLL_SD10G65_TX_RCPLL_STAT1_PLLF_FSM_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)




/**
 * \brief
 * frequency multiplier decoder bypass
 *
 * \details
 * Field: VTSS_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1 . SYNTH_FREQ_MULT_BYP
 */
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_SYNTH_SD10G65_RX_SYNTH_CFG1_SYNTH_FREQ_MULT_BYP  VTSS_BIT(26)

/**
 * \brief
 * Actual value of the FSM stage,
 *
 * \details
 * 0: reset state
 * 1: init state after reset
 * 3: ramp up state checks for the counters and ramps up the frequency
 * 6: additional wait state for internal BIAS settling
 * 8: additional wait state 1
 * 9: additional wait state 2
 * 10; additional wait state 3
 * 11: additional wait state 4
 * 12: 1st locking state enables dynamic locking
 * 13: final locking state checks for out of lock and overrun condition
 * 14: error state low frequency
 * 15: error state high frequency
 *
 * Field: VTSS_F2DF_DF2F_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1 . PLLF_FSM_STAT
 */
#define  VTSS_F_F2DF_DF2F_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_FSM_STAT(x)  VTSS_ENCODE_BITFIELD(x,0,4)
#define  VTSS_M_F2DF_DF2F_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_FSM_STAT     VTSS_ENCODE_BITMASK(0,4)
#define  VTSS_X_F2DF_DF2F_32BIT_SD10G65_RX_RCPLL_SD10G65_RX_RCPLL_STAT1_PLLF_FSM_STAT(x)  VTSS_EXTRACT_BITFIELD(x,0,4)

#endif

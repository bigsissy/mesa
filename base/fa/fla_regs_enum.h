// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

// This file is autogenerated by cml-utils 2022-12-02 08:57:23 +0100.
// Commit ID: 1fb411dcf848d8deb97976d8795eb3edef248fbc (dirty)

enum fla_targets {
	TGT_TO_AFI,
	TGT_TO_ANA_AC,
	TGT_TO_ANA_AC_OAM_MOD,
	TGT_TO_ANA_AC_POL,
	TGT_TO_ANA_AC_SDLB,
	TGT_TO_ANA_ACL,
	TGT_TO_ANA_CL,
	TGT_TO_ANA_L2,
	TGT_TO_ANA_L3,
	TGT_TO_ASM,
	TGT_TO_CHIP_TOP,
	TGT_TO_CPU,
	TGT_TO_DEV10G_0,
	TGT_TO_DEV10G_1,
	TGT_TO_DEV10G_2,
	TGT_TO_DEV10G_3,
	TGT_TO_DEV10G_4,
	TGT_TO_DEV10G_5,
	TGT_TO_DEV10G_6,
	TGT_TO_DEV10G_7,
	TGT_TO_DEV10G_8,
	TGT_TO_DEV10G_9,
	TGT_TO_DEV5G_0,
	TGT_TO_DEV5G_1,
	TGT_TO_DEV5G_2,
	TGT_TO_DEV5G_3,
	TGT_TO_DEV2G5_0,
	TGT_TO_DEV2G5_1,
	TGT_TO_DEV2G5_2,
	TGT_TO_DEV2G5_3,
	TGT_TO_DEV2G5_4,
	TGT_TO_DEV2G5_5,
	TGT_TO_DEV2G5_6,
	TGT_TO_DEV2G5_7,
	TGT_TO_DEV2G5_8,
	TGT_TO_DEV2G5_9,
	TGT_TO_DEV2G5_10,
	TGT_TO_DEV2G5_11,
	TGT_TO_DEV2G5_12,
	TGT_TO_DEV2G5_13,
	TGT_TO_DEV2G5_14,
	TGT_TO_DEV2G5_15,
	TGT_TO_DEV2G5_16,
	TGT_TO_DEV2G5_17,
	TGT_TO_DEV2G5_18,
	TGT_TO_DEV2G5_19,
	TGT_TO_DEV2G5_20,
	TGT_TO_DEV2G5_21,
	TGT_TO_DEV2G5_22,
	TGT_TO_DEV2G5_23,
	TGT_TO_DEV2G5_24,
	TGT_TO_DEV2G5_25,
	TGT_TO_DEV2G5_26,
	TGT_TO_DEV2G5_27,
	TGT_TO_DEVCPU_GCB,
	TGT_TO_DEVCPU_ORG0,
	TGT_TO_DEVCPU_ORG1,
	TGT_TO_DEVCPU_ORG2,
	TGT_TO_DEVCPU_PTP,
	TGT_TO_DEVCPU_QS,
	TGT_TO_DSM,
	TGT_TO_EACL,
	TGT_TO_FDMA,
	TGT_TO_HSCH,
	TGT_TO_HSIO_WRAP,
	TGT_TO_LRN,
	TGT_TO_PCS10G_BR_0,
	TGT_TO_PCS10G_BR_1,
	TGT_TO_PCS10G_BR_2,
	TGT_TO_PCS10G_BR_3,
	TGT_TO_PCS10G_BR_4,
	TGT_TO_PCS10G_BR_5,
	TGT_TO_PCS10G_BR_6,
	TGT_TO_PCS10G_BR_7,
	TGT_TO_PCS10G_BR_8,
	TGT_TO_PCS10G_BR_9,
	TGT_TO_PCS5G_BR_0,
	TGT_TO_PCS5G_BR_1,
	TGT_TO_PCS5G_BR_2,
	TGT_TO_PCS5G_BR_3,
	TGT_TO_PORT_CONF,
	TGT_TO_QFWD,
	TGT_TO_QRES,
	TGT_TO_QSYS,
	TGT_TO_REW,
	TGT_TO_SD_CMU_0,
	TGT_TO_SD_CMU_1,
	TGT_TO_SD_CMU_2,
	TGT_TO_SD_CMU_3,
	TGT_TO_SD_CMU_4,
	TGT_TO_SD_CMU_5,
	TGT_TO_SD_CMU_CFG_0,
	TGT_TO_SD_CMU_CFG_1,
	TGT_TO_SD_CMU_CFG_2,
	TGT_TO_SD_CMU_CFG_3,
	TGT_TO_SD_CMU_CFG_4,
	TGT_TO_SD_CMU_CFG_5,
	TGT_TO_SD10G_LANE_0,
	TGT_TO_SD10G_LANE_1,
	TGT_TO_SD10G_LANE_2,
	TGT_TO_SD10G_LANE_3,
	TGT_TO_SD10G_LANE_4,
	TGT_TO_SD10G_LANE_5,
	TGT_TO_SD10G_LANE_6,
	TGT_TO_SD10G_LANE_7,
	TGT_TO_SD10G_LANE_8,
	TGT_TO_SD10G_LANE_9,
	TGT_TO_SD10G_KR_0,
	TGT_TO_SD10G_KR_1,
	TGT_TO_SD10G_KR_2,
	TGT_TO_SD10G_KR_3,
	TGT_TO_SD10G_KR_4,
	TGT_TO_SD10G_KR_5,
	TGT_TO_SD10G_KR_6,
	TGT_TO_SD10G_KR_7,
	TGT_TO_SD10G_KR_8,
	TGT_TO_SD10G_KR_9,
	TGT_TO_SD_LANE_0,
	TGT_TO_SD_LANE_1,
	TGT_TO_SD_LANE_2,
	TGT_TO_SD_LANE_3,
	TGT_TO_SD_LANE_4,
	TGT_TO_SD_LANE_5,
	TGT_TO_SD_LANE_6,
	TGT_TO_SD_LANE_7,
	TGT_TO_SD_LANE_8,
	TGT_TO_SD_LANE_9,
	TGT_TO_VCAP_ES0,
	TGT_TO_VCAP_ES2,
	TGT_TO_VCAP_IP6PFX,
	TGT_TO_VCAP_SUPER,
	TGT_TO_VOP,
	TGT_TO_VOP_L3,
	TGT_TO_VOP_MPLS,
	TGT_TO_XQS,
	VTSS_TO_LAST
};

/* Group target address enums */
enum fla_groups {
	GRP_AFI_MISC,
	GRP_AFI_FRM_TBL,
	GRP_AFI_DTI_TBL,
	GRP_AFI_DTI_MISC,
	GRP_AFI_TTI_TICKS,
	GRP_AFI_TTI_MISC,
	GRP_AFI_PORT_TBL,
	GRP_ANA_AC_RAM_CTRL,
	GRP_ANA_AC_COREMEM,
	GRP_ANA_AC_PS_COMMON,
	GRP_ANA_AC_MIRROR_PROBE,
	GRP_ANA_AC_AGGR,
	GRP_ANA_AC_SRC,
	GRP_ANA_AC_SFLOW,
	GRP_ANA_AC_UPSID,
	GRP_ANA_AC_GLAG,
	GRP_ANA_AC_PGID,
	GRP_ANA_AC_CSD,
	GRP_ANA_AC_LAG_RST,
	GRP_ANA_AC_PS_STICKY,
	GRP_ANA_AC_PS_STICKY_MASK,
	GRP_ANA_AC_FRER_GEN,
	GRP_ANA_AC_FRER_GEN_STATE_ACC,
	GRP_ANA_AC_FRER_GEN_STATE,
	GRP_ANA_AC_TSN_SF,
	GRP_ANA_AC_TSN_SF_CFG,
	GRP_ANA_AC_TSN_SF_STATUS,
	GRP_ANA_AC_SG_ACCESS,
	GRP_ANA_AC_SG_CONFIG,
	GRP_ANA_AC_SG_STATUS,
	GRP_ANA_AC_SG_STATUS_STICKY,
	GRP_ANA_AC_STAT_GLOBAL_CFG_PORT,
	GRP_ANA_AC_STAT_CNT_CFG_PORT,
	GRP_ANA_AC_STAT_GLOBAL_CFG_ACL,
	GRP_ANA_AC_STAT_CNT_CFG_ACL,
	GRP_ANA_AC_STAT_GLOBAL_CFG_QUEUE,
	GRP_ANA_AC_STAT_CNT_CFG_QUEUE,
	GRP_ANA_AC_STAT_GLOBAL_CFG_ISDX,
	GRP_ANA_AC_STAT_CNT_CFG_ISDX,
	GRP_ANA_AC_STAT_GLOBAL_CFG_BDLB,
	GRP_ANA_AC_STAT_CNT_CFG_BDLB,
	GRP_ANA_AC_STAT_GLOBAL_CFG_BUM,
	GRP_ANA_AC_STAT_CNT_CFG_BUM,
	GRP_ANA_AC_STAT_GLOBAL_CFG_IRLEG,
	GRP_ANA_AC_STAT_CNT_CFG_IRLEG,
	GRP_ANA_AC_STAT_GLOBAL_CFG_ERLEG,
	GRP_ANA_AC_STAT_CNT_CFG_ERLEG,
	GRP_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT,
	GRP_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT,
	GRP_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT,
	GRP_ANA_AC_OAM_MOD_PDU_MOD_CFG,
	GRP_ANA_AC_POL_POL_ALL_CFG,
	GRP_ANA_AC_POL_POL_PORT_CFG,
	GRP_ANA_AC_POL_POL_PORT_CTRL,
	GRP_ANA_AC_POL_PORT_PT_CTRL,
	GRP_ANA_AC_POL_COMMON_BDLB,
	GRP_ANA_AC_POL_BDLB,
	GRP_ANA_AC_POL_COMMON_BUM_SLB,
	GRP_ANA_AC_POL_BUM_SLB,
	GRP_ANA_AC_SDLB_MISC,
	GRP_ANA_AC_SDLB_LBGRP_TBL,
	GRP_ANA_ACL_COMMON,
	GRP_ANA_ACL_PORT,
	GRP_ANA_ACL_KEY_SEL,
	GRP_ANA_ACL_CNT_B,
	GRP_ANA_ACL_PTP_MASTER_CFG,
	GRP_ANA_ACL_STICKY,
	GRP_ANA_CL_PORT,
	GRP_ANA_CL_COMMON,
	GRP_ANA_CL_MPLS_PROFILE,
	GRP_ANA_CL_MIP_TBL,
	GRP_ANA_CL_L2CP_TBL,
	GRP_ANA_CL_MAP_TBL,
	GRP_ANA_CL_IPT,
	GRP_ANA_CL_PPT,
	GRP_ANA_CL_VMID,
	GRP_ANA_CL_CSC,
	GRP_ANA_CL_STICKY,
	GRP_ANA_CL_STICKY_MASK,
	GRP_ANA_L2_COMMON,
	GRP_ANA_L2_PORT_LIMIT,
	GRP_ANA_L2_STICKY,
	GRP_ANA_L2_STICKY_MASK,
	GRP_ANA_L3_COMMON,
	GRP_ANA_L3_MSTP,
	GRP_ANA_L3_VMID,
	GRP_ANA_L3_ARP_PTR_REMAP,
	GRP_ANA_L3_ARP,
	GRP_ANA_L3_L3MC,
	GRP_ANA_L3_LPM_REMAP_STICKY,
	GRP_ANA_L3_VLAN_ARP_L3MC_STICKY,
	GRP_ANA_L3_L3_STICKY_MASK,
	GRP_ASM_CFG,
	GRP_ASM_DBG,
	GRP_ASM_PORT_STATUS,
	GRP_ASM_PFC,
	GRP_ASM_PFC_TIMER_CFG,
	GRP_ASM_LBK_WM_CFG,
	GRP_ASM_LBK_MISC_CFG,
	GRP_ASM_LBK_STAT,
	GRP_ASM_RAM_CTRL,
	GRP_ASM_COREMEM,
	GRP_CHIP_TOP_OTP_MEM,
	GRP_CPU_VCORE_ACC,
	GRP_CPU_MSIX_ACC,
	GRP_CPU_EXT_IF_ACC_STAT,
	GRP_CPU_INTR,
	GRP_CPU_DDRCTRL,
	GRP_DEV1G_MM_CONFIG,
	GRP_DEV1G_MM_STATISTICS,
	GRP_DEV1G_DEV1G_INTR_CFG_STATUS,
	GRP_DEV1G_DEV2G5U_INTR_CFG_STATUS,
	GRP_DEVCPU_GCB_SI_REGS,
	GRP_DEVCPU_GCB_SW_REGS,
	GRP_DEVCPU_GCB_VCORE_ACCESS,
	GRP_DEVCPU_GCB_GPIO,
	GRP_DEVCPU_GCB_MIIM,
	GRP_DEVCPU_GCB_MIIM_READ_SCAN,
	GRP_DEVCPU_GCB_ROSC,
	GRP_DEVCPU_GCB_SIO_CTRL,
	GRP_DEVCPU_GCB_FAN_CTRL,
	GRP_DEVCPU_GCB_MEMITGR,
	GRP_DEVCPU_GCB_ETHERACCESS,
	GRP_DEVCPU_PTP_PTP_CFG,
	GRP_DEVCPU_PTP_PTP_TOD_DOMAINS,
	GRP_DEVCPU_PTP_PHASE_DETECTOR_CTRL,
	GRP_EACL_COMMON,
	GRP_EACL_INTERFACE_MAP,
	GRP_EACL_ES2_KEY_SELECT_PROFILE,
	GRP_EACL_CNT_TBL,
	GRP_EACL_POL_CFG,
	GRP_EACL_ES2_STICKY,
	GRP_EACL_DBG_STICKY,
	GRP_EACL_FRER_CFG,
	GRP_EACL_FRER_CFG_COMPOUND,
	GRP_EACL_FRER_CFG_MEMBER,
	GRP_EACL_FRER_STA_COMPOUND,
	GRP_EACL_FRER_STA_MEMBER,
	GRP_EACL_FRER_CNT_COMPOUND,
	GRP_EACL_FRER_CNT_MEMBER,
	GRP_EACL_STAT_GLOBAL_CFG_EACL,
	GRP_EACL_STAT_CNT_CFG_EACL,
	GRP_EACL_RAM_CTRL,
	GRP_EACL_COREMEM,
	GRP_HSCH_HSCH_L0_CFG,
	GRP_HSCH_HSCH_L1_CFG,
	GRP_HSCH_HSCH_STATUS,
	GRP_HSCH_QSHP_CFG,
	GRP_HSCH_QSHP_ALLOC_CFG,
	GRP_HSCH_QSHP_STATUS,
	GRP_HSCH_HSCH_INP_STATE,
	GRP_HSCH_HSCH_DWRR,
	GRP_HSCH_HSCH_MISC,
	GRP_HSCH_HSCH_LEAK_LISTS,
	GRP_HSCH_SYSTEM,
	GRP_HSCH_MMGT,
	GRP_HSCH_TAS_CONFIG,
	GRP_HSCH_TAS_PROFILE_CFG,
	GRP_HSCH_TAS_LIST_CFG,
	GRP_HSCH_TAS_GCL_CFG,
	GRP_HSCH_HSCH_TAS_STATE,
	GRP_HSIOWRAP_SYNC_ETH_CFG,
	GRP_HSIOWRAP_GPIO_CFG,
	GRP_PORT_CONF_USXGMII_CFG,
	GRP_PORT_CONF_USXGMII_STAT,
	GRP_QSYS_MMGT_PORT,
	GRP_QSYS_SOFDATA_POOL,
	GRP_QSYS_CALCFG,
	GRP_QSYS_RAM_CTRL,
	GRP_QSYS_COREMEM,
	GRP_REW_COMMON,
	GRP_REW_MAP_RES_A,
	GRP_REW_MAP_RES_B,
	GRP_REW_PORT,
	GRP_REW_MIP_TBL,
	GRP_REW_MAC_TBL,
	GRP_REW_ISDX_TBL,
	GRP_REW_ENCAP_IP4,
	GRP_REW_VMID,
	GRP_REW_PTP_SEQ_NO,
	GRP_REW_VOE_SRV_LM_CNT,
	GRP_REW_VOE_PORT_LM_CNT,
	GRP_REW_OAM_PDU_MOD_CONT,
	GRP_REW_PDU_MOD_CFG,
	GRP_REW_RAM_CTRL,
	GRP_REW_COREMEM,
	GRP_VOP_COMMON,
	GRP_VOP_VOE_CONF_REG,
	GRP_VOP_VOE_STAT,
	GRP_VOP_VOE_STAT_REG,
	GRP_VOP_VOE_CCM_LM,
	GRP_VOP_VOE_CONTEXT_ANA,
	GRP_VOP_VOE_CONTEXT_REW,
	GRP_VOP_VOE_CRC_ERR,
	GRP_VOP_ANA_COSID_MAP_CONF,
	GRP_VOP_REW_COSID_MAP_CONF,
	GRP_VOP_PORT_COSID_MAP_CONF,
	GRP_VOP_SAM_COSID_SEQ_CNT,
	GRP_VOP_RAM_CTRL,
	GRP_VOP_COREMEM,
	GRP_VOP_L3_VOE_STAT_L3,
	GRP_VOP_MPLS_VOE_CONF_MPLS,
	GRP_XQS_SYSTEM,
	GRP_XQS_QMAP_SE_TBL,
	GRP_XQS_QMAP_QOS_TBL,
	GRP_XQS_QLIMIT_QUEUE,
	GRP_XQS_QLIMIT_SE,
	GRP_XQS_QLIMIT_CFG,
	GRP_XQS_QLIMIT_SHR,
	GRP_XQS_QLIMIT_MON,
	GRP_PTP_PTP_CFG,	// LAGUNA only
	GRP_PTP_PTP_TOD_DOMAINS,	// LAGUNA only
	GRP_PTP_PHASE_DETECTOR_CTRL,	// LAGUNA only
	GRP_OFFSET_LAST
};

/* Group size address enums */
enum fla_groups_sz {
	GRP_ANA_AC_SRC_SZ,
	GRP_ANA_AC_STAT_GLOBAL_CFG_ISDX_SZ,
	GRP_ANA_L2_COMMON_SZ,
	GRP_ASM_CFG_SZ,
	GRP_ASM_PORT_STATUS_SZ,
	GRP_CPU_CPU_REGS_SZ,
	GRP_CPU_INTR_SZ,
	GRP_CPU_DDRCTRL_SZ,
	GRP_DEV10G_PHASE_DETECTOR_CTRL_SZ,
	GRP_DEV1G_PHASE_DETECTOR_CTRL_SZ,
	GRP_DEVCPU_GCB_CHIP_REGS_SZ,
	GRP_DEVCPU_GCB_VCORE_ACCESS_SZ,
	GRP_DEVCPU_GCB_GPIO_SZ,
	GRP_DEVCPU_GCB_MIIM_READ_SCAN_SZ,
	GRP_DEVCPU_GCB_ROSC_SZ,
	GRP_DEVCPU_ORG_ORG_SZ,
	GRP_FDMA_FDMA_SZ,
	GRP_HSCH_TAS_CONFIG_SZ,
	GRP_HSCH_TAS_PROFILE_CFG_SZ,
	GRP_HSCH_TAS_GCL_CFG_SZ,
	GRP_HSIOWRAP_GPIO_CFG_SZ,
	GRP_QSYS_PAUSE_CFG_SZ,
	GRP_VOP_COMMON_SZ,
	GRP_XQS_QMAP_VPORT_TBL_SZ,
	GRP_OFFSET_SZ_LAST
};

/* Unstable register address enums */
enum fla_unstable_regs {
	REG_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_CFG,
	REG_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_EVENT_MASK,
	REG_ANA_AC_STAT_CNT_CFG_ISDX_STAT_MSB_CNT,
	REG_CPU_RESET,
	REG_CPU_RESET_PROT_STAT,
	REG_CPU_GENERAL_CTRL,
	REG_CPU_GENERAL_STAT,
	REG_CPU_ENDIANNESS,
	REG_CPU_PROC_CTRL,
	REG_CPU_CPU0_RVBAR_LSB,
	REG_CPU_CPU0_RVBAR_MSB,
	REG_CPU_PROC_STAT,
	REG_CPU_INTR_TRIGGER,
	REG_CPU_INTR_TRIGGER1,
	REG_CPU_INTR_FORCE,
	REG_CPU_INTR_FORCE1,
	REG_CPU_INTR_STICKY,
	REG_CPU_INTR_STICKY1,
	REG_CPU_INTR_BYPASS,
	REG_CPU_INTR_BYPASS1,
	REG_CPU_INTR_ENA,
	REG_CPU_INTR_ENA1,
	REG_CPU_INTR_ENA_CLR,
	REG_CPU_INTR_ENA_CLR1,
	REG_CPU_INTR_ENA_SET,
	REG_CPU_INTR_ENA_SET1,
	REG_CPU_INTR_IDENT,
	REG_CPU_INTR_IDENT1,
	REG_CPU_DST_INTR_MAP,
	REG_CPU_DST_INTR_MAP1,
	REG_CPU_DST_INTR_IDENT,
	REG_CPU_DST_INTR_IDENT1,
	REG_CPU_EXT_SRC_INTR_POL,
	REG_CPU_EXT_DST_INTR_POL,
	REG_CPU_EXT_DST_INTR_DRV,
	REG_CPU_DEV_INTR_POL,
	REG_CPU_DEV_INTR_RAW,
	REG_CPU_DEV_INTR_TRIGGER,
	REG_CPU_DEV_INTR_STICKY,
	REG_CPU_DEV_INTR_BYPASS,
	REG_CPU_DEV_INTR_ENA,
	REG_CPU_DEV_INTR_IDENT,
	REG_DEVCPU_GCB_GPR,
	REG_DEVCPU_GCB_SOFT_RST,
	REG_DEVCPU_GCB_HW_SGPIO_TO_SD_MAP_CFG,
	REG_DEVCPU_GCB_HW_SGPIO_TO_SERDES_SD_MAP_CFG,
	REG_DEVCPU_GCB_VA_DATA,
	REG_DEVCPU_GCB_VA_DATA_INCR,
	REG_DEVCPU_GCB_VA_DATA_INERT,
	REG_DEVCPU_GCB_GPIO_OUT_CLR,
	REG_DEVCPU_GCB_GPIO_OUT_CLR1,
	REG_DEVCPU_GCB_GPIO_OUT,
	REG_DEVCPU_GCB_GPIO_OUT1,
	REG_DEVCPU_GCB_GPIO_IN,
	REG_DEVCPU_GCB_GPIO_IN1,
	REG_DEVCPU_GCB_GPIO_OE,
	REG_DEVCPU_GCB_GPIO_OE1,
	REG_DEVCPU_GCB_GPIO_INTR,
	REG_DEVCPU_GCB_GPIO_INTR1,
	REG_DEVCPU_GCB_GPIO_INTR_ENA,
	REG_DEVCPU_GCB_GPIO_INTR_ENA1,
	REG_DEVCPU_GCB_GPIO_INTR_IDENT,
	REG_DEVCPU_GCB_GPIO_INTR_IDENT1,
	REG_DEVCPU_GCB_GPIO_ALT,
	REG_DEVCPU_GCB_GPIO_ALT1,
	REG_DEVCPU_GCB_ROSC_MEASURE_CFG,
	REG_DEVCPU_GCB_ROSC_FREQ_CNT,
	REG_VOP_HMO_PERIOD_CFG,
	REG_VOP_HMO_FORCE_SLOT_CFG,
	REG_VOP_HMO_TIMER_CFG,
	REG_VOP_LOC_SCAN_STICKY,
	REG_VOP_MASTER_INTR_CTRL,
	REG_VOP_VOE32_INTR,
	REG_VOP_INTR,
	REG_VOP_COMMON_MEP_MC_MAC_LSB,
	REG_VOP_COMMON_MEP_MC_MAC_MSB,
	REG_ENUM_LAST
};

/* Unstable register fields enums */
enum fla_unstable_flds {
	FLD_P_ANA_CL_MISC_CFG_UPDATE_DSCP_WITH_MEL_ENA,
	FLD_P_ANA_L2_MISC_CFG_CT_DIS,
	FLD_P_ANA_L2_MISC_CFG_RSDX_DIS,
	FLD_P_CPU_RESET_VCORE_RST,
	FLD_P_CPU_RESET_CPU_CORE_0_WARM_RST,
	FLD_P_CPU_RESET_PROC_DBG_RST,
	FLD_P_CPU_RESET_CPU_L2_RST,
	FLD_P_CPU_RESET_MEM_RST,
	FLD_P_CPU_RESET_WDT_FORCE_RST,
	FLD_P_CPU_RESET_CPU_CORE_0_COLD_RST,
	FLD_P_CPU_RESET_PROT_STAT_SYS_RST_PROT_VCORE,
	FLD_P_CPU_RESET_PROT_STAT_VCORE_RST_PROT_AMBA,
	FLD_P_CPU_RESET_PROT_STAT_VCORE_RST_PROT_WDT,
	FLD_P_CPU_RESET_PROT_STAT_VCORE_WDT_RST_PROT_WDT,
	FLD_P_CPU_RESET_PROT_STAT_VCORE_WDT_RST_STAT,
	FLD_P_CPU_GENERAL_CTRL_IF_MIIM_SLV_ENA,
	FLD_P_CPU_GENERAL_CTRL_IF_SI_OWNER,
	FLD_W_CPU_GENERAL_CTRL_IF_SI_OWNER,
	FLD_P_CPU_GENERAL_CTRL_VCORE_CPU_DIS,
	FLD_P_CPU_GENERAL_STAT_REG_IF_ERR,
	FLD_P_CPU_PROC_CTRL_AARCH64_MODE_ENA,
	FLD_P_CPU_PROC_CTRL_L2_RST_INVALIDATE_DIS,
	FLD_P_CPU_PROC_CTRL_L1_RST_INVALIDATE_DIS,
	FLD_P_CPU_PROC_CTRL_BE_EXCEP_MODE,
	FLD_P_CPU_PROC_CTRL_VINITHI,
	FLD_P_CPU_PROC_CTRL_CFGTE,
	FLD_P_CPU_PROC_CTRL_CP15S_DISABLE,
	FLD_P_CPU_PROC_CTRL_PROC_CRYPTO_DISABLE,
	FLD_P_CPU_PROC_CTRL_L2_FLUSH_REQ,
	FLD_P_CPU_PROC_STAT_DAP_JTAG_SW_MODE,
	FLD_P_CPU_DDRCTRL_CLK_DDRPHY_APB_CLK_ENA,
	FLD_P_CPU_DDRCTRL_CLK_DDRPHY_CTL_CLK_ENA,
	FLD_P_CPU_DDRCTRL_CLK_DDR_APB_CLK_ENA,
	FLD_P_CPU_DDRCTRL_RST_DDRPHY_APB_RST,
	FLD_P_CPU_DDRCTRL_RST_DDRPHY_CTL_RST,
	FLD_P_CPU_DDRCTRL_RST_DDR_APB_RST,
	FLD_P_CPU_DDRC_INTR_RAW_STAT_DFI_ALERT_ERR_INTR_RAW_STAT,
	FLD_P_CPU_DDRC_INTR_MASK_DFI_ALERT_ERR_INTR_MASK,
	FLD_P_CPU_DDRC_INTR_MASKED_STAT_DFI_ALERT_ERR_INTR_STAT,
	FLD_P_DEV10G_PHAD_CTRL_PHAD_ENA,
	FLD_P_DEV10G_PHAD_CTRL_PHAD_FAILED,
	FLD_P_DEV1G_PHAD_CTRL_PHAD_ENA,
	FLD_P_DEV1G_PHAD_CTRL_PHAD_FAILED,
	FLD_P_DEVCPU_GCB_PWM_FREQ_CLK_CYCLES_10US,
	FLD_W_DEVCPU_GCB_PWM_FREQ_CLK_CYCLES_10US,
	FLD_P_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_ACTION,
	FLD_P_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SYNC,
	FLD_P_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_INV_POL,
	FLD_P_DEVCPU_PTP_PHAD_CTRL_PHAD_ENA,
	FLD_P_DEVCPU_PTP_PHAD_CTRL_PHAD_FAILED,
	FLD_P_FDMA_FDMA_CH_STATUS_CH_FILL_LVL,
	FLD_W_FDMA_FDMA_CH_STATUS_CH_FILL_LVL,
	FLD_P_FDMA_FDMA_CH_CFG_CH_XTR_STATUS_MODE,
	FLD_P_FDMA_FDMA_CH_CFG_CH_INTR_DB_EOF_ONLY,
	FLD_P_FDMA_FDMA_CH_CFG_CH_INJ_PORT,
	FLD_P_VOP_LOC_CTRL_LOC_SPACE_BETWEEN_ENTRY_SCAN,
	FLD_W_DEVCPU_PTP_PTP_PIN_CFG_PTP_PIN_SELECT,
	FLD_ENUM_LAST
};

/* register count enums */
enum fla_register_cnt {
	REG_ANA_AC_PS_COMMON_OWN_UPSID_CNT,
	REG_ANA_AC_PS_COMMON_VSTAX_CTRL_CNT,
	REG_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_CFG_CNT,
	REG_ANA_AC_STAT_GLOBAL_CFG_ISDX_STAT_GLOBAL_EVENT_MASK_CNT,
	REG_ANA_AC_OAM_MOD_DM_PTP_DOMAIN_CFG_CNT,
	REG_ANA_AC_POL_POL_ALL_CFG_POL_ACL_RATE_CFG_CNT,
	REG_ANA_AC_POL_POL_ALL_CFG_POL_ACL_THRES_CFG_CNT,
	REG_ANA_AC_POL_POL_ALL_CFG_POL_ACL_CTRL_CNT,
	REG_ANA_AC_POL_POL_ALL_CFG_POL_PORT_FC_CFG_CNT,
	REG_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_0_CNT,
	REG_ANA_AC_POL_POL_PORT_CFG_POL_PORT_THRES_CFG_1_CNT,
	REG_ANA_AC_POL_POL_PORT_CFG_POL_PORT_RATE_CFG_CNT,
	REG_ANA_ACL_VCAP_S2_CFG_CNT,
	REG_ANA_ACL_OWN_UPSID_CNT,
	REG_ANA_CL_OWN_UPSID_CNT,
	REG_ANA_CL_PP_CFG_CNT,
	REG_ANA_L2_PORT_DLB_CFG_CNT,
	REG_ANA_L2_PORT_ISDX_LIMIT_CFG_CNT,
	REG_ANA_L2_OWN_UPSID_CNT,
	REG_ASM_MAC_ADDR_HIGH_CFG_CNT,
	REG_ASM_MAC_ADDR_LOW_CFG_CNT,
	REG_ASM_PORT_CFG_CNT,
	REG_ASM_PAUSE_CFG_CNT,
	REG_ASM_ERR_STICKY_CNT,
	REG_ASM_CELLBUF_STAT_CNT,
	REG_ASM_PORT_STICKY_CNT,
	REG_ASM_LBK_AGING_DIS_CNT,
	REG_ASM_LBK_OVFLW_STICKY_CNT,
	REG_ASM_LBK_AGING_STICKY_CNT,
	REG_CPU_DST_INTR_MAP_CNT,
	REG_CPU_DST_INTR_MAP1_CNT,
	REG_CPU_DST_INTR_IDENT_CNT,
	REG_CPU_DST_INTR_IDENT1_CNT,
	REG_DEVCPU_GCB_HW_SGPIO_TO_SD_MAP_CFG_CNT,
	REG_DEVCPU_GCB_HW_SGPIO_TO_SERDES_SD_MAP_CFG_CNT,
	REG_DEVCPU_GCB_GPIO_ALT_CNT,
	REG_DEVCPU_GCB_GPIO_ALT1_CNT,
	REG_DEVCPU_GCB_MII_SCAN_RSLTS_STICKY_CNT,
	REG_DEVCPU_GCB_ROSC_CFG_CNT,
	REG_DSM_BUF_CFG_CNT,
	REG_DSM_RATE_CTRL_CNT,
	REG_DSM_IPG_SHRINK_CFG_CNT,
	REG_DSM_CLR_BUF_CNT,
	REG_DSM_SCH_STOP_WM_CFG_CNT,
	REG_DSM_TX_START_WM_CFG_CNT,
	REG_DSM_DEV_TX_STOP_WM_CFG_CNT,
	REG_DSM_RX_PAUSE_CFG_CNT,
	REG_DSM_ETH_FC_CFG_CNT,
	REG_DSM_ETH_PFC_CFG_CNT,
	REG_DSM_MAC_CFG_CNT,
	REG_DSM_MAC_ADDR_BASE_HIGH_CFG_CNT,
	REG_DSM_MAC_ADDR_BASE_LOW_CFG_CNT,
	REG_DSM_TAXI_CAL_CFG_CNT,
	REG_DSM_PREEMPT_CFG_CNT,
	REG_DSM_AGED_FRMS_CNT,
	REG_DSM_BUF_OFLW_STICKY_CNT,
	REG_DSM_BUF_UFLW_STICKY_CNT,
	REG_DSM_BUF_MAX_FILL_CNT,
	REG_DSM_TX_RATE_LIMIT_MODE_CNT,
	REG_DSM_TX_IPG_STRETCH_RATIO_CFG_CNT,
	REG_DSM_TX_FRAME_RATE_START_CFG_CNT,
	REG_DSM_TX_RATE_LIMIT_STICKY_CNT,
	REG_EACL_POL_EACL_RATE_CFG_CNT,
	REG_EACL_POL_EACL_THRES_CFG_CNT,
	REG_EACL_POL_EACL_CTRL_CNT,
	REG_HSCH_HSCH_MISC_PORT_CFG_CNT,
	REG_HSCH_PFC_CFG_CNT,
	REG_HSCH_HSCH_LARGE_ENA_CNT,
	REG_HSCH_PORT_MODE_CNT,
	REG_HSIOWRAP_GPIO_CFG_CNT,
	REG_QFWD_SWITCH_PORT_MODE_CNT,
	REG_QRES_WRED_GROUP_CNT,
	REG_QSYS_EEE_CFG_CNT,
	REG_QSYS_IQUEUE_CFG_CNT,
	REG_QSYS_PAUSE_CFG_CNT,
	REG_QSYS_ATOP_CNT,
	REG_QSYS_FWD_PRESSURE_CNT,
	REG_QSYS_PFC_CFG_CNT,
	REG_QSYS_SOFDATA_STAT_CNT,
	REG_QSYS_SOFDATA_CFG_CNT,
	REG_QSYS_CAL_AUTO_CNT,
	REG_REW_OWN_UPSID_CNT,
	REG_REW_IFH_CTRL_CNT,
	REG_REW_PORT_CTRL_CNT,
	REG_REW_RTAG_ETAG_CTRL_CNT,
	REG_VOP_LOC_PERIOD_CFG_CNT,
	REG_VOP_VOE32_INTR_CNT,
	REG_VOP_INTR_CNT,
	REG_XQS_FWD_DROP_EVENTS_CNT,
	REG_XQS_FWD_CT_CFG_CNT,
	REG_XQS_QMAP_PORT_MODE_CNT,
	REG_XQS_QMAP_VPORT_TBL_CNT,
	REG_XQS_QLIMIT_SE_USE_CNT,
	REG_XQS_QLIMIT_PORT_CFG_CNT,
	REG_CNT_ENUM_LAST
};

/* Group count enums */
enum fla_groups_cnt {
	GRP_AFI_FRM_TBL_CNT,
	GRP_AFI_DTI_TBL_CNT,
	GRP_AFI_DTI_MISC_CNT,
	GRP_AFI_TTI_TBL_CNT,
	GRP_AFI_PORT_TBL_CNT,
	GRP_ANA_AC_SRC_CNT,
	GRP_ANA_AC_SFLOW_CNT,
	GRP_ANA_AC_PGID_CNT,
	GRP_ANA_AC_LAG_RST_CNT,
	GRP_ANA_AC_FRER_GEN_CNT,
	GRP_ANA_AC_TSN_SF_CFG_CNT,
	GRP_ANA_AC_STAT_CNT_CFG_PORT_CNT,
	GRP_ANA_AC_STAT_CNT_CFG_ACL_CNT,
	GRP_ANA_AC_STAT_CNT_CFG_QUEUE_CNT,
	GRP_ANA_AC_STAT_CNT_CFG_ISDX_CNT,
	GRP_ANA_AC_STAT_CNT_CFG_BDLB_CNT,
	GRP_ANA_AC_STAT_CNT_CFG_BUM_CNT,
	GRP_ANA_AC_STAT_CNT_CFG_IRLEG_CNT,
	GRP_ANA_AC_STAT_CNT_CFG_ERLEG_CNT,
	GRP_ANA_AC_OAM_MOD_VOE_SRV_LM_CNT_CNT,
	GRP_ANA_AC_OAM_MOD_VOE_PORT_LM_CNT_CNT,
	GRP_ANA_AC_OAM_MOD_OAM_PDU_MOD_CONT_CNT,
	GRP_ANA_AC_POL_POL_PORT_CTRL_CNT,
	GRP_ANA_AC_POL_PORT_PT_CTRL_CNT,
	GRP_ANA_AC_POL_BDLB_CNT,
	GRP_ANA_AC_POL_BUM_SLB_CNT,
	GRP_ANA_AC_SDLB_LBGRP_TBL_CNT,
	GRP_ANA_AC_SDLB_LBSET_TBL_CNT,
	GRP_ANA_ACL_PORT_CNT,
	GRP_ANA_ACL_KEY_SEL_CNT,
	GRP_ANA_ACL_CNT_A_CNT,
	GRP_ANA_ACL_CNT_B_CNT,
	GRP_ANA_CL_PORT_CNT,
	GRP_ANA_CL_MIP_TBL_CNT,
	GRP_ANA_CL_L2CP_TBL_CNT,
	GRP_ANA_CL_MAP_TBL_CNT,
	GRP_ANA_CL_IPT_CNT,
	GRP_ANA_CL_VMID_CNT,
	GRP_ANA_L2_LRN_LIMIT_CNT,
	GRP_ANA_L2_ISDX_LIMIT_CNT,
	GRP_ANA_L2_PORT_LIMIT_CNT,
	GRP_ANA_L2_ISDX_CNT,
	GRP_ANA_L3_VLAN_CNT,
	GRP_ANA_L3_VMID_CNT,
	GRP_ANA_L3_ARP_CNT,
	GRP_ANA_L3_L3MC_CNT,
	GRP_ASM_DEV_STATISTICS_CNT,
	GRP_ASM_PFC_CNT,
	GRP_DEVCPU_GCB_MIIM_CNT,
	GRP_DEVCPU_GCB_SIO_CTRL_CNT,
	GRP_EACL_INTERFACE_MAP_CNT,
	GRP_EACL_ES2_KEY_SELECT_PROFILE_CNT,
	GRP_EACL_CNT_TBL_CNT,
	GRP_EACL_FRER_MAP_CNT,
	GRP_EACL_FRER_CFG_COMPOUND_CNT,
	GRP_EACL_FRER_CFG_MEMBER_CNT,
	GRP_EACL_FRER_CNT_COMPOUND_CNT,
	GRP_EACL_FRER_CNT_MEMBER_CNT,
	GRP_EACL_STAT_CNT_CFG_EACL_CNT,
	GRP_HSCH_HSCH_L0_CFG_CNT,
	GRP_HSCH_HSCH_L1_CFG_CNT,
	GRP_HSCH_HSCH_CFG_CNT,
	GRP_HSCH_HSCH_STATUS_CNT,
	GRP_HSCH_QSHP_CFG_CNT,
	GRP_HSCH_QSHP_ALLOC_CFG_CNT,
	GRP_HSCH_QSHP_STATUS_CNT,
	GRP_HSCH_HSCH_INP_STATE_CNT,
	GRP_HSCH_HSCH_DWRR_CNT,
	GRP_HSCH_TAS_PROFILE_CFG_CNT,
	GRP_PORT_CONF_USXGMII_CFG_CNT,
	GRP_PORT_CONF_USXGMII_STAT_CNT,
	GRP_REW_MAP_RES_A_CNT,
	GRP_REW_MAP_RES_B_CNT,
	GRP_REW_PORT_CNT,
	GRP_REW_MIP_TBL_CNT,
	GRP_REW_ISDX_TBL_CNT,
	GRP_REW_ENCAP_CNT,
	GRP_REW_ENCAP_IP4_CNT,
	GRP_REW_VMID_CNT,
	GRP_REW_VOE_SRV_LM_CNT_CNT,
	GRP_REW_VOE_PORT_LM_CNT_CNT,
	GRP_REW_OAM_PDU_MOD_CONT_CNT,
	GRP_VOP_VOE_CONF_REG_CNT,
	GRP_VOP_VOE_CONF_CNT,
	GRP_VOP_VOE_STAT_CNT,
	GRP_VOP_VOE_STAT_REG_CNT,
	GRP_VOP_VOE_CCM_LM_CNT,
	GRP_VOP_VOE_CONTEXT_ANA_CNT,
	GRP_VOP_VOE_CONTEXT_REW_CNT,
	GRP_VOP_VOE_CRC_ERR_CNT,
	GRP_VOP_ANA_COSID_MAP_CONF_CNT,
	GRP_VOP_REW_COSID_MAP_CONF_CNT,
	GRP_VOP_PORT_COSID_MAP_CONF_CNT,
	GRP_VOP_L3_VOE_CONF_L3_CNT,
	GRP_VOP_L3_VOE_STAT_L3_CNT,
	GRP_VOP_MPLS_VOE_CONF_MPLS_CNT,
	GRP_VOP_MPLS_VOE_STAT_MPLS_CNT,
	GRP_CNT_ENUM_LAST
};

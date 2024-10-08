// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_LAGUNA_REGS_VOP_H_
#define _VTSS_LAGUNA_REGS_VOP_H_

#include "vtss_laguna_regs_common.h"

/***********************************************************************
 *
 * Target: \a VOP
 *
 * The Versatile OAM MEP Processor (VOP) implements the HW support for
 * implementing OAM MEPs.
 *
 * The HW support for implementing an OAM MEP is implemented in a sub
 * block, referred to as:
 * Versatile OAM Endpoint (VOE).
 *
 * The VOEs can be configured for either Y.1731, MPLS-TP, or L3 OAM PDU
 * processing.
 *
 * The VOP includes the following:
 *
 *  * 32 Service / Path VOEs
 *  * 30 Port VOEs
 *
 * The VOEs can be configured for either Y.1731, MPLS-TP, or L3 OAM PDU
 * processing using the following register:
 *  * VOP:VOE_CONF_REG:VOE_MISC_CONFIG.VOE_ENA
 *
 * To configure VOEs configured for Y.1731, use CSR target VOP.
 * To configure VOEs configured for MPLS-TP, use CSR target VOP_MPLS.
 * To configure VOEs configured for L3 OAM, use CSR target VOP_L3.
 *
 * For VOEs not configured for Y.1731, the following register groups are
 * invalid:
 *
 *  * VOP:VOE_CONF
 *  * VOP:VOE_STAT
 *
 * With the exception of VOP:VOE_CONF:VOE_COMMON_CFG which is always valid.
 *
 ***********************************************************************/

/**
 * Register Group: \a VOP:COMMON
 *
 * Configuration Registers for VOP.
 */


/**
 * \brief Miscellaneous Versatile OAM Processor Controls
 *
 * \details
 * This register contains variable settings which are global to all VOEs.
 *
 * Register: \a VOP:COMMON:VOP_CTRL
 */
#define VTSS_VOP_VOP_CTRL                    VTSS_IOREG(VTSS_TO_VOP,0x357e)

/**
 * \brief
 * The CCM PDU does not have a dedicated register for the RxFCf
 * counter.However there is a reserved field which can be used to hold this
 * value.Asserting this field enables updating reserved field for Rx CCM LM
 * PDU with RxFCf.This is the only way to relay the RxFCf counter to the
 * CPU.
 *
 * \details
 * 0: Do not update CCM-LM frames with RxFC_f information
 * 1: Update the CCM-LM Reserved field with RxFC_f information
 *
 * Field: ::VTSS_VOP_VOP_CTRL . CCM_LM_UPD_RSV_ENA
 */
#define  VTSS_F_VOP_VOP_CTRL_CCM_LM_UPD_RSV_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_VOP_CTRL_CCM_LM_UPD_RSV_ENA  VTSS_BIT(11)
#define  VTSS_X_VOP_VOP_CTRL_CCM_LM_UPD_RSV_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * The LMR PDU does not have any fields reserved to hold the RxFCb counter
 * upon reception of an LMR/SLR frame.For LMR:----------------The VOE
 * supports adding the RxFCb counter following the other three counters in
 * the LMR/SLR PDU. This requires extending the first TLV from 12 --> 16
 * bytes.Asserting this fields enables updating TLV OFFSET to 16 and
 * setting inserting RxFCb after TxFCb.Further a new End TLV = 0 is written
 * right after the LMR.RxFCb (at offset = 16)For SLR:--------------The VOE
 * supports adding the RxFCb counter following the other three counters in
 * the SLR PDU. This requires extending the first TLV from 16 --> 20
 * bytes.Asserting this fields enables updating TLV OFFSET to 16 and
 * setting inserting RxFCb after TxFCb.Further a new End TLV = 0 is written
 * right after the SLR.RxFCb (at offset = 16)This solution is a proprietary
 * solution, which allows forwarding the RxFCb value to an internal or
 * external CPU.NOTE this will result in a non standards compliant
 * frame.However, this is the only way to convey the RxFCb frame count to a
 * CPU.
 *
 * \details
 * 0: No modifications to LMR upon reception
 * 1: Update LMR frames as described above.
 *
 * Field: ::VTSS_VOP_VOP_CTRL . LMR_UPD_RXFCL_ENA
 */
#define  VTSS_F_VOP_VOP_CTRL_LMR_UPD_RXFCL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_VOP_CTRL_LMR_UPD_RXFCL_ENA  VTSS_BIT(10)
#define  VTSS_X_VOP_VOP_CTRL_LMR_UPD_RXFCL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Enables or disables automated Loss Of Continuity (LOC) Controller to be
 * used for LOC detection by both Ethernet and MPLS-TP VOEs.When the LOC
 * SCAN is disabled, the LOC timers will not expire so there is no increase
 * of the LOC counters in the VOEs.When the LOC SCAN is enabled, the LOC
 * timers will expire and increment the VOE LOC counters. LOC timers are
 * configured in register:VOP::LOC_CTRL.*When the LOC scan controller is
 * disabled, the LOC scan controller is automatically reset.I.e. all
 * internal counters are set to default values.NOTE: This does not affect
 * the LOC miss counters in the VOE.
 *
 * \details
 * Field: ::VTSS_VOP_VOP_CTRL . LOC_SCAN_ENA
 */
#define  VTSS_F_VOP_VOP_CTRL_LOC_SCAN_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_VOP_CTRL_LOC_SCAN_ENA     VTSS_BIT(1)
#define  VTSS_X_VOP_VOP_CTRL_LOC_SCAN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enables or disables the Versatile OAM Processor (VOP).When the VOP is
 * disabled, both VOP and the single VOEs can be configured, but no frame
 * processing is done.Further each individual VOE must be enabled to enable
 * its functionality.
 *
 * \details
 * Field: ::VTSS_VOP_VOP_CTRL . VOP_ENA
 */
#define  VTSS_F_VOP_VOP_CTRL_VOP_ENA(x)       VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_VOP_CTRL_VOP_ENA          VTSS_BIT(0)
#define  VTSS_X_VOP_VOP_CTRL_VOP_ENA(x)       VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * The VOE can optionally detect changes in the source port for CCM
 * PDUs.The port on which the last valid PDU was received is saved: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_RX_SRC_PORTThe VOE counts the number of
 * valid CCM PDUs received on the same port as the previous in the
 * following register: * VOP:VOE_STAT:CCM_STAT.CCM_RX_SRC_PORT_CNTIf this
 * count reaches the value configured in this field, the following sticky
 * bit is asserted: *
 * VOP:VOE_STAT:INTR_STICKY.CCM_RX_SRC_PORT_DETECT_STICKYThe sticky bit can
 * optionally generate an interrupt.Note: that the VOE counts the number of
 * frames matching the previous, hence if this bitfield is programmed to
 * 'X', it will require 'X' + 1 consecutive frames on the same port to
 * assert the sticky bit.
 *
 * \details
 * 0: illegal value (Will never generate a sticky bit)
 * 1-7: Assert sticky bit when 1-7 CCM PDUs were received on the same port
 * as the previous.
 *
 * Field: ::VTSS_VOP_VOP_CTRL . CCM_RX_SRC_PORT_DETECT_CNT
 */
#define  VTSS_F_VOP_VOP_CTRL_CCM_RX_SRC_PORT_DETECT_CNT(x)  VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_VOP_VOP_CTRL_CCM_RX_SRC_PORT_DETECT_CNT     VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_VOP_VOP_CTRL_CCM_RX_SRC_PORT_DETECT_CNT(x)  VTSS_EXTRACT_BITFIELD(x,7,3)

/**
 * \brief
 * Asserting this bit will disable the Y.1731 MEL checking (RX / TX) in the
 * VOE when the VOE is configured for G.8113.1 OAM.This is intended for use
 * with G.8113.1 OAM.Since the MEL has no meaning in MPLS OAM, it is
 * possible to disable the MEL using this bit, even if the standard
 * specifies to set the MEL values of all OAM PDUs to the correct value.
 *
 * \details
 * 0: MEL checking is done in the VOE as per Y.1731
 * 1: MEL checking is disabled in the VOE. All frames are considered to
 * have correct MEL.
 *
 * Field: ::VTSS_VOP_VOP_CTRL . G_8113_1_MEL_CHK_DIS
 */
#define  VTSS_F_VOP_VOP_CTRL_G_8113_1_MEL_CHK_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_VOP_CTRL_G_8113_1_MEL_CHK_DIS  VTSS_BIT(6)
#define  VTSS_X_VOP_VOP_CTRL_G_8113_1_MEL_CHK_DIS(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * The G.8113.1 standard (date: 11/2012) is not 100% clear on which MEP IDs
 * are being exchanged and verified when two MEPs are exchanging 'LBM
 * Target MEP ID' TLV <-> LBR 'Replying LBR MEP ID' TLV.It is therefore
 * configurable which MEP IDs are carried in the TLVs, and from this
 * follows which MEP IDs whill be used in the Initiator / Responder VOEs
 * for MEP ID verification.The 4 possible scenarios are as follows:Scenario
 * A:--------------------------------Initiator MEP transmits 'Target MEP ID
 * TLV' with the Initiator MEP ID (local MEP ID)Responder MEP replies with
 * 'Replying MEP ID TLV' with the Initiator MEP ID (remote MEP ID)In this
 * scenario the 'Responder MEP' must verify the Rx LBM Target MEP ID
 * against the remote MEP ID (CCM_MEPID)In this scenario the 'Initiator
 * MEP' must verify the Rx LBR Replying MEP ID against the local MEP ID
 * (VOE_MEPID)Scenario B:--------------------------------Initiator MEP
 * transmits 'Target MEP ID TLV' with the Initiator MEP ID (local MEP
 * ID)Responder MEP replies with  'Replying MEP ID TLV' with the Responder
 * MEP ID (local MEP ID)In this scenario the 'Responder MEP' must verify
 * the Rx LBM Target MEP ID against the remote MEP ID (CCM_MEPID)In this
 * scenario the 'Initiator MEP' must verify the Rx LBR Replying MEP ID
 * against the remote MEP ID (CCM_MEPID)Scenario
 * C:--------------------------------Initiator MEP transmits 'Target MEP ID
 * TLV' with the Responder MEP ID (remote MEP ID)Responder MEP replies with
 *  'Replying MEP ID TLV' with the Responder MEP ID (local MEP ID)In this
 * scenario the 'Responder MEP' must verify the Rx LBM Target MEP ID
 * against the local MEP ID (VOE_MEPID)In this scenario the 'Initiator MEP'
 * must verify the Rx LBR Replying MEP ID against the remote MEP ID
 * (CCM_MEPID)Scenario D:--------------------------------Initiator MEP
 * transmits 'Target MEP ID TLV' with the Responder MEP ID (remote MEP
 * ID)Responder MEP replies with  'Replying MEP ID TLV' with the Initiator
 * MEP ID (remote MEP ID)In this scenario the 'Responder MEP' must verify
 * the Rx LBM Target MEP ID against the local MEP ID (VOE_MEPID)In this
 * scenario the 'Initiator MEP' must verify the Rx LBR Replying MEP ID
 * against the local MEP ID (VOE_MEPID)
 *
 * \details
 * 00: Scenario A
 * 01: Scenario B
 * 10: Scenario C
 * 11: Scenario D
 *
 * Field: ::VTSS_VOP_VOP_CTRL . G_8113_1_MEP_SCENARIO
 */
#define  VTSS_F_VOP_VOP_CTRL_G_8113_1_MEP_SCENARIO(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VOP_VOP_CTRL_G_8113_1_MEP_SCENARIO     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VOP_VOP_CTRL_G_8113_1_MEP_SCENARIO(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * If enabled the G.8113.1 LBR Rx errors at the 'Initiator MEP' are counted
 * in the following counters:MEPID errors:  *
 * VOP:VOE_STAT:CCM_RX_ERR_1.CCM_RX_MEPID_ERR_CNTMEGID errors: *
 * VOP:VOE_STAT:CCM_RX_ERR_1.CCM_RX_MEGID_ERR_CNTThese counters are reused
 * from Y.1731 CCM error counters.Note that only LBR Rx due to MEP ID and
 * MEG ID mismatch are counted.LBR Rx errors due to 'illegal ID Sub-Type'
 * and 'illlegal Loopback Indicator' are not counted.This bit only has
 * effect for VOEs configured for G.8113.1 OAM.
 *
 * \details
 * 0: Do not count G.8113.1 LBR Rx errors.
 * 1: Count G.8113.1 LBR Rx errors.
 *
 * Field: ::VTSS_VOP_VOP_CTRL . G_8113_1_CNT_LBR_RX_ERROR_ENA
 */
#define  VTSS_F_VOP_VOP_CTRL_G_8113_1_CNT_LBR_RX_ERROR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_VOP_CTRL_G_8113_1_CNT_LBR_RX_ERROR_ENA  VTSS_BIT(3)
#define  VTSS_X_VOP_VOP_CTRL_G_8113_1_CNT_LBR_RX_ERROR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * When the VOE is configured for G.8113.1 OAM, the 'Initiator MEP' will
 * determine if incoming Rx LBR PDUs carry the 'Requesting MEP ID' TLV.If
 * so the 'Initiator MEP' will determine if the 'Loopback Indicator' has
 * been set to '1' by the 'Responder MEP'.If the 'Loopback Indicator' is
 * not equal to '1' the frame is marked as invalid.In the VOE the 'Loopback
 * Indicator' check is optional and can be configured using this bitfield.
 *
 * \details
 * 0: Disable the 'Loopback Indicator' check in the 'Initiator MEP"
 * (G.8113.1 OAM)
 * 1: Enable the 'Loopback Indicator' check in the 'Initiator MEP"
 * (G.8113.1 OAM)
 *
 * Field: ::VTSS_VOP_VOP_CTRL . G_8113_1_LBK_INDC_CHK_ENA
 */
#define  VTSS_F_VOP_VOP_CTRL_G_8113_1_LBK_INDC_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_VOP_CTRL_G_8113_1_LBK_INDC_CHK_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_VOP_CTRL_G_8113_1_LBK_INDC_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)


/**
 * \brief Configuring destination for frames extracted to the CPU by Ethernet VOEs
 *
 * \details
 * This register configures the destination for OAM frames which are
 * extracted to CPU by the VOE for various reasons.
 *
 * An OAM PDU may be extracted to the CPU for various reasons:
 *  * Based on PDU type (See register: VOP:VOE_CONF:OAM_CPU_COPY_CTRL.*
 *  * OAM error condition (e.g. DMAC error)
 *  * PDU specific extraction reasons.
 *
 * Most HW supported OAM PDUs have their own configuration, while some
 * related PDUs share a single configuration.
 *
 * The configuration for each OAM PDU consists of one bit field which
 * indicate which of the extraction queues the relevant PDUs are extracted:
 *
 *  *_CPU_QU
 *
 * OAM PDU types which do not have a specific configuration will use the
 * default configuration:
 *
 * DEF_COPY_CPU_QU
 *
 * The details are described for each bit field.
 *
 * Register: \a VOP:COMMON:CPU_EXTR_CFG
 */
#define VTSS_VOP_CPU_EXTR_CFG                VTSS_IOREG(VTSS_TO_VOP,0x357f)

/**
 * \brief
 * Configures the destination for PDUs extracted to the Default CPU
 * queue.The default CPU extraction queue is used for extraction of PDUs
 * which do not have a dedicated extraction queue (UNKNOWN OPCODES).
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG . DEF_COPY_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_DEF_COPY_QU(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_DEF_COPY_QU     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_DEF_COPY_QU(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * Configures the CPU queue port of the CPU error queue.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG . CPU_ERR_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_CPU_ERR_QU(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_CPU_ERR_QU     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_CPU_ERR_QU(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * Configures the CPU queue to which LMM/SLM frames are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG . LMM_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_LMM_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_LMM_CPU_QU     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_LMM_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * Configures the CPU queue to which LMR / SLR / 1SL frames are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG . LMR_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_LMR_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_LMR_CPU_QU     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_LMR_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * Configures the CPU queue to which DMM frames are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG . DMM_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_DMM_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_DMM_CPU_QU     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_DMM_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Configures the CPU queue to which DMR and 1DM frames are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG . DMR_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_DMR_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_DMR_CPU_QU     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_DMR_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Configuring destination for frames extracted to the CPU.
 *
 * \details
 * See description for CPU_EXTR_CFG
 *
 * Register: \a VOP:COMMON:CPU_EXTR_CFG_1
 */
#define VTSS_VOP_CPU_EXTR_CFG_1              VTSS_IOREG(VTSS_TO_VOP,0x3580)

/**
 * \brief
 * Configures the CPU queue to which CCM frames are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG_1 . CCM_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_1_CCM_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_1_CCM_CPU_QU     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_1_CCM_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * Configures the CPU queue to which CCM-LM frames are extracted.CCM-LM
 * frames are CCM PDUs with non-zero content of the LM counters in the PDU
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG_1 . CCM_LM_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_1_CCM_LM_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_1_CCM_LM_CPU_QU     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_1_CCM_LM_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * Configures the CPU queue to which LBM frames are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG_1 . LBM_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_1_LBM_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_1_LBM_CPU_QU     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_1_LBM_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * Configures the CPU queue to which LBR and SAM_SEQ frames are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG_1 . LBR_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_1_LBR_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_1_LBR_CPU_QU     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_1_LBR_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * Configures the CPU queue to which TST frames are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG_1 . TST_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_1_TST_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_1_TST_CPU_QU     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_1_TST_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Configures the CPU queue to which LTM/LTR frames are
 * extracted.(Configuration is shared for LTM and LTR PDUs)
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG_1 . LT_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_1_LT_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_1_LT_CPU_QU     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_1_LT_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Configuring destination for frames extracted to the CPU.
 *
 * \details
 * See description for CPU_EXTR_CFG
 *
 * Register: \a VOP:COMMON:CPU_EXTR_CFG_2
 */
#define VTSS_VOP_CPU_EXTR_CFG_2              VTSS_IOREG(VTSS_TO_VOP,0x3581)

/**
 * \brief
 * Configures the CPU queue to which AIS frames are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG_2 . AIS_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_2_AIS_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_2_AIS_CPU_QU     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_2_AIS_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * Configures the CPU queue to which LCK frames are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG_2 . LCK_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_2_LCK_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_2_LCK_CPU_QU     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_2_LCK_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Configures the CPU queue to which CSF frames are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_CFG_2 . CSF_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_CFG_2_CSF_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CPU_EXTR_CFG_2_CSF_CPU_QU     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CPU_EXTR_CFG_2_CSF_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Configuring destination for frames extracted to the CPU by MPLS VOEs
 *
 * \details
 * See description for CPU_EXTR_CFG
 *
 * Register: \a VOP:COMMON:CPU_EXTR_MPLS
 */
#define VTSS_VOP_CPU_EXTR_MPLS               VTSS_IOREG(VTSS_TO_VOP,0x3582)

/**
 * \brief
 * Configures the CPU queue to which BFD-CC PDUs are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_MPLS . BFD_CC_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_MPLS_BFD_CC_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CPU_EXTR_MPLS_BFD_CC_CPU_QU     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CPU_EXTR_MPLS_BFD_CC_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Configures the CPU queue to which BFD-CV PDUs are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_MPLS . BFD_CV_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_MPLS_BFD_CV_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CPU_EXTR_MPLS_BFD_CV_CPU_QU     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CPU_EXTR_MPLS_BFD_CV_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Configuring destination for frames extracted to the CPU by L3 VOEs
 *
 * \details
 * See description for CPU_EXTR_CFG
 *
 * Register: \a VOP:COMMON:CPU_EXTR_L3
 */
#define VTSS_VOP_CPU_EXTR_L3                 VTSS_IOREG(VTSS_TO_VOP,0x3583)

/**
 * \brief
 * Configures the CPU queue to which TCP frames are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_L3 . TCP_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_L3_TCP_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CPU_EXTR_L3_TCP_CPU_QU     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CPU_EXTR_L3_TCP_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Configures the CPU queue to which TWAMP frames are extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_CPU_EXTR_L3 . TWAMP_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_L3_TWAMP_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CPU_EXTR_L3_TWAMP_CPU_QU     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CPU_EXTR_L3_TWAMP_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Define valid y.1731 PDU version number.
 *
 * \details
 * This register group allows configuration of which versions of the PDU is
 * valid for each of the Y.1731 PDUs supported by HW processing.
 *
 * Only the PDUs which are being processed by VOE can be verified by the
 * VOE.
 *
 * For PDUs being forwarded to the CPU the version is assumed to be
 * verified in SW.
 *
 * The version is configured commonly for Message and Response of the same
 * PDU type.
 *
 * For each PDU (pair) there are 8 bits, each representing a version
 * number: 0 - 7.
 *
 * Asserting the bit corresponding to a given version will configure the
 * VOE to accept PDUs of this version.
 *
 * E.g. the following will configure VERSION = 1 as being valid for
 * CCM(-LM) frames.
 *  * CCM_VERSION(1) = 1
 *
 * Register: \a VOP:COMMON:VERSION_CTRL
 */
#define VTSS_VOP_VERSION_CTRL                VTSS_IOREG(VTSS_TO_VOP,0x3584)

/**
 * \brief
 * Configure which versions of the CCM(-LM) PDU will be processed by the
 * VOE.
 *
 * \details
 * CCM_VERSION(x) = '0'; Version X of the CCM(-LM) PDU is invalid.
 * CCM_VERSION(x) = '1'; Version X of the CCM(-LM) PDU is valid.
 *
 * Field: ::VTSS_VOP_VERSION_CTRL . CCM_VERSION
 */
#define  VTSS_F_VOP_VERSION_CTRL_CCM_VERSION(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_VOP_VERSION_CTRL_CCM_VERSION     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_VOP_VERSION_CTRL_CCM_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * Configure which versions of the LMM/LMR PDU will be processed by the
 * VOE.
 *
 * \details
 * LM_VERSION(x) = '0'; Version X of the LMM/LMR PDU is invalid.
 * LM_VERSION(x) = '1'; Version X of the LMM/LMR PDU is valid.
 *
 * Field: ::VTSS_VOP_VERSION_CTRL . LM_VERSION
 */
#define  VTSS_F_VOP_VERSION_CTRL_LM_VERSION(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_VOP_VERSION_CTRL_LM_VERSION     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_VOP_VERSION_CTRL_LM_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Configure which versions of the DMM/DMR PDU will be processed by the
 * VOE.
 *
 * \details
 * DM_VERSION(x) = '0'; Version X of the DMM/DMR PDU is invalid.
 * DM_VERSION(x) = '1'; Version X of the DMM/DMR PDU is valid.
 *
 * Field: ::VTSS_VOP_VERSION_CTRL . DM_VERSION
 */
#define  VTSS_F_VOP_VERSION_CTRL_DM_VERSION(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VOP_VERSION_CTRL_DM_VERSION     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VOP_VERSION_CTRL_DM_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Configure which versions of the 1DM PDU will be processed by the VOE.
 *
 * \details
 * SDM_VERSION(x) = '0'; Version X of the 1DM PDU is invalid.
 * SDM_VERSION(x) = '1'; Version X of the 1DM PDU is valid.
 *
 * Field: ::VTSS_VOP_VERSION_CTRL . SDM_VERSION
 */
#define  VTSS_F_VOP_VERSION_CTRL_SDM_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VOP_VERSION_CTRL_SDM_VERSION     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VOP_VERSION_CTRL_SDM_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Define valid y.1731 PDU version number.
 *
 * \details
 * This register group allows configuration of which versions of the PDU is
 * valid for each of the Y.1731 PDUs supported by HW processing.
 *
 * Only the PDUs which are being processed by VOE can be verified by the
 * VOE.
 *
 * For PDUs being forwarded to the CPU the version is assumed to be
 * verified in SW.
 *
 * The version is configured commonly for Message and Response of the same
 * PDU type.
 *
 * For each PDU (pair) there are 8 bits, each representing a version
 * number: 0 - 7.
 *
 * Asserting the bit corresponding to a given version will configure the
 * VOE to accept PDUs of this version.
 *
 * E.g. the following will configure VERSION = 1 as being valid for
 * CCM(-LM) frames.
 *  * CCM_VERSION(1) = 1
 *
 * Register: \a VOP:COMMON:VERSION_CTRL_2
 */
#define VTSS_VOP_VERSION_CTRL_2              VTSS_IOREG(VTSS_TO_VOP,0x3585)

/**
 * \brief
 * Configure which versions of the TST PDU will be processed by the VOE.
 *
 * \details
 * TST_VERSION(x) = '0'; Version X of the TST PDU is invalid.
 * TST_VERSION(x) = '1'; Version X of the TST PDU is valid.
 *
 * Field: ::VTSS_VOP_VERSION_CTRL_2 . TST_VERSION
 */
#define  VTSS_F_VOP_VERSION_CTRL_2_TST_VERSION(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_VOP_VERSION_CTRL_2_TST_VERSION     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_VOP_VERSION_CTRL_2_TST_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * Configure which versions of the LBM/LBR PDU will be processed by the
 * VOE.
 *
 * \details
 * LB_VERSION(x) = '0'; Version X of the LBM/LBR PDU is invalid.
 * LB_VERSION(x) = '1'; Version X of the LBM/LBR PDU is valid.
 *
 * Field: ::VTSS_VOP_VERSION_CTRL_2 . LB_VERSION
 */
#define  VTSS_F_VOP_VERSION_CTRL_2_LB_VERSION(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_VOP_VERSION_CTRL_2_LB_VERSION     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_VOP_VERSION_CTRL_2_LB_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Configure which versions of the SLM/SLR PDU will be processed by the
 * VOE.
 *
 * \details
 * SL_VERSION(x) = '0'; Version X of the SLM/SLR PDU is invalid.
 * SL_VERSION(x) = '1'; Version X of the SLM/SLR PDU is valid.
 *
 * Field: ::VTSS_VOP_VERSION_CTRL_2 . SL_VERSION
 */
#define  VTSS_F_VOP_VERSION_CTRL_2_SL_VERSION(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VOP_VERSION_CTRL_2_SL_VERSION     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VOP_VERSION_CTRL_2_SL_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Configure which versions of the 1SL PDU will be processed by the VOE.
 *
 * \details
 * SL1_VERSION(x) = '0'; Version X of the 1SL PDU is invalid.
 * SL1_VERSION(x) = '1'; Version X of the 1SL PDU is valid.
 *
 * Field: ::VTSS_VOP_VERSION_CTRL_2 . SL1_VERSION
 */
#define  VTSS_F_VOP_VERSION_CTRL_2_SL1_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VOP_VERSION_CTRL_2_SL1_VERSION     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VOP_VERSION_CTRL_2_SL1_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Define valid y.1731 PDU version number.
 *
 * \details
 * This register group allows configuration of which versions of the PDU is
 * valid for each of the Y.1731 PDUs supported by HW processing.
 *
 * Only the PDUs which are being processed by VOE can be verified by the
 * VOE.
 *
 * For PDUs being forwarded to the CPU the version is assumed to be
 * verified in SW.
 *
 * The version is configured commonly for Message and Response of the same
 * PDU type.
 *
 * For each PDU (pair) there are 8 bits, each representing a version
 * number: 0 - 7.
 *
 * Asserting the bit corresponding to a given version will configure the
 * VOE to accept PDUs of this version.
 *
 * E.g. the following will configure VERSION = 1 as being valid for
 * CCM(-LM) frames.
 *  * CCM_VERSION(1) = 1
 *
 * Register: \a VOP:COMMON:VERSION_CTRL_3
 */
#define VTSS_VOP_VERSION_CTRL_3              VTSS_IOREG(VTSS_TO_VOP,0x3586)

/**
 * \brief
 * Configure which versions of the AIS PDU will be processed by the VOE.
 *
 * \details
 * AIS_VERSION(x) = '0'; Version X of the AIS PDU is invalid.
 * AIS_VERSION(x) = '1'; Version X of the AIS PDU is valid.
 *
 * Field: ::VTSS_VOP_VERSION_CTRL_3 . AIS_VERSION
 */
#define  VTSS_F_VOP_VERSION_CTRL_3_AIS_VERSION(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_VOP_VERSION_CTRL_3_AIS_VERSION     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_VOP_VERSION_CTRL_3_AIS_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Configure which versions of the LCK PDU will be processed by the VOE.
 *
 * \details
 * LCK_VERSION(x) = '0'; Version X of the LCK PDU is invalid.
 * LCK_VERSION(x) = '1'; Version X of the LCK PDU is valid.
 *
 * Field: ::VTSS_VOP_VERSION_CTRL_3 . LCK_VERSION
 */
#define  VTSS_F_VOP_VERSION_CTRL_3_LCK_VERSION(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VOP_VERSION_CTRL_3_LCK_VERSION     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VOP_VERSION_CTRL_3_LCK_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Configure which versions of the CSF PDU will be processed by the VOE.
 *
 * \details
 * CSF_VERSION(x) = '0'; Version X of the CSF PDU is invalid.
 * CSF_VERSION(x) = '1'; Version X of the CSF PDU is valid.
 *
 * Field: ::VTSS_VOP_VERSION_CTRL_3 . CSF_VERSION
 */
#define  VTSS_F_VOP_VERSION_CTRL_3_CSF_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VOP_VERSION_CTRL_3_CSF_VERSION     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VOP_VERSION_CTRL_3_CSF_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Version control configuration for MPLS
 *
 * \details
 * Register: \a VOP:COMMON:VERSION_CTRL_MPLS
 */
#define VTSS_VOP_VERSION_CTRL_MPLS           VTSS_IOREG(VTSS_TO_VOP,0x3587)

/**
 * \brief
 * The VOE will optionally validate the version of the incoming BFD frames
 * against the value configured in this register.If the version in the
 * incoming frame is not as configured, the frame will be discarded.The Rx
 * validation is configured in the following bitfields: *
 * VOP_MPLS:VOE_CONF_MPLS:BFD_CONFIG.BFD_RX_VERIFY_*
 *
 * \details
 * Field: ::VTSS_VOP_VERSION_CTRL_MPLS . BFD_VERSION
 */
#define  VTSS_F_VOP_VERSION_CTRL_MPLS_BFD_VERSION(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_VERSION_CTRL_MPLS_BFD_VERSION     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_VERSION_CTRL_MPLS_BFD_VERSION(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Generic OAM PDU Opcodes configuration
 *
 * \details
 * The VOE implements HW support for a number of selected OAM PDUs which
 * all have dedicated control registers.
 *
 * In addition to the selected OAM PDUs with dedicated control registers,
 * the VOE further supports configuring 16 Generic Opcodes, which can be
 * extracted to CPU or forwarded independently of other OpCodes.
 *
 * The value of each OpCode is configured globally across all VOEs in the
 * following bit field:
 *
 *  * GENERIC_OPCODE_VAL
 *
 * An opcode which is not explicitly supported and which not configured as
 * a Generic OpCode will be treated as an UNKNOWN opcode.
 *
 * The extraction and forwarding of Generic OpCodes can be configured
 * individually pr. VOE using the following registers:
 *
 *  * VOP:VOE_CONF:OAM_CPU_COPY_CTRL_2.GENERIC_COPY_MASK
 *  * VOP:VOE_CONF:OAM_CNT_OAM_CTRL.GENERIC_OAM_CNT_MASK
 *  * VOP:VOE_CONF:OAM_CNT_DATA_CTRL.GENERIC_DATA_CNT_MASK
 *
 * Register: \a VOP:COMMON:OAM_GENERIC_CFG
 *
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_GEN_OPCODES (??), 0-15
 */
#define VTSS_VOP_OAM_GENERIC_CFG(ri)         VTSS_IOREG(VTSS_TO_VOP,0x3588 + (ri))

/**
 * \brief
 * This value configures the Y.1731 OpCode to be processed as a Generic
 * OpCode corresponding to this generic Index.
 *
 * \details
 * Field: ::VTSS_VOP_OAM_GENERIC_CFG . GENERIC_OPCODE_VAL
 */
#define  VTSS_F_VOP_OAM_GENERIC_CFG_GENERIC_OPCODE_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VOP_OAM_GENERIC_CFG_GENERIC_OPCODE_VAL     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VOP_OAM_GENERIC_CFG_GENERIC_OPCODE_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,8)

/**
 * \brief
 * Configures the CPU queue to which frames for this generic OpCode are
 * extracted.
 *
 * \details
 * 0: CPU queue 0
 * 1: CPU queue 1
 * ...
 * 7: CPU queue 7
 *
 * Field: ::VTSS_VOP_OAM_GENERIC_CFG . GENERIC_OPCODE_CPU_QU
 */
#define  VTSS_F_VOP_OAM_GENERIC_CFG_GENERIC_OPCODE_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_VOP_OAM_GENERIC_CFG_GENERIC_OPCODE_CPU_QU     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_VOP_OAM_GENERIC_CFG_GENERIC_OPCODE_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,8,3)

/**
 * \brief
 * If this bit is asserted, the DMAC check will be disabled for this
 * generic OpCode, regardless of the configuration of the bit
 * field:VOP:VOE_CONF:VOE_CTRL.RX_DMAC_CHK_SELThis bit is required because
 * some OpCodes (i.e. Ring PDU) will use a DMAC which is different from the
 * configured Multicast and Unicast.
 *
 * \details
 * 0: Perform DMAC check according to the value configured in
 * VOP:VOE_CONF:VOE_CTRL.RX_DMAC_CHK_SEL
 * 1: No DMAC check for this Generic OpCode.
 *
 * Field: ::VTSS_VOP_OAM_GENERIC_CFG . GENERIC_DMAC_CHK_DIS
 */
#define  VTSS_F_VOP_OAM_GENERIC_CFG_GENERIC_DMAC_CHK_DIS(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_VOP_OAM_GENERIC_CFG_GENERIC_DMAC_CHK_DIS  VTSS_BIT(17)
#define  VTSS_X_VOP_OAM_GENERIC_CFG_GENERIC_DMAC_CHK_DIS(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * If this bit is asserted, the server blocking function (aBLK) is enabled
 * for this generic OpCode, when the VOE is processing OAM PDUs. This means
 * that frames will be blocked in the processing VOE, depending on the
 * setting of:	* VOP:VOE_CONF_REG:VOE_MISC_CONFIG.BLK_ENAIf this bit is
 * de-asserted, the server blocking function (aBLK) has no effect on
 * injection/extraction of OAM PDUs with this generic OpCode.
 *
 * \details
 * 0: No server blocking for this Generic OpCode when the VOE is processing
 * the OAM PDU.
 * 1: Perform server blocking according to the configuration of
 * VOP:VOE_CONF_REG:VOE_MISC_CONFIG.BLK_ENA, when the VOE is processing the
 * OAM PDU.
 *
 * Field: ::VTSS_VOP_OAM_GENERIC_CFG . GENERIC_BLK_SERVER_ENA
 */
#define  VTSS_F_VOP_OAM_GENERIC_CFG_GENERIC_BLK_SERVER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_VOP_OAM_GENERIC_CFG_GENERIC_BLK_SERVER_ENA  VTSS_BIT(18)
#define  VTSS_X_VOP_OAM_GENERIC_CFG_GENERIC_BLK_SERVER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * If this bit is asserted, the client blocking function (LOCK) is enabled
 * for this generic OpCode, when Rx injecting OAM PDUs into the client
 * flows. This means that frames will be blocked in the VOE of the Rx
 * injection, depending on the setting of:  *
 * VOP:VOE_CONF_REG:VOE_MISC_CONFIG.BLK_ENAIf this bit is de-asserted, the
 * client blocking function (LOCK) has no effect on Rx injection of OAM
 * PDUs with this generic OpCode.
 *
 * \details
 * 0: No client blocking for this Generic OpCode when Rx injecting the OAM
 * PDU.
 * 1: Perform client blocking according to the configuration of
 * VOP:VOE_CONF_REG:VOE_MISC_CONFIG.BLK_ENA, when Rx injecting into the
 * VOE.

 *
 * Field: ::VTSS_VOP_OAM_GENERIC_CFG . GENERIC_BLK_CLIENT_ENA
 */
#define  VTSS_F_VOP_OAM_GENERIC_CFG_GENERIC_BLK_CLIENT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_VOP_OAM_GENERIC_CFG_GENERIC_BLK_CLIENT_ENA  VTSS_BIT(19)
#define  VTSS_X_VOP_OAM_GENERIC_CFG_GENERIC_BLK_CLIENT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,19,1)


/**
 * \brief Generic OAM PDU Opcodes configuration
 *
 * \details
 * The VOE implements HW support for a number of dedicated MPLS-TP
 * codepoints (BFD CC/CV) which all have dedicated control registers.
 *
 * In addition to the dedicated MPLS-TP Codepoints with dedicated control
 * registers, the VOE further supports configuring 8 Generic Codepoints,
 * which can be extracted to CPU or forwarded independently of other
 * Codepoints.
 *
 * The Generic Codepoints are configured using this register.
 *
 * The value of each Codepoint is configured globally across all VOEs in
 * the following bit field:
 *
 *  * GENERIC_CODEPOINT_VAL
 *
 * A codepoint which is not explicitly supported and which not configured
 * as a Generic Codepoint will be treated as an UNKNOWN Codepoint.
 *
 * The extraction and forwarding of Generic Codepoints can be configured
 * individually pr. VOE using the following registers:
 *  * VOP_MPLS:VOE_CONF_MPLS:CPU_COPY_CTRL_MPLS.GENERIC_COPY_MASK
 *  * VOP_MPLS:VOE_CONF_MPLS:OAM_CNT_SEL_MPLS.GENERIC_CPT_CNT_SEL_MASK
 *
 * Register: \a VOP:COMMON:MPLS_GENERIC_CODEPOINT
 *
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_GEN_OPCODES (??), 0-15
 */
#define VTSS_VOP_MPLS_GENERIC_CODEPOINT(ri)  VTSS_IOREG(VTSS_TO_VOP,0x3598 + (ri))

/**
 * \brief
 * This value configures the MPLS-TP G-ACH Channel Type to be processed as
 * a Generic OpCode corresponding to this generic Index.
 *
 * \details
 * Field: ::VTSS_VOP_MPLS_GENERIC_CODEPOINT . GENERIC_CODEPOINT_VAL
 */
#define  VTSS_F_VOP_MPLS_GENERIC_CODEPOINT_GENERIC_CODEPOINT_VAL(x)  VTSS_ENCODE_BITFIELD(x,11,16)
#define  VTSS_M_VOP_MPLS_GENERIC_CODEPOINT_GENERIC_CODEPOINT_VAL     VTSS_ENCODE_BITMASK(11,16)
#define  VTSS_X_VOP_MPLS_GENERIC_CODEPOINT_GENERIC_CODEPOINT_VAL(x)  VTSS_EXTRACT_BITFIELD(x,11,16)

/**
 * \brief
 * Configures CPU queue to which MPLS-TP OAM PDUs with a G-ACH Channel Type
 * configured as generic codepoints are extracted.
 *
 * \details
 * Field: ::VTSS_VOP_MPLS_GENERIC_CODEPOINT . GENERIC_CODEPOINT_CPU_QU
 */
#define  VTSS_F_VOP_MPLS_GENERIC_CODEPOINT_GENERIC_CODEPOINT_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_VOP_MPLS_GENERIC_CODEPOINT_GENERIC_CODEPOINT_CPU_QU     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_VOP_MPLS_GENERIC_CODEPOINT_GENERIC_CODEPOINT_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,8,3)


/**
 * \brief Proprietary SAM time stamping PDU format configuration
 *
 * \details
 * A VOE can be configured to support sequence numbering and time stamping
 * of non OAM frames.
 * This can be used for testing as specified in SAM or RFC2544 etc.
 *
 * This functionality is referred to as SAM_SEQ.
 *
 * Configuration of time stamp format of the proprietary non-OAM SAM PDUs
 * is done in this register and is common to all VOEs.
 *
 * Configuration of sequece numbering and per-VOE time stamp configuration
 * is done in:
 *
 *  * VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG

 *
 * Register: \a VOP:COMMON:SAM_SEQ_TS_CFG
 */
#define VTSS_VOP_SAM_SEQ_TS_CFG              VTSS_IOREG(VTSS_TO_VOP,0x35a8)

/**
 * \brief
 * This configures the byte offset to the 8-bytes TxTimestampf time stamp
 * to be updated within the non-OAM frame (SAM_SEQ).The PDU is assumed to
 * carry zeros in these bytes before the time stamp is inserted.For
 * Ethernet frames this field MUST be programmed a value no less than 2
 * bytes, to avoid overwriting the EPID field.For UDP frames this field
 * MUST be programmed a value no less than 8 bytes, to avoid overwriting
 * the UDP protocol information.Only even offset values are supported (the
 * LSB is ignored).The largest allowed value of this field is 72.The time
 * stamp in the PDU MUST be located within the first 148 bytes of the
 * frame. This implies that in case of a long encapsulation (e.g. IPv6 over
 * ETH over MPLS over ETH) there will be an upper limit to the valid value
 * of the offset.
 *
 * \details
 * Field: ::VTSS_VOP_SAM_SEQ_TS_CFG . SAM_SEQ_OFFSET_TS_TXTSF
 */
#define  VTSS_F_VOP_SAM_SEQ_TS_CFG_SAM_SEQ_OFFSET_TS_TXTSF(x)  VTSS_ENCODE_BITFIELD(x,21,7)
#define  VTSS_M_VOP_SAM_SEQ_TS_CFG_SAM_SEQ_OFFSET_TS_TXTSF     VTSS_ENCODE_BITMASK(21,7)
#define  VTSS_X_VOP_SAM_SEQ_TS_CFG_SAM_SEQ_OFFSET_TS_TXTSF(x)  VTSS_EXTRACT_BITFIELD(x,21,7)

/**
 * \brief
 * This configures the byte offset to the RxTimestampf time stamp to be
 * updated within the non-OAM frame (SAM_SEQ).The PDU is assumed to carry
 * zeros in these bytes before the time stamp is inserted.For Ethernet
 * frames this field MUST be programmed a value no less than 2 bytes, to
 * avoid overwriting the EPID field.For UDP frames this field MUST be
 * programmed a value no less than 8 bytes, to avoid overwriting the UDP
 * protocol information.Only even offset values are supported (the LSB is
 * ignored).The largest allowed value of this field is 72.The time stamp in
 * the PDU MUST be located within the first 148 bytes of the frame. This
 * implies that in case of a long encapsulation (e.g. IPv6 over ETH over
 * MPLS over ETH) there will be an upper limit to the valid value of the
 * offset.
 *
 * \details
 * Field: ::VTSS_VOP_SAM_SEQ_TS_CFG . SAM_SEQ_OFFSET_TS_RXTSF
 */
#define  VTSS_F_VOP_SAM_SEQ_TS_CFG_SAM_SEQ_OFFSET_TS_RXTSF(x)  VTSS_ENCODE_BITFIELD(x,14,7)
#define  VTSS_M_VOP_SAM_SEQ_TS_CFG_SAM_SEQ_OFFSET_TS_RXTSF     VTSS_ENCODE_BITMASK(14,7)
#define  VTSS_X_VOP_SAM_SEQ_TS_CFG_SAM_SEQ_OFFSET_TS_RXTSF(x)  VTSS_EXTRACT_BITFIELD(x,14,7)

/**
 * \brief
 * This configures the byte offset to the TxTimestampb time stamp to be
 * updated within the non-OAM frame (SAM_SEQ).The PDU is assumed to carry
 * zeros in these bytes before the time stamp is inserted.For Ethernet
 * frames this field MUST be programmed a value no less than 2 bytes, to
 * avoid overwriting the EPID field.For UDP frames this field MUST be
 * programmed a value no less than 8 bytes, to avoid overwriting the UDP
 * protocol information.Only even offset values are supported (the LSB is
 * ignored).The largest allowed value of this field is 72.The time stamp in
 * the PDU MUST be located within the first 148 bytes of the frame. This
 * implies that in case of a long encapsulation (e.g. IPv6 over ETH over
 * MPLS over ETH) there will be an upper limit to the valid value of the
 * offset.
 *
 * \details
 * Field: ::VTSS_VOP_SAM_SEQ_TS_CFG . SAM_SEQ_OFFSET_TS_TXTSB
 */
#define  VTSS_F_VOP_SAM_SEQ_TS_CFG_SAM_SEQ_OFFSET_TS_TXTSB(x)  VTSS_ENCODE_BITFIELD(x,7,7)
#define  VTSS_M_VOP_SAM_SEQ_TS_CFG_SAM_SEQ_OFFSET_TS_TXTSB     VTSS_ENCODE_BITMASK(7,7)
#define  VTSS_X_VOP_SAM_SEQ_TS_CFG_SAM_SEQ_OFFSET_TS_TXTSB(x)  VTSS_EXTRACT_BITFIELD(x,7,7)

/**
 * \brief
 * This configures the byte offset to the RxTimestampb time stamp to be
 * updated within the non-OAM frame (SAM_SEQ).The PDU is assumed to carry
 * zeros in these bytes before the time stamp is inserted.For Ethernet
 * frames this field MUST be programmed a value no less than 2 bytes, to
 * avoid overwriting the EPID field.For UDP frames this field MUST be
 * programmed a value no less than 8 bytes, to avoid overwriting the UDP
 * protocol information.Only even offset values are supported (the LSB is
 * ignored).The largest allowed value of this field is 72.The time stamp in
 * the PDU MUST be located within the first 148 bytes of the frame. This
 * implies that in case of a long encapsulation (e.g. IPv6 over ETH over
 * MPLS over ETH) there will be an upper limit to the valid value of the
 * offset.
 *
 * \details
 * Field: ::VTSS_VOP_SAM_SEQ_TS_CFG . SAM_SEQ_OFFSET_TS_RXTSB
 */
#define  VTSS_F_VOP_SAM_SEQ_TS_CFG_SAM_SEQ_OFFSET_TS_RXTSB(x)  VTSS_ENCODE_BITFIELD(x,0,7)
#define  VTSS_M_VOP_SAM_SEQ_TS_CFG_SAM_SEQ_OFFSET_TS_RXTSB     VTSS_ENCODE_BITMASK(0,7)
#define  VTSS_X_VOP_SAM_SEQ_TS_CFG_SAM_SEQ_OFFSET_TS_RXTSB(x)  VTSS_EXTRACT_BITFIELD(x,0,7)


/**
 * \brief Proprietary SAM time stamping PDU format configuration
 *
 * \details
 * See description for SAM_SEQ_TS_CFG.
 *
 * Register: \a VOP:COMMON:SAM_SEQ_TS_CFG_2
 */
#define VTSS_VOP_SAM_SEQ_TS_CFG_2            VTSS_IOREG(VTSS_TO_VOP,0x35a9)

/**
 * \brief
 * This configures the byte offset to the UDP checksum compesation field to
 * be updated within the non-OAM frame (SAM_SEQ).When a time stamp is
 * inserted into a UDP frame, the UDP checksum is not re-calculated, but
 * this field is updated to make the time stamp intertion UDP checksum
 * neutral.This field MUST be programmed a value no less than 8 bytes, to
 * avoid overwriting the UDP protocol information.Only even offset values
 * are supported (the LSB is ignored).The largest allowed value of this
 * field is 72.The UDP checksum compensation field in the PDU MUST be
 * located within the first 148 bytes of the frame. This implies that in
 * case of a long encapsulation (e.g. IPv6 over ETH over MPLS over ETH)
 * there will be an upper limit to the valid value of the offset.Update of
 * the UDP checksum compesation field is enabled in *
 * VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG.SAM_SEQ_TS_UPD_CHKSUM
 *
 * \details
 * Field: ::VTSS_VOP_SAM_SEQ_TS_CFG_2 . SAM_SEQ_OFFSET_TS_UDP_CHKSUM
 */
#define  VTSS_F_VOP_SAM_SEQ_TS_CFG_2_SAM_SEQ_OFFSET_TS_UDP_CHKSUM(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_SAM_SEQ_TS_CFG_2_SAM_SEQ_OFFSET_TS_UDP_CHKSUM     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_SAM_SEQ_TS_CFG_2_SAM_SEQ_OFFSET_TS_UDP_CHKSUM(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Loss Of Continuity Controller configuration
 *
 * \details
 * Configures LOC Controller to increment the LOC miss counters in the
 * VOEs.

 *
 * Register: \a VOP:COMMON:LOC_CTRL
 */
#define VTSS_VOP_LOC_CTRL                    VTSS_IOREG(VTSS_TO_VOP,0x35aa)

/**
 * \brief
 * Specifies the number of clk cycle before another scan entry can be
 * attempted.This can be used to space the LOC miss scanning of the VOEs.If
 * an active SCAN is ongoing, the VOE will scan through the VOE_STAT and
 * update the LOC miss counter of VOEs which are enabled for LOC
 * detection.The scan will be done in 'idle cycles'.'Idle cycles' are
 * defined as cycles where the is no frame access and no CSR access to the
 * VOP.
 *
 * \details
 * 0-1: A scan is attempted at every idle cycle in the VOP
 * 2: A scan is attempted no more often than every 2nd cycle.
 * 3: A scan is attempted no more often than every 3rd cycle.
 *
 * Field: ::VTSS_VOP_LOC_CTRL . LOC_SPACE_BETWEEN_ENTRY_SCAN
 */
#define  VTSS_F_VOP_LOC_CTRL_LOC_SPACE_BETWEEN_ENTRY_SCAN(x)  VTSS_ENCODE_BITFIELD(x,29,2)
#define  VTSS_M_VOP_LOC_CTRL_LOC_SPACE_BETWEEN_ENTRY_SCAN     VTSS_ENCODE_BITMASK(29,2)
#define  VTSS_X_VOP_LOC_CTRL_LOC_SPACE_BETWEEN_ENTRY_SCAN(x)  VTSS_EXTRACT_BITFIELD(x,29,2)

/**
 * \brief
 * When a LOC scan timer expires, the VOE will scan through all VOEs in the
 * VOP and increment the LOC miss counter of all the VOEs assigned to that
 * LOC timer.When a HMO scan timer expires, the VOE will scan through all
 * VOEs in the VOP and assert the HMO extraction bits configured for the
 * VOE.Another way to force a LOC scan / HMO is to write a mask to
 * LOC_FORCE_HW_SCAN_ENA. Each of the bits in this register represents a
 * LOC timer.Writing a mask to this register will force a LOC scan as if
 * the LOC timers indicated in the mask had expired.A forced scan will
 * start as soon as any currently active scan completesActive scan can be
 * stopped by disabling the LOC scan controller.The width of the SCAN_MASK
 * is 29 bits which are allocated as follows:bits 0-26: LOC scan timer 0 -
 * 26bits 27-28: HMO scan timer 0 - 1
 *
 * \details
 * 0: No force
 * bit 0 = 1: Force a scan of LOC scan timer 0
 * bit 1 = 1: Force a scan of LOC scan timer 1
 * bit 2 = 1: Force a scan of LOC scan timer 2
 * bit 3 = 1: Force a scan of LOC scan timer 3
 * bit 4 = 1: Force a scan of LOC scan timer 4
 * bit 5 = 1: Force a scan of LOC scan timer 5
 * bit 6 = 1: Force a scan of LOC scan timer 6
 * bit 7 = 1: Force a scan of LOC scan timer 7
 * ...
 * bit 25 = 1: Force a scan of LOC scan timer 25
 * bit 26 = 1: Force a scan of LOC scan timer 26
 * bit 27 = 1: Force a scan of HMO scan timer 0; (using HMO slot configured
 * in VOP::HMO_FORCE_SLOT_CFG(0).HMO_FORCE_SLOT)
 * bit 28 = 1: Force a scan of HMO scan timer 1; (using HMO slot configured
 * in VOP::HMO_FORCE_SLOT_CFG(1).HMO_FORCE_SLOT)
 *
 * Field: ::VTSS_VOP_LOC_CTRL . LOC_FORCE_HW_SCAN_ENA
 */
#define  VTSS_F_VOP_LOC_CTRL_LOC_FORCE_HW_SCAN_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,29)
#define  VTSS_M_VOP_LOC_CTRL_LOC_FORCE_HW_SCAN_ENA     VTSS_ENCODE_BITMASK(0,29)
#define  VTSS_X_VOP_LOC_CTRL_LOC_FORCE_HW_SCAN_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,29)


/**
 * \brief Configures the 7 different LOC scan periods
 *
 * \details
 * Independent timers are implemented to be used with the Loss Of
 * Continuity (LOC) Scan.
 *
 * This register implements the timeout period for every one of the 7 LOC
 * timers.
 * The timeout period is specified in the number of LOC base ticks between
 * every LOC timer expiry.
 *
 * For configuration of the LOC base tick, see bit field:
 *  * VOP::LOC_CTRL_2.LOC_BASE_TICK_CNT
 *
 *
 * A LOC miss count scan is initiated at half the configured LOC PERIOD.
 *
 * A VOE can be configured for LOC checking based on one of the 7 timeout
 * counters.
 *
 * The LOC Controller is used both by Ethernet VOEs and MPLS-TP VOEs for
 * LOC detection.
 *
 * Ethernet VOE:
 * ---------------
 * A LOC event is generated at the VOE when the CCM miss count is 7.
 *
 * VOP:VOE_STAT:CCM_STAT.CCM_MISS_CNT
 *
 * This effectively implements a LOC event at 3.5 times the configured LOC
 * period.
 *
 * MPLS-TP VOE:
 * --------------------------
 * A LOC event is generated at the VOE when the BFD_MISS_CNT is equal to
 * the valid Detect Multiplier in the VOE.
 *
 * Register: \a VOP:COMMON:LOC_PERIOD_CFG
 *
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_LOC_SCAN_CNT (??), 0-26
 */
#define VTSS_VOP_LOC_PERIOD_CFG(ri)          VTSS_IOREG(VTSS_TO_VOP,0x35ab + (ri))

/**
 * \brief
 * Configures Expiry Period of the 27 LOC timers as the number of
 * BASE_TICKs between every LOC timer expiry.The BASE_TICK is configured:
 * VOP::LOC_CTRL_2.LOC_BASE_TICK_CNT
 *
 * \details
 * A value of 0 disables the timeout for this counter. Configuration
 * example when LOC_BASE_TICK_CNT is 100ns:
 * 100: 10us
 * 1000: 100us
 * 10000: 1 ms
 * 33000: 3.3ms
 * 100000: 10ms
 * 1000000: 100ms
 * 10000000: 1s
 *
 * Field: ::VTSS_VOP_LOC_PERIOD_CFG . LOC_PERIOD_VAL
 */
#define  VTSS_F_VOP_LOC_PERIOD_CFG_LOC_PERIOD_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,31)
#define  VTSS_M_VOP_LOC_PERIOD_CFG_LOC_PERIOD_VAL     VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_X_VOP_LOC_PERIOD_CFG_LOC_PERIOD_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,31)


/**
 * \brief Configures the 2 different HMO scan periods
 *
 * \details
 * 2 independent HMO timers are implemented to be used with the auto
 * Hit-Me-Once (HMO) scan.
 *
 * This register implements a separate timeout period for each of the 2 HMO
 * timers.
 * The timeout period is specified in the number of LOC base ticks between
 * every HMO timer expiry.
 *
 * Each HMO scan timer has an associated HMO slot (0-7 i.e. 3 bit), which
 * is increased every time the HMO scan timer expires.
 * When a HMO scan timer expires and causes a HMO scan, the current HMO
 * slot is part of the scan, so that only the VOEs assigned to that HMO
 * slot are affected by the scan.
 *
 * This allows the distributing the VOEs assigned to a given HMO scan timer
 * into 8 HMO slots.
 *
 * Hence each VOE is only affected by 1 of 8 HMO scans for a given HMO scan
 * timer. I.e. to achieve auto HMO frame extraction every 1 second, the HMO
 * timer must be set to expire every 125 us.
 *
 * For configuration of the LOC base tick, see bit field:
 *  * VOP::LOC_CTRL_2.LOC_BASE_TICK_CNT
 *
 * A HMO scan is initiated at half the configured HMO PERIOD, because this
 * is the way the scans are implemented for LOC scanning.
 *
 * A VOE can be configured for HMO auto assertion based on one of the 2 HMO
 * timers.
 *
 * The HMO timers are used only Ethernet VOEs. The HMO timers have no
 * effect on MPLS-TP VOEs.
 *
 * Ethernet VOE:
 * -----------------------
 * The HMO events are assigned to a specific HMO scan timer:
 *  * VOP::HMO_TIMER_CFG.*
 *
 * The VOE is assigned a HMO slot using the following register:
 *  * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_SLOT
 *
 * When the HMO timer assigned to the VOE, causes a HMO scan with the HMO
 * slot assigned to the VOE, the VOE will assert the extraction bits
 * selected for auto HMO.
 *
 * The extraction bits are located in the following register:
 *  * VOP:VOE_STAT:PDU_EXTRACT
 *
 * The extraction bits are assigned for auto HMO in the following register:
 *  * VOP:VOE_STAT:AUTO_HIT_ME_ONCE
 *
 *
 *
 * MPLS-TP VOE:
 * --------------------------
 * The HMO counters have no effect.
 *
 * Register: \a VOP:COMMON:HMO_PERIOD_CFG
 *
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_HMO_SCAN_CNT (??), 0-1
 */
#define VTSS_VOP_HMO_PERIOD_CFG(ri)          VTSS_IOREG(VTSS_TO_VOP,0x35c6 + (ri))

/**
 * \brief
 * Configures expiry period of the 2 HMO timers as the number of BASE_TICKs
 * between every LOC timer expiry.The BASE_TICK is configured: *
 * VOP::LOC_CTRL_2.LOC_BASE_TICK_CNTDefault HMO timer is set to 0, which
 * causes the HMO timer to never expire.
 *
 * \details
 * With a LOC_BASE_TICK_CNT value of 200ns the HMO scan timer will expire
 * with the following intervals.
 *
 * A value of 0 disables the timeout for this counter.
 * 50: 10us
 * 500: 100us
 * 5000: 1 ms
 * 16500: 3.3ms
 * 50000: 10ms
 * 500000: 100ms
 * 5000000: 1s
 *
 * Field: ::VTSS_VOP_HMO_PERIOD_CFG . HMO_PERIOD_VAL
 */
#define  VTSS_F_VOP_HMO_PERIOD_CFG_HMO_PERIOD_VAL(x)  VTSS_ENCODE_BITFIELD(x,0,31)
#define  VTSS_M_VOP_HMO_PERIOD_CFG_HMO_PERIOD_VAL     VTSS_ENCODE_BITMASK(0,31)
#define  VTSS_X_VOP_HMO_PERIOD_CFG_HMO_PERIOD_VAL(x)  VTSS_EXTRACT_BITFIELD(x,0,31)


/**
 * \brief HMO slots used for forced scanning.
 *
 * \details
 * When an HMO scan is forced, the HMO slots used for the scan is
 * programmed in this register.
 *
 * A separate HMO slot can be programmed for each of the HMO timers.
 *
 * A HMO scan is forced using the following register:
 *  - VOP::LOC_CTRL.LOC_FORCE_HW_SCAN_ENA
 *
 * Register: \a VOP:COMMON:HMO_FORCE_SLOT_CFG
 *
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_HMO_SCAN_CNT (??), 0-1
 */
#define VTSS_VOP_HMO_FORCE_SLOT_CFG(ri)      VTSS_IOREG(VTSS_TO_VOP,0x35c8 + (ri))

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_HMO_FORCE_SLOT_CFG . HMO_FORCE_SLOT
 */
#define  VTSS_F_VOP_HMO_FORCE_SLOT_CFG_HMO_FORCE_SLOT(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_HMO_FORCE_SLOT_CFG_HMO_FORCE_SLOT     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_HMO_FORCE_SLOT_CFG_HMO_FORCE_SLOT(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Configure HMO TIMER for HMO extraction events.
 *
 * \details
 * There are 2 HMO timers, which allow for Auto HMO of selected frame
 * types.
 *
 * Each of the events which support HMO are assigned to one of the 2 HMO
 * timers using this register. This setting is hence global for all VOEs.
 *
 * For each of the bitfields, it is configured which of the HMO timers will
 * trigger the HMO bits to be asserted.
 *
 * In addition to the correct HMO timer expiring, the VOE must be
 * configured for the correct HMO SLOT and the Auto HMO must be enabled in
 * the VOE before the HMO bits are asserted.
 *
 * The is used to space the extracted frames, so the CPU does not get
 * flooded with frames from all active VOEs at once.
 *
 * Register: \a VOP:COMMON:HMO_TIMER_CFG
 */
#define VTSS_VOP_HMO_TIMER_CFG               VTSS_IOREG(VTSS_TO_VOP,0x35ca)

/**
 * \brief
 * Assign which HMO timer will trigger the following VOE Auto HMO bits: *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_RX_CCM_NXT_EXTRTo trigger the Auto HMO
 * bits, this must be enabled by the VOE: *
 * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_CCM_RX_BAD_NXT
 *
 * \details
 * Field: ::VTSS_VOP_HMO_TIMER_CFG . HMO_RX_CCM_NXT_TIMER
 */
#define  VTSS_F_VOP_HMO_TIMER_CFG_HMO_RX_CCM_NXT_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_HMO_TIMER_CFG_HMO_RX_CCM_NXT_TIMER  VTSS_BIT(12)
#define  VTSS_X_VOP_HMO_TIMER_CFG_HMO_RX_CCM_NXT_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Assign which HMO timer will trigger the following VOE Auto HMO bits: *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_RX_TLV_NON_ZERO_EXTRTo trigger the Auto HMO
 * bits, this must be enabled by the VOE: *
 * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_CCM_RX_TLV_NON_ZERO
 *
 * \details
 * Field: ::VTSS_VOP_HMO_TIMER_CFG . HMO_CCM_RX_TLV_NON_ZERO_TIMER
 */
#define  VTSS_F_VOP_HMO_TIMER_CFG_HMO_CCM_RX_TLV_NON_ZERO_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_HMO_TIMER_CFG_HMO_CCM_RX_TLV_NON_ZERO_TIMER  VTSS_BIT(11)
#define  VTSS_X_VOP_HMO_TIMER_CFG_HMO_CCM_RX_TLV_NON_ZERO_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Assign which HMO timer will trigger the following VOE Auto HMO bits: *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_ZERO_PERIOD_RX_ERR_EXTR *
 * VOP:VOE_STAT:PDU_EXTRACT.RX_MEL_LOW_ERR_EXTR *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_MEGID_RX_ERR_EXTR *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_MEPID_RX_ERR_EXTR *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_PERIOD_RX_ERR_EXTR *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_PRIO_RX_ERR_EXTRTo trigger the Auto HMO
 * bits, this must be enabled by the VOE: *
 * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_CCM_RX_BAD_NXT
 *
 * \details
 * Field: ::VTSS_VOP_HMO_TIMER_CFG . HMO_CCM_RX_BAD_NXT_TIMER
 */
#define  VTSS_F_VOP_HMO_TIMER_CFG_HMO_CCM_RX_BAD_NXT_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_HMO_TIMER_CFG_HMO_CCM_RX_BAD_NXT_TIMER  VTSS_BIT(10)
#define  VTSS_X_VOP_HMO_TIMER_CFG_HMO_CCM_RX_BAD_NXT_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Assign which HMO timer will trigger the following VOE Auto HMO bits:*
 * VOP:VOE_STAT:PDU_EXTRACT.RX_TEST_FRM_NXT_EXTRTo trigger the Auto HMO
 * bits, this must be enabled by the VOE: *
 * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_RX_TEST_FRM_NXT
 *
 * \details
 * Field: ::VTSS_VOP_HMO_TIMER_CFG . HMO_RX_TEST_FRM_NXT_TIMER
 */
#define  VTSS_F_VOP_HMO_TIMER_CFG_HMO_RX_TEST_FRM_NXT_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_HMO_TIMER_CFG_HMO_RX_TEST_FRM_NXT_TIMER  VTSS_BIT(9)
#define  VTSS_X_VOP_HMO_TIMER_CFG_HMO_RX_TEST_FRM_NXT_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Assign which HMO timer will trigger the following VOE Auto HMO bits:*
 * VOP:VOE_STAT:SYNLM_EXTRACT.EXTRACT_PEER_RX_SLM*
 * VOP:VOE_STAT:SYNLM_EXTRACT.EXTRACT_PEER_RX_SLRTo trigger the Auto HMO
 * bits, this must be enabled by the VOE: *
 * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_EXTRACT_PEER_RX_SLM *
 * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_EXTRACT_PEER_RX_SLR
 *
 * \details
 * Field: ::VTSS_VOP_HMO_TIMER_CFG . HMO_EXTRACT_PEER_RX_TIMER
 */
#define  VTSS_F_VOP_HMO_TIMER_CFG_HMO_EXTRACT_PEER_RX_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_HMO_TIMER_CFG_HMO_EXTRACT_PEER_RX_TIMER  VTSS_BIT(8)
#define  VTSS_X_VOP_HMO_TIMER_CFG_HMO_EXTRACT_PEER_RX_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Assign which HMO timer will trigger the following VOE Auto HMO bits:*
 * VOP:VOE_STAT:PDU_EXTRACT.AIS_ERR_EXTRTo trigger the Auto HMO bits, this
 * must be enabled by the VOE: *
 * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_AIS_RX_BAD_NXT
 *
 * \details
 * Field: ::VTSS_VOP_HMO_TIMER_CFG . HMO_AIS_RX_BAD_NXT_TIMER
 */
#define  VTSS_F_VOP_HMO_TIMER_CFG_HMO_AIS_RX_BAD_NXT_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_HMO_TIMER_CFG_HMO_AIS_RX_BAD_NXT_TIMER  VTSS_BIT(7)
#define  VTSS_X_VOP_HMO_TIMER_CFG_HMO_AIS_RX_BAD_NXT_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Assign which HMO timer will trigger the following VOE Auto HMO bits:*
 * VOP:VOE_STAT:PDU_EXTRACT.AIS_RX_FRM_NXT_EXTRTo trigger the Auto HMO
 * bits, this must be enabled by the VOE: *
 * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_AIS_RX_FRM_NXT
 *
 * \details
 * Field: ::VTSS_VOP_HMO_TIMER_CFG . HMO_AIS_RX_FRM_NXT_TIMER
 */
#define  VTSS_F_VOP_HMO_TIMER_CFG_HMO_AIS_RX_FRM_NXT_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_HMO_TIMER_CFG_HMO_AIS_RX_FRM_NXT_TIMER  VTSS_BIT(6)
#define  VTSS_X_VOP_HMO_TIMER_CFG_HMO_AIS_RX_FRM_NXT_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Assign which HMO timer will trigger the following VOE Auto HMO bits:*
 * VOP:VOE_STAT:PDU_EXTRACT.LCK_ERR_EXTRTo trigger the Auto HMO bits, this
 * must be enabled by the VOE: *
 * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_LCK_RX_BAD_NXT
 *
 * \details
 * Field: ::VTSS_VOP_HMO_TIMER_CFG . HMO_LCK_RX_BAD_NXT_TIMER
 */
#define  VTSS_F_VOP_HMO_TIMER_CFG_HMO_LCK_RX_BAD_NXT_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_HMO_TIMER_CFG_HMO_LCK_RX_BAD_NXT_TIMER  VTSS_BIT(5)
#define  VTSS_X_VOP_HMO_TIMER_CFG_HMO_LCK_RX_BAD_NXT_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Assign which HMO timer will trigger the following VOE Auto HMO bits:*
 * VOP:VOE_STAT:PDU_EXTRACT.LCK_RX_FRM_NXT_EXTRTo trigger the Auto HMO
 * bits, this must be enabled by the VOE: *
 * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_LCK_RX_FRM_NXT
 *
 * \details
 * Field: ::VTSS_VOP_HMO_TIMER_CFG . HMO_LCK_RX_FRM_NXT_TIMER
 */
#define  VTSS_F_VOP_HMO_TIMER_CFG_HMO_LCK_RX_FRM_NXT_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_HMO_TIMER_CFG_HMO_LCK_RX_FRM_NXT_TIMER  VTSS_BIT(4)
#define  VTSS_X_VOP_HMO_TIMER_CFG_HMO_LCK_RX_FRM_NXT_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Assign which HMO timer will trigger the following VOE Auto HMO bits:*
 * VOP:VOE_STAT:PDU_EXTRACT.CSF_ERR_EXTRTo trigger the Auto HMO bits, this
 * must be enabled by the VOE: *
 * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_CSF_RX_BAD_NXT
 *
 * \details
 * Field: ::VTSS_VOP_HMO_TIMER_CFG . HMO_CSF_RX_BAD_NXT_TIMER
 */
#define  VTSS_F_VOP_HMO_TIMER_CFG_HMO_CSF_RX_BAD_NXT_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_HMO_TIMER_CFG_HMO_CSF_RX_BAD_NXT_TIMER  VTSS_BIT(3)
#define  VTSS_X_VOP_HMO_TIMER_CFG_HMO_CSF_RX_BAD_NXT_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Assign which HMO timer will trigger the following VOE Auto HMO bits:*
 * VOP:VOE_STAT:PDU_EXTRACT.CSF_RX_FRM_NXT_EXTRTo trigger the Auto HMO
 * bits, this must be enabled by the VOE: *
 * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_CSF_RX_FRM_NXT
 *
 * \details
 * Field: ::VTSS_VOP_HMO_TIMER_CFG . HMO_CSF_RX_FRM_NXT_TIMER
 */
#define  VTSS_F_VOP_HMO_TIMER_CFG_HMO_CSF_RX_FRM_NXT_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_HMO_TIMER_CFG_HMO_CSF_RX_FRM_NXT_TIMER  VTSS_BIT(2)
#define  VTSS_X_VOP_HMO_TIMER_CFG_HMO_CSF_RX_FRM_NXT_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Assign which HMO timer will trigger the following VOE Auto HMO bits:*
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_RX_NXT_EXTRTo trigger the
 * Auto HMO bits, this must be enabled by the VOE:*
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_RX_NXT_HMO_ENA
 *
 * \details
 * Field: ::VTSS_VOP_HMO_TIMER_CFG . HMO_TWAMP_RX_NXT_TIMER
 */
#define  VTSS_F_VOP_HMO_TIMER_CFG_HMO_TWAMP_RX_NXT_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_HMO_TIMER_CFG_HMO_TWAMP_RX_NXT_TIMER  VTSS_BIT(1)
#define  VTSS_X_VOP_HMO_TIMER_CFG_HMO_TWAMP_RX_NXT_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Assign which HMO timer will trigger the following VOE Auto HMO bits:*
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.UNKNOWN_SESSION_RX_ERR_EXTR*
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.VOE_MAC_RX_ERR_EXTR*
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.VOE_IP_RX_ERR_EXTR*
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.PEER_IP_RX_ERR_EXTR*
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_MULT_RX_ERR_EXTR*
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_SEQ_NUM_RX_ERR_EXTRTo
 * trigger the Auto HMO bits, this must be enabled by the VOE:*
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.UNKNOWN_SESSION_RX_ERR_HMO_ENA*
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.VOE_MAC_RX_ERR_HMO_ENA*
 * VOP_L3:VOE_STAT_L3:EXTRACT_L3.VOE_IP_RX_ERR_HMO_ENA*
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.PEER_IP_RX_ERR_HMO_ENA*
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_MULT_RX_ERR_HMO_ENA*
 * VOP_L3:VOE_STAT_L3:EXTRACT_SESSION_L3.TWAMP_SEQ_NUM_RX_ERR_HMO_ENA
 *
 * \details
 * Field: ::VTSS_VOP_HMO_TIMER_CFG . HMO_TWAMP_RX_BAD_NXT_TIMER
 */
#define  VTSS_F_VOP_HMO_TIMER_CFG_HMO_TWAMP_RX_BAD_NXT_TIMER(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_HMO_TIMER_CFG_HMO_TWAMP_RX_BAD_NXT_TIMER  VTSS_BIT(0)
#define  VTSS_X_VOP_HMO_TIMER_CFG_HMO_TWAMP_RX_BAD_NXT_TIMER(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CCM SCAN Diagnostic
 *
 * \details
 * Bits in this register indicate the current status of the LOC scanning.
 *
 * Note that the following bit field is NOT sticky:
 *
 *  * LOC_SCAN_ONGOING_STATUS
 *
 * Register: \a VOP:COMMON:LOC_SCAN_STICKY
 */
#define VTSS_VOP_LOC_SCAN_STICKY             VTSS_IOREG(VTSS_TO_VOP,0x35cb)

/**
 * \brief
 * Reflects the current LOC scan mask.A bit is asserted for each of the LOC
 * counters currently being increased.NOTE: This is not a sticky bit.
 *
 * \details
 * 0: No event has occurred
 * 1: LOC scan ongoing. A bit is asserted for each LOC counter which is
 * updating the LOC MISS CNT.
 *
 * Field: ::VTSS_VOP_LOC_SCAN_STICKY . LOC_SCAN_ONGOING_STATUS
 */
#define  VTSS_F_VOP_LOC_SCAN_STICKY_LOC_SCAN_ONGOING_STATUS(x)  VTSS_ENCODE_BITFIELD(x,3,29)
#define  VTSS_M_VOP_LOC_SCAN_STICKY_LOC_SCAN_ONGOING_STATUS     VTSS_ENCODE_BITMASK(3,29)
#define  VTSS_X_VOP_LOC_SCAN_STICKY_LOC_SCAN_ONGOING_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,3,29)

/**
 * \brief
 * Asserted by VOP when LOC_SCAN completes.
 *
 * \details
 * 0: No event has occurred
 * 1: LOC scan completed
 *
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_VOP_LOC_SCAN_STICKY . LOC_SCAN_COMPLETED_STICKY
 */
#define  VTSS_F_VOP_LOC_SCAN_STICKY_LOC_SCAN_COMPLETED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_LOC_SCAN_STICKY_LOC_SCAN_COMPLETED_STICKY  VTSS_BIT(2)
#define  VTSS_X_VOP_LOC_SCAN_STICKY_LOC_SCAN_COMPLETED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Asserted by VOP when LOC_SCAN starts.
 *
 * \details
 * 0: No event has occurred
 * 1: LOC scan started
 *
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_VOP_LOC_SCAN_STICKY . LOC_SCAN_STARTED_STICKY
 */
#define  VTSS_F_VOP_LOC_SCAN_STICKY_LOC_SCAN_STARTED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_LOC_SCAN_STICKY_LOC_SCAN_STARTED_STICKY  VTSS_BIT(1)
#define  VTSS_X_VOP_LOC_SCAN_STICKY_LOC_SCAN_STARTED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Set when a LOC scan could not start because a scan is already ongoing.
 * This is an indication that a LOC timer expired before the previous scan
 * scheduled by the same LOC timer was initiated.This is an error
 * condition. To fix it, the configured Period time of the LOC scan
 * controller must be incremented.
 *
 * \details
 * 0: No event has occurred
 * 1: Scan could not start in time
 *
 * Bit is cleared by writing a 1 to this position.
 *
 * Field: ::VTSS_VOP_LOC_SCAN_STICKY . LOC_SCAN_START_DELAYED_STICKY
 */
#define  VTSS_F_VOP_LOC_SCAN_STICKY_LOC_SCAN_START_DELAYED_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_LOC_SCAN_STICKY_LOC_SCAN_START_DELAYED_STICKY  VTSS_BIT(0)
#define  VTSS_X_VOP_LOC_SCAN_STICKY_LOC_SCAN_START_DELAYED_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief VOP interrupt control.
 *
 * \details
 * This is the combined interrupt output from the VOP.
 *
 * To determine the VOE source of the interrupt, read register:
 *
 *  * VOP::INTR.VOE_INTR
 *
 * Register: \a VOP:COMMON:MASTER_INTR_CTRL
 */
#define VTSS_VOP_MASTER_INTR_CTRL            VTSS_IOREG(VTSS_TO_VOP,0x35cc)

/**
 * \brief
 * Status of the VOP interrupt to the CPU.Generation of interrupts to the
 * CPU is optional and is enabled in *
 * VOP::MASTER_INTR_CTRL.OAM_MEP_INTR_ENA
 *
 * \details
 * 0: VOP interrupt is deasserted.
 * 1: VOP interrupt is asserted.
 *
 * Field: ::VTSS_VOP_MASTER_INTR_CTRL . OAM_MEP_INTR
 */
#define  VTSS_F_VOP_MASTER_INTR_CTRL_OAM_MEP_INTR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_MASTER_INTR_CTRL_OAM_MEP_INTR  VTSS_BIT(8)
#define  VTSS_X_VOP_MASTER_INTR_CTRL_OAM_MEP_INTR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Configures if OAM_MEP_INTR causes CPU interrupts
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_MASTER_INTR_CTRL . OAM_MEP_INTR_ENA
 */
#define  VTSS_F_VOP_MASTER_INTR_CTRL_OAM_MEP_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_VOP_MASTER_INTR_CTRL_OAM_MEP_INTR_ENA  VTSS_BIT(25)
#define  VTSS_X_VOP_MASTER_INTR_CTRL_OAM_MEP_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,25,1)


/**
 * \brief One bit per 32 VOE interrupts.
 *
 * \details
 * The following register contains a bit for every VOE indicating whether
 * VOE interrupt is asserted:
 *
 *  * VOP::INTR.*
 *
 * To speed up the process of finding out which interrups are asserted,
 * this register (INTR_VOE32) contains a single bit for every 32-bit
 * register in the above register.
 * Every bit in INTR_VOE32 indicates if an interrupt is asserted in the
 * corresponding 32 bit register in VOP::INTR.*
 *
 * I.e.
 *
 * bit 0 = '1' indicates an active interrupt in VOP::INTR[0].VOE_INTR
 * bit 1 = '1' indicates an active interrupt in VOP::INTR[1].VOE_INTR
 *
 * ...
 *
 * Register: \a VOP:COMMON:VOE32_INTR
 */
#define VTSS_VOP_VOE32_INTR                  VTSS_IOREG(VTSS_TO_VOP,0x35cd)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_VOE32_INTR . VOE32_INTR
 */
#define  VTSS_F_VOP_VOE32_INTR_VOE32_INTR(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VOP_VOE32_INTR_VOE32_INTR     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VOP_VOE32_INTR_VOE32_INTR(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief VOE interrupts
 *
 * \details
 * This register contains the interrupt for each individual VOE, grouped in
 * 32 bit registers.
 *
 * The interrupts are numbered according to the VOEs:
 *
 * 0 - 31 are the Service / Path VOEs
 * 32 - 61 are the Port VOEs
 *
 * The VOE interrupts are enabled in the following registers:
 *
 * Ethernet:
 * -------------------
 *  * VOP:VOE_STAT:INTR_ENA
 *
 * MPLS-TP:
 * -----------------
 *  * VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS
 *
 * The following register indicates with a single bit if there is an
 * asserted interrupt in each of the registers in VOE_INTR
 *
 *  * VOP::VOE32_INTR
 *
 * Register: \a VOP:COMMON:INTR
 *
 * @param ri Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE_DIV32_CEIL (??), 0-1
 */
#define VTSS_VOP_INTR(ri)                    VTSS_IOREG(VTSS_TO_VOP,0x35cf + (ri))

/**
 * \brief
 * Status of interrupts per VOEEthernet:----------------------Interrupt is
 * cleared by clearing the sticky causing interrupt in
 * VOP:VOE_STAT:INTR_STICKY:* or by disabling the interrupt source in
 * VOP:VOE_STAT:INTR_ENA.*MPLS-TP:-------------------------Interrupt is
 * cleared by clearing the sticky causing interrupt in
 * VOP_MPLS:VOE_STAT_MPLS:INTR_STICKY_MPLS.* or by disabling the interrupt
 * source in VOP_MPLS:VOE_STAT_MPLS:INTR_ENA_MPLS.*
 *
 * \details
 * Each bit in the field indicates the interrupt from a single VOE.
 *
 * 0: No interrupt from VOE
 * 1: VOE has asserted the interrupt.

 *
 * Field: ::VTSS_VOP_INTR . VOE_INTR
 */
#define  VTSS_F_VOP_INTR_VOE_INTR(x)          (x)
#define  VTSS_M_VOP_INTR_VOE_INTR             0xffffffff
#define  VTSS_X_VOP_INTR_VOE_INTR(x)          (x)


/**
 * \brief VOP Multicast MAC address configuration (LSB)
 *
 * \details
 * Each VOE can be addressed using either a common Multicast MAC address or
 * a VOE specific Unicast MAC address.
 *
 * This register configures the Multicast Address common to all the VOEs.
 *
 * The full MAC address is a concatenation of the following registers:
 * 1) VOP::COMMON_MEP_MC_MAC_LSB
 * 2) VOP::COMMON_MEP_MC_MAC_MSB
 *
 * The default value of this register is determined by 802.1ag.
 *
 * The DMAC check to be performed for each VOE is configured in the
 * following bit field:
 * VOP:VOE_CONF:VOE_CTRL.RX_DMAC_CHK_SEL
 *
 * Note that only the upper 44 bits are matched, since the lower 4 bits of
 * the DMAC address contain the MEG level.
 *
 * Register: \a VOP:COMMON:COMMON_MEP_MC_MAC_LSB
 */
#define VTSS_VOP_COMMON_MEP_MC_MAC_LSB       VTSS_IOREG(VTSS_TO_VOP,0x35f2)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_COMMON_MEP_MC_MAC_LSB . MEP_MC_MAC_LSB
 */
#define  VTSS_F_VOP_COMMON_MEP_MC_MAC_LSB_MEP_MC_MAC_LSB(x)  VTSS_ENCODE_BITFIELD(x,3,28)
#define  VTSS_M_VOP_COMMON_MEP_MC_MAC_LSB_MEP_MC_MAC_LSB     VTSS_ENCODE_BITMASK(3,28)
#define  VTSS_X_VOP_COMMON_MEP_MC_MAC_LSB_MEP_MC_MAC_LSB(x)  VTSS_EXTRACT_BITFIELD(x,3,28)


/**
 * \brief VOP Multicast MAC address configuration (MSB)
 *
 * \details
 * Each VOE can be addressed using either a common Multicast MAC address or
 * a VOE specific Unicast MAC address.
 *
 * This register configures the Multicast Address common to all the VOEs.
 *
 * The full MAC address is a concatenation of the following registers:
 * 1) VOP::COMMON_MEP_MC_MAC_LSB
 * 2) VOP::COMMON_MEP_MC_MAC_MSB
 *
 * The default value of this register is determined by 802.1ag.
 *
 * The DMAC check to be performed for each VOE is configured in the
 * following bit field:
 * VOP:VOE_CONF:VOE_CTRL.RX_DMAC_CHK_SEL
 *
 * Note that only the upper 44 bits are matched, since the lower 4 bits of
 * the DMAC address contain the MEG level.
 *
 * Register: \a VOP:COMMON:COMMON_MEP_MC_MAC_MSB
 */
#define VTSS_VOP_COMMON_MEP_MC_MAC_MSB       VTSS_IOREG(VTSS_TO_VOP,0x35f3)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_COMMON_MEP_MC_MAC_MSB . MEP_MC_MAC_MSB
 */
#define  VTSS_F_VOP_COMMON_MEP_MC_MAC_MSB_MEP_MC_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_COMMON_MEP_MC_MAC_MSB_MEP_MC_MAC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_COMMON_MEP_MC_MAC_MSB_MEP_MC_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Loss Of Continuity Controller base tick configuration
 *
 * \details
 * Configures LOC Controller base tick value

 *
 * Register: \a VOP:COMMON:LOC_CTRL_2
 */
#define VTSS_VOP_LOC_CTRL_2                  VTSS_IOREG(VTSS_TO_VOP,0x35f4)

/**
 * \brief
 * Specifies the number of system clock cycles for each LOC base time
 * tick.The base tick, is the event used for incrementing the 27 LOC
 * counters. The time at which each of the LOC timers will timeout is
 * specified in:  * VOP::LOC_PERIOD_CFG::LOC_PERIOD_VALEthernet
 * VOEs:------------------------When a LOC timer expires it causes a LOC
 * Scan event, which will increment the CCM miss counter
 * (VOP:VOE_STAT:CCM_STAT.CCM_MISS_CNT) for each VOE assigned to that
 * particular LOC timer.The CCM miss counter for each VOE (CCM_MISS_CNT)
 * will be cleared each time the VOE receives a valid CCM or CCM-LM
 * frame.If the CCM_MISS count reaches 7 it will optionally cause an
 * interrupt.MPLS-TP VOEs:------------------------When a LOC timer expires
 * it causes a LOC Scan event, which will increment the BFD miss counter
 * (VOP_MPLS:VOE_STAT_MPLS:BFD_STAT.BFD_MISS_CNT) for each VOE assigned to
 * that particular LOC timer.The LOC counter for each VOE (BFD_MISS_CNT)
 * will be cleared each time the VOE receives a valid BFD-CC or BFD-CV
 * PDU.If the BFD_MISS_CNT count reaches the configured Detect Multiplier
 * it will optionally cause an interrupt.
 *
 * \details
 * 0: Illegal value
 * 1: One clock between interval increment
 * ...
 * n: n clock between interval increment
 *
 * Field: ::VTSS_VOP_LOC_CTRL_2 . LOC_BASE_TICK_CNT
 */
#define  VTSS_F_VOP_LOC_CTRL_2_LOC_BASE_TICK_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VOP_LOC_CTRL_2_LOC_BASE_TICK_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VOP_LOC_CTRL_2_LOC_BASE_TICK_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Configuration for CPU-copied MRP frames
 *
 * \details
 * Register: \a VOP:COMMON:CPU_EXTR_MRP
 */
#define VTSS_VOP_CPU_EXTR_MRP                VTSS_IOREG(VTSS_TO_VOP,0x35f5)

/**
 * \brief
 * CPU queue used by MRP_Test frames with MRP_SA from remote MRM or by
 * MRP_InTest frames with MRP_SA from remote MIM.Related paramenters:-
 * VOP_MRP:VOE_CONF_MRP:TST_FWD_CTRL.REM_FWD_SEL-
 * VOP_MRP:VOE_CONF_MRP:ITST_FWD_CTRL.ITST_REM_FWD_SEL.
 *
 * \details
 * Field: ::VTSS_VOP_CPU_EXTR_MRP . REM_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_MRP_REM_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,18,3)
#define  VTSS_M_VOP_CPU_EXTR_MRP_REM_CPU_QU     VTSS_ENCODE_BITMASK(18,3)
#define  VTSS_X_VOP_CPU_EXTR_MRP_REM_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,18,3)

/**
 * \brief
 * CPU queue used by MRP_Test or MRP_InTest frames with MRP_SA from
 * itself.Related paramenters:-
 * VOP_MRP:VOE_CONF_MRP:TST_FWD_CTRL.OWN_FWD_SEL-
 * VOP_MRP:VOE_CONF_MRP:ITST_FWD_CTRL.ITST_OWN_FWD_SEL.
 *
 * \details
 * Field: ::VTSS_VOP_CPU_EXTR_MRP . OWN_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_MRP_OWN_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_VOP_CPU_EXTR_MRP_OWN_CPU_QU     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_VOP_CPU_EXTR_MRP_OWN_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * CPU queue used by VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL.OTHER_FWD_SEL.
 *
 * \details
 * Field: ::VTSS_VOP_CPU_EXTR_MRP . MRP_OTHER_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_MRP_MRP_OTHER_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_VOP_CPU_EXTR_MRP_MRP_OTHER_CPU_QU     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_VOP_CPU_EXTR_MRP_MRP_OTHER_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * CPU queue used by frames with MC_TEST MAC address.Related paramenters:-
 * VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL
 *
 * \details
 * Field: ::VTSS_VOP_CPU_EXTR_MRP . MRP_TST_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_MRP_MRP_TST_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_VOP_CPU_EXTR_MRP_MRP_TST_CPU_QU     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_VOP_CPU_EXTR_MRP_MRP_TST_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * CPU queue used by frames with MC_CONTROL MAC address.Related
 * paramenters:- VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL
 *
 * \details
 * Field: ::VTSS_VOP_CPU_EXTR_MRP . MRP_CTRL_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_MRP_MRP_CTRL_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VOP_CPU_EXTR_MRP_MRP_CTRL_CPU_QU     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VOP_CPU_EXTR_MRP_MRP_CTRL_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * CPU queue used by frames with MC_INTEST MAC address.Related
 * paramenters:- VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL
 *
 * \details
 * Field: ::VTSS_VOP_CPU_EXTR_MRP . MRP_ITST_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_MRP_MRP_ITST_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CPU_EXTR_MRP_MRP_ITST_CPU_QU     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CPU_EXTR_MRP_MRP_ITST_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * CPU queue used by frames with MC_INCONTROL MAC address.Related
 * paramenters:- VOP_MRP:VOE_CONF_MRP:MRP_FWD_CTRL
 *
 * \details
 * Field: ::VTSS_VOP_CPU_EXTR_MRP . MRP_ICTRL_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_MRP_MRP_ICTRL_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CPU_EXTR_MRP_MRP_ICTRL_CPU_QU     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CPU_EXTR_MRP_MRP_ICTRL_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Configuration for CPU-copied DLR frames
 *
 * \details
 * Register: \a VOP:COMMON:CPU_EXTR_DLR
 */
#define VTSS_VOP_CPU_EXTR_DLR                VTSS_IOREG(VTSS_TO_VOP,0x35f6)

/**
 * \brief
 * CPU queue used by Beacon/Advertise frames from new ring
 * surpervisor/gateway.Related paramenters:-
 * VOP_DLR:VOE_CONF_DLR:BCN_FWD_CTRL.HI_PRIO_FWD_SEL-
 * VOP_DLR:VOE_CONF_DLR:BCN_FWD_CTRL.LO_PRIO_FWD_SEL-
 * VOP_DLR:VOE_CONF_DLR:ADV_FWD_CTRL.GW_HI_PRIO_FWD_SEL
 *
 * \details
 * Field: ::VTSS_VOP_CPU_EXTR_DLR . NEW_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_DLR_NEW_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_VOP_CPU_EXTR_DLR_NEW_CPU_QU     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_VOP_CPU_EXTR_DLR_NEW_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * CPU queue used by Beacon/Advertise frames from active ring
 * surpervisor/gateway.Related paramenters:-
 * VOP_DLR:VOE_CONF_DLR:BCN_FWD_CTRL.ACT_FWD_SEL-
 * VOP_DLR:VOE_CONF_DLR:BCN_FWD_CTRL.ACT_FAULT_FWD_SEL-
 * VOP_DLR:VOE_CONF_DLR:ADV_FWD_CTRL.GW_FWD_SEL
 *
 * \details
 * Field: ::VTSS_VOP_CPU_EXTR_DLR . ACT_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_DLR_ACT_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_VOP_CPU_EXTR_DLR_ACT_CPU_QU     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_VOP_CPU_EXTR_DLR_ACT_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * CPU queue used by VOP_DLR:VOE_CONF_DLR:DLR_FWD_CTRL.DLR_ADV_FWD_SEL.
 *
 * \details
 * Field: ::VTSS_VOP_CPU_EXTR_DLR . DLR_ADV_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_DLR_DLR_ADV_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VOP_CPU_EXTR_DLR_DLR_ADV_CPU_QU     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VOP_CPU_EXTR_DLR_DLR_ADV_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * CPU queue used by VOP_DLR:VOE_CONF_DLR:DLR_FWD_CTRL.DLR_BCN_FWD_SEL.
 *
 * \details
 * Field: ::VTSS_VOP_CPU_EXTR_DLR . DLR_BCN_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_DLR_DLR_BCN_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CPU_EXTR_DLR_DLR_BCN_CPU_QU     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CPU_EXTR_DLR_DLR_BCN_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * CPU queue used by VOP_DLR:VOE_CONF_DLR:DLR_FWD_CTRL for non-Beacon and
 * non-Advertise DLR frames
 *
 * \details
 * Field: ::VTSS_VOP_CPU_EXTR_DLR . DLR_OTHER_CPU_QU
 */
#define  VTSS_F_VOP_CPU_EXTR_DLR_DLR_OTHER_CPU_QU(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CPU_EXTR_DLR_DLR_OTHER_CPU_QU     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CPU_EXTR_DLR_DLR_OTHER_CPU_QU(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Configuration of MRP time stamp granularity
 *
 * \details
 * Configuration of MRP time stamp granularity.
 *
 * Register: \a VOP:COMMON:TICK_CFG
 */
#define VTSS_VOP_TICK_CFG                    VTSS_IOREG(VTSS_TO_VOP,0x35f7)

/**
 * \brief
 * Base tick count to 1ms.
 *
 * \details
 * Field: ::VTSS_VOP_TICK_CFG . TICK_CNT
 */
#define  VTSS_F_VOP_TICK_CFG_TICK_CNT(x)      VTSS_ENCODE_BITFIELD(x,0,19)
#define  VTSS_M_VOP_TICK_CFG_TICK_CNT         VTSS_ENCODE_BITMASK(0,19)
#define  VTSS_X_VOP_TICK_CFG_TICK_CNT(x)      VTSS_EXTRACT_BITFIELD(x,0,19)


/**
 * \brief Configuration of MRP time stamp
 *
 * \details
 * Configuration of MRP time stamp.
 *
 * Register: \a VOP:COMMON:MRP_TS_CFG
 */
#define VTSS_VOP_MRP_TS_CFG                  VTSS_IOREG(VTSS_TO_VOP,0x35f8)

/**
 * \brief
 * Current time in ms. Value increments every 1 ms.
 *
 * \details
 * Field: ::VTSS_VOP_MRP_TS_CFG . MRP_TS
 */
#define  VTSS_F_VOP_MRP_TS_CFG_MRP_TS(x)      (x)
#define  VTSS_M_VOP_MRP_TS_CFG_MRP_TS         0xffffffff
#define  VTSS_X_VOP_MRP_TS_CFG_MRP_TS(x)      (x)

/**
 * Register Group: \a VOP:VOE_CONF_REG
 *
 * VOE configuration registers
 */


/**
 * \brief Miscellaneous per VOE configuration
 *
 * \details
 * Miscellaneous per VOE configuration.
 *
 * Register: \a VOP:VOE_CONF_REG:VOE_MISC_CONFIG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_VOE_MISC_CONFIG(gi)         VTSS_IOREG_IX(VTSS_TO_VOP,0x34c0,gi,1,0,0)

/**
 * \brief
 * Enables VOE functionality.When the VOE is not enabled, it will not do
 * any OAM processing or update statistics.The VOE will process either
 * Y.1731, MPLS, L3 OAM PDUs, MRP PDUs or DLR PDUs depending on the
 * configuration of this register.The VOE can be configured while not
 * enabled.
 *
 * \details
 * Field: ::VTSS_VOP_VOE_MISC_CONFIG . VOE_ENA
 */
#define  VTSS_F_VOP_VOE_MISC_CONFIG_VOE_ENA(x)  VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_VOP_VOE_MISC_CONFIG_VOE_ENA     VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_VOP_VOE_MISC_CONFIG_VOE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * If this field is asserted, the VOE will count bytes instead of
 * frames.This is not 100% supported and tested.Feature is only available
 * for Service / Path VOEs.Byte count is disabled for Port VOEs.
 *
 * \details
 * Field: ::VTSS_VOP_VOE_MISC_CONFIG . LM_CNT_BYTE
 */
#define  VTSS_F_VOP_VOE_MISC_CONFIG_LM_CNT_BYTE(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_VOE_MISC_CONFIG_LM_CNT_BYTE  VTSS_BIT(3)
#define  VTSS_X_VOP_VOE_MISC_CONFIG_LM_CNT_BYTE(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable the VOE for Synthetic Loss Measurements.If enabled, the normal LM
 * counters are used differently than when running standard frame loss
 * measurements.Synthetic Loss Measurement can either be  run against a
 * single peer with counters per COSIDs or against multiple peers with one
 * counter per peer. This is controlled by *
 * VOP:VOE_CONF:SLM_PEER_LIST.SLM_PEER_ENAIf a single Peer MEP is enabled:-
 * The Rx LM counters are used to count SLR/1SL frames received from the
 * Peer MEP per COSID.- The Tx LM counters are used to count SLR frames
 * transmitted to the Peer MEP per COSID.If multiple Peer MEPs are
 * enabled:- The Rx LM counters are used to count SLR/1SL frames received
 * from different Peer MEPs.- The Tx LM counters are used to count SLR
 * frames transmitted to different Peer MEPs.- LM counters count only a
 * selected COSID, which is selected by *
 * VOP:VOE_CONF:SLM_CONFIG.SLM_PRIOTransmitted SLM/1SL frames are counted
 * in * VOP:VOE_STAT:SLM_TX_FRM_CNT.SLM_TX_FRM_CNTNote that there is no
 * counting of data frames or other non-SL OAM PDUs.Asserting this register
 * will avoid any other VOEs from updating the LM counters of this VOE as
 * part of a hierarchical LM counter update.
 *
 * \details
 * Field: ::VTSS_VOP_VOE_MISC_CONFIG . SL_ENA
 */
#define  VTSS_F_VOP_VOE_MISC_CONFIG_SL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_VOE_MISC_CONFIG_SL_ENA    VTSS_BIT(2)
#define  VTSS_X_VOP_VOE_MISC_CONFIG_SL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Puts VOE into client and/or server blocking state. When in a blocking
 * state, frames are blocked in both Rx and Tx directions.Server layer
 * blocking corresponds to G.8021 aBLK.Server layer blocking in the Tx
 * direction of a processing VOE: - The VOE will block all client layer
 * data. - The VOE will block CSF OAM frames. - The VOE will optionally
 * block frames with selected generic OAM PDU types, depending on the
 * configuration of   * VOP:COMMON:OAM_GENERIC_CFG.GENERIC_BLK_SERVER_ENA -
 * Frames blocked by this functionality will not be counted as part of the
 * LM Tx counters. - Frames injected into the VOE are subject to the server
 * blocking listed above.Server layer blocking in the Rx direction of a
 * processing VOE: - The VOE will block all client layer data. - The VOE
 * will block CSF OAM frames. - The VOE will optionally block frames with
 * selected generic OAM PDU types, depending on the configuration of   *
 * VOP:COMMON:OAM_GENERIC_CFG.GENERIC_BLK_SERVER_ENA - Frames blocked by
 * this functionality will be counted as part of the LM Rx counters.Server
 * layer blocking in a nested VOE in the blocking hierarchy: - The VOE will
 * block all Rx and Tx frames going through the VOE.Client layer blocking
 * corresponds to G.8021 MI_Admin_State (LOCK).Client layer blocking in the
 * Tx direction of a processing VOE: - The VOE will block all Tx frames not
 * blocked by MEL filtering in the VOE. - This blocking will not interfere
 * with OAM PDUs processed or MEL filtered by the VOE, but it will block
 * all service frames in the Tx direction. - This blocking will not
 * interfere with OAM LCK PDUs injected into the client flows. - Frames
 * blocked by this functionality will not be counted as part of the LM Tx
 * counters.Client layer blocking in the Rx direction of a processing VOE:
 * - The VOE will block all Rx frames not processed or blocked by MEL
 * filtering in the VOE. - This blocking will not interfere with OAM PDUs
 * processed or MEL filtered by the VOE, but it will block all service
 * frames in the Rx direction. - Frames blocked by this functionality will
 * be counted as part of the LM Rx counters. - OAM PDUs injected into the
 * client flows in the Rx direction will be blocked, except for LCK frames.
 * - OAM PDUs injected into the client flows in the Rx direction with
 * selected generic OAM PDU types will be blocked, depending on the
 * configuration of   *
 * VOP:COMMON:OAM_GENERIC_CFG.GENERIC_BLK_CLIENT_ENA.Client layer blocking
 * in a nested VOE in the blocking hierarchy: - The VOE will block all Rx
 * and Tx frames going through the VOE.Blocking in evaluated hirarchically,
 * meaning:- Data hitting a Service VOE is blocked if either	the Service
 * VOE itself is blocking,    the Service VOE has a Path VOE enabled
 * (VOP::VOE_COMMON_CFG.PATH_VOE_ENA, VOP::VOE_COMMON_CFG.PATH_VOEID),
 * which is blocking, or    the Port VOE is blocking.- Data hitting a Path
 * VOE is blocked if either    the Path VOE itself is blocking, or    the
 * Port VOE is blocking.- Data hitting a Port VOE is blocked if    the Port
 * VOE itself is blocking.OAM frames processed by the VOE, which are
 * discarded by blocking, will counted in the following counters: *
 * VOP:VOE_STAT:TX_OAM_DISCARD.TX_FRM_DISCARD_CNT *
 * VOP:VOE_STAT:RX_OAM_DISCARD.RX_FRM_DISCARD_CNT
 *
 * \details
 * "00": The VOE is not blocking.
 * "01": The VOE is in the client layer blocking state (LOCK).
 * "10": The VOE is in the server layer blocking state (aBLK).
 * "11": The VOE is in both client layer state and server layer blocking
 * state.
 *
 * Field: ::VTSS_VOP_VOE_MISC_CONFIG . BLK_ENA
 */
#define  VTSS_F_VOP_VOE_MISC_CONFIG_BLK_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VOP_VOE_MISC_CONFIG_BLK_ENA     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VOP_VOE_MISC_CONFIG_BLK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a VOP:VOE_CONF
 *
 * Configuration per Versatile OAM MEP Endpoints (VOE) for Y.1731 OAM
 */


/**
 * \brief VOE configuration common between VOE types
 *
 * \details
 * This register is identical in VOE_CONF, VOE_CONF_MPLS, and VOE_CONF_L3.
 *
 * Register: \a VOP:VOE_CONF:VOE_COMMON_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_VOE_COMMON_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,0)

/**
 * \brief
 * Configures VOE for Down-MEP or Up-MEP operation.Note:Port VOEs only
 * support Down-MEP functionality. UPMEP_ENA must be set to 0.L3 VOEs only
 * support Up-MEP functionality. UPMEP_ENA must be set to 1.
 *
 * \details
 * 0: Configure VOE for Down-MEP functionality.
 * 1: Configure VOE for Up-MEP functionality.
 *
 * Field: ::VTSS_VOP_VOE_COMMON_CFG . UPMEP_ENA
 */
#define  VTSS_F_VOP_VOE_COMMON_CFG_UPMEP_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_VOE_COMMON_CFG_UPMEP_ENA  VTSS_BIT(13)
#define  VTSS_X_VOP_VOE_COMMON_CFG_UPMEP_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * If another VOE is pointing to this VOE as a Path VOE using the following
 * configuration: * PATH_VOEID * PATH_VOE_ENAthis register MUST be set to
 * '1'.If not this register must be set to '0'.
 *
 * \details
 * '0': This VOE is not configured as PATH VOE in another VOE.
 * '1': This VOE is configured as PATH VOE in another VOE.
 *
 * Field: ::VTSS_VOP_VOE_COMMON_CFG . VOE_IS_PATH
 */
#define  VTSS_F_VOP_VOE_COMMON_CFG_VOE_IS_PATH(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_VOE_COMMON_CFG_VOE_IS_PATH  VTSS_BIT(12)
#define  VTSS_X_VOP_VOE_COMMON_CFG_VOE_IS_PATH(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * The VOE supports hierarchical LM counting.This implies that when a VOE
 * is processing a frame, it can update the LM counter of the VOE
 * configured at the Server Layer, if a Server Layer exists.Within the
 * scope of the register list, a VOE configured at the Server Layer is
 * referred to as Path VOE.This register is used to assign a Path VOE to
 * the current service VOE.Port VOEs are considered as Server Layer VOEs
 * per default, and can not be assigned at Path VOEs.Assigning a Path VOE
 * to the VOE implies that all frames received by this VOE, will also be
 * counted by the Path VOE indicated by the following register: *
 * PATH_VOEIDThe path VOE must be enabled by asserting the following field:
 *  * PATH_VOE_ENANote, that the VOE assigned as Path VOP must be enabled
 * for Path VOE operation: * VOE_IS_PATH
 *
 * \details
 * Field: ::VTSS_VOP_VOE_COMMON_CFG . PATH_VOE_ENA
 */
#define  VTSS_F_VOP_VOE_COMMON_CFG_PATH_VOE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_VOE_COMMON_CFG_PATH_VOE_ENA  VTSS_BIT(11)
#define  VTSS_X_VOP_VOE_COMMON_CFG_PATH_VOE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Assigns a Path VOE to the VOE. See description in PATH_VOE_ENA.Must
 * point to a VOE in the pool of Service VOEs (0 - 31).
 *
 * \details
 * Field: ::VTSS_VOP_VOE_COMMON_CFG . PATH_VOEID
 */
#define  VTSS_F_VOP_VOE_COMMON_CFG_PATH_VOEID(x)  VTSS_ENCODE_BITFIELD(x,1,5)
#define  VTSS_M_VOP_VOE_COMMON_CFG_PATH_VOEID     VTSS_ENCODE_BITMASK(1,5)
#define  VTSS_X_VOP_VOE_COMMON_CFG_PATH_VOEID(x)  VTSS_EXTRACT_BITFIELD(x,1,5)

/**
 * \brief
 * If ESDX counter control is enabled, the VOP will signal disabling of
 * ESDX counting to the REW for OAM frames.This ESDX_CNT_CTRL_ENA field is
 * intended for Subscriber Up-MEPs that are intended to count frames going
 * into the EVC after policing. In this case, SAT_TEST_VOE cannot be
 * enabled, since that would cause the MEP to count frames prior to
 * policing.Note, that for a Y.1731 VOE enabled for SAT test in  *
 * VOP:VOE_CONF:VOE_CTRL.SAT_TEST_VOEESDX counting will be performed for
 * all frames, independently of the value of this field.
 *
 * \details
 * Field: ::VTSS_VOP_VOE_COMMON_CFG . ESDX_CNT_CTRL_ENA
 */
#define  VTSS_F_VOP_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_VOE_COMMON_CFG_ESDX_CNT_CTRL_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Misc. VOE control configuration
 *
 * \details
 * This register includes configuration of misc. VOE properties.
 *
 * Register: \a VOP:VOE_CONF:VOE_CTRL
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_VOE_CTRL(gi)                VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,1)

/**
 * \brief
 * This register configures the MEL value for the VOE, used for Y.1731 MEL
 * filtering.PDUs passing the VOE with MEL above this MEL_VAL will be
 * treated as data.PDUs passing the VOE with MEL below this MEL_VAL will be
 * discarded.PDUs passing the VOE with MEL equal to this MEL_VAL are
 * optionally processed by the VOE / copied to CPU. The processing of OAM
 * PDUs with a MEL value equal to the VOE MEL_VAL depends on the following:
 * * If the PDU was inserted by the CPU * If the PDU type is enabled for
 * processing by the VOE * If the PDU is received on the Active or Passive
 * side of the VOE.
 *
 * \details
 * Field: ::VTSS_VOP_VOE_CTRL . MEL_VAL
 */
#define  VTSS_F_VOP_VOE_CTRL_MEL_VAL(x)       VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_VOP_VOE_CTRL_MEL_VAL          VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_VOP_VOE_CTRL_MEL_VAL(x)       VTSS_EXTRACT_BITFIELD(x,7,3)

/**
 * \brief
 * Assert to configure the VOE for G.8113.1 MPLS OAM.When the VOE is
 * enabled for G.8113.1 it will support : - Verifying the LBM / LBR MEP ID
 * TLVs - Disabling the MEL CHECKWhen the VOE is enabled for G.8113.1 it
 * will NOT support: - Validation of TST TLVs for Rx LBR / TST PDUsWhen the
 * VOE is configured for G.8113.1 the blocking of Rx OAM PDUs with MEL HIGH
 * should always be enabled: * VOP:VOE_CONF:VOE_CTRL.BLOCK_MEL_HIGH_RX
 *
 * \details
 * 0: VOE processes according to Y.1731 (Ethernet OAM)
 * 1: VOE processes according to G.8113.1 (MPLS OAM)
 *
 * Field: ::VTSS_VOP_VOE_CTRL . G_8113_1_ENA
 */
#define  VTSS_F_VOP_VOE_CTRL_G_8113_1_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_VOE_CTRL_G_8113_1_ENA     VTSS_BIT(6)
#define  VTSS_X_VOP_VOE_CTRL_G_8113_1_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Configures the DMAC check performed when received from the peer MEP.This
 * check can be disabled for Generic OpCodes. See
 * VOP::OAM_GENERIC_CFG.GENERIC_DMAC_CHK_DISIn case of MPLS-TP encapsulated
 * frames, the check is performed on the Customer DMAC (Inner DMAC)If DMAC
 * check fails, the frame is discarded.The following sticky bit is asserted
 * when the VOE receives an OAM PDU which fails the DMAC check: *
 * VOP:VOE_STAT:OAM_RX_STICKY.DMAC_RX_ERR_STICKY
 *
 * \details
 * VOE configured as MEP:
 * 0: No DMAC check
 * 1: Check DMAC against MEP_UC_MAC_MSB and MEP_UC_MAC_LSB
 * 2: Check DMAC against MEP_MC_MAC_MSB and MEP_MC_MAC_LSB
 * 3: Check DMAC against either MEP_UC_MAC_MSB and MEP_UC_MAC_LSB or
 * MEP_MC_MAC_MSB and MEP_MC_MAC_LSB
 *
 * Field: ::VTSS_VOP_VOE_CTRL . RX_DMAC_CHK_SEL
 */
#define  VTSS_F_VOP_VOE_CTRL_RX_DMAC_CHK_SEL(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VOP_VOE_CTRL_RX_DMAC_CHK_SEL     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VOP_VOE_CTRL_RX_DMAC_CHK_SEL(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \brief
 * On reception of an OAM PDU in the Rx direction, the VOE will verify that
 * the Y.1731 version number in the OAM PDU header is valid according to
 * the configured valid versions:- VOP::VERSION_CTRL.*-
 * VOP::VERSION_CTRL_2.*- VOP::VERSION_CTRL_3.*The VERSION is verified for
 * all but GENERIC and UNKNOWN PDUs, since these are not processed by the
 * VOE.This bit field can disable the VERSION verification as part of the
 * Rx verification.If the VERSION verification fails, the following sticky
 * bit is asserted: *
 * VOP:VOE_STAT:OAM_RX_STICKY.PDU_VERSION_RX_ERR_STICKYOAM PDUs which fail
 * the version check can optionally be extracted using the following
 * configuration bit: * VOP:VOE_STAT:PDU_EXTRACT.PDU_VERSION_RX_ERR_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_VOE_CTRL . VERIFY_VERSION_ENA
 */
#define  VTSS_F_VOP_VOE_CTRL_VERIFY_VERSION_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_VOE_CTRL_VERIFY_VERSION_ENA  VTSS_BIT(3)
#define  VTSS_X_VOP_VOE_CTRL_VERIFY_VERSION_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * When asserted, the VOE will assume that an external device updates the
 * time stamp information in Y.1731 Delay Measurement PDUs (DMM / DMR /
 * 1DM) and in non-OAM PDUs enabled for time stamping (SAM_SEQ).Hence the
 * VOE will not update the DM PDUs and SAM_SEQ PDUs with TS information.The
 * VOE will however, still extract and loop DM PDUs and SAM_SEQ PDUs
 * according to VOE configuration.
 *
 * \details
 * Field: ::VTSS_VOP_VOE_CTRL . EXTERN_DM_TSTAMP
 */
#define  VTSS_F_VOP_VOE_CTRL_EXTERN_DM_TSTAMP(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_VOE_CTRL_EXTERN_DM_TSTAMP  VTSS_BIT(2)
#define  VTSS_X_VOP_VOE_CTRL_EXTERN_DM_TSTAMP(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * When asserted, the VOE will block Y.1731 PDUs with MEL higher than the
 * configured MEP MEL in the Rx direction.This can be used to terminate
 * higher MEL frames when the VOE is located at the border of a MEG
 * domain.This bit should always be enabled when the VOE is configured for
 * G.8113.1 - VOP:VOE_CONF:VOE_CTRL.G_8113_1_ENA
 *
 * \details
 * 0: Allow Rx PDUs with MEL HIGH to pass the VOE.
 * 1: Block Rx PDUs with MEL HIGH to pass the VOE.
 *
 * Field: ::VTSS_VOP_VOE_CTRL . BLOCK_MEL_HIGH_RX
 */
#define  VTSS_F_VOP_VOE_CTRL_BLOCK_MEL_HIGH_RX(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_VOE_CTRL_BLOCK_MEL_HIGH_RX  VTSS_BIT(1)
#define  VTSS_X_VOP_VOE_CTRL_BLOCK_MEL_HIGH_RX(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Configure the current VOE to be used as a subscriber SAT test VOE which
 * uses ihf.iprio as the VOE priority domain instead of COSID.When the VOE
 * is used as a subscriber SAT test VOE, the OAM frames being processed by
 * the VOE is counted in the egress statistics, which is not the default
 * VOE behavior.
 *
 * \details
 * 0: Configure as standard VOE.
 * 1: Configure as a subscriber SAT test VOE.
 *
 * Field: ::VTSS_VOP_VOE_CTRL . SAT_TEST_VOE
 */
#define  VTSS_F_VOP_VOE_CTRL_SAT_TEST_VOE(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_VOE_CTRL_SAT_TEST_VOE     VTSS_BIT(0)
#define  VTSS_X_VOP_VOE_CTRL_SAT_TEST_VOE(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief VOE MEPID
 *
 * \details
 * The MEPID of the VOE.
 *
 * This is currently only used for SLM and LBM / LBR TLV verification
 * (G.8113.1 only).
 *
 * Register: \a VOP:VOE_CONF:VOE_MEPID_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_VOE_MEPID_CFG(gi)           VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,2)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_VOE_MEPID_CFG . VOE_MEPID
 */
#define  VTSS_F_VOP_VOE_MEPID_CFG_VOE_MEPID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_VOE_MEPID_CFG_VOE_MEPID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_VOE_MEPID_CFG_VOE_MEPID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Configuration of CCM MEPID
 *
 * \details
 * Configures 16 bit MEP ID of the peer MEP.
 *
 *
 * This value is used for two purposes:
 *
 * CCM(-LM):
 * --------------------------
 * This value is verified against incoming CCM(-LM) frames.
 *
 * In case MEP ID verification is enabled
 * (VOP:VOE_CONF:CCM_CFG.CCM_MEPID_CHK_ENA = 1) the value of the CCM.MEPID
 * field of incoming CCM/CCM-LM frames will be verified against the value
 * configured in this register.
 *
 * If there is a mismatch, the following bit will be asserted:
 *
 *  * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_MEPID_DEFECT
 *
 * When the above bit changes value, the VOE optionally generates an
 * interrupt.
 *
 * LBM / LBR TLV verification (G.8113.1 OAM)
 * -----------------------------------------------------------------------
 * The peer MEP ID is used to verify the MEP ID contained in the Rx
 * LBM'Target MEP / MIP ID' / LBR 'Replying MEP / MIP ID TLV.
 *
 * Register: \a VOP:VOE_CONF:PEER_MEPID_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_PEER_MEPID_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,3)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_PEER_MEPID_CFG . PEER_MEPID
 */
#define  VTSS_F_VOP_PEER_MEPID_CFG_PEER_MEPID(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_PEER_MEPID_CFG_PEER_MEPID     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_PEER_MEPID_CFG_PEER_MEPID(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief SAM per COSID sequence numbering
 *
 * \details
 * As per default, the VOE will use a single sequence number across all
 * COSIDs for each of the following PDU types:
 *
 *  * CCM
 *  * LBM/LBR, TST or SAM_SEQ (mutually exclusive)
 *
 * Additionally the VOP includes 32 counter sets which can be used for SAM
 * per COSID sequence numbering of the following PDU types:
 *
 *  * CCM
 *  * LBM/LBR, TST or SAM_SEQ (mutually exclusive)
 *
 * This register is used to configure the VOE for per COSID sequence
 * numbering by assigning one of the SAM per COSID counter sets to the VOE.
 *
 * The per COSID sequence numbering is implemented by using the
 * corresponding register in the VOE to count priority 7, while the
 * remaining priorities (0-6) are counted using a dedicated RAM.
 *
 * The SAM per COSID counters (prio: 0 - 6) are located in:
 *  * VOP:SAM_COSID_SEQ_CNT
 *
 * NOTE: The appointed per COSID counter set can be used for either
 * LBM/LBR/TST or CCM, hence only one of the below registers may be
 * asserted.
 *
 *  * PER_COSID_LBM
 *  * PER_COSID_CCM
 *
 * Asserting both is a misconfiguration.
 *
 * When per COSID sequence numbering is enabled, the VOE will use the
 * counter set configured in:
 *
 *  * PER_COSID_CNT_SET
 *
 * Register: \a VOP:VOE_CONF:SAM_COSID_SEQ_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_SAM_COSID_SEQ_CFG(gi)       VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,4)

/**
 * \brief
 * Enable SAM per COSID sequence numbering for the following PDUs * TST *
 * LBM/LBR * non OAM sequence numbering (see
 * VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG.*)Note that the above PDUs are mutually
 * exclusive.This bit field MUST not be asserted at the same time as:
 * PER_COSID_CCMWhen SAM per COSID sequence numbering is enabled, the VOE
 * will use the SAM counter set configured in: * PER_COSID_CNT_SET
 *
 * \details
 * Field: ::VTSS_VOP_SAM_COSID_SEQ_CFG . PER_COSID_LBM
 */
#define  VTSS_F_VOP_SAM_COSID_SEQ_CFG_PER_COSID_LBM(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_SAM_COSID_SEQ_CFG_PER_COSID_LBM  VTSS_BIT(6)
#define  VTSS_X_VOP_SAM_COSID_SEQ_CFG_PER_COSID_LBM(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enable SAM per COSID sequence numbering for the following PDUs *
 * CCM(-LM)This bit field MUST not be asserted at the same time as:
 * PER_COSID_LBMWhen SAM per COSID sequence numbering is enabled, the VOE
 * will use the SAM counter set configured in: * PER_COSID_CNT_SET
 *
 * \details
 * Field: ::VTSS_VOP_SAM_COSID_SEQ_CFG . PER_COSID_CCM
 */
#define  VTSS_F_VOP_SAM_COSID_SEQ_CFG_PER_COSID_CCM(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_SAM_COSID_SEQ_CFG_PER_COSID_CCM  VTSS_BIT(5)
#define  VTSS_X_VOP_SAM_COSID_SEQ_CFG_PER_COSID_CCM(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * When per COSID sequence numbering is enabled by asserting one of the
 * following bitfields, this register selects which of the per COSID
 * counter sets will be used for per COSID statistics.Per COSID sequence
 * numbering is enabled by asserting one of the following bit fields: *
 * PER_COSID_LBM * PER_COSID_CCMCounters are located in CSR register group:
 * * VOP:SAM_COSID_SEQ_CNT:*
 *
 * \details
 * Field: ::VTSS_VOP_SAM_COSID_SEQ_CFG . PER_COSID_CNT_SET
 */
#define  VTSS_F_VOP_SAM_COSID_SEQ_CFG_PER_COSID_CNT_SET(x)  VTSS_ENCODE_BITFIELD(x,0,5)
#define  VTSS_M_VOP_SAM_COSID_SEQ_CFG_PER_COSID_CNT_SET     VTSS_ENCODE_BITMASK(0,5)
#define  VTSS_X_VOP_SAM_COSID_SEQ_CFG_PER_COSID_CNT_SET(x)  VTSS_EXTRACT_BITFIELD(x,0,5)


/**
 * \brief Support for SAM sequence numbering of non-OAM frames
 *
 * \details
 * The VOE can be configured to support sequence numbering and/or time
 * stamping of non OAM frames.
 * This can be used for testing as specified in SAM or RFC2544 etc.
 *
 * This functionality is referred to as SAM_SEQ.
 *
 * Note that the configuring support for sequence numbering of non-OAM
 * frames excludes the use of the following PDU types for this VOE:
 *  * TST
 *  * LBM
 *  * LBR
 *
 * This is because the statistics used to support non-OAM sequence
 * numbering re-uses the registers otherwise used for processing the above
 * PDUs.
 *
 * Sequence numbering is enabled by
 *
 *  * VOP:VOE_CONF:OAM_HW_CTRL.LBR_ENA
 *  * VOP:VOE_CONF:TX_TRANSID_UPDATE.LBM_UPDATE_ENA
 *  * VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG.SAM_SEQ_FORMAT_SEQ_NO (must be set
 * to 0 to disable sequence numbering)
 *
 * Timestamping is enabled by
 *
 *  * VOP:VOE_CONF:OAM_HW_CTRL.LBR_ENA
 *  * VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG.SAM_SEQ_TS_ENA
 *
 * Register: \a VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_SAM_NON_OAM_SEQ_CFG(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,5)

/**
 * \brief
 * Asserting this bit will configure the VOE as initiator of non-OAM frames
 * with sequence number and/or time stamps (SAM_SEQ).This must NOT be
 * asserted at the same time as asserting: * SAM_SEQ_RESP = 1
 *
 * \details
 * Field: ::VTSS_VOP_SAM_NON_OAM_SEQ_CFG . SAM_SEQ_INIT
 */
#define  VTSS_F_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_INIT(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_INIT  VTSS_BIT(15)
#define  VTSS_X_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_INIT(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Asserting this bit will configure the VOE as responder of non-OAM frames
 * with sequence number and/or time stamps (SAM_SEQ).This must NOT be
 * asserted at the same time as asserting: * SAM_SEQ_INIT = 1
 *
 * \details
 * Field: ::VTSS_VOP_SAM_NON_OAM_SEQ_CFG . SAM_SEQ_RESP
 */
#define  VTSS_F_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_RESP(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_RESP  VTSS_BIT(14)
#define  VTSS_X_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_RESP(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * This configures the byte offset to the sequence number to be updated
 * within the non-OAM frame (SAM_SEQ).For Ethernet frames this field MUST
 * be programmed a value no less than 2 bytes, to avoid overwriting the
 * EPID field.For UDP frames this field MUST be programmed a value no less
 * than 8 bytes, to avoid overwriting the UDP protocol information.The
 * largest allowed value of this field is 72.The sequence number in the PDU
 * MUST be located within the first 148 bytes of the frame. This implies
 * that in case of a long encapsulation (e.g. IPv6 over ETH over MPLS over
 * ETH) there will be an upper limit to the valid value of the offset.
 *
 * \details
 * Field: ::VTSS_VOP_SAM_NON_OAM_SEQ_CFG . SAM_SEQ_OFFSET_SEQ_NO
 */
#define  VTSS_F_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_OFFSET_SEQ_NO(x)  VTSS_ENCODE_BITFIELD(x,7,7)
#define  VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_OFFSET_SEQ_NO     VTSS_ENCODE_BITMASK(7,7)
#define  VTSS_X_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_OFFSET_SEQ_NO(x)  VTSS_EXTRACT_BITFIELD(x,7,7)

/**
 * \brief
 * Select the format of the sequence number in SAM_SEQ frames.
 *
 * \details
 * 0: Include only a 4-byte sequence number.
 * 1: Use the full SAM_SEQ format.
 *
 * Field: ::VTSS_VOP_SAM_NON_OAM_SEQ_CFG . SAM_SEQ_FORMAT_SEQ_NO
 */
#define  VTSS_F_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_FORMAT_SEQ_NO(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_FORMAT_SEQ_NO  VTSS_BIT(6)
#define  VTSS_X_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_FORMAT_SEQ_NO(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * If the frames are IP/UDP frames, the VOE must update not only the
 * sequence number, but also the UDP checksum compensation field to avoid
 * altering the UDP checksum when updating the SAM_SEQ frame (Sequence
 * number / FORWARD-SEQ-NUM-ERROR).For this to happen, this register must
 * be asserted.UDP checksum handling is done independently for sequence
 * number and time stamps.
 *
 * \details
 * 0: Do not update the sequence number UDP checksum compensation field.
 * 1: Update the sequence number UDP checksum compensation field.
 *
 * Field: ::VTSS_VOP_SAM_NON_OAM_SEQ_CFG . SAM_SEQ_UPD_CHKSUM
 */
#define  VTSS_F_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_UPD_CHKSUM(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_UPD_CHKSUM  VTSS_BIT(5)
#define  VTSS_X_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_UPD_CHKSUM(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Asserting this bitfield requires: * SAM_SEQ_INIT = 1When the Initiator
 * function receives non OAM frames with sequence numbers, it can count
 * either: 1) Number of frames received with FORWARD-SEQ-NUMBER-ERROR = 12)
 * Number of frames received where the sequence number does not match the
 * sequence number received in the previous frame + 1.Frames 1) are always
 * counted if the SAM_SEQ format is used (see SAM_SEQ_FORMAT_SEQ_NO).If
 * SAM_SEQ_RX_ERR_CNT_ENA = 1 also frames 2) will be counted.The
 * configuration of this bit also determines which frames will assert the
 * sticky bit:	* VOP:VOE_STAT:OAM_RX_STICKY.LBR_TRANSID_ERR_STICKYand be
 * extracted to the CPU based on the following configuration: *
 * VOP:VOE_STAT:PDU_EXTRACT.SAM_RX_SEQ_ERR_EXTR
 *
 * \details
 * 0: Count only Rx SAM_SEQ frames with FORWARD-SEQ-NUMBER-ERROR = 1
 * 1: Count Rx SAM_SEQ frames with FORWARD-SEQ-NUMBER-ERROR = 1 or with
 * unexpected sequence number.
 *
 * Field: ::VTSS_VOP_SAM_NON_OAM_SEQ_CFG . SAM_SEQ_RX_ERR_CNT_ENA
 */
#define  VTSS_F_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_RX_ERR_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_RX_ERR_CNT_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_RX_ERR_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable time stamping functionality.
 *
 * \details
 * 0: Timestamping functionality is disabled.
 * 1: Timestamping functionality is enabled.
 *
 * Field: ::VTSS_VOP_SAM_NON_OAM_SEQ_CFG . SAM_SEQ_TS_ENA
 */
#define  VTSS_F_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_TS_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_TS_ENA  VTSS_BIT(3)
#define  VTSS_X_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_TS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Select between 8-bytes NTP and 8-bytes PTP time stamp formats.
 *
 * \details
 * 0: Use PTP time stamp format.
 * 1: Use NTP time stamp format.
 *
 * Field: ::VTSS_VOP_SAM_NON_OAM_SEQ_CFG . SAM_SEQ_TS_FORMAT
 */
#define  VTSS_F_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_TS_FORMAT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_TS_FORMAT  VTSS_BIT(2)
#define  VTSS_X_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_TS_FORMAT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * If the frames are IP/UDP frames, the VOE must update not only the time
 * stamp, but also the UDP checksum compensation field to avoid altering
 * the UDP checksum when updating the SAM_SEQ frame.For this to happen,
 * this register must be asserted.UDP checksum handling is done
 * independently for sequence number and time stamps.
 *
 * \details
 * 0: Do not update the time stamp UDP checksum compensation field.
 * 1: Update the time stamp UDP checksum compensation field.
 *
 * Field: ::VTSS_VOP_SAM_NON_OAM_SEQ_CFG . SAM_SEQ_TS_UPD_CHKSUM
 */
#define  VTSS_F_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_TS_UPD_CHKSUM(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_TS_UPD_CHKSUM  VTSS_BIT(1)
#define  VTSS_X_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_TS_UPD_CHKSUM(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * For Up-MEP VOEs the time used for time stamps is sampled in the
 * OAM_PDU_MOD block in the ANA block for Tx frames and in the REW block
 * for Rx frames. Latency and delay variation through the queue system will
 * therefore be included in the delay measurement for Up-MEPs.For Down-MEP
 * VOEs, the time used for time stamps can optionally be sampled in the
 * port module by setting this field. When using PTP time stamp format,
 * this option makes the precision similar to that of PTP time stamping.
 * When using NTP time stamp format, the precision is better than 20
 * ns.Since the port module does not have the ability to update the UDP
 * checksum compensation field, this option should only be enabled when UDP
 * checksum compesation is disabled.
 *
 * \details
 * 0: Down-MEP uses the OAM_PDU_MOD block in ANA/REW as reference point for
 * sampling the time used for the time stamp
 * 1: Down-MEP uses the port module as reference point for sampling the
 * time used for the time stamp
 *
 * Field: ::VTSS_VOP_SAM_NON_OAM_SEQ_CFG . SAM_SEQ_TS_PORT_REF
 */
#define  VTSS_F_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_TS_PORT_REF(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_TS_PORT_REF  VTSS_BIT(0)
#define  VTSS_X_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_TS_PORT_REF(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CPU extraction for the supported OAM PDU OpCodes.
 *
 * \details
 * Configures CPU copy for the supported OAM PDU OpCodes.
 *
 * Configuring a PDU type for CPU extraction, will result in all valid OAM
 * PDUs of this type to extracted to the CPU.
 *
 * Invalid OAM PDUs are not extracted. OAM PDUs are considered invalid if
 * they fail either of the following checks:
 *
 *  * MEL check (Must match the VOE)
 *  * MAC check
 *  * CCM validation (CCM/CCM-LM frames only)
 *  * SynLM check fails (SLM/SLR/1SL)
 *
 * Frames extracted by asserting this bit field are extracted to the
 * destination queues configured of the VOP:
 *
 *  * VOP::CPU_EXTR_CFG.*
 *  * VOP::CPU_EXTR_CFG_1.*
 *  * VOP::CPU_EXTR_CFG_2.*
 *
 * Register: \a VOP:VOE_CONF:OAM_CPU_COPY_CTRL
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_OAM_CPU_COPY_CTRL(gi)       VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,6)

/**
 * \brief
 * Configures whether OAM PDUs with UNKNOWN opcode should be extracted to
 * the CPU.Extracted frames are extracted to the default CPU queue,
 * configured in: * VOP::CPU_EXTR_CFG.DEF_COPY_QU
 *
 * \details
 * '0': No CPU copy
 * '1': Copy to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . UNK_OPCODE_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_UNK_OPCODE_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_UNK_OPCODE_CPU_COPY_ENA  VTSS_BIT(16)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_UNK_OPCODE_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * If asserted all valid LTM PDUs received by the VOE are extracted to the
 * CPU.Extraction queue is determined by: * VOP::CPU_EXTR_CFG_1.LT_CPU_QU
 *
 * \details
 * '0': No extraction to CPU
 * '1': Extract valid LTM frames to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . LTM_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_LTM_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_LTM_CPU_COPY_ENA  VTSS_BIT(15)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_LTM_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * If asserted all valid LTR PDUs received by the VOE are extracted to the
 * CPU.Extraction queue is determined by: * VOP::CPU_EXTR_CFG_1.LT_CPU_QU
 *
 * \details
 * '0': No extraction to CPU
 * '1': Extract valid LTR frames to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . LTR_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_LTR_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_LTR_CPU_COPY_ENA  VTSS_BIT(14)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_LTR_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * If asserted all valid LMM/SLM PDUs received by the VOE are extracted to
 * the CPU.Extraction queue is determined by: *
 * VOP::CPU_EXTR_CFG.LMM_CPU_QU
 *
 * \details
 * '0': No extraction to CPU
 * '1': Extract valid LMM frames to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . LMM_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_LMM_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_LMM_CPU_COPY_ENA  VTSS_BIT(13)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_LMM_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * If asserted all valid LMR / SLR / 1SL  PDUs received by the VOE are
 * extracted to the CPU.Extraction queue is determined by: *
 * VOP::CPU_EXTR_CFG.LMR_CPU_QU
 *
 * \details
 * '0': No extraction to CPU
 * '1': Extract valid LMR frames to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . LMR_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_LMR_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_LMR_CPU_COPY_ENA  VTSS_BIT(12)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_LMR_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * If asserted all valid TST PDUs received by the VOE are extracted to the
 * CPU.Extraction queue is determined by: * VOP::CPU_EXTR_CFG_1.TST_CPU_QU
 *
 * \details
 * '0': No extraction to CPU
 * '1': Extract valid TST frames to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . TST_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_TST_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_TST_CPU_COPY_ENA  VTSS_BIT(11)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_TST_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * If asserted all valid LBM PDUs received by the VOE are extracted to the
 * CPU.Extraction queue is determined by: * VOP::CPU_EXTR_CFG_1.LBM_CPU_QU
 *
 * \details
 * '0': No extraction to CPU
 * '1': Extract valid LBM frames to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . LBM_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_LBM_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_LBM_CPU_COPY_ENA  VTSS_BIT(10)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_LBM_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * If asserted all valid LBR PDUs received by the VOE are extracted to the
 * CPU.Extraction queue is determined by: *
 * VOP::CPU_EXTR_CFG_1.LBR_CPU_QUThis setting is also used to control
 * extraction of SAM_SEQ frames (see VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG.*)
 *
 * \details
 * '0': No extraction to CPU
 * '1': Extract valid LBR frames to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . LBR_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_LBR_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_LBR_CPU_COPY_ENA  VTSS_BIT(9)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_LBR_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * If asserted all valid DMM PDUs received by the VOE are extracted to the
 * CPU.Extraction queue is determined by: * VOP::CPU_EXTR_CFG.DMM_CPU_QU
 *
 * \details
 * '0': No extraction to CPU
 * '1': Extract valid DMM frames to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . DMM_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_DMM_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_DMM_CPU_COPY_ENA  VTSS_BIT(8)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_DMM_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * If asserted all valid DMR PDUs by the VOE are extracted to the
 * CPU.Extraction queue is determined by: * VOP::CPU_EXTR_CFG.DMR_CPU_QU
 *
 * \details
 * '0': No extraction to CPU
 * '1': Extract valid DMR frames to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . DMR_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_DMR_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_DMR_CPU_COPY_ENA  VTSS_BIT(7)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_DMR_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * If asserted all valid 1DM PDUs received by the VOE are extracted to the
 * CPU.Extraction queue is determined by: *
 * VOP::CPU_EXTR_CFG.DMR_CPU_QU(This PDU type reuses the DMR extraction
 * queue)
 *
 * \details
 * '0': No extraction to CPU
 * '1': Extract valid 1DM frames to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . SDM_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_SDM_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_SDM_CPU_COPY_ENA  VTSS_BIT(6)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_SDM_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * If asserted all valid CCM PDUs received by the VOE are extracted to the
 * CPU.Extraction queue is determined by: * VOP::CPU_EXTR_CFG_1.CCM_CPU_QU
 *
 * \details
 * '0': No extraction to CPU
 * '1': Extract valid CCM frames to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . CCM_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_CCM_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_CCM_CPU_COPY_ENA  VTSS_BIT(5)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_CCM_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * If asserted all valid CCM-LM PDUs received by the VOE are extracted to
 * the CPU.Extraction queue is determined by: *
 * VOP::CPU_EXTR_CFG_1.CCM_LM_CPU_QU
 *
 * \details
 * '0': No extraction to CPU
 * '1': Extract valid CCM_LM frames to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . CCM_LM_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_CCM_LM_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_CCM_LM_CPU_COPY_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_CCM_LM_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * The configuration of this bit field influences the following PDU error
 * verification:RX:---------- * RX_MEL_LOW * DMAC_RX_ERR *
 * PDU_VERSION_RX_ERRTX:-------------- * TX_BLOCK_ERRThe checks mentioned
 * above will be done for all PDU types, however the associated sticky bit
 * assertion and extraction of PDUs will depend on the setting of this
 * register.
 *
 * \details
 * 0: Assert sticky bit and extract PDU for all PDU types.
 * 1: Assert sticky bit and extract PDU only for CCM(-LM) frames.
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . PDU_ERR_EXTRACT_CCM_ONLY
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_PDU_ERR_EXTRACT_CCM_ONLY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_PDU_ERR_EXTRACT_CCM_ONLY  VTSS_BIT(3)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_PDU_ERR_EXTRACT_CCM_ONLY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * If asserted all valid AIS PDUs received by the VOE are extracted to the
 * CPU.Extraction queue is determined by: * VOP::CPU_EXTR_CFG_2.AIS_CPU_QU
 *
 * \details
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . AIS_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_AIS_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_AIS_CPU_COPY_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_AIS_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * If asserted all valid LCK PDUs received by the VOE are extracted to the
 * CPU.Extraction queue is determined by: * VOP::CPU_EXTR_CFG_2.LCK_CPU_QU
 *
 * \details
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . LCK_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_LCK_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_LCK_CPU_COPY_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_LCK_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * If asserted all valid CSF PDUs received by the VOE are extracted to the
 * CPU.Extraction queue is determined by: * VOP::CPU_EXTR_CFG_2.CSF_CPU_QU
 *
 * \details
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL . CSF_CPU_COPY_ENA
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_CSF_CPU_COPY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_CSF_CPU_COPY_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_CSF_CPU_COPY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief CPU extraction for the supported OAM PDU OpCodes.
 *
 * \details
 * Configures CPU copy for the supported OAM PDU OpCodes.
 *
 * Configuring a PDU type for CPU extraction, will result in all valid OAM
 * PDUs of this type to extracted to the CPU.
 *
 * Invalid OAM PDUs are not extracted. OAM PDUs are considered invalid if
 * they fail either of the following checks:
 *
 *  * MEL check (Must match the VOE)
 *  * MAC check
 *  * CCM validation (CCM/CCM-LM frames only)
 *  * SynLM check fails (SLM/SLR/1SL)
 *
 * Frames extracted by asserting this bit field are extracted to the
 * destination queues configured of the VOP:
 *
 *  * VOP::CPU_EXTR_CFG.*
 *  * VOP::CPU_EXTR_CFG_1.*
 *  * VOP::CPU_EXTR_CFG_2.*
 *
 * Register: \a VOP:VOE_CONF:OAM_CPU_COPY_CTRL_2
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_OAM_CPU_COPY_CTRL_2(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,7)

/**
 * \brief
 * This bit field contains 16 bits each of which represents one of the
 * Generic OpCodes.If the bit representing a specific Generic OpCode is
 * asserted, all valid PDUs received by the VOE of that type are extracted
 * to the CPU queue configured in the following field: *
 * VOP::OAM_GENERIC_CFG.GENERIC_OPCODE_CPU_QU
 *
 * \details
 * '0': No CPU copy
 * '1': Copy to CPU
 *
 * Field: ::VTSS_VOP_OAM_CPU_COPY_CTRL_2 . GENERIC_COPY_MASK
 */
#define  VTSS_F_VOP_OAM_CPU_COPY_CTRL_2_GENERIC_COPY_MASK(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_OAM_CPU_COPY_CTRL_2_GENERIC_COPY_MASK     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_OAM_CPU_COPY_CTRL_2_GENERIC_COPY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Allow PDUs to pass through the VOE.
 *
 * \details
 * Standard Y.1731 MEL filtering requires a MEP to terminate / block all
 * OAM PDUs received at the same level as configured for the MEP. It is
 * default behavior for the VOE to implement this MEL filtering.
 *
 * This behavior can be altered for generic OpCodes by asserting this bit.

 *
 * Register: \a VOP:VOE_CONF:PDU_VOE_PASS
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_PDU_VOE_PASS(gi)            VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,8)

/**
 * \brief
 * Each of the bits in the register represents a Generic OpCode.See:
 * VOP::OAM_GENERIC_CFG.*When asserting a bit in the register, the
 * corresponding Generic OpCode will be allowed to pass though VOE, rather
 * than be terminated, when received at the same MEL as is configured for
 * the VOE.This can be used to allow e.g. Ring PDUs to be copied and to
 * pass transparently through the VOE.If a blocking VOE is located after
 * the VOE terminating the generic Opcode PDU on the same side of the
 * switch, the PDU will be blocked correctly. However, any service
 * statistic, shaping or policing located between the pipeline points of
 * the two VOEs may not count the generic PDU.
 *
 * \details
 * Field: ::VTSS_VOP_PDU_VOE_PASS . GENERIC_VOE_PASS_ENA
 */
#define  VTSS_F_VOP_PDU_VOE_PASS_GENERIC_VOE_PASS_ENA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_PDU_VOE_PASS_GENERIC_VOE_PASS_ENA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_PDU_VOE_PASS_GENERIC_VOE_PASS_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Configuration which OAM PDUs are counted in selected PDU counter.
 *
 * \details
 * The OAM frames processed by the VOE can be counted separately in Rx and
 * Tx direction.
 * In each direction there are two counters:
 *
 * 1) Default OAM counter
 * This counter counts all the PDU types which are NOT selected using the
 * OAM_CNT_OAM_CTRL register:
 *
 *  * RX_OAM_FRM_CNT
 *  * TX_OAM_FRM_CNT
 *
 * 2) Selected OAM counter:
 * This counter counts all the PDU types selected for counting using the
 * OAM_CNT_OAM_CTRL register:
 *
 *  * RX_SEL_OAM_CNT
 *  * TX_SEL_OAM_CNT
 *
 * Any valid OAM PDU is counted in exactly one of the above registers.
 *
 * I.e. as default all OAM PDUs are not selected, and they are all counted
 * in the default OAM counters: RX / TX _ OAM_FRM_CNT.
 *
 * Using this register (OAM_CNT_OAM_CTRL), PDUs can be moved to the
 * selected counters:
 * RX / TX SEL_OAM_CNT.
 *
 * The selection of OAM PDUs for the selected counter is done commonly for
 * the Tx and Rx direction.
 *
 * Register: \a VOP:VOE_CONF:OAM_CNT_OAM_CTRL
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_OAM_CNT_OAM_CTRL(gi)        VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,9)

/**
 * \brief
 * Enable / disable that valid OAM PDUs with Generic OpCodes are counted as
 * selected OAM.This bit field contains a separate bit for each of the
 * possible 8 Generic OpCodes.
 *
 * \details
 * x0x: Count as other OAM
 * x1x: Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . GENERIC_OAM_CNT_MASK
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_GENERIC_OAM_CNT_MASK(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_GENERIC_OAM_CNT_MASK     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_GENERIC_OAM_CNT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * OAM PDUs not recognized as either of the PDUs with special configuration
 * or as a Generic OpCode, will be classified as an UNKNOWN PDU.This
 * register configures whether UNKNOWN PDUs should be counted as selected
 * OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . UNK_OPCODE_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_UNK_OPCODE_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_UNK_OPCODE_OAM_CNT_ENA  VTSS_BIT(15)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_UNK_OPCODE_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Enable / disable count of OAM PDU LTM as selected OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . LTM_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_LTM_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_LTM_OAM_CNT_ENA  VTSS_BIT(14)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_LTM_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Enable / disable count of OAM PDU LTR as selected OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . LTR_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_LTR_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_LTR_OAM_CNT_ENA  VTSS_BIT(13)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_LTR_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Enable / disable count of OAM PDU LMM/SLM as selected OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . LMM_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_LMM_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_LMM_OAM_CNT_ENA  VTSS_BIT(12)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_LMM_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Enable / disable count of OAM PDU LMR/SLR/1SL as selected OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . LMR_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_LMR_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_LMR_OAM_CNT_ENA  VTSS_BIT(11)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_LMR_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Enable / disable count of OAM PDU LBM as selected OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . LBM_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_LBM_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_LBM_OAM_CNT_ENA  VTSS_BIT(10)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_LBM_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Enable / disable count of OAM PDU TST as selected OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . TST_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_TST_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_TST_OAM_CNT_ENA  VTSS_BIT(9)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_TST_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Enable / disable count of OAM PDU LBR as selected OAM.This setting is
 * also used to control counting of SAM_SEQ frames (see
 * VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG.*)
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . LBR_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_LBR_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_LBR_OAM_CNT_ENA  VTSS_BIT(8)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_LBR_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Enable / disable count of OAM PDU DMM as selected OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . DMM_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_DMM_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_DMM_OAM_CNT_ENA  VTSS_BIT(7)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_DMM_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable / disable count of OAM PDU DMR as selected OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . DMR_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_DMR_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_DMR_OAM_CNT_ENA  VTSS_BIT(6)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_DMR_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enable / disable count of OAM PDU 1DM as selected OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . SDM_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_SDM_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_SDM_OAM_CNT_ENA  VTSS_BIT(5)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_SDM_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable / disable count of OAM PDU CCM as selected OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . CCM_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_CCM_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_CCM_OAM_CNT_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_CCM_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable / disable count of OAM PDU CCM with LM content as selected
 * OAM.For this register to take effect, the HW processing of CCM-LM frames
 * must be enabled: * VOP:VOE_CONF:OAM_HW_CTRL.CCM_LM_ENA
 *
 * \details
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . CCM_LM_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_CCM_LM_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_CCM_LM_OAM_CNT_ENA  VTSS_BIT(3)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_CCM_LM_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable / disable count of OAM PDU AIS as selected OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . AIS_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_AIS_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_AIS_OAM_CNT_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_AIS_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable / disable count of OAM PDU LCK as selected OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . LCK_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_LCK_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_LCK_OAM_CNT_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_LCK_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable / disable count of OAM PDU CSF as selected OAM.
 *
 * \details
 * '0': Count as other OAM
 * '1': Count as selected OAM
 *
 * Field: ::VTSS_VOP_OAM_CNT_OAM_CTRL . CSF_OAM_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_OAM_CTRL_CSF_OAM_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_OAM_CNT_OAM_CTRL_CSF_OAM_CNT_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_OAM_CNT_OAM_CTRL_CSF_OAM_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configuration of which OAM PDUs should be counted by LM counters.
 *
 * \details
 * Default behavior is that all OAM PDUs processed by a VOE (i.e. OAM PDU
 * MEG level matches VOE MEL_VAL) will not be counted as data by the LM
 * counters. This is according to Y.1731
 *
 * Using this register (OAM_CNT_DATA_CTRL) it is possible to configure the
 * OAM PDUs separately to be counted as data.
 * This includes all PDUs except for SLM, SLR and 1SL which are never
 * counted in the LM counters, unless the VOE is configured for synthetic
 * loss measurement:
 *
 *  * VOP:VOE_CONF_REG:VOE_MISC_CONFIG.SL_ENA
 *
 * The configuration in this register controls the counting in both the Rx
 * and Tx direction.
 *
 * The data counters are located:
 *
 * Service VOE:
 * ---------------------
 * Egress: REW:VOE_SRV_LM_CNT:SRV_LM_CNT_LSB.SRV_LM_CNT_LSB
 * Ingress: ANA_AC_OAM_MOD:VOE_SRV_LM_CNT:SRV_LM_CNT_LSB.SRV_LM_CNT_LSB
 *
 * Port VOE:
 * -------------------
 * Egress: REW:VOE_PORT_LM_CNT:PORT_LM_CNT_LSB.PORT_LM_CNT_LSB
 * Ingress: ANA_AC_OAM_MOD:VOE_PORT_LM_CNT:PORT_LM_CNT_LSB.PORT_LM_CNT_LSB

 *
 * Register: \a VOP:VOE_CONF:OAM_CNT_DATA_CTRL
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_OAM_CNT_DATA_CTRL(gi)       VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,10)

/**
 * \brief
 * Enable / disable that valid OAM PDUs with Generic OpCodes are counted by
 * the VOE LM counters.This bit field contains a separate bit for each of
 * the possible 16 Generic OpCodes.
 *
 * \details
 * x0x: Do NOT count generic OpCode in LM counters.
 * x1x: DO count generic OpCode in LM counters.
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . GENERIC_DATA_CNT_MASK
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_GENERIC_DATA_CNT_MASK(x)  VTSS_ENCODE_BITFIELD(x,15,16)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_GENERIC_DATA_CNT_MASK     VTSS_ENCODE_BITMASK(15,16)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_GENERIC_DATA_CNT_MASK(x)  VTSS_EXTRACT_BITFIELD(x,15,16)

/**
 * \brief
 * If a PDU is received with an OpCode which does not match any Specific
 * OpCode or a Generic OpCode, it will be processed as an UNKNOWN
 * OpCode.This bit field configures if OAM frames with UNKOWN OpCode are
 * counted as data in the LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . UNK_OPCODE_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_UNK_OPCODE_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_UNK_OPCODE_DATA_CNT_ENA  VTSS_BIT(14)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_UNK_OPCODE_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Enable / disable counting valid LTM PDUs as data in LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . LTM_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_LTM_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_LTM_DATA_CNT_ENA  VTSS_BIT(13)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_LTM_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Enable / disable counting valid LTR PDUs as data in LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . LTR_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_LTR_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_LTR_DATA_CNT_ENA  VTSS_BIT(12)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_LTR_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Enable / disable counting valid LMM PDUs as data in LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . LMM_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_LMM_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_LMM_DATA_CNT_ENA  VTSS_BIT(11)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_LMM_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Enable / disable counting valid LMR PDUs as data in LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . LMR_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_LMR_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_LMR_DATA_CNT_ENA  VTSS_BIT(10)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_LMR_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Enable / disable counting valid LBM PDUs as data in LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . LBM_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_LBM_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_LBM_DATA_CNT_ENA  VTSS_BIT(9)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_LBM_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Enable / disable counting valid TST PDUs as data in LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . TST_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_TST_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_TST_DATA_CNT_ENA  VTSS_BIT(8)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_TST_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Enable / disable counting valid LBR PDUs as data in LM counters.This
 * setting is also used to control counting SAM_SEQ frames (see
 * VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG.*)
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . LBR_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_LBR_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_LBR_DATA_CNT_ENA  VTSS_BIT(7)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_LBR_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable / disable counting valid DMM PDUs as data in LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . DMM_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_DMM_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_DMM_DATA_CNT_ENA  VTSS_BIT(6)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_DMM_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enable / disable counting valid DMR PDUs as data in LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . DMR_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_DMR_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_DMR_DATA_CNT_ENA  VTSS_BIT(5)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_DMR_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable / disable counting valid 1DM PDUs as data in LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . SDM_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_SDM_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_SDM_DATA_CNT_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_SDM_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable / disable counting valid CCM(-LM) PDUs as data in LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . CCM_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_CCM_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_CCM_DATA_CNT_ENA  VTSS_BIT(3)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_CCM_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable / disable counting valid AIS PDUs as data in LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . AIS_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_AIS_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_AIS_DATA_CNT_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_AIS_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable / disable counting valid LCK PDUs as data in LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . LCK_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_LCK_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_LCK_DATA_CNT_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_LCK_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable / disable counting valid CSF PDUs as data in LM counters.
 *
 * \details
 * '0': Do not count as data
 * '1': Count as data
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL . CSF_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_CSF_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_CSF_DATA_CNT_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_CSF_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configuration of which OAM PDUs should be counted by LM counters.
 *
 * \details
 * See description of OAM_CNT_DATA_CTRL.
 *
 * Register: \a VOP:VOE_CONF:OAM_CNT_DATA_CTRL_2
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_OAM_CNT_DATA_CTRL_2(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,11)

/**
 * \brief
 * According to G.8021, PDUs with MEL low, which are blocked by the MEL
 * filter, should be included in Rx LM count.Whether such Rx PDUs (except
 * for CCM(-LM)) are included in LM count or not can be controlled by this
 * field.LM counting of CCM(-LM) PDUs with MEL low is controlled by *
 * VOP:VOE_CONF:OAM_CNT_DATA_CTRL_2.CCM_MEL_LOW_DATA_CNT_ENAWhen this field
 * is set, LM counting of Rx MEL low PDUs is done independently of the
 * enable fields for the individual PDU types in  *
 * VOP:VOE_CONF:OAM_CNT_DATA_CTRL
 *
 * \details
 * '0': PDUs with MEL low are not included in LM count.
 * '1': PDUs with MEL low are included in LM count, excpet for CCM(-LM)
 * PDUs.
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL_2 . MEL_LOW_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_2_MEL_LOW_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_2_MEL_LOW_DATA_CNT_ENA  VTSS_BIT(3)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_2_MEL_LOW_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * According to G.8021, CCM PDUs with MEL low should not be included in Rx
 * LM count, if CCM-based loss measurement is used.Whether Rx CCM(-LM) PDUs
 * with MEL low are included in LM count or not can be controlled by this
 * field.LM counting of other PDU types than CCM(-LM) with MEL low is
 * controlled by *
 * VOP:VOE_CONF:OAM_CNT_DATA_CTRL_2.MEL_LOW_DATA_CNT_ENAWhen this field is
 * set, LM counting of CM-(LM) Rx MEL low PDUs is done independently of the
 * enable fields for the CCM(-LM) PDU type in  *
 * VOP:VOE_CONF:OAM_CNT_DATA_CTRL.CCM_DATA_CNT_ENA
 *
 * \details
 * '0': CCM(-LM) PDUs with MEL low are not included in LM count.
 * '1': CCM(-LM) PDUs with MEL low are included in LM count.
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL_2 . CCM_MEL_LOW_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_2_CCM_MEL_LOW_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_2_CCM_MEL_LOW_DATA_CNT_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_2_CCM_MEL_LOW_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * According to G.8021, all PDUs should be included in Rx LM count when
 * when running LMM/LMR based loss measurement. This includes PDUs with
 * matching MEL which fail the DMAC check and are therefore ignored by the
 * reception process for the particular PDU type.Whether such Rx PDUs are
 * included in LM count or not can be controlled by this field.When this
 * field is set, LM counting of Rx DMAC fail PDUs is only done if the
 * enable field for the particular PDU type is set in  *
 * VOP:VOE_CONF:OAM_CNT_DATA_CTRL
 *
 * \details
 * '0': PDUs which fail the DMAC check are not included in LM count.
 * '1': PDUs which fail the DMAC check are included in LM count.
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL_2 . DMAC_FAIL_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_2_DMAC_FAIL_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_2_DMAC_FAIL_DATA_CNT_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_2_DMAC_FAIL_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * According to G.8021, all PDUs should be included in Rx LM count when
 * when running LMM/LMR based loss measurement. This includes PDUs with
 * matching MEL which fail the version check and are therefore ignored by
 * the reception process for the particular PDU type.Whether such Rx PDUs
 * are included in LM count or not can be controlled by this field.When
 * this field is set, LM counting of Rx version fail PDUs is only done if
 * the enable field for the particular PDU type is set in  *
 * VOP:VOE_CONF:OAM_CNT_DATA_CTRL
 *
 * \details
 * '0': PDUs which fail the version check are not included in LM count.
 * '1': PDUs which fail the version check are included in LM count.
 *
 * Field: ::VTSS_VOP_OAM_CNT_DATA_CTRL_2 . VER_FAIL_DATA_CNT_ENA
 */
#define  VTSS_F_VOP_OAM_CNT_DATA_CTRL_2_VER_FAIL_DATA_CNT_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_OAM_CNT_DATA_CTRL_2_VER_FAIL_DATA_CNT_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_OAM_CNT_DATA_CTRL_2_VER_FAIL_DATA_CNT_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief VOE MAC Unicast address (LSB)
 *
 * \details
 * Configures the VOE Unicast MAC address (LSB).
 *
 * This address can be verified by the VOE when frames arrive, depending on
 * the configuration of:
 * VOP:VOE_CONF:VOE_CTRL.RX_DMAC_CHK_SEL
 *
 * Register: \a VOP:VOE_CONF:MEP_UC_MAC_LSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_MEP_UC_MAC_LSB(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,12)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_MEP_UC_MAC_LSB . MEP_UC_MAC_LSB
 */
#define  VTSS_F_VOP_MEP_UC_MAC_LSB_MEP_UC_MAC_LSB(x)  (x)
#define  VTSS_M_VOP_MEP_UC_MAC_LSB_MEP_UC_MAC_LSB     0xffffffff
#define  VTSS_X_VOP_MEP_UC_MAC_LSB_MEP_UC_MAC_LSB(x)  (x)


/**
 * \brief VOE MAC Unicast address (MSB)
 *
 * \details
 * Configures the VOE Unicast MAC address (MSB).
 *
 * This address can be verified by the VOE when frames arrive, depending on
 * the configuration of:
 *  * VOP:VOE_CONF:VOE_CTRL.RX_DMAC_CHK_SEL
 *
 * Register: \a VOP:VOE_CONF:MEP_UC_MAC_MSB
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_MEP_UC_MAC_MSB(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,13)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_MEP_UC_MAC_MSB . MEP_UC_MAC_MSB
 */
#define  VTSS_F_VOP_MEP_UC_MAC_MSB_MEP_UC_MAC_MSB(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_MEP_UC_MAC_MSB_MEP_UC_MAC_MSB     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_MEP_UC_MAC_MSB_MEP_UC_MAC_MSB(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief OAM HW processing control
 *
 * \details
 * Configures per OAM OpCode if it is processed by the VOE.
 *
 * If an OAM PDU type is not enabled in this register, the OAM PDU will not
 * be updated by the VOE.
 * This allows the PDU processing to be done in SW.
 *
 * OAM PDU statistics are updated regardless of this setting.
 *
 * When OAM PDU is disabled, the following functions are still performed by
 * the VOE:
 *  * Generic Y.1731 frame validation: MEL filtering, DMAC check. No PDU
 * specific filtering (CCM only)
 *  * The Rx sticky bits will be set for a PDU.
 *  * OAM PDUs can be extracted to the CPU.
 *  * OAM PDUs can be counted as data.
 *  * OAM PDUs specific counters are updated.
 *
 * Further TST / LBR Test TLV CRC can be enabled, using the following bit
 * fields:
 *  * TST_TLV_CRC_VERIFY_ENA
 *  * LBR_TLV_CRC_VERIFY_ENA
 *
 * Register: \a VOP:VOE_CONF:OAM_HW_CTRL
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_OAM_HW_CTRL(gi)             VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,14)

/**
 * \brief
 * Enable HW processing of valid LMM/SLM PDUs received by the VOE in both
 * the Tx and the Rx direction.
 *
 * \details
 * Field: ::VTSS_VOP_OAM_HW_CTRL . LMM_ENA
 */
#define  VTSS_F_VOP_OAM_HW_CTRL_LMM_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_OAM_HW_CTRL_LMM_ENA       VTSS_BIT(11)
#define  VTSS_X_VOP_OAM_HW_CTRL_LMM_ENA(x)    VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Enable HW processing of valid LMR/SLR/1SL PDUs received by the VOE in
 * both the Tx and the Rx direction.
 *
 * \details
 * Field: ::VTSS_VOP_OAM_HW_CTRL . LMR_ENA
 */
#define  VTSS_F_VOP_OAM_HW_CTRL_LMR_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_OAM_HW_CTRL_LMR_ENA       VTSS_BIT(10)
#define  VTSS_X_VOP_OAM_HW_CTRL_LMR_ENA(x)    VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Enable HW processing of valid TST PDUs received by the VOE in both the
 * Tx and the Rx direction.
 *
 * \details
 * Field: ::VTSS_VOP_OAM_HW_CTRL . TST_ENA
 */
#define  VTSS_F_VOP_OAM_HW_CTRL_TST_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_OAM_HW_CTRL_TST_ENA       VTSS_BIT(9)
#define  VTSS_X_VOP_OAM_HW_CTRL_TST_ENA(x)    VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Assertion of this bit field requires TST_ENA to be asserted.If this bit
 * field is asserted, the incoming TST PDUs will be checked for having a
 * TLV of type = "Test TLV" (Type= 32).If the TLV Test PDU includes a
 * CRC-32 field, the CRC is calculated across the Data Pattern, and the
 * CRC-32 field is verified.The number of Test TLV with CRC-32 error is
 * counted in: * VOP:VOE_CRC_ERR:LBR_CRC_ERR_CNT.LBR_CRC_ERR_CNTNote: The
 * Test TLV must be the first TLV in the received TST PDU.In case several
 * Test TLVs are present in the same PDU, only the first is checked for
 * CRC.Note: This should not be enabled at the same time as:  *
 * LBR_TLV_CRC_VERIFY_ENA(The TST and LBM/LBR are expected to mutually
 * exclusive, hence they will use the same TLV_CRC_ERR counter)
 *
 * \details
 * Field: ::VTSS_VOP_OAM_HW_CTRL . TST_TLV_CRC_VERIFY_ENA
 */
#define  VTSS_F_VOP_OAM_HW_CTRL_TST_TLV_CRC_VERIFY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_OAM_HW_CTRL_TST_TLV_CRC_VERIFY_ENA  VTSS_BIT(8)
#define  VTSS_X_VOP_OAM_HW_CTRL_TST_TLV_CRC_VERIFY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Enable HW processing of valid LBM PDUs received by the VOE in both the
 * Tx and the Rx direction.
 *
 * \details
 * Field: ::VTSS_VOP_OAM_HW_CTRL . LBM_ENA
 */
#define  VTSS_F_VOP_OAM_HW_CTRL_LBM_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_OAM_HW_CTRL_LBM_ENA       VTSS_BIT(7)
#define  VTSS_X_VOP_OAM_HW_CTRL_LBM_ENA(x)    VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enable HW processing of valid LBR PDUs received by the VOE in both the
 * Tx and the Rx direction.This bit is also used to enable any SAM_SEQ PDU
 * HW updates.
 *
 * \details
 * Field: ::VTSS_VOP_OAM_HW_CTRL . LBR_ENA
 */
#define  VTSS_F_VOP_OAM_HW_CTRL_LBR_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_OAM_HW_CTRL_LBR_ENA       VTSS_BIT(6)
#define  VTSS_X_VOP_OAM_HW_CTRL_LBR_ENA(x)    VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Assertion of this bit field requires LBR_ENA to be asserted.If this bit
 * field is asserted, the incoming LBR PDUs will be checked for having a
 * TLV of type = "Test TLV" (Type= 32).If the TLV Test PDU includes a
 * CRC-32 field, the CRC is calculated across the Data Pattern, and the
 * CRC-32 field is verified.The number of Test TLV with CRC-32 error is
 * counted in: * VOP:VOE_CRC_ERR:LBR_CRC_ERR_CNT.LBR_CRC_ERR_CNTNote: The
 * Test TLV must be the first TLV in the received LBR PDU.In case several
 * Test TLVs are present in the same PDU, only the first is checked for
 * CRC.Note: This should not be enabled at the same time as:  *
 * TST_TLV_CRC_VERIFY_ENA(The TST and LBM/LBR are expected to mutually
 * exclusive, hence they will use the same TLV_CRC_ERR counter)
 *
 * \details
 * Field: ::VTSS_VOP_OAM_HW_CTRL . LBR_TLV_CRC_VERIFY_ENA
 */
#define  VTSS_F_VOP_OAM_HW_CTRL_LBR_TLV_CRC_VERIFY_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_OAM_HW_CTRL_LBR_TLV_CRC_VERIFY_ENA  VTSS_BIT(5)
#define  VTSS_X_VOP_OAM_HW_CTRL_LBR_TLV_CRC_VERIFY_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enable HW processing of valid DMM PDUs received by the VOE in both the
 * Tx and the Rx direction.
 *
 * \details
 * Field: ::VTSS_VOP_OAM_HW_CTRL . DMM_ENA
 */
#define  VTSS_F_VOP_OAM_HW_CTRL_DMM_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_OAM_HW_CTRL_DMM_ENA       VTSS_BIT(4)
#define  VTSS_X_VOP_OAM_HW_CTRL_DMM_ENA(x)    VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enable HW processing of valid DMR PDUs received by the VOE in both the
 * Tx and the Rx direction.
 *
 * \details
 * Field: ::VTSS_VOP_OAM_HW_CTRL . DMR_ENA
 */
#define  VTSS_F_VOP_OAM_HW_CTRL_DMR_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_OAM_HW_CTRL_DMR_ENA       VTSS_BIT(3)
#define  VTSS_X_VOP_OAM_HW_CTRL_DMR_ENA(x)    VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enable HW processing of valid 1DM PDUs received by the VOE in both the
 * Tx and the Rx direction.
 *
 * \details
 * Field: ::VTSS_VOP_OAM_HW_CTRL . SDM_ENA
 */
#define  VTSS_F_VOP_OAM_HW_CTRL_SDM_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_OAM_HW_CTRL_SDM_ENA       VTSS_BIT(2)
#define  VTSS_X_VOP_OAM_HW_CTRL_SDM_ENA(x)    VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enable HW processing of valid CCM PDUs received by the VOE in both the
 * Tx and the Rx direction.
 *
 * \details
 * Field: ::VTSS_VOP_OAM_HW_CTRL . CCM_ENA
 */
#define  VTSS_F_VOP_OAM_HW_CTRL_CCM_ENA(x)    VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_OAM_HW_CTRL_CCM_ENA       VTSS_BIT(1)
#define  VTSS_X_VOP_OAM_HW_CTRL_CCM_ENA(x)    VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enable HW processing of valid CCM-LM PDUs received by the VOE in both
 * the Tx and the Rx direction.CC-LM is only supported on the priority
 * configured in the following priority: * VOP:VOE_CONF:CCM_CFG.CCM_PRIOIf
 * an Rx CCM PDU is received on another priority than this, statistics are
 * updated as if it was a CCM-LM PDU, but no values are sampled for use in
 * the Tx direction: * CCM-LM.TX_FC_F * FC LM Rx counter when the CCM-LM
 * frame was receivedThese values are sampled for valid CCM-LM PDUs
 * received on the correct priority.The result of the priority test for the
 * latest valid Rx CCM-LM PDU is stored: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_PRIO_DEFECTNote:	CCM_ENA must be
 * asserted when asserting CCM_LM_ENA
 *
 * \details
 * Field: ::VTSS_VOP_OAM_HW_CTRL . CCM_LM_ENA
 */
#define  VTSS_F_VOP_OAM_HW_CTRL_CCM_LM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_OAM_HW_CTRL_CCM_LM_ENA    VTSS_BIT(0)
#define  VTSS_X_VOP_OAM_HW_CTRL_CCM_LM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Enables loopback of OAM Messages to OAM Replies
 *
 * \details
 * Some OAM PDU types can be looped, by returning a Reply in response to a
 * Message.
 *
 * The looping of these PDUs is enabled by setting the bit fields in this
 * register.
 *
 * When looping a PDU, both the Message and the Reply must be enabled for
 * PDU updating:
 *
 *  * VOP:VOE_CONF:OAM_HW_CTRL.*
 *
 * Register: \a VOP:VOE_CONF:LOOPBACK_ENA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_LOOPBACK_ENA(gi)            VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,15)

/**
 * \brief
 * This field determines whether incoming LBM frames are looped and
 * transmitted as LBR frames.If loopback is not enabled frames are
 * discarded.Incoming LBM frames can optionally be extracted to the CPU,
 * regardless of loopback setting.This setting is also used to loop SAM_SEQ
 * frames (see VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG.*)
 *
 * \details
 * '0': OAM LBM PDU is not looped as LBR frames.
 * '1': OAM LBM PDU is looped as a LBR frame.
 *
 * Field: ::VTSS_VOP_LOOPBACK_ENA . LB_LBM_ENA
 */
#define  VTSS_F_VOP_LOOPBACK_ENA_LB_LBM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_LOOPBACK_ENA_LB_LBM_ENA   VTSS_BIT(2)
#define  VTSS_X_VOP_LOOPBACK_ENA_LB_LBM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * This field determines whether incoming LMM/SLM frames are looped and
 * transmitted as LMR/SLR frames.If loopback is not enabled frames are
 * discarded.Incoming LMM/SLM frames can optionally be extracted to the
 * CPU, regardless of loopback setting.
 *
 * \details
 * '0': OAM LMM/SLM PDU is not looped as LMR/SLR frames.
 * '1': OAM LMM/SLM PDU is looped as a LMR/SLR frame.
 *
 * Field: ::VTSS_VOP_LOOPBACK_ENA . LB_LMM_ENA
 */
#define  VTSS_F_VOP_LOOPBACK_ENA_LB_LMM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_LOOPBACK_ENA_LB_LMM_ENA   VTSS_BIT(1)
#define  VTSS_X_VOP_LOOPBACK_ENA_LB_LMM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This field determines whether incoming DMM frames are looped and
 * transmitted as DMR frames.If loopback is not enabled frames are
 * discarded.Incoming DMM frames can optionally be extracted to the CPU,
 * regardless of loopback setting.
 *
 * \details
 * '0': OAM DMM PDU is not looped as DMR frames.
 * '1': OAM DMM PDU is looped as a DMR frame.
 *
 * Field: ::VTSS_VOP_LOOPBACK_ENA . LB_DMM_ENA
 */
#define  VTSS_F_VOP_LOOPBACK_ENA_LB_DMM_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_LOOPBACK_ENA_LB_DMM_ENA   VTSS_BIT(0)
#define  VTSS_X_VOP_LOOPBACK_ENA_LB_DMM_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief OAM Loopback configuration
 *
 * \details
 * Contains configuration for looping back frames. I.e. returning OAM
 * replies in response to messages.
 *
 * When OAM Messages are looped into OAM Replies, by the VOE, the ISDX of
 * the OAM Reply is set to the value configured in:
 *
 *  * LB_ISDX
 *
 * regardless of the ISDX of the incoming OAM Message.
 *
 * All OAM Replies are assigned the same ISDX value.
 *
 * Register: \a VOP:VOE_CONF:LOOPBACK_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_LOOPBACK_CFG(gi)            VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,16)

/**
 * \brief
 * Used for Down-MEP only - has no effect for Up-MEP.When a PDU Message is
 * looped to a PDU Reply, the ISDX for the PDU Reply will be changed to the
 * value configured in: * LB_ISDXWhen the Reply passes through the REW, the
 * value in this register will overwrite the IFH.FWD.ES0_ISDX_KEY_ENA.This
 * allows the value of IFH.FWD.ES0_ISDX_KEY_ENA to reflect the new ISDX of
 * the frame.Hence using this bit field it is possible to configure whether
 * the PDU Message will use ISDX for the ES0 lookup.This is relevant for
 * the following PDU types: * LMM --> LMR * SLM --> SLR * DMM --> DMR * LBM
 * --> LBR
 *
 * \details
 * Field: ::VTSS_VOP_LOOPBACK_CFG . LB_ES0_ISDX_ENA
 */
#define  VTSS_F_VOP_LOOPBACK_CFG_LB_ES0_ISDX_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_LOOPBACK_CFG_LB_ES0_ISDX_ENA  VTSS_BIT(13)
#define  VTSS_X_VOP_LOOPBACK_CFG_LB_ES0_ISDX_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * All valid OAM messages (LBM, DMM, LMM, SLM) which are looped back into
 * OAM replies (LBR, DMR, LMR, SLR) will be forwarded in the return
 * direction with the ISDX value configured in this register.
 *
 * \details
 * Valid ISDX value: 1-1023
 *
 * Field: ::VTSS_VOP_LOOPBACK_CFG . LB_ISDX
 */
#define  VTSS_F_VOP_LOOPBACK_CFG_LB_ISDX(x)   VTSS_ENCODE_BITFIELD(x,1,10)
#define  VTSS_M_VOP_LOOPBACK_CFG_LB_ISDX      VTSS_ENCODE_BITMASK(1,10)
#define  VTSS_X_VOP_LOOPBACK_CFG_LB_ISDX(x)   VTSS_EXTRACT_BITFIELD(x,1,10)

/**
 * \brief
 * When OAM PDUs are looped, the DP bits can be cleared or keep their value
 * depending on the setting of this bit.This only affects frames being
 * looped: * LBM --> LBR * LMM --> LMR * DMM --> DMR * SLM --> SLR
 *
 * \details
 * 0: DP bits to be looped with the frame.
 * 1: DP bits are cleared when frame is looped.
 *
 * Field: ::VTSS_VOP_LOOPBACK_CFG . CLEAR_DP_ON_LOOP
 */
#define  VTSS_F_VOP_LOOPBACK_CFG_CLEAR_DP_ON_LOOP(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_LOOPBACK_CFG_CLEAR_DP_ON_LOOP  VTSS_BIT(0)
#define  VTSS_X_VOP_LOOPBACK_CFG_CLEAR_DP_ON_LOOP(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configures updating sequence numbers / transactions ID (TX)
 *
 * \details
 * The configuration in this register group determines whether the VOE will
 * update the sequence number / transaction ID for valid Tx frames.
 *
 * Register: \a VOP:VOE_CONF:TX_TRANSID_UPDATE
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_TX_TRANSID_UPDATE(gi)       VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,17)

/**
 * \brief
 * If asserted, the transaction ID will be updated for valid LBM frames
 * transmitted by this VOE.This can be used to avoid overwriting the Tx ID
 * for externally generated LBM frames.
 *
 * \details
 * Field: ::VTSS_VOP_TX_TRANSID_UPDATE . LBM_UPDATE_ENA
 */
#define  VTSS_F_VOP_TX_TRANSID_UPDATE_LBM_UPDATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_TX_TRANSID_UPDATE_LBM_UPDATE_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_TX_TRANSID_UPDATE_LBM_UPDATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * If asserted, the transaction ID will be updated for valid TST frames
 * transmitted by this VOE.This can be used to avoid overwriting the Tx ID
 * for externally generated TST frames.
 *
 * \details
 * Field: ::VTSS_VOP_TX_TRANSID_UPDATE . TST_UPDATE_ENA
 */
#define  VTSS_F_VOP_TX_TRANSID_UPDATE_TST_UPDATE_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_TX_TRANSID_UPDATE_TST_UPDATE_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_TX_TRANSID_UPDATE_TST_UPDATE_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Miscellaneous CCM configuration
 *
 * \details
 * Misc configuration for CCM(-LM) PDU handling.
 *
 * Register: \a VOP:VOE_CONF:CCM_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CCM_CFG(gi)                 VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,18)

/**
 * \brief
 * The VOE inserts LM information into Tx CCM frames injected by internal
 * or external CPU if the following bit field is asserted. *
 * VOP:VOE_STAT:CCM_STAT.CCM_LM_INSERT_NXTThis is known as LM insertion.The
 * VOE clears this bit field, when inserting LM information into a Tx CCM
 * PDU.The assertion of this bit field can be done either by the CPU or
 * automatically based on LOC timeout counter expiry.To enable automatic LM
 * insertion a LOC timeout counter must be assigned for LM insertion, by
 * programming the number of the LOC timeout counter into this field.Every
 * second time the configured LOC timeout counter expires, the above bit
 * field will be asserted.This configuration will NOT affect the CCM PDU
 * period field.The rate at which LM information is inserted is the rate
 * indicated by the LOC_PERIOD_VAL of the selected timeout counter.I.e. if
 * the VOP::LOC_PERIOD_CFG.LOC_PERIOD_VAL of the selected timeout counter
 * is set to 10 ms, LM information will be inserted every 10 ms.Note:
 * VOP:VOE_CONF:OAM_HW_CTRL.CCM_LM_ENA must be asserted prior to
 * configuring this register.
 *
 * \details
 * 0: Disable automatic insertion of Loss Measurements in OAM CCM PDU
 * n: Automatic insertion of Loss Measurements in next OAM CCM PDU when the
 * corresponding VOP::LOC_PERIOD_CFG occurs.
 *
 * Field: ::VTSS_VOP_CCM_CFG . CCM_LM_PERIOD
 */
#define  VTSS_F_VOP_CCM_CFG_CCM_LM_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_VOP_CCM_CFG_CCM_LM_PERIOD     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_VOP_CCM_CFG_CCM_LM_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * If asserted, the sequence number will be updated for CCM frames
 * transmitted from this VOE.The CCM sequence number of transmitted
 * CCM(-LM) frames will be overwritten with the value configured in the
 * following bit field: * VOP:VOE_STAT:CCM_TX_SEQ_CFG.CCM_TX_SEQ(Note that
 * the above register is always updated +1 when the VOE transmits a valid
 * CCM(-LM) PDU)
 *
 * \details
 * Field: ::VTSS_VOP_CCM_CFG . CCM_SEQ_UPD_ENA
 */
#define  VTSS_F_VOP_CCM_CFG_CCM_SEQ_UPD_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_CCM_CFG_CCM_SEQ_UPD_ENA   VTSS_BIT(11)
#define  VTSS_X_VOP_CCM_CFG_CCM_SEQ_UPD_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * If asserted, the sequence number of valid CCM(-LM) frames received by
 * the VOE is validated against the expected value.The expected value is
 * the value of the following bit field + 1: *
 * VOP:VOE_STAT:CCM_RX_SEQ_CFG.CCM_RX_SEQWhen a valid CCM(-LM) PDU is
 * received by the VOE, the value of the CCM(-LM).sequence_number is stored
 * in the above bit field.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_CFG . CCM_RX_SEQ_CHK_ENA
 */
#define  VTSS_F_VOP_CCM_CFG_CCM_RX_SEQ_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_CCM_CFG_CCM_RX_SEQ_CHK_ENA  VTSS_BIT(10)
#define  VTSS_X_VOP_CCM_CFG_CCM_RX_SEQ_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Configures expected priority of CCM(-LM) frames received by the VOE.The
 * VOE will verify the priority of valid incoming CCM(-LM) PDUs against
 * this value.If the PRIO validation fails the following sticky bit is
 * asserted: * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_PRIO_DEFECTAn interrupt
 * can optionally be generated when the state of the CCM PRIO verification
 * changes: * VOP:VOE_STAT:INTR_STICKY.CCM_UNEXP_PRIO_STICKYNote that a
 * CCM(-LM) frame is valid even when the CCM PRIO verification fails.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_CFG . CCM_PRIO
 */
#define  VTSS_F_VOP_CCM_CFG_CCM_PRIO(x)       VTSS_ENCODE_BITFIELD(x,7,3)
#define  VTSS_M_VOP_CCM_CFG_CCM_PRIO          VTSS_ENCODE_BITMASK(7,3)
#define  VTSS_X_VOP_CCM_CFG_CCM_PRIO(x)       VTSS_EXTRACT_BITFIELD(x,7,3)

/**
 * \brief
 * This bitfield serves two
 * purposes:------------------------------------------------------------ *
 * Configures expected CCM period. * Assigns a LOC counter which will
 * increment the LOC miss counter.The PERIOD fields of the valid incoming
 * CCM frames will be checked against this value.If the PERIOD verification
 * fails the following sticky bit is asserted: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_PERIOD_DEFECTAn interrupt can
 * optionally be generated when the state of the CCM PERIOD verification
 * changes: * VOP:VOE_STAT:INTR_STICKY.CCM_UNEXP_PERIOD_STICKYThe LOC
 * counter is assigned as indicated in the 'Encoding field'.Note:If the
 * PERIOD verification fails, the frame is marked as invalid.
 *
 * \details
 * 0: LOC counter is not incremented. (Zero is an illegal period value)
 * 1: LOC counter is incremented by LOC timeout counter 0 (Verify period ==
 * 1)
 * 2: LOC counter is incremented by LOC timeout counter 1 (Verify period ==
 * 2)
 * 3: LOC counter is incremented by LOC timeout counter 2 (Verify period ==
 * 3)
 * 4: LOC counter is incremented by LOC timeout counter 3 (Verify period ==
 * 4)
 * 5: LOC counter is incremented by LOC timeout counter 4 (Verify period ==
 * 5)
 * 6: LOC counter is incremented by LOC timeout counter 5 (Verify period ==
 * 6)
 * 7: LOC counter is incremented by LOC timeout counter 6 (Verify period ==
 * 7)
 *
 * Field: ::VTSS_VOP_CCM_CFG . CCM_PERIOD
 */
#define  VTSS_F_VOP_CCM_CFG_CCM_PERIOD(x)     VTSS_ENCODE_BITFIELD(x,4,3)
#define  VTSS_M_VOP_CCM_CFG_CCM_PERIOD        VTSS_ENCODE_BITMASK(4,3)
#define  VTSS_X_VOP_CCM_CFG_CCM_PERIOD(x)     VTSS_EXTRACT_BITFIELD(x,4,3)

/**
 * \brief
 * Configures if the VOE will validate the MEG ID of valid incoming
 * CCM(-LM) PDUs against the valued configured in:  *
 * VOP:VOE_CONF:CCM_MEGID_CFG.CCM_MEGIDIf the MEGID verification fails the
 * following sticky bit is asserted: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_MEGID_DEFECTAn interrupt can
 * optionally be generated when the state of the CCM MEGID verification
 * changes: * VOP:VOE_STAT:INTR_STICKY.CCM_UNEXP_MEGID_STICKYIf the MEGID
 * verification fails, the frame is marked as invalid.
 *
 * \details
 * 0: No MEGID check
 * 1: Check MEG ID
 *
 * Field: ::VTSS_VOP_CCM_CFG . CCM_MEGID_CHK_ENA
 */
#define  VTSS_F_VOP_CCM_CFG_CCM_MEGID_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CCM_CFG_CCM_MEGID_CHK_ENA  VTSS_BIT(3)
#define  VTSS_X_VOP_CCM_CFG_CCM_MEGID_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * If this bit is asserted, the value of the MEP ID in incoming CCM frames
 * will be verified against the value programmed in: *
 * VOP:VOE_CONF:PEER_MEPID_CFG.PEER_MEPIDIf the MEPID verification fails
 * the following sticky bit is asserted: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_MEPID_DEFECTAn interrupt can
 * optionally be generated when the state of the CCM MEPID verification
 * changes: * VOP:VOE_STAT:INTR_STICKY.CCM_UNEXP_MEPID_STICKYIf the MEPID
 * verification fails, the frame is marked as invalid.
 *
 * \details
 * 0: No MEPID check
 * 1: Check MEP ID
 *
 * Field: ::VTSS_VOP_CCM_CFG . CCM_MEPID_CHK_ENA
 */
#define  VTSS_F_VOP_CCM_CFG_CCM_MEPID_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CCM_CFG_CCM_MEPID_CHK_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_CCM_CFG_CCM_MEPID_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * If this bit is asserted, the value of the PERIOD field in incoming CCM
 * frames will be verified against the value programmed in: *
 * VOP:VOE_CONF:CCM_CFG.CCM_PERIODIf the PERIOD verification fails the
 * following sticky bit is asserted: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_PERIOD_DEFECTAn interrupt can
 * optionally be generated when the state of the CCM PERIOD verification
 * changes: * VOP:VOE_STAT:INTR_STICKY.CCM_UNEXP_PERIOD_STICKYIf the PERIOD
 * verification fails, the frame is marked as invalid.
 *
 * \details
 * 0: No PERIOD check
 * 1: Check PERIOD
 *
 * Field: ::VTSS_VOP_CCM_CFG . CCM_PERIOD_CHK_ENA
 */
#define  VTSS_F_VOP_CCM_CFG_CCM_PERIOD_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CCM_CFG_CCM_PERIOD_CHK_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_CCM_CFG_CCM_PERIOD_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * If this bit is asserted, the DMAC check will be disabled for CCM(-LM)
 * PDUs, regardless of the configuration of the bit
 * field:VOP:VOE_CONF:VOE_CTRL.RX_DMAC_CHK_SELThe CCM reception process in
 * G.8021 does not include DMAC check.
 *
 * \details
 * 0: No CCM(-LM) DMAC check
 * 1: Check CCM(-LM) DMAC
 *
 * Field: ::VTSS_VOP_CCM_CFG . CCM_RX_DMAC_CHK_ENA
 */
#define  VTSS_F_VOP_CCM_CFG_CCM_RX_DMAC_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CCM_CFG_CCM_RX_DMAC_CHK_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_CCM_CFG_CCM_RX_DMAC_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configuration of CCM MEGID
 *
 * \details
 * Configures 48 byte MEG ID (lowest replication index correspond to MSB)
 * to be verified in incoming CCM(-LM) frames.
 *
 * In case MEG ID verification is enabled
 * (VOP:VOE_CONF:CCM_CFG.CCM_MEGID_CHK_ENA = 1) the value of the CCM.MEGID
 * field of incoming CCM(-LM) frames will be verified against the value
 * configured in this register.
 *
 * If there is a mismatch, the following bit will be asserted:
 *
 *  * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_MEGID_DEFECT
 *
 * When the above bit changes value, the VOE optionally generates an
 * interrupt.
 *
 * Register: \a VOP:VOE_CONF:CCM_MEGID_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 * @param ri Register: CCM_MEGID_CFG (??), 0-11
 */
#define VTSS_VOP_CCM_MEGID_CFG(gi,ri)        VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,ri,19)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_MEGID_CFG . CCM_MEGID
 */
#define  VTSS_F_VOP_CCM_MEGID_CFG_CCM_MEGID(x)  (x)
#define  VTSS_M_VOP_CCM_MEGID_CFG_CCM_MEGID     0xffffffff
#define  VTSS_X_VOP_CCM_MEGID_CFG_CCM_MEGID(x)  (x)


/**
 * \brief Configurations for Synthetic Loss Measurements
 *
 * \details
 * This register contains miscellaneous configurations for Synthetic Loss
 * Measurement.
 *
 * Register: \a VOP:VOE_CONF:SLM_CONFIG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_SLM_CONFIG(gi)              VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,31)

/**
 * \brief
 * The VOE supports only a single priority (COSID) when configured for
 * SynLM and configured for multiple peers. This register selects the COSID
 * to count.When configured for a single peer, the COSID configured in this
 * field selects the COSID for which to increment *
 * VOP:VOE_STAT:SLM_TX_FRM_CNT.SLM_TX_FRM_CNTfor transmitted SLM/1SL
 * frames. The counter will not be incremented for transmitted SLM/1SL
 * frames with other COSIDs.
 *
 * \details
 * Field: ::VTSS_VOP_SLM_CONFIG . SLM_PRIO
 */
#define  VTSS_F_VOP_SLM_CONFIG_SLM_PRIO(x)    VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_SLM_CONFIG_SLM_PRIO       VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_SLM_CONFIG_SLM_PRIO(x)    VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief SynLM Initiator Test ID
 *
 * \details
 * A SynLM session is identified by a SynLM Test ID.
 *
 * The VOE supports a single Test ID for each Initiator function.
 * The Initiator function will validate the Test ID of incoming SLR PDUs.
 * If the Test ID of the incoming SLR PDU doest not match the value
 * configured in this register, the frame will be considered invalid and
 * the following sticky bit is asserted:
 *
 *  * VOP:VOE_STAT:OAM_RX_STICKY2.RX_SLM_TESTID_ERR_STICKY
 *
 * The VOE will not verify the Test ID in incoming PDUs when acting as a
 * Remote MEP.
 *
 * Register: \a VOP:VOE_CONF:SLM_TEST_ID
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_SLM_TEST_ID(gi)             VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,32)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_SLM_TEST_ID . SLM_TEST_ID
 */
#define  VTSS_F_VOP_SLM_TEST_ID_SLM_TEST_ID(x)  (x)
#define  VTSS_M_VOP_SLM_TEST_ID_SLM_TEST_ID     0xffffffff
#define  VTSS_X_VOP_SLM_TEST_ID_SLM_TEST_ID(x)  (x)


/**
 * \brief A list of the MEPIDs with which SLM is supported.
 *
 * \details
 * This list can be programmed with up to 8 MEPIDs which identify the peer
 * MEPs which are part of the SynLM session.
 *
 * When a SynLM PDU is processed by the VOE, the VOE will match the MEPID
 * of the peer MEP (found in the SynLM PDU).
 *
 * If a match is found, the VOE will use the index of the row which matches
 * the MEPID to identify which peer MEP the frame is sent to / received
 * from.
 *
 * If multiple peer are enabled, this index is used when updating the Rx /
 * Tx LM counters for a VOE which is enabled for SynLM.
 *
 * If only peer index zero in the list is enabled, the COSID is used when
 * updating the Rx / Tx LM counters for SynLM.
 *
 * Register: \a VOP:VOE_CONF:SLM_PEER_LIST
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 * @param ri Replicator: x_VTSS_OAM_MEP_SLM_PEERS_SUPPORTED (??), 0-7
 */
#define VTSS_VOP_SLM_PEER_LIST(gi,ri)        VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,ri,33)

/**
 * \brief
 * MEPID used to identify the peer MEP from which the SL PDU is received /
 * to which the SL PDU is sent.Only valid if SLM_PEER_ENA = 1
 *
 * \details
 * Field: ::VTSS_VOP_SLM_PEER_LIST . SLM_PEER_MEPID
 */
#define  VTSS_F_VOP_SLM_PEER_LIST_SLM_PEER_MEPID(x)  VTSS_ENCODE_BITFIELD(x,1,13)
#define  VTSS_M_VOP_SLM_PEER_LIST_SLM_PEER_MEPID     VTSS_ENCODE_BITMASK(1,13)
#define  VTSS_X_VOP_SLM_PEER_LIST_SLM_PEER_MEPID(x)  VTSS_EXTRACT_BITFIELD(x,1,13)

/**
 * \brief
 * If enabled, SLM_PEER_MEPID contains a valid MEPID
 *
 * \details
 * Field: ::VTSS_VOP_SLM_PEER_LIST . SLM_PEER_ENA
 */
#define  VTSS_F_VOP_SLM_PEER_LIST_SLM_PEER_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_SLM_PEER_LIST_SLM_PEER_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_SLM_PEER_LIST_SLM_PEER_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Configuration of G.8113.1 OAM
 *
 * \details
 * Register contains bit for configuring the G.8113.1 functionality of the
 * VOE.
 *
 * Configuration only has effect if the VOE is configured for G.8113.1 OAM.
 *
 *  * VOP:VOE_CONF:VOE_CTRL.G_8113_1_ENA
 *
 * Register: \a VOP:VOE_CONF:G_8113_1_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_G_8113_1_CFG(gi)            VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,41)

/**
 * \brief
 * When running G.8113 LBM / LBR there are two phases:Discovery
 * phase.----------------------------'Initiator MEPs' transmit Discovery
 * 'Target MEP ID' TLVs to the peers (MIPs / MEP) on the MPLS
 * connection.The peers will respond with 'Replying MEP ID' TLVs including
 * their MIP / MEP identification.In this phase the 'Initiator MEP' cannot
 * verify the incoming 'Replying MEP ID' TLVs.When configured for
 * 'Discovery', the 'Initiator VOE' will discard incoming Discovery TLVs
 * (ID Sub-Type: 0, 1)The following sticky bit is asserted: *
 * VOP:VOE_STAT:OAM_RX_STICKY2.G_8113_1_LBX_RX_ILLEGAL_SUBTYPE_STICKYDiscar
 * ded frames can optionally be extracted to the CPU error queue: *
 * VOP:VOE_STAT:PDU_EXTRACT.G_8113_1_LBR_RX_ERR_EXTRAll other TLVs are
 * accepted without further verification and can optionally be extracted
 * the CPU for peer MEP identification. *
 * VOP:VOE_CONF:OAM_CPU_COPY_CTRL.LBR_CPU_COPY_ENAConnection Verification
 * (CV) phase.-------------------------------------------------Once the MEP
 * is aware the identity of the MIPs, MEP along the MPLS connection, it
 * will transmit LBM PDUs with 'Target MEP ID' TLVs directed at the
 * specific MIPs / MEPs.When receiving the Rx LBR PDUs it must verify that
 * the 'Reponder MIP / MEP' matches the expected peer MIP/MEP.In this phase
 * the VOE can be configured to expect either 'Replying MEP ID' TLV (ID
 * Sub-Type: 2) or 'Replying MIP ID' TLV (ID Sub-Type: 3)If an unexpected
 * ID Sub-Type is received, the frame is marked as invalid and the
 * following sticky bit is asserted: *
 * VOP:VOE_STAT:OAM_RX_STICKY2.G_8113_1_LBX_RX_ILLEGAL_SUBTYPE_STICKYDiscar
 * ded frames can optionally be extracted to the CPU error queue: *
 * VOP:VOE_STAT:PDU_EXTRACT.G_8113_1_LBR_RX_ERR_EXTRWhen an expected ID
 * Sub-Type the contents is validated against the values configured in the
 * VOE as follows:CV - MIP (ID Sub-Type:
 * 3)--------------------------------------------If 'Replying MEP ID TLV'
 * verification is enabled: *
 * VOP:VOE_CONF:G_8113_1_CFG.G_8113_1_LBX_MEXID_CHK_ENAThe VOE will verify
 * the content of the TLV as follows: * TLV.CarrierCode ==
 * G_8113_1_REMOTE_MIPID[13:8] * TLV.NodeID == G_8113_1_REMOTE_MIPID[7:4] *
 * TLV.IfNum == G_8113_1_REMOTE_MIPID[3:0]CV - MEP (ID Sub-Type:
 * 2)---------------------------------------------If 'Replying MEP ID TLV'
 * verification is enabled: *
 * VOP:VOE_CONF:G_8113_1_CFG.G_8113_1_LBX_MEXID_CHK_ENAThe VOE will verify
 * the MEP ID of the incoming LBR 'Replying MEP ID' TLV.If the verification
 * fails (MIP / MEP ID), the frame is marked as invalid. The following
 * sticky bit is asserted: *
 * VOP:VOE_STAT:OAM_RX_STICKY2.G_8113_1_LBX_RX_ILLEGAL_MEXID_STICKYThe
 * frame can optionally be extracted to the CPU error queue: *
 * VOP:VOE_STAT:PDU_EXTRACT.G_8113_1_LBR_RX_ERR_EXTR
 *
 * \details
 * 00: Discovery phase
 * 01: Connection Verification - MIP
 * 10: Connection Verification - MEP
 *
 * Field: ::VTSS_VOP_G_8113_1_CFG . G_8113_1_INITIATOR_FUNCTION
 */
#define  VTSS_F_VOP_G_8113_1_CFG_G_8113_1_INITIATOR_FUNCTION(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_VOP_G_8113_1_CFG_G_8113_1_INITIATOR_FUNCTION     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_VOP_G_8113_1_CFG_G_8113_1_INITIATOR_FUNCTION(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * Determines whether the 'Initator/ Responder 'VOE validates the MEPID /
 * MEGID fields when receiving LBM / LBR PDUs:= 0; Do not verify TLV MIP /
 * MEP / MEG IDs.= 1; Verify TLV MIP / MEP / MEG IDs.The fields to be
 * verified are as follows:'Responder MEP':------------------------------*
 * LBM.TargetID.MEPID* LBM.Requesting.MEPID (if present)*
 * LBM.Requesting.MEGID (if present)'Initiator
 * MEP':------------------------------* LBR.ReplyingID.MEPID*
 * LBR.Requesting.MEPID (if present)* LBR.Requesting.MEGID (if present)
 *
 * \details
 * 0: Don't verify incoming LBM / LBR TLV MEP / MIP / MEG ID values
 * (G.8113.1)
 * 0: Verify incoming LBM / LBR TLV MEP / MIP / MEG ID values (G.8113.1)
 *
 * Field: ::VTSS_VOP_G_8113_1_CFG . G_8113_1_LBX_MEXID_CHK_ENA
 */
#define  VTSS_F_VOP_G_8113_1_CFG_G_8113_1_LBX_MEXID_CHK_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_G_8113_1_CFG_G_8113_1_LBX_MEXID_CHK_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_G_8113_1_CFG_G_8113_1_LBX_MEXID_CHK_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief G.8113.1 MIP ID verification configuration
 *
 * \details
 * When the G.8113.1 'Initator MEP' is configured for : Connection
 * Verification - MIP:
 *
 *  * VOP:VOE_CONF:G_8113_1_CFG.G_8113_1_INITIATOR_FUNCTION
 *
 * There are 14 bytes in the 'Replying MIP ID' TLV which must be verified.
 * These are configured in this register.
 *
 * I practice the register is split into 4 separate registers:
 *
 *  * G_8113_1_REMOTE_MIPID (32 bits)
 *  * G_8113_1_REMOTE_MIPID1 (32 bits)
 *  * G_8113_1_REMOTE_MIPID2 (32 bits)
 *  * G_8113_1_REMOTE_MIPID3 (16 bits)
 *
 * The below description will assume that these 4 registers are
 * concatenated into one 14 byte long register.
 *
 * The bytes to be verified in the 'Replying MIP ID' TLV are configured as
 * follows:
 *
 *  * LBR.CarrierCode == G_8113_1_REMOTE_MIPID[13:8]
 *  * LBR.NodeID == G_8113_1_REMOTE_MIPID[7:4]
 *  * LBR.IfNum == G_8113_1_REMOTE_MIPID[3:0]
 *
 * Register: \a VOP:VOE_CONF:G_8113_1_REMOTE_MIPID
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_G_8113_1_REMOTE_MIPID(gi)   VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,42)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_G_8113_1_REMOTE_MIPID . G_8113_1_REMOTE_MIPID
 */
#define  VTSS_F_VOP_G_8113_1_REMOTE_MIPID_G_8113_1_REMOTE_MIPID(x)  (x)
#define  VTSS_M_VOP_G_8113_1_REMOTE_MIPID_G_8113_1_REMOTE_MIPID     0xffffffff
#define  VTSS_X_VOP_G_8113_1_REMOTE_MIPID_G_8113_1_REMOTE_MIPID(x)  (x)


/**
 * \brief G.8113.1 MIP ID verification configuration
 *
 * \details
 * When the G.8113.1 'Initator MEP' is configured for : Connection
 * Verification - MIP:
 *
 *  * VOP:VOE_CONF:G_8113_1_CFG.G_8113_1_INITIATOR_FUNCTION
 *
 * There are 14 bytes in the 'Replying MIP ID' TLV which must be verified.
 * These are configured in this register.
 *
 * I practice the register is split into 4 separate registers:
 *
 *  * G_8113_1_REMOTE_MIPID (32 bits)
 *  * G_8113_1_REMOTE_MIPID1 (32 bits)
 *  * G_8113_1_REMOTE_MIPID2 (32 bits)
 *  * G_8113_1_REMOTE_MIPID3 (16 bits)
 *
 * The below description will assume that these 4 registers are
 * concatenated into one 14 byte long register.
 *
 * The bytes to be verified in the 'Replying MIP ID' TLV are configured as
 * follows:
 *
 *  * LBR.CarrierCode == G_8113_1_REMOTE_MIPID[13:8]
 *  * LBR.NodeID == G_8113_1_REMOTE_MIPID[7:4]
 *  * LBR.IfNum == G_8113_1_REMOTE_MIPID[3:0]
 *
 * Register: \a VOP:VOE_CONF:G_8113_1_REMOTE_MIPID1
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_G_8113_1_REMOTE_MIPID1(gi)  VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,43)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_G_8113_1_REMOTE_MIPID1 . G_8113_1_REMOTE_MIPID1
 */
#define  VTSS_F_VOP_G_8113_1_REMOTE_MIPID1_G_8113_1_REMOTE_MIPID1(x)  (x)
#define  VTSS_M_VOP_G_8113_1_REMOTE_MIPID1_G_8113_1_REMOTE_MIPID1     0xffffffff
#define  VTSS_X_VOP_G_8113_1_REMOTE_MIPID1_G_8113_1_REMOTE_MIPID1(x)  (x)


/**
 * \brief G.8113.1 MIP ID verification configuration
 *
 * \details
 * When the G.8113.1 'Initator MEP' is configured for : Connection
 * Verification - MIP:
 *
 *  * VOP:VOE_CONF:G_8113_1_CFG.G_8113_1_INITIATOR_FUNCTION
 *
 * There are 14 bytes in the 'Replying MIP ID' TLV which must be verified.
 * These are configured in this register.
 *
 * I practice the register is split into 4 separate registers:
 *
 *  * G_8113_1_REMOTE_MIPID (32 bits)
 *  * G_8113_1_REMOTE_MIPID1 (32 bits)
 *  * G_8113_1_REMOTE_MIPID2 (32 bits)
 *  * G_8113_1_REMOTE_MIPID3 (16 bits)
 *
 * The below description will assume that these 4 registers are
 * concatenated into one 14 byte long register.
 *
 * The bytes to be verified in the 'Replying MIP ID' TLV are configured as
 * follows:
 *
 *  * LBR.CarrierCode == G_8113_1_REMOTE_MIPID[13:8]
 *  * LBR.NodeID == G_8113_1_REMOTE_MIPID[7:4]
 *  * LBR.IfNum == G_8113_1_REMOTE_MIPID[3:0]
 *
 * Register: \a VOP:VOE_CONF:G_8113_1_REMOTE_MIPID2
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_G_8113_1_REMOTE_MIPID2(gi)  VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,44)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_G_8113_1_REMOTE_MIPID2 . G_8113_1_REMOTE_MIPID2
 */
#define  VTSS_F_VOP_G_8113_1_REMOTE_MIPID2_G_8113_1_REMOTE_MIPID2(x)  (x)
#define  VTSS_M_VOP_G_8113_1_REMOTE_MIPID2_G_8113_1_REMOTE_MIPID2     0xffffffff
#define  VTSS_X_VOP_G_8113_1_REMOTE_MIPID2_G_8113_1_REMOTE_MIPID2(x)  (x)


/**
 * \brief G.8113.1 MIP ID verification configuration
 *
 * \details
 * When the G.8113.1 'Initator MEP' is configured for : Connection
 * Verification - MIP:
 *
 *  * VOP:VOE_CONF:G_8113_1_CFG.G_8113_1_INITIATOR_FUNCTION
 *
 * There are 14 bytes in the 'Replying MIP ID' TLV which must be verified.
 * These are configured in this register.
 *
 * I practice the register is split into 4 separate registers:
 *
 *  * G_8113_1_REMOTE_MIPID (32 bits)
 *  * G_8113_1_REMOTE_MIPID1 (32 bits)
 *  * G_8113_1_REMOTE_MIPID2 (32 bits)
 *  * G_8113_1_REMOTE_MIPID3 (16 bits)
 *
 * The below description will assume that these 4 registers are
 * concatenated into one 14 byte long register.
 *
 * The bytes to be verified in the 'Replying MIP ID' TLV are configured as
 * follows:
 *
 *  * LBR.CarrierCode == G_8113_1_REMOTE_MIPID[13:8]
 *  * LBR.NodeID == G_8113_1_REMOTE_MIPID[7:4]
 *  * LBR.IfNum == G_8113_1_REMOTE_MIPID[3:0]
 *
 * Register: \a VOP:VOE_CONF:G_8113_1_REMOTE_MIPID3
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_G_8113_1_REMOTE_MIPID3(gi)  VTSS_IOREG_IX(VTSS_TO_VOP,0x0,gi,64,0,45)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_G_8113_1_REMOTE_MIPID3 . G_8113_1_REMOTE_MIPID3
 */
#define  VTSS_F_VOP_G_8113_1_REMOTE_MIPID3_G_8113_1_REMOTE_MIPID3(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_G_8113_1_REMOTE_MIPID3_G_8113_1_REMOTE_MIPID3     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_G_8113_1_REMOTE_MIPID3_G_8113_1_REMOTE_MIPID3(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VOP:VOE_STAT
 *
 * Per VOE statistics and counters (Y.1731 OAM)
 */


/**
 * \brief Count selected OAM PDU received by VOE.
 *
 * \details
 * All PDU types can be configured as either selected or non-selected PDUs.
 *
 * This register counts the number of valid Rx OAM PDUs configured as
 * selected PDU type, received by the VOE.
 *
 * Selected OAM PDUs are configured in: VOP:VOE_CONF:OAM_CNT_OAM_CTRL.*
 *
 * Register: \a VOP:VOE_STAT:RX_SEL_OAM_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_RX_SEL_OAM_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,0)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_RX_SEL_OAM_CNT . RX_SEL_OAM_FRM_CNT
 */
#define  VTSS_F_VOP_RX_SEL_OAM_CNT_RX_SEL_OAM_FRM_CNT(x)  (x)
#define  VTSS_M_VOP_RX_SEL_OAM_CNT_RX_SEL_OAM_FRM_CNT     0xffffffff
#define  VTSS_X_VOP_RX_SEL_OAM_CNT_RX_SEL_OAM_FRM_CNT(x)  (x)


/**
 * \brief Count non-selected OAM PDU received by VOE.
 *
 * \details
 * All PDU types can be configured as either selected or non-selected PDUs.
 *
 * This register counts the number of valid Rx OAM PDUs configured as
 * non-selected PDU type.
 *
 * Selected OAM PDUs are configured in: VOP:VOE_CONF:OAM_CNT_OAM_CTRL.*
 *
 * Register: \a VOP:VOE_STAT:RX_OAM_FRM_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_RX_OAM_FRM_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,1)

/**
 * \brief
 * See register description
 *
 * \details
 * Field: ::VTSS_VOP_RX_OAM_FRM_CNT . RX_OAM_FRM_CNT
 */
#define  VTSS_F_VOP_RX_OAM_FRM_CNT_RX_OAM_FRM_CNT(x)  (x)
#define  VTSS_M_VOP_RX_OAM_FRM_CNT_RX_OAM_FRM_CNT     0xffffffff
#define  VTSS_X_VOP_RX_OAM_FRM_CNT_RX_OAM_FRM_CNT(x)  (x)


/**
 * \brief Count selected OAM PDUs transmitted by VOE.
 *
 * \details
 * All PDU types can be configured as either selected or non-selected PDUs.
 *
 * This register counts the number of valid Tx OAM PDUs configured as
 * selected PDU type.
 *
 * Selected OAM PDUs are configured in: VOP:VOE_CONF:OAM_CNT_OAM_CTRL.*
 *
 * Register: \a VOP:VOE_STAT:TX_SEL_OAM_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_TX_SEL_OAM_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,2)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_TX_SEL_OAM_CNT . TX_SEL_OAM_FRM_CNT
 */
#define  VTSS_F_VOP_TX_SEL_OAM_CNT_TX_SEL_OAM_FRM_CNT(x)  (x)
#define  VTSS_M_VOP_TX_SEL_OAM_CNT_TX_SEL_OAM_FRM_CNT     0xffffffff
#define  VTSS_X_VOP_TX_SEL_OAM_CNT_TX_SEL_OAM_FRM_CNT(x)  (x)


/**
 * \brief Count non-selected OAM PDUs transmitted by VOE.
 *
 * \details
 * All PDU types can be configured as either selected or non-selected PDUs.
 *
 * This register counts the number of valid Tx OAM PDUs configured as
 * non-selected PDU type.
 *
 * Selected OAM PDUs are configured in: VOP:VOE_CONF:OAM_CNT_OAM_CTRL.*
 *
 * Register: \a VOP:VOE_STAT:TX_OAM_FRM_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_TX_OAM_FRM_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,3)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_TX_OAM_FRM_CNT . TX_OAM_FRM_CNT
 */
#define  VTSS_F_VOP_TX_OAM_FRM_CNT_TX_OAM_FRM_CNT(x)  (x)
#define  VTSS_M_VOP_TX_OAM_FRM_CNT_TX_OAM_FRM_CNT     0xffffffff
#define  VTSS_X_VOP_TX_OAM_FRM_CNT_TX_OAM_FRM_CNT(x)  (x)


/**
 * \brief Number of valid / invalid CCM(-LM) PDUs received by the VOE.
 *
 * \details
 * Counts the number of valid / invalid Rx OAM CCM PDUs received by the
 * VOE.
 *
 * Valid CCM(-LM) PDUs will clear the CCM_MISS counter.
 *
 * Counters are updated regardless of the value of:
 *
 *  * VOP:VOE_CONF:OAM_HW_CTRL.CCM_ENA
 *  * VOP:VOE_CONF:OAM_HW_CTRL.CCM_LM_ENA
 *
 * Register: \a VOP:VOE_STAT:CCM_RX_FRM_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CCM_RX_FRM_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,4)

/**
 * \brief
 * Counts the number of valid Rx OAM CCM PDUs received by the VOE.Valid
 * CCM(-LM) PDUs will clear the CCM_MISS counter.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_RX_FRM_CNT . CCM_RX_VLD_FC_CNT
 */
#define  VTSS_F_VOP_CCM_RX_FRM_CNT_CCM_RX_VLD_FC_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_VOP_CCM_RX_FRM_CNT_CCM_RX_VLD_FC_CNT     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_VOP_CCM_RX_FRM_CNT_CCM_RX_VLD_FC_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Counts number of Rx invalid CCM(-LM) PDUs received by the VOE.Invalid
 * CCM(-LM) PDUs will not clear the CCM_MISS_CNT.Invalid CCM(-LM) PDUs are
 * defined as the CCM(-LM) PDUs which do not pass VOE Rx validation.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_RX_FRM_CNT . CCM_RX_INVLD_FC_CNT
 */
#define  VTSS_F_VOP_CCM_RX_FRM_CNT_CCM_RX_INVLD_FC_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_CCM_RX_FRM_CNT_CCM_RX_INVLD_FC_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_CCM_RX_FRM_CNT_CCM_RX_INVLD_FC_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Configuration of CCM Sequence number
 *
 * \details
 * Configures CCM Sequence number to be inserted into the next CCM or
 * CCM-LM PDU.
 *
 * The sequence number of valid CCM(-LM) PDUs is overwritten in the Tx
 * direction depending on the configuration of the following bit field:
 *
 *  * VOP:VOE_CONF:CCM_CFG.CCM_SEQ_UPD_ENA
 *
 * Counters are updated regardless of the value of:
 *
 *  * VOP:VOE_CONF:OAM_HW_CTRL.CCM_ENA
 *  * VOP:VOE_CONF:OAM_HW_CTRL.CCM_LM_ENA
 *
 * Register: \a VOP:VOE_STAT:CCM_TX_SEQ_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CCM_TX_SEQ_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,5)

/**
 * \brief
 * See Register Description
 *
 * \details
 * Field: ::VTSS_VOP_CCM_TX_SEQ_CFG . CCM_TX_SEQ
 */
#define  VTSS_F_VOP_CCM_TX_SEQ_CFG_CCM_TX_SEQ(x)  (x)
#define  VTSS_M_VOP_CCM_TX_SEQ_CFG_CCM_TX_SEQ     0xffffffff
#define  VTSS_X_VOP_CCM_TX_SEQ_CFG_CCM_TX_SEQ(x)  (x)


/**
 * \brief Latest Rx CCM Sequence number
 *
 * \details
 * This register contains the CCM sequence number of the latest valid
 * CCM(-LM) PDU received  by the VOE.
 * The register is automatically updated upon reception of a valid CCM(-LM)
 * PDU.
 *
 * If Rx CCM sequence number checking is enabled, the expected value of the
 * next CCM(-LM) sequence number is the value contained in this register +
 * 1.
 *
 * Rx CCM sequence number checking is enabled using the following bit
 * field:
 *
 *  * VOP:VOE_CONF:CCM_CFG.CCM_SEQ_UPD_ENA
 *
 * Register: \a VOP:VOE_STAT:CCM_RX_SEQ_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CCM_RX_SEQ_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,6)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_RX_SEQ_CFG . CCM_RX_SEQ
 */
#define  VTSS_F_VOP_CCM_RX_SEQ_CFG_CCM_RX_SEQ(x)  (x)
#define  VTSS_M_VOP_CCM_RX_SEQ_CFG_CCM_RX_SEQ     0xffffffff
#define  VTSS_X_VOP_CCM_RX_SEQ_CFG_CCM_RX_SEQ(x)  (x)


/**
 * \brief Number of valid CCM(-LM) received with sequence error
 *
 * \details
 * This register contains counters for the following CCM(-LM) PDU warnings:
 *
 *  * Sequence Errors
 *  * Period Errors
 *
 * These counters are only updated when:
 *
 *  * VOP:VOE_CONF:OAM_HW_CTRL.CCM_ENA = 1
 *
 * Frames included in these frame counts are valid CCM(-LM) PDUs.
 *
 * Register: \a VOP:VOE_STAT:CCM_RX_WARNING
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CCM_RX_WARNING(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,7)

/**
 * \brief
 * Number of valid CCM received with sequence number error.Sequence numbers
 * are counted when the CCM.SequenceNumber of a valid CCM PDU is not equal
 * to the previously received sequence number + 1.The previously received
 * CCM_PDU.SequenceNumber is stored in: *
 * VOP:VOE_STAT:CCM_RX_SEQ_CFG.CCM_RX_SEQ
 *
 * \details
 * Field: ::VTSS_VOP_CCM_RX_WARNING . CCM_RX_SEQNO_ERR_CNT
 */
#define  VTSS_F_VOP_CCM_RX_WARNING_CCM_RX_SEQNO_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_CCM_RX_WARNING_CCM_RX_SEQNO_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_CCM_RX_WARNING_CCM_RX_SEQNO_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief CCM MEL error counter
 *
 * \details
 * Counts CCM(-LM) PDUs received with specific CCM errors.
 *
 * Register: \a VOP:VOE_STAT:CCM_ERR
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CCM_ERR(gi)                 VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,8)

/**
 * \brief
 * Number of CCM(-LM) PDUs received with MEL lower than the MEL configured
 * for the VOE.This counter is updated regardless of the value of: *
 * VOP:VOE_CONF:OAM_HW_CTRL.CCM_ENA
 *
 * \details
 * Field: ::VTSS_VOP_CCM_ERR . CCM_RX_MEL_ERR_CNT
 */
#define  VTSS_F_VOP_CCM_ERR_CCM_RX_MEL_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_VOP_CCM_ERR_CCM_RX_MEL_ERR_CNT     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_VOP_CCM_ERR_CCM_RX_MEL_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Number of valid CCM(-LM) received with Period error.The Period of the
 * incoming CCM(-LM) PDUs is checked against the following value:  *
 * VOP:VOE_CONF:CCM_CFG.CCM_PERIOD
 *
 * \details
 * Field: ::VTSS_VOP_CCM_ERR . CCM_RX_PERIOD_ERR_CNT
 */
#define  VTSS_F_VOP_CCM_ERR_CCM_RX_PERIOD_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_CCM_ERR_CCM_RX_PERIOD_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_CCM_ERR_CCM_RX_PERIOD_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief CCM error counter
 *
 * \details
 * Counts CCM(-LM) PDUs received with specific CCM errors.
 *
 * These counters are only updated when:
 *
 *  * VOP:VOE_CONF:OAM_HW_CTRL.CCM_ENA = 1
 *
 * Register: \a VOP:VOE_STAT:CCM_RX_ERR_1
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CCM_RX_ERR_1(gi)            VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,9)

/**
 * \brief
 * Number of CCM(-LM) PDUs received at the correct MEL, but failing the
 * MEGID verification.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_RX_ERR_1 . CCM_RX_MEGID_ERR_CNT
 */
#define  VTSS_F_VOP_CCM_RX_ERR_1_CCM_RX_MEGID_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_VOP_CCM_RX_ERR_1_CCM_RX_MEGID_ERR_CNT     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_VOP_CCM_RX_ERR_1_CCM_RX_MEGID_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \brief
 * Number of CCM(-LM) PDUs received at the correct MEL, but failing the
 * MEPID verification.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_RX_ERR_1 . CCM_RX_MEPID_ERR_CNT
 */
#define  VTSS_F_VOP_CCM_RX_ERR_1_CCM_RX_MEPID_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_CCM_RX_ERR_1_CCM_RX_MEPID_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_CCM_RX_ERR_1_CCM_RX_MEPID_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Configuration of LBM transaction ID.
 *
 * \details
 * This register holds the transaction ID to be inserted into the next
 * valid LBM PDU transmitted by the VOE.
 *
 * LBM Tx frames will be updated with this value if updating is enabled:
 *
 *  * VOP:VOE_CONF:TX_TRANSID_UPDATE.LBM_UPDATE_ENA
 *
 * When updating a Tx LBM frame, the VOE will automatically increment the
 * value of this register by 1.
 *
 * Register: \a VOP:VOE_STAT:LBM_TX_TRANSID_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_LBM_TX_TRANSID_CFG(gi)      VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,10)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_LBM_TX_TRANSID_CFG . LBM_TX_TRANSID
 */
#define  VTSS_F_VOP_LBM_TX_TRANSID_CFG_LBM_TX_TRANSID(x)  (x)
#define  VTSS_M_VOP_LBM_TX_TRANSID_CFG_LBM_TX_TRANSID     0xffffffff
#define  VTSS_X_VOP_LBM_TX_TRANSID_CFG_LBM_TX_TRANSID(x)  (x)


/**
 * \brief LBR PDU TX counter.
 *
 * \details
 * Number of LBR PDUs transmitted by the VOE.
 *
 * This number will be equal to the number of LBM PDUs received by the VOE,
 * assuming that no PDUs were lost during the loop.
 *
 * Register: \a VOP:VOE_STAT:LBR_TX_FRM_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_LBR_TX_FRM_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,11)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_LBR_TX_FRM_CNT . LBR_TX_FRM_CNT
 */
#define  VTSS_F_VOP_LBR_TX_FRM_CNT_LBR_TX_FRM_CNT(x)  (x)
#define  VTSS_M_VOP_LBR_TX_FRM_CNT_LBR_TX_FRM_CNT     0xffffffff
#define  VTSS_X_VOP_LBR_TX_FRM_CNT_LBR_TX_FRM_CNT(x)  (x)


/**
 * \brief The latest LBR Transaction ID
 *
 * \details
 * Holds the value of the transaction ID of the last valid expected LBR PDU
 * received by the VOE.
 *
 * When a valid LBR PDU is received by the VOE, it is validated against the
 * value of this register + 1.
 *
 * In case the received Transaction ID does not match the expected, it will
 * result in the assertion of the following sticky bit:
 *
 *  * VOP:VOE_STAT:OAM_RX_STICKY.LBR_TRANSID_ERR_STICKY
 *
 * Further the following error counter is increased:
 *
 *  * VOP:VOE_STAT:LBR_RX_TRANSID_ERR_CNT.LBR_RX_TRANSID_ERR_CNT
 *
 * The register is only updated when:
 *
 *  * VOP:VOE_CONF:OAM_HW_CTRL.LBR_ENA = 1
 *
 * or
 *
 *  * VOP:VOE_CONF:OAM_HW_CTRL.TST_ENA = 1
 *
 * Register: \a VOP:VOE_STAT:LBR_RX_TRANSID_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_LBR_RX_TRANSID_CFG(gi)      VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,12)

/**
 * \brief
 * See bit group description.
 *
 * \details
 * Field: ::VTSS_VOP_LBR_RX_TRANSID_CFG . LBR_RX_TRANSID
 */
#define  VTSS_F_VOP_LBR_RX_TRANSID_CFG_LBR_RX_TRANSID(x)  (x)
#define  VTSS_M_VOP_LBR_RX_TRANSID_CFG_LBR_RX_TRANSID     0xffffffff
#define  VTSS_X_VOP_LBR_RX_TRANSID_CFG_LBR_RX_TRANSID(x)  (x)


/**
 * \brief Count number of received LBR frames
 *
 * \details
 * Counts number of valid LBR PDUs received by the VOE.
 *
 * Register: \a VOP:VOE_STAT:LBR_RX_FRM_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_LBR_RX_FRM_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,13)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_LBR_RX_FRM_CNT . LBR_RX_FRM_CNT
 */
#define  VTSS_F_VOP_LBR_RX_FRM_CNT_LBR_RX_FRM_CNT(x)  (x)
#define  VTSS_M_VOP_LBR_RX_FRM_CNT_LBR_RX_FRM_CNT     0xffffffff
#define  VTSS_X_VOP_LBR_RX_FRM_CNT_LBR_RX_FRM_CNT(x)  (x)


/**
 * \brief Number of valid LBR frames with transaction ID error.
 *
 * \details
 * Counts number of valid OAM LBR PDUs received by the VOE for which the
 * transaction ID differs from the expected value:
 *
 *  * VOP:VOE_STAT:LBR_RX_TRANSID_CFG.LBR_RX_TRANSID + 1
 *
 * When the above counter is increased, the following sticky bit is
 * asserted:
 *
 *  * VOP:VOE_STAT:OAM_RX_STICKY.LBR_TRANSID_ERR_STICKY
 *
 * Register: \a VOP:VOE_STAT:LBR_RX_TRANSID_ERR_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_LBR_RX_TRANSID_ERR_CNT(gi)  VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,14)

/**
 * \brief
 * See register description
 *
 * \details
 * Field: ::VTSS_VOP_LBR_RX_TRANSID_ERR_CNT . LBR_RX_TRANSID_ERR_CNT
 */
#define  VTSS_F_VOP_LBR_RX_TRANSID_ERR_CNT_LBR_RX_TRANSID_ERR_CNT(x)  (x)
#define  VTSS_M_VOP_LBR_RX_TRANSID_ERR_CNT_LBR_RX_TRANSID_ERR_CNT     0xffffffff
#define  VTSS_X_VOP_LBR_RX_TRANSID_ERR_CNT_LBR_RX_TRANSID_ERR_CNT(x)  (x)


/**
 * \brief DM stat counters.
 *
 * \details
 * This register contains counters for the number of valid DM PDUs.
 *
 * The counters are shared between the following PDU types:
 *  * DMM/DMR
 *  * 1DM
 *
 * Register: \a VOP:VOE_STAT:DM_PDU_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_DM_PDU_CNT(gi)              VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,15)

/**
 * \brief
 * Counts the number of valid Tx DMM/1DM PDUs transmitted by the VOE.
 *
 * \details
 * Field: ::VTSS_VOP_DM_PDU_CNT . DMM_TX_PDU_CNT
 */
#define  VTSS_F_VOP_DM_PDU_CNT_DMM_TX_PDU_CNT(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_VOP_DM_PDU_CNT_DMM_TX_PDU_CNT     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_VOP_DM_PDU_CNT_DMM_TX_PDU_CNT(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * Counts the number of valid Rx DMM PDUs received by the VOE.
 *
 * \details
 * Field: ::VTSS_VOP_DM_PDU_CNT . DMM_RX_PDU_CNT
 */
#define  VTSS_F_VOP_DM_PDU_CNT_DMM_RX_PDU_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_VOP_DM_PDU_CNT_DMM_RX_PDU_CNT     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_VOP_DM_PDU_CNT_DMM_RX_PDU_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Counts the number of valid Tx DMR PDUs transmitted by the VOE.
 *
 * \details
 * Field: ::VTSS_VOP_DM_PDU_CNT . DMR_TX_PDU_CNT
 */
#define  VTSS_F_VOP_DM_PDU_CNT_DMR_TX_PDU_CNT(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VOP_DM_PDU_CNT_DMR_TX_PDU_CNT     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VOP_DM_PDU_CNT_DMR_TX_PDU_CNT(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Counts the number of valid Rx DMR/1DM PDUs received by the VOE.
 *
 * \details
 * Field: ::VTSS_VOP_DM_PDU_CNT . DMR_RX_PDU_CNT
 */
#define  VTSS_F_VOP_DM_PDU_CNT_DMR_RX_PDU_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VOP_DM_PDU_CNT_DMR_RX_PDU_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VOP_DM_PDU_CNT_DMR_RX_PDU_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief LM stat counters.
 *
 * \details
 * This register contains counters for the number of valid LM PDUs.
 *
 * The counters are shared between the following PDU types:
 *  * LMM/LMR
 *  * CCM_LM (only counted if CCM_LM_ENA = 1)
 *
 * Counters are updated regardless of the value of the PDU enable signals:
 *  * VOP:VOE_CONF:OAM_HW_CTRL.*
 *
 * Register: \a VOP:VOE_STAT:LM_PDU_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_LM_PDU_CNT(gi)              VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,16)

/**
 * \brief
 * Counts the number of valid Tx LMM / CCM-LM PDUs transmitted by the VOE.
 *
 * \details
 * Field: ::VTSS_VOP_LM_PDU_CNT . LMM_TX_PDU_CNT
 */
#define  VTSS_F_VOP_LM_PDU_CNT_LMM_TX_PDU_CNT(x)  VTSS_ENCODE_BITFIELD(x,24,8)
#define  VTSS_M_VOP_LM_PDU_CNT_LMM_TX_PDU_CNT     VTSS_ENCODE_BITMASK(24,8)
#define  VTSS_X_VOP_LM_PDU_CNT_LMM_TX_PDU_CNT(x)  VTSS_EXTRACT_BITFIELD(x,24,8)

/**
 * \brief
 * Counts the number of valid Rx LMM PDUs received by the VOE.
 *
 * \details
 * Field: ::VTSS_VOP_LM_PDU_CNT . LMM_RX_PDU_CNT
 */
#define  VTSS_F_VOP_LM_PDU_CNT_LMM_RX_PDU_CNT(x)  VTSS_ENCODE_BITFIELD(x,16,8)
#define  VTSS_M_VOP_LM_PDU_CNT_LMM_RX_PDU_CNT     VTSS_ENCODE_BITMASK(16,8)
#define  VTSS_X_VOP_LM_PDU_CNT_LMM_RX_PDU_CNT(x)  VTSS_EXTRACT_BITFIELD(x,16,8)

/**
 * \brief
 * Counts the number of valid Tx LMR PDUs transmitted by the VOE.
 *
 * \details
 * Field: ::VTSS_VOP_LM_PDU_CNT . LMR_TX_PDU_CNT
 */
#define  VTSS_F_VOP_LM_PDU_CNT_LMR_TX_PDU_CNT(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VOP_LM_PDU_CNT_LMR_TX_PDU_CNT     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VOP_LM_PDU_CNT_LMR_TX_PDU_CNT(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * Counts the number of valid Rx LMR / CCM-LM PDUs received by the VOE.
 *
 * \details
 * Field: ::VTSS_VOP_LM_PDU_CNT . LMR_RX_PDU_CNT
 */
#define  VTSS_F_VOP_LM_PDU_CNT_LMR_RX_PDU_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VOP_LM_PDU_CNT_LMR_RX_PDU_CNT     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VOP_LM_PDU_CNT_LMR_RX_PDU_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief OAM Tx discard counter
 *
 * \details
 * The number of Tx frames discarded by the VOE due to:
 *
 *  * MEL filtering (Blocking in the Tx direction)
 *  * Server layer blocking (aBLK)
 *  * Client layer blocking (LOCK)
 *
 * Register: \a VOP:VOE_STAT:TX_OAM_DISCARD
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_TX_OAM_DISCARD(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,17)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_TX_OAM_DISCARD . TX_FRM_DISCARD_CNT
 */
#define  VTSS_F_VOP_TX_OAM_DISCARD_TX_FRM_DISCARD_CNT(x)  (x)
#define  VTSS_M_VOP_TX_OAM_DISCARD_TX_FRM_DISCARD_CNT     0xffffffff
#define  VTSS_X_VOP_TX_OAM_DISCARD_TX_FRM_DISCARD_CNT(x)  (x)


/**
 * \brief OAM Rx discard counter
 *
 * \details
 * Number of Rx frames discarded by the VOE, due to:
 *
 *  * MEL filtering
 *  * DMAC check
 *  * Version check
 *  * MEL block high
 *  * CCM verification
 *  * AIS/LCK/CSF verification
 *  * SLM/SLR/SL1 verification
 *  * If SAM_SEQ frames are received on a VOE not enabled for SAM_SEQ
 * processing
 *    (See VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG.*)
 *  * Server layer blocking (aBLK)
 *  * Client layer blocking (LOCK)
 *
 * Register: \a VOP:VOE_STAT:RX_OAM_DISCARD
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_RX_OAM_DISCARD(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,18)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_RX_OAM_DISCARD . RX_FRM_DISCARD_CNT
 */
#define  VTSS_F_VOP_RX_OAM_DISCARD_RX_FRM_DISCARD_CNT(x)  (x)
#define  VTSS_M_VOP_RX_OAM_DISCARD_RX_FRM_DISCARD_CNT     0xffffffff
#define  VTSS_X_VOP_RX_OAM_DISCARD_RX_FRM_DISCARD_CNT(x)  (x)


/**
 * \brief Extraction of PDU errors to the CPU_ERR_QU
 *
 * \details
 * Each of the bit fields in this register represent a specific PDU
 * condition, which will cause the next PDU meeting the condition to be
 * copied to the CPU if the matching bit is asserted.
 *
 * All the bits - with the exception of "CCM_RX_CCM_NXT_EXTR" and
 * "RX_TEST_FRM_NXT_EXTR" - are encoded as either "Extract All" or "Hit Me
 * Once" (This is different if auto HMO is enabled for the VOE, see
 * description of HMO below)
 *
 * This depends on the value of bit field:
 *
 *  * EXTRACT_HIT_ME_ONCE
 *
 * If configured for "Hit Me Once" then the VOE will clear the bit, when a
 * PDU which meets the condition has been copied to the CPU.
 *
 * To extract another frame meeting the same condition, the CPU must
 * re-assert the bit.
 *
 * If not configured for "Hit Me Once" the VOE will not clear the
 * extraction bit and all frames matching the condition will be extracted,
 * until the extraction bit is cleared by SW.
 *
 * "CCM_RX_CCM_NXT_EXTR" will always be implemented as "Hit Me Once". If
 * all the CCM(-LM) frames are to be extracted, use the PDU specific
 * extract bits:
 *
 *  * VOP:VOE_CONF:OAM_CPU_COPY_CTRL.*
 *
 * If the VOE is enabled for auto HMO, the registers which are enabled for
 * auto HMO will always be extracted Hit-Me-Once, regardless of the value
 * of :
 *
 *  * EXTRACT_HIT_ME_ONCE
 *
 * Auto HMO is configured in the following register:
 *
 *  * VOP:VOE_STAT:AUTO_HIT_ME_ONCE
 *
 * Register: \a VOP:VOE_STAT:PDU_EXTRACT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_PDU_EXTRACT(gi)             VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,19)

/**
 * \brief
 * Is used to configure whether the following extract bits are implemented
 * as "Hit Me Once" or "Extract all": * CCM_ZERO_PERIOD_RX_ERR_EXTR *
 * RX_MEL_LOW_ERR_EXTR * RX_MEL_HIGH_BLOCK_EXTR * DMAC_RX_ERR_EXTR *
 * PDU_VERSION_RX_ERR_EXTR * CCM_MEGID_RX_ERR_EXTR * CCM_MEPID_RX_ERR_EXTR
 * * CCM_PERIOD_RX_ERR_EXTR * CCM_PRIO_RX_ERR_EXTR *
 * CCM_RX_TLV_NON_ZERO_EXTR * RX_TEST_FRM_NXT_EXTR * TX_BLOCK_ERR_EXTR *
 * SAM_RX_SEQ_ERR_EXTR * SL_ERR_EXTR * AIS_ERR_EXTR * AIS_RX_FRM_NXT_EXTR *
 * LCK_ERR_EXTR * LCK_RX_FRM_NXT_EXTR * CSF_ERR_EXTR * CSF_RX_FRM_NXT_EXTR
 * * G_8113_1_LBM_RX_ERR_EXTR * G_8113_1_LBR_RX_ERR_EXTRThis configuration
 * bit has no effect on the following extraction bit:"CCM_RX_CCM_NXT_EXTR"
 * The above extraction bits can be enabled for 'auto HMO'.When 'auto HMO'
 * is enabled, the extraction is always done 'Hit-Me-Once' regardless of
 * the configuration of the 'EXTRACT_HIT_ME_ONCE' bit field.For information
 * on 'auto HMO' see register group: * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.*
 *
 * \details
 * 0: Extract all frames meeting the condition of the extract bits (Extract
 * all).
 * 1: Extract only the next frame which meets the condition of the extract
 * bits (Hit Me once).
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . EXTRACT_HIT_ME_ONCE
 */
#define  VTSS_F_VOP_PDU_EXTRACT_EXTRACT_HIT_ME_ONCE(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_VOP_PDU_EXTRACT_EXTRACT_HIT_ME_ONCE  VTSS_BIT(23)
#define  VTSS_X_VOP_PDU_EXTRACT_EXTRACT_HIT_ME_ONCE(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * If asserted, all OAM PDUs which assert the following status bit will be
 * extracted to the CPU: * VOP:VOE_STAT:CCM_RX_LAST.CCM_ZERO_PERIOD_ERRPDUs
 * will be extracted to the following CPU queue: *
 * VOP::CPU_EXTR_CFG.CPU_ERR_QU.The extraction will be "Hit Me Once" or
 * "Extract All" depending on the configuration of: * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . CCM_ZERO_PERIOD_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_CCM_ZERO_PERIOD_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_VOP_PDU_EXTRACT_CCM_ZERO_PERIOD_RX_ERR_EXTR  VTSS_BIT(22)
#define  VTSS_X_VOP_PDU_EXTRACT_CCM_ZERO_PERIOD_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * If asserted, all OAM PDUs which assert the following sticky bit will be
 * extracted to the CPU: *
 * VOP:VOE_STAT:OAM_RX_STICKY.RX_MEL_LOW_BLOCK_STICKYPDUs will be extracted
 * to the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU.The
 * extraction will be "Hit Me Once" or "Extract All" depending on the
 * configuration of: * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . RX_MEL_LOW_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_RX_MEL_LOW_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_VOP_PDU_EXTRACT_RX_MEL_LOW_ERR_EXTR  VTSS_BIT(21)
#define  VTSS_X_VOP_PDU_EXTRACT_RX_MEL_LOW_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * If asserted, all OAM PDUs which assert the following status bit will be
 * extracted to the CPU: *
 * VOP:VOE_STAT:OAM_RX_STICKY.RX_MEL_HIGH_BLOCK_STICKYPDUs will be
 * extracted to the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU.The
 * extraction will be "Hit Me Once" or "Extract All" depending on the
 * configuration of: * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . RX_MEL_HIGH_BLOCK_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_RX_MEL_HIGH_BLOCK_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_VOP_PDU_EXTRACT_RX_MEL_HIGH_BLOCK_EXTR  VTSS_BIT(20)
#define  VTSS_X_VOP_PDU_EXTRACT_RX_MEL_HIGH_BLOCK_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * If asserted, all OAM PDUs which assert the following sticky bit will be
 * extracted to the CPU: *
 * VOP:VOE_STAT:OAM_RX_STICKY.DMAC_RX_ERR_STICKYPDUs will be extracted to
 * the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU.The extraction
 * will be "Hit Me Once" or "Extract All" depending on the configuration
 * of: * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . DMAC_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_DMAC_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_VOP_PDU_EXTRACT_DMAC_RX_ERR_EXTR  VTSS_BIT(19)
#define  VTSS_X_VOP_PDU_EXTRACT_DMAC_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * If asserted, all OAM PDUs which assert the following sticky bit will be
 * extracted to the CPU: *
 * VOP:VOE_STAT:OAM_RX_STICKY.PDU_VERSION_RX_ERR_STICKYPDUs will be
 * extracted to the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU.The
 * extraction will be "Hit Me Once" or "Extract All" depending on the
 * configuration of: * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . PDU_VERSION_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_PDU_VERSION_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_VOP_PDU_EXTRACT_PDU_VERSION_RX_ERR_EXTR  VTSS_BIT(18)
#define  VTSS_X_VOP_PDU_EXTRACT_PDU_VERSION_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * If asserted, all OAM PDUs which assert the following status bit will be
 * extracted to the CPU: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_MEGID_DEFECTPDUs will be extracted to
 * the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU.The extraction
 * will be "Hit Me Once" or "Extract All" depending on the configuration
 * of: * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . CCM_MEGID_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_CCM_MEGID_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_VOP_PDU_EXTRACT_CCM_MEGID_RX_ERR_EXTR  VTSS_BIT(17)
#define  VTSS_X_VOP_PDU_EXTRACT_CCM_MEGID_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * If asserted, all OAM PDUs which assert the following status bit will be
 * extracted to the CPU: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_MEPID_DEFECTPDUs will be extracted to
 * the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU.The extraction
 * will be "Hit Me Once" or "Extract All" depending on the configuration
 * of: * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . CCM_MEPID_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_CCM_MEPID_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_PDU_EXTRACT_CCM_MEPID_RX_ERR_EXTR  VTSS_BIT(16)
#define  VTSS_X_VOP_PDU_EXTRACT_CCM_MEPID_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * If asserted, all OAM PDUs which assert the following status bit will be
 * extracted to the CPU: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_PERIOD_DEFECTPDUs will be extracted
 * to the following CPU queue:CCM:--------------- *
 * VOP::CPU_EXTR_CFG_1.CCM_CPU_QU.CCM-LM:--------------- *
 * VOP::CPU_EXTR_CFG_1.CCM_LM_CPU_QU.The extraction will be "Hit Me Once"
 * or "Extract All" depending on the configuration of: *
 * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . CCM_PERIOD_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_CCM_PERIOD_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_PDU_EXTRACT_CCM_PERIOD_RX_ERR_EXTR  VTSS_BIT(15)
#define  VTSS_X_VOP_PDU_EXTRACT_CCM_PERIOD_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * If asserted, all OAM PDUs which assert the following status bit will be
 * extracted to the CPU: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_PRIO_DEFECTPDUs will be extracted to
 * the following CPU queue:CCM:--------------- *
 * VOP::CPU_EXTR_CFG_1.CCM_CPU_QU.CCM-LM:--------------- *
 * VOP::CPU_EXTR_CFG_1.CCM_LM_CPU_QU.The extraction will be "Hit Me Once"
 * or "Extract All" depending on the configuration of: *
 * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . CCM_PRIO_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_CCM_PRIO_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_PDU_EXTRACT_CCM_PRIO_RX_ERR_EXTR  VTSS_BIT(14)
#define  VTSS_X_VOP_PDU_EXTRACT_CCM_PRIO_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * If asserted, all CCM(-LM) PDUs which assert the following sticky bit
 * will be extracted to the CPU: *
 * VOP:VOE_STAT:OAM_RX_STICKY.CCM_RX_TLV_NON_ZERO_STICKYFrames are
 * extracted to one of the following queues depending on whether the PDU is
 * CCM or CCM-LMCCM:------------ *
 * VOP::CPU_EXTR_CFG_1.CCM_CPU_QUCCM-LM:----------------- *
 * VOP::CPU_EXTR_CFG_1.CCM_LM_CPU_QUThe extraction will be "Hit Me Once" or
 * "Extract All" depending on the configuration of: *
 * EXTRACT_HIT_ME_ONCEThis bit field allows the next CCM frame with Second
 * TLV to CPU. (IEEE802.1AG relevant only).
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . CCM_RX_TLV_NON_ZERO_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_CCM_RX_TLV_NON_ZERO_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_PDU_EXTRACT_CCM_RX_TLV_NON_ZERO_EXTR  VTSS_BIT(13)
#define  VTSS_X_VOP_PDU_EXTRACT_CCM_RX_TLV_NON_ZERO_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * If asserted the next valid CCM(-LM) frame will be extracted to the
 * CPU.Frames are extracted to one of the following queues depending on
 * whether the PDU is CCM or CCM-LMCCM:------------- *
 * VOP::CPU_EXTR_CFG_1.CCM_CPU_QUCCM-LM:------------- *
 * VOP::CPU_EXTR_CFG_1.CCM_LM_CPU_QUThis extraction is always implemented
 * as: "Hit Me Once"
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract next valid CCM PDU to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . CCM_RX_CCM_NXT_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_CCM_RX_CCM_NXT_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_PDU_EXTRACT_CCM_RX_CCM_NXT_EXTR  VTSS_BIT(12)
#define  VTSS_X_VOP_PDU_EXTRACT_CCM_RX_CCM_NXT_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * If asserted by SW, the next valid OAM PDU received of one of the
 * following PDU types will be extracted: * TST * LBR * NON_OAM_MSGOnly the
 * first PDU is extracted, regardless of which of the three PDU types it
 * is.When a PDU has been extracted, the bit will be cleared by the VOE,
 * regardless of the value of: * EXTRACT_HIT_ME_ONCEThe PDU is extracted to
 * the queue assigned to the relevant PDU type in the CPU extract queues.
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . RX_TEST_FRM_NXT_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_RX_TEST_FRM_NXT_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_PDU_EXTRACT_RX_TEST_FRM_NXT_EXTR  VTSS_BIT(11)
#define  VTSS_X_VOP_PDU_EXTRACT_RX_TEST_FRM_NXT_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * If asserted, all OAM PDUs which assert the following sticky bit will be
 * extracted to the CPU: *
 * VOP:VOE_STAT:OAM_TX_STICKY.TX_BLOCK_ERR_STICKYPDUs will be extracted to
 * the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU.The extraction
 * will be "Hit Me Once" or "Extract All" depending on the configuration
 * of: * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . TX_BLOCK_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_TX_BLOCK_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_PDU_EXTRACT_TX_BLOCK_ERR_EXTR  VTSS_BIT(10)
#define  VTSS_X_VOP_PDU_EXTRACT_TX_BLOCK_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Extract non OAM sequence numbered frames in the SAM_SEQ Initiator.Out of
 * sequence non OAM frames is further indicated by asserting the following
 * sticky bit: * VOP:VOE_STAT:OAM_RX_STICKY.LBR_TRANSID_ERR_STICKYThe
 * frames which are extracted due to this bit will depend on the config
 * following configuration: *
 * VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG.SAM_SEQ_RX_ERR_CNT_ENAPDUs will be
 * extracted to the following CPU queue: *
 * VOP::CPU_EXTR_CFG_1.LBR_CPU_QUThe extraction will be "Hit Me Once" or
 * "Extract All" depending on the configuration of: * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . SAM_RX_SEQ_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_SAM_RX_SEQ_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_PDU_EXTRACT_SAM_RX_SEQ_ERR_EXTR  VTSS_BIT(9)
#define  VTSS_X_VOP_PDU_EXTRACT_SAM_RX_SEQ_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * If asserted the VOE will extract frames asserting one of the following
 * sticky bits: * VOP:VOE_STAT:OAM_RX_STICKY2.RX_SLM_TESTID_ERR_STICKY *
 * VOP:VOE_STAT:OAM_RX_STICKY2.RX_SLM_PRIO_ERR_STICKY *
 * VOP:VOE_STAT:OAM_RX_STICKY2.RX_SLM_MEPID_ERR_STICKY *
 * VOP:VOE_STAT:OAM_RX_STICKY2.RX_INI_ILLEGAL_MEPID_STICKY *
 * VOP:VOE_STAT:OAM_TX_STICKY.TX_SLM_PRIO_ERR_STICKYThe extraction will be
 * "Hit Me Once" or "Extract All" depending on the configuration of: *
 * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . SL_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_SL_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_PDU_EXTRACT_SL_ERR_EXTR   VTSS_BIT(8)
#define  VTSS_X_VOP_PDU_EXTRACT_SL_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * If asserted the VOE will extract frames asserting the following sticky
 * bit: * VOP:VOE_STAT:INTR_STICKY.AIS_ZERO_PERIOD_STICKYPDUs will be
 * extracted to the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU.The
 * extraction will be "Hit Me Once" or "Extract All" depending on the
 * configuration of: * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . AIS_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_AIS_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_PDU_EXTRACT_AIS_ERR_EXTR  VTSS_BIT(7)
#define  VTSS_X_VOP_PDU_EXTRACT_AIS_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * If asserted, the next valid AIS PDU received will be extracted.PDUs will
 * be extracted to the following CPU queue: *
 * VOP:COMMON:CPU_EXTR_CFG_2.AIS_CPU_QUThe extraction will be "Hit Me Once"
 * or "Extract All" depending on the configuration of: *
 * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . AIS_RX_FRM_NXT_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_AIS_RX_FRM_NXT_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_PDU_EXTRACT_AIS_RX_FRM_NXT_EXTR  VTSS_BIT(6)
#define  VTSS_X_VOP_PDU_EXTRACT_AIS_RX_FRM_NXT_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * If asserted the VOE will extract frames asserting the following sticky
 * bit: * VOP:VOE_STAT:INTR_STICKY.LCK_ZERO_PERIOD_STICKYPDUs will be
 * extracted to the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU.The
 * extraction will be "Hit Me Once" or "Extract All" depending on the
 * configuration of: * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . LCK_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_LCK_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_PDU_EXTRACT_LCK_ERR_EXTR  VTSS_BIT(5)
#define  VTSS_X_VOP_PDU_EXTRACT_LCK_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * If asserted, the next valid LCK PDU received will be extracted.PDUs will
 * be extracted to the following CPU queue: *
 * VOP:COMMON:CPU_EXTR_CFG_2.LCK_CPU_QUThe extraction will be "Hit Me Once"
 * or "Extract All" depending on the configuration of: *
 * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . LCK_RX_FRM_NXT_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_LCK_RX_FRM_NXT_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_PDU_EXTRACT_LCK_RX_FRM_NXT_EXTR  VTSS_BIT(4)
#define  VTSS_X_VOP_PDU_EXTRACT_LCK_RX_FRM_NXT_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * If asserted the VOE will extract frames asserting the following sticky
 * bit: * VOP:VOE_STAT:INTR_STICKY.CSF_ZERO_PERIOD_STICKY *
 * VOP:VOE_STAT:INTR_STICKY.CSF_INVLD_CSF_TYPE_STICKYPDUs will be extracted
 * to the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU.The
 * extraction will be "Hit Me Once" or "Extract All" depending on the
 * configuration of: * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . CSF_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_CSF_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_PDU_EXTRACT_CSF_ERR_EXTR  VTSS_BIT(3)
#define  VTSS_X_VOP_PDU_EXTRACT_CSF_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * If asserted, the next valid CSF PDU received will be extracted.PDUs will
 * be extracted to the following CPU queue: *
 * VOP:COMMON:CPU_EXTR_CFG_2.CSF_CPU_QUThe extraction will be "Hit Me Once"
 * or "Extract All" depending on the configuration of: *
 * EXTRACT_HIT_ME_ONCE
 *
 * \details
 * 0: Do not extract to CPU.
 * 1: Extract frames to CPU.
 *
 * Field: ::VTSS_VOP_PDU_EXTRACT . CSF_RX_FRM_NXT_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_CSF_RX_FRM_NXT_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_PDU_EXTRACT_CSF_RX_FRM_NXT_EXTR  VTSS_BIT(2)
#define  VTSS_X_VOP_PDU_EXTRACT_CSF_RX_FRM_NXT_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Only valid if the VOE is configured for G.8113.1 OAM: *
 * VOP:VOE_CONF:VOE_CTRL.G_8113_1_ENAIf this bit is asserted any LBM Rx PDU
 * which asserts either of the following sticky bits will be extracted to
 * the CPU error queue. *
 * VOP:VOE_STAT:OAM_RX_STICKY2.G_8113_1_LBX_RX_MISSING_TLV_STICKY *
 * VOP:VOE_STAT:OAM_RX_STICKY2.G_8113_1_LBX_RX_ILLEGAL_SUBTYPE_STICKY *
 * VOP:VOE_STAT:OAM_RX_STICKY2.G_8113_1_LBX_RX_ILLEGAL_MEXID_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_PDU_EXTRACT . G_8113_1_LBM_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_G_8113_1_LBM_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_PDU_EXTRACT_G_8113_1_LBM_RX_ERR_EXTR  VTSS_BIT(1)
#define  VTSS_X_VOP_PDU_EXTRACT_G_8113_1_LBM_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Only valid if the VOE is configured for G.8113.1 OAM: *
 * VOP:VOE_CONF:VOE_CTRL.G_8113_1_ENAIf this bit is asserted any LBR Rx PDU
 * which asserts either of the following sticky bits will be extracted to
 * the CPU error queue. *
 * VOP:VOE_STAT:OAM_RX_STICKY2.G_8113_1_LBX_RX_MISSING_TLV_STICKY *
 * VOP:VOE_STAT:OAM_RX_STICKY2.G_8113_1_LBX_RX_ILLEGAL_SUBTYPE_STICKY *
 * VOP:VOE_STAT:OAM_RX_STICKY2.G_8113_1_LBX_RX_ILLEGAL_MEXID_STICKY *
 * VOP:VOE_STAT:OAM_RX_STICKY2.G_8113_1_LBR_RX_ILL_LBK_IND_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_PDU_EXTRACT . G_8113_1_LBR_RX_ERR_EXTR
 */
#define  VTSS_F_VOP_PDU_EXTRACT_G_8113_1_LBR_RX_ERR_EXTR(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_PDU_EXTRACT_G_8113_1_LBR_RX_ERR_EXTR  VTSS_BIT(0)
#define  VTSS_X_VOP_PDU_EXTRACT_G_8113_1_LBR_RX_ERR_EXTR(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Auto assertion of Hit Me Once bits.
 *
 * \details
 * This register configures the VOE for auto Hit-Me-Once (HMO), which
 * allows certain frames to be extracted with regular intervals without CPU
 * interventions.
 *
 * The VOE can be configured to extract certain frames with regular
 * intervals using the 2 HMO scan timers.
 *
 * When a HMO scan is active, the VOE will update the HMO extraction bits
 * which are configured for the active HMO scan, provided that the
 * currently active HMO SLOT matches the HMO SLOT configured for the VOE.
 *
 * HMO scan timer configuration:
 *
 *  * VOP::HMO_TIMER_CFG.*
 *
 * Further the currenly active HMO slot must match:
 *
 *  * VOP:VOE_STAT:AUTO_HIT_ME_ONCE.HMO_SLOT
 *
 * If the current HMO scan matches the HMO_SLOT of an active HMO scan, the
 * VOE will assert the HMO extract bits configured for the active HMO scan.
 *
 * See the detailed description in the bit fields descriptions.
 *
 * Register: \a VOP:VOE_STAT:AUTO_HIT_ME_ONCE
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_AUTO_HIT_ME_ONCE(gi)        VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,20)

/**
 * \brief
 * Determines which of the HMO scan timers that is active for this VOE
 *
 * \details
 * Field: ::VTSS_VOP_AUTO_HIT_ME_ONCE . HMO_SLOT
 */
#define  VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_SLOT(x)  VTSS_ENCODE_BITFIELD(x,26,3)
#define  VTSS_M_VOP_AUTO_HIT_ME_ONCE_HMO_SLOT     VTSS_ENCODE_BITMASK(26,3)
#define  VTSS_X_VOP_AUTO_HIT_ME_ONCE_HMO_SLOT(x)  VTSS_EXTRACT_BITFIELD(x,26,3)

/**
 * \brief
 * If asserted the following bit will be asserted every time the VOE
 * matches the current HMO scan: *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_RX_CCM_NXT_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_AUTO_HIT_ME_ONCE . HMO_CCM_RX_CCM_NXT
 */
#define  VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_CCM_RX_CCM_NXT(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_VOP_AUTO_HIT_ME_ONCE_HMO_CCM_RX_CCM_NXT  VTSS_BIT(25)
#define  VTSS_X_VOP_AUTO_HIT_ME_ONCE_HMO_CCM_RX_CCM_NXT(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * If asserted the following bit will be asserted every time the VOE
 * matches the current HMO scan: *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_RX_TLV_NON_ZERO_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_AUTO_HIT_ME_ONCE . HMO_CCM_RX_TLV_NON_ZERO
 */
#define  VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_CCM_RX_TLV_NON_ZERO(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_VOP_AUTO_HIT_ME_ONCE_HMO_CCM_RX_TLV_NON_ZERO  VTSS_BIT(24)
#define  VTSS_X_VOP_AUTO_HIT_ME_ONCE_HMO_CCM_RX_TLV_NON_ZERO(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * If asserted the following 6 bitfields will be asserted every time the
 * VOE matches the current HMO scan: *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_ZERO_PERIOD_RX_ERR_EXTR *
 * VOP:VOE_STAT:PDU_EXTRACT.RX_MEL_LOW_ERR_EXTR *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_MEGID_RX_ERR_EXTR *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_MEPID_RX_ERR_EXTR *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_PERIOD_RX_ERR_EXTR *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_PRIO_RX_ERR_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_AUTO_HIT_ME_ONCE . HMO_CCM_RX_BAD_NXT
 */
#define  VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_CCM_RX_BAD_NXT(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_VOP_AUTO_HIT_ME_ONCE_HMO_CCM_RX_BAD_NXT  VTSS_BIT(23)
#define  VTSS_X_VOP_AUTO_HIT_ME_ONCE_HMO_CCM_RX_BAD_NXT(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * If asserted the following bit will be asserted every time the VOE
 * matches the current HMO scan: *
 * VOP:VOE_STAT:PDU_EXTRACT.RX_TEST_FRM_NXT_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_AUTO_HIT_ME_ONCE . HMO_RX_TEST_FRM_NXT
 */
#define  VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_RX_TEST_FRM_NXT(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_VOP_AUTO_HIT_ME_ONCE_HMO_RX_TEST_FRM_NXT  VTSS_BIT(22)
#define  VTSS_X_VOP_AUTO_HIT_ME_ONCE_HMO_RX_TEST_FRM_NXT(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * This value will be written to the following register every time the VOE
 * matches the current HMO scan: *
 * VOP:VOE_STAT:SYNLM_EXTRACT.EXTRACT_PEER_RX_SLM
 *
 * \details
 * Field: ::VTSS_VOP_AUTO_HIT_ME_ONCE . HMO_EXTRACT_PEER_RX_SLM
 */
#define  VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_EXTRACT_PEER_RX_SLM(x)  VTSS_ENCODE_BITFIELD(x,14,8)
#define  VTSS_M_VOP_AUTO_HIT_ME_ONCE_HMO_EXTRACT_PEER_RX_SLM     VTSS_ENCODE_BITMASK(14,8)
#define  VTSS_X_VOP_AUTO_HIT_ME_ONCE_HMO_EXTRACT_PEER_RX_SLM(x)  VTSS_EXTRACT_BITFIELD(x,14,8)

/**
 * \brief
 * This value will be written to the following register every time the VOE
 * matches the current HMO scan: *
 * VOP:VOE_STAT:SYNLM_EXTRACT.EXTRACT_PEER_RX_SLR
 *
 * \details
 * Field: ::VTSS_VOP_AUTO_HIT_ME_ONCE . HMO_EXTRACT_PEER_RX_SLR
 */
#define  VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_EXTRACT_PEER_RX_SLR(x)  VTSS_ENCODE_BITFIELD(x,6,8)
#define  VTSS_M_VOP_AUTO_HIT_ME_ONCE_HMO_EXTRACT_PEER_RX_SLR     VTSS_ENCODE_BITMASK(6,8)
#define  VTSS_X_VOP_AUTO_HIT_ME_ONCE_HMO_EXTRACT_PEER_RX_SLR(x)  VTSS_EXTRACT_BITFIELD(x,6,8)

/**
 * \brief
 * If asserted the following bit field will be asserted every time the VOE
 * matches the current HMO scan: * VOP:VOE_STAT:PDU_EXTRACT.AIS_ERR_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_AUTO_HIT_ME_ONCE . HMO_AIS_RX_BAD_NXT
 */
#define  VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_AIS_RX_BAD_NXT(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_AUTO_HIT_ME_ONCE_HMO_AIS_RX_BAD_NXT  VTSS_BIT(5)
#define  VTSS_X_VOP_AUTO_HIT_ME_ONCE_HMO_AIS_RX_BAD_NXT(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * If asserted the following bit will be asserted every time the VOE
 * matches the current HMO scan: *
 * VOP:VOE_STAT:PDU_EXTRACT.AIS_RX_FRM_NXT_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_AUTO_HIT_ME_ONCE . HMO_AIS_RX_FRM_NXT
 */
#define  VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_AIS_RX_FRM_NXT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_AUTO_HIT_ME_ONCE_HMO_AIS_RX_FRM_NXT  VTSS_BIT(4)
#define  VTSS_X_VOP_AUTO_HIT_ME_ONCE_HMO_AIS_RX_FRM_NXT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * If asserted the following bit field will be asserted every time the VOE
 * matches the current HMO scan: * VOP:VOE_STAT:PDU_EXTRACT.LCK_ERR_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_AUTO_HIT_ME_ONCE . HMO_LCK_RX_BAD_NXT
 */
#define  VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_LCK_RX_BAD_NXT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_AUTO_HIT_ME_ONCE_HMO_LCK_RX_BAD_NXT  VTSS_BIT(3)
#define  VTSS_X_VOP_AUTO_HIT_ME_ONCE_HMO_LCK_RX_BAD_NXT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * If asserted the following bit will be asserted every time the VOE
 * matches the current HMO scan: *
 * VOP:VOE_STAT:PDU_EXTRACT.LCK_RX_FRM_NXT_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_AUTO_HIT_ME_ONCE . HMO_LCK_RX_FRM_NXT
 */
#define  VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_LCK_RX_FRM_NXT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_AUTO_HIT_ME_ONCE_HMO_LCK_RX_FRM_NXT  VTSS_BIT(2)
#define  VTSS_X_VOP_AUTO_HIT_ME_ONCE_HMO_LCK_RX_FRM_NXT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * If asserted the following bit field will be asserted every time the VOE
 * matches the current HMO scan: * VOP:VOE_STAT:PDU_EXTRACT.CSF_ERR_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_AUTO_HIT_ME_ONCE . HMO_CSF_RX_BAD_NXT
 */
#define  VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_CSF_RX_BAD_NXT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_AUTO_HIT_ME_ONCE_HMO_CSF_RX_BAD_NXT  VTSS_BIT(1)
#define  VTSS_X_VOP_AUTO_HIT_ME_ONCE_HMO_CSF_RX_BAD_NXT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * If asserted the following bit will be asserted every time the VOE
 * matches the current HMO scan: *
 * VOP:VOE_STAT:PDU_EXTRACT.CSF_RX_FRM_NXT_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_AUTO_HIT_ME_ONCE . HMO_CSF_RX_FRM_NXT
 */
#define  VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_CSF_RX_FRM_NXT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_AUTO_HIT_ME_ONCE_HMO_CSF_RX_FRM_NXT  VTSS_BIT(0)
#define  VTSS_X_VOP_AUTO_HIT_ME_ONCE_HMO_CSF_RX_FRM_NXT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Extraction of SynLM Rx PDUs
 *
 * \details
 * This register allows extraction of SLM/SLR/1SL PDUs received from
 * selected Peer MEPs.
 *
 * Register: \a VOP:VOE_STAT:SYNLM_EXTRACT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_SYNLM_EXTRACT(gi)           VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,21)

/**
 * \brief
 * If asserted, the frame extraction due to a match in the following
 * register: * VOP:VOE_STAT:SYNLM_EXTRACT.EXTRACT_PEER_RX_SLM *
 * VOP:VOE_STAT:SYNLM_EXTRACT.EXTRACT_PEER_RX_SLMwill be done "Hit Me
 * Once"If not asserted all frames matching the above will be extracted to
 * CPU.
 *
 * \details
 * Field: ::VTSS_VOP_SYNLM_EXTRACT . EXTRACT_HMO
 */
#define  VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_HMO(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_SYNLM_EXTRACT_EXTRACT_HMO  VTSS_BIT(16)
#define  VTSS_X_VOP_SYNLM_EXTRACT_EXTRACT_HMO(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * When the Responder MEP enabled for SynLM processes Rx SLM PDUs, they are
 * extracted if so configured in this register.Configuring this register
 * allows for extracting only Rx frames from selected SynLM peer MEPs.The
 * register width is 8. Each bit represents a SynLM peer MEP.The SynLM peer
 * MEP associated with an Rx PDU is determined from matching the MEPID of
 * the Rx SynLM PDU against the configured list of SynLM peer MEPIDs: *
 * VOP:VOE_CONF:SLM_PEER_LIST.SLM_PEER_MEPIDIf the bit (in the current
 * register) representing the SynLM peer index of the Rx frame, the frame
 * is extracted to the CPU.The extraction will be done either extract ALL
 * or extract "Hit Me Once" depending on the value of the following bit
 * field: * VOP:VOE_STAT:SYNLM_EXTRACT.EXTRACT_HMO
 *
 * \details
 * Field: ::VTSS_VOP_SYNLM_EXTRACT . EXTRACT_PEER_RX_SLM
 */
#define  VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM(x)  VTSS_ENCODE_BITFIELD(x,8,8)
#define  VTSS_M_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM     VTSS_ENCODE_BITMASK(8,8)
#define  VTSS_X_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM(x)  VTSS_EXTRACT_BITFIELD(x,8,8)

/**
 * \brief
 * When the Initiator MEP enabled for SynLM processes Rx SLR / 1SL PDUs,
 * they are extracted if so configured in this register.Configuring this
 * register allows for extracting only Rx frames from selected SynLM peer
 * MEPs.The register width is 8. Each bit represents a SynLM peer MEP.The
 * SynLM peer MEP associated with an Rx PDU is determined from matching the
 * MEPID of the Rx SynLM PDU against the configured list of SynLM peer
 * MEPIDs: * VOP:VOE_CONF:SLM_PEER_LIST.SLM_PEER_MEPIDIf the bit (in the
 * current register) representing the SynLM peer index of the Rx frame, the
 * frame is extracted to the CPU.The extraction will be done either extract
 * ALL or extract "Hit Me Once" depending on the value of the following bit
 * field: * VOP:VOE_STAT:SYNLM_EXTRACT.EXTRACT_HMO
 *
 * \details
 * Field: ::VTSS_VOP_SYNLM_EXTRACT . EXTRACT_PEER_RX_SLR
 */
#define  VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR(x)  VTSS_ENCODE_BITFIELD(x,0,8)
#define  VTSS_M_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR     VTSS_ENCODE_BITMASK(0,8)
#define  VTSS_X_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR(x)  VTSS_EXTRACT_BITFIELD(x,0,8)


/**
 * \brief Tx sticky bits
 *
 * \details
 * VOE Tx sticky bits.
 *
 * Register: \a VOP:VOE_STAT:OAM_TX_STICKY
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_OAM_TX_STICKY(gi)           VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,22)

/**
 * \brief
 * This register is asserted if a frame is blocked in the Tx direction due
 * to a MEL value which is too low.A low MEL value will result as one of
 * two
 * conditions:-------------------------------------------------------------
 * -----------------------1) Injection Tx PDUIf an OAM PDU is injected by
 * the CPU in the Tx direction with a MEL different from the MEL configured
 * for the VOE.2) Forwarding Tx PDUIf a frame from a front port (non CPU
 * inject) is forwarded in the Tx direction with a MEL which is equal to or
 * lower that the MEL configured for the VOE.The MEL for the VOE is
 * configured in the following bit field: *
 * VOP:VOE_CONF:VOE_CTRL.MEL_VALThe assertion of this sticky bit depends on
 * the setting of the following bit field: *
 * VOP:VOE_CONF:OAM_CPU_COPY_CTRL.PDU_ERR_EXTRACT_CCM_ONLY
 *
 * \details
 * Field: ::VTSS_VOP_OAM_TX_STICKY . TX_BLOCK_ERR_STICKY
 */
#define  VTSS_F_VOP_OAM_TX_STICKY_TX_BLOCK_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_OAM_TX_STICKY_TX_BLOCK_ERR_STICKY  VTSS_BIT(1)
#define  VTSS_X_VOP_OAM_TX_STICKY_TX_BLOCK_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * If a SynLM PDU is transmitted with a priority (COSID) which is different
 * from the SynLM PRIO configured for the VOE,	*
 * VOP:VOE_CONF:SLM_CONFIG.SLM_PRIOthe frame will be marked as invalid and
 * this sticky bit is asserted.Frames which fail the SynLM priority check
 * can optionally be extracted to the CPU error queue: *
 * VOP:VOE_STAT:PDU_EXTRACT.SL_ERR_EXTRThe priority check and update of
 * this field is only performed when multiple Peer MEPs are enabled: *
 * VOP:VOE_CONF:SLM_PEER_LIST.SLM_PEER_ENA
 *
 * \details
 * Field: ::VTSS_VOP_OAM_TX_STICKY . TX_SLM_PRIO_ERR_STICKY
 */
#define  VTSS_F_VOP_OAM_TX_STICKY_TX_SLM_PRIO_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_OAM_TX_STICKY_TX_SLM_PRIO_ERR_STICKY  VTSS_BIT(0)
#define  VTSS_X_VOP_OAM_TX_STICKY_TX_SLM_PRIO_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Rx Sticky bits
 *
 * \details
 * The sticky bits included in this register can be subdivided into two
 * groups:
 * ------------------------------------------------------------------------
 * --------------------------------------------
 *  * Valid OAM PDUs: Sticky bits which indicate that a valid OAM PDU is
 * received by the VOE.
 *  * Error conditions: The VOE detected a given error condition.
 *
 *
 * Valid OAM PDU sticky bits:
 * ---------------------------------------------------
 * The PDU specific Rx sticky bits:
 *
 *  * "xxx"_RX_STICKY
 *
 * will be asserted even when the PDU is not enabled
 * (VOE_CONF.OAM_HW_CTRL), to allow detecting PDU types which are not
 * expected.
 *
 * Error conditions:
 * -----------------------------------------------------
 * For the remaining sticky bits the VOE will require the PDU type to be
 * enabled, before asserting the sticky bits.
 *
 * The OAM PDU is considered valid when:
 *  * PDU MEL is equal to the VOE MEL.
 *  * DMAC is verified according to VOE configuration
 * (VOP:VOE_CONF:VOE_CTRL.RX_DMAC_CHK_SEL)
 *  * PDU version matches configuration.
 *
 * For CCM(-LM) frames the following checks are performed to validate the
 * PDU:
 *  * Verify MEGID
 *  * Verify MEPID
 *  * Verify Period is non-zero
 *
 * Register: \a VOP:VOE_STAT:OAM_RX_STICKY
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_OAM_RX_STICKY(gi)           VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,23)

/**
 * \brief
 * Asserted when the VOE receives a valid OAM PDU with an OpCode which is
 * detected as UNKNOWN.UNKNOWN OpCode is used for OAM PDU types which do
 * not have dedicated HW support and which is not encoded as a GENERIC PDU.
 *
 * \details
 * '0': No PDU received
 * '1': PDU with UNKNOWN OpCode received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . UNK_OPCODE_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_UNK_OPCODE_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_UNK_OPCODE_RX_STICKY  VTSS_BIT(26)
#define  VTSS_X_VOP_OAM_RX_STICKY_UNK_OPCODE_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \brief
 * Asserted when the VOE receives a valid LTM PDU.
 *
 * \details
 * '0': No valid LTM PDU received
 * '1': Valid LTM PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . LTM_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_LTM_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_LTM_RX_STICKY  VTSS_BIT(25)
#define  VTSS_X_VOP_OAM_RX_STICKY_LTM_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \brief
 * Asserted when the VOE receives a valid LTR PDU
 *
 * \details
 * '0': No valid LTR PDU received
 * '1': Valid LTR PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . LTR_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_LTR_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),24,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_LTR_RX_STICKY  VTSS_BIT(24)
#define  VTSS_X_VOP_OAM_RX_STICKY_LTR_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,24,1)

/**
 * \brief
 * Asserted when the VOE receives a valid LMM PDU
 *
 * \details
 * '0': No valid LMM PDU received
 * '1': Valid LMM PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . LMM_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_LMM_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),23,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_LMM_RX_STICKY  VTSS_BIT(23)
#define  VTSS_X_VOP_OAM_RX_STICKY_LMM_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,23,1)

/**
 * \brief
 * Asserted when the VOE receives a valid LMR PDU
 *
 * \details
 * '0': No valid LMR PDU received
 * '1': Valid LMR PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . LMR_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_LMR_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_LMR_RX_STICKY  VTSS_BIT(22)
#define  VTSS_X_VOP_OAM_RX_STICKY_LMR_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * Asserted when the VOE receives a valid TST PDU
 *
 * \details
 * '0': No valid TST PDU received
 * '1': Valid TST PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . TST_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_TST_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_TST_RX_STICKY  VTSS_BIT(21)
#define  VTSS_X_VOP_OAM_RX_STICKY_TST_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Asserted when the VOE receives a valid LBM PDU
 *
 * \details
 * '0': No valid LBM PDU received
 * '1': Valid LBM PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . LBM_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_LBM_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),20,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_LBM_RX_STICKY  VTSS_BIT(20)
#define  VTSS_X_VOP_OAM_RX_STICKY_LBM_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,20,1)

/**
 * \brief
 * Asserted when the VOE receives a valid LBR PDU
 *
 * \details
 * '0': No valid LBR PDU received
 * '1': Valid LBR PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . LBR_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_LBR_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_LBR_RX_STICKY  VTSS_BIT(19)
#define  VTSS_X_VOP_OAM_RX_STICKY_LBR_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \brief
 * Asserted when the VOE receives a valid DMM PDU
 *
 * \details
 * '0': No valid DMM PDU received
 * '1': Valid DMM PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . DMM_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_DMM_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_DMM_RX_STICKY  VTSS_BIT(18)
#define  VTSS_X_VOP_OAM_RX_STICKY_DMM_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Asserted when the VOE receives a valid DMR PDU
 *
 * \details
 * '0': No valid DMR PDU received
 * '1': Valid DMR PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . DMR_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_DMR_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_DMR_RX_STICKY  VTSS_BIT(17)
#define  VTSS_X_VOP_OAM_RX_STICKY_DMR_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Asserted when the VOE receives a valid 1DM PDU
 *
 * \details
 * '0': No valid 1DM PDU received
 * '1': Valid 1DM PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . SDM_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_SDM_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_SDM_RX_STICKY  VTSS_BIT(16)
#define  VTSS_X_VOP_OAM_RX_STICKY_SDM_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Asserted when the VOE receives a valid CCM PDU.
 *
 * \details
 * '0': No valid CCM PDU received
 * '1': Valid CCM PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . CCM_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_CCM_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_CCM_RX_STICKY  VTSS_BIT(15)
#define  VTSS_X_VOP_OAM_RX_STICKY_CCM_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Asserted when the VOE receives a valid CCM-LM PDU
 *
 * \details
 * '0': No valid CCM-LM PDU received
 * '1': Valid CCM-LM PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . CCM_LM_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_CCM_LM_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_CCM_LM_RX_STICKY  VTSS_BIT(14)
#define  VTSS_X_VOP_OAM_RX_STICKY_CCM_LM_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Asserted when the VOE receives a valid SLM PDU.
 *
 * \details
 * '0': No valid SLM PDU received
 * '1': Valid SLM PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . SLM_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_SLM_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_SLM_RX_STICKY  VTSS_BIT(13)
#define  VTSS_X_VOP_OAM_RX_STICKY_SLM_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Asserted when the VOE receives a valid SLR PDU.
 *
 * \details
 * '0': No valid SLR PDU received
 * '1': Valid SLR PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . SLR_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_SLR_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_SLR_RX_STICKY  VTSS_BIT(12)
#define  VTSS_X_VOP_OAM_RX_STICKY_SLR_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Asserted when the VOE receives a valid 1SL PDU.
 *
 * \details
 * '0': No valid 1SL PDU received
 * '1': Valid 1SL PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . SL1_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_SL1_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_SL1_RX_STICKY  VTSS_BIT(11)
#define  VTSS_X_VOP_OAM_RX_STICKY_SL1_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Asserted when the VOE receives a valid AIS PDU.
 *
 * \details
 * '0': No valid AIS PDU received
 * '1': Valid AIS PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . AIS_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_AIS_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_AIS_RX_STICKY  VTSS_BIT(10)
#define  VTSS_X_VOP_OAM_RX_STICKY_AIS_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Asserted when the VOE receives a valid LCK PDU.
 *
 * \details
 * '0': No valid LCK PDU received
 * '1': Valid LCK PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . LCK_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_LCK_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_LCK_RX_STICKY  VTSS_BIT(9)
#define  VTSS_X_VOP_OAM_RX_STICKY_LCK_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Asserted when the VOE receives a valid CSF PDU.
 *
 * \details
 * '0': No valid CSF PDU received
 * '1': Valid CSF PDU received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . CSF_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_CSF_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_CSF_RX_STICKY  VTSS_BIT(8)
#define  VTSS_X_VOP_OAM_RX_STICKY_CSF_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \brief
 * Sticky bit is asserted when the VOE receives a non OAM frame with
 * sequence number.This requires that the VOE is configured as either
 * SAM_SEQ Initiator:  * VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG.SAM_SEQ_INITor as
 * SAM_SEQ Responder: * VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG.SAM_SEQ_RESPWhen
 * configured for "SAM_SEQ Initiator" this bit indicates reception of
 * NON_OAM_RSP.When configured for "SAM_SEQ Responder" this bit indicates
 * reception of NON_OAM_MSG.
 *
 * \details
 * '0': No valid SAM_SEQ frame received
 * '1': Valid SAM_SEQ frame received
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . NON_OAM_SEQ_RX_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_NON_OAM_SEQ_RX_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_NON_OAM_SEQ_RX_STICKY  VTSS_BIT(7)
#define  VTSS_X_VOP_OAM_RX_STICKY_NON_OAM_SEQ_RX_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Standard LBM/LBR:--------------------------------Valid LBR frame was
 * received with Transaction ID which did not match the expected value of:
 * * VOP:VOE_STAT:LBR_RX_TRANSID_CFG.LBR_RX_TRANSID + 1SAM_SEQ (Non OAM
 * sequence numbering)--------------------------------The assertion of this
 * bit will depend on the following configuration: *
 * VOP:VOE_CONF:SAM_NON_OAM_SEQ_CFG.SAM_SEQ_RX_ERR_CNT_ENA
 *
 * \details
 * 0: No LBR / SAM_SEQ with sequence error was received VOE.
 * 1: LBR / SAM_SEQ with sequence error was received by VOE.
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . LBR_TRANSID_ERR_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_LBR_TRANSID_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_LBR_TRANSID_ERR_STICKY  VTSS_BIT(6)
#define  VTSS_X_VOP_OAM_RX_STICKY_LBR_TRANSID_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * The VOE discarded an Rx OAM PDU with correct MEL, which failed the DMAC
 * check configured in: * VOP:VOE_CONF:VOE_CTRL.RX_DMAC_CHK_SELOAM PDUs
 * failing DMAC check can optionally be extracted using: *
 * VOP:VOE_STAT:PDU_EXTRACT.DMAC_RX_ERR_EXTRFrames failing the DMAC
 * validation can optionally be extracted to the CPU error queue: *
 * VOP::CPU_EXTR_CFG.CPU_ERR_QUThe DMAC check is performed for all PDU
 * types. It is configurable if all PDU types or only for CCM(-LM) PDUs are
 * extracted and cause the assertion of a sticky bit: *
 * VOP:VOE_CONF:OAM_CPU_COPY_CTRL.PDU_ERR_EXTRACT_CCM_ONLY
 *
 * \details
 * 0: No DMAC errors detected.
 * 1: An OAM PDU failed the DMAC check.
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . DMAC_RX_ERR_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_DMAC_RX_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_DMAC_RX_ERR_STICKY  VTSS_BIT(5)
#define  VTSS_X_VOP_OAM_RX_STICKY_DMAC_RX_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Indicates that a OAM PDU was received by the VOE with a Y.1731 version
 * code which is not configured as valid: * VOP::VERSION_CTRL.* *
 * VOP::VERSION_CTRL_2.*Frames with version error are discarded and can
 * optionally be extracted to the CPU using: *
 * VOP:VOE_STAT:PDU_EXTRACT.PDU_VERSION_RX_ERR_EXTRFrames extracted to the
 * CPU due to Y.1731 version error are extracted to the CPU error
 * queue:VOP::CPU_EXTR_CFG.CPU_ERR_QUIt is configurable if the VERSION
 * check is performed for all PDU types or only for CCM(-LM) PDUs using the
 * following bit field: *
 * VOP:VOE_CONF:OAM_CPU_COPY_CTRL.PDU_ERR_EXTRACT_CCM_ONLY
 *
 * \details
 * 0: No PDU with VERSION error received by VOE.
 * 1: PDU with VERSION error received by VOE.

 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . PDU_VERSION_RX_ERR_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_PDU_VERSION_RX_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_PDU_VERSION_RX_ERR_STICKY  VTSS_BIT(4)
#define  VTSS_X_VOP_OAM_RX_STICKY_PDU_VERSION_RX_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * The VOE supports the following two (CCM-LM) TLVs in HW, provided that
 * they are located as the first TLVs after the CCM(-LM) payload. - "Port
 * Status TLV" (see VOP:VOE_STAT:CCM_RX_LAST.TLV_PORT_STATUS) - "Interface
 * Status" (see VOP:VOE_STAT:CCM_RX_LAST.TLV_INTERFACE_STATUS)Indicates
 * that an OAM PDU was received by the VOE with an End TLV which is
 * non-zero.In this context the "End TLV" denotes the first TLV after the
 * CCM(-LM) PDU bypassing the "Port Status TLV" and the "Interface Status
 * TLV" is these are present.This is a valid option according to
 * 802.1ag.The additional TLV following the CCM PDU cannot be processed by
 * the VOE, but frames including such a TLV can be extracted to the CPU,
 * using the following register: *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_RX_TLV_NON_ZERO_EXTRFrames are extracted to
 * one of the following queues depending on whether the PDU is CCM or
 * CCM-LM * VOP::CPU_EXTR_CFG_1.CCM_CPU_QU *
 * VOP::CPU_EXTR_CFG_1.CCM_LM_CPU_QU
 *
 * \details
 * 0: No CCM PDU with non-zero TLV received by the VOE.
 * 1: CCM PDU with non-zero TLV was received by the VOE.
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . CCM_RX_TLV_NON_ZERO_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_CCM_RX_TLV_NON_ZERO_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_CCM_RX_TLV_NON_ZERO_STICKY  VTSS_BIT(3)
#define  VTSS_X_VOP_OAM_RX_STICKY_CCM_RX_TLV_NON_ZERO_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Valid CCM(-LM) PDU with sequence error received by VOE.Only updated when
 * updating the CCM sequence number is enable: *
 * VOP:VOE_CONF:CCM_CFG.CCM_SEQ_UPD_ENAOnly updated when: *
 * VOP:VOE_CONF:OAM_HW_CTRL.CCM_ENA = 1
 *
 * \details
 * 0: No errors detected in the incoming CCM Seq Number.
 * 1: Detected error in the incoming CCM Seq Number.
 *
 * Field: ::VTSS_VOP_OAM_RX_STICKY . CCM_RX_SEQ_ERR_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_CCM_RX_SEQ_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_CCM_RX_SEQ_ERR_STICKY  VTSS_BIT(2)
#define  VTSS_X_VOP_OAM_RX_STICKY_CCM_RX_SEQ_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * An OAM PDU was discarded because it was received by the VOE with MEL
 * which is lower than the MEL value configure for the MEL.All Rx frames
 * are subjected to the MEL verification, however it is configurable if the
 * Rx MEL LOW extraction is done for all PDU types or only for CCM(-LM)
 * PDUs using the following bit field: *
 * VOP:VOE_CONF:OAM_CPU_COPY_CTRL.PDU_ERR_EXTRACT_CCM_ONLY
 *
 * \details
 * Field: ::VTSS_VOP_OAM_RX_STICKY . RX_MEL_LOW_BLOCK_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_RX_MEL_LOW_BLOCK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_RX_MEL_LOW_BLOCK_STICKY  VTSS_BIT(1)
#define  VTSS_X_VOP_OAM_RX_STICKY_RX_MEL_LOW_BLOCK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * This sticky bit is asserted when a frame is discarded because the
 * following option is enabled: * VOP:VOE_CONF:VOE_CTRL.BLOCK_MEL_HIGH_RX
 *
 * \details
 * Field: ::VTSS_VOP_OAM_RX_STICKY . RX_MEL_HIGH_BLOCK_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY_RX_MEL_HIGH_BLOCK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_OAM_RX_STICKY_RX_MEL_HIGH_BLOCK_STICKY  VTSS_BIT(0)
#define  VTSS_X_VOP_OAM_RX_STICKY_RX_MEL_HIGH_BLOCK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Rx Sticky bits - continued
 *
 * \details
 * Rx sticky bits related to SymLM frame verification.
 *
 * Register: \a VOP:VOE_STAT:OAM_RX_STICKY2
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_OAM_RX_STICKY2(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,24)

/**
 * \brief
 * Asserted when the VOE receives a valid OAM PDU with an OpCode which is
 * configured as a GENERIC OPCODE in the following register: *
 * VOP::OAM_GENERIC_CFG.*There is a separate bit to indicate the reception
 * of each of the configured GENERIC OpCodes.
 *
 * \details
 * Field: ::VTSS_VOP_OAM_RX_STICKY2 . GENERIC_RX_STICKY_MASK
 */
#define  VTSS_F_VOP_OAM_RX_STICKY2_GENERIC_RX_STICKY_MASK(x)  VTSS_ENCODE_BITFIELD(x,8,16)
#define  VTSS_M_VOP_OAM_RX_STICKY2_GENERIC_RX_STICKY_MASK     VTSS_ENCODE_BITMASK(8,16)
#define  VTSS_X_VOP_OAM_RX_STICKY2_GENERIC_RX_STICKY_MASK(x)  VTSS_EXTRACT_BITFIELD(x,8,16)

/**
 * \brief
 * The VOE received an SLR frame with a TEST ID which is different from the
 * value programmed for the VOE in the following register: *
 * VOP:VOE_CONF:SLM_TEST_ID.SLM_TEST_IDIf the SLR.TEST_ID does not match
 * the above value, this sticky bit is asserted and the frame is considered
 * invalid.Frames which fail the TEST_ID check can optionally be extracted
 * to the CPU error queue:  * VOP:VOE_STAT:PDU_EXTRACT.SL_ERR_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_OAM_RX_STICKY2 . RX_SLM_TESTID_ERR_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY2_RX_SLM_TESTID_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_OAM_RX_STICKY2_RX_SLM_TESTID_ERR_STICKY  VTSS_BIT(7)
#define  VTSS_X_VOP_OAM_RX_STICKY2_RX_SLM_TESTID_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * The VOE received an SLM/SLR/1SL frame with a priority which is different
 * from the value programmed for the VOE in the following register: *
 * VOP:VOE_CONF:SLM_CONFIG.SLM_PRIOthe frame will be marked as invalid and
 * this sticky bit is asserted.Frames which fail the SynLM priority check
 * can optionally be extracted to the CPU error queue:	*
 * VOP:VOE_STAT:PDU_EXTRACT.SL_ERR_EXTRThe priority check and update of
 * this field is only performed when multiple Peer MEPs are enabled: *
 * VOP:VOE_CONF:SLM_PEER_LIST.SLM_PEER_ENA
 *
 * \details
 * Field: ::VTSS_VOP_OAM_RX_STICKY2 . RX_SLM_PRIO_ERR_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY2_RX_SLM_PRIO_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_OAM_RX_STICKY2_RX_SLM_PRIO_ERR_STICKY  VTSS_BIT(6)
#define  VTSS_X_VOP_OAM_RX_STICKY2_RX_SLM_PRIO_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * When SynLM frames are received from a SynLM peer MEP, the VOE will
 * verify the MEPID of the incoming PDU against the list of valid peer
 * MEPIDs programmed in the VOE: *
 * VOP:VOE_CONF:SLM_PEER_LIST.SLM_PEER_MEPIDIf no match is found, this
 * sticky bit is asserted and the frame is considered invalid.Whether the
 * VOE matches the SRC_MEPID or the RCV_MEPID depends on the PDU type and
 * the direction of the PDU (RX/TX).Frames which fail the SynLM peer MEPID
 * check can optionally be extracted to the CPU error queue:  *
 * VOP:VOE_STAT:PDU_EXTRACT.SL_ERR_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_OAM_RX_STICKY2 . RX_SLM_MEPID_ERR_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY2_RX_SLM_MEPID_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_OAM_RX_STICKY2_RX_SLM_MEPID_ERR_STICKY  VTSS_BIT(5)
#define  VTSS_X_VOP_OAM_RX_STICKY2_RX_SLM_MEPID_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * When an SLR PDU is received by an Initiator MEP, the VOE will verify
 * that the SLR.SRC_MEPID of the incoming frame matches the Initiator's own
 * MEPID: * VOP:VOE_CONF:VOE_MEPID_CFG.VOE_MEPIDIf the SLR.SRC_MEPID does
 * not match the above value, this sticky bit is asserted and the frame is
 * considered invalid.Frames which fail the SynLM Initiator MEP MEPID check
 * can optionally be extracted to the CPU error queue:	*
 * VOP:VOE_STAT:PDU_EXTRACT.SL_ERR_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_OAM_RX_STICKY2 . RX_INI_ILLEGAL_MEPID_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY2_RX_INI_ILLEGAL_MEPID_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_OAM_RX_STICKY2_RX_INI_ILLEGAL_MEPID_STICKY  VTSS_BIT(4)
#define  VTSS_X_VOP_OAM_RX_STICKY2_RX_INI_ILLEGAL_MEPID_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Only valid if the VOE is configured for G.8113.1 OAM: *
 * VOP:VOE_CONF:VOE_CTRL.G_8113_1_ENAIf an LBM or LBR PDU is received
 * without the mandatory TLV: * LBM mandatory TLV: 'Target MEP/MIP TLV'
 * (TLV type 33) * LBR mandatory TLV: 'Replying MEP/MIP TLV' (TLV type
 * 34)This sticky bit is asserted and the frame is marked as invalid.The
 * frame can optionally be extracted to the CPU error queue depending on
 * the PDU type:LBM: ----------- *
 * VOP:VOE_STAT:PDU_EXTRACT.G_8113_1_LBM_RX_ERR_EXTRLBR: ----------- *
 * VOP:VOE_STAT:PDU_EXTRACT.G_8113_1_LBR_RX_ERR_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_OAM_RX_STICKY2 . G_8113_1_LBX_RX_MISSING_TLV_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_MISSING_TLV_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_MISSING_TLV_STICKY  VTSS_BIT(3)
#define  VTSS_X_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_MISSING_TLV_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Only valid if the VOE is configured for G.8113.1 OAM: *
 * VOP:VOE_CONF:VOE_CTRL.G_8113_1_ENAOnly valid if the VOE is configured
 * for G.8113.1 OAM: * VOP:VOE_CONF:VOE_CTRL.G_8113_1_ENAIf an LBM or LBR
 * PDU is received with an illegal ID Sub-Type in the mandatory TLV: * LBM
 * mandatory TLV: 'Target MEP/MIP TLV' (TLV type 33) * LBR mandatory TLV:
 * 'Replying MEP/MIP TLV' (TLV type 34)This sticky bit is asserted and the
 * frame is marked as invalid.The frame can optionally be extracted to the
 * CPU error queue depending on the PDU type:LBM: ----------- *
 * VOP:VOE_STAT:PDU_EXTRACT.G_8113_1_LBM_RX_ERR_EXTRLBR: ----------- *
 * VOP:VOE_STAT:PDU_EXTRACT.G_8113_1_LBR_RX_ERR_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_OAM_RX_STICKY2 . G_8113_1_LBX_RX_ILLEGAL_SUBTYPE_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_ILLEGAL_SUBTYPE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_ILLEGAL_SUBTYPE_STICKY  VTSS_BIT(2)
#define  VTSS_X_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_ILLEGAL_SUBTYPE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Only valid if the VOE is configured for G.8113.1 OAM: *
 * VOP:VOE_CONF:VOE_CTRL.G_8113_1_ENAIf MIP / MEP / MEG ID verification is
 * enabled: * VOP:VOE_CONF:G_8113_1_CFG.G_8113_1_LBX_MEXID_CHK_ENAThe VOE
 * will validate the MIP / MEP / MEG ID of incoming LBM or LBR PDUs: * Rx
 * LBM:--------------------    - Validate LBM.TargetTLV.MEP_ID (Mandatory
 * TLV)    - Validate LBM.Requesting.MEP_ID (Optional TLV)    - Validate
 * LBM.Requesting.MEG_ID (Optional TLV)For LBR PDUs the validation is
 * depending on configured 'Initiator VOE' configuration: *
 * VOP:VOE_CONF:G_8113_1_CFG.G_8113_1_INITIATOR_FUNCTIONFor LBR PDUs the
 * following fields are configured. * Rx LBR (CV -
 * MIP):----------------------------------    - Validate
 * LBR.ReplyingTLV.CarrierCode + NodeID + IfNum (Mandatory TLV)    -
 * Validate LBR.Requesting.MEP_ID (Optional TLV)    - Validate
 * LBR.Requesting.MEG_ID (Optional TLV) * Rx LBR (CV -
 * MEP):----------------------------------    - Validate
 * LBR.TargetTLV.MEP_ID (Mandatory TLV)    - Validate LBR.Requesting.MEP_ID
 * (Optional TLV)    - Validate LBR.Requesting.MEG_ID (Optional TLV)If the
 * verification fails, this sticky bit is asserted and the frame is marked
 * as invalid.The frame can optionally be extracted to the CPU error queue
 * depending on the PDU type:LBM: ----------- *
 * VOP:VOE_STAT:PDU_EXTRACT.G_8113_1_LBM_RX_ERR_EXTRLBR: ----------- *
 * VOP:VOE_STAT:PDU_EXTRACT.G_8113_1_LBR_RX_ERR_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_OAM_RX_STICKY2 . G_8113_1_LBX_RX_ILLEGAL_MEXID_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_ILLEGAL_MEXID_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_ILLEGAL_MEXID_STICKY  VTSS_BIT(1)
#define  VTSS_X_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_ILLEGAL_MEXID_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Only valid if the VOE is configured for G.8113.1 OAM: *
 * VOP:VOE_CONF:VOE_CTRL.G_8113_1_ENAThe 'Initiator VOE' will verify the
 * value of the incoming 'Loopback Indicator' in the 'Requesting MEP ID
 * TLV' (if present).If the value is != 1 this sticky bit is asserted and
 * the PDU is marked invalid.The frame can optionally be extracted to the
 * CPU error queue:LBR: ----------- *
 * VOP:VOE_STAT:PDU_EXTRACT.G_8113_1_LBR_RX_ERR_EXTR
 *
 * \details
 * Field: ::VTSS_VOP_OAM_RX_STICKY2 . G_8113_1_LBR_RX_ILL_LBK_IND_STICKY
 */
#define  VTSS_F_VOP_OAM_RX_STICKY2_G_8113_1_LBR_RX_ILL_LBK_IND_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_OAM_RX_STICKY2_G_8113_1_LBR_RX_ILL_LBK_IND_STICKY  VTSS_BIT(0)
#define  VTSS_X_VOP_OAM_RX_STICKY2_G_8113_1_LBR_RX_ILL_LBK_IND_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Misc. CCM statistics
 *
 * \details
 * This bit fields in this register contain misc. CCM(-LM) statistics.
 *
 * Register: \a VOP:VOE_STAT:CCM_STAT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CCM_STAT(gi)                VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,25)

/**
 * \brief
 * If this bitfield is asserted, CCM-LM info will be inserted into next CCM
 * frame transmitted by the VOE.(Note: VOP:VOE_CONF:OAM_HW_CTRL.CCM_LM_ENA
 * must be asserted prior to asserting this register.)Upon transmission of
 * CCM-LM information, the bit is cleared by the VOE.If the VOE is
 * configured for automatic LM insertion, this bitfield is automatically
 * asserted by the VOE every time CCM_LM_PERIOD has occurred.Automatic LM
 * insertion is configured: * VOP:VOE_CONF:CCM_CFG.CCM_LM_PERIODLM
 * Insertion can also be forced by SW writing a '1' to this register.This
 * function can be used to implement Dual Ended LM flow, by inserting LM
 * information into the CCM frames with a given period.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_STAT . CCM_LM_INSERT_NXT
 */
#define  VTSS_F_VOP_CCM_STAT_CCM_LM_INSERT_NXT(x)  VTSS_ENCODE_BITFIELD(!!(x),22,1)
#define  VTSS_M_VOP_CCM_STAT_CCM_LM_INSERT_NXT  VTSS_BIT(22)
#define  VTSS_X_VOP_CCM_STAT_CCM_LM_INSERT_NXT(x)  VTSS_EXTRACT_BITFIELD(x,22,1)

/**
 * \brief
 * This configures the value to be inserted in the RDI field in the next
 * valid CCM(-LM) PDU being transmitted by the VOE.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_STAT . CCM_TX_RDI
 */
#define  VTSS_F_VOP_CCM_STAT_CCM_TX_RDI(x)    VTSS_ENCODE_BITFIELD(!!(x),21,1)
#define  VTSS_M_VOP_CCM_STAT_CCM_TX_RDI       VTSS_BIT(21)
#define  VTSS_X_VOP_CCM_STAT_CCM_TX_RDI(x)    VTSS_EXTRACT_BITFIELD(x,21,1)

/**
 * \brief
 * Specifies the number of CCM half periods has passed without CCM messages
 * received from the peer MEP.Cleared when the VOE receives a valid CCM PDU
 * from the peer associated with MEP.It will be periodically incremented by
 * the LOC timer configured by the following register: *
 * VOP:VOE_CONF:CCM_CFG.CCM_PERIODWhen the CCM_MISS counter is incremented
 * to 7, an interrupt is generated if so configured in the following bit
 * field: * VOP:VOE_STAT:INTR_ENA.CCM_LOC_INTR_ENA
 *
 * \details
 * <7: No Loss of continuity
 * ==7: Loss of continuity
 *
 * Field: ::VTSS_VOP_CCM_STAT . CCM_MISS_CNT
 */
#define  VTSS_F_VOP_CCM_STAT_CCM_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,18,3)
#define  VTSS_M_VOP_CCM_STAT_CCM_MISS_CNT     VTSS_ENCODE_BITMASK(18,3)
#define  VTSS_X_VOP_CCM_STAT_CCM_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,18,3)

/**
 * \brief
 * The number of CCM half periods which has passed without reception of CCM
 * messages with low MEL value.Cleared when the VOE receives a valid CCM
 * PDU from the peer associated with the MEP.It will be periodically
 * incremented by the LOC timer pointed to by: *
 * VOP:VOE_STAT:CCM_STAT_2.CCM_RX_MEL_LOW_PERIODWhen the Rx MEL low miss
 * counter is incremented to 7, the defect is cleared and an interrupt is
 * generated if so configured in the following bit field: *
 * VOP:VOE_STAT:INTR_ENA.CCM_RX_MEL_LOW_INTR_ENA
 *
 * \details
 * <7: Rx MEL low defect detected
 * ==7: Rx MEL low defect cleared
 *
 * Field: ::VTSS_VOP_CCM_STAT . CCM_RX_MEL_LOW_MISS_CNT
 */
#define  VTSS_F_VOP_CCM_STAT_CCM_RX_MEL_LOW_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,15,3)
#define  VTSS_M_VOP_CCM_STAT_CCM_RX_MEL_LOW_MISS_CNT     VTSS_ENCODE_BITMASK(15,3)
#define  VTSS_X_VOP_CCM_STAT_CCM_RX_MEL_LOW_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,15,3)

/**
 * \brief
 * The number of CCM half periods which has passed without reception of CCM
 * messages with an unexpected MEG ID.Cleared when the VOE receives a valid
 * CCM PDU from the peer associated with the MEP.It will be periodically
 * incremented by the LOC timer pointed to by: *
 * VOP:VOE_STAT:CCM_STAT_2.CCM_UNEXP_MEGID_PERIODWhen the MEG ID miss
 * counter is incremented to 7, the defect is cleared and an interrupt is
 * generated if so configured in the following bit field: *
 * VOP:VOE_STAT:INTR_ENA.CCM_UNEXP_MEGID_INTR_ENA
 *
 * \details
 * <7: Unexpected MEG ID defect detected.
 * ==7: Unexpected MEG ID defect cleared.
 *
 * Field: ::VTSS_VOP_CCM_STAT . CCM_UNEXP_MEGID_MISS_CNT
 */
#define  VTSS_F_VOP_CCM_STAT_CCM_UNEXP_MEGID_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_VOP_CCM_STAT_CCM_UNEXP_MEGID_MISS_CNT     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_VOP_CCM_STAT_CCM_UNEXP_MEGID_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * The number of CCM half periods which has passed without reception of CCM
 * messages with an unexpected MEP ID.Cleared when the VOE receives a valid
 * CCM PDU from the peer associated with the MEP.It will be periodically
 * incremented by the LOC timer pointed to by: *
 * VOP:VOE_STAT:CCM_STAT_2.CCM_UNEXP_MEPID_PERIODWhen the unexpected MEP ID
 * miss counter is incremented to 7, the defect is cleared and an interrupt
 * is generated if so configured in the following bit field: *
 * VOP:VOE_STAT:INTR_ENA.CCM_UNEXP_MEPID_INTR_ENA
 *
 * \details
 * <7: Unexpected MEP ID defect detected.
 * ==7: Unexpected MEP ID defect cleared.
 *
 * Field: ::VTSS_VOP_CCM_STAT . CCM_UNEXP_MEPID_MISS_CNT
 */
#define  VTSS_F_VOP_CCM_STAT_CCM_UNEXP_MEPID_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_VOP_CCM_STAT_CCM_UNEXP_MEPID_MISS_CNT     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_VOP_CCM_STAT_CCM_UNEXP_MEPID_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * The number of CCM half periods which has passed without reception of CCM
 * messages with an unexpected PERIOD value.Cleared when the VOE receives a
 * valid CCM PDU from the peer associated with the MEP.It will be
 * periodically incremented by the LOC timer pointed to by: *
 * VOP:VOE_STAT:CCM_STAT_2.CCM_UNEXP_PERIOD_PERIODWhen the unexpected
 * PERIOD miss counter is incremented to 7, the defect is cleared and an
 * interrupt is generated if so configured in the following bit field: *
 * VOP:VOE_STAT:INTR_ENA.CCM_UNEXP_PERIOD_INTR_ENA
 *
 * \details
 * <7: No Loss of continuity
 * ==7: Loss of continuity
 *
 * Field: ::VTSS_VOP_CCM_STAT . CCM_UNEXP_PERIOD_MISS_CNT
 */
#define  VTSS_F_VOP_CCM_STAT_CCM_UNEXP_PERIOD_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VOP_CCM_STAT_CCM_UNEXP_PERIOD_MISS_CNT     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VOP_CCM_STAT_CCM_UNEXP_PERIOD_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * The number of CCM half periods which has passed without reception of CCM
 * messages with an unexpected PRIO value.Cleared when the VOE receives a
 * valid CCM PDU from the peer associated with the MEP.It will be
 * periodically incremented by the LOC timer pointed to by: *
 * VOP:VOE_STAT:CCM_STAT_2.CCM_UNEXP_PRIO_PERIODWhen the unexpected PRIO
 * miss counter is incremented to 7, the defect is cleared and an interrupt
 * is generated if so configured in the following bit field: *
 * VOP:VOE_STAT:INTR_ENA.CCM_UNEXP_PRIO_INTR_ENA
 *
 * \details
 * <7: No Loss of continuity
 * ==7: Loss of continuity
 *
 * Field: ::VTSS_VOP_CCM_STAT . CCM_UNEXP_PRIO_MISS_CNT
 */
#define  VTSS_F_VOP_CCM_STAT_CCM_UNEXP_PRIO_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CCM_STAT_CCM_UNEXP_PRIO_MISS_CNT     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CCM_STAT_CCM_UNEXP_PRIO_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * The VOE will count the number of consecutive CCM(-LM) PDUs received on a
 * front port.This can be used for implementing E-Line services over
 * networks using Ethernet Ring protection.The number of consecutive frames
 * received on the same port (not counting the first one) are counted by
 * this counter (CCM_RX_SRC_PORT_CNT).The front port on which the last
 * valid CCM(-LM) PDU was received is stored in: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_RX_SRC_PORTWhen the CPU flushes the MAC
 * table, it can instruct the VOE to detect when CCM(-LM) PDUs are received
 * a number of times on the same front port.When a number of consecutive
 * CCM(-LM) PDUs have been received on the same front port, the following
 * sticky bit is asserted: *
 * VOP:VOE_STAT:INTR_STICKY.CCM_RX_SRC_PORT_DETECT_STICKYThis can
 * optionally generate an interrupt.The number of consecutive CCM(-LM) PDUs
 * which must be received on the same front port before asserting the
 * sticky bit is configured in the following bitfield: *
 * VOP::VOP_CTRL.CCM_RX_SRC_PORT_DETECT_CNTThis field is updated by the VOE
 * and should never be altered by the CPU.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_STAT . CCM_RX_SRC_PORT_CNT
 */
#define  VTSS_F_VOP_CCM_STAT_CCM_RX_SRC_PORT_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CCM_STAT_CCM_RX_SRC_PORT_CNT     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CCM_STAT_CCM_RX_SRC_PORT_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Misc. CCM statistics - continued
 *
 * \details
 * Register: \a VOP:VOE_STAT:CCM_STAT_2
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CCM_STAT_2(gi)              VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,26)

/**
 * \brief
 * Assigns an LOC counter which will be used to increment the Rx MEL low
 * miss counter.The value is extracted from the PERIOD field in received
 * CCM(-LM) frames with low MEL value. The field is updated when the Rx MEL
 * low defect becomes active and again whenever a frame is received while
 * the defect is active, which holds a PERIOD value greater than the
 * current value of CCM_RX_MEL_LOW_PERIOD.The result is that the longest
 * period signaled by Rx MEL low frames will determine the rate of
 * incrementing * VOP:VOE_STAT:CCM_STAT.CCM_RX_MEL_LOW_MISS_CNTand,
 * consequently, the timeout period of clearing the defect, once frames
 * with Rx MEL low are no longer received.
 *
 * \details
 * 0: CCM_RX_MEL_LOW_MISS_CNT is not incremented. (Zero is an illegal
 * period value)
 * 1: CCM_RX_MEL_LOW_MISS_CNT is incremented by LOC timeout counter 0
 * (Timeout period == 1)
 * 2: CCM_RX_MEL_LOW_MISS_CNT is incremented by LOC timeout counter 1
 * (Timeout period == 2)
 * 3: CCM_RX_MEL_LOW_MISS_CNT is incremented by LOC timeout counter 2
 * (Timeout period == 3)
 * 4: CCM_RX_MEL_LOW_MISS_CNT is incremented by LOC timeout counter 3
 * (Timeout period == 4)
 * 5: CCM_RX_MEL_LOW_MISS_CNT is incremented by LOC timeout counter 4
 * (Timeout period == 5)
 * 6: CCM_RX_MEL_LOW_MISS_CNT is incremented by LOC timeout counter 5
 * (Timeout period == 6)
 * 7: CCM_RX_MEL_LOW_MISS_CNT is incremented by LOC timeout counter 6
 * (Timeout period == 7)
 *
 * Field: ::VTSS_VOP_CCM_STAT_2 . CCM_RX_MEL_LOW_PERIOD
 */
#define  VTSS_F_VOP_CCM_STAT_2_CCM_RX_MEL_LOW_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_VOP_CCM_STAT_2_CCM_RX_MEL_LOW_PERIOD     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_VOP_CCM_STAT_2_CCM_RX_MEL_LOW_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \brief
 * Assigns an LOC counter which will be used to increment the unexpected
 * MEG ID miss counter.The value is extracted from the PERIOD field in
 * received CCM(-LM) frames with unexpected MEG ID. The field is updated
 * when the unexpected MEG ID defect becomes active and again whenever a
 * frame is received while the defect is active, which holds a PERIOD value
 * greater than the current value of CCM_UNEXP_MEGID_PERIOD.The result is
 * that the longest period signaled by frames with an unexpected MEG ID
 * will determine the rate of incrementing *
 * VOP:VOE_STAT:CCM_STAT.CCM_UNEXP_MEGID_MISS_CNTand, consequently, the
 * timeout period of clearing the defect, once frames with unexpected MEG
 * ID are no longer received.
 *
 * \details
 * 0: CCM_MEGID_MISS_CNT is not incremented. (Zero is an illegal period
 * value)
 * 1: CCM_MEGID_MISS_CNT is incremented by LOC timeout counter 0 (Timeout
 * period == 1)
 * 2: CCM_MEGID_MISS_CNT is incremented by LOC timeout counter 1 (Timeout
 * period == 2)
 * 3: CCM_MEGID_MISS_CNT is incremented by LOC timeout counter 2 (Timeout
 * period == 3)
 * 4: CCM_MEGID_MISS_CNT is incremented by LOC timeout counter 3 (Timeout
 * period == 4)
 * 5: CCM_MEGID_MISS_CNT is incremented by LOC timeout counter 4 (Timeout
 * period == 5)
 * 6: CCM_MEGID_MISS_CNT is incremented by LOC timeout counter 5 (Timeout
 * period == 6)
 * 7: CCM_MEGID_MISS_CNT is incremented by LOC timeout counter 6 (Timeout
 * period == 7)
 *
 * Field: ::VTSS_VOP_CCM_STAT_2 . CCM_UNEXP_MEGID_PERIOD
 */
#define  VTSS_F_VOP_CCM_STAT_2_CCM_UNEXP_MEGID_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_VOP_CCM_STAT_2_CCM_UNEXP_MEGID_PERIOD     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_VOP_CCM_STAT_2_CCM_UNEXP_MEGID_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \brief
 * Assigns an LOC counter which will be used to increment the unexpected
 * MEP ID miss counter.The value is extracted from the PERIOD field in
 * received CCM(-LM) frames with unexpected MEP ID. The field is updated
 * when the unexpected MEP ID defect becomes active and again whenever a
 * frame is received while the defect is active, which holds a PERIOD value
 * greater than the current value of CCM_UNEXP_MEPID_PERIOD.The result is
 * that the longest period signaled by frames with an unexpected MEP ID
 * will determine the rate of incrementing *
 * VOP:VOE_STAT:CCM_STAT.CCM_UNEXP_MEPID_MISS_CNTand, consequently, the
 * timeout period of clearing the defect, once frames with unexpected MEP
 * ID are no longer received.
 *
 * \details
 * 0: CCM_MEPID_MISS_CNT is not incremented. (Zero is an illegal period
 * value)
 * 1: CCM_MEPID_MISS_CNT is incremented by LOC timeout counter 0 (Timeout
 * period == 1)
 * 2: CCM_MEPID_MISS_CNT is incremented by LOC timeout counter 1 (Timeout
 * period == 2)
 * 3: CCM_MEPID_MISS_CNT is incremented by LOC timeout counter 2 (Timeout
 * period == 3)
 * 4: CCM_MEPID_MISS_CNT is incremented by LOC timeout counter 3 (Timeout
 * period == 4)
 * 5: CCM_MEPID_MISS_CNT is incremented by LOC timeout counter 4 (Timeout
 * period == 5)
 * 6: CCM_MEPID_MISS_CNT is incremented by LOC timeout counter 5 (Timeout
 * period == 6)
 * 7: CCM_MEPID_MISS_CNT is incremented by LOC timeout counter 6 (Timeout
 * period == 7)
 *
 * Field: ::VTSS_VOP_CCM_STAT_2 . CCM_UNEXP_MEPID_PERIOD
 */
#define  VTSS_F_VOP_CCM_STAT_2_CCM_UNEXP_MEPID_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VOP_CCM_STAT_2_CCM_UNEXP_MEPID_PERIOD     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VOP_CCM_STAT_2_CCM_UNEXP_MEPID_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * Assigns an LOC counter which will be used to increment the unexpected
 * PERIOD miss counter.The value is extracted from the PERIOD field in
 * received CCM(-LM) frames with an unexpected PERIOD value. The field is
 * updated when the unexpected PERIOD defect becomes active and again
 * whenever a frame is received while the defect is active, which holds a
 * PERIOD value greater than the current value of
 * CCM_UNEXP_PERIOD_PERIOD.The result is that the longest period signaled
 * by frames with an unexpected PERIOD value will determine the rate of
 * incrementing * VOP:VOE_STAT:CCM_STAT.CCM_UNEXP_PERIOD_MISS_CNTand,
 * consequently, the timeout period of clearing the defect, once frames
 * with unexpected PERIOD are no longer received.
 *
 * \details
 * 0: CCM_PERIOD_MISS_CNT is not incremented. (Zero is an illegal period
 * value)
 * 1: CCM_PERIOD_MISS_CNT is incremented by LOC timeout counter 0 (Timeout
 * period == 1)
 * 2: CCM_PERIOD_MISS_CNT is incremented by LOC timeout counter 1 (Timeout
 * period == 2)
 * 3: CCM_PERIOD_MISS_CNT is incremented by LOC timeout counter 2 (Timeout
 * period == 3)
 * 4: CCM_PERIOD_MISS_CNT is incremented by LOC timeout counter 3 (Timeout
 * period == 4)
 * 5: CCM_PERIOD_MISS_CNT is incremented by LOC timeout counter 4 (Timeout
 * period == 5)
 * 6: CCM_PERIOD_MISS_CNT is incremented by LOC timeout counter 5 (Timeout
 * period == 6)
 * 7: CCM_PERIOD_MISS_CNT is incremented by LOC timeout counter 6 (Timeout
 * period == 7)
 *
 * Field: ::VTSS_VOP_CCM_STAT_2 . CCM_UNEXP_PERIOD_PERIOD
 */
#define  VTSS_F_VOP_CCM_STAT_2_CCM_UNEXP_PERIOD_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CCM_STAT_2_CCM_UNEXP_PERIOD_PERIOD     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CCM_STAT_2_CCM_UNEXP_PERIOD_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Assigns an LOC counter which will be used to increment the unexpected
 * PRIO miss counter.The value is extracted from the PERIOD field in
 * received CCM(-LM) frames with an unexpected PRIO value. The field is
 * updated when the unexpected PRIO defect becomes active and again
 * whenever a frame is received while the defect is active, which holds a
 * PERIOD value greater than the current value of CCM_UNEXP_PRIO_PERIOD.The
 * result is that the longest period signaled by frames with an unexpected
 * PRIO value will determine the rate of incrementing *
 * VOP:VOE_STAT:CCM_STAT.CCM_UNEXP_PRIO_MISS_CNTand, consequently, the
 * timeout period of clearing the defect, once frames with unexpected PRIO
 * are no longer received.
 *
 * \details
 * 0: CCM_PRIO_MISS_CNT is not incremented. (Zero is an illegal period
 * value)
 * 1: CCM_PRIO_MISS_CNT is incremented by LOC timeout counter 0 (Timeout
 * period == 1)
 * 2: CCM_PRIO_MISS_CNT is incremented by LOC timeout counter 1 (Timeout
 * period == 2)
 * 3: CCM_PRIO_MISS_CNT is incremented by LOC timeout counter 2 (Timeout
 * period == 3)
 * 4: CCM_PRIO_MISS_CNT is incremented by LOC timeout counter 3 (Timeout
 * period == 4)
 * 5: CCM_PRIO_MISS_CNT is incremented by LOC timeout counter 4 (Timeout
 * period == 5)
 * 6: CCM_PRIO_MISS_CNT is incremented by LOC timeout counter 5 (Timeout
 * period == 6)
 * 7: CCM_PRIO_MISS_CNT is incremented by LOC timeout counter 6 (Timeout
 * period == 7)
 *
 * Field: ::VTSS_VOP_CCM_STAT_2 . CCM_UNEXP_PRIO_PERIOD
 */
#define  VTSS_F_VOP_CCM_STAT_2_CCM_UNEXP_PRIO_PERIOD(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CCM_STAT_2_CCM_UNEXP_PRIO_PERIOD     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CCM_STAT_2_CCM_UNEXP_PRIO_PERIOD(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Misc. CCM(-LM) statistics for the latest Rx frame.
 *
 * \details
 * This register contains a number of status bits.
 *
 * Each status bit indicates the latest result of a specific check
 * performed on Rx CCM PDUs.
 *
 * Each of the status bits in this register corresponds to a sticky bit in
 * the following register:
 *
 *  * VOP:VOE_STAT:INTR_STICKY.*
 *
 * When a status bit this in this register (CCM_RX_LAST) changes its value,
 * the corresponding sticky bit is asserted.
 *
 * The bits in this register are status bits updated by the VOE, and the
 * values should never be altered by the CPU, because they must represent
 * the state of the latest valid CCM PDU.
 *
 * Bit field CCM_LOC_DEFECT differs from the other bit fields because it is
 * updated not only when a CCM(-LM) PDU is received, but also by the LOC
 * Controller, when a LOC condition is detected.
 *
 * Bit fields CCM_RX_MEL_LOW_DEFECT, CCM_UNEXP_MEGID_DEFECT,
 * CCM_UNEXP_MEPID_DEFECT, CCM_UNEXP_PERIOD_DEFECT and
 * CCM_UNEXP_PRIO_DEFECT differ from the other bit fields because they are
 * updated not only when a CCM(-LM) PDU is received, but also by the LOC
 * Controller, when a defect clear condition is detected.
 *
 * Register: \a VOP:VOE_STAT:CCM_RX_LAST
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CCM_RX_LAST(gi)             VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,27)

/**
 * \brief
 * If the value of the PERIOD field in a CCM(-LM) payload received is ZERO,
 * the CCM(-LM) frame is invalid.The value of the period of all Rx CCM(-LM)
 *  frames, is checked for a non-zero value.This register holds the value
 * of the latest check performed by the VOE.If the result of the ZERO
 * period check changes, the corresponding sticky bit is asserted:  *
 * VOP:VOE_STAT:INTR_STICKY.CCM_ZERO_PERIOD_RX_ERR_STICKYThis allows
 * interrupt generation when result of the incoming CCM_ZERO_PERIOD check
 * changes.This check will be done for CCM(-LM) frames only.CCM PDUs
 * received by the VOE, which fail the CCM_ZERO_PERIOD verification can
 * optionally be extracted to the CPU using the following bit field: *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_ZERO_PERIOD_RX_ERR_EXTRExtracted CCM PDUs
 * are extracted to the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU
 *
 * \details
 * 0: No ZERO period error detected in the last valid CCM(-LM) frame
 * received.
 * 1: Detected ZERO period error in the last valid CCM(-LM) frame received.
 *
 * Field: ::VTSS_VOP_CCM_RX_LAST . CCM_ZERO_PERIOD_ERR
 */
#define  VTSS_F_VOP_CCM_RX_LAST_CCM_ZERO_PERIOD_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CCM_RX_LAST_CCM_ZERO_PERIOD_ERR  VTSS_BIT(5)
#define  VTSS_X_VOP_CCM_RX_LAST_CCM_ZERO_PERIOD_ERR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Current status of the Rx MEL low defect.This bitfield is asserted upon
 * reception of a CCM(-LM) frame with a low MEL value and is deasserted by
 * the LOC Controller.If the MEL value of an Rx OAM PDU is lower than the
 * MEL configured for the VOE, this is an RX_MEL_LOW error.If the defect
 * status changes, the corresponding STICKY bit is asserted: *
 * VOP:VOE_STAT:INTR_STICKY.CCM_RX_MEL_LOW_STICKYOAM PDUs received by the
 * VOE, which fail the RX_MEL_LOW verification can optionally be extracted
 * to the CPU using the following bit field: *
 * VOP:VOE_STAT:PDU_EXTRACT.RX_MEL_LOW_ERR_EXTRExtracted CCM PDUs are
 * extracted to the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU
 *
 * \details
 * 0: No Rx MEL LOW error detected in the last valid CCM(-LM) frame
 * received.
 * 1: Detected Rx MEL LOW error in the last valid CCM(-LM) frame received.
 *
 * Field: ::VTSS_VOP_CCM_RX_LAST . CCM_RX_MEL_LOW_DEFECT
 */
#define  VTSS_F_VOP_CCM_RX_LAST_CCM_RX_MEL_LOW_DEFECT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CCM_RX_LAST_CCM_RX_MEL_LOW_DEFECT  VTSS_BIT(0)
#define  VTSS_X_VOP_CCM_RX_LAST_CCM_RX_MEL_LOW_DEFECT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Current status of the unexpected MEG ID defect.This bitfield is asserted
 * upon reception of a CCM(-LM) frame with an unexpected MEG ID and is
 * deasserted by the LOC Controller.For all valid CCM(-LM) frames received
 * by the VOE, the value of the CCM(-LM) MEPID field is validated against
 * the MEGID configured for the VOE: *
 * VOP:VOE_CONF:CCM_MEGID_CFG.CCM_MEGIDIf the defect status changes, the
 * corresponding STICKY bit is asserted: *
 * VOP:VOE_STAT:INTR_STICKY.CCM_UNEXP_MEGID_STICKYThis check will be done
 * for CCM(-LM) frames only.MEGID checking is enabled by: *
 * VOP:VOE_CONF:CCM_CFG.CCM_MEGID_CHK_ENA = 1CCM PDUs received by the VOE,
 * which fail the MEG ID verification can optionally be extracted to the
 * CPU using the following bit field: *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_MEGID_RX_ERR_EXTRExtracted CCM PDUs are
 * extracted to the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU
 *
 * \details
 * 0: No MEGID error detected in the last valid CCM(-LM) frame received.
 * 1: Detected MEGID error in the last valid CCM(-LM) frame received.
 *
 * Field: ::VTSS_VOP_CCM_RX_LAST . CCM_UNEXP_MEGID_DEFECT
 */
#define  VTSS_F_VOP_CCM_RX_LAST_CCM_UNEXP_MEGID_DEFECT(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CCM_RX_LAST_CCM_UNEXP_MEGID_DEFECT  VTSS_BIT(1)
#define  VTSS_X_VOP_CCM_RX_LAST_CCM_UNEXP_MEGID_DEFECT(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Current status of the unexpected MEP ID defect.This bitfield is asserted
 * upon reception of a CCM(-LM) frame with an unexpected MEP ID and is
 * deasserted by the LOC Controller.For all valid CCM(-LM) frames received
 * by the VOE, the value of the CCM(-LM) MEGID field is validated against
 * the PEER_MEGID configured for the VOE: *
 * VOP:VOE_CONF:PEER_MEPID_CFG.PEER_MEPIDIf the defect status changes, the
 * corresponding STICKY bit is asserted: *
 * VOP:VOE_STAT:INTR_STICKY.CCM_UNEXP_MEPID_STICKYThis check will be done
 * for CCM(-LM) frames only.MEP ID check is enabled by setting: *
 * VOP:VOE_CONF:CCM_CFG.CCM_MEPID_CHK_ENA = 1CCM PDUs received by the VOE,
 * which fail the MEP ID verification can optionally be extracted to the
 * CPU using the following bit field: *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_MEPID_RX_ERR_EXTRExtracted CCM PDUs are
 * extracted to the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU
 *
 * \details
 * 0: No MEPID error detected in the last valid CCM(-LM) frame received.
 * 1: Detected MEPID error in the last valid CCM(-LM) frame received.
 *
 * Field: ::VTSS_VOP_CCM_RX_LAST . CCM_UNEXP_MEPID_DEFECT
 */
#define  VTSS_F_VOP_CCM_RX_LAST_CCM_UNEXP_MEPID_DEFECT(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CCM_RX_LAST_CCM_UNEXP_MEPID_DEFECT  VTSS_BIT(2)
#define  VTSS_X_VOP_CCM_RX_LAST_CCM_UNEXP_MEPID_DEFECT(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Current status of the unexpected PERIOD defect.This bitfield is asserted
 * upon reception of a CCM(-LM) frame with an unexpected period value and
 * is deasserted by the LOC Controller.For all valid CCM(-LM) frames
 * received by the VOE, the value of the CCM(-LM) PERIOD field is validated
 * against the CCM_PERIOD configured for the VOE: *
 * VOP:VOE_CONF:CCM_CFG.CCM_PERIODIf the defect status changes, the
 * corresponding STICKY bit is asserted: *
 * VOP:VOE_STAT:INTR_STICKY.CCM_UNEXP_PERIOD_STICKYCCM(-LM) PDUs received
 * by the VOE, which fail the CCM PERIOD verification can optionally be
 * extracted to the CPU using the following bit field: *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_PERIOD_RX_ERR_EXTRExtracted CCM PDUs are
 * extracted to the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU
 *
 * \details
 * 0: No PERIOD error detected in the last valid CCM(-LM) frame received.
 * 1: Detected PERIOD error in the last valid CCM(-LM) frame received.
 *
 * Field: ::VTSS_VOP_CCM_RX_LAST . CCM_UNEXP_PERIOD_DEFECT
 */
#define  VTSS_F_VOP_CCM_RX_LAST_CCM_UNEXP_PERIOD_DEFECT(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_CCM_RX_LAST_CCM_UNEXP_PERIOD_DEFECT  VTSS_BIT(7)
#define  VTSS_X_VOP_CCM_RX_LAST_CCM_UNEXP_PERIOD_DEFECT(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Current status of the unexpected PRIO defect.This bitfield is asserted
 * upon reception of a CCM(-LM) frame with an unexpected frame priority and
 * is deasserted by the LOC Controller.For all valid CCM(-LM) frames
 * received by the VOE, the value of the CCM(-LM) frame priority is
 * validated against the CCM_PRIO configured for the VOE: *
 * VOP:VOE_CONF:CCM_CFG.CCM_PRIOIf the defect status changes, the
 * corresponding STICKY bit is asserted: *
 * VOP:VOE_STAT:INTR_STICKY.CCM_UNEXP_PRIO_STICKYCCM(-LM) PDUs received by
 * the VOE, which fail the CCM_PRIO verification can optionally be
 * extracted to the CPU using the following bit field: *
 * VOP:VOE_STAT:PDU_EXTRACT.CCM_PRIO_RX_ERR_EXTRCCM:-----------------------
 * ------------ *
 * VOP::CPU_EXTR_CFG_1.CCM_CPU_QUCCM-LM:-----------------------------------
 * * VOP::CPU_EXTR_CFG_1.CCM_LM_CPU_QU
 *
 * \details
 * 0: No PRIO error detected in the last valid CCM(-LM) frame received.
 * 1: Detected PRIO error in the last valid CCM(-LM) frame received.
 *
 * Field: ::VTSS_VOP_CCM_RX_LAST . CCM_UNEXP_PRIO_DEFECT
 */
#define  VTSS_F_VOP_CCM_RX_LAST_CCM_UNEXP_PRIO_DEFECT(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_CCM_RX_LAST_CCM_UNEXP_PRIO_DEFECT  VTSS_BIT(6)
#define  VTSS_X_VOP_CCM_RX_LAST_CCM_UNEXP_PRIO_DEFECT(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Current Loss Of Continuity status.This bitfield is asserted by the LOC
 * Controller and deasserted upon reception of a valid CCM(-LM) frame.When
 * the value of this bit field changes, the following sticky bit is
 * asserted: * VOP:VOE_STAT:INTR_STICKY.CCM_LOC_STICKYOptionally the
 * interrupt is asserted.
 *
 * \details
 * 0: No LOC condition exists in VOE.
 * 1: LOC condition exists in VOE.
 *
 * Field: ::VTSS_VOP_CCM_RX_LAST . CCM_LOC_DEFECT
 */
#define  VTSS_F_VOP_CCM_RX_LAST_CCM_LOC_DEFECT(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CCM_RX_LAST_CCM_LOC_DEFECT  VTSS_BIT(3)
#define  VTSS_X_VOP_CCM_RX_LAST_CCM_LOC_DEFECT(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * The value of RDI bit received with the last valid CCM(-LM) frame.When
 * this status changes, the following sticky bit will be asserted: *
 * VOP:VOE_STAT:INTR_STICKY.CCM_RX_RDI_STICKYThis allows interrupt
 * generation when the incoming RDI stat changes.
 *
 * \details
 * 0: RDI bit was '0' in the last valid CCM(-LM) frame.
 * 1: RDI bit was '1' in the last valid CCM(-LM) frame.
 *
 * Field: ::VTSS_VOP_CCM_RX_LAST . CCM_RX_RDI
 */
#define  VTSS_F_VOP_CCM_RX_LAST_CCM_RX_RDI(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CCM_RX_LAST_CCM_RX_RDI    VTSS_BIT(4)
#define  VTSS_X_VOP_CCM_RX_LAST_CCM_RX_RDI(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * The source port on which the last CCM(-LM) PDU was received.Can be used
 * for implementing E-Line services over networks using Ethernet Ring
 * protection, without learning the MAC addresses.When the CPU flushes the
 * MAC table, it can instruct the VOE to detect when CCM(-LM) PDUs are
 * received a number of times on the same front port.This register contains
 * the latest front port on which a valid CCM(-LM) PDU was received.The
 * number of consecutive frames received on the same port (not counting the
 * first one) are counted by the following counter: *
 * VOP:VOE_STAT:CCM_STAT.CCM_RX_SRC_PORT_CNTWhen a number of consecutive
 * CCM(-LM) PDUs have been received on the same front port, the following
 * sticky bit is asserted: *
 * VOP:VOE_STAT:INTR_STICKY.CCM_RX_SRC_PORT_DETECT_STICKYThis can
 * optionally generate an interrupt.The number of consecutive CCM(-LM) PDUs
 * which must be received on the same front port before asserting the
 * sticky bit is configured in the following bitfield: *
 * VOP::VOP_CTRL.CCM_RX_SRC_PORT_DETECT_CNT
 *
 * \details
 * Port number of the last port on which a valid Rx CCM(-LM) PDU was
 * received.
 *
 * Field: ::VTSS_VOP_CCM_RX_LAST . CCM_RX_SRC_PORT
 */
#define  VTSS_F_VOP_CCM_RX_LAST_CCM_RX_SRC_PORT(x)  VTSS_ENCODE_BITFIELD(x,13,5)
#define  VTSS_M_VOP_CCM_RX_LAST_CCM_RX_SRC_PORT     VTSS_ENCODE_BITMASK(13,5)
#define  VTSS_X_VOP_CCM_RX_LAST_CCM_RX_SRC_PORT(x)  VTSS_EXTRACT_BITFIELD(x,13,5)

/**
 * \brief
 * If a (CCM-LM) frame carries a "Port Status TLV" the value of this TLV is
 * sampled and stored in this  register.When this status changes, the
 * following sticky bit will be asserted: *
 * VOP:VOE_STAT:INTR_STICKY.TLV_PORT_STATUS_STICKYThis allows interrupt
 * generation when the value of the incoming "Port Status TLV" changes.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_RX_LAST . TLV_PORT_STATUS
 */
#define  VTSS_F_VOP_CCM_RX_LAST_TLV_PORT_STATUS(x)  VTSS_ENCODE_BITFIELD(x,11,2)
#define  VTSS_M_VOP_CCM_RX_LAST_TLV_PORT_STATUS     VTSS_ENCODE_BITMASK(11,2)
#define  VTSS_X_VOP_CCM_RX_LAST_TLV_PORT_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,11,2)

/**
 * \brief
 * If a (CCM-LM) frame carries a "Interface Status TLV" the value of this
 * TLV is sampled and stored in this  register.When this status changes,
 * the following sticky bit will be asserted: *
 * VOP:VOE_STAT:INTR_STICKY.TLV_INTERFACE_STATUS_STICKYThis allows
 * interrupt generation when the value of the incoming "Interface Status
 * TLV" changes.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_RX_LAST . TLV_INTERFACE_STATUS
 */
#define  VTSS_F_VOP_CCM_RX_LAST_TLV_INTERFACE_STATUS(x)  VTSS_ENCODE_BITFIELD(x,8,3)
#define  VTSS_M_VOP_CCM_RX_LAST_TLV_INTERFACE_STATUS     VTSS_ENCODE_BITMASK(8,3)
#define  VTSS_X_VOP_CCM_RX_LAST_TLV_INTERFACE_STATUS(x)  VTSS_EXTRACT_BITFIELD(x,8,3)


/**
 * \brief Misc. AIS statistics
 *
 * \details
 * This bit fields in this register contain misc. AIS statistics.
 *
 * Register: \a VOP:VOE_STAT:AIS_STAT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_AIS_STAT(gi)                VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,28)

/**
 * \brief
 * The number of AIS half periods which has passed without reception of AIS
 * messages.Cleared when the VOE receives an AIS PDU.It will be
 * periodically incremented by the LOC timer pointed to by: *
 * VOP:VOE_STAT:AIS_STAT.AIS_PERIODWhen the AIS miss counter is incremented
 * to 7, the defect is cleared and an interrupt is generated if so
 * configured in the following bit field: *
 * VOP:VOE_STAT:INTR_ENA.AIS_INTR_ENA
 *
 * \details
 * Field: ::VTSS_VOP_AIS_STAT . AIS_MISS_CNT
 */
#define  VTSS_F_VOP_AIS_STAT_AIS_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_AIS_STAT_AIS_MISS_CNT     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_AIS_STAT_AIS_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Assigns an LOC counter which will be used to increment the AIS miss
 * counter.The value is extracted from the PERIOD field in received AIS
 * frames. The field is updated when the AIS defect becomes active and
 * again whenever a frame is received while the defect is active, which
 * holds a PERIOD value greater than the current value of AIS_PERIOD.The
 * result is that the longest period signaled by AIS frames will determine
 * the rate of incrementing * VOP:VOE_STAT:AIS_STAT.AIS_MISS_CNTand,
 * consequently, the timeout period of clearing the defect, once AIS frames
 * are no longer received.
 *
 * \details
 * Field: ::VTSS_VOP_AIS_STAT . AIS_PERIOD
 */
#define  VTSS_F_VOP_AIS_STAT_AIS_PERIOD(x)    VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_AIS_STAT_AIS_PERIOD       VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_AIS_STAT_AIS_PERIOD(x)    VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Misc. AIS statistics for the latest Rx frame.
 *
 * \details
 * This register contains a number of status bits.
 *
 * Each status bit indicates the latest result of a specific check
 * performed on Rx AIS PDUs.
 *
 * Each of the status bits in this register corresponds to a sticky bit in
 * the following register:
 *
 *  * VOP:VOE_STAT:INTR_STICKY.*
 *
 * When a status bit this in this register (AIS_RX_LAST) changes its value,
 * the corresponding sticky bit is asserted.
 *
 * The bits in this register are status bits updated by the VOE, and the
 * values should never be altered by the CPU, because they must represent
 * the state of the latest valid AIS PDU.
 *
 * Bit field AIS_DEFECT differs from the other bit fields because it is
 * updated not only when an AIS PDU is received, but also by the LOC
 * Controller, when a defect clear condition is detected.
 *
 * Register: \a VOP:VOE_STAT:AIS_RX_LAST
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_AIS_RX_LAST(gi)             VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,29)

/**
 * \brief
 * If the value of the PERIOD field in a received AIS PDU is ZERO, the AIS
 * frame is invalid.The value of the period of all Rx AIS  frames, is
 * checked for non-zero values.This register holds the result of the latest
 * check performed by the VOE.If the result of the ZERO period check
 * changes, the corresponding sticky bit is asserted:  *
 * VOP:VOE_STAT:INTR_STICKY.AIS_ZERO_PERIOD_STICKYThis allows interrupt
 * generation when result of the incoming AIS zero period check changes.AIS
 * PDUs received by the VOE, which fail the AIS zero period verification,
 * can optionally be extracted to the CPU using the following bit field: *
 * VOP:VOE_STAT:PDU_EXTRACT.AIS_ERR_EXTRExtracted AIS PDUs are extracted to
 * the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU
 *
 * \details
 * 0: No ZERO period error detected in the last valid AIS frame received.
 * 1: Detected ZERO period error in the last valid AIS frame received.
 *
 * Field: ::VTSS_VOP_AIS_RX_LAST . AIS_ZERO_PERIOD_ERR
 */
#define  VTSS_F_VOP_AIS_RX_LAST_AIS_ZERO_PERIOD_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_AIS_RX_LAST_AIS_ZERO_PERIOD_ERR  VTSS_BIT(1)
#define  VTSS_X_VOP_AIS_RX_LAST_AIS_ZERO_PERIOD_ERR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Current status of the AIS defect.This bit field is asserted upon
 * reception of an AIS frame and is deasserted by the LOC Controller.If the
 * defect status changes, the corresponding STICKY bit is asserted: *
 * VOP:VOE_STAT:INTR_STICKY.AIS_STICKYValid AIS PDUs received by the VOE
 * can optionally be extracted to the CPU using the following bit field: *
 * VOP:VOE_STAT:PDU_EXTRACT.AIS_RX_FRM_NXT_EXTRExtracted AIS PDUs are
 * extracted to the following CPU queue: * VOP::CPU_EXTR_CFG_2.AIS_CPU_QU
 *
 * \details
 * 0: No AIS defect condition exists in VOE.
 * 1: AIS defect condition exists in VOE.
 *
 * Field: ::VTSS_VOP_AIS_RX_LAST . AIS_DEFECT
 */
#define  VTSS_F_VOP_AIS_RX_LAST_AIS_DEFECT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_AIS_RX_LAST_AIS_DEFECT    VTSS_BIT(0)
#define  VTSS_X_VOP_AIS_RX_LAST_AIS_DEFECT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Misc. LCK statistics
 *
 * \details
 * This bit fields in this register contain misc. LCK statistics.
 *
 * Register: \a VOP:VOE_STAT:LCK_STAT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_LCK_STAT(gi)                VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,30)

/**
 * \brief
 * The number of LCK half periods which has passed without reception of LCK
 * messages.Cleared when the VOE receives an LCK PDU.It will be
 * periodically incremented by the LOC timer pointed to by: *
 * VOP:VOE_STAT:LCK_STAT.LCK_PERIODWhen the LCK miss counter is incremented
 * to 7, the defect is cleared and an interrupt is generated if so
 * configured in the following bit field: *
 * VOP:VOE_STAT:INTR_ENA.LCK_INTR_ENA
 *
 * \details
 * Field: ::VTSS_VOP_LCK_STAT . LCK_MISS_CNT
 */
#define  VTSS_F_VOP_LCK_STAT_LCK_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_LCK_STAT_LCK_MISS_CNT     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_LCK_STAT_LCK_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Assigns an LOC counter which will be used to increment the LCK miss
 * counter.The value is extracted from the PERIOD field in received LCK
 * frames. The field is updated when the LCK defect becomes active and
 * again whenever a frame is received while the defect is active, which
 * holds a PERIOD value greater than the current value of LCK_PERIOD.The
 * result is that the longest period signaled by LCK frames will determine
 * the rate of incrementing * VOP:VOE_STAT:LCK_STAT.LCK_MISS_CNTand,
 * consequently, the timeout period of clearing the defect, once LCK frames
 * are no longer received.
 *
 * \details
 * Field: ::VTSS_VOP_LCK_STAT . LCK_PERIOD
 */
#define  VTSS_F_VOP_LCK_STAT_LCK_PERIOD(x)    VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_LCK_STAT_LCK_PERIOD       VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_LCK_STAT_LCK_PERIOD(x)    VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Misc. LCK statistics for the latest Rx frame.
 *
 * \details
 * This register contains a number of status bits.
 *
 * Each status bit indicates the latest result of a specific check
 * performed on Rx LCK PDUs.
 *
 * Each of the status bits in this register corresponds to a sticky bit in
 * the following register:
 *
 *  * VOP:VOE_STAT:INTR_STICKY.*
 *
 * When a status bit this in this register (LCK_RX_LAST) changes its value,
 * the corresponding sticky bit is asserted.
 *
 * The bits in this register are status bits updated by the VOE, and the
 * values should never be altered by the CPU, because they must represent
 * the state of the latest valid LCK PDU.
 *
 * Bit field LCK_DEFECT differs from the other bit fields because it is
 * updated not only when an LCK PDU is received, but also by the LOC
 * Controller, when a defect clear condition is detected.
 *
 * Register: \a VOP:VOE_STAT:LCK_RX_LAST
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_LCK_RX_LAST(gi)             VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,31)

/**
 * \brief
 * If the value of the PERIOD field in a received LCK PDU is ZERO, the LCK
 * frame is invalid.The value of the period of all Rx LCK  frames, is
 * checked for non-zero values.This register holds the result of the latest
 * check performed by the VOE.If the result of the ZERO period check
 * changes, the corresponding sticky bit is asserted:  *
 * VOP:VOE_STAT:INTR_STICKY.LCK_ZERO_PERIOD_STICKYThis allows interrupt
 * generation when result of the incoming LCK zero period check changes.LCK
 * PDUs received by the VOE, which fail the LCK zero period verification,
 * can optionally be extracted to the CPU using the following bit field: *
 * VOP:VOE_STAT:PDU_EXTRACT.LCK_ERR_EXTRExtracted LCK PDUs are extracted to
 * the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU
 *
 * \details
 * 0: No ZERO period error detected in the last valid LCK frame received.
 * 1: Detected ZERO period error in the last valid LCK frame received.
 *
 * Field: ::VTSS_VOP_LCK_RX_LAST . LCK_ZERO_PERIOD_ERR
 */
#define  VTSS_F_VOP_LCK_RX_LAST_LCK_ZERO_PERIOD_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_LCK_RX_LAST_LCK_ZERO_PERIOD_ERR  VTSS_BIT(1)
#define  VTSS_X_VOP_LCK_RX_LAST_LCK_ZERO_PERIOD_ERR(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Current status of the LCK defect.This bit field is asserted upon
 * reception of an LCK frame and is deasserted by the LOC Controller.If the
 * defect status changes, the corresponding STICKY bit is asserted: *
 * VOP:VOE_STAT:INTR_STICKY.LCK_STICKYValid LCK PDUs received by the VOE
 * can optionally be extracted to the CPU using the following bit field: *
 * VOP:VOE_STAT:PDU_EXTRACT.LCK_RX_FRM_NXT_EXTRExtracted LCK PDUs are
 * extracted to the following CPU queue: * VOP::CPU_EXTR_CFG_2.LCK_CPU_QU
 *
 * \details
 * 0: No LCK defect condition exists in VOE.
 * 1: LCK defect condition exists in VOE.
 *
 * Field: ::VTSS_VOP_LCK_RX_LAST . LCK_DEFECT
 */
#define  VTSS_F_VOP_LCK_RX_LAST_LCK_DEFECT(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_LCK_RX_LAST_LCK_DEFECT    VTSS_BIT(0)
#define  VTSS_X_VOP_LCK_RX_LAST_LCK_DEFECT(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Misc. CSF statistics
 *
 * \details
 * This bit fields in this register contain misc. CSF statistics.
 *
 * Register: \a VOP:VOE_STAT:CSF_STAT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CSF_STAT(gi)                VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,32)

/**
 * \brief
 * The number of CSF half periods which has passed without reception of CSF
 * messages.Cleared when the VOE receives a CSF PDU with CSF Type equal to
 * LOS, FDI/AIS or RDI.It will be periodically incremented by the LOC timer
 * pointed to by: * VOP:VOE_STAT:CSF_STAT.CSF_PERIODWhen the CSF miss
 * counter is incremented to 7 or when a CSF PDU is received with CSF Type
 * equal to DCI, the defect is cleared and an interrupt is generated if so
 * configured in the following bit field: *
 * VOP:VOE_STAT:INTR_ENA.CSF_INTR_ENA
 *
 * \details
 * Field: ::VTSS_VOP_CSF_STAT . CSF_MISS_CNT
 */
#define  VTSS_F_VOP_CSF_STAT_CSF_MISS_CNT(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CSF_STAT_CSF_MISS_CNT     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CSF_STAT_CSF_MISS_CNT(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * Assigns an LOC counter which will be used to increment the CSF miss
 * counter.The value is extracted from the PERIOD field in received CSF
 * frames. The field is updated when the CSF defect becomes active and
 * again whenever a frame is received while the defect is active, which
 * holds a PERIOD value greater than the current value of CSF_PERIOD.The
 * result is that the longest period signaled by CSF frames will determine
 * the rate of incrementing * VOP:VOE_STAT:CSF_STAT.CSF_MISS_CNTand,
 * consequently, the timeout period of clearing the defect, once CSF frames
 * are no longer received.
 *
 * \details
 * Field: ::VTSS_VOP_CSF_STAT . CSF_PERIOD
 */
#define  VTSS_F_VOP_CSF_STAT_CSF_PERIOD(x)    VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CSF_STAT_CSF_PERIOD       VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CSF_STAT_CSF_PERIOD(x)    VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Misc. CSF statistics for the latest Rx frame.
 *
 * \details
 * This register contains a number of status bits.
 *
 * Each status bit indicates the latest result of a specific check
 * performed on Rx CSF PDUs.
 *
 * Each of the status bits in this register corresponds to a sticky bit in
 * the following register:
 *
 *  * VOP:VOE_STAT:INTR_STICKY.*
 *
 * When a status bit this in this register (CSF_RX_LAST) changes its value,
 * the corresponding sticky bit is asserted.
 *
 * The bits in this register are status bits updated by the VOE, and the
 * values should never be altered by the CPU, because they must represent
 * the state of the latest valid CSF PDU.
 *
 * Bit field CSF_DEFECT differs from the other bit fields because it is
 * updated not only when an CSF PDU is received, but also by the LOC
 * Controller, when a defect clear condition is detected.
 *
 * Register: \a VOP:VOE_STAT:CSF_RX_LAST
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CSF_RX_LAST(gi)             VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,33)

/**
 * \brief
 * If the value of the PERIOD field in a received CSF PDU is ZERO, the CSF
 * frame is invalid.The value of the period of all Rx CSF  frames, is
 * checked for non-zero values.This register holds the result of the latest
 * check performed by the VOE.If the result of the ZERO period check
 * changes, the corresponding sticky bit is asserted:  *
 * VOP:VOE_STAT:INTR_STICKY.CSF_ZERO_PERIOD_STICKYThis allows interrupt
 * generation when result of the incoming CSF zero period check changes.CSF
 * PDUs received by the VOE, which fail the CSF zero period verification,
 * can optionally be extracted to the CPU using the following bit field: *
 * VOP:VOE_STAT:PDU_EXTRACT.CSF_ERR_EXTRExtracted CSF PDUs are extracted to
 * the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU
 *
 * \details
 * 0: No ZERO period error detected in the last valid CSF frame received.
 * 1: Detected ZERO period error in the last valid CSF frame received.
 *
 * Field: ::VTSS_VOP_CSF_RX_LAST . CSF_ZERO_PERIOD_ERR
 */
#define  VTSS_F_VOP_CSF_RX_LAST_CSF_ZERO_PERIOD_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CSF_RX_LAST_CSF_ZERO_PERIOD_ERR  VTSS_BIT(5)
#define  VTSS_X_VOP_CSF_RX_LAST_CSF_ZERO_PERIOD_ERR(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Current status of the CSF defect.This bit field is asserted upon
 * reception of a CSF PDU with CSF Type equal to LOS, FDI/AIS or RDI. It is
 * deasserted by the LOC Controller or upon reception of a CSF PDU with CSF
 * Type equal to DCI.If the defect status changes, the corresponding STICKY
 * bit is asserted: * VOP:VOE_STAT:INTR_STICKY.CSF_STICKYValid CSF PDUs
 * received by the VOE can optionally be extracted to the CPU using the
 * following bit field: *
 * VOP:VOE_STAT:PDU_EXTRACT.CSF_RX_FRM_NXT_EXTRExtracted CSF PDUs are
 * extracted to the following CPU queue: * VOP::CPU_EXTR_CFG_2.CSF_CPU_QU
 *
 * \details
 * 0: No CSF defect condition exists in VOE.
 * 1: CSF defect condition exists in VOE.
 *
 * Field: ::VTSS_VOP_CSF_RX_LAST . CSF_DEFECT
 */
#define  VTSS_F_VOP_CSF_RX_LAST_CSF_DEFECT(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CSF_RX_LAST_CSF_DEFECT    VTSS_BIT(4)
#define  VTSS_X_VOP_CSF_RX_LAST_CSF_DEFECT(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * If the value of the CSF Type field in a received CSF PDU is invalid, the
 * CSF frame is invalid.The value of the CSF Type of all Rx CSF  frames, is
 * checked for valid values:  000: LOS (Client loss of signal)	001:
 * FDI/AIS (Client forward defect indication)  010: RDI (Client reverse
 * defect indication)  011: DCI (Client defect clear indication)This
 * register holds the result of the latest check performed by the VOE.If
 * the result of the CSF Type validity check changes, the corresponding
 * sticky bit is asserted:  *
 * VOP:VOE_STAT:INTR_STICKY.CSF_INVLD_CSF_TYPE_STICKYThis allows interrupt
 * generation when result of the incoming CSF Type check changes.CSF PDUs
 * received by the VOE, which fail the CSF Type validity check, can
 * optionally be extracted to the CPU using the following bit field: *
 * VOP:VOE_STAT:PDU_EXTRACT.CSF_ERR_EXTRExtracted CSF PDUs are extracted to
 * the following CPU queue: * VOP::CPU_EXTR_CFG.CPU_ERR_QU
 *
 * \details
 * Field: ::VTSS_VOP_CSF_RX_LAST . CSF_INVLD_CSF_TYPE_ERR
 */
#define  VTSS_F_VOP_CSF_RX_LAST_CSF_INVLD_CSF_TYPE_ERR(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CSF_RX_LAST_CSF_INVLD_CSF_TYPE_ERR  VTSS_BIT(3)
#define  VTSS_X_VOP_CSF_RX_LAST_CSF_INVLD_CSF_TYPE_ERR(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * The value of CSF Type received with the last valid CSF frame.When this
 * status changes, the following sticky bit will be asserted: *
 * VOP:VOE_STAT:INTR_STICKY.CSF_RX_CSF_TYPE_STICKYThis allows interrupt
 * generation when the incoming CSF Type status changes.
 *
 * \details
 * 000: CSF Type was LOS in the last valid CSF frame.
 * 001: CSF Type was FDI/AIS in the last valid CSF frame.
 * 010: CSF Type was RDI in the last valid CSF frame.
 * 011: CSF Type was DCI in the last valid CSF frame.
 *
 * Field: ::VTSS_VOP_CSF_RX_LAST . CSF_RX_CSF_TYPE
 */
#define  VTSS_F_VOP_CSF_RX_LAST_CSF_RX_CSF_TYPE(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CSF_RX_LAST_CSF_RX_CSF_TYPE     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CSF_RX_LAST_CSF_RX_CSF_TYPE(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief CCM(-LM) sticky status indications
 *
 * \details
 * Each of the sticky bits in this register is closely related to a
 * specific status bit in the following register:
 *
 *  * VOP:VOE_STAT:CCM_RX_LAST.*
 *
 * The above register contains a number of status bits. Each status bit
 * indicates the latest result of a specific check performed on incoming
 * CCM(-LM) PDUs.
 *
 * If the value of one of these status bits change, the corresponding
 * sticky bit in this register is asserted.
 *
 * Hence if the RDI bit of the incoming CCM frames change from '1' --> '0',
 * this will cause the following changes:
 *
 *  * VOP:VOE_STAT:CCM_RX_LAST.CCM_RX_RDI is modified: '1' --> '0'
 *  * VOP:VOE_STAT:INTR_STICKY.CCM_RX_RDI_STICKY is asserted.
 *
 * Each of the sticky bits in this register can optionally be configured to
 * generate an interrupt, using the following register:
 *
 *  * VOP:VOE_STAT:INTR_ENA.*
 *
 * Sticky bits are only asserted when:
 *  * VOP:VOE_CONF:OAM_HW_CTRL.CCM_ENA = 1

 *
 * Register: \a VOP:VOE_STAT:INTR_STICKY
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_INTR_STICKY(gi)             VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,34)

/**
 * \brief
 * Indicates a change in the status of the ZERO period check of incoming
 * CCM(-LM) frames. When a CCM(-LM) frame is received by the VOE, the
 * result of the ZERO period check is compared to the value stored in: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_ZERO_PERIOD_ERRIf the value changes, the
 * sticky bit is asserted. This can optionally be configured to generate an
 * interrupt: * VOP:VOE_STAT:INTR_ENA.CCM_ZERO_PERIOD_INTR_ENA(According to
 * G.8021 CCM(-LM) frames with PERIOD = 0 is an illegal value.)
 *
 * \details
 * 0: No change in the result of the ZERO period check.
 * 1: The result of the ZERO period check changed.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . CCM_ZERO_PERIOD_RX_ERR_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_CCM_ZERO_PERIOD_RX_ERR_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_INTR_STICKY_CCM_ZERO_PERIOD_RX_ERR_STICKY  VTSS_BIT(7)
#define  VTSS_X_VOP_INTR_STICKY_CCM_ZERO_PERIOD_RX_ERR_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Indicate a change in the Rx MEL low defect status of this VOE.The
 * current Rx MEL low defect status is contained in: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_RX_MEL_LOW_DEFECTThe sticky bit can
 * optionally be configured to generate an interrupt: *
 * VOP:VOE_STAT:INTR_ENA.CCM_RX_MEL_LOW_INTR_ENA
 *
 * \details
 * 0: No change in Rx MEL low defect status.
 * 1: Rx MEL low defect status changed.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . CCM_RX_MEL_LOW_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_CCM_RX_MEL_LOW_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_INTR_STICKY_CCM_RX_MEL_LOW_STICKY  VTSS_BIT(6)
#define  VTSS_X_VOP_INTR_STICKY_CCM_RX_MEL_LOW_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Indicate a change in the unexpected MEG ID defect status of this VOE.The
 * current unexpected MEG ID defect status is contained in: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_MEGID_DEFECTThe sticky bit can
 * optionally be configured to generate an interrupt: *
 * VOP:VOE_STAT:INTR_ENA.CCM_UNEXP_MEGID_INTR_ENA
 *
 * \details
 * 0: No change in unexpected MEG ID defect status.
 * 1: Unexpected MEG ID defect status changed.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . CCM_UNEXP_MEGID_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_CCM_UNEXP_MEGID_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_INTR_STICKY_CCM_UNEXP_MEGID_STICKY  VTSS_BIT(5)
#define  VTSS_X_VOP_INTR_STICKY_CCM_UNEXP_MEGID_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Indicate a change in the unexpected MEP ID defect status of this VOE.The
 * current unexpected MEP ID defect status is contained in: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_MEPID_DEFECTThe sticky bit can
 * optionally be configured to generate an interrupt: *
 * VOP:VOE_STAT:INTR_ENA.CCM_UNEXP_MEPID_INTR_ENA
 *
 * \details
 * 0: No change in unexpected MEP ID defect status.
 * 1: Unexpected MEP ID defect status changed.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . CCM_UNEXP_MEPID_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_CCM_UNEXP_MEPID_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_INTR_STICKY_CCM_UNEXP_MEPID_STICKY  VTSS_BIT(4)
#define  VTSS_X_VOP_INTR_STICKY_CCM_UNEXP_MEPID_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Indicate a change in the unexpected PERIOD defect status of this VOE.The
 * current unexpected PERIOD defect status is contained in: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_PERIOD_DEFECTThe sticky bit can
 * optionally be configured to generate an interrupt: *
 * VOP:VOE_STAT:INTR_ENA.CCM_UNEXP_PERIOD_INTR_ENA
 *
 * \details
 * 0: No change in unexpected PERIOD defect status.
 * 1: Unexpected PERIOD defect status changed.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . CCM_UNEXP_PERIOD_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_CCM_UNEXP_PERIOD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_INTR_STICKY_CCM_UNEXP_PERIOD_STICKY  VTSS_BIT(3)
#define  VTSS_X_VOP_INTR_STICKY_CCM_UNEXP_PERIOD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Indicate a change in the unexpected PRIO defect status of this VOE.The
 * current unexpected PRIO defect status is contained in: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_UNEXP_PRIO_DEFECTThe sticky bit can
 * optionally be configured to generate an interrupt: *
 * VOP:VOE_STAT:INTR_ENA.CCM_UNEXP_PRIO_INTR_ENA
 *
 * \details
 * 0: No change in unexpected PRIO defect status.
 * 1: Unexpected PRIO defect status changed.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . CCM_UNEXP_PRIO_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_CCM_UNEXP_PRIO_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_INTR_STICKY_CCM_UNEXP_PRIO_STICKY  VTSS_BIT(2)
#define  VTSS_X_VOP_INTR_STICKY_CCM_UNEXP_PRIO_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Indicates a change in the Loss Of Continuity (LOC) status of this
 * VOE.The current LOC status is contained in: *
 * VOP:VOE_STAT:CCM_RX_LAST.CCM_LOC_DEFECTThe sticky bit can optionally be
 * configured to generate an interrupt: *
 * VOP:VOE_STAT:INTR_ENA.CCM_LOC_INTR_ENA
 *
 * \details
 * 0: No change in the LOC status.
 * 1: LOC status changed.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . CCM_LOC_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_CCM_LOC_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_INTR_STICKY_CCM_LOC_STICKY  VTSS_BIT(1)
#define  VTSS_X_VOP_INTR_STICKY_CCM_LOC_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Indicate a change in the status of the RDI of incoming CCM(-LM) frames.
 * When a CCM(-LM) frame is received by the VOE, the result of the RDI is
 * compared to the value stored in: * VOP:VOE_STAT:CCM_RX_LAST.CCM_RX_RDIIf
 * the value changes, the sticky bit is asserted. This can optionally be
 * configured to generate an interrupt: *
 * VOP:VOE_STAT:INTR_ENA.CCM_RX_RDI_INTR_ENA
 *
 * \details
 * 0: No change in the Rx RDI value.
 * 1: The value of the Rx RDI value changed.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . CCM_RX_RDI_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_CCM_RX_RDI_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_INTR_STICKY_CCM_RX_RDI_STICKY  VTSS_BIT(0)
#define  VTSS_X_VOP_INTR_STICKY_CCM_RX_RDI_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * The number of successive OAM PDUs received on the same port are counted
 * in the following register: *
 * VOP:VOE_STAT:CCM_STAT.CCM_RX_SRC_PORT_CNTWhen this value reaches the
 * value configured in: * VOP::VOP_CTRL.CCM_RX_SRC_PORT_DETECT_CNTThis
 * sticky bit is asserted.This sticky bit can optionally generate an
 * interrupt depending on the following bit field: *
 * VOP:VOE_STAT:INTR_ENA.CCM_RX_SRC_PORT_DETECT_INTR_ENA
 *
 * \details
 * 0: CCM(-LM) Rx port is not stable.
 * 1: CCM(-LM) Rx port is considered stable.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . CCM_RX_SRC_PORT_DETECT_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_CCM_RX_SRC_PORT_DETECT_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_VOP_INTR_STICKY_CCM_RX_SRC_PORT_DETECT_STICKY  VTSS_BIT(18)
#define  VTSS_X_VOP_INTR_STICKY_CCM_RX_SRC_PORT_DETECT_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Indicate a change in the value of the "Port Status TLV" of incoming
 * CCM(-LM) frames. When a CCM(-LM) frame which includes a "Port Status
 * TLV" is received by the VOE, the value of the "Port Status TLV" is
 * compared to the value stored in: *
 * VOP:VOE_STAT:CCM_RX_LAST.TLV_PORT_STATUSIf the value changes, the sticky
 * bit is asserted. This can optionally be configured to generate an
 * interrupt: * VOP:VOE_STAT:INTR_ENA.TLV_PORT_STATUS_INTR_ENA
 *
 * \details
 * Field: ::VTSS_VOP_INTR_STICKY . TLV_PORT_STATUS_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_TLV_PORT_STATUS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_VOP_INTR_STICKY_TLV_PORT_STATUS_STICKY  VTSS_BIT(17)
#define  VTSS_X_VOP_INTR_STICKY_TLV_PORT_STATUS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Indicate a change in the value of the "Interface Status TLV" of incoming
 * CCM(-LM) frames. When a CCM(-LM) frame which includes a "Interface
 * Status TLV" is received by the VOE, the value of the "Interface Status
 * TLV" is compared to the value stored in: *
 * VOP:VOE_STAT:CCM_RX_LAST.TLV_INTERFACE_STATUSIf the value changes, the
 * sticky bit is asserted. This can optionally be configured to generate an
 * interrupt: * VOP:VOE_STAT:INTR_ENA.TLV_INTERFACE_STATUS_INTR_ENA
 *
 * \details
 * Field: ::VTSS_VOP_INTR_STICKY . TLV_INTERFACE_STATUS_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_TLV_INTERFACE_STATUS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_INTR_STICKY_TLV_INTERFACE_STATUS_STICKY  VTSS_BIT(16)
#define  VTSS_X_VOP_INTR_STICKY_TLV_INTERFACE_STATUS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Indicates a change in the status of the ZERO period check of incoming
 * AIS frames. When an AIS frame is received by the VOE, the result of the
 * ZERO period check is compared to the value stored in: *
 * VOP:VOE_STAT:AIS_RX_LAST.AIS_ZERO_PERIOD_ERRIf the value changes, the
 * sticky bit is asserted. This can optionally be configured to generate an
 * interrupt: * VOP:VOE_STAT:INTR_ENA.AIS_ZERO_PERIOD_INTR_ENA
 *
 * \details
 * 0: No change in the result of the ZERO period check.
 * 1: The result of the ZERO period check changed.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . AIS_ZERO_PERIOD_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_AIS_ZERO_PERIOD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_INTR_STICKY_AIS_ZERO_PERIOD_STICKY  VTSS_BIT(15)
#define  VTSS_X_VOP_INTR_STICKY_AIS_ZERO_PERIOD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Indicates a change in the AIS defect status of this VOE.The current AIS
 * defect status is contained in: * VOP:VOE_STAT:AIS_RX_LAST.AIS_DEFECTThe
 * sticky bit can optionally be configured to generate an interrupt: *
 * VOP:VOE_STAT:INTR_ENA.AIS_INTR_ENA
 *
 * \details
 * Field: ::VTSS_VOP_INTR_STICKY . AIS_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_AIS_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_INTR_STICKY_AIS_STICKY    VTSS_BIT(14)
#define  VTSS_X_VOP_INTR_STICKY_AIS_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Indicates a change in the status of the ZERO period check of incoming
 * LCK frames. When an LCK frame is received by the VOE, the result of the
 * ZERO period check is compared to the value stored in: *
 * VOP:VOE_STAT:LCK_RX_LAST.LCK_ZERO_PERIOD_ERRIf the value changes, the
 * sticky bit is asserted. This can optionally be configured to generate an
 * interrupt: * VOP:VOE_STAT:INTR_ENA.LCK_ZERO_PERIOD_INTR_ENA
 *
 * \details
 * 0: No change in the result of the ZERO period check.
 * 1: The result of the ZERO period check changed.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . LCK_ZERO_PERIOD_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_LCK_ZERO_PERIOD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_INTR_STICKY_LCK_ZERO_PERIOD_STICKY  VTSS_BIT(13)
#define  VTSS_X_VOP_INTR_STICKY_LCK_ZERO_PERIOD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Indicates a change in the LCK defect status of this VOE.The current LCK
 * defect status is contained in: * VOP:VOE_STAT:LCK_RX_LAST.LCK_DEFECTThe
 * sticky bit can optionally be configured to generate an interrupt: *
 * VOP:VOE_STAT:INTR_ENA.LCK_INTR_ENA
 *
 * \details
 * Field: ::VTSS_VOP_INTR_STICKY . LCK_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_LCK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_INTR_STICKY_LCK_STICKY    VTSS_BIT(12)
#define  VTSS_X_VOP_INTR_STICKY_LCK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Indicates a change in the status of the ZERO period check of incoming
 * CSF frames. When a CSF frame is received by the VOE, the result of the
 * ZERO period check is compared to the value stored in: *
 * VOP:VOE_STAT:CSF_RX_LAST.CSF_ZERO_PERIOD_ERRIf the value changes, the
 * sticky bit is asserted. This can optionally be configured to generate an
 * interrupt: * VOP:VOE_STAT:INTR_ENA.CSF_ZERO_PERIOD_INTR_ENA
 *
 * \details
 * 0: No change in the result of the ZERO period check.
 * 1: The result of the ZERO period check changed.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . CSF_ZERO_PERIOD_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_CSF_ZERO_PERIOD_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_INTR_STICKY_CSF_ZERO_PERIOD_STICKY  VTSS_BIT(11)
#define  VTSS_X_VOP_INTR_STICKY_CSF_ZERO_PERIOD_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Indicates a change in the CSF defect status of this VOE.The current CSF
 * defect status is contained in: * VOP:VOE_STAT:CSF_RX_LAST.CSF_DEFECTThe
 * sticky bit can optionally be configured to generate an interrupt: *
 * VOP:VOE_STAT:INTR_ENA.CSF_INTR_ENA
 *
 * \details
 * Field: ::VTSS_VOP_INTR_STICKY . CSF_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_CSF_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_INTR_STICKY_CSF_STICKY    VTSS_BIT(10)
#define  VTSS_X_VOP_INTR_STICKY_CSF_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Indicates a change in the status of the CSF Type of incoming CSF frames.
 * When a CSF frame is received by the VOE, the CSF Type is compared to the
 * value stored in: * VOP:VOE_STAT:CSF_RX_LAST.CSF_RX_CSF_TYPEIf the value
 * changes, the sticky bit is asserted. This can optionally be configured
 * to generate an interrupt: *
 * VOP:VOE_STAT:INTR_ENA.CSF_RX_CSF_TYPE_INTR_ENA
 *
 * \details
 * 0: No change in the received CSF Type.
 * 1: The received CSF Type changed.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . CSF_RX_CSF_TYPE_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_CSF_RX_CSF_TYPE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_INTR_STICKY_CSF_RX_CSF_TYPE_STICKY  VTSS_BIT(9)
#define  VTSS_X_VOP_INTR_STICKY_CSF_RX_CSF_TYPE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Indicates a change in the status of the CSF Type check of incoming CSF
 * frames. When a CSF frame is received by the VOE, the result of the CSF
 * Type check is compared to the value stored in: *
 * VOP:VOE_STAT:CSF_RX_LAST.CSF_INVLD_CSF_TYPE_ERRIf the value changes, the
 * sticky bit is asserted. This can optionally be configured to generate an
 * interrupt: * VOP:VOE_STAT:INTR_ENA.CSF_INVLD_CSF_TYPE_INTR_ENA
 *
 * \details
 * 0: No change in the result of the CSF Type validity check.
 * 1: The result of the CSF Type validity check changed.
 *
 * Field: ::VTSS_VOP_INTR_STICKY . CSF_INVLD_CSF_TYPE_STICKY
 */
#define  VTSS_F_VOP_INTR_STICKY_CSF_INVLD_CSF_TYPE_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_INTR_STICKY_CSF_INVLD_CSF_TYPE_STICKY  VTSS_BIT(8)
#define  VTSS_X_VOP_INTR_STICKY_CSF_INVLD_CSF_TYPE_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief Enable VOE interrupt sources
 *
 * \details
 * This register contains a bitfield for each of the interrupt sources
 * defined for the VOE.
 * This allows enabling the interrupts independently.
 *
 * Status of interrupt sources can be found in VOP:VOE_STAT:INTR_STICKY
 *
 * Current status of the VOE interrupt can be found in VOP::INTR
 *
 * Register: \a VOP:VOE_STAT:INTR_ENA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_INTR_ENA(gi)                VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,35)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.CCM_ZERO_PERIOD_RX_ERR_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . CCM_ZERO_PERIOD_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_CCM_ZERO_PERIOD_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_INTR_ENA_CCM_ZERO_PERIOD_INTR_ENA  VTSS_BIT(5)
#define  VTSS_X_VOP_INTR_ENA_CCM_ZERO_PERIOD_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.CCM_RX_MEL_LOW_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . CCM_RX_MEL_LOW_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_CCM_RX_MEL_LOW_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_INTR_ENA_CCM_RX_MEL_LOW_INTR_ENA  VTSS_BIT(0)
#define  VTSS_X_VOP_INTR_ENA_CCM_RX_MEL_LOW_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.CCM_UNEXP_MEGID_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . CCM_UNEXP_MEGID_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_CCM_UNEXP_MEGID_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_INTR_ENA_CCM_UNEXP_MEGID_INTR_ENA  VTSS_BIT(1)
#define  VTSS_X_VOP_INTR_ENA_CCM_UNEXP_MEGID_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.CCM_UNEXP_MEPID_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . CCM_UNEXP_MEPID_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_CCM_UNEXP_MEPID_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_INTR_ENA_CCM_UNEXP_MEPID_INTR_ENA  VTSS_BIT(2)
#define  VTSS_X_VOP_INTR_ENA_CCM_UNEXP_MEPID_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.CCM_UNEXP_PERIOD_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . CCM_UNEXP_PERIOD_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_CCM_UNEXP_PERIOD_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_INTR_ENA_CCM_UNEXP_PERIOD_INTR_ENA  VTSS_BIT(7)
#define  VTSS_X_VOP_INTR_ENA_CCM_UNEXP_PERIOD_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.CCM_UNEXP_PRIO_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . CCM_UNEXP_PRIO_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_CCM_UNEXP_PRIO_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_INTR_ENA_CCM_UNEXP_PRIO_INTR_ENA  VTSS_BIT(6)
#define  VTSS_X_VOP_INTR_ENA_CCM_UNEXP_PRIO_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.CCM_LOC_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . CCM_LOC_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_CCM_LOC_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_INTR_ENA_CCM_LOC_INTR_ENA  VTSS_BIT(3)
#define  VTSS_X_VOP_INTR_ENA_CCM_LOC_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.CCM_RX_RDI_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . CCM_RX_RDI_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_CCM_RX_RDI_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_INTR_ENA_CCM_RX_RDI_INTR_ENA  VTSS_BIT(4)
#define  VTSS_X_VOP_INTR_ENA_CCM_RX_RDI_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.CCM_RX_SRC_PORT_DETECT_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_INTR_ENA . CCM_RX_SRC_PORT_DETECT_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_CCM_RX_SRC_PORT_DETECT_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_VOP_INTR_ENA_CCM_RX_SRC_PORT_DETECT_INTR_ENA  VTSS_BIT(18)
#define  VTSS_X_VOP_INTR_ENA_CCM_RX_SRC_PORT_DETECT_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.TLV_PORT_STATUS_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_INTR_ENA . TLV_PORT_STATUS_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_TLV_PORT_STATUS_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_VOP_INTR_ENA_TLV_PORT_STATUS_INTR_ENA  VTSS_BIT(17)
#define  VTSS_X_VOP_INTR_ENA_TLV_PORT_STATUS_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.TLV_INTERFACE_STATUS_STICKY
 *
 * \details
 * Field: ::VTSS_VOP_INTR_ENA . TLV_INTERFACE_STATUS_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_TLV_INTERFACE_STATUS_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_INTR_ENA_TLV_INTERFACE_STATUS_INTR_ENA  VTSS_BIT(16)
#define  VTSS_X_VOP_INTR_ENA_TLV_INTERFACE_STATUS_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.AIS_ZERO_PERIOD_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . AIS_ZERO_PERIOD_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_AIS_ZERO_PERIOD_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_INTR_ENA_AIS_ZERO_PERIOD_INTR_ENA  VTSS_BIT(15)
#define  VTSS_X_VOP_INTR_ENA_AIS_ZERO_PERIOD_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.AIS_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . AIS_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_AIS_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_INTR_ENA_AIS_INTR_ENA     VTSS_BIT(14)
#define  VTSS_X_VOP_INTR_ENA_AIS_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.LCK_ZERO_PERIOD_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . LCK_ZERO_PERIOD_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_LCK_ZERO_PERIOD_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_INTR_ENA_LCK_ZERO_PERIOD_INTR_ENA  VTSS_BIT(13)
#define  VTSS_X_VOP_INTR_ENA_LCK_ZERO_PERIOD_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.LCK_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . LCK_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_LCK_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_INTR_ENA_LCK_INTR_ENA     VTSS_BIT(12)
#define  VTSS_X_VOP_INTR_ENA_LCK_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.CSF_ZERO_PERIOD_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . CSF_ZERO_PERIOD_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_CSF_ZERO_PERIOD_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_INTR_ENA_CSF_ZERO_PERIOD_INTR_ENA  VTSS_BIT(11)
#define  VTSS_X_VOP_INTR_ENA_CSF_ZERO_PERIOD_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.CSF_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . CSF_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_CSF_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_INTR_ENA_CSF_INTR_ENA     VTSS_BIT(10)
#define  VTSS_X_VOP_INTR_ENA_CSF_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.CSF_RX_CSF_TYPE_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . CSF_RX_CSF_TYPE_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_CSF_RX_CSF_TYPE_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_INTR_ENA_CSF_RX_CSF_TYPE_INTR_ENA  VTSS_BIT(9)
#define  VTSS_X_VOP_INTR_ENA_CSF_RX_CSF_TYPE_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * Enables interrupt generation when the following sticky bit is asserted:
 * * VOP:VOE_STAT:INTR_STICKY.CSF_INVLD_CSF_TYPE_STICKY
 *
 * \details
 * 0: Disable interrupt
 * 1: Enable interrupt
 *
 * Field: ::VTSS_VOP_INTR_ENA . CSF_INVLD_CSF_TYPE_INTR_ENA
 */
#define  VTSS_F_VOP_INTR_ENA_CSF_INVLD_CSF_TYPE_INTR_ENA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_INTR_ENA_CSF_INVLD_CSF_TYPE_INTR_ENA  VTSS_BIT(8)
#define  VTSS_X_VOP_INTR_ENA_CSF_INVLD_CSF_TYPE_INTR_ENA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)


/**
 * \brief SynLM Tx frame counter.
 *
 * \details
 * TX counter for counting Initiator MEP Tx SynLM PDUs (SLM / 1SL).
 *
 * The counter value is written into the following fields of Tx SynLM PDUs:
 *   * SLM.TxFCf
 *   * 1SL.TxFCf
 *
 * The counter is increased (+1) after being written to the Tx PDU.
 *
 * When running SynLM against a single peer in multiple priorities, this
 * counter is only updated when a frames of the selected priority is
 * transmitted:
 *
 *  * VOP:VOE_CONF:SLM_CONFIG.SLM_PRIO
 *
 * Note:
 * To send TxFCf = 1 in the first Tx SynLM PDU, this register must be
 * initialized to 1.
 *
 * Register: \a VOP:VOE_STAT:SLM_TX_FRM_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_SLM_TX_FRM_CNT(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0x1000,gi,64,0,36)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_SLM_TX_FRM_CNT . SLM_TX_FRM_CNT
 */
#define  VTSS_F_VOP_SLM_TX_FRM_CNT_SLM_TX_FRM_CNT(x)  (x)
#define  VTSS_M_VOP_SLM_TX_FRM_CNT_SLM_TX_FRM_CNT     0xffffffff
#define  VTSS_X_VOP_SLM_TX_FRM_CNT_SLM_TX_FRM_CNT(x)  (x)

/**
 * Register Group: \a VOP:VOE_STAT_REG
 *
 * Per VOE statistics registers
 */


/**
 * \brief Sticky bits for frames blocked by the VOE.
 *
 * \details
 * Register: \a VOP:VOE_STAT_REG:BLK_STICKY
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_BLK_STICKY(gi)              VTSS_IOREG_IX(VTSS_TO_VOP,0x3500,gi,1,0,0)

/**
 * \brief
 * Asserted when frames have been blocked in the Tx direction of the VOE at
 * the client layer due to the LOCK state enabled in: *
 * VOP:VOE_CONF_REG:VOE_MISC_CONFIG.BLK_ENA
 *
 * \details
 * '0': No client layer Tx blocking detected
 * '1': Client layer Tx blocking detected
 *
 * Field: ::VTSS_VOP_BLK_STICKY . TX_CLIENT_BLK_STICKY
 */
#define  VTSS_F_VOP_BLK_STICKY_TX_CLIENT_BLK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_BLK_STICKY_TX_CLIENT_BLK_STICKY  VTSS_BIT(3)
#define  VTSS_X_VOP_BLK_STICKY_TX_CLIENT_BLK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \brief
 * Asserted when frames have been blocked in the Rx direction of the VOE at
 * the client layer due to the LOCK state enabled in: *
 * VOP:VOE_CONF_REG:VOE_MISC_CONFIG.BLK_ENA
 *
 * \details
 * '0': No client layer Rx blocking detected
 * '1': Client layer Rx blocking detected
 *
 * Field: ::VTSS_VOP_BLK_STICKY . RX_CLIENT_BLK_STICKY
 */
#define  VTSS_F_VOP_BLK_STICKY_RX_CLIENT_BLK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_BLK_STICKY_RX_CLIENT_BLK_STICKY  VTSS_BIT(2)
#define  VTSS_X_VOP_BLK_STICKY_RX_CLIENT_BLK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \brief
 * Asserted when frames have been blocked in the Tx direction of the VOE at
 * the server layer due to the aBLK state enabled in: *
 * VOP:VOE_CONF_REG:VOE_MISC_CONFIG.BLK_ENA
 *
 * \details
 * '0': No server layer Tx blocking detected
 * '1': Server layer Tx blocking detected
 *
 * Field: ::VTSS_VOP_BLK_STICKY . TX_SERVER_BLK_STICKY
 */
#define  VTSS_F_VOP_BLK_STICKY_TX_SERVER_BLK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_BLK_STICKY_TX_SERVER_BLK_STICKY  VTSS_BIT(1)
#define  VTSS_X_VOP_BLK_STICKY_TX_SERVER_BLK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * Asserted when frames have been blocked in the Rx direction of the VOE at
 * the server layer due to the aBLK state enabled in: *
 * VOP:VOE_CONF_REG:VOE_MISC_CONFIG.BLK_ENA
 *
 * \details
 * '0': No server layer Rx blocking detected
 * '1': Server layer Rx blocking detected
 *
 * Field: ::VTSS_VOP_BLK_STICKY . RX_SERVER_BLK_STICKY
 */
#define  VTSS_F_VOP_BLK_STICKY_RX_SERVER_BLK_STICKY(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_BLK_STICKY_RX_SERVER_BLK_STICKY  VTSS_BIT(0)
#define  VTSS_X_VOP_BLK_STICKY_RX_SERVER_BLK_STICKY(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a VOP:VOE_CCM_LM
 *
 * VOE CCM-LM samples
 */


/**
 * \brief CCM-LM Tx sample value.
 *
 * \details
 * Value of the CCM-LM.TX_FC_F field in the lastest received valid CCM-LM
 * frame by this VOE.
 *
 * This value must be transmitted as CCM-LM.TX_FCB in the next CCM-LM frame
 * transmitted by this VOE.
 *
 * Register: \a VOP:VOE_CCM_LM:CCM_TX_FCB_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CCM_TX_FCB_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0xf80,gi,2,0,0)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_TX_FCB_CFG . CCM_TX_FCB
 */
#define  VTSS_F_VOP_CCM_TX_FCB_CFG_CCM_TX_FCB(x)  (x)
#define  VTSS_M_VOP_CCM_TX_FCB_CFG_CCM_TX_FCB     0xffffffff
#define  VTSS_X_VOP_CCM_TX_FCB_CFG_CCM_TX_FCB(x)  (x)


/**
 * \brief CCM-LM Rx LM sample value.
 *
 * \details
 * This is the value of the Rx LM counter sampled when the latest CCM-LM
 * frame was received.
 *
 * This value must be transmitted as CCM-LM.RX_FCB in the next CCM-LM frame
 * transmitted by this VOE.
 *
 * Register: \a VOP:VOE_CCM_LM:CCM_RX_FCB_CFG
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_CCM_RX_FCB_CFG(gi)          VTSS_IOREG_IX(VTSS_TO_VOP,0xf80,gi,2,0,1)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_CCM_RX_FCB_CFG . CCM_RX_FCB
 */
#define  VTSS_F_VOP_CCM_RX_FCB_CFG_CCM_RX_FCB(x)  (x)
#define  VTSS_M_VOP_CCM_RX_FCB_CFG_CCM_RX_FCB     0xffffffff
#define  VTSS_X_VOP_CCM_RX_FCB_CFG_CCM_RX_FCB(x)  (x)

/**
 * Register Group: \a VOP:VOE_CONTEXT_ANA
 *
 * Contains the context for the VOE if in ANA.
 */


/**
 * \brief Common context for all OAM types.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_COMMON_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_COMMON_ANA(gi)       VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,0)

/**
 * \brief
 * Indicator for valid context entry.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_ANA . CT_ENTRY_VALID_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_ANA_CT_ENTRY_VALID_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_VOP_CT_OAM_COMMON_ANA_CT_ENTRY_VALID_ANA  VTSS_BIT(29)
#define  VTSS_X_VOP_CT_OAM_COMMON_ANA_CT_ENTRY_VALID_ANA(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Source port.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_ANA . CT_SRC_PORT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_ANA_CT_SRC_PORT_ANA(x)  VTSS_ENCODE_BITFIELD(x,22,5)
#define  VTSS_M_VOP_CT_OAM_COMMON_ANA_CT_SRC_PORT_ANA     VTSS_ENCODE_BITMASK(22,5)
#define  VTSS_X_VOP_CT_OAM_COMMON_ANA_CT_SRC_PORT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,22,5)

/**
 * \brief
 * OAM type currently being processed.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_ANA . CT_OAM_TYPE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_ANA_CT_OAM_TYPE_ANA(x)  VTSS_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_VOP_CT_OAM_COMMON_ANA_CT_OAM_TYPE_ANA     VTSS_ENCODE_BITMASK(19,3)
#define  VTSS_X_VOP_CT_OAM_COMMON_ANA_CT_OAM_TYPE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,19,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_ANA . CT_LOOKUP_TYPE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_ANA_CT_LOOKUP_TYPE_ANA(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_VOP_CT_OAM_COMMON_ANA_CT_LOOKUP_TYPE_ANA     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_VOP_CT_OAM_COMMON_ANA_CT_LOOKUP_TYPE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * PDU has hardware modification enabled.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_ANA . CT_PDU_HW_ENA_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_ANA_CT_PDU_HW_ENA_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_CT_OAM_COMMON_ANA_CT_PDU_HW_ENA_ANA  VTSS_BIT(15)
#define  VTSS_X_VOP_CT_OAM_COMMON_ANA_CT_PDU_HW_ENA_ANA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * PDU was correctly validated by the VOE and is ready to be processed.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_ANA . CT_VALID_PDU_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_ANA_CT_VALID_PDU_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_CT_OAM_COMMON_ANA_CT_VALID_PDU_ANA  VTSS_BIT(14)
#define  VTSS_X_VOP_CT_OAM_COMMON_ANA_CT_VALID_PDU_ANA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Generic index if the OpCode is generic.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_ANA . CT_OAM_GEN_IDX_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_ANA_CT_OAM_GEN_IDX_ANA(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_VOP_CT_OAM_COMMON_ANA_CT_OAM_GEN_IDX_ANA     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_VOP_CT_OAM_COMMON_ANA_CT_OAM_GEN_IDX_ANA(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/**
 * \brief
 * Determines if the PDU is to be counted as Selected OAM or NON Selected
 * OAM.
 *
 * \details
 * 0: Count as NON Selected OAM
 * 1: Count as Selected OAM
 *
 * Field: ::VTSS_VOP_CT_OAM_COMMON_ANA . CT_SEL_OAM_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_ANA_CT_SEL_OAM_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_CT_OAM_COMMON_ANA_CT_SEL_OAM_ANA  VTSS_BIT(9)
#define  VTSS_X_VOP_CT_OAM_COMMON_ANA_CT_SEL_OAM_ANA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * CPU extract queue.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_ANA . CT_EXTRACT_QU_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_ANA_CT_EXTRACT_QU_ANA(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VOP_CT_OAM_COMMON_ANA_CT_EXTRACT_QU_ANA     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VOP_CT_OAM_COMMON_ANA_CT_EXTRACT_QU_ANA(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * COS ID.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_ANA . CT_COSID_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_ANA_CT_COSID_ANA(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CT_OAM_COMMON_ANA_CT_COSID_ANA     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CT_OAM_COMMON_ANA_CT_COSID_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * ifh.iprio.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_ANA . CT_IPRIO_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_ANA_CT_IPRIO_ANA(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CT_OAM_COMMON_ANA_CT_IPRIO_ANA     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CT_OAM_COMMON_ANA_CT_IPRIO_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Common context for all OAM types.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_COMMON1_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_COMMON1_ANA(gi)      VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON1_ANA . CT_BLOCK_PORT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON1_ANA_CT_BLOCK_PORT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_COMMON1_ANA_CT_BLOCK_PORT_ANA  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_COMMON1_ANA_CT_BLOCK_PORT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON1_ANA . CT_BLOCK_SRV_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON1_ANA_CT_BLOCK_SRV_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_COMMON1_ANA_CT_BLOCK_SRV_ANA  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_COMMON1_ANA_CT_BLOCK_SRV_ANA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON1_ANA . CT_BLOCK_PATH_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON1_ANA_CT_BLOCK_PATH_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_COMMON1_ANA_CT_BLOCK_PATH_ANA  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_COMMON1_ANA_CT_BLOCK_PATH_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON1_ANA . CT_PORT_VOE_RX_INJ_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON1_ANA_CT_PORT_VOE_RX_INJ_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CT_OAM_COMMON1_ANA_CT_PORT_VOE_RX_INJ_ANA  VTSS_BIT(2)
#define  VTSS_X_VOP_CT_OAM_COMMON1_ANA_CT_PORT_VOE_RX_INJ_ANA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON1_ANA . CT_SRV_VOE_RX_INJ_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON1_ANA_CT_SRV_VOE_RX_INJ_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CT_OAM_COMMON1_ANA_CT_SRV_VOE_RX_INJ_ANA  VTSS_BIT(1)
#define  VTSS_X_VOP_CT_OAM_COMMON1_ANA_CT_SRV_VOE_RX_INJ_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON1_ANA . CT_PATH_VOE_RX_INJ_ANA
 */
#define  VTSS_F_VOP_CT_OAM_COMMON1_ANA_CT_PATH_VOE_RX_INJ_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CT_OAM_COMMON1_ANA_CT_PATH_VOE_RX_INJ_ANA  VTSS_BIT(0)
#define  VTSS_X_VOP_CT_OAM_COMMON1_ANA_CT_PATH_VOE_RX_INJ_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Context for Y.1731 OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_INFO_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_INFO_ANA(gi)         VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,2)

/**
 * \brief
 * OAM PDU currently being processed.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_OAM_PDU_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_OAM_PDU_ANA(x)  VTSS_ENCODE_BITFIELD(x,27,5)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_OAM_PDU_ANA     VTSS_ENCODE_BITMASK(27,5)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_OAM_PDU_ANA(x)  VTSS_EXTRACT_BITFIELD(x,27,5)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_MEL_HIGH_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_MEL_HIGH_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_MEL_HIGH_ANA  VTSS_BIT(26)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_MEL_HIGH_ANA(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_CCM_LM_AS_SEL_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_CCM_LM_AS_SEL_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_CCM_LM_AS_SEL_ANA  VTSS_BIT(25)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_CCM_LM_AS_SEL_ANA(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_EXTRACT_CAUSE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_EXTRACT_CAUSE_ANA(x)  VTSS_ENCODE_BITFIELD(x,20,5)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_EXTRACT_CAUSE_ANA     VTSS_ENCODE_BITMASK(20,5)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_EXTRACT_CAUSE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,20,5)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_CHK_SEQ_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_CHK_SEQ_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_CHK_SEQ_ANA  VTSS_BIT(19)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_CHK_SEQ_ANA(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_UPD_SEQ_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_UPD_SEQ_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_UPD_SEQ_ANA  VTSS_BIT(18)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_UPD_SEQ_ANA(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_CCM_PERIOD_ERR_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_CCM_PERIOD_ERR_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_CCM_PERIOD_ERR_ANA  VTSS_BIT(17)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_CCM_PERIOD_ERR_ANA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_CCM_PERIOD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_CCM_PERIOD_ANA(x)  VTSS_ENCODE_BITFIELD(x,14,3)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_CCM_PERIOD_ANA     VTSS_ENCODE_BITMASK(14,3)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_CCM_PERIOD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,14,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_CCM_PRIO_ERR_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_CCM_PRIO_ERR_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_CCM_PRIO_ERR_ANA  VTSS_BIT(13)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_CCM_PRIO_ERR_ANA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_CCM_NONZERO_ENDTLV_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_CCM_NONZERO_ENDTLV_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_CCM_NONZERO_ENDTLV_ANA  VTSS_BIT(12)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_CCM_NONZERO_ENDTLV_ANA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_SAM_SEQ_LBM_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_SAM_SEQ_LBM_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_SAM_SEQ_LBM_ANA  VTSS_BIT(11)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_SAM_SEQ_LBM_ANA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_SAM_SEQ_CCM_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_SAM_SEQ_CCM_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_SAM_SEQ_CCM_ANA  VTSS_BIT(10)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_SAM_SEQ_CCM_ANA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_SAM_SEQ_IDX_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_SAM_SEQ_IDX_ANA(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_SAM_SEQ_IDX_ANA     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_SAM_SEQ_IDX_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_NON_OAM_ERR_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_NON_OAM_ERR_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_NON_OAM_ERR_CNT_ANA  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_NON_OAM_ERR_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_NON_OAM_FWD_ERR_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_NON_OAM_FWD_ERR_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_NON_OAM_FWD_ERR_ANA  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_NON_OAM_FWD_ERR_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_ANA . CT_SYNLM_PEER_IDX_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO_ANA_CT_SYNLM_PEER_IDX_ANA(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CT_OAM_INFO_ANA_CT_SYNLM_PEER_IDX_ANA     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CT_OAM_INFO_ANA_CT_SYNLM_PEER_IDX_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Context for Y.1731 OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_INFO1_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_INFO1_ANA(gi)        VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO1_ANA . CT_SYNLM_PEER_SGL_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO1_ANA_CT_SYNLM_PEER_SGL_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_CT_OAM_INFO1_ANA_CT_SYNLM_PEER_SGL_ANA  VTSS_BIT(15)
#define  VTSS_X_VOP_CT_OAM_INFO1_ANA_CT_SYNLM_PEER_SGL_ANA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO1_ANA . CT_SYNLM_PRIO_CFG_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO1_ANA_CT_SYNLM_PRIO_CFG_ANA(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_VOP_CT_OAM_INFO1_ANA_CT_SYNLM_PRIO_CFG_ANA     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_VOP_CT_OAM_INFO1_ANA_CT_SYNLM_PRIO_CFG_ANA(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO1_ANA . CT_AIS_PERIOD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO1_ANA_CT_AIS_PERIOD_ANA(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_VOP_CT_OAM_INFO1_ANA_CT_AIS_PERIOD_ANA     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_VOP_CT_OAM_INFO1_ANA_CT_AIS_PERIOD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO1_ANA . CT_LCK_PERIOD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO1_ANA_CT_LCK_PERIOD_ANA(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VOP_CT_OAM_INFO1_ANA_CT_LCK_PERIOD_ANA     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VOP_CT_OAM_INFO1_ANA_CT_LCK_PERIOD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO1_ANA . CT_CSF_PERIOD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO1_ANA_CT_CSF_PERIOD_ANA(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CT_OAM_INFO1_ANA_CT_CSF_PERIOD_ANA     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CT_OAM_INFO1_ANA_CT_CSF_PERIOD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO1_ANA . CT_CSF_TYPE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_INFO1_ANA_CT_CSF_TYPE_ANA(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CT_OAM_INFO1_ANA_CT_CSF_TYPE_ANA     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CT_OAM_INFO1_ANA_CT_CSF_TYPE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief CCM TLV context for Y.1731 OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_CCM_TLV_INFO_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_CCM_TLV_INFO_ANA(gi)  VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,4)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_CCM_TLV_INFO_ANA . CT_PORT_STATUS_VLD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_CCM_TLV_INFO_ANA_CT_PORT_STATUS_VLD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_CT_OAM_CCM_TLV_INFO_ANA_CT_PORT_STATUS_VLD_ANA  VTSS_BIT(6)
#define  VTSS_X_VOP_CT_OAM_CCM_TLV_INFO_ANA_CT_PORT_STATUS_VLD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_CCM_TLV_INFO_ANA . CT_PORT_STATUS_VALUE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_CCM_TLV_INFO_ANA_CT_PORT_STATUS_VALUE_ANA(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VOP_CT_OAM_CCM_TLV_INFO_ANA_CT_PORT_STATUS_VALUE_ANA     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VOP_CT_OAM_CCM_TLV_INFO_ANA_CT_PORT_STATUS_VALUE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_CCM_TLV_INFO_ANA . CT_IF_STATUS_VLD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_CCM_TLV_INFO_ANA_CT_IF_STATUS_VLD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_CCM_TLV_INFO_ANA_CT_IF_STATUS_VLD_ANA  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_CCM_TLV_INFO_ANA_CT_IF_STATUS_VLD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_CCM_TLV_INFO_ANA . CT_IF_STATUS_VALUE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_CCM_TLV_INFO_ANA_CT_IF_STATUS_VALUE_ANA(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CT_OAM_CCM_TLV_INFO_ANA_CT_IF_STATUS_VALUE_ANA     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CT_OAM_CCM_TLV_INFO_ANA_CT_IF_STATUS_VALUE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Context for MPLS-TP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_MPLS_INFO_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_MPLS_INFO_ANA(gi)    VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,5)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_ANA . CT_CODEPOINT_MPLS_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_ANA_CT_CODEPOINT_MPLS_ANA(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_ANA_CT_CODEPOINT_MPLS_ANA     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_ANA_CT_CODEPOINT_MPLS_ANA(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_ANA . CT_EXTRACT_CAUSE_MPLS_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_ANA_CT_EXTRACT_CAUSE_MPLS_ANA(x)  VTSS_ENCODE_BITFIELD(x,6,4)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_ANA_CT_EXTRACT_CAUSE_MPLS_ANA     VTSS_ENCODE_BITMASK(6,4)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_ANA_CT_EXTRACT_CAUSE_MPLS_ANA(x)  VTSS_EXTRACT_BITFIELD(x,6,4)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_ANA . CT_BFD_SESSION_SEL_MPLS_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_ANA_CT_BFD_SESSION_SEL_MPLS_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_ANA_CT_BFD_SESSION_SEL_MPLS_ANA  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_ANA_CT_BFD_SESSION_SEL_MPLS_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_ANA . CT_CLR_BFD_MISS_CNT_MPLS_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_ANA_CT_CLR_BFD_MISS_CNT_MPLS_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_ANA_CT_CLR_BFD_MISS_CNT_MPLS_ANA  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_ANA_CT_CLR_BFD_MISS_CNT_MPLS_ANA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_ANA . CT_BFD_TX_UPDATE_ENA_MPLS_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_ANA_CT_BFD_TX_UPDATE_ENA_MPLS_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_ANA_CT_BFD_TX_UPDATE_ENA_MPLS_ANA  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_ANA_CT_BFD_TX_UPDATE_ENA_MPLS_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_ANA . CT_BFD_RX_SAMPLE_ENA_MPLS_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_ANA_CT_BFD_RX_SAMPLE_ENA_MPLS_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_ANA_CT_BFD_RX_SAMPLE_ENA_MPLS_ANA  VTSS_BIT(2)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_ANA_CT_BFD_RX_SAMPLE_ENA_MPLS_ANA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_ANA . CT_POLL_BIT_MPLS_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_ANA_CT_POLL_BIT_MPLS_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_ANA_CT_POLL_BIT_MPLS_ANA  VTSS_BIT(1)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_ANA_CT_POLL_BIT_MPLS_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_ANA . CT_FINAL_BIT_MPLS_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_ANA_CT_FINAL_BIT_MPLS_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_ANA_CT_FINAL_BIT_MPLS_ANA  VTSS_BIT(0)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_ANA_CT_FINAL_BIT_MPLS_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Context for Layer 3 OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_L3_INFO_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_L3_INFO_ANA(gi)      VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,6)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_L3_INFO_ANA . CT_SESSION_VLD_L3_ANA
 */
#define  VTSS_F_VOP_CT_OAM_L3_INFO_ANA_CT_SESSION_VLD_L3_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_L3_INFO_ANA_CT_SESSION_VLD_L3_ANA  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_L3_INFO_ANA_CT_SESSION_VLD_L3_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_L3_INFO_ANA . CT_SESSION_L3_ANA
 */
#define  VTSS_F_VOP_CT_OAM_L3_INFO_ANA_CT_SESSION_L3_ANA(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VOP_CT_OAM_L3_INFO_ANA_CT_SESSION_L3_ANA     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VOP_CT_OAM_L3_INFO_ANA_CT_SESSION_L3_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_L3_INFO_ANA . CT_EXTRACT_CAUSE_L3_ANA
 */
#define  VTSS_F_VOP_CT_OAM_L3_INFO_ANA_CT_EXTRACT_CAUSE_L3_ANA(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CT_OAM_L3_INFO_ANA_CT_EXTRACT_CAUSE_L3_ANA     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CT_OAM_L3_INFO_ANA_CT_EXTRACT_CAUSE_L3_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_DATA_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_DATA_ANA(gi)         VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,7)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DATA_ANA . CT_OAM_DATA_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DATA_ANA_CT_OAM_DATA_ANA(x)  (x)
#define  VTSS_M_VOP_CT_OAM_DATA_ANA_CT_OAM_DATA_ANA     0xffffffff
#define  VTSS_X_VOP_CT_OAM_DATA_ANA_CT_OAM_DATA_ANA(x)  (x)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_DATA1_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_DATA1_ANA(gi)        VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,8)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DATA1_ANA . CT_OAM_DATA1_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DATA1_ANA_CT_OAM_DATA1_ANA(x)  (x)
#define  VTSS_M_VOP_CT_OAM_DATA1_ANA_CT_OAM_DATA1_ANA     0xffffffff
#define  VTSS_X_VOP_CT_OAM_DATA1_ANA_CT_OAM_DATA1_ANA(x)  (x)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_MRP_DELTA_TS_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_MRP_DELTA_TS_ANA(gi)  VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,9)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_DELTA_TS_ANA . CT_DELTA_TS_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_DELTA_TS_ANA_CT_DELTA_TS_ANA(x)  (x)
#define  VTSS_M_VOP_CT_OAM_MRP_DELTA_TS_ANA_CT_DELTA_TS_ANA     0xffffffff
#define  VTSS_X_VOP_CT_OAM_MRP_DELTA_TS_ANA_CT_DELTA_TS_ANA(x)  (x)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_MRP_SEQ_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_MRP_SEQ_ANA(gi)      VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,10)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_SEQ_ANA . CT_BEST_PRIO_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_SEQ_ANA_CT_BEST_PRIO_ANA(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_VOP_CT_OAM_MRP_SEQ_ANA_CT_BEST_PRIO_ANA     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_VOP_CT_OAM_MRP_SEQ_ANA_CT_BEST_PRIO_ANA(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_SEQ_ANA . CT_RX_SEQ_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_SEQ_ANA_CT_RX_SEQ_ANA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_CT_OAM_MRP_SEQ_ANA_CT_RX_SEQ_ANA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_CT_OAM_MRP_SEQ_ANA_CT_RX_SEQ_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_MRP_INFO_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_MRP_INFO_ANA(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,11)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_STORE_PRIO_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_STORE_PRIO_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_STORE_PRIO_ANA  VTSS_BIT(16)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_STORE_PRIO_ANA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_CHK_ANA  VTSS_BIT(15)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_CHK_ANA  VTSS_BIT(14)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_UPD_ANA  VTSS_BIT(13)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_UPD_ANA  VTSS_BIT(12)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_CLR_ITST_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_ITST_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_ITST_MISS_CNT_ANA  VTSS_BIT(11)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_ITST_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_CLR_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_MISS_CNT_ANA  VTSS_BIT(10)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_VERSION_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_VERSION_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_VERSION_ERR_STICKY_ANA  VTSS_BIT(9)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_VERSION_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_DMAC_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_DMAC_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_DMAC_ERR_STICKY_ANA  VTSS_BIT(8)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_DMAC_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_MRP_RX_PROC_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_PROC_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_PROC_STICKY_ANA  VTSS_BIT(7)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_PROC_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_MRP_RX_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_STICKY_ANA  VTSS_BIT(6)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_NXT_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_NXT_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_LOC_CNT_UPD_ANA  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_CNT_UPD_ANA  VTSS_BIT(2)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_LOC_CNT_UPD_ANA  VTSS_BIT(1)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_CNT_UPD_ANA  VTSS_BIT(0)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_DLR_INFO_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_DLR_INFO_ANA(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,12)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_CNT_UPD_ANA  VTSS_BIT(17)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_LOC_CNT_UPD_ANA  VTSS_BIT(16)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_CNT_UPD_ANA  VTSS_BIT(15)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_LOC_CNT_UPD_ANA  VTSS_BIT(14)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(13)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_NXT_FAULT_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_FAULT_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_FAULT_CPU_HITME_ONCE_ANA  VTSS_BIT(12)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_FAULT_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(11)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_RX_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_STICKY_ANA  VTSS_BIT(10)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_RX_PROC_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_PROC_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_PROC_STICKY_ANA  VTSS_BIT(9)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_PROC_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_DMAC_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_DMAC_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_DMAC_ERR_STICKY_ANA  VTSS_BIT(8)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_DMAC_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_VERSION_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_VERSION_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_VERSION_ERR_STICKY_ANA  VTSS_BIT(7)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_VERSION_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_CLR_BCN_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_BCN_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_BCN_MISS_CNT_ANA  VTSS_BIT(6)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_BCN_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_CLR_ADV_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_ADV_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_ADV_MISS_CNT_ANA  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_ADV_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_RX_SEQ_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_SEQ_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_SEQ_ANA  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_SEQ_ANA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_CHK_ANA  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_UPD_ANA  VTSS_BIT(2)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_CHK_ANA  VTSS_BIT(1)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_UPD_ANA  VTSS_BIT(0)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_DATA_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_DATA_ANA(gi)         VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,11)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DATA_ANA . CT_OAM_DATA_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DATA_ANA_CT_OAM_DATA_ANA(x)  (x)
#define  VTSS_M_VOP_CT_OAM_DATA_ANA_CT_OAM_DATA_ANA     0xffffffff
#define  VTSS_X_VOP_CT_OAM_DATA_ANA_CT_OAM_DATA_ANA(x)  (x)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_DATA1_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_DATA1_ANA(gi)        VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,12)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DATA1_ANA . CT_OAM_DATA1_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DATA1_ANA_CT_OAM_DATA1_ANA(x)  (x)
#define  VTSS_M_VOP_CT_OAM_DATA1_ANA_CT_OAM_DATA1_ANA     0xffffffff
#define  VTSS_X_VOP_CT_OAM_DATA1_ANA_CT_OAM_DATA1_ANA(x)  (x)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_MRP_DELTA_TS_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_MRP_DELTA_TS_ANA(gi)  VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,9)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_DELTA_TS_ANA . CT_DELTA_TS_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_DELTA_TS_ANA_CT_DELTA_TS_ANA(x)  (x)
#define  VTSS_M_VOP_CT_OAM_MRP_DELTA_TS_ANA_CT_DELTA_TS_ANA     0xffffffff
#define  VTSS_X_VOP_CT_OAM_MRP_DELTA_TS_ANA_CT_DELTA_TS_ANA(x)  (x)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_MRP_SEQ_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_MRP_SEQ_ANA(gi)      VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,10)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_SEQ_ANA . CT_BEST_PRIO_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_SEQ_ANA_CT_BEST_PRIO_ANA(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_VOP_CT_OAM_MRP_SEQ_ANA_CT_BEST_PRIO_ANA     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_VOP_CT_OAM_MRP_SEQ_ANA_CT_BEST_PRIO_ANA(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_SEQ_ANA . CT_RX_SEQ_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_SEQ_ANA_CT_RX_SEQ_ANA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_CT_OAM_MRP_SEQ_ANA_CT_RX_SEQ_ANA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_CT_OAM_MRP_SEQ_ANA_CT_RX_SEQ_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_MRP_INFO_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_MRP_INFO_ANA(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,11)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_STORE_PRIO_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_STORE_PRIO_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_STORE_PRIO_ANA  VTSS_BIT(16)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_STORE_PRIO_ANA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_CHK_ANA  VTSS_BIT(15)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_CHK_ANA  VTSS_BIT(14)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_UPD_ANA  VTSS_BIT(13)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_UPD_ANA  VTSS_BIT(12)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_CLR_ITST_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_ITST_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_ITST_MISS_CNT_ANA  VTSS_BIT(11)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_ITST_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_CLR_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_MISS_CNT_ANA  VTSS_BIT(10)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_VERSION_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_VERSION_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_VERSION_ERR_STICKY_ANA  VTSS_BIT(9)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_VERSION_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_DMAC_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_DMAC_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_DMAC_ERR_STICKY_ANA  VTSS_BIT(8)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_DMAC_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_MRP_RX_PROC_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_PROC_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_PROC_STICKY_ANA  VTSS_BIT(7)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_PROC_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_MRP_RX_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_STICKY_ANA  VTSS_BIT(6)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_NXT_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_NXT_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_LOC_CNT_UPD_ANA  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_CNT_UPD_ANA  VTSS_BIT(2)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_LOC_CNT_UPD_ANA  VTSS_BIT(1)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_CNT_UPD_ANA  VTSS_BIT(0)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_DLR_INFO_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_DLR_INFO_ANA(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,12)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_CNT_UPD_ANA  VTSS_BIT(17)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_LOC_CNT_UPD_ANA  VTSS_BIT(16)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_CNT_UPD_ANA  VTSS_BIT(15)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_LOC_CNT_UPD_ANA  VTSS_BIT(14)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(13)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_NXT_FAULT_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_FAULT_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_FAULT_CPU_HITME_ONCE_ANA  VTSS_BIT(12)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_FAULT_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(11)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_RX_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_STICKY_ANA  VTSS_BIT(10)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_RX_PROC_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_PROC_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_PROC_STICKY_ANA  VTSS_BIT(9)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_PROC_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_DMAC_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_DMAC_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_DMAC_ERR_STICKY_ANA  VTSS_BIT(8)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_DMAC_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_VERSION_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_VERSION_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_VERSION_ERR_STICKY_ANA  VTSS_BIT(7)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_VERSION_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_CLR_BCN_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_BCN_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_BCN_MISS_CNT_ANA  VTSS_BIT(6)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_BCN_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_CLR_ADV_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_ADV_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_ADV_MISS_CNT_ANA  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_ADV_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_RX_SEQ_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_SEQ_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_SEQ_ANA  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_SEQ_ANA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_CHK_ANA  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_UPD_ANA  VTSS_BIT(2)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_CHK_ANA  VTSS_BIT(1)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_UPD_ANA  VTSS_BIT(0)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_DATA_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_DATA_ANA(gi)         VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,11)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DATA_ANA . CT_OAM_DATA_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DATA_ANA_CT_OAM_DATA_ANA(x)  (x)
#define  VTSS_M_VOP_CT_OAM_DATA_ANA_CT_OAM_DATA_ANA     0xffffffff
#define  VTSS_X_VOP_CT_OAM_DATA_ANA_CT_OAM_DATA_ANA(x)  (x)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_DATA1_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_DATA1_ANA(gi)        VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,12)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DATA1_ANA . CT_OAM_DATA1_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DATA1_ANA_CT_OAM_DATA1_ANA(x)  (x)
#define  VTSS_M_VOP_CT_OAM_DATA1_ANA_CT_OAM_DATA1_ANA     0xffffffff
#define  VTSS_X_VOP_CT_OAM_DATA1_ANA_CT_OAM_DATA1_ANA(x)  (x)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_MRP_DELTA_TS_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_MRP_DELTA_TS_ANA(gi)  VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,9)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_DELTA_TS_ANA . CT_DELTA_TS_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_DELTA_TS_ANA_CT_DELTA_TS_ANA(x)  (x)
#define  VTSS_M_VOP_CT_OAM_MRP_DELTA_TS_ANA_CT_DELTA_TS_ANA     0xffffffff
#define  VTSS_X_VOP_CT_OAM_MRP_DELTA_TS_ANA_CT_DELTA_TS_ANA(x)  (x)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_MRP_SEQ_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_MRP_SEQ_ANA(gi)      VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,10)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_SEQ_ANA . CT_BEST_PRIO_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_SEQ_ANA_CT_BEST_PRIO_ANA(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_VOP_CT_OAM_MRP_SEQ_ANA_CT_BEST_PRIO_ANA     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_VOP_CT_OAM_MRP_SEQ_ANA_CT_BEST_PRIO_ANA(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_SEQ_ANA . CT_RX_SEQ_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_SEQ_ANA_CT_RX_SEQ_ANA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_CT_OAM_MRP_SEQ_ANA_CT_RX_SEQ_ANA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_CT_OAM_MRP_SEQ_ANA_CT_RX_SEQ_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_MRP_INFO_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_MRP_INFO_ANA(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,11)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_STORE_PRIO_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_STORE_PRIO_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_STORE_PRIO_ANA  VTSS_BIT(16)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_STORE_PRIO_ANA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_CHK_ANA  VTSS_BIT(15)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_CHK_ANA  VTSS_BIT(14)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_UPD_ANA  VTSS_BIT(13)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_UPD_ANA  VTSS_BIT(12)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_CLR_ITST_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_ITST_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_ITST_MISS_CNT_ANA  VTSS_BIT(11)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_ITST_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_CLR_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_MISS_CNT_ANA  VTSS_BIT(10)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_VERSION_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_VERSION_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_VERSION_ERR_STICKY_ANA  VTSS_BIT(9)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_VERSION_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_DMAC_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_DMAC_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_DMAC_ERR_STICKY_ANA  VTSS_BIT(8)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_DMAC_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_MRP_RX_PROC_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_PROC_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_PROC_STICKY_ANA  VTSS_BIT(7)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_PROC_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_MRP_RX_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_STICKY_ANA  VTSS_BIT(6)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_NXT_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_NXT_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_LOC_CNT_UPD_ANA  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_CNT_UPD_ANA  VTSS_BIT(2)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_LOC_CNT_UPD_ANA  VTSS_BIT(1)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_CNT_UPD_ANA  VTSS_BIT(0)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_DLR_INFO_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_DLR_INFO_ANA(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,12)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_CNT_UPD_ANA  VTSS_BIT(17)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_LOC_CNT_UPD_ANA  VTSS_BIT(16)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_CNT_UPD_ANA  VTSS_BIT(15)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_LOC_CNT_UPD_ANA  VTSS_BIT(14)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(13)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_NXT_FAULT_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_FAULT_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_FAULT_CPU_HITME_ONCE_ANA  VTSS_BIT(12)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_FAULT_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(11)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_RX_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_STICKY_ANA  VTSS_BIT(10)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_RX_PROC_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_PROC_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_PROC_STICKY_ANA  VTSS_BIT(9)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_PROC_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_DMAC_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_DMAC_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_DMAC_ERR_STICKY_ANA  VTSS_BIT(8)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_DMAC_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_VERSION_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_VERSION_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_VERSION_ERR_STICKY_ANA  VTSS_BIT(7)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_VERSION_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_CLR_BCN_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_BCN_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_BCN_MISS_CNT_ANA  VTSS_BIT(6)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_BCN_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_CLR_ADV_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_ADV_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_ADV_MISS_CNT_ANA  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_ADV_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_RX_SEQ_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_SEQ_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_SEQ_ANA  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_SEQ_ANA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_CHK_ANA  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_UPD_ANA  VTSS_BIT(2)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_CHK_ANA  VTSS_BIT(1)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_UPD_ANA  VTSS_BIT(0)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_DATA_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_DATA_ANA(gi)         VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,11)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DATA_ANA . CT_OAM_DATA_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DATA_ANA_CT_OAM_DATA_ANA(x)  (x)
#define  VTSS_M_VOP_CT_OAM_DATA_ANA_CT_OAM_DATA_ANA     0xffffffff
#define  VTSS_X_VOP_CT_OAM_DATA_ANA_CT_OAM_DATA_ANA(x)  (x)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_DATA1_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_DATA1_ANA(gi)        VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,12)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DATA1_ANA . CT_OAM_DATA1_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DATA1_ANA_CT_OAM_DATA1_ANA(x)  (x)
#define  VTSS_M_VOP_CT_OAM_DATA1_ANA_CT_OAM_DATA1_ANA     0xffffffff
#define  VTSS_X_VOP_CT_OAM_DATA1_ANA_CT_OAM_DATA1_ANA(x)  (x)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_MRP_DELTA_TS_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_MRP_DELTA_TS_ANA(gi)  VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,9)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_DELTA_TS_ANA . CT_DELTA_TS_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_DELTA_TS_ANA_CT_DELTA_TS_ANA(x)  (x)
#define  VTSS_M_VOP_CT_OAM_MRP_DELTA_TS_ANA_CT_DELTA_TS_ANA     0xffffffff
#define  VTSS_X_VOP_CT_OAM_MRP_DELTA_TS_ANA_CT_DELTA_TS_ANA(x)  (x)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_MRP_SEQ_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_MRP_SEQ_ANA(gi)      VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,10)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_SEQ_ANA . CT_BEST_PRIO_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_SEQ_ANA_CT_BEST_PRIO_ANA(x)  VTSS_ENCODE_BITFIELD(x,16,16)
#define  VTSS_M_VOP_CT_OAM_MRP_SEQ_ANA_CT_BEST_PRIO_ANA     VTSS_ENCODE_BITMASK(16,16)
#define  VTSS_X_VOP_CT_OAM_MRP_SEQ_ANA_CT_BEST_PRIO_ANA(x)  VTSS_EXTRACT_BITFIELD(x,16,16)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_SEQ_ANA . CT_RX_SEQ_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_SEQ_ANA_CT_RX_SEQ_ANA(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_CT_OAM_MRP_SEQ_ANA_CT_RX_SEQ_ANA     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_CT_OAM_MRP_SEQ_ANA_CT_RX_SEQ_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,16)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_MRP_INFO_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_MRP_INFO_ANA(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,11)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_STORE_PRIO_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_STORE_PRIO_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_STORE_PRIO_ANA  VTSS_BIT(16)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_STORE_PRIO_ANA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_CHK_ANA  VTSS_BIT(15)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_CHK_ANA  VTSS_BIT(14)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_UPD_ANA  VTSS_BIT(13)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_UPD_ANA  VTSS_BIT(12)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_CLR_ITST_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_ITST_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_ITST_MISS_CNT_ANA  VTSS_BIT(11)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_ITST_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_CLR_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_MISS_CNT_ANA  VTSS_BIT(10)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_CLR_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_VERSION_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_VERSION_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_VERSION_ERR_STICKY_ANA  VTSS_BIT(9)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_VERSION_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_DMAC_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_DMAC_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_DMAC_ERR_STICKY_ANA  VTSS_BIT(8)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_DMAC_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_MRP_RX_PROC_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_PROC_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_PROC_STICKY_ANA  VTSS_BIT(7)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_PROC_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_MRP_RX_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_STICKY_ANA  VTSS_BIT(6)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_MRP_RX_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_NXT_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_NXT_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_NXT_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_LOC_CNT_UPD_ANA  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_ITST_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_CNT_UPD_ANA  VTSS_BIT(2)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_ITST_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_LOC_CNT_UPD_ANA  VTSS_BIT(1)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_ANA . CT_TST_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_CNT_UPD_ANA  VTSS_BIT(0)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_ANA_CT_TST_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_ANA:CT_OAM_DLR_INFO_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_INB_PORTS (??), 0-124
 */
#define VTSS_VOP_CT_OAM_DLR_INFO_ANA(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x2800,gi,16,0,12)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_CNT_UPD_ANA  VTSS_BIT(17)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),16,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_LOC_CNT_UPD_ANA  VTSS_BIT(16)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,16,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_CNT_UPD_ANA  VTSS_BIT(15)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_LOC_CNT_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_LOC_CNT_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_LOC_CNT_UPD_ANA  VTSS_BIT(14)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_LOC_CNT_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(13)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_BCN_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_NXT_FAULT_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_FAULT_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_FAULT_CPU_HITME_ONCE_ANA  VTSS_BIT(12)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_FAULT_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA  VTSS_BIT(11)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_NXT_ADV_LOC_CPU_HITME_ONCE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_RX_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_STICKY_ANA  VTSS_BIT(10)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_RX_PROC_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_PROC_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_PROC_STICKY_ANA  VTSS_BIT(9)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_PROC_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_DMAC_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_DMAC_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),8,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_DMAC_ERR_STICKY_ANA  VTSS_BIT(8)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_DMAC_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,8,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_VERSION_ERR_STICKY_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_VERSION_ERR_STICKY_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),7,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_VERSION_ERR_STICKY_ANA  VTSS_BIT(7)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_VERSION_ERR_STICKY_ANA(x)  VTSS_EXTRACT_BITFIELD(x,7,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_CLR_BCN_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_BCN_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_BCN_MISS_CNT_ANA  VTSS_BIT(6)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_BCN_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_CLR_ADV_MISS_CNT_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_ADV_MISS_CNT_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_ADV_MISS_CNT_ANA  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_CLR_ADV_MISS_CNT_ANA(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_DLR_RX_SEQ_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_SEQ_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_SEQ_ANA  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_DLR_RX_SEQ_ANA(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_CHK_ANA  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_BCN_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_UPD_ANA  VTSS_BIT(2)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_BCN_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_SEQ_CHK_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_CHK_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_CHK_ANA  VTSS_BIT(1)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_CHK_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DLR_INFO_ANA . CT_ADV_RX_SEQ_UPD_ANA
 */
#define  VTSS_F_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_UPD_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_UPD_ANA  VTSS_BIT(0)
#define  VTSS_X_VOP_CT_OAM_DLR_INFO_ANA_CT_ADV_RX_SEQ_UPD_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a VOP:VOE_CONTEXT_REW
 *
 * Contains the context for the VOE if in REW.
 */


/**
 * \brief Common context for all OAM types.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_REW:CT_OAM_COMMON_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_OUTB_PORTS (??), 0-64
 */
#define VTSS_VOP_CT_OAM_COMMON_REW(gi)       VTSS_IOREG_IX(VTSS_TO_VOP,0x3000,gi,16,0,0)

/**
 * \brief
 * Indicator for valid context entry.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_REW . CT_ENTRY_VALID_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_REW_CT_ENTRY_VALID_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),29,1)
#define  VTSS_M_VOP_CT_OAM_COMMON_REW_CT_ENTRY_VALID_REW  VTSS_BIT(29)
#define  VTSS_X_VOP_CT_OAM_COMMON_REW_CT_ENTRY_VALID_REW(x)  VTSS_EXTRACT_BITFIELD(x,29,1)

/**
 * \brief
 * Source port.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_REW . CT_SRC_PORT_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_REW_CT_SRC_PORT_REW(x)  VTSS_ENCODE_BITFIELD(x,22,5)
#define  VTSS_M_VOP_CT_OAM_COMMON_REW_CT_SRC_PORT_REW     VTSS_ENCODE_BITMASK(22,5)
#define  VTSS_X_VOP_CT_OAM_COMMON_REW_CT_SRC_PORT_REW(x)  VTSS_EXTRACT_BITFIELD(x,22,5)

/**
 * \brief
 * OAM type currently being processed.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_REW . CT_OAM_TYPE_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_REW_CT_OAM_TYPE_REW(x)  VTSS_ENCODE_BITFIELD(x,19,3)
#define  VTSS_M_VOP_CT_OAM_COMMON_REW_CT_OAM_TYPE_REW     VTSS_ENCODE_BITMASK(19,3)
#define  VTSS_X_VOP_CT_OAM_COMMON_REW_CT_OAM_TYPE_REW(x)  VTSS_EXTRACT_BITFIELD(x,19,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_REW . CT_LOOKUP_TYPE_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_REW_CT_LOOKUP_TYPE_REW(x)  VTSS_ENCODE_BITFIELD(x,16,3)
#define  VTSS_M_VOP_CT_OAM_COMMON_REW_CT_LOOKUP_TYPE_REW     VTSS_ENCODE_BITMASK(16,3)
#define  VTSS_X_VOP_CT_OAM_COMMON_REW_CT_LOOKUP_TYPE_REW(x)  VTSS_EXTRACT_BITFIELD(x,16,3)

/**
 * \brief
 * PDU has hardware modification enabled.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_REW . CT_PDU_HW_ENA_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_REW_CT_PDU_HW_ENA_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_CT_OAM_COMMON_REW_CT_PDU_HW_ENA_REW  VTSS_BIT(15)
#define  VTSS_X_VOP_CT_OAM_COMMON_REW_CT_PDU_HW_ENA_REW(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \brief
 * PDU was correctly validated by the VOE and is ready to be processed.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_REW . CT_VALID_PDU_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_REW_CT_VALID_PDU_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),14,1)
#define  VTSS_M_VOP_CT_OAM_COMMON_REW_CT_VALID_PDU_REW  VTSS_BIT(14)
#define  VTSS_X_VOP_CT_OAM_COMMON_REW_CT_VALID_PDU_REW(x)  VTSS_EXTRACT_BITFIELD(x,14,1)

/**
 * \brief
 * Generic index if the OpCode is generic.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_REW . CT_OAM_GEN_IDX_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_REW_CT_OAM_GEN_IDX_REW(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_VOP_CT_OAM_COMMON_REW_CT_OAM_GEN_IDX_REW     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_VOP_CT_OAM_COMMON_REW_CT_OAM_GEN_IDX_REW(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/**
 * \brief
 * Determines if the PDU is to be counted as Selected OAM or NON Selected
 * OAM.
 *
 * \details
 * 0: Count as NON Selected OAM
 * 1: Count as Selected OAM
 *
 * Field: ::VTSS_VOP_CT_OAM_COMMON_REW . CT_SEL_OAM_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_REW_CT_SEL_OAM_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),9,1)
#define  VTSS_M_VOP_CT_OAM_COMMON_REW_CT_SEL_OAM_REW  VTSS_BIT(9)
#define  VTSS_X_VOP_CT_OAM_COMMON_REW_CT_SEL_OAM_REW(x)  VTSS_EXTRACT_BITFIELD(x,9,1)

/**
 * \brief
 * CPU extract queue.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_REW . CT_EXTRACT_QU_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_REW_CT_EXTRACT_QU_REW(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VOP_CT_OAM_COMMON_REW_CT_EXTRACT_QU_REW     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VOP_CT_OAM_COMMON_REW_CT_EXTRACT_QU_REW(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \brief
 * COS ID.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_REW . CT_COSID_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_REW_CT_COSID_REW(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CT_OAM_COMMON_REW_CT_COSID_REW     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CT_OAM_COMMON_REW_CT_COSID_REW(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \brief
 * ifh.iprio.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON_REW . CT_IPRIO_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON_REW_CT_IPRIO_REW(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CT_OAM_COMMON_REW_CT_IPRIO_REW     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CT_OAM_COMMON_REW_CT_IPRIO_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Common context for all OAM types.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_REW:CT_OAM_COMMON1_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_OUTB_PORTS (??), 0-64
 */
#define VTSS_VOP_CT_OAM_COMMON1_REW(gi)      VTSS_IOREG_IX(VTSS_TO_VOP,0x3000,gi,16,0,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON1_REW . CT_BLOCK_PORT_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON1_REW_CT_BLOCK_PORT_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_COMMON1_REW_CT_BLOCK_PORT_REW  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_COMMON1_REW_CT_BLOCK_PORT_REW(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON1_REW . CT_BLOCK_SRV_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON1_REW_CT_BLOCK_SRV_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_COMMON1_REW_CT_BLOCK_SRV_REW  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_COMMON1_REW_CT_BLOCK_SRV_REW(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON1_REW . CT_BLOCK_PATH_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON1_REW_CT_BLOCK_PATH_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_COMMON1_REW_CT_BLOCK_PATH_REW  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_COMMON1_REW_CT_BLOCK_PATH_REW(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON1_REW . CT_PORT_VOE_RX_INJ_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON1_REW_CT_PORT_VOE_RX_INJ_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CT_OAM_COMMON1_REW_CT_PORT_VOE_RX_INJ_REW  VTSS_BIT(2)
#define  VTSS_X_VOP_CT_OAM_COMMON1_REW_CT_PORT_VOE_RX_INJ_REW(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON1_REW . CT_SRV_VOE_RX_INJ_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON1_REW_CT_SRV_VOE_RX_INJ_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CT_OAM_COMMON1_REW_CT_SRV_VOE_RX_INJ_REW  VTSS_BIT(1)
#define  VTSS_X_VOP_CT_OAM_COMMON1_REW_CT_SRV_VOE_RX_INJ_REW(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_COMMON1_REW . CT_PATH_VOE_RX_INJ_REW
 */
#define  VTSS_F_VOP_CT_OAM_COMMON1_REW_CT_PATH_VOE_RX_INJ_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CT_OAM_COMMON1_REW_CT_PATH_VOE_RX_INJ_REW  VTSS_BIT(0)
#define  VTSS_X_VOP_CT_OAM_COMMON1_REW_CT_PATH_VOE_RX_INJ_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Context for Y.1731 OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_REW:CT_OAM_INFO_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_OUTB_PORTS (??), 0-64
 */
#define VTSS_VOP_CT_OAM_INFO_REW(gi)         VTSS_IOREG_IX(VTSS_TO_VOP,0x3000,gi,16,0,2)

/**
 * \brief
 * OAM PDU currently being processed.
 *
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_OAM_PDU_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_OAM_PDU_REW(x)  VTSS_ENCODE_BITFIELD(x,27,5)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_OAM_PDU_REW     VTSS_ENCODE_BITMASK(27,5)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_OAM_PDU_REW(x)  VTSS_EXTRACT_BITFIELD(x,27,5)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_MEL_HIGH_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_MEL_HIGH_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),26,1)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_MEL_HIGH_REW  VTSS_BIT(26)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_MEL_HIGH_REW(x)  VTSS_EXTRACT_BITFIELD(x,26,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_CCM_LM_AS_SEL_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_CCM_LM_AS_SEL_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),25,1)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_CCM_LM_AS_SEL_REW  VTSS_BIT(25)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_CCM_LM_AS_SEL_REW(x)  VTSS_EXTRACT_BITFIELD(x,25,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_EXTRACT_CAUSE_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_EXTRACT_CAUSE_REW(x)  VTSS_ENCODE_BITFIELD(x,20,5)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_EXTRACT_CAUSE_REW     VTSS_ENCODE_BITMASK(20,5)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_EXTRACT_CAUSE_REW(x)  VTSS_EXTRACT_BITFIELD(x,20,5)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_CHK_SEQ_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_CHK_SEQ_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),19,1)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_CHK_SEQ_REW  VTSS_BIT(19)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_CHK_SEQ_REW(x)  VTSS_EXTRACT_BITFIELD(x,19,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_UPD_SEQ_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_UPD_SEQ_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),18,1)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_UPD_SEQ_REW  VTSS_BIT(18)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_UPD_SEQ_REW(x)  VTSS_EXTRACT_BITFIELD(x,18,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_CCM_PERIOD_ERR_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_CCM_PERIOD_ERR_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),17,1)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_CCM_PERIOD_ERR_REW  VTSS_BIT(17)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_CCM_PERIOD_ERR_REW(x)  VTSS_EXTRACT_BITFIELD(x,17,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_CCM_PERIOD_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_CCM_PERIOD_REW(x)  VTSS_ENCODE_BITFIELD(x,14,3)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_CCM_PERIOD_REW     VTSS_ENCODE_BITMASK(14,3)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_CCM_PERIOD_REW(x)  VTSS_EXTRACT_BITFIELD(x,14,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_CCM_PRIO_ERR_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_CCM_PRIO_ERR_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),13,1)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_CCM_PRIO_ERR_REW  VTSS_BIT(13)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_CCM_PRIO_ERR_REW(x)  VTSS_EXTRACT_BITFIELD(x,13,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_CCM_NONZERO_ENDTLV_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_CCM_NONZERO_ENDTLV_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),12,1)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_CCM_NONZERO_ENDTLV_REW  VTSS_BIT(12)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_CCM_NONZERO_ENDTLV_REW(x)  VTSS_EXTRACT_BITFIELD(x,12,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_SAM_SEQ_LBM_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_SAM_SEQ_LBM_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),11,1)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_SAM_SEQ_LBM_REW  VTSS_BIT(11)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_SAM_SEQ_LBM_REW(x)  VTSS_EXTRACT_BITFIELD(x,11,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_SAM_SEQ_CCM_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_SAM_SEQ_CCM_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),10,1)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_SAM_SEQ_CCM_REW  VTSS_BIT(10)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_SAM_SEQ_CCM_REW(x)  VTSS_EXTRACT_BITFIELD(x,10,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_SAM_SEQ_IDX_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_SAM_SEQ_IDX_REW(x)  VTSS_ENCODE_BITFIELD(x,5,5)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_SAM_SEQ_IDX_REW     VTSS_ENCODE_BITMASK(5,5)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_SAM_SEQ_IDX_REW(x)  VTSS_EXTRACT_BITFIELD(x,5,5)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_NON_OAM_ERR_CNT_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_NON_OAM_ERR_CNT_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_NON_OAM_ERR_CNT_REW  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_NON_OAM_ERR_CNT_REW(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_NON_OAM_FWD_ERR_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_NON_OAM_FWD_ERR_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_NON_OAM_FWD_ERR_REW  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_NON_OAM_FWD_ERR_REW(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INFO_REW . CT_SYNLM_PEER_IDX_REW
 */
#define  VTSS_F_VOP_CT_OAM_INFO_REW_CT_SYNLM_PEER_IDX_REW(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CT_OAM_INFO_REW_CT_SYNLM_PEER_IDX_REW     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CT_OAM_INFO_REW_CT_SYNLM_PEER_IDX_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Context for Y.1731 OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_REW:CT_OAM_INTO1_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_OUTB_PORTS (??), 0-64
 */
#define VTSS_VOP_CT_OAM_INTO1_REW(gi)        VTSS_IOREG_IX(VTSS_TO_VOP,0x3000,gi,16,0,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INTO1_REW . CT_SYNLM_PEER_SGL_REW
 */
#define  VTSS_F_VOP_CT_OAM_INTO1_REW_CT_SYNLM_PEER_SGL_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),15,1)
#define  VTSS_M_VOP_CT_OAM_INTO1_REW_CT_SYNLM_PEER_SGL_REW  VTSS_BIT(15)
#define  VTSS_X_VOP_CT_OAM_INTO1_REW_CT_SYNLM_PEER_SGL_REW(x)  VTSS_EXTRACT_BITFIELD(x,15,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INTO1_REW . CT_SYNLM_PRIO_CFG_REW
 */
#define  VTSS_F_VOP_CT_OAM_INTO1_REW_CT_SYNLM_PRIO_CFG_REW(x)  VTSS_ENCODE_BITFIELD(x,12,3)
#define  VTSS_M_VOP_CT_OAM_INTO1_REW_CT_SYNLM_PRIO_CFG_REW     VTSS_ENCODE_BITMASK(12,3)
#define  VTSS_X_VOP_CT_OAM_INTO1_REW_CT_SYNLM_PRIO_CFG_REW(x)  VTSS_EXTRACT_BITFIELD(x,12,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INTO1_REW . CT_AIS_PERIOD_REW
 */
#define  VTSS_F_VOP_CT_OAM_INTO1_REW_CT_AIS_PERIOD_REW(x)  VTSS_ENCODE_BITFIELD(x,9,3)
#define  VTSS_M_VOP_CT_OAM_INTO1_REW_CT_AIS_PERIOD_REW     VTSS_ENCODE_BITMASK(9,3)
#define  VTSS_X_VOP_CT_OAM_INTO1_REW_CT_AIS_PERIOD_REW(x)  VTSS_EXTRACT_BITFIELD(x,9,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INTO1_REW . CT_LCK_PERIOD_REW
 */
#define  VTSS_F_VOP_CT_OAM_INTO1_REW_CT_LCK_PERIOD_REW(x)  VTSS_ENCODE_BITFIELD(x,6,3)
#define  VTSS_M_VOP_CT_OAM_INTO1_REW_CT_LCK_PERIOD_REW     VTSS_ENCODE_BITMASK(6,3)
#define  VTSS_X_VOP_CT_OAM_INTO1_REW_CT_LCK_PERIOD_REW(x)  VTSS_EXTRACT_BITFIELD(x,6,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INTO1_REW . CT_CSF_PERIOD_REW
 */
#define  VTSS_F_VOP_CT_OAM_INTO1_REW_CT_CSF_PERIOD_REW(x)  VTSS_ENCODE_BITFIELD(x,3,3)
#define  VTSS_M_VOP_CT_OAM_INTO1_REW_CT_CSF_PERIOD_REW     VTSS_ENCODE_BITMASK(3,3)
#define  VTSS_X_VOP_CT_OAM_INTO1_REW_CT_CSF_PERIOD_REW(x)  VTSS_EXTRACT_BITFIELD(x,3,3)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_INTO1_REW . CT_CSF_TYPE_REW
 */
#define  VTSS_F_VOP_CT_OAM_INTO1_REW_CT_CSF_TYPE_REW(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CT_OAM_INTO1_REW_CT_CSF_TYPE_REW     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CT_OAM_INTO1_REW_CT_CSF_TYPE_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief CCM TLV context for Y.1731 OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_REW:CT_OAM_CCM_TLV_INFO_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_OUTB_PORTS (??), 0-64
 */
#define VTSS_VOP_CT_OAM_CCM_TLV_INFO_REW(gi)  VTSS_IOREG_IX(VTSS_TO_VOP,0x3000,gi,16,0,4)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_CCM_TLV_INFO_REW . CT_PORT_STATUS_VLD_REW
 */
#define  VTSS_F_VOP_CT_OAM_CCM_TLV_INFO_REW_CT_PORT_STATUS_VLD_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),6,1)
#define  VTSS_M_VOP_CT_OAM_CCM_TLV_INFO_REW_CT_PORT_STATUS_VLD_REW  VTSS_BIT(6)
#define  VTSS_X_VOP_CT_OAM_CCM_TLV_INFO_REW_CT_PORT_STATUS_VLD_REW(x)  VTSS_EXTRACT_BITFIELD(x,6,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_CCM_TLV_INFO_REW . CT_PORT_STATUS_VALUE_REW
 */
#define  VTSS_F_VOP_CT_OAM_CCM_TLV_INFO_REW_CT_PORT_STATUS_VALUE_REW(x)  VTSS_ENCODE_BITFIELD(x,4,2)
#define  VTSS_M_VOP_CT_OAM_CCM_TLV_INFO_REW_CT_PORT_STATUS_VALUE_REW     VTSS_ENCODE_BITMASK(4,2)
#define  VTSS_X_VOP_CT_OAM_CCM_TLV_INFO_REW_CT_PORT_STATUS_VALUE_REW(x)  VTSS_EXTRACT_BITFIELD(x,4,2)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_CCM_TLV_INFO_REW . CT_IF_STATUS_VLD_REW
 */
#define  VTSS_F_VOP_CT_OAM_CCM_TLV_INFO_REW_CT_IF_STATUS_VLD_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_CCM_TLV_INFO_REW_CT_IF_STATUS_VLD_REW  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_CCM_TLV_INFO_REW_CT_IF_STATUS_VLD_REW(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_CCM_TLV_INFO_REW . CT_IF_STATUS_VALUE_REW
 */
#define  VTSS_F_VOP_CT_OAM_CCM_TLV_INFO_REW_CT_IF_STATUS_VALUE_REW(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CT_OAM_CCM_TLV_INFO_REW_CT_IF_STATUS_VALUE_REW     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CT_OAM_CCM_TLV_INFO_REW_CT_IF_STATUS_VALUE_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Context for MPLS-TP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_REW:CT_OAM_MPLS_INFO_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_OUTB_PORTS (??), 0-64
 */
#define VTSS_VOP_CT_OAM_MPLS_INFO_REW(gi)    VTSS_IOREG_IX(VTSS_TO_VOP,0x3000,gi,16,0,5)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_REW . CT_CODEPOINT_MPLS_REW
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_REW_CT_CODEPOINT_MPLS_REW(x)  VTSS_ENCODE_BITFIELD(x,10,4)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_REW_CT_CODEPOINT_MPLS_REW     VTSS_ENCODE_BITMASK(10,4)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_REW_CT_CODEPOINT_MPLS_REW(x)  VTSS_EXTRACT_BITFIELD(x,10,4)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_REW . CT_EXTRACT_CAUSE_MPLS_REW
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_REW_CT_EXTRACT_CAUSE_MPLS_REW(x)  VTSS_ENCODE_BITFIELD(x,6,4)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_REW_CT_EXTRACT_CAUSE_MPLS_REW     VTSS_ENCODE_BITMASK(6,4)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_REW_CT_EXTRACT_CAUSE_MPLS_REW(x)  VTSS_EXTRACT_BITFIELD(x,6,4)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_REW . CT_BFD_SESSION_SEL_MPLS_REW
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_REW_CT_BFD_SESSION_SEL_MPLS_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_REW_CT_BFD_SESSION_SEL_MPLS_REW  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_REW_CT_BFD_SESSION_SEL_MPLS_REW(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_REW . CT_CLR_BFD_MISS_CNT_MPLS_REW
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_REW_CT_CLR_BFD_MISS_CNT_MPLS_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),4,1)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_REW_CT_CLR_BFD_MISS_CNT_MPLS_REW  VTSS_BIT(4)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_REW_CT_CLR_BFD_MISS_CNT_MPLS_REW(x)  VTSS_EXTRACT_BITFIELD(x,4,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_REW . CT_BFD_TX_UPDATE_ENA_MPLS_REW
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_REW_CT_BFD_TX_UPDATE_ENA_MPLS_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),3,1)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_REW_CT_BFD_TX_UPDATE_ENA_MPLS_REW  VTSS_BIT(3)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_REW_CT_BFD_TX_UPDATE_ENA_MPLS_REW(x)  VTSS_EXTRACT_BITFIELD(x,3,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_REW . CT_BFD_RX_SAMPLE_ENA_MPLS_REW
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_REW_CT_BFD_RX_SAMPLE_ENA_MPLS_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),2,1)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_REW_CT_BFD_RX_SAMPLE_ENA_MPLS_REW  VTSS_BIT(2)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_REW_CT_BFD_RX_SAMPLE_ENA_MPLS_REW(x)  VTSS_EXTRACT_BITFIELD(x,2,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_REW . CT_POLL_BIT_MPLS_REW
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_REW_CT_POLL_BIT_MPLS_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_REW_CT_POLL_BIT_MPLS_REW  VTSS_BIT(1)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_REW_CT_POLL_BIT_MPLS_REW(x)  VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MPLS_INFO_REW . CT_FINAL_BIT_MPLS_REW
 */
#define  VTSS_F_VOP_CT_OAM_MPLS_INFO_REW_CT_FINAL_BIT_MPLS_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_CT_OAM_MPLS_INFO_REW_CT_FINAL_BIT_MPLS_REW  VTSS_BIT(0)
#define  VTSS_X_VOP_CT_OAM_MPLS_INFO_REW_CT_FINAL_BIT_MPLS_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,1)


/**
 * \brief Context for Layer 3 OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_REW:CT_OAM_L3_INFO_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_OUTB_PORTS (??), 0-64
 */
#define VTSS_VOP_CT_OAM_L3_INFO_REW(gi)      VTSS_IOREG_IX(VTSS_TO_VOP,0x3000,gi,16,0,6)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_L3_INFO_REW . CT_SESSION_VLD_L3_REW
 */
#define  VTSS_F_VOP_CT_OAM_L3_INFO_REW_CT_SESSION_VLD_L3_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),5,1)
#define  VTSS_M_VOP_CT_OAM_L3_INFO_REW_CT_SESSION_VLD_L3_REW  VTSS_BIT(5)
#define  VTSS_X_VOP_CT_OAM_L3_INFO_REW_CT_SESSION_VLD_L3_REW(x)  VTSS_EXTRACT_BITFIELD(x,5,1)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_L3_INFO_REW . CT_SESSION_L3_REW
 */
#define  VTSS_F_VOP_CT_OAM_L3_INFO_REW_CT_SESSION_L3_REW(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VOP_CT_OAM_L3_INFO_REW_CT_SESSION_L3_REW     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VOP_CT_OAM_L3_INFO_REW_CT_SESSION_L3_REW(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_L3_INFO_REW . CT_EXTRACT_CAUSE_L3_REW
 */
#define  VTSS_F_VOP_CT_OAM_L3_INFO_REW_CT_EXTRACT_CAUSE_L3_REW(x)  VTSS_ENCODE_BITFIELD(x,0,3)
#define  VTSS_M_VOP_CT_OAM_L3_INFO_REW_CT_EXTRACT_CAUSE_L3_REW     VTSS_ENCODE_BITMASK(0,3)
#define  VTSS_X_VOP_CT_OAM_L3_INFO_REW_CT_EXTRACT_CAUSE_L3_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,3)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_REW:CT_OAM_DATA_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_OUTB_PORTS (??), 0-64
 */
#define VTSS_VOP_CT_OAM_DATA_REW(gi)         VTSS_IOREG_IX(VTSS_TO_VOP,0x3000,gi,16,0,7)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DATA_REW . CT_OAM_DATA_REW
 */
#define  VTSS_F_VOP_CT_OAM_DATA_REW_CT_OAM_DATA_REW(x)  (x)
#define  VTSS_M_VOP_CT_OAM_DATA_REW_CT_OAM_DATA_REW     0xffffffff
#define  VTSS_X_VOP_CT_OAM_DATA_REW_CT_OAM_DATA_REW(x)  (x)


/**
 * \brief Context data
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_REW:CT_OAM_DATA1_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_OUTB_PORTS (??), 0-64
 */
#define VTSS_VOP_CT_OAM_DATA1_REW(gi)        VTSS_IOREG_IX(VTSS_TO_VOP,0x3000,gi,16,0,8)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_DATA1_REW . CT_OAM_DATA1_REW
 */
#define  VTSS_F_VOP_CT_OAM_DATA1_REW_CT_OAM_DATA1_REW(x)  (x)
#define  VTSS_M_VOP_CT_OAM_DATA1_REW_CT_OAM_DATA1_REW     0xffffffff
#define  VTSS_X_VOP_CT_OAM_DATA1_REW_CT_OAM_DATA1_REW(x)  (x)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_REW:CT_OAM_MRP_INFO_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_OUTB_PORTS (??), 0-64
 */
#define VTSS_VOP_CT_OAM_MRP_INFO_REW(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x3000,gi,16,0,9)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_REW . CT_FRM_TYPE_REW
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_REW_CT_FRM_TYPE_REW(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_REW_CT_FRM_TYPE_REW     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_REW_CT_FRM_TYPE_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_REW:CT_OAM_MRP_INFO_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_OUTB_PORTS (??), 0-64
 */
#define VTSS_VOP_CT_OAM_MRP_INFO_REW(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x3000,gi,16,0,9)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_REW . CT_FRM_TYPE_REW
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_REW_CT_FRM_TYPE_REW(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_REW_CT_FRM_TYPE_REW     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_REW_CT_FRM_TYPE_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_REW:CT_OAM_MRP_INFO_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_OUTB_PORTS (??), 0-64
 */
#define VTSS_VOP_CT_OAM_MRP_INFO_REW(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x3000,gi,16,0,9)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_REW . CT_FRM_TYPE_REW
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_REW_CT_FRM_TYPE_REW(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_REW_CT_FRM_TYPE_REW     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_REW_CT_FRM_TYPE_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,2)


/**
 * \brief Context for MRP OAM PDUs.
 *
 * \details
 * Register: \a VOP:VOE_CONTEXT_REW:CT_OAM_MRP_INFO_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_CELLBUS_OUTB_PORTS (??), 0-64
 */
#define VTSS_VOP_CT_OAM_MRP_INFO_REW(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x3000,gi,16,0,9)

/**
 * \details
 * Field: ::VTSS_VOP_CT_OAM_MRP_INFO_REW . CT_FRM_TYPE_REW
 */
#define  VTSS_F_VOP_CT_OAM_MRP_INFO_REW_CT_FRM_TYPE_REW(x)  VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VOP_CT_OAM_MRP_INFO_REW_CT_FRM_TYPE_REW     VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VOP_CT_OAM_MRP_INFO_REW_CT_FRM_TYPE_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,2)

/**
 * Register Group: \a VOP:VOE_CRC_ERR
 *
 * Count the number of CRC errors in Rx LBR / TST TLVs
 */


/**
 * \brief Count the number of LBR and TST CRC errors received.
 *
 * \details
 * The VOE can verify the CRC-32 of Test TLVs in incoming LBR and TST PDUs.
 *
 * This functionality is enabled using one of the following bit fields:
 *
 *  * VOP:VOE_CONF:OAM_HW_CTRL.LBR_TLV_CRC_VERIFY_ENA
 *  * VOP:VOE_CONF:OAM_HW_CTRL.TST_TLV_CRC_VERIFY_ENA
 *
 * When enabled the VOE examines the TLV field of valid LBR and TST PDUs in
 * the Rx direction.
 * If the first TLV following the LBR or TST PDU is a Test TLV including a
 * CRC-32 across the Data Pattern, the VOE will calculate the CRC across
 * the Data Pattern and verify the CRC-32.
 *
 * This register will count the number of CRC errors received by the VOE.
 *
 * The CRC counters are indexed as follows:
 *  * Service (/Path) VOEs are indexed: 0 - 31
 *  * Port VOEs are indexed: 32 (Port 0) - 61 (Port 29)
 *
 * Register: \a VOP:VOE_CRC_ERR:LBR_CRC_ERR_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_TOTAL_VOE (??), 0-61
 */
#define VTSS_VOP_LBR_CRC_ERR_CNT(gi)         VTSS_IOREG_IX(VTSS_TO_VOP,0x3540,gi,1,0,0)

/**
 * \brief
 * See Register Description.
 *
 * \details
 * Field: ::VTSS_VOP_LBR_CRC_ERR_CNT . LBR_CRC_ERR_CNT
 */
#define  VTSS_F_VOP_LBR_CRC_ERR_CNT_LBR_CRC_ERR_CNT(x)  (x)
#define  VTSS_M_VOP_LBR_CRC_ERR_CNT_LBR_CRC_ERR_CNT     0xffffffff
#define  VTSS_X_VOP_LBR_CRC_ERR_CNT_LBR_CRC_ERR_CNT(x)  (x)

/**
 * Register Group: \a VOP:ANA_COSID_MAP_CONF
 *
 * COSID / Color config in ANA - Service VOEs
 */


/**
 * \brief COSID mapping table
 *
 * \details
 * COSID mapping table used for mapping the selected COSID values.
 *
 * A single mapping table is available for each of the Service/Path VOEs.
 *
 * Register: \a VOP:ANA_COSID_MAP_CONF:COSID_MAP_TABLE_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_VOE (??), 0-31
 */
#define VTSS_VOP_COSID_MAP_TABLE_ANA(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x3440,gi,2,0,0)

/**
 * \brief
 * The table is used to map the chosen COSID in the ANA.bit(2:0) will be
 * used to map COSID = 0bit(5:3) will be used to map COSID = 1...bit(23:21)
 * will be used to map COSID = 7When mapping a COSID, the following
 * procedure is followed:1) Use COSID_SRC_SEL_ANA to select the source of
 * the COSID mapping.I.e. if COSID_SRC_SEL_ANA = 1 (TC) the input to the
 * mapping table is set to the IFH.TC.2) Map the selected value.If IFH.TC =
 * 3, the mapped COSID will be set to COSID_MAP_TABLE_ANA[11:9]
 *
 * \details
 * Field: ::VTSS_VOP_COSID_MAP_TABLE_ANA . COSID_MAP_TABLE_ANA
 */
#define  VTSS_F_VOP_COSID_MAP_TABLE_ANA_COSID_MAP_TABLE_ANA(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_VOP_COSID_MAP_TABLE_ANA_COSID_MAP_TABLE_ANA     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_VOP_COSID_MAP_TABLE_ANA_COSID_MAP_TABLE_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief COSID / Color control signals
 *
 * \details
 * The bit fields in this register determines the source of the COSID
 * mapping / COLOR of frames not processed by the VOE.
 *
 * Register: \a VOP:ANA_COSID_MAP_CONF:COSID_MAP_CFG_ANA
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_VOE (??), 0-31
 */
#define VTSS_VOP_COSID_MAP_CFG_ANA(gi)       VTSS_IOREG_IX(VTSS_TO_VOP,0x3440,gi,2,0,1)

/**
 * \brief
 * Selects the source of the COSID mapping.
 *
 * \details
 * "00": ifh.cosid
 * "01": ifh.tc
 * "10": ifh_iprio
 * "11": ANA_CL:MAP_TBL:MAP_ENTRY.PATH_COSID_VAL (Output from mapping
 * table. Do not use for Up-MEP)
 *
 * Field: ::VTSS_VOP_COSID_MAP_CFG_ANA . COSID_SRC_SEL_ANA
 */
#define  VTSS_F_VOP_COSID_MAP_CFG_ANA_COSID_SRC_SEL_ANA(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VOP_COSID_MAP_CFG_ANA_COSID_SRC_SEL_ANA     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VOP_COSID_MAP_CFG_ANA_COSID_SRC_SEL_ANA(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Determines which internal signal carries color for the current VOE.This
 * configuration is only used in ANA, the corresponding configuration in
 * the REW is not used.
 *
 * \details
 * "00": ifh.dp_color
 * "01": ifh.cl_dei
 * "10": ANA_CL:MAP_TBL:MAP_ENTRY.PATH_COLOR_VAL (Output from mapping
 * table. Do not use for Up-MEP)
 * "11": reserved for future use (do not use)
 *
 * Field: ::VTSS_VOP_COSID_MAP_CFG_ANA . COLOR_SRC_SEL_ANA
 */
#define  VTSS_F_VOP_COSID_MAP_CFG_ANA_COLOR_SRC_SEL_ANA(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_VOP_COSID_MAP_CFG_ANA_COLOR_SRC_SEL_ANA     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_VOP_COSID_MAP_CFG_ANA_COLOR_SRC_SEL_ANA(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * Determines if the VOE LM counters counts all frames or only GREEN
 * frames.
 *
 * \details
 * '0': do not include yellow frames in the LM count.
 * '1': include yellow frames in the LM count.
 *
 * Field: ::VTSS_VOP_COSID_MAP_CFG_ANA . CNT_YELLOW_ANA
 */
#define  VTSS_F_VOP_COSID_MAP_CFG_ANA_CNT_YELLOW_ANA(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_COSID_MAP_CFG_ANA_CNT_YELLOW_ANA  VTSS_BIT(0)
#define  VTSS_X_VOP_COSID_MAP_CFG_ANA_CNT_YELLOW_ANA(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a VOP:REW_COSID_MAP_CONF
 *
 * COSID / Color config in REW - Service VOEs
 */


/**
 * \brief COSID mapping table
 *
 * \details
 * COSID mapping table used for mapping the selected COSID values.
 *
 * A single mapping table is available for each of the Service/Path VOEs.
 *
 * Register: \a VOP:REW_COSID_MAP_CONF:COSID_MAP_TABLE_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_VOE (??), 0-31
 */
#define VTSS_VOP_COSID_MAP_TABLE_REW(gi)     VTSS_IOREG_IX(VTSS_TO_VOP,0x3480,gi,2,0,0)

/**
 * \brief
 * The table is used to map the chosen COSID in the REW.bit(2:0) will be
 * used to map COSID = 0bit(5:3) will be used to map COSID = 1...bit(23:21)
 * will be used to map COSID = 7When mapping a COSID, the following
 * procedure is followed:1) Use COSID_SRC_SEL_REW to select the source of
 * the COSID mapping.I.e. if COSID_SRC_SEL_REW = 1 (TC) the input to the
 * mapping table is set to the IFH.TC.2) Map the selected value.If IFH.TC =
 * 3, the mapped COSID will be set to COSID_MAP_TABLE_REW[11:9]
 *
 * \details
 * Field: ::VTSS_VOP_COSID_MAP_TABLE_REW . COSID_MAP_TABLE_REW
 */
#define  VTSS_F_VOP_COSID_MAP_TABLE_REW_COSID_MAP_TABLE_REW(x)  VTSS_ENCODE_BITFIELD(x,0,24)
#define  VTSS_M_VOP_COSID_MAP_TABLE_REW_COSID_MAP_TABLE_REW     VTSS_ENCODE_BITMASK(0,24)
#define  VTSS_X_VOP_COSID_MAP_TABLE_REW_COSID_MAP_TABLE_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,24)


/**
 * \brief COSID / Color control signals
 *
 * \details
 * The bit fields in this register determines the source of the COSID
 * mapping / COLOR of frames not processed by the VOE.
 *
 * Register: \a VOP:REW_COSID_MAP_CONF:COSID_MAP_CFG_REW
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_VOE (??), 0-31
 */
#define VTSS_VOP_COSID_MAP_CFG_REW(gi)       VTSS_IOREG_IX(VTSS_TO_VOP,0x3480,gi,2,0,1)

/**
 * \brief
 * Selects the source of the COSID mapping.
 *
 * \details
 * "00": ifh.cosid
 * "01": ifh.tc
 * "10": ifh_iprio
 * "11":
 * REW:MAP_RES_A:MAP_VAL_A.OAM_COSID/REW:MAP_RES_B:MAP_VAL_B.OAM_COSID
 * (Output from the mapping table)
 *
 * Field: ::VTSS_VOP_COSID_MAP_CFG_REW . COSID_SRC_SEL_REW
 */
#define  VTSS_F_VOP_COSID_MAP_CFG_REW_COSID_SRC_SEL_REW(x)  VTSS_ENCODE_BITFIELD(x,3,2)
#define  VTSS_M_VOP_COSID_MAP_CFG_REW_COSID_SRC_SEL_REW     VTSS_ENCODE_BITMASK(3,2)
#define  VTSS_X_VOP_COSID_MAP_CFG_REW_COSID_SRC_SEL_REW(x)  VTSS_EXTRACT_BITFIELD(x,3,2)

/**
 * \brief
 * Determines which internal signal carries color for the current VOE.
 *
 * \details
 * "00": ifh.dp_color
 * "01": ifh.cl_dei
 * "10":
 * REW:MAP_RES_A:MAP_VAL_A.OAM_COLOR/REW:MAP_RES_B:MAP_VAL_B.OAM_COLOR
 * (Output from the mapping table)
 * "11": reserved for future use (do not use)
 *
 * Field: ::VTSS_VOP_COSID_MAP_CFG_REW . COLOR_SRC_SEL_REW
 */
#define  VTSS_F_VOP_COSID_MAP_CFG_REW_COLOR_SRC_SEL_REW(x)  VTSS_ENCODE_BITFIELD(x,1,2)
#define  VTSS_M_VOP_COSID_MAP_CFG_REW_COLOR_SRC_SEL_REW     VTSS_ENCODE_BITMASK(1,2)
#define  VTSS_X_VOP_COSID_MAP_CFG_REW_COLOR_SRC_SEL_REW(x)  VTSS_EXTRACT_BITFIELD(x,1,2)

/**
 * \brief
 * Determines if the VOE LM counters counts all frames or only GREEN
 * frames.
 *
 * \details
 * '0': do not include yellow frames in the LM count.
 * '1': include yellow frames in the LM count.
 *
 * Field: ::VTSS_VOP_COSID_MAP_CFG_REW . CNT_YELLOW_REW
 */
#define  VTSS_F_VOP_COSID_MAP_CFG_REW_CNT_YELLOW_REW(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_COSID_MAP_CFG_REW_CNT_YELLOW_REW  VTSS_BIT(0)
#define  VTSS_X_VOP_COSID_MAP_CFG_REW_CNT_YELLOW_REW(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a VOP:PORT_COSID_MAP_CONF
 *
 * COSID / Color config - Port VOEs
 */


/**
 * \brief LSB of Rx Port VOE mapping table (ANA).
 *
 * \details
 * This register contains the lower 32 bits of the Port VOE Rx (ANA) COSID
 * mapping table.
 *
 * The mapping in this register is used when Port DEI = 0.
 *
 * Register: \a VOP:PORT_COSID_MAP_CONF:PORT_RX_COSID_MAP
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_ETH_PORTS (??), 0-29
 */
#define VTSS_VOP_PORT_RX_COSID_MAP(gi)       VTSS_IOREG_IX(VTSS_TO_VOP,0x1f80,gi,4,0,0)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_PORT_RX_COSID_MAP . PORT_RX_COSID_MAP
 */
#define  VTSS_F_VOP_PORT_RX_COSID_MAP_PORT_RX_COSID_MAP(x)  (x)
#define  VTSS_M_VOP_PORT_RX_COSID_MAP_PORT_RX_COSID_MAP     0xffffffff
#define  VTSS_X_VOP_PORT_RX_COSID_MAP_PORT_RX_COSID_MAP(x)  (x)


/**
 * \brief MSB of Rx Port VOE mapping table (ANA).
 *
 * \details
 * This register contains the upper 32 bits of the Port VOE Rx (ANA) COSID
 * mapping table.
 *
 * This mapping in this register is used when Port DEI = 1
 *
 * Register: \a VOP:PORT_COSID_MAP_CONF:PORT_RX_COSID_MAP1
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_ETH_PORTS (??), 0-29
 */
#define VTSS_VOP_PORT_RX_COSID_MAP1(gi)      VTSS_IOREG_IX(VTSS_TO_VOP,0x1f80,gi,4,0,1)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_PORT_RX_COSID_MAP1 . PORT_RX_COSID_MAP1
 */
#define  VTSS_F_VOP_PORT_RX_COSID_MAP1_PORT_RX_COSID_MAP1(x)  (x)
#define  VTSS_M_VOP_PORT_RX_COSID_MAP1_PORT_RX_COSID_MAP1     0xffffffff
#define  VTSS_X_VOP_PORT_RX_COSID_MAP1_PORT_RX_COSID_MAP1(x)  (x)


/**
 * \brief LSB of Tx Port VOE mapping table (REW).
 *
 * \details
 * This register contains the lower 32 bits of the Port VOE Tx (REW) COSID
 * mapping table.
 *
 * This mapping in this register is used when Port DEI = 0
 *
 * Register: \a VOP:PORT_COSID_MAP_CONF:PORT_TX_COSID_MAP
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_ETH_PORTS (??), 0-29
 */
#define VTSS_VOP_PORT_TX_COSID_MAP(gi)       VTSS_IOREG_IX(VTSS_TO_VOP,0x1f80,gi,4,0,2)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_PORT_TX_COSID_MAP . PORT_TX_COSID_MAP
 */
#define  VTSS_F_VOP_PORT_TX_COSID_MAP_PORT_TX_COSID_MAP(x)  (x)
#define  VTSS_M_VOP_PORT_TX_COSID_MAP_PORT_TX_COSID_MAP     0xffffffff
#define  VTSS_X_VOP_PORT_TX_COSID_MAP_PORT_TX_COSID_MAP(x)  (x)


/**
 * \brief MSB of Tx Port VOE mapping table (REW).
 *
 * \details
 * This register contains the upper 32 bits of the Port VOE Tx (REW) COSID
 * mapping table.
 *
 * This mapping in this register is used when Port DEI = 1
 *
 * Register: \a VOP:PORT_COSID_MAP_CONF:PORT_TX_COSID_MAP1
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_NUM_ETH_PORTS (??), 0-29
 */
#define VTSS_VOP_PORT_TX_COSID_MAP1(gi)      VTSS_IOREG_IX(VTSS_TO_VOP,0x1f80,gi,4,0,3)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_PORT_TX_COSID_MAP1 . PORT_TX_COSID_MAP1
 */
#define  VTSS_F_VOP_PORT_TX_COSID_MAP1_PORT_TX_COSID_MAP1(x)  (x)
#define  VTSS_M_VOP_PORT_TX_COSID_MAP1_PORT_TX_COSID_MAP1     0xffffffff
#define  VTSS_X_VOP_PORT_TX_COSID_MAP1_PORT_TX_COSID_MAP1(x)  (x)

/**
 * Register Group: \a VOP:SAM_COSID_SEQ_CNT
 *
 * SAM per COSID sequence counters
 */


/**
 * \brief LBM/TST/CCM Tx PDUs per priority.
 *
 * \details
 * When a VOE is assigned a SAM per COSID counter set, this register counts
 * the number of Tx CCM/LBM/TST PDUs for priorities 0-6.
 * Depending on the PDU being counted, priority 7 is counted by the
 * following counter.
 *
 * CCM:
 *  * VOP:VOE_STAT:CCM_TX_SEQ_CFG.CCM_TX_SEQ
 *
 * LBM/LBR:
 *  * VOP:VOE_STAT:LBM_TX_TRANSID_CFG.LBM_TX_TRANSID
 *
 * TST:
 *  * VOP:VOE_STAT:LBM_TX_TRANSID_CFG.LBM_TX_TRANSID
 *
 * Register: \a VOP:SAM_COSID_SEQ_CNT:SAM_LBM_TX_TRANSID
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_SAM_SEQ_SETS (??), 0-31
 * @param ri Register: SAM_LBM_TX_TRANSID (??), 0-6
 */
#define VTSS_VOP_SAM_LBM_TX_TRANSID(gi,ri)   VTSS_IOREG_IX(VTSS_TO_VOP,0x2000,gi,64,ri,0)

/**
 * \brief
 * See register description
 *
 * \details
 * Field: ::VTSS_VOP_SAM_LBM_TX_TRANSID . SAM_LBM_TX_TRANSID
 */
#define  VTSS_F_VOP_SAM_LBM_TX_TRANSID_SAM_LBM_TX_TRANSID(x)  (x)
#define  VTSS_M_VOP_SAM_LBM_TX_TRANSID_SAM_LBM_TX_TRANSID     0xffffffff
#define  VTSS_X_VOP_SAM_LBM_TX_TRANSID_SAM_LBM_TX_TRANSID(x)  (x)


/**
 * \brief LBR Tx PDUs per priority
 *
 * \details
 * When a VOE is assigned a SAM per COSID counter set, this register counts
 * the number of Tx LBR PDU for priorities 0-6.
 * Depending on the PDU being counted, priority 7 is counted by the
 * following counter.
 *
 * CCM: (Not used)
 *
 * LBR:
 *  * VOP:VOE_STAT:LBR_TX_FRM_CNT.LBR_TX_FRM_CNT
 *
 * TST: (Not used)
 *
 * Register: \a VOP:SAM_COSID_SEQ_CNT:SAM_LBR_TX_FRM_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_SAM_SEQ_SETS (??), 0-31
 * @param ri Register: SAM_LBR_TX_FRM_CNT (??), 0-6
 */
#define VTSS_VOP_SAM_LBR_TX_FRM_CNT(gi,ri)   VTSS_IOREG_IX(VTSS_TO_VOP,0x2000,gi,64,ri,7)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_SAM_LBR_TX_FRM_CNT . SAM_LBR_TX_FRM_CNT
 */
#define  VTSS_F_VOP_SAM_LBR_TX_FRM_CNT_SAM_LBR_TX_FRM_CNT(x)  (x)
#define  VTSS_M_VOP_SAM_LBR_TX_FRM_CNT_SAM_LBR_TX_FRM_CNT     0xffffffff
#define  VTSS_X_VOP_SAM_LBR_TX_FRM_CNT_SAM_LBR_TX_FRM_CNT(x)  (x)


/**
 * \brief LBR/TST/CCM Rx PDUs per priority
 *
 * \details
 * When a VOE is assigned a SAM per COSID counter set, this register counts
 * the number of Rx LBR/TST/CCM PDU for priorities 0-6.
 * Depending on the PDU being counted, priority 7 is counted by the
 * following counter.
 *
 * CCM:
 *  * VOP:VOE_STAT:CCM_RX_FRM_CNT.CCM_RX_VLD_FC_CNT
 *
 * LBM/LBR:
 *  * VOP:VOE_STAT: LBR_RX_FRM_CNT.LBR_RX_FRM_CNT
 *
 * TST:
 *  * VOP:VOE_STAT: LBR_RX_FRM_CNT.LBR_RX_FRM_CNT
 *
 * Register: \a VOP:SAM_COSID_SEQ_CNT:SAM_LBR_RX_FRM_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_SAM_SEQ_SETS (??), 0-31
 * @param ri Register: SAM_LBR_RX_FRM_CNT (??), 0-6
 */
#define VTSS_VOP_SAM_LBR_RX_FRM_CNT(gi,ri)   VTSS_IOREG_IX(VTSS_TO_VOP,0x2000,gi,64,ri,14)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_SAM_LBR_RX_FRM_CNT . SAM_LBR_RX_FRM_CNT
 */
#define  VTSS_F_VOP_SAM_LBR_RX_FRM_CNT_SAM_LBR_RX_FRM_CNT(x)  (x)
#define  VTSS_M_VOP_SAM_LBR_RX_FRM_CNT_SAM_LBR_RX_FRM_CNT     0xffffffff
#define  VTSS_X_VOP_SAM_LBR_RX_FRM_CNT_SAM_LBR_RX_FRM_CNT(x)  (x)


/**
 * \brief LBR/TST/CCM Rx Transaction ID per priority
 *
 * \details
 * When a VOE is assigned a SAM per COSID counter set, this register counts
 * the latest Sequence Number / Transaction ID received in a valid
 * LBR/TST/CCM PDU for priorities 0-6.
 * Depending on the PDU being counted, priority 7 is stored in the
 * following register.
 *
 * CCM:
 *  * VOP:VOE_STAT:CCM_RX_SEQ_CFG.CCM_RX_SEQ
 *
 * LBM/LBR:
 *  * VOP:VOE_STAT:LBR_RX_TRANSID_CFG.LBR_RX_TRANSID
 *
 * TST:
 *  * VOP:VOE_STAT:LBR_RX_TRANSID_CFG.LBR_RX_TRANSID
 *
 * Register: \a VOP:SAM_COSID_SEQ_CNT:SAM_LBR_RX_TRANSID
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_SAM_SEQ_SETS (??), 0-31
 * @param ri Register: SAM_LBR_RX_TRANSID (??), 0-6
 */
#define VTSS_VOP_SAM_LBR_RX_TRANSID(gi,ri)   VTSS_IOREG_IX(VTSS_TO_VOP,0x2000,gi,64,ri,21)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_SAM_LBR_RX_TRANSID . SAM_LBR_RX_TRANSID
 */
#define  VTSS_F_VOP_SAM_LBR_RX_TRANSID_SAM_LBR_RX_TRANSID(x)  (x)
#define  VTSS_M_VOP_SAM_LBR_RX_TRANSID_SAM_LBR_RX_TRANSID     0xffffffff
#define  VTSS_X_VOP_SAM_LBR_RX_TRANSID_SAM_LBR_RX_TRANSID(x)  (x)


/**
 * \brief LBR/TST/CCM out of sequence errors per priority
 *
 * \details
 * When a VOE is assigned a SAM per COSID counter set, this register counts
 * the number of out-of-sequence errors for LBR/TST/CCM PDUs for priorities
 * 0-6.
 * Depending on the PDU being counted, priority 7 is counted in the
 * following counter.
 *
 * CCM:
 *  *  VOP:VOE_STAT:CCM_RX_WARNING.CCM_RX_SEQNO_ERR_CNT
 *
 * LBM/LBR:
 *  * VOP:VOE_STAT:LBR_RX_TRANSID_ERR_CNT.LBR_RX_TRANSID_ERR_CNT
 *
 * TST:
 *  * VOP:VOE_STAT:LBR_RX_TRANSID_ERR_CNT.LBR_RX_TRANSID_ERR_CNT
 *
 * Register: \a VOP:SAM_COSID_SEQ_CNT:SAM_LBR_RX_TRANSID_ERR_CNT
 *
 * @param gi Replicator: x_VTSS_OAM_MEP_SAM_SEQ_SETS (??), 0-31
 * @param ri Register: SAM_LBR_RX_TRANSID_ERR_CNT (??), 0-6
 */
#define VTSS_VOP_SAM_LBR_RX_TRANSID_ERR_CNT(gi,ri)  VTSS_IOREG_IX(VTSS_TO_VOP,0x2000,gi,64,ri,28)

/**
 * \brief
 * See register description.
 *
 * \details
 * Field: ::VTSS_VOP_SAM_LBR_RX_TRANSID_ERR_CNT . SAM_LBR_RX_TRANSID_ERR_CNT
 */
#define  VTSS_F_VOP_SAM_LBR_RX_TRANSID_ERR_CNT_SAM_LBR_RX_TRANSID_ERR_CNT(x)  VTSS_ENCODE_BITFIELD(x,0,16)
#define  VTSS_M_VOP_SAM_LBR_RX_TRANSID_ERR_CNT_SAM_LBR_RX_TRANSID_ERR_CNT     VTSS_ENCODE_BITMASK(0,16)
#define  VTSS_X_VOP_SAM_LBR_RX_TRANSID_ERR_CNT_SAM_LBR_RX_TRANSID_ERR_CNT(x)  VTSS_EXTRACT_BITFIELD(x,0,16)

/**
 * Register Group: \a VOP:RAM_CTRL
 *
 * Access core memory
 */


/**
 * \brief Core reset control
 *
 * \details
 * Controls reset and initialization of the switching core. Proper startup
 * sequence is:
 * - Enable memories
 * - Initialize memories
 * - Enable core
 *
 * Register: \a VOP:RAM_CTRL:RAM_INIT
 */
#define VTSS_VOP_RAM_INIT                    VTSS_IOREG(VTSS_TO_VOP,0xffc)

/**
 * \brief
 * Testing options for memories
 *
 * \details
 * xx1: Make parity errors on all memories
 * x1x: Make parity errors on local ring memories
 * 1xx: Make parity errors only at writes from software
 *
 * Field: ::VTSS_VOP_RAM_INIT . RAM_TEST_OPT
 */
#define  VTSS_F_VOP_RAM_INIT_RAM_TEST_OPT(x)  VTSS_ENCODE_BITFIELD(x,2,3)
#define  VTSS_M_VOP_RAM_INIT_RAM_TEST_OPT     VTSS_ENCODE_BITMASK(2,3)
#define  VTSS_X_VOP_RAM_INIT_RAM_TEST_OPT(x)  VTSS_EXTRACT_BITFIELD(x,2,3)

/**
 * \brief
 * Initialize core memories. Field is automatically cleared when operation
 * is complete (approx. 40 us).
 *
 * \details
 * Field: ::VTSS_VOP_RAM_INIT . RAM_INIT
 */
#define  VTSS_F_VOP_RAM_INIT_RAM_INIT(x)      VTSS_ENCODE_BITFIELD(!!(x),1,1)
#define  VTSS_M_VOP_RAM_INIT_RAM_INIT         VTSS_BIT(1)
#define  VTSS_X_VOP_RAM_INIT_RAM_INIT(x)      VTSS_EXTRACT_BITFIELD(x,1,1)

/**
 * \brief
 * When this field is set, all memories HA_RESTART behavior will be
 * inverted. It is a backdoor for potentiel access issues.
 *
 * \details
 * Field: ::VTSS_VOP_RAM_INIT . RAM_CFG_HOOK
 */
#define  VTSS_F_VOP_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_ENCODE_BITFIELD(!!(x),0,1)
#define  VTSS_M_VOP_RAM_INIT_RAM_CFG_HOOK     VTSS_BIT(0)
#define  VTSS_X_VOP_RAM_INIT_RAM_CFG_HOOK(x)  VTSS_EXTRACT_BITFIELD(x,0,1)

/**
 * Register Group: \a VOP:COREMEM
 *
 * Access core memory
 */


/**
 * \brief Address selection
 *
 * \details
 * Register: \a VOP:COREMEM:CM_ADDR
 */
#define VTSS_VOP_CM_ADDR                     VTSS_IOREG(VTSS_TO_VOP,0x1ff8)

/**
 * \brief
 * Address selection for the ram debug address space.
 *
 * \details
 * Field: ::VTSS_VOP_CM_ADDR . CM_ADDR
 */
#define  VTSS_F_VOP_CM_ADDR_CM_ADDR(x)        (x)
#define  VTSS_M_VOP_CM_ADDR_CM_ADDR           0xffffffff
#define  VTSS_X_VOP_CM_ADDR_CM_ADDR(x)        (x)


/**
 * \brief Data register for core memory access.
 *
 * \details
 * Register: \a VOP:COREMEM:CM_DATA_WR
 */
#define VTSS_VOP_CM_DATA_WR                  VTSS_IOREG(VTSS_TO_VOP,0x1ff9)

/**
 * \brief
 * Data register for core memory access. Wider memories are big endian
 * mapped into the 32 bit inspection space. This register provides data to
 * be written when CM_OP is set.When CM_OP is set to 11 this register
 * encodes ram checking mode:-single /double parity errors induced on
 * writes-all chip memories or only the memories connected to this init
 * controller-errors at any write or only by software access
 *
 * \details
 * 000: No testing
 * 001: Single, local, any write
 * 010: Single, all, any write
 * 011: Single, local, s/w write
 * 100: Single, all, s/w write
 * 101: Double, local. s/w write
 * 110: Double, all, s/w write
 * 111: Solve climate crisis
 *
 * Field: ::VTSS_VOP_CM_DATA_WR . CM_DATA_WR
 */
#define  VTSS_F_VOP_CM_DATA_WR_CM_DATA_WR(x)  (x)
#define  VTSS_M_VOP_CM_DATA_WR_CM_DATA_WR     0xffffffff
#define  VTSS_X_VOP_CM_DATA_WR_CM_DATA_WR(x)  (x)


/**
 * \brief Core memory data register for read result
 *
 * \details
 * Register: \a VOP:COREMEM:CM_DATA_RD
 */
#define VTSS_VOP_CM_DATA_RD                  VTSS_IOREG(VTSS_TO_VOP,0x1ffa)

/**
 * \brief
 * Read result
 *
 * \details
 * Field: ::VTSS_VOP_CM_DATA_RD . CM_DATA_RD
 */
#define  VTSS_F_VOP_CM_DATA_RD_CM_DATA_RD(x)  (x)
#define  VTSS_M_VOP_CM_DATA_RD_CM_DATA_RD     0xffffffff
#define  VTSS_X_VOP_CM_DATA_RD_CM_DATA_RD(x)  (x)


/**
 * \brief Operation to perform in core memory
 *
 * \details
 * Register: \a VOP:COREMEM:CM_OP
 */
#define VTSS_VOP_CM_OP                       VTSS_IOREG(VTSS_TO_VOP,0x1ffb)

/**
 * \brief
 * Ask the memory debug system to read or write a specific location. If no
 * response is received from a memory, due to timeout, or selected address
 * out of range, the state machine can be reset by issuing the 11
 * command.Field will return to 00 upon completion.When the 11 command is
 * issued, cm_data_wr(2..0) enables ram test modes.000: No testing001:
 * Single error induced on local memories010: Single error induced on all
 * memories011: Single error induced on local memories accessed from
 * software only100: Single error induced on all memories accessed from
 * software only101: Double error induced on local memories from software
 * only110: Double error induced on all memories from software only111:
 * Solve climate crisis
 *
 * \details
 * 00: NOP
 * 01: Read from selected address into CM_DATA_RD
 * 10: Write CM_DATA_WR into selected address
 * 11: Reset debug access and configure test mode
 *
 * Field: ::VTSS_VOP_CM_OP . CM_OP
 */
#define  VTSS_F_VOP_CM_OP_CM_OP(x)            VTSS_ENCODE_BITFIELD(x,0,2)
#define  VTSS_M_VOP_CM_OP_CM_OP               VTSS_ENCODE_BITMASK(0,2)
#define  VTSS_X_VOP_CM_OP_CM_OP(x)            VTSS_EXTRACT_BITFIELD(x,0,2)


#endif /* _VTSS_LAGUNA_REGS_VOP_H_ */

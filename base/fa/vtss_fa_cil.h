// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_CIL_H_
#define _VTSS_FA_CIL_H_

#include "vtss_api.h"

#if defined(VTSS_ARCH_LAN969X_FPGA)
#include "vtss_fa_fpga_cil.h"
#endif

#if defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN969X)
#define VTSS_ARCH_FA
#endif

// Set runtime constant, if smaller than AIL default
#define VTSS_RT_SET(_vs, _rt) { if (_rt < _vs) _vs = _rt; }

#if defined(VTSS_ARCH_FA)
#define VTSS_TRACE_LAYER VTSS_TRACE_LAYER_CIL
#include "../ail/vtss_state.h"
#include "../ail/vtss_common.h"
#include "../ail/vtss_util.h"
#include "../ail/vtss_sd10g28_procs.h"
#include "../ail/vtss_sd25g28_procs.h"
#include "vtss_fa_reg.h"
#include "fla_const_enum.h"
#if !defined(VTSS_ARCH_LAN969X_FPGA)
#include "fla_regs_def.h"
#include "fla_merged_regs.h" // New FA/LA merged header files
#include "fla_vcap_regs.h"   // New FA/LA merged VCAP header files
#endif

#if !defined(VTSS_ARCH_LAN969X_FPGA)
#if defined(VTSS_FEATURE_FDMA) && VTSS_OPT_FDMA
#include "vtss_fa_fdma.h"
#endif

// Fireant port devices:
// D0  - D11                     DEV5G  (12)
// D12 - D15                     DEV10G  (4)
// D16 - D47                     DEV2G5 (32)
// D48 - D55                     DEV10G  (8)
// D56 - D63                     DEV25G  (8)
// D64                           DEV5G   (1)
//                               -----------
//                               65 port devices + 33 DEV2G5 'shadow' devices

// Laguna port devices:
// D1-D3,D5-D7,D10-D11,D14-D15,
// D18-D19.D22-D23,D28-D29       DEV2G5 (16)
// D9,D13,D17,D21                DEV5G  (6)
// D0,D4,D8,D12,D16,D20,D24-D27  DEV10G (10)
//                               -----------
//                               30 port devices + 14 'shadow' devices

// FA/LA compile defines
#define FA_BUFFER_CELL_SZ                   184 // FA=LA

// FA/LA Runtime Defines
#define RT_SERDES_10G_START                 fla_get_const(vtss_state, __RT_SERDES_10G_START)
#define RT_SERDES_25G_START                 fla_get_const(vtss_state, __RT_SERDES_25G_START)
#define RT_SERDES_CNT                       fla_get_const(vtss_state, __RT_SERDES_CNT)
#define RT_CMU_CNT                          fla_get_const(vtss_state, __RT_CMU_CNT)
#define RT_BUFFER_MEMORY                    fla_get_const(vtss_state, __RT_BUFFER_MEMORY)
#define RT_BUFFER_REFERENCE                 fla_get_const(vtss_state, __RT_BUFFER_REFERENCE)
#define RT_RES_CFG_MAX_PORT_IDX             fla_get_const(vtss_state, __RT_RES_CFG_MAX_PORT_IDX)
#define RT_RES_CFG_MAX_PRIO_IDX             fla_get_const(vtss_state, __RT_RES_CFG_MAX_PRIO_IDX)
#define RT_RES_CFG_MAX_COLOUR_IDX           fla_get_const(vtss_state, __RT_RES_CFG_MAX_COLOUR_IDX)
#define RT_CORE_QUEUE_CNT                   fla_get_const(vtss_state, __RT_CORE_QUEUE_CNT)
#define RT_CHIP_PORTS                       vtss_state->chip_const[__RT_CHIP_PORTS]
#define RT_CHIP_PORT_CPU                    RT_CHIP_PORTS
#define RT_CHIP_PORT_CPU_0                  (RT_CHIP_PORT_CPU + 0) /* 1. CPU Port */
#define RT_CHIP_PORT_CPU_1                  (RT_CHIP_PORT_CPU + 1) /* 2. CPU Port */
#define RT_CHIP_PORT_VD0                    (RT_CHIP_PORT_CPU + 2) /* VD0/Port used for IPMC */
#define RT_CHIP_PORT_VD1                    (RT_CHIP_PORT_CPU + 3) /* VD1/Port used for AFI/OAM */
#define RT_CHIP_PORT_VD2                    (RT_CHIP_PORT_CPU + 4) /* VD2/Port used for IPinIP*/
#define RT_CHIP_PORTS_ALL                   (RT_CHIP_PORT_CPU + 5) /* Total number of ports */
#define RT_PORT_ARRAY_SIZE                  (RT_CHIP_PORTS > VTSS_PORT_ARRAY_SIZE ? VTSS_PORT_ARRAY_SIZE : RT_CHIP_PORTS)
#define RT_TAS_NUMBER_OF_LISTS              fla_get_const(vtss_state, __RT_TAS_NUMBER_OF_LISTS)
#define RT_TAS_NUMBER_OF_PROFILES           fla_get_const(vtss_state, __RT_TAS_NUMBER_OF_PROFILES)
#define RT_TAS_NUMBER_OF_ENTRIES            fla_get_const(vtss_state, __RT_TAS_NUMBER_OF_ENTRIES)
#define RT_TAS_NUMBER_OF_ENTRIES_PER_BLOCK  32
#define RT_TAS_NUMBER_OF_BLOCKS_PER_ROW     (VTSS_QOS_TAS_GCL_LEN_MAX / VTSS_TAS_NUMBER_OF_ENTRIES_PER_BLOCK)
#define RT_TAS_NUMBER_OF_ENTRIES_PER_ROW    VTSS_QOS_TAS_GCL_LEN_MAX
#define RT_TAS_NUMBER_OF_ROWS               (VTSS_TAS_NUMBER_OF_ENTRIES/VTSS_TAS_NUMBER_OF_ENTRIES_PER_ROW)
#define RT_EVC_POL_CNT                      fla_get_const(vtss_state, __RT_EVC_POL_CNT)
#define RT_EVC_STAT_CNT                     fla_get_const(vtss_state, __RT_EVC_STAT_CNT)
#define RT_SDX_CNT                          fla_get_const(vtss_state, __RT_SDX_CNT)
#define RT_HSCH_LAYERS                      fla_get_const(vtss_state, __RT_HSCH_LAYERS)
#define RT_HSCH_L0_SES                      fla_get_const(vtss_state, __RT_HSCH_L0_SES)
#define RT_HSCH_L1_SES                      fla_get_const(vtss_state, __RT_HSCH_L1_SES)
#define RT_HSCH_L2_SES                      fla_get_const(vtss_state, __RT_HSCH_L2_SES)
#define RT_HSCH_L3_QSHPS                    fla_get_const(vtss_state, __RT_HSCH_L3_QSHPS)
#define RT_HSCH_MAX_RATE_GROUP_0            fla_get_const(vtss_state, __RT_HSCH_MAX_RATE_GROUP_0)
#define RT_HSCH_MAX_RATE_GROUP_1            fla_get_const(vtss_state, __RT_HSCH_MAX_RATE_GROUP_1)
#define RT_HSCH_MAX_RATE_GROUP_2            fla_get_const(vtss_state, __RT_HSCH_MAX_RATE_GROUP_2)
#define RT_HSCH_MAX_RATE_GROUP_3            fla_get_const(vtss_state, __RT_HSCH_MAX_RATE_GROUP_3)
#define RT_HSCH_MAX_RATE_QSHP_GROUP_0       fla_get_const(vtss_state, __RT_HSCH_MAX_RATE_QSHP_GROUP_0)
#define RT_HSCH_MAX_RATE_QSHP_GROUP_1       fla_get_const(vtss_state, __RT_HSCH_MAX_RATE_QSHP_GROUP_1)
#define RT_HSCH_MAX_RATE_QSHP_GROUP_2       fla_get_const(vtss_state, __RT_HSCH_MAX_RATE_QSHP_GROUP_2)
#define RT_HSCH_MAX_RATE_QSHP_GROUP_3       fla_get_const(vtss_state, __RT_HSCH_MAX_RATE_QSHP_GROUP_3)
#define RT_LB_GROUP_CNT                     fla_get_const(vtss_state, __RT_LB_GROUP_CNT)
#define RT_LB_SET_CNT                       fla_get_const(vtss_state, __RT_LB_SET_CNT)
#define RT_PGID_FA                          fla_get_const(vtss_state, __RT_PGID_FA)
#define RT_MAC_INDEX_CNT                    fla_get_const(vtss_state, __RT_MAC_INDEX_CNT)
#define RT_MAC_ADDRS                        fla_get_const(vtss_state, __RT_MAC_ADDRS)
#define RT_DSM_CAL_MAX_DEVS_PER_TAXI        fla_get_const(vtss_state, __RT_DSM_CAL_MAX_DEVS_PER_TAXI)
#define RT_DSM_CAL_TAXIS                    fla_get_const(vtss_state, __RT_DSM_CAL_TAXIS)
#define RT_MSTREAM_CNT                      fla_get_const(vtss_state, __RT_MSTREAM_CNT)
#define RT_CSTREAM_CNT                      fla_get_const(vtss_state, __RT_CSTREAM_CNT)
#define RT_AFI_SLOW_INJ_CNT                 fla_get_const(vtss_state, __RT_AFI_SLOW_INJ_CNT)
#define RT_AFI_FAST_INJ_BPS_MIN             1000ULL
#define RT_AFI_FAST_INJ_BPS_MAX             (FA_TGT ? 25000000000ULL : 10000000000ULL)
#define RT_PATH_SERVICE_VOE_CNT             fla_get_const(vtss_state, __RT_PATH_SERVICE_VOE_CNT)
#define RT_PORT_VOE_BASE_IDX                fla_get_const(vtss_state, __RT_PORT_VOE_BASE_IDX)
#define RT_PORT_VOE_CNT                     fla_get_const(vtss_state, __RT_PORT_VOE_CNT)
#define RT_DOWN_VOI_CNT                     fla_get_const(vtss_state, __RT_DOWN_VOI_CNT)
#define RT_UP_VOI_CNT                       fla_get_const(vtss_state, __RT_UP_VOI_CNT)
#define RT_VOE_CNT                          ((RT_PATH_SERVICE_VOE_CNT) + (RT_PORT_VOE_CNT))
#define RT_VOI_CNT                          ((RT_DOWN_VOI_CNT) + (RT_UP_VOI_CNT))
#define RT_EVENT_MASK_ARRAY_SIZE            ((RT_VOE_CNT+31)/32)
#define RT_ACL_CNT_SIZE                     fla_get_const(vtss_state, __RT_ACL_CNT_SIZE)
#define RT_ES2_CNT_SIZE                     fla_get_const(vtss_state, __RT_ES2_CNT_SIZE)
#define RT_ES0_CNT                          fla_get_const(vtss_state, __RT_ES0_CNT)
#define RT_ES2_CNT                          fla_get_const(vtss_state, __RT_ES2_CNT)
#define RT_FA_ES2_CNT                       fla_get_const(vtss_state, __RT_FA_ES2_CNT)
#define RT_IP6PFX_CNT                       fla_get_const(vtss_state, __RT_IP6PFX_CNT)
#define RT_VCAP_SUPER_BLK_CNT               fla_get_const(vtss_state, __RT_VCAP_SUPER_BLK_CNT)
#define RT_VCAP_SUPER_RULE_CNT              (RT_VCAP_SUPER_BLK_CNT * VTSS_VCAP_SUPER_ROW_CNT * 6)
#define RT_QOS_EGRESS_MAP_IDS               fla_get_const(vtss_state, __RT_QOS_EGRESS_MAP_IDS)
#define RT_QOS_EGRESS_MAP_ID_END            (VTSS_QOS_EGRESS_MAP_ID_START + RT_QOS_EGRESS_MAP_IDS)
#define RT_QOS_INGRESS_MAP_IDS              fla_get_const(vtss_state, __RT_QOS_INGRESS_MAP_IDS)
#define RT_QOS_INGRESS_MAP_ID_END           (VTSS_QOS_INGRESS_MAP_ID_START + RT_QOS_INGRESS_MAP_IDS)
#define RT_QOS_EGRESS_MAP_ROWS              RT_QOS_EGRESS_MAP_IDS
#define RT_QOS_INGRESS_MAP_ROWS             (RT_QOS_INGRESS_MAP_IDS * 2)
#define RT_QOS_INGRESS_MAP_IX_RESERVED      (RT_QOS_INGRESS_MAP_ROWS - VTSS_QOS_INGRESS_ROW_MIN)

// FA/LA runtimes macros
#define VTSS_PORT_IS_2G5(port)  fla_port_is_2G5(vtss_state, port)
#define VTSS_PORT_IS_5G(port)   fla_port_is_5G(vtss_state, port)
#define VTSS_PORT_IS_10G(port)  fla_port_is_10G(vtss_state, port)
#define VTSS_PORT_IS_25G(port)  fla_port_is_25G(vtss_state, port)

#define VTSS_TO_DEV2G5(port)   vtss_to_dev2g5(vtss_state, port)
#define VTSS_TO_DEV5G(port)    vtss_to_dev5g(vtss_state, port)
#define VTSS_TO_DEV10G(port)   vtss_to_dev10g(vtss_state, port)
#define VTSS_TO_DEV25G(port)   vtss_to_dev25g(vtss_state, port)
#define VTSS_TO_HIGH_DEV(port) VTSS_PORT_IS_5G(port) ? VTSS_TO_DEV5G(port) :  \
                               VTSS_PORT_IS_10G(port) ? VTSS_TO_DEV10G(port) : VTSS_TO_DEV25G(port)
#define VTSS_TO_PCS_TGT(port)  VTSS_PORT_IS_5G(port) ? vtss_to_pcs5g(vtss_state, port) : \
                               VTSS_PORT_IS_10G(port) ? vtss_to_pcs10g(vtss_state, port) : vtss_to_pcs25g(vtss_state, port)
#define VTSS_TO_SD_CMU(indx)  vtss_to_sd_cmu(vtss_state, indx)
#define VTSS_TO_SD_CMU_CFG(indx)  vtss_to_sd_cmu_cfg(vtss_state, indx)
#define VTSS_TO_SD6G_LANE(indx) vtss_to_sd6g_lane(vtss_state, indx)
#define VTSS_TO_SD10G_LANE(indx) vtss_to_sd10g_lane(vtss_state, indx)
#define VTSS_TO_SD25G_LANE(indx) vtss_to_sd25g_lane(vtss_state, indx)
#define VTSS_TO_SD_LANE(indx) vtss_to_sd_lane(vtss_state, indx)

// Fireant has 4 PTP PIN connected to GPIO that can be used for different purposes,
// the defines below defines the default usage of the 4 pins.
// PIN configuration for external clock
#define EXT_CLK_PIN 1               // external clock 1 pps output
// PIN configuration for alternative clock
#define ALT_LDST_PIN 2              // alternative clock 1 pps input (Load/Store)
#define ALT_PPS_PIN  3              // alternative clock 1pps pulse
// The last PTP pin is not connected to GPIO but can be used for TOD access
#define TOD_ACC_PIN 4               // pin used for timeofday get/set

/* ================================================================= *
 *  Register access
 * ================================================================= */
extern vtss_rc (*vtss_fa_wr)(vtss_state_t *vtss_state, u32 addr, u32 value);
extern vtss_rc (*vtss_fa_rd)(vtss_state_t *vtss_state, u32 addr, u32 *value);
vtss_rc vtss_fa_wrm(vtss_state_t *vtss_state, u32 addr, u32 value, u32 mask);
void vtss_fa_reg_error(const char *file, int line, char *txt);

// @param dsg - fa or la
// @param t   - target base offset
// @param o   - group offset
// @param gi  - group instance,
// @param gw  - group width
// @param ri  - register (instance) number
// @param rw  - register width
// @param gc  - group repl count
// @param rc  - register repl count


static inline u32 __ioreg(int dsg, int t, int o, int gi, int gw, int ri, int rw, int gc, int rc)
{
    if ((gi >= gc) || (ri >= rc)) {
        vtss_fa_reg_error(__FILE__, __LINE__, "Illegal register address!");
        return 0xffffffff;
    }
    return (t + (o) + ((gi) * (gw)) + (ri) + (rw));
}

#define IOREG(dsg, t, o, gi, gw, ri, rw, gc, rc) __ioreg(dsg, t, o, gi, gw, ri, rw, gc, rc)

#define REG_ADDR(p) IOREG(p)

#define REG_RD(...) REG_RD_(__VA_ARGS__)
#define REG_RD_(dsg, tgt, off, gr, gw, r, ro, gc, rc, value)           \
    do {                                                               \
        u32 o = __ioreg(dsg, tgt, off, gr, gw, r, ro, gc, rc);         \
        if ((dsg != 0) && vtss_state->chip_design != dsg)              \
            vtss_fa_reg_error(__FILE__, __LINE__,                      \
                              "Register not existing in this chip!");  \
        vtss_rc __rc = vtss_fa_rd(vtss_state, o, value);               \
        if (__rc != VTSS_RC_OK)                                        \
            return __rc;                                               \
    } while (0)

#define REG_WR(...) REG_WR_(__VA_ARGS__)
#define REG_WR_(dsg, tgt, off, gr, gw, r, ro, gc, rc, value)           \
    do {                                                               \
        u32 o = __ioreg(dsg, tgt, off, gr, gw, r, ro, gc, rc);         \
        if ((dsg != 0) && vtss_state->chip_design != dsg)              \
            vtss_fa_reg_error(__FILE__, __LINE__,                      \
                              "Register not existing in this chip!");  \
        vtss_rc __rc = vtss_fa_wr(vtss_state, o, value);               \
        if (__rc != VTSS_RC_OK)                                        \
            return __rc;                                               \
    } while (0)

#define REG_WRM(...) REG_WRM_(__VA_ARGS__)
#define REG_WRM_(dsg, tgt, off, gr, gw, r, ro, gc, rc, value, mask)    \
    do {                                                               \
        u32 o = __ioreg(dsg, tgt, off, gr, gw, r, ro, gc, rc);         \
        if ((dsg != 0) && vtss_state->chip_design != dsg)              \
            vtss_fa_reg_error(__FILE__, __LINE__,                      \
                              "Register not existing in this chip!");  \
        vtss_rc __rc = vtss_fa_wrm(vtss_state, o, value, mask);        \
        if (__rc != VTSS_RC_OK)                                        \
            return __rc;                                               \
    } while (0)

#define REG_WRM_SET(p, mask) REG_WRM(p, mask, mask)
#define REG_WRM_CLR(p, mask) REG_WRM(p, 0,    mask)
#define REG_WRM_CTL(p, _cond_, mask) REG_WRM(p, (_cond_) ? mask : 0, mask)

#define DEV_RD(name, port, value)                                      \
    {                                                                  \
        if (vtss_fa_port_is_high_speed(vtss_state, port)) {            \
            REG_RD(VTSS_DEV10G_##name(VTSS_TO_HIGH_DEV(port)), value); \
        } else {                                                       \
            REG_RD(VTSS_DEV1G_##name(VTSS_TO_DEV2G5(port)), value);    \
        }                                                              \
    }

#define DEV_WR(name, port, value)                                      \
    {                                                                  \
        REG_WR(VTSS_DEV1G_##name(VTSS_TO_DEV2G5(port)), value);        \
        if (!VTSS_PORT_IS_2G5(port)) {                                 \
            REG_WR(VTSS_DEV10G_##name(VTSS_TO_HIGH_DEV(port)), value); \
        }                                                              \
    }

#define DEV_WRM(name, port, value, mask)                                      \
    {                                                                         \
        REG_WRM(VTSS_DEV1G_##name(VTSS_TO_DEV2G5(port)), value, mask);        \
        if (!VTSS_PORT_IS_2G5(port)) {                                        \
            REG_WRM(VTSS_DEV10G_##name(VTSS_TO_HIGH_DEV(port)), value, mask); \
        }                                                                     \
    }

/* Decode register bit field */
#define REG_BF(name, value) ((VTSS_M_##name & value) ? 1 : 0)

/* Poll bits in mask until all are zero */
#define REG_POLL_MASK(_p_, _mask_)                                                  \
    {                                                                               \
        u32 _x_, _cnt_ = 0;                                                         \
        do {                                                                        \
            REG_RD(_p_, &_x_);                                                      \
            VTSS_MSLEEP(1);                                                         \
            if (++_cnt_ == 100) {                                                   \
                VTSS_E("timeout, addr: %s, m: 0x%x, v: 0x%x", #_p_, (_mask_), _x_); \
                return VTSS_RC_ERROR;                                               \
            }                                                                       \
        } while (_x_ & (_mask_));                                                   \
    }

// Determine instance count based on register field
#define REG_FLD_CNT(name) (VTSS_X_##name(VTSS_M_##name) + 1)

// RedBox target offset
#define RB_TGT(i) (VTSS_TO_RB_0 + (i) * (VTSS_TO_RB_1 - VTSS_TO_RB_0))

/* ================================================================= *
 *  Port masks
 * ================================================================= */
#define REG_WR_PMASK(_t, _m)          { REG_WR(_t, (_m).m[0]);                               \
                                        if (FA_TGT) REG_WR(_t##1, (_m).m[1]);                \
                                        if (FA_TGT) REG_WR(_t##2, (_m).m[2]);                }
#define REG_WRX_PMASK(_t, x, _m)      {                                                      \
                                       REG_WR(_t(x), (_m).m[0]);                             \
                                       if (FA_TGT) REG_WR(_t##1(x), (_m).m[1]);              \
                                       if (FA_TGT) REG_WR(_t##2(x), (_m).m[2]);              }
#define REG_WRM_PMASK(_t, _v, _m)     { REG_WRM(_t, (_v).m[0], (_m).m[0]);                   \
                                        if (FA_TGT) REG_WRM(_t##1, (_v).m[1], (_m).m[1]);    \
                                        if (FA_TGT) REG_WRM(_t##2, (_v).m[2], (_m).m[2]);    }
#define REG_RD_PMASK(_t, _m)          { REG_RD(_t, &(_m)->m[0]);                             \
                                        if (FA_TGT) REG_RD(_t##1, &(_m)->m[1]);              \
                                        if (FA_TGT) REG_RD(_t##2, &(_m)->m[2]);              }
#define REG_RDX_PMASK(_t, x, _m)      { REG_RD(_t(x), &(_m)->m[0]);                          \
                                        if (FA_TGT) REG_RD(_t##1(x), &(_m)->m[1]);           \
                                        if (FA_TGT) REG_RD(_t##2(x), &(_m)->m[2]);           }
#define REG_WRXM_PMASK(_t, x, _v, _m) { REG_WRM(_t(x), (_v).m[0], (_m).m[0]);                \
                                        if (FA_TGT) REG_WRM(_t##1(x), (_v).m[1], (_m).m[1]); \
                                        if (FA_TGT) REG_WRM(_t##2(x), (_v).m[2], (_m).m[2]); }

static inline u32 fla_get_const(vtss_state_t *vtss_state, u32 constant)
{
    return vtss_state->chip_const[constant];
}

#if VTSS_OPT_DEBUG_PRINT
void vtss_fa_debug_print_port_header(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr, const char *txt);
void vtss_fa_debug_print_pmask(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr, vtss_port_mask_t *pmask);
void vtss_fa_debug_reg_header(const vtss_debug_printf_t pr, const char *name);
void vtss_fa_debug_reg(vtss_state_t *vtss_state,
                       const vtss_debug_printf_t pr, u32 addr, const char *name);
void vtss_fa_debug_reg_inst(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr, u32 addr, u32 i, const char *name);
void vtss_fa_debug_sticky(vtss_state_t *vtss_state,
                          const vtss_debug_printf_t pr, u32 addr, const char *name);
void vtss_fa_debug_cnt(const vtss_debug_printf_t pr, const char *col1, const char *col2,
                       vtss_chip_counter_t *c1, vtss_chip_counter_t *c2);
#endif
#define FA_DEBUG_REG(pr, tgt, addr)                vtss_fa_debug_reg(vtss_state, pr, REG_ADDR(VTSS_##tgt##_##addr), #addr)
#define FA_DEBUG_REG_NAME(pr, tgt, addr, name)     vtss_fa_debug_reg(vtss_state, pr, REG_ADDR(VTSS_##tgt##_##addr), name)
#define FA_DEBUG_REGX_NAME(pr, tgt, addr, x, name) vtss_fa_debug_reg_inst(vtss_state, pr, REG_ADDR(VTSS_##tgt##_##addr(x)), x, name)

/* MC PGIDs */
#define PGID_BASE         RT_CHIP_PORTS
#define PGID_UC_FLOOD     (PGID_BASE + 0)
#define PGID_MC_FLOOD     (PGID_BASE + 1)
#define PGID_IPV4_MC_DATA (PGID_BASE + 2)
#define PGID_IPV4_MC_CTRL (PGID_BASE + 3)
#define PGID_IPV6_MC_DATA (PGID_BASE + 4)
#define PGID_IPV6_MC_CTRL (PGID_BASE + 5)
#define PGID_DROP         (PGID_BASE + 6)
#define PGID_FLOOD        (PGID_BASE + 7)

/* Mirror probe usage */
#define FA_MIRROR_PROBE_RX   0 /* Ingress mirror probe */
#define FA_MIRROR_PROBE_TX   1 /* Egress mirror probe */
#define FA_MIRROR_PROBE_VLAN 2 /* VLAN mirror probe */

#define QFWD_FRAME_COPY_CFG_CPU_QU(qu)              (qu)
#define QFWD_FRAME_COPY_CFG_LRN_ALL                 8
#define QFWD_FRAME_COPY_CFG_MIRROR_PROBE(probe_idx) (probe_idx + 9)

/* sFlow H/W-related min/max */
#define FA_SFLOW_MIN_SAMPLE_RATE       1 /**< Minimum allowable sampling rate for sFlow */
#define FA_SFLOW_MAX_SAMPLE_RATE   32767 /**< Maximum allowable sampling rate for sFlow */

/* Bits used to control IFH.CL_RSLT from CLM/IS2 */
#define FA_IFH_CL_RSLT_ACL_HIT  0x0001 /* ACL hit flag */
#define FA_IFH_CL_RSLT_ACL_FLAG 0x0002 /* ACL discard flag */

/* IS2 key selection starting at index 70 */
#define FA_VCAP_IS2_KEY_SEL_IRLEG 0
#define FA_VCAP_IS2_KEY_SEL_ERLEG 1
#define FA_VCAP_IS2_KEY_SEL_VD0   2

/* Common functions */
vtss_rc vtss_fa_init_groups(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_fa_port2taxi(vtss_state_t *vtss_state,
                          u32 taxi, vtss_port_no_t port_no, u32 *taxi_port);

/* Port functions */
vtss_rc vtss_fa_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_fa_port_debug_print(vtss_state_t *vtss_state,
                                   const vtss_debug_printf_t pr,
                                   const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_port_debug_qres(vtss_state_t *vtss_state, const vtss_debug_printf_t pr, BOOL res_stat_cur);
#endif

/* Port functions for index to address target */
u32 vtss_port_dev_index(vtss_state_t *vtss_state, u32 port);
u32 fla_port_is_2G5(vtss_state_t *vtss_state, u32 p);
u32 fla_port_is_5G(vtss_state_t *vtss_state, u32 p);
u32 fla_port_is_10G(vtss_state_t *vtss_state, u32 p);
u32 fla_port_is_25G(vtss_state_t *vtss_state, u32 p);
u32 vtss_to_dev2g5(vtss_state_t *vtss_state, u32 port);
u32 vtss_to_dev5g(vtss_state_t *vtss_state, u32 port);
u32 vtss_to_dev10g(vtss_state_t *vtss_state, u32 port);
u32 vtss_to_sd10g_lane(vtss_state_t *vtss_state, u32 indx);
u32 vtss_to_sd_cmu(vtss_state_t *vtss_state, u32 indx);
u32 vtss_to_sd_cmu_cfg(vtss_state_t *vtss_state, u32 indx);
u32 vtss_to_sd_lane(vtss_state_t *vtss_state, u32 indx);
u32 vtss_fa_dev_tgt(vtss_state_t *vtss_state, vtss_port_no_t port_no);
u32 vtss_to_sd6g_lane(vtss_state_t *vtss_state, u32 indx);
u32 vtss_to_dev25g(vtss_state_t *vtss_state, u32 port);
u32 vtss_to_sd25g_lane(vtss_state_t *vtss_state, u32 indx);
vtss_rc vtss_fa_sd25g_init(vtss_state_t *vtss_state, u32 sd_id);

/* Serdes functions */
#define FA_SERDES_TYPE_UNKNOWN  0
#define FA_SERDES_CMU 14
#define FA_SERDES_TYPE_6G  6
#define FA_SERDES_TYPE_10G 10
#define FA_SERDES_TYPE_25G 25
#define FA_TGT (vtss_state->chip_design == 1)
#define LA_TGT !FA_TGT
vtss_rc vtss_fa_port2sd(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 *sd_indx, u32 *sd_type);
u32 vtss_fa_sd_lane_indx(vtss_state_t *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_fa_sd_cfg(vtss_state_t *vtss_state, vtss_port_no_t port_no, vtss_serdes_mode_t mode);
vtss_rc vtss_fa_cmu_cfg(vtss_state_t *vtss_state, u32 cmu_id);
u32 vtss_fa_sd10g28_get_cmu (vtss_state_t *vtss_state, vtss_sd10g28_cmu_t cmu_type, vtss_port_no_t port_no);
u32 vtss_fa_port2sd_indx(vtss_state_t *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_fa_serdes_init(vtss_state_t *vtss_state);
vtss_rc vtss_fa_cmu_init(vtss_state_t *vtss_state);
vtss_rc  vtss_ant_sd10g28_cmu_reg_cfg(vtss_state_t *vtss_state, u32 cmu_num);
vtss_rc  vtss_laguna_sd10g28_cmu_reg_cfg(vtss_state_t *vtss_state, u32 cmu_num);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc fa_debug_chip_serdes(vtss_state_t *vtss_state,  const vtss_debug_printf_t pr,
                             const vtss_debug_info_t   *const info, vtss_port_no_t port_no);
#endif
vtss_rc fa_debug_serdes_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                            const vtss_port_serdes_debug_t *const conf);
BOOL fa_is_target(vtss_state_t *vtss_state);
vtss_rc fa_kr_eye_height(vtss_state_t *vtss_state,  vtss_port_no_t port_no, u32 action, u32 *ret_val);
vtss_rc fa_serdes_ctle_adjust(vtss_state_t *vtss_state,
#if VTSS_OPT_DEBUG_PRINT
                              const vtss_debug_printf_t pr,
#endif
                              u32 port_no, BOOL ro, u32 *vga, u32 *eqr, u32 *eqc);
#if defined(VTSS_FEATURE_PORT_KR_IRQ)
vtss_rc fa_kr_coef2status(vtss_state_t *vtss_state,
                          const vtss_port_no_t port_no,
                          const u16 coef_in,
                          vtss_kr_status_results_t *const status_out);
vtss_rc fa_port_kr_tap_get(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                           u16 *tap_dly, u16 *tap_adv, u16 *ampl);
vtss_rc fa_port_kr_tap_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                           u16 tap_dly, u16 tap_adv, u16 ampl);

vtss_rc fa_serdes_40b_mode(vtss_state_t *vtss_state, u32 port_no);

vtss_rc fa_port_kr_tap_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no,
                           u16 tap_dly, u16 tap_adv, u16 ampl);
#endif


/* Miscellaneous functions */
vtss_rc vtss_fa_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_fa_misc_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);
#endif
vtss_rc vtss_fa_chip_id_get(vtss_state_t *vtss_state, vtss_chip_id_t *const chip_id);
vtss_rc vtss_fa_gpio_mode(vtss_state_t *vtss_state,
                          const vtss_chip_no_t   chip_no,
                          const vtss_gpio_no_t   gpio_no,
                          const vtss_gpio_mode_t mode);
u32 vtss_fa_clk_period(vtss_core_clock_freq_t clock);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_fa_dsm_cal_debug(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr);
vtss_rc vtss_fa_cell_cal_debug(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr);
#endif
u32 vtss_get_fifo_size(vtss_state_t *vtss_state, vtss_port_no_t port_no);
vtss_rc fa_dsm_calc_and_apply_calendar(vtss_state_t *vtss_state);
vtss_rc fa_cell_calendar_auto(vtss_state_t *vtss_state);
#if defined(VTSS_SDX_CNT)
vtss_rc vtss_fa_isdx_update(vtss_state_t *vtss_state, vtss_sdx_entry_t *sdx);
#endif
#if defined(VTSS_EVC_STAT_CNT)
vtss_rc vtss_fa_sdx_counters_update(vtss_state_t *vtss_state, vtss_stat_idx_t *stat_idx, vtss_evc_counters_t *const cnt, BOOL clr);
#endif
BOOL vtss_fa_port_is_high_speed(vtss_state_t *vtss_state, u32 port);


/* QoS functions */
#if defined(VTSS_FEATURE_QOS)
vtss_rc vtss_fa_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_fa_port_policer_fc_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no);
#if defined(VTSS_FEATURE_QOS_POLICER_DLB)
vtss_rc vtss_fa_policer_conf_set(vtss_state_t *vtss_state, u32 lb_set_idx, vtss_dlb_policer_conf_t *conf);
#endif
u32 vtss_fa_imap_key2clm(u16 imap_key, BOOL inner_tag);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_fa_qos_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);
#endif
vtss_rc vtss_fa_qos_port_change(vtss_state_t *vtss_state, vtss_port_no_t port_no, BOOL is_reset);
vtss_rc vtss_fa_qos_tas_port_conf_update(struct vtss_state_s   *vtss_state,
                                         const vtss_port_no_t  port_no);
#endif /* VTSS_FEATURE_QOS */

/* L2 functions */
vtss_rc vtss_fa_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
u32 vtss_fa_vtss_pgid(const vtss_state_t *const vtss_state, u32 pgid);
vtss_rc vtss_fa_vlan_update(vtss_state_t *vtss_state, vtss_vid_t vid);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_fa_l2_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);
#endif

/* L3 functions */
vtss_rc vtss_fa_l3_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_fa_l3_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);
#endif
/* Packet functions */
typedef struct {
    vtss_packet_reg_type_t reg;
    vtss_packet_rx_queue_t queue;
    BOOL                   cosid_enable;
    vtss_cosid_t           cosid;
} vtss_fa_l2cp_conf_t;

vtss_rc vtss_fa_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_fa_packet_debug_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info);
#endif
vtss_rc vtss_fa_l2cp_conf_set(vtss_state_t *vtss_state, u32 profile, u32 l2cp, vtss_fa_l2cp_conf_t *conf);

#if defined(VTSS_FEATURE_AFI_SWC)
vtss_rc vtss_fa_afi_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);
#if defined(VTSS_AFI_V2)
vtss_rc vtss_fa_afi_init(vtss_state_t *const vtss_state, const vtss_init_cmd_t cmd);
#endif /* VTSS_AFI_V2 */
#endif /* VTSS_FEATURE_AFI_SWC */

#if defined(VTSS_FEATURE_VOP)
/* OAM functions */
u32 vtss_fa_voi_idx_to_mip_idx(vtss_state_t *vtss_state, vtss_voi_idx_t  voi_idx);
vtss_rc vtss_fa_vop_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_fa_vop_debug_print(vtss_state_t *vtss_state,
                                  const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info);
#endif /* VTSS_FEATURE_VOP */

#if defined(VTSS_FEATURE_MRP)
/* MRP functions */
vtss_rc vtss_lan969x_mrp_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_lan969x_mrp_debug_print(vtss_state_t *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info);
#endif /* VTSS_FEATURE_MRP */

/* VCAP functions */
#if defined(VTSS_FEATURE_VCAP)
vtss_rc vtss_fa_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_fa_vcap_port_key_set(vtss_state_t *vtss_state, vtss_port_no_t port_no,
                                  u32 lookup, vtss_vcap_key_type_t key_type, BOOL dmac_dip);
vtss_rc vtss_fa_vcap_port_update(vtss_state_t *vtss_state,
                                 vtss_port_no_t port_no);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_fa_vcap_debug_print(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_debug_clm_a(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_debug_clm_b(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_debug_clm_c(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr,
                            const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_debug_es0(vtss_state_t *vtss_state,
                          const vtss_debug_printf_t pr,
                          const vtss_debug_info_t   *const info);
vtss_rc vtss_fa_debug_lpm(vtss_state_t *vtss_state,
                          const vtss_debug_printf_t pr,
                          const vtss_debug_info_t   *const info);
#endif
#endif /* VTSS_FEATURE_VCAP */

void fla_init_regs(vtss_state_t *vtss_state, BOOL fa);
void fla_init_const(vtss_state_t *vtss_state, BOOL fa);

#if defined(VTSS_FEATURE_TIMESTAMP)
/* Timestamp functions */
vtss_rc vtss_fa_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
#if VTSS_OPT_DEBUG_PRINT
vtss_rc vtss_fa_ts_debug_print(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info);
#endif
vtss_rc vtss_timestampSub(vtss_timestamp_t *ts, const vtss_timestamp_t *ts_sub);
vtss_rc vtss_timestampAddNano(vtss_timestamp_t *ts, u64 nano);
vtss_rc vtss_timestampSubNano(vtss_timestamp_t *ts, u64 nano);
BOOL vtss_timestampLarger(const vtss_timestamp_t *ts1, const vtss_timestamp_t *ts2);


#endif /* VTSS_FEATURE_TIMESTAMP */

#if defined(VTSS_FEATURE_VOP)
vtss_voe_idx_t vtss_fa_service_voe_alloc(vtss_state_t *vtss_state, vtss_voe_function_t function);
vtss_rc vtss_fa_service_voe_free(vtss_state_t         *vtss_state,
                                 vtss_voe_function_t  function,
                                 vtss_voe_idx_t       voe_idx);
#endif
#endif /* VTSS_FPGA_FA */
#endif /* VTSS_ARCH_FA */
#endif /* _VTSS_FA_CIL_H_ */

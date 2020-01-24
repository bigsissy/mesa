// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_MAS_CIL_H_
#define _VTSS_MAS_CIL_H_

#include "vtss_api.h"

#if defined(VTSS_ARCH_LAN966X)
#define VTSS_TRACE_LAYER VTSS_TRACE_LAYER_CIL
#include "../ail/vtss_state.h"
#include "../ail/vtss_common.h"
#include "../ail/vtss_util.h"
#include "vtss_lan966x.h"
#include "vtss_lan966x_regs.h"

/* ================================================================= *
 *  Register access
 * ================================================================= */
extern vtss_rc (*vtss_lan966x_wr)(vtss_state_t *vtss_state, u32 addr, u32 val);
extern vtss_rc (*vtss_lan966x_rd)(vtss_state_t *vtss_state, u32 addr, u32 *val);
vtss_rc vtss_lan966x_wrm(vtss_state_t *vtss_state, u32 reg, u32 val, u32 mask);
void vtss_lan966x_reg_error(const char *file, int line);

// TODO This should come from the CML file and go into the auto-generated header
#define VTSS_LAN966X_TARGET_MAX 22
inline u32 vtss_lan966x_target_id_to_addr(int target_id)
{
    switch (target_id) {
        case  0: return 0x00300000;
        case  1: return 0x00280000;
        case  2: return 0x00100000;
        case  3: return 0x00110000;
        case  4: return 0x00120000;
        case  5: return 0x00130000;
        case  6: return 0x00140000;
        case  7: return 0x00150000;
        case  8: return 0x00160000;
        case  9: return 0x00170000;
        case 10: return 0x00070000;
        case 11: return 0x00ff0000;
        case 12: return 0x000a0000;
        case 13: return 0x00000000;
        case 14: return 0x00090000;
        case 15: return 0x00080000;
        case 16: return 0x00200000;
        case 17: return 0x00030000;
        case 18: return 0x00380000;
        case 19: return 0x00010000;
        case 20: return 0x00040000;
        case 21: return 0x00050000;
        case 22: return 0x00060000;
        default: return 0xffffffff;
    }
}
// End of hard-coded Adaro constants. //////////////////////////////////////////

inline u32 __ioreg(const char *file, int line, int tbaseid, int tinst, int tcnt,
                   int gbase, int ginst, int gcnt, int gwidth,
                   int raddr, int rinst, int rcnt, int rwidth)
{
    if (tbaseid + tinst > VTSS_LAN966X_TARGET_MAX || tinst >= tcnt ||
        ginst >= gcnt || rinst >= rcnt) {
        vtss_lan966x_reg_error(file, line);
        return 0xffffffff;
    }

    return (vtss_lan966x_target_id_to_addr(tbaseid + tinst) +
            gbase + ((ginst) * gwidth) +
            raddr + ((rinst) * rwidth)) / 4;
}

#define IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,                \
              raddr, rinst, rcnt, rwidth)                                      \
        __ioreg(__FILE__, __LINE__, tbaseid, tinst, tcnt, gbase, ginst, gcnt,  \
                gwidth, raddr, rinst, rcnt, rwidth)

#define REG_ADDR(p) IOREG(p)

#define REG_RD(...) REG_RD_(__VA_ARGS__)
#define REG_RD_(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,              \
               raddr, rinst, rcnt, rwidth, val)                                \
    do {                                                                       \
        u32 o = IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,        \
                      raddr, rinst, rcnt, rwidth);                             \
        vtss_rc __rc = vtss_lan966x_rd(vtss_state, o, val);                    \
        if (__rc != VTSS_RC_OK)                                                \
            return __rc;                                                       \
    } while (0)

#define REG_WR(...) REG_WR_(__VA_ARGS__)
#define REG_WR_(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,              \
               raddr, rinst, rcnt, rwidth, val)                                \
    do {                                                                       \
        u32 o = IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,        \
                      raddr, rinst, rcnt, rwidth);                             \
        vtss_rc __rc = vtss_lan966x_wr(vtss_state, o, val);                    \
        if (__rc != VTSS_RC_OK)                                                \
            return __rc;                                                       \
    } while (0)

#define REG_WRM(...) REG_WRM_(__VA_ARGS__)
#define REG_WRM_(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,             \
                raddr, rinst, rcnt, rwidth, val, msk)                          \
    do {                                                                       \
        u32 o = IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,        \
                      raddr, rinst, rcnt, rwidth);                             \
        vtss_rc __rc = vtss_lan966x_wrm(vtss_state, o, val, msk);              \
        if (__rc != VTSS_RC_OK)                                                \
            return __rc;                                                       \
    } while (0)

#define REG_WRM_SET(...) REG_WRM_SET_(__VA_ARGS__)
#define REG_WRM_SET_(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,         \
                    raddr, rinst, rcnt, rwidth, msk)                           \
    do {                                                                       \
        u32 o = IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,        \
                      raddr, rinst, rcnt, rwidth);                             \
        vtss_rc __rc = vtss_lan966x_wrm(vtss_state, o, msk, msk);              \
        if (__rc != VTSS_RC_OK)                                                \
            return __rc;                                                       \
    } while (0)

#define REG_WRM_CLR(...) REG_WRM_CLR_(__VA_ARGS__)
#define REG_WRM_CLR_(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,         \
                    raddr, rinst, rcnt, rwidth, msk)                           \
    do {                                                                       \
        u32 o = IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,        \
                      raddr, rinst, rcnt, rwidth);                             \
        vtss_rc __rc = vtss_lan966x_wrm(vtss_state, o, 0, msk);                \
        if (__rc != VTSS_RC_OK)                                                \
            return __rc;                                                       \
    } while (0)

#define REG_WRM_CTL(...) REG_WRM_CTL_(__VA_ARGS__)
#define REG_WRM_CTL_(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,         \
                    raddr, rinst, rcnt, rwidth, _cond_, msk)                   \
    do {                                                                       \
        u32 o = IOREG(tbaseid, tinst, tcnt, gbase, ginst, gcnt, gwidth,        \
                      raddr, rinst, rcnt, rwidth);                             \
        vtss_rc __rc = vtss_lan966x_wrm(vtss_state, o,                         \
                                        (_cond_) ? (msk) : 0, msk);            \
        if (__rc != VTSS_RC_OK)                                                \
            return __rc;                                                       \
    } while (0)

/* ================================================================= *
 *  Chip ports
 * ================================================================= */
#define VTSS_CHIP_PORTS      8    /* Port 0-7 */
#define VTSS_CHIP_PORT_CPU   VTSS_CHIP_PORTS /* Next port is CPU port */
#define VTSS_CHIP_PORT_CPU_0 (VTSS_CHIP_PORT_CPU + 0) /* Aka. CPU Port 8 */
#define VTSS_CHIP_PORT_CPU_1 (VTSS_CHIP_PORT_CPU + 1) /* Aka. CPU Port 9 */
#define VTSS_CHIP_PORT_MASK  VTSS_BITMASK(VTSS_CHIP_PORTS) /* Chip port mask */

#define LAN966X_ACS          16  /* Number of aggregation masks */

/* Reserved PGIDs */
#define PGID_UC     (VTSS_PGIDS - 4)
#define PGID_MC     (VTSS_PGIDS - 3)
#define PGID_MCIPV4 (VTSS_PGIDS - 2)
#define PGID_MCIPV6 (VTSS_PGIDS - 1)
#define PGID_AGGR   (VTSS_PGIDS)
#define PGID_SRC    (PGID_AGGR + LAN966X_ACS)

/* ================================================================= *
 *  Common functions
 * ================================================================= */
vtss_rc vtss_lan966x_init_groups(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
u32 vtss_lan966x_port_mask(vtss_state_t *vtss_state, const BOOL member[]);
void vtss_lan966x_debug_print_port_header(vtss_state_t *vtss_state,
                                          const vtss_debug_printf_t pr, const char *txt);
void vtss_lan966x_debug_print_mask(const vtss_debug_printf_t pr, u32 mask);
void vtss_lan966x_debug_reg_header(const vtss_debug_printf_t pr, const char *name) ;
void vtss_lan966x_debug_reg(vtss_state_t *vtss_state,
                            const vtss_debug_printf_t pr, u32 addr, const char *name);
void vtss_lan966x_debug_reg_inst(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr, u32 addr, u32 i, const char *name);

vtss_rc vtss_lan966x_port_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);
vtss_rc vtss_lan966x_port_max_tags_set(vtss_state_t *vtss_state, vtss_port_no_t port_no);

vtss_rc vtss_lan966x_packet_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_afi_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_misc_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_l2_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_qos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_ts_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_vcap_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

vtss_rc vtss_lan966x_oam_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd);

#endif /* VTSS_ARCH_LAN966X */
#endif /* _VTSS_MAS_CIL_H_ */

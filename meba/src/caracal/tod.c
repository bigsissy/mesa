// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "microchip/ethernet/board/api.h"

#include "meba_aux.h"

mesa_rc meba_tod_phy_ts_clk_info_1g(meba_inst_t inst,
                                    mesa_phy_ts_clockfreq_t *freq,
                                    mesa_phy_ts_clock_src_t *src,
                                    mesa_timeinterval_t *pps_load_delay,
                                    mesa_timeinterval_t *pps_save_delay)
{
#if defined(VTSS_PHY_TS_SILABS_CLK_DLL)
    *freq = MESA_PHY_TS_CLOCK_FREQ_250M;
    *src = MESA_PHY_TS_CLOCK_SRC_INTERNAL;
    /* default 1pps latency for the phy is 3 clock cycles */
    *pps_load_delay = (((mesa_timeinterval_t)MESA_ONE_MIA << 16) * 4LL) / clk_mhz[*freq];
    *pps_save_delay = (((mesa_timeinterval_t)MESA_ONE_MIA << 16) * 3LL) / clk_mhz[*freq];
#else
    *freq = MESA_PHY_TS_CLOCK_FREQ_125M;
    *src = MESA_PHY_TS_CLOCK_SRC_CLIENT_TX;
    /* default 1pps latency for the phy is 3 clock cycles */
    *pps_load_delay = (((mesa_timeinterval_t)MESA_ONE_MIA << 16) * 4LL) / clk_mhz[*freq];
    *pps_save_delay = (((mesa_timeinterval_t)MESA_ONE_MIA << 16) * 3LL) / clk_mhz[*freq];
#endif /* defined(VTSS_PHY_TS_SILABS_CLK_DLL) */

    return MESA_RC_OK;
}

static meba_api_tod_t public_functions = {
#define X(name) . name = name,
    MEBA_LIST_OF_API_TOD_CALLS
#undef X
};

meba_api_tod_t *meba_tod_get()
{
    return &public_functions;
}

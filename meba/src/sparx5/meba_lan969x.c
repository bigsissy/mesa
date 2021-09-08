// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <microchip/ethernet/board/api.h>

#include "meba_aux.h"
#include "meba_generic.h"
#include "meba_common.h"

static void lan969x_init_port(meba_inst_t inst, mesa_port_no_t port_no, meba_port_entry_t *entry)
{
    if (port_no == 0)
        entry->map.chip_port = 8;
    else if (port_no == 1)
        entry->map.chip_port = 24;

    entry->map.miim_controller = MESA_MIIM_CONTROLLER_NONE;
    entry->map.max_bw          = MESA_BW_10G;
    entry->mac_if              = MESA_PORT_INTERFACE_SFI;
    entry->cap                 = MEBA_PORT_CAP_10G_FDX;
}

static mesa_rc lan969x_board_init(meba_inst_t inst)
{
    meba_board_state_t     *board = INST2BOARD(inst);

    switch (board->type) {
    case BOARD_TYPE_SUNRISE:
        break;
    default:
        break;
    }
    return MESA_RC_OK;
}


/* typedef struct meba_board_state { */
/*     board_type_t          type; */
/*     board_port_cfg_t      port_cfg; */
/*     const mesa_fan_conf_t *fan_spec; */
/*     mesa_bool_t           beaglebone; */
/*     mesa_bool_t           ls1046; */
/*     uint32_t              port_cnt; */
/*     int                   cpu_port_cnt; */
/*     fa_port_info_t       *port; */
/*     const board_func_t    *func; */
/*      mepa_device_t        *phy_devices[MAX_PORTS]; */
/* } meba_board_state_t; */


/** \brief Board instance struct */
/* struct meba_inst { */
/*     int                      api_version;            /\**< The MEBA version of the board implementation *\/ */
/*     size_t                   instance_size;          /\**< The size of this structure (for compatibility checking) *\/ */
/*     void                     *private_data;          /\**< Private (implementation) state data; *\/ */
/*     meba_board_interface_t   iface;                  /\**< Board interface functions *\/ */
/*     meba_board_props_t       props;                  /\**< Public board properties *\/ */
/*     meba_api_t               api;                    /\**< Board API entrypoints *\/ */
/*     meba_api_synce_t         *api_synce;             /\**< SyncE board API entrypoints *\/ */
/*     meba_api_tod_t           *api_tod;               /\**< TOD board API entrypoints *\/ */
/*     meba_api_poe_t           *api_poe;               /\**< PoE board API entrypoints *\/ */
/*     int                      synce_spi_if_fd;        /\**< File descriptor of SyncE SPI interface.  *\/ */
/*     meba_api_cpu_port_t      *api_cpu_port;          /\**< CPU Port API entrypoints *\/ */
/*     int                      phy_device_cnt;         /\**< Total number of phy devices/ports available in board (needed for phy API) *\/ */
/*     mepa_device_t            **phy_devices;          /\**< Entry point to phy driver devices. *\/ */
/* }; */


static uint32_t lan969x_capability(meba_inst_t inst, int cap)
{
    meba_board_state_t *board = INST2BOARD(inst);
    T_N(inst, "Called - %d", cap);
    switch (cap) {
        case MEBA_CAP_POE:
            return 0;
        case MEBA_CAP_1588_CLK_ADJ_DAC:
            return 0;
        case MEBA_CAP_1588_REF_CLK_SEL:
            return 0;
        case MEBA_CAP_TEMP_SENSORS:
            return 0;
        case MEBA_CAP_BOARD_PORT_COUNT:
        case MEBA_CAP_BOARD_PORT_MAP_COUNT:
            return board->port_cnt;
        case MEBA_CAP_LED_MODES:
            return 0;
        case MEBA_CAP_DYING_GASP:
            return 0;
        case MEBA_CAP_FAN_SUPPORT:
            return 0;
        default:
            T_E(inst, "Unknown capability %d", cap);
            MEBA_ASSERT(0);
    }
    return 0;
}

static mesa_rc lan969x_port_entry_get(meba_inst_t inst,
                                      mesa_port_no_t port_no,
                                      meba_port_entry_t *entry)
{
    mesa_rc rc;
    meba_board_state_t *board = INST2BOARD(inst);

    T_N(inst, "Called");
    if (port_no < board->port_cnt) {

        *entry = board->port[port_no].map;
        rc = MESA_RC_OK;
    } else {
        rc = MESA_RC_ERROR;
    }
    T_N(inst, "Called(%d): rc %d - chip %d, miim bus %d, addr: %d", port_no, rc,
        entry->map.chip_port, entry->map.miim_controller, entry->map.miim_addr);
    return rc;
}


static mesa_rc lan969x_sfp_i2c_xfer(meba_inst_t inst,
                                    mesa_port_no_t port_no,
                                    mesa_bool_t write,
                                    uint8_t i2c_addr,
                                    uint8_t addr,
                                    uint8_t *data,
                                    uint8_t cnt,
                                    mesa_bool_t word_access)
{
    mesa_rc            rc = MESA_RC_ERROR;
    meba_board_state_t *board = INST2BOARD(inst);
    uint32_t           board_port = PORT_2_BOARD_PORT(board, port_no);

    T_N(inst, "Called");

    if (write) {    // cnt ignored
        uint8_t i2c_data[3];
        i2c_data[0] = addr;
        memcpy(&i2c_data[1], data, 2);
        rc = inst->iface.i2c_write(board_port, i2c_addr, i2c_data, 3);
    } else {
        rc = inst->iface.i2c_read(board_port, i2c_addr, addr, data, cnt);
    }

    T_D(inst, "i2c %s port %d - address 0x%02x:0x%02x, %d bytes return %d", write ? "write" : "read", board_port, i2c_addr, addr, cnt, rc);
    return rc;
}

static mesa_rc lan969x_sfp_insertion_status_get(meba_inst_t inst, mesa_port_list_t *present)
{
    mesa_rc                rc = MESA_RC_OK;
//    meba_board_state_t *board = INST2BOARD(inst);

    T_N(inst, "Called");
    mesa_port_list_clear(present);

    return rc;
}

static mesa_rc lan969x_sfp_status_get(meba_inst_t inst,
                                      mesa_port_no_t port_no,
                                      meba_sfp_status_t *status)
{
    mesa_rc rc = MESA_RC_OK;
//    meba_board_state_t *board = INST2BOARD(inst);

    return rc;
}

// Applies only to SFPs where TxDisable is enabled/disabled
static mesa_rc lan969x_port_admin_state_set(meba_inst_t inst,
                                            mesa_port_no_t port_no,
                                            const meba_port_admin_state_t *state)
{
    mesa_rc            rc = MESA_RC_OK;
    meba_board_state_t *board = INST2BOARD(inst);

    if (board->port[port_no].map.map.miim_controller == MESA_MIIM_CONTROLLER_NONE) {

    }

    return rc;
}

static mesa_rc lan969x_status_led_set(meba_inst_t inst,
                                      meba_led_type_t type,
                                      meba_led_color_t color)
{
    mesa_rc rc = MESA_RC_ERROR;
    if (type == MEBA_LED_TYPE_FRONT && color < MEBA_LED_COLOR_COUNT) {
        T_I(inst, "LED:%d, color=%d", type, color);
        switch (color) {
            case MEBA_LED_COLOR_OFF:
                (void) mesa_gpio_write(NULL, 0, STATUSLED_R_GPIO, false);
                rc = mesa_gpio_write(NULL, 0, STATUSLED_G_GPIO, false);
                break;
            case MEBA_LED_COLOR_GREEN:
                (void) mesa_gpio_write(NULL, 0, STATUSLED_R_GPIO, false);
                rc = mesa_gpio_write(NULL, 0, STATUSLED_G_GPIO, true);
                break;
            case MEBA_LED_COLOR_RED:
                (void) mesa_gpio_write(NULL, 0, STATUSLED_R_GPIO, true);
                rc = mesa_gpio_write(NULL, 0, STATUSLED_G_GPIO, false);
                break;
            case MEBA_LED_COLOR_YELLOW:
                (void) mesa_gpio_write(NULL, 0, STATUSLED_R_GPIO, true);
                rc = mesa_gpio_write(NULL, 0, STATUSLED_G_GPIO, true);
                break;
            default:
                rc = MESA_RC_ERROR;
        }
    }
    return rc;
}

static mesa_rc lan969x_reset(meba_inst_t inst, meba_reset_point_t reset)
{
//    meba_board_state_t *board = INST2BOARD(inst);
    mesa_rc rc = MESA_RC_OK;

    T_D(inst, "Called - %d", reset);
    switch (reset) {
        case MEBA_BOARD_INITIALIZE:
            lan969x_board_init(inst);
            break;
        case MEBA_PORT_RESET:
            break;
        case MEBA_PORT_RESET_POST:
            break;
        case MEBA_STATUS_LED_INITIALIZE:
            break;
        case MEBA_PORT_LED_INITIALIZE:
            break;
        case MEBA_FAN_INITIALIZE:
            break;
        case MEBA_SENSOR_INITIALIZE:
            break;
        case MEBA_INTERRUPT_INITIALIZE:
            break;
        case MEBA_PHY_INITIALIZE:
            break;
        default:
            rc = MESA_RC_ERROR;
    }
    T_D(inst, "Called - %d - Done", reset);
    return rc;
}

// IRQ Support
static mesa_rc lan969x_event_enable(meba_inst_t inst,
                                    meba_event_t event_id,
                                    mesa_bool_t enable)
{
    mesa_rc               rc = MESA_RC_OK;
//    meba_board_state_t    *board = INST2BOARD(inst);

    T_I(inst, "%sable event %d", enable ? "en" : "dis", event_id);
    return rc;
}


static mesa_rc lan969x_irq_handler(meba_inst_t inst,
                                   mesa_irq_t chip_irq,
                                   meba_event_signal_t signal_notifier)
{
//    meba_board_state_t *board = INST2BOARD(inst);
    T_I(inst, "Called - irq %d", chip_irq);
    return MESA_RC_NOT_IMPLEMENTED;
}

static mesa_rc lan969x_irq_requested(meba_inst_t inst, mesa_irq_t chip_irq)
{
    mesa_rc rc = MESA_RC_NOT_IMPLEMENTED;
    return rc;
}


// lan969x Initialize
meba_inst_t lan969x_initialize(meba_inst_t inst, const meba_board_interface_t *callouts)
{
    meba_board_state_t *board;
    mesa_port_no_t     port_no;
    int                pcb, target;

    board = INST2BOARD(inst);

    // Get board type
    if (meba_conf_get_hex(inst, "pcb", &pcb) != MESA_RC_OK) {
        fprintf(stderr, "Could not read pcb id\n");
        goto error_out;
    }
    if (meba_conf_get_hex(inst, "target", &target) != MESA_RC_OK) {
        fprintf(stderr, "Could not read target\n");
        goto error_out;
    }

    board->type = (board_type_t)pcb;
    inst->props.board_type = board->type;
    inst->props.target = target;
    board->port = (fa_port_info_t*) calloc(30, sizeof(fa_port_info_t));
    if (board->port == NULL) {
        fprintf(stderr, "1Port table malloc failure\n");
        goto error_out;
    }

    switch (board->type) {
    case BOARD_TYPE_SUNRISE:
        board->port_cnt = 2;
        for (port_no = 0; port_no < board->port_cnt; port_no++) {
            lan969x_init_port(inst, port_no,  &board->port[port_no].map);
        }
        break;
    default:
        break;
    }

    T_I(inst, "Board: %s, type %d, target %4x, mux %d, %d ports", inst->props.name, board->type, inst->props.target,
        inst->props.mux_mode, board->port_cnt);

    // Hook up board API functions
    T_D(inst, "Hooking up board API");
    inst->api.meba_capability                 = lan969x_capability;
    inst->api.meba_port_entry_get             = lan969x_port_entry_get;
    inst->api.meba_reset                      = lan969x_reset;
    inst->api.meba_sfp_i2c_xfer               = lan969x_sfp_i2c_xfer;
    inst->api.meba_sfp_insertion_status_get   = lan969x_sfp_insertion_status_get;
    inst->api.meba_sfp_status_get             = lan969x_sfp_status_get;
    inst->api.meba_port_admin_state_set       = lan969x_port_admin_state_set;
    inst->api.meba_status_led_set             = lan969x_status_led_set;
    inst->api.meba_irq_handler                = lan969x_irq_handler;
    inst->api.meba_irq_requested              = lan969x_irq_requested;
    inst->api.meba_event_enable               = lan969x_event_enable;
    return inst;

error_out:
    free(inst);
    return NULL;
}

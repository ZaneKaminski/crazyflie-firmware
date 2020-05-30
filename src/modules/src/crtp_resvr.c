/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie Firmware
 *
 * Copyright (C) 2011-2017 Zane Kaminski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */
#include "crtp_resvr.h"

#include "crtp.h"

#include <stdbool.h>
#include <stdint.h>

#include "log.h"
#include "resvr.h"
#include "kalman_core.h"

static bool isInit;

resvr_t reservoirs[CRTP_RSVR_MAX_RESVRS];
char reservoir_isactive[CRTP_RSVR_MAX_RESVRS];
float reservoir_scale[CRTP_RSVR_MAX_RESVRS];
int reservoir_paramids[CRTP_RSVR_MAX_RESVRS][RESVR_NUM_INPUTS];

static void processResvrPacket(CRTPPacket* pk)
{
  if(pk->port == CRTP_PORT_RESVR && pk->channel == 0) {
    switch ((crtp_resvr_msg_type_t)pk->data[0]) {
      case CRTP_RESVR_MSG_SETSIZE: {
        crtp_resvr_msg_setsize_t *m = (crtp_resvr_msg_setsize_t*)pk->data;
        if (m->id < CRTP_RSVR_MAX_RESVRS && !reservoir_isactive[m->id]) { // Bounds check & disabled check
          // Set reservoir size
          reservoirs[m->id].size = m->size;
        }
      } case CRTP_RESVR_MSG_SETINPUTLAYER: {
        crtp_resvr_msg_setinputlayer_t *m = (crtp_resvr_msg_setinputlayer_t*)pk->data;
        if (m->id < CRTP_RSVR_MAX_RESVRS && !reservoir_isactive[m->id]) { // Bounds check & disabled check
          // Set reservoir input layer struct pointer
          reservoirs[m->id].input = blob_getptr(m->input);
        }
      } case CRTP_RESVR_MSG_SETOUTPUTLAYER: {
        crtp_resvr_msg_setoutputlayer_t *m =(crtp_resvr_msg_setoutputlayer_t*)pk->data;
        if (m->id < CRTP_RSVR_MAX_RESVRS && !reservoir_isactive[m->id]) { // Bounds check & disabled check
          // Set reservoir output layer struct pointer
          reservoirs[m->id].output = blob_getptr(m->output);
        }
      } case CRTP_RESVR_MSG_SETINPUTPARAM: {
        crtp_resvr_msg_setinputparam_t *m =(crtp_resvr_msg_setinputparam_t*)pk->data;
        if (m->id < CRTP_RSVR_MAX_RESVRS && !reservoir_isactive[m->id]) { // Bounds check & disabled check
          reservoir_paramids[m->id][m->index] = m->logid;
        }
      } case CRTP_RESVR_MSG_SETSCALE: {
        crtp_resvr_msg_setscale_t *m = (crtp_resvr_msg_setscale_t*)pk->data;
        if (m->id < CRTP_RSVR_MAX_RESVRS) { // Bounds check
          // Set scale
          reservoir_scale[m->id] = m->scale;
        }
      } case CRTP_RESVR_MSG_START: {
        crtp_resvr_msg_start_t *m = (crtp_resvr_msg_start_t*)pk->data;
        if (m->id < CRTP_RSVR_MAX_RESVRS) { // Bounds check
          // Enable reservoir propagation
          reservoir_isactive[m->id] = 1;
        }
      } case CRTP_RESVR_MSG_STOP: {
        crtp_resvr_msg_stop_t *m = (crtp_resvr_msg_stop_t*)pk->data;
        if (m->id < CRTP_RSVR_MAX_RESVRS) { // Bounds check
          // Disable reservoir propagation
          reservoir_isactive[m->id] = 0;
        }
      }
    }
  }
}

void crtpResvrInit(void)
{
  if(isInit) { return; }

  // Clear reservoir data
  memset(reservoirs, 0, sizeof(reservoirs));
  memset(reservoir_isactive, 0, sizeof(reservoir_isactive));
  memset(reservoirs, 0, sizeof(reservoir_scale));
  
  crtpInit();
  crtpRegisterPortCB(CRTP_PORT_RESVR, processResvrPacket);

  isInit = true;
}

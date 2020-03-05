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
#include "crtp_reservoir.h"

#include "crtp.h"

#include <stdbool.h>
#include <stdint.h>

#include "log.h"
#include "reservoir.h"
#include "kalman_core.h"

uint8_t res_checksum;
static bool isInit;

static void processReservoirPacket(CRTPPacket* pk)
{
  if(pk->port == CRTP_PORT_RESERVOIR && pk->channel == 0) {
    switch ((crtp_reservoir_message_type_t)pk->data[0]) {
      case CRTP_RESERVOIR_MESSAGE_ALLOC_RESERVOIR: {
        crtp_reservoir_message_alloc_reservoir_t *m = 
          (crtp_reservoir_message_alloc_reservoir_t*)pk->data;
        res_alloc_reservoir(m->res, m->size, m->connectivity);
        break; 
      } case CRTP_RESERVOIR_MESSAGE_SET_INPUT: {
        crtp_reservoir_message_set_input_t *m = 
          (crtp_reservoir_message_set_input_t*)pk->data;
        res_set_input_weight(m->res, m->input, m->neuron, m->weight);
        break;
      } case CRTP_RESERVOIR_MESSAGE_APPEND_INTENRAL: {
        crtp_reservoir_message_append_internal_t *m = 
          (crtp_reservoir_message_append_internal_t*)pk->data;
        res_append_internal_weight(m->res, m->index, m->output, m->input, m->weight);
        break;
      } case CRTP_RESERVOIR_MESSAGE_SET_OUTPUT: {
        crtp_reservoir_message_set_output_t *m = 
          (crtp_reservoir_message_set_output_t*)pk->data;
        res_set_output_weight(m->res, m->output, m->neuron, m->weight);
        break;
      } case CRTP_RESERVOIR_MESSAGE_COMPUTE_CHECKSUM: {
        res_checksum = res_compute_checksum();
        break;
      }
    }
  }
}

void crtpReservoirInit(void)
{
  if(isInit) { return; }
  
  crtpInit();

  crtpRegisterPortCB(CRTP_PORT_RESERVOIR, processReservoirPacket);

  isInit = true;
}

LOG_GROUP_START(res)
LOG_ADD(LOG_UINT8, checksum, &res_checksum)
LOG_GROUP_STOP(res)

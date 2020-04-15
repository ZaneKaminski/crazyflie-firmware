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
#include "crtp_blob.h"

#include "crtp.h"

#include <stdbool.h>
#include <stdint.h>

#include "log.h"

static bool isInit;

static void processBlobPacket(CRTPPacket* pk)
{
  if(pk->port == CRTP_PORT_BLOB && pk->channel == 0) {
    switch ((crtp_blob_message_type_t)pk->data[0]) {
      case CRTP_BLOB_MESSAGE_CLEAR: {
        blob_clear();
        break;
      } case CRTP_BLOB_MESSAGE_SET8: {
        crtp_blob_message_set8_t *m = 
          (crtp_blob_message_set8_t*)pk->data;
        blob_set32(m->addr, m->data);
        break; 
      } case CRTP_BLOB_MESSAGE_SET32: {
        crtp_blob_message_set32_t *m = 
          (crtp_blob_message_set32_t*)pk->data;
        blob_set32(m->addr, m->data);
        break;
      } case CRTP_BLOB_MESSAGE_SET_READBACK_ADDR: {
        crtp_blob_message_set_readback_addr_t *m = 
          (crtp_blob_message_set_readback_addr_t*)pk->data;
        blob_set_readback_addr(m->addr);
        break;
      }
    }
  }
}

void crtpBlobInit(void)
{
  if(isInit) { return; }
  
  crtpInit();

  crtpRegisterPortCB(CRTP_PORT_BLOB, processBlobPacket);

  isInit = true;
}

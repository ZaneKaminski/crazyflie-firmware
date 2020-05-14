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

static bool isInit;

static void processReservoirPacket(CRTPPacket* pk)
{
  if(pk->port == CRTP_PORT_RESERVOIR && pk->channel == 0) {
    switch ((crtp_reservoir_message_type_t)pk->data[0]) {
      
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

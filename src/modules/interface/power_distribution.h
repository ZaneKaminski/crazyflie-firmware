/**
 *    ||          ____  _ __
 * +------+      / __ )(_) /_______________ _____  ___
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2011-2016 Bitcraze AB
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
 * power_distribution.h - Interface to stabilizer power distribution
 */
#ifndef __POWER_DISTRIBUTION_H__
#define __POWER_DISTRIBUTION_H__

#include "stabilizer_types.h"

typedef struct motors_s {
  uint32_t m1;
  uint32_t m2;
  uint32_t m3;
  uint32_t m4;
} motors_t;

typedef struct motors_adj_s {
  int32_t m1;
  int32_t m2;
  int32_t m3;
  int32_t m4;
} motors_adj_t;

void powerDistributionInit(void);
bool powerDistributionTest(void);
void powerDistribution(const control_t *control);
void powerDistributionWithAdjust(const control_t *control, motors_adj_t adj);
void powerStop();


#endif //__POWER_DISTRIBUTION_H__

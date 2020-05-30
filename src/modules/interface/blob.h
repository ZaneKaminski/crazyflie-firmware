/*
 *    ||          ____  _ __                           
 * +------+      / __ )(_) /_______________ _____  ___ 
 * | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2020 Zane Kaminski
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
 * blob.h - Binary large object storage
 */

#include <stdint.h>

#ifndef __BLOB_H__
#define __BLOB_H__

typedef uint16_t blob_addr_t;

void blob_init(void);
void blob_clear(void);

uint8_t blob_get8(blob_addr_t addr);
uint32_t blob_get32(blob_addr_t addr);

void blob_set8(blob_addr_t addr, uint8_t data);
void blob_set32(blob_addr_t addr, uint32_t data);

void *blob_getptr(blob_addr_t addr);

uint8_t blob_readback(blob_addr_t addr);

#endif //__BLOB_H__

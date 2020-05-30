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
 * blob.c - Binary large object storage
 */
#include "blob.h"

#include <stdint.h>
#include <string.h>

#include "log.h"
#include "crtp_blob.h"

#define BLOB_DATA_SIZE 65536

static bool blob_isInit;
static void* const blob_data = (void*)0x10000000;
static uint8_t blob_readback_data;

void blob_init(void) {
	if(blob_isInit) { return; }

	blob_clear();

	crtpBlobInit();

	blob_isInit = true;
}

void blob_clear(void) {
	// Zero readback data
	blob_readback_data = 0;

	// Zero blob data
	memset(blob_data, 0, BLOB_DATA_SIZE);
}

uint8_t blob_get8(blob_addr_t addr) {
	// Bounds checking
	if (addr < BLOB_DATA_SIZE) { return *(uint8_t*)(blob_data + addr); }
	else { return 0; }
}

uint32_t blob_get32(blob_addr_t addr) {
	// Bounds checking
	if (addr < BLOB_DATA_SIZE) { return *(uint32_t*)(blob_data + addr); }
	else { return 0; }
}

void blob_set8(blob_addr_t addr, uint8_t data) {
	// Only set if in bounds
	if (addr < BLOB_DATA_SIZE) { *(uint8_t*)(blob_data + addr) = data; }
}

void blob_set32(blob_addr_t addr, uint32_t data) {
	// Only set if in bounds
	if (addr < BLOB_DATA_SIZE) { *(uint32_t*)(blob_data + addr) = data; }
}

void *blob_getptr(blob_addr_t addr) { return blob_data + addr; }

uint8_t blob_readback(blob_addr_t addr) {
	return blob_readback_data = blob_get8(addr);
}

LOG_GROUP_START(blob)
LOG_ADD(LOG_UINT8, readback_rd_data, &blob_readback_data)
LOG_GROUP_STOP(blob)

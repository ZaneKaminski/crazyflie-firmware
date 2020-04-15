/**
 *    ||          ____  _ __  ______
 * +------+      / __ )(_) /_/ ____/_________ _____  ___
 * | 0xBC |     / __  / / __/ /    / ___/ __ `/_  / / _	\
 * +------+    / /_/ / / /_/ /___ / /  / /_/ / / /_/  __/
 *  ||  ||    /_____/_/\__/\____//_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) Zane Kaminski
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
 */

#include <stdbool.h>
#include <stdint.h>

#include "blob.h"

#ifndef CRTP_BLOB_H_
#define CRTP_BLOB_H_

#define CRTP_BLOB_MESSAGE_CLEAR 0
#define CRTP_BLOB_MESSAGE_SET8 1
#define CRTP_BLOB_MESSAGE_SET32 2
#define CRTP_BLOB_MESSAGE_SET_READBACK_ADDR 3

typedef uint8_t crtp_blob_message_type_t;

typedef struct crtp_blob_message_alloc_set8_s {
	crtp_blob_message_type_t type;
	blob_addr_t addr;
	uint8_t data;
} __attribute__((packed)) crtp_blob_message_set8_t;

typedef struct crtp_blob_message_set32_s {
	crtp_blob_message_type_t type;
	blob_addr_t addr;
	uint32_t data;
} __attribute__((packed)) crtp_blob_message_set32_t;

typedef struct crtp_blob_message_set_readback_addr_s {
	crtp_blob_message_type_t type;
	blob_addr_t addr;
} __attribute__((packed)) crtp_blob_message_set_readback_addr_t;

void crtpBlobInit(void);

#endif /* CRTP_RESERVOIR_H_ */

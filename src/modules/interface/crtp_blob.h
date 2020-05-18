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

#define CRTP_BLOB_MSG_CLEAR 0
#define CRTP_BLOB_MSG_SET8 1
#define CRTP_BLOB_MSG_SET32 2
#define CRTP_BLOB_MSG_READBACK 3

typedef uint8_t crtp_blob_msg_type_t;

typedef struct crtp_blob_msg_set8_s {
	crtp_blob_msg_type_t type;
	blob_addr_t addr;
	uint8_t data;
} __attribute__((packed)) crtp_blob_msg_set8_t;

typedef struct crtp_blob_msg_set32_s {
	crtp_blob_msg_type_t type;
	blob_addr_t addr;
	uint32_t data;
} __attribute__((packed)) crtp_blob_msg_set32_t;

typedef struct crtp_blob_msg_readback_s {
	crtp_blob_msg_type_t type;
	blob_addr_t addr;
} __attribute__((packed)) crtp_blob_msg_readback_t;

void crtpBlobInit(void);

#endif /* CRTP_RESVR_H_ */

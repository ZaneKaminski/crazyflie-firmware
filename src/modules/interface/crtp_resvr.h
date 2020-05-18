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

#include "resvr.h"
#include "blob.h"

#ifndef CRTP_RESVR_H_
#define CRTP_RESVR_H_

typedef uint8_t crtp_resvr_msg_type_t;

#define CRTP_RESVR_MSG_START 0
#define CRTP_RESVR_MSG_SETSCALE 1
#define CRTP_RESVR_MSG_STOP 2

#define CRTP_RSVR_MAX_RESVRS 4
typedef uint8_t resvr_id_t;

typedef struct crtp_resvr_msg_start_s {
	crtp_resvr_msg_type_t type;
	resvr_id_t id;
	resvr_neuron_count_t size;
	blob_addr_t in;
	blob_addr_t out;
} crtp_resvr_msg_start_t;

typedef struct crtp_resvr_msg_setscale_s {
	crtp_resvr_msg_type_t type;
	resvr_id_t id;
	float scale;
} crtp_resvr_msg_setscale_t;

typedef struct crtp_resvr_msg_stop_s {
	crtp_resvr_msg_type_t type;
	resvr_id_t id;
} crtp_resvr_msg_stop_t;

void crtpResvrInit(void);

#endif /* CRTP_RESVR_H_ */

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

#include "reservoir.h"

#ifndef CRTP_RESERVOIR_H_
#define CRTP_RESERVOIR_H_

#define CRTP_RESERVOIR_MESSAGE_ALLOC_RESERVOIR 0
#define CRTP_RESERVOIR_MESSAGE_SET_INPUT 1
#define CRTP_RESERVOIR_MESSAGE_APPEND_INTENRAL 2
#define CRTP_RESERVOIR_MESSAGE_SET_OUTPUT 3
#define CRTP_RESERVOIR_MESSAGE_COMPUTE_CHECKSUM 4

typedef uint8_t crtp_reservoir_message_type_t;

typedef struct crtp_reservoir_message_alloc_reservoir_s {
	crtp_reservoir_message_type_t type;
	res_index_t res;
	res_neuron_count_t size;
	res_connectivity_t connectivity;
} crtp_reservoir_message_alloc_reservoir_t;

typedef struct crtp_reservoir_message_set_input_s {
	crtp_reservoir_message_type_t type;
	res_index_t res;
	res_input_index_t input;
	res_neuron_index_t neuron;
	res_weight_t weight;
} crtp_reservoir_message_set_input_t;

typedef struct crtp_reservoir_message_append_internal_s {
	crtp_reservoir_message_type_t type;
	res_index_t res;
	res_connection_index_t index;
	res_neuron_index_t output;
	res_neuron_index_t input;
	res_weight_t weight;
} crtp_reservoir_message_append_internal_t;

typedef struct crtp_reservoir_message_set_output_s {
	crtp_reservoir_message_type_t type;
	res_index_t res;
	res_output_index_t output;
	res_neuron_index_t neuron;
	res_weight_t weight;
} crtp_reservoir_message_set_output_t;

typedef struct crtp_reservoir_message_compute_checksum_s {
	crtp_reservoir_message_type_t type;
} crtp_reservoir_message_compute_checksum_t;

void crtpReservoirInit(void);

#endif /* CRTP_RESERVOIR_H_ */

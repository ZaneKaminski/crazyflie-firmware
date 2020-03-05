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
 * reservoir.h - Reservoir type definitions
 */

#include "stdint.h"

#ifndef __RESERVOIR_H__
#define __RESERVOIR_H__

#define RES_NUM_INPUTS	3
#define RES_NUM_OUTPUTS	4

typedef uint8_t res_index_t;
typedef uint8_t res_neuron_count_t;
typedef uint16_t res_connectivity_t;

typedef uint8_t res_input_index_t;
typedef uint8_t res_neuron_index_t;
typedef uint8_t res_output_index_t;
typedef uint16_t res_connection_index_t;

typedef float res_weight_t;

typedef struct res_input_connection_s {
	res_weight_t weights[RES_NUM_INPUTS]; 
} res_input_connection_t;

typedef struct res_internal_connection_s {
	res_neuron_index_t input;
	res_neuron_index_t output;
	res_weight_t weight;
} res_internal_connection_t;

typedef struct res_output_connection_s {
	res_weight_t weights[RES_NUM_OUTPUTS]; 
} res_output_connection_t;

typedef struct reservoir_s {
	res_neuron_count_t size;
	res_connectivity_t connectivity;
	res_neuron_index_t current_output;
	res_input_connection_t *inputs;
	res_internal_connection_t *internal;
	res_output_connection_t *outputs;
} reservoir_t;

void res_init();

void res_alloc_reservoir(res_index_t res, res_neuron_count_t size, res_connectivity_t connectivity);

void res_set_input_weight(res_index_t res, res_input_index_t input, res_neuron_index_t neuron, res_weight_t weight);

void res_append_neuron_weight(res_index_t res, res_connection_index_t index,
	res_neuron_index_t output, res_neuron_index_t input, res_weight_t weight);

void res_set_output_weight(res_index_t res, res_output_index_t output, res_neuron_index_t neuron, res_weight_t weight);

uint8_t res_get_checksum(res_index_t res);

#endif //__RESERVOIR_H__

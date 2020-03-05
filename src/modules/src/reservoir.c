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
 * reservoir.h - 
 */
#include "reservoir.h"

#define RES_DATA_SIZE 65536

static reservoir_t res_table[16];

static char res_data[RES_DATA_SIZE];
static void *res_index;

void res_init() {
	res_index = res_data;
	for (int i = 0; i < 16; i++) {
		res_table[i] = (reservoir_t){0};
	}
}

void res_alloc_reservoir(res_index_t res, res_neuron_count_t size, res_connectivity_t connectivity) {
	res_table[res].size = size;
	res_table[res].connectivity = connectivity;

	res_table[res].inputs = res_index;

	res_table[res].outputs = (res_output_connection_t*)((void*)(res_table[res].inputs) +
		sizeof(res_output_connection_t) * size * RES_NUM_INPUTS);

	res_table[res].internal = (res_internal_connection_t*)((void*)(res_table[res].outputs) +
		sizeof(res_input_connection_t) * size * RES_NUM_OUTPUTS);

	res_index = res_table[res].internal + 
		sizeof(res_internal_connection_t) * connectivity;

	if (res_index > (void*)res_data + RES_DATA_SIZE) {
		res_index = res_data + RES_DATA_SIZE;
		res_table[res].size = 0;
		res_table[res].connectivity = 0;
	}
}

void res_set_input_weight(res_index_t res,
	res_input_index_t input, res_neuron_index_t neuron, 
	res_weight_t weight) {
	if (input < RES_NUM_INPUTS && neuron < res_table[res].size) {
		res_table[res].inputs[neuron].weights[input] = weight;
	}
}

void res_append_neuron_weight(res_index_t res, res_connection_index_t index,
	res_neuron_index_t output, res_neuron_index_t input, 
	res_weight_t weight) {
	if (index < res_table[res].connectivity &&
		output < res_table[res].size && input < res_table[res].size &&
		output >= res_table[res].current_output) {
		res_table[res].current_output = output;
		res_table[res].internal[index].input = input;
		res_table[res].internal[index].output = output;
		res_table[res].internal[index].weight = weight;
	}
}

void res_set_output_weight(res_index_t res,
	res_output_index_t output, res_neuron_index_t neuron,
	res_weight_t weight) {
	if (output < RES_NUM_OUTPUTS && neuron < res_table[res].size) {
		res_table[res].outputs[neuron].weights[output] = weight;
	}
}

uint8_t res_get_checksum(res_index_t res) {
	uint8_t result = 0;
	for (int i = 0; i < sizeof(res_input_connection_t) * res_table[res].size * RES_NUM_INPUTS; i++) {
		result ^= *((uint8_t*)res_table[res].inputs + i);
	}
	for (int i = 0; i < sizeof(res_output_connection_t) * res_table[res].size * RES_NUM_OUTPUTS; i++) {
		result ^= *((uint8_t*)res_table[res].outputs + i);
	}
	for (int i = 0; i < sizeof(res_internal_connection_t) * res_table[res].connectivity; i++) {
		result ^= *((uint8_t*)res_table[res].outputs + i);
	}
	return result;
}

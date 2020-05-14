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
#include "res_sigmoid_table.h"

#include <stdbool.h>
#include <stdint.h>

#include <string.h>
#include <math.h>
#include <assert.h>

#include "log.h"

#include "crtp_reservoir.h"

#define RES_SIGMOID_SATURATION_P 2
#define RES_SIGMOID_SATURATION_I (1 << RES_SIGMOID_SATURATION_P)
#define RES_SIGMOID_SATURATION_F ((float)RES_SIGMOID_SATURATION_I)

/* Returns the absolute value of the float x. */
float res_abs(float x) {
	// Ensure we are using the right abs routine.
	// This amounts to one instruction and will be inlined.
	return fabsf(x);
}

/* Returns the magnitude of float x with the sign of float s.
 * Requires that x is positive. */
float res_match_sign(float x, float s) {
	// Get these to do bitwise manipulation of the float values
	uint32_t ix = *(uint32_t*)&x;
	uint32_t is = *(uint32_t*)&s;

	// Conditionally set the sign bit of ix
	ix |= is & 0x80000000;

	return *(float*)&ix;
}

float res_sigmoid(float x) {
	// First we check if we should saturate rather than table lookup
	if (res_abs(x) >= RES_SIGMOID_SATURATION_F) {
		return res_match_sign(1.0f, x);
	}

	// Compute the index in the lookup table
	float indexf = res_abs(x) * RES_SIGMOID_TABLE_SIZE;
	uint32_t index = ((uint32_t)indexf) >> RES_SIGMOID_SATURATION_P;

	// Look up the result and return the sign-matched output
	float y = res_sigmoid_table[index];
	return res_match_sign(y, x);
}

void res_propagate(reservoir_t *res,
	res_input_t *in, res_output_t *out,
	neuron_value_t *old, neuron_value_t *new) {

	// Clear the output values
	for (int i = 0; i < RES_NUM_OUTPUTS; i++) { out[i] = 0.0f; }

	// Pointer to the current neuron input descriptor
	neuron_input_t *n = res->input;

	// Update each neuron and its contribution to the output
	for (int i = 0; i < res->size; i++) {
		float sum = 0; // Sums passed to sigmoid function accumulated here

		// Sum inputs
		for (int j = 0; j < RES_NUM_INPUTS; j++) {
			sum += n->weight_input[j] * in[j];
		}
		// Sum internal connections
		for (int j = 0; j < n->num_recur; j++) {
			sum += n->weight_recur[j].weight * old[n->weight_recur[j].index];
		}

		// Calculate new neuron value
		new[i] = (1.0f - n->gamma) * old[i] + 
			n->gamma * res_sigmoid(sum + n->bias);

		// Accumulate contributions to outputs
		for (int j = 0; j < RES_NUM_OUTPUTS; j++) {
			out[j] += res->output[i].weight[j] * new[i];
		}
		
		// Advance pointer to the neuron input descriptor.
		char *nv = (char*)n + sizeof(neuron_input_t) + n->num_recur * 
			(offsetof(neuron_input_t, weight_recur[1]) - 
			 offsetof(neuron_input_t, weight_recur[0]));
		n = (neuron_input_t*)nv;
	}
}

LOG_GROUP_START(reservoir)

LOG_GROUP_STOP(reservoir)

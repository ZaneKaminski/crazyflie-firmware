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
 * resvr.h - 
 */
#include "resvr.h"
#include "resvr_sigmoid_table.h"

#include <stdbool.h>
#include <stdint.h>

#include <string.h>
#include <math.h>
#include <assert.h>

#include "log.h"

#include "crtp_resvr.h"

#define RESVR_SIGMOID_TABLE_SIZE 65536

// Saturation parameters
#define RESVR_SIGMOID_SAT_P 2
#define RESVR_SIGMOID_SAT_I (1 << RESVR_SIGMOID_SAT_P)
#define RESVR_SIGMOID_SAT_F ((float)RESVR_SIGMOID_SAT_I)


// Use fabsf! This amounts to one instruction and will all be inlined.
static inline float resvr_abs(float x) { return fabsf(x); }

/* Returns the magnitude of float x with the sign of float s.
 * Requires that x is positive. */
static float resvr_match_sign(float x, float s) {
	// Get these to do bitwise manipulation of the float values
	uint32_t ix = *(uint32_t*)&x;
	uint32_t is = *(uint32_t*)&s;

	// Conditionally set the sign bit of ix
	ix |= is & 0x80000000;

	return *(float*)&ix;
}

static float resvr_sigmoid(float x) {
	// First we check if we should saturate rather than table lookup
	if (resvr_abs(x) >= RESVR_SIGMOID_SAT_F) {
		return resvr_match_sign(1.0f, x);
	}

	// Compute the index in the lookup table
	float indexf = resvr_abs(x) * RESVR_SIGMOID_TABLE_SIZE;
	uint32_t index = ((uint32_t)indexf) >> RESVR_SIGMOID_SAT_P;

	// Look up the result and return the sign-matched output
	float y = resvr_sigmoid_table[index];
	return resvr_match_sign(y, x);
}

void resvr_propagate(resvr_t *res,
	resvr_input_t *in, resvr_output_t *out,
	resvr_neuron_value_t *old, resvr_neuron_value_t *new) {

	// Clear the output values
	for (int i = 0; i < RESVR_NUM_OUTPUTS; i++) { out[i] = 0.0f; }

	// Pointer to the current neuron input descriptor
	resvr_neuron_input_t *n = res->input;

	// Update each neuron and its contribution to the output
	for (int i = 0; i < res->size; i++) {
		float sum = 0; // Sums passed to sigmoid function accumulated here

		// Sum inputs
		for (int j = 0; j < RESVR_NUM_INPUTS; j++) {
			sum += n->weight_input[j] * in[j];
		}
		// Sum internal connections
		for (int j = 0; j < n->num_recur; j++) {
			sum += n->weight_recur[j].weight * old[n->weight_recur[j].index];
		}

		// Calculate new neuron value
		new[i] = (1.0f - n->gamma) * old[i] + 
			n->gamma * resvr_sigmoid(sum + n->bias);

		// Accumulate contributions to outputs
		for (int j = 0; j < RESVR_NUM_OUTPUTS; j++) {
			out[j] += res->output[i].weight[j] * new[i];
		}
		
		// Advance pointer to the neuron input descriptor.
		char *nv = (char*)n + sizeof(resvr_neuron_input_t) + n->num_recur * 
			(offsetof(resvr_neuron_input_t, weight_recur[1]) - 
			 offsetof(resvr_neuron_input_t, weight_recur[0]));
		n = (resvr_neuron_input_t*)nv;
	}
}

LOG_GROUP_START(resvr)

LOG_GROUP_STOP(resvr)

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
 * resvr.h - Reservoir type definitions
 */

#include <stdbool.h>
#include <stdint.h>

#ifndef __RESVR_H__
#define __RESVR_H__

#define RESVR_NUM_INPUTS 7
#define RESVR_NUM_OUTPUTS 4

typedef float resvr_input_t;
typedef float resvr_output_t;

typedef uint8_t resvr_neuron_count_t;
typedef uint8_t resvr_neuron_index_t;
typedef float resvr_neuron_value_t;
typedef float resvr_neuron_gamma_t;
typedef float resvr_neuron_bias_t;
typedef float resvr_neuron_weight_t;

typedef struct resvr_neuron_weight_recur_s {
	resvr_neuron_index_t index;
	resvr_neuron_weight_t weight;
} resvr_neuron_weight_recur_t;

typedef struct resvr_neuron_input_s {
	resvr_neuron_gamma_t gamma;
	resvr_neuron_bias_t bias;
	resvr_neuron_weight_t weight_input[RESVR_NUM_INPUTS];
	resvr_neuron_count_t num_recur;
	resvr_neuron_weight_recur_t weight_recur[];
} resvr_neuron_input_t;

typedef struct resvr_neuron_output_s {
	resvr_neuron_weight_t weight[RESVR_NUM_OUTPUTS];
} resvr_neuron_output_t;

typedef struct resvr_s {
	resvr_neuron_count_t size;
	resvr_neuron_input_t *input;
	resvr_neuron_output_t *output;
} resvr_t;

void resvr_propagate(resvr_t *res,
	resvr_input_t *in, resvr_output_t *out,
	resvr_neuron_value_t *old, resvr_neuron_value_t *new);

#endif //__RESVR_H__

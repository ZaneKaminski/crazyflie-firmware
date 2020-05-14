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

#include <stdbool.h>
#include <stdint.h>

#ifndef __RESERVOIR_H__
#define __RESERVOIR_H__

#define RES_NUM_INPUTS 7
#define RES_NUM_OUTPUTS 4

typedef float res_input_t;
typedef float res_output_t;

typedef uint8_t neuron_count_t;
typedef uint8_t neuron_index_t;
typedef float neuron_value_t;
typedef float neuron_gamma_t;
typedef float neuron_bias_t;
typedef float neuron_weight_t;

typedef struct neuron_weight_recur_s {
	neuron_index_t index;
	neuron_weight_t weight;
} neuron_weight_recur_t;

typedef struct neuron_input_s {
	neuron_gamma_t gamma;
	neuron_bias_t bias;
	neuron_weight_t weight_input[RES_NUM_INPUTS];
	neuron_count_t num_recur;
	neuron_weight_recur_t weight_recur[];
} neuron_input_t;

typedef struct neuron_output_s {
	neuron_weight_t weight[RES_NUM_OUTPUTS];
} neuron_output_t;

typedef struct reservoir_s {
	neuron_count_t size;
	neuron_input_t *input;
	neuron_output_t *output;
} reservoir_t;

void asdf(uint32_t x);

#define RES_SIGMOID_TABLE_SIZE 65536

#endif //__RESERVOIR_H__

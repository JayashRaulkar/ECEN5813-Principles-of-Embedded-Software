/*****************************************************************************
 * Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users
 * are permitted to modify this and use it to learn about the field of
 * embedded software. Jayash Arun Raulkar and the University of Colorado are not
 * liable for any misuse of this material.
 *****************************************************************************/

/*
 * @file    op_module.h
 * @brief	This is header file of functions for DAC intialisation, for generating the buffer, DMA
 *
 * @author  Jayash Arun Raulkar
 * @date    29 November 2023
 *
 */

#ifndef _OP_MODULE_H_
#define _OP_MODULE_H_

#include <stdint.h>


/* brief: Below is the initialization function of DAC
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void DAC_initialise();


/* brief: Below is function to fill the sine buffer with sine values
 *
 *  Parameters:
 *  Takes the buffer pointer into  which we want to fill values and the frequency of the sine wave
 *
 * Returns:
 *  none
 */
void generate_sine_waveform(uint16_t *buffer, uint32_t frequency);


/* brief: Below is function to fill the Square buffer with Square values
 *
 *  Parameters:
 *  Takes the buffer pointer into  which we want to fill values and the frequency of the Square wave
 *
 * Returns:
 *  none
 */
void generate_square_waveform(uint16_t *buffer, uint32_t frequency);


/* brief: Below is function to fill the Triangle buffer with Triangle values
 *
 *  Parameters:
 *  Takes the buffer pointer into  which we want to fill values and the frequency of the Triangle wave
 *
 * Returns:
 *  none
 */
void generate_triangle_waveform(uint16_t *buffer, uint32_t frequency);


/* brief: Below is function to fill the all buffers
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void generate_waveform_buffer();


/* brief: Below is function to put the values from buffer into DAC with DMA
 *
 *  Parameters:
 *  pointer to buffer from which we will we will pass he values to DAC
 *
 * Returns:
 *  none
 */
void generate_waveform(uint16_t *buffer, uint16_t wf_freq);


/* brief: Below is function to generate the all three waveforms
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void display_waveform();


/* brief: initialises DMA module
 *
 *  Parameters:
 *  pointer of source containing samples and the number of bytes or count
 *
 * Returns:
 *  none
 */
void Init_dma_for_playback(uint16_t *source, uint32_t count);


/* brief: Sets source and destination pointer and enable DMA
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void start_dma_playback();


/* brief: DMA modules Interuppt handler
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void DMA0_IRQHandler();


#endif // _OP_MODULE_H_

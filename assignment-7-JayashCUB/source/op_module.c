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
 * @file    op_module.c
 * @brief	This file has functions for DAC intialisation, for generating the buffer, DMA
 *
 * @author  Jayash Arun Raulkar
 * @date    29 November 2023
 *
 * @reference
 *
 * 	 1) Alexander G Dean's github repository and Book
 * 		 https://github.com/alexander-g-dean/ESF/tree/master/
 * 		 for DMA functions info about DAC
 */

#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "op_module.h" // include output module Header file
#include "fp_trig.h" // include header file of sin, square and triangle waveform
#include "mysystick.h" // include header file of systick API

#define DAC_PIN 	(30UL) 	// DAC pin number
#define SIN_WF_FREQ 	(600UL) // Set SINE wf frequency
#define SQ_WF_FREQ 	(400UL) // Set Square wf frequency
#define TRI_WF_FREQ 	(800UL) // Set triangular wf frequency

#define DAC_FREQ 	(96000UL) // DAC sampling rate
#define BUF_SIZE 		(1024UL) // define buffer size

#define DMA_CHANNEL 		0 // define the DMA channel number
#define DMA_REQUEST_SOURCE 	54 // set DMA trigger source as TPM0

uint16_t sin_wf_buf[BUF_SIZE]; // buffer to store SINE values
uint16_t sq_wf_buf[BUF_SIZE]; // buffer to store Square values
uint16_t Tri_wf_buf[BUF_SIZE]; // buffer to store Triangle values

uint8_t waveform = 0; // variable for differentiate all three waveforms

uint16_t* Reload_DMA_Source; // declare a pointer to reload DMA source
uint32_t Reload_DMA_Byte_count; // declare a variable to store the reload DMA byte count


void DAC_initialise()
{

    SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;     // Enable clock to DAC module

    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;    // Enable clock to PORTE module

    PORTE->PCR[DAC_PIN] &= (PORT_PCR_MUX(0));    // Set PTE30 as DAC (wiz Default AFR value 0)

    DAC0->C1 = 0;    // Disable the buffer
    DAC0->C2 = 0;    // Disable buffer pointer

    DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK; // Enable DAC0 and select DACREF_2 as the reference voltage
}


void generate_sine_waveform(uint16_t *buffer, uint32_t frequency)
{
    uint32_t samples_per_period = (DAC_FREQ / frequency);    // Calculate the no of samples for each Waveform

    uint32_t no_of_wf = BUF_SIZE / samples_per_period;    // Calculate the number of waveforms in buffer

    uint32_t total_no_of_samples = samples_per_period * no_of_wf;    // Calculate total actual samples in buffer

    for(int i = 0; i < total_no_of_samples; i++)     // Fill the buffer with sine values
    {
        buffer[i] = fp_sin(i*TWO_PI / samples_per_period) + TRIG_SCALE_FACTOR;
    }
}


void generate_square_waveform(uint16_t *buffer, uint32_t frequency)
{
    uint32_t samples_per_period = (DAC_FREQ / frequency);    // Calculate the no of samples for each Waveform

    uint32_t no_of_wf = BUF_SIZE / samples_per_period;    // Calculate the number of waveforms in buffer

    uint32_t total_no_of_samples = samples_per_period * no_of_wf;    // Calculate total actual samples in buffer

    for(int i = 0; i < total_no_of_samples; i++)     // Fill the buffer with square wf values
    {
        buffer[i] = fp_square(i*TWO_PI / samples_per_period) + TRIG_SCALE_FACTOR;
    }
}

void generate_triangle_waveform(uint16_t *buffer, uint32_t frequency)
{
    uint32_t samples_per_period = (DAC_FREQ / frequency);    // Calculate the no of samples for each Waveform

    uint32_t no_of_wf = BUF_SIZE / samples_per_period;    // Calculate the number of waveforms in buffer

    uint32_t total_no_of_samples = samples_per_period * no_of_wf;    // Calculate total actual samples in buffer

    for(int i = 0; i < total_no_of_samples; i++)      // Fill the buffer with triangular values
    {
        buffer[i] = fp_triangle(i*TWO_PI / samples_per_period) + TRIG_SCALE_FACTOR;
    }
}


void generate_waveform_buffer() {

    generate_sine_waveform(sin_wf_buf, SIN_WF_FREQ);    // Generate SINE values and store it in sin_wf_buf

    generate_square_waveform(sq_wf_buf, SQ_WF_FREQ);    // Generate SQUARE values and store it in sq_wf_buf

    generate_triangle_waveform(Tri_wf_buf, TRI_WF_FREQ);    // Generate Triangle values and store it in Tri_wf_buf

}


void generate_waveform(uint16_t *buffer, uint16_t wf_freq)
{
    uint32_t samples_per_period = (DAC_FREQ / wf_freq);    // Calculate the no of samples for each Waveform

    uint32_t no_of_wf = BUF_SIZE / samples_per_period;    // Calculate the number of waveforms in buffer

    uint32_t total_no_of_samples = samples_per_period * no_of_wf;    // Calculate total actual samples in buffer

    // Print the number of generated samples, the computed period and the tone frequency
    PRINTF("\n\rGenerated %d samples at %d Hz computed period=%d samples\n\r", total_no_of_samples, wf_freq, samples_per_period);

    // Reset the timer
    reset_timer();

    // Initialize DMA for playback with the generated samples
    Init_dma_for_playback(buffer, total_no_of_samples);

    // Start DMA playback
    start_dma_playback();
}


void display_waveform()
{
	// Sine Waveform
	if (waveform==0) {
		generate_waveform(sin_wf_buf, SIN_WF_FREQ); // generate wf for sine
		waveform++; //next square
	}
	// Square Waveform
	else if (waveform==1) {
		generate_waveform(sq_wf_buf, SQ_WF_FREQ); // generate wf for square
		waveform++; //next triangle
	}
	// Triangular Waveform
	else if (waveform==2) {
		generate_waveform(Tri_wf_buf, TRI_WF_FREQ); // generate wf for triangle
		waveform = 0; // reset to start again from sine
	}
}

void Init_dma_for_playback(uint16_t *source, uint32_t count) {

    // Save reload info
    Reload_DMA_Source = source;
    Reload_DMA_Byte_count = count * 2;

    // Enable the DMA and DMAMUX clocks
    SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
    SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

    // Disable DMA channel to allow configuration
    DMAMUX0->CHCFG[DMA_CHANNEL] = 0;

    //generate DMA interuppt when done, increment source, transfer words(16bits), enable peripheral request
    DMA0->DMA[DMA_CHANNEL].DCR = DMA_DCR_EINT_MASK | DMA_DCR_SINC_MASK | DMA_DCR_SSIZE(2) |
    		DMA_DCR_DSIZE(2) | DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK ;

    // Set the DMA interrupt priority and enable the DMA interrupt
    NVIC_SetPriority(DMA0_IRQn, 2);
    NVIC_ClearPendingIRQ(DMA0_IRQn);
    NVIC_EnableIRQ(DMA0_IRQn);

    // Set DMA MUX channel to use TPM0 overflow as trigger
    DMAMUX0->CHCFG[DMA_CHANNEL] = DMAMUX_CHCFG_SOURCE(DMA_REQUEST_SOURCE);

}

void start_dma_playback() {

    // initialise source and destination pointers
    DMA0->DMA[DMA_CHANNEL].SAR = DMA_SAR_SAR((uint32_t) Reload_DMA_Source);
    DMA0->DMA[DMA_CHANNEL].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));
    //set the byte count
    DMA0->DMA[DMA_CHANNEL].DSR_BCR = DMA_DSR_BCR_BCR(Reload_DMA_Byte_count);

    // Clear the DMA done flag
    DMA0->DMA[DMA_CHANNEL].DSR_BCR &= ~DMA_DSR_BCR_DONE_MASK;
    // Set enable flag
    DMAMUX0->CHCFG[DMA_CHANNEL] |= DMAMUX_CHCFG_ENBL_MASK;

}

void DMA0_IRQHandler() {

    // Clear the DMA done flag
    DMA0->DMA[DMA_CHANNEL].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
    // Start the next DMA playback cycle
    start_dma_playback();

}

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
 * @file    ip_module.c
 * @brief	This file has functions for ADC intialisation and analysing Waveforms
 *
 * @author  Jayash Arun Raulkar
 * @date    29 November 2023
 *
 * @reference
 *
 * 	 1) Alexander G Dean's github repository and Book
 * 		 https://github.com/alexander-g-dean/ESF/tree/master/
 */

#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "autocorrelate.h"                 		// Include the autocorrelate header file.
#include "mytpm.h"                           	// Include the tpm header file.

#include <ip_module.h>                   		// Include the input module header file.

#define ADC_PIN                  (20UL)    // Define ADC pin 20.
#define ADC_INPUT_CHANNEL        (23UL)    // Define ADC input channel as 23.
#define ADC_BUF_SIZE        (1024UL)       // Define the global input buffer size as 1024.

#define GENERIC_DELAY_CYCLES        (2)
#define DELAY_TIME                  (3)

uint16_t ADC_buffer[ADC_BUF_SIZE];  // Define the global input buffer.


void ADC_initialise(void)
{
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;  // Enable clock for ADC0 module

    PORTE->PCR[ADC_PIN] &= ~PORT_PCR_MUX_MASK;
    PORTE->PCR[ADC_PIN] |= PORT_PCR_MUX(0);     // Set the PTE20 as ADC

    // ADC configuration: single-ended 16-bit conversion, Bus clock,  (input clock)/4.
    ADC0->CFG1 = ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0) | ADC_CFG1_ADIV(2);

    ADC0->SC1[0] |= ADC_SC1_ADCH(ADC_INPUT_CHANNEL); //AD23 is selected as input channel for the ADC

    ADC0->SC2 |= ADC_SC2_ADTRG(1); //setting  hardware trigger

    //Alternate trigger selected for ADC0, TPM1 overflow,  Pre-trigger A
    SIM->SOPT7 |= SIM_SOPT7_ADC0ALTTRGEN(1) | SIM_SOPT7_ADC0TRGSEL(9) | SIM_SOPT7_ADC0PRETRGSEL(0);
}

//for creating a very small delay in order to not lose the converted values
void generic_delay(int n) {
    int i, k;
    for (i = 0; i < n; i++) {
        __asm("nop"); // No operation
        for (k = 0; k <= GENERIC_DELAY_CYCLES; k++) {
             __asm("nop"); // NO operation
        }
    }
}


void waveform_input(void) {
    for(int i = 0; i < ADC_BUF_SIZE; i++) {

        ADC0->SC1[0] = ADC_INPUT_CHANNEL;    // Start ADC conversion

        while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)) {
            // Wait for ADC conversion to complete
        }

        generic_delay(DELAY_TIME);        // Small Delay for good sampling and complete conversion

        ADC_buffer[i] = ADC0->R[0];      // Store ADC converted output in buffer
    }
}



void waveform_calculation(void) {
    int sum = 0; // initialize a variable to store the sum of all the values in the global input buffer
    int min = ADC_buffer[0]; // initialize the minimum value to the first value in the global input buffer
    int max = ADC_buffer[0]; // initialize the maximum value to the first value in the global input buffer
    int i;

    //Loop to find the minimun and maximum value of the ADC buffer and to calculate the sum of all values.
    for(i = 0; i < ADC_BUF_SIZE; i++)
    {
        if(min > ADC_buffer[i])
        {
            min = ADC_buffer[i];
        }
        if(max < ADC_buffer[i])
        {
            max = ADC_buffer[i];
        }
        sum += ADC_buffer[i];
    }

    int avg = sum / i;  //average value

    int period = autocorrelate_detect_period(ADC_buffer, ADC_BUF_SIZE, kAC_16bps_unsigned);     // fundamental period of a waveform using autocorrelation

    PRINTF(" min=%d max=%d avg=%d period=%d samples frequency=%d Hz\n\r",
        min, max, avg, period, (TPM_OVERFLOW / period));
}

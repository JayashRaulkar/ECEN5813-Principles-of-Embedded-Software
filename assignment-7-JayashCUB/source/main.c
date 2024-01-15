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
 * @file    main.c
 * @brief	This is the main file which calls all initialization function
 * 			and all waveform functions
 *
 * @author  Jayash Arun Raulkar
 * @date    29 November 2023
 *
 * @reference
 *
 * 	 1) Alexander G Dean's github repository and Book
 * 		 https://github.com/alexander-g-dean/ESF/tree/master/
 *	 2) Prof Lalit Pandit, Class ppt for understanding of DAC, ADC, Scaling and Sampling
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "test_sine.h"					// include header file for testing sine wave
#include <stdio.h>
#include "peripherals.h"
#include "clock_config.h"
#include "MKL25Z4.h"


#include "fp_trig.h"                   	// include header file for fixed-point trigonometry functions
#include "mytpm.h"                      // include header file for TPM
#include "mysystick.h"                  // include header file for systick
#include "op_module.h"              	// include header file for output module (DAC DMA)
#include "ip_module.h"               	// include header file for input module (ADC)


int main(void)
{
	/* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("PES Assignment 7: Waveforms\r\n\n");
    test_sin();
    //test_taylor_sin();

    DAC_initialise();               // Initialize DAC
    generate_waveform_buffer();     // Fill buffer all 3 waves
    timer_init_TMP0(TPM_PERIOD);  	// Initialize TPM0
    timer_init_TMP1();				// Initialize TPM1
    init_systick();                 // Initialize SysTick
    ADC_initialise();               // Initialize ADC

    while (1)
    {
    	delay_ms(2000);
    	display_waveform();			//Display Waveform
    	waveform_input();			//Fill ADC data into buffer
    	waveform_calculation();		//Calculate Waveform Parameters
    }
}

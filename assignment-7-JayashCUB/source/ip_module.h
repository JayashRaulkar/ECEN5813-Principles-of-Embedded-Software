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
 * @file    ip_module.h
 * @brief	Header file ADC initialisation and analyzing Waveforms
 *
 * @author  Jayash Arun Raulkar
 * @date    29 November 2023
 *
 * @reference
 *
 * 	 1) Alexander G Dean's github repository and Book
 * 		 https://github.com/alexander-g-dean/ESF/tree/master/
 */

#ifndef _IP_MODULE_H_
#define _IP_MODULE_H_


/* brief: Below is the initialization function of ADC
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void ADC_initialise(void);


/* brief: Fills an  buffer with ADC conversion values
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void waveform_input(void);


/*
 * brief: calculates min max and total of of values in ADC buffer.
 *
 * Parameters:
 *    None
 *
 * Returns:
 *    None
 */
void waveform_calculation(void);


/* brief: generic delay function
 *
 *  Parameters:
 *  n
 *
 * Returns:
 *  none
 */
void generic_delay(int n);


#endif // _IP_MODULE_H_

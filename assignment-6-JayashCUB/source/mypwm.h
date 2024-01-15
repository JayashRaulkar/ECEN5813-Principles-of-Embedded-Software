/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    mypwm.h
 * @brief   header file for pwm led
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    11 November 2023
 *
 */
#ifndef MYPWM_H_    //Header guards to avoid repetetion of including multiple headers
#define MYPWM_H_

#include <stdint.h>
#include "MKL25Z4.h"
// Freedom KL25Z LEDs
#define RED_LED_POS (18)		// on port B red light
#define GREEN_LED_POS (19)	// on port B green lilght
#define BLUE_LED_POS (1)		// on port D blue light

#define PWM_PERIOD (0xff)		//Setting the PWM period as 0xff (255) because it will be easy to
								//match it with different RGb values varying from 0 to 0xff (0 to 255)
								// thus setting the resolution of Output compare TPM with 255 levels

void Init_LED_PWM(uint16_t period);
void PWM_LED_control(uint32_t RGB_value);

#endif

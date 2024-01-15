/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    mysystick.c
 * @brief   This file has functions to initialize the Systick timer
 * 			and various other API functions
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    11 November 2023
 *
 */
#include <stdint.h>
#include "mysystick.h"
#include <MKL25Z4.H>


volatile uint32_t ticks = 0;  // Making it volatile as it's modified in ISR
volatile uint32_t reset_ticks = 0;  // Making it volatile as it's modified in ISR

/* brief: Below is the intialization function of systick timer
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void init_systick(void)
{

    SysTick->LOAD = 1500 - 1; // -1 because it's zero indexed
    NVIC_SetPriority(SysTick_IRQn, 3);
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
    NVIC_EnableIRQ(SysTick_IRQn);
}

/* brief: ISR of the Systick handler
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void SysTick_Handler(void)
{
    //incrementing ticks every 1ms
	ticks++;
    reset_ticks++;
}

/* brief: function for 1ms delay
 *
 *  Parameters:
 *  number of ms delay we want
 *
 * Returns:
 *  none
 */
void delay_ms(ticktime_t delay)
{
	//wait till ticks equal to given delay
	uint32_t start_ticks = ticks;
    while ((ticks - start_ticks) < delay);
}


// returns time since startup, in one tenth of a second
ticktime_t now()
{
	return ticks;
}

/*Returns total number of ticks since last reset_timer function call*/
ticktime_t get_timer()
{
	return reset_ticks;
}

/* Resets the reset counter value to 0*/
void reset_timer()
{
	reset_ticks = 0;
}

/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    mysystick.h
 * @brief   header file for Systick timer
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    14 October 2023
 *
 */

#ifndef MYSYSTICK_H_
#define MYSYSTICK_H_


extern volatile uint32_t ticks;  // Making it extern as it is initialised in mysystick.c
extern volatile uint32_t reset_ticks;  // Making it extern as it is initialised in mysystick.c

typedef uint32_t ticktime_t;

void init_systick(void);
void SysTick_Handler(void);
void delay_ms(ticktime_t delay);
ticktime_t now();
ticktime_t get_timer();
void reset_timer();

#endif

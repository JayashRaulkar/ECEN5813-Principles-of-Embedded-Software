
/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    myled.h
 * @brief   header file for LEDs
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    03 October 2023
 *
 */

#ifndef MYLED_H_
#define MYLED_H_

#define RED_LED_SHIFT (18)		//for PTB18
#define GREEN_LED_SHIFT (19)	//for PTB19
#define BLUE_LED_SHIFT (1)		//for PTD1
#define MASK(x) (1UL << (x))
//aprrox delay values for 1000ms 500ms and 100ms are defined as macro to be used by delay function
#define ms_1000 5000000
#define ms_500 2500000
#define ms_100 500000
//my delay function declaration. takes an uint as parameter
void mydelay(volatile unsigned int time_del);
/*Below are the function declaration of functions which are
 * defined in myled.c file. No parameters (void)*/
void LED_init(void);
void LED_clear(void);
void RED_on(void);
void GREEN_on(void);
void BLUE_on(void);
void WHITE_on(void);
void YELLOW_on();
void startup_LED_test(void);


#endif

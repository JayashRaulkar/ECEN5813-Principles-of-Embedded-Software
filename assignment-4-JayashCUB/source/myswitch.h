/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    myswitch.h
 * @brief   header file for external switch interfacing
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    17 October 2023
 *
 */

#ifndef MYSWITCH_H_    //Header guards to avoid repetetion of including multiple headers
#define MYSWITCH_H_

#define PTD5_shift 5
#define MASK(x) (1UL << (x))

void ptd5_int_init(void);
void PORTD_IRQHandler();
void emergency_function(uint32_t cur_st_RGB);

#endif

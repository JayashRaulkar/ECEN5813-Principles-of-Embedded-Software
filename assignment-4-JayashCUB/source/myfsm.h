/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    myfsm.h
 * @brief   header file for Finite state machine
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    14 October 2023
 *
 */

#ifndef MYFSM_H_    //Header guards to avoid repetetion of including multiple headers
#define MYFSM_H_

//RGB values for the 4 states: terminal T, concourse A/B , shed S
#define st_T_RGB (0xFFFFFF)
#define st_A_RGB (0x0000FF)
#define st_B_RGB (0x00FF00)
#define st_S_RGB (0x00FFFF)


void my_FSM(void);
void transition(uint32_t from, uint32_t to);

#endif

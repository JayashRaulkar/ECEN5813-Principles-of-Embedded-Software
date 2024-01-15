/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    mylog.h
 * @brief   log.h - abstraction away from printf
 * 					and different delay values for DEBUG and RELEASE MODE
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    14 October 2023
 *
 */
#ifndef MYLOG_H_
#define MYLOG_H_

#ifdef DEBUG
#define LOG PRINTF
#define T_delay_count 30
#define A_delay_count 20
#define B_delay_count 20
#define S_delay_count 10
#else
#define LOG(...)
#define T_delay_count 50
#define A_delay_count 40
#define B_delay_count 40
#define S_delay_count 30
#endif

#endif

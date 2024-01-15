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
 *          credits - Prof. Lalit Pandit
 *          Source - class ppt
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    03 October 2023
 *
 */

#ifndef MYLOG_H_
#define MYLOG_H_

#ifdef DEBUG
# define LOG PRINTF
#else
# define LOG(...)
#endif

#endif /* MYLOG_H_ */

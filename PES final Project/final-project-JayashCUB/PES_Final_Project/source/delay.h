/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    delay.h
 * @brief   header file for delay function
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    10 December 2023
 *
 */

#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

/* brief: Generic delay having for loop to create a small delay
 *
 *  Parameters:
 *  delay ticks for a loop
 *
 * Returns:
 *  none
 */
void Delay(uint32_t dlyTicks);

#endif

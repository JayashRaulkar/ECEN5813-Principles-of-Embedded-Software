/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    mymma.h
 * @brief   header file for mma sensor
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    10 December 2023
 *
 */

#ifndef MMA8451_H
#define MMA8451_H
#include <stdint.h>

//device addrress
#define MMA_ADDR 0x3A

//sensor data registers
#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_CTRL1  0x2A

//variable to store sensor data
extern int16_t acc_X, acc_Y, acc_Z;

/* brief: Below is the intialization function for mma sensor
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void init_mma(void);


/* brief: Below is the function to read mma sensor data
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void read_xyz(void);

#endif

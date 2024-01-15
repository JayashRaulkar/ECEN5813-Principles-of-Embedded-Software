/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    mymma.c
 * @brief   This file has function definition of all mma functions
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    10 December 2023
 *
 */

#include <MKL25Z4.H>
#include "mymma.h"
#include "myi2c.h"
#include "delay.h"
#include <math.h>

int16_t acc_X=0, acc_Y=0, acc_Z=0;   //set to zero

//initializes mma8451 sensor
//i2c has to already be enabled
void init_mma()
{
	//set active mode, 14 bit samples and 800 Hz ODR
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
}

//read accel x y and z values
void read_xyz(void)
{
	// sign extend byte to 16 bits - need to cast to signed since function
	// returns uint8_t which is unsigned
	acc_X = (int8_t) i2c_read_byte(MMA_ADDR, REG_XHI);
	Delay(100);
	acc_Y = (int8_t) i2c_read_byte(MMA_ADDR, REG_YHI);
	Delay(100);
	acc_Z = (int8_t) i2c_read_byte(MMA_ADDR, REG_ZHI);
}

/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    myi2c.h
 * @brief   header file for I2C
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    10 December 2023
 *
 */
#ifndef _MYI2C_H_
#define _MYI2C_H_

#include <stdint.h>

#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK          	//select master mode
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK			//select slave mode
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK			//create a repeated start

#define I2C_TRAN			I2C0->C1 |= I2C_C1_TX_MASK			//selects transmit direction
#define I2C_REC				I2C0->C1 &= ~I2C_C1_TX_MASK			//selects receive direction

#define BUSY_ACK 	    while(I2C0->S & 0x01)					//wait till ack signal is received
#define TRANS_COMP		while(!(I2C0->S & 0x80))				//wait till transfer is complete

#define I2C_WAIT		while((I2C0->S & I2C_S_IICIF_MASK)==0) {} \
							I2C0->S |= I2C_S_IICIF_MASK;

#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK           I2C0->C1 &= ~I2C_C1_TXAK_MASK				//acknowledge signal is sent to the bus



/* brief: Below is the intialization function I2C
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void i2c_init(void);



/* brief: Below is the function to read a byte using I2C
 *
 *  Parameters:
 *  device address and register adress from which we want to read
 *
 * Returns:
 *  the read byte
 */
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);



/* brief: Below is the function to write a byte using I2C
 *
 *  Parameters:
 *  device address and register address to which we want to write
 *
 * Returns:
 *  none
 */
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif //_MYI2C_H_

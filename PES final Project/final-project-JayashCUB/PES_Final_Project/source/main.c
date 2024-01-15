/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    main.c
 * @brief   main file having calling init functions, reads sensor data and sends to arduino
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    10 December 2023
 *
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include <mycbfifo.h>				// Header file for cbfifo
#include "myuart.h"					// Header file for UART

#include "delay.h"					//Header of delay function
#include "myi2c.h"					// Header file for I2C
#include "mymma.h"					// Header file for MMA sensor

// Define the UART baud rate
#define BAUD_RATE (38400)

int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    Init_UART0(BAUD_RATE);				//Initailize UART
    PRINTF("UART initialised \n\r ");
    i2c_init();							//Initailize I2C
    PRINTF("IIC initialised \n\r ");
    init_mma();							//Initailize MMA
    PRINTF("MMA initialised \n\r ");
    Delay(100);

    while(1) {
    	read_xyz();						//read sensor register for xyz value
    	PRINTF("acc_X is:");
    	uart_send_integer(acc_X);		//send x value to Arduino
    	PRINTF("\n\r");
    	Delay(500);						//for synchronization
    }
    return 0 ;
}

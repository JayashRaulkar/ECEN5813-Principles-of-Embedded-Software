/*****************************************************************************
 * Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users
 * are permitted to modify this and use it to learn about the field of
 * embedded software. Jayash Arun Raulkar and the University of Colorado are not
 * liable for any misuse of this material.
 *****************************************************************************/

/**
 * @file    main.c
 * @brief   main file
 *
 * @author  Jayash Arun Raulkar
 * @date    11 November 2023
 *
 * @references
 *
 * 	1) Alexander G Dean's github repository and Book for UART configration - https://github.com/alexander-g-dean/ESF/tree/master/
 * 	2) Prof. Lalit Pandit for the command processing code of lexical analysis, using fucntion pointers and lookup table. - Lecture Slides
 *	3) Sai Charan Mandadi for clearing doubts of what exactly happens to buffer during transmission and reception of data on Tx RX
 */

// Include standard C headers
#include <stdio.h>

// Include headers for the system clock, UART, command processor, systick and led
#include "sysclock.h"
#include "myuart.h"
#include "mycmdproc.h"
#include "mysystick.h"
#include "mypwm.h"

// Define the UART baud rate
#define BAUD_RATE (38400)

int main(void)
{
    // Initialize the system clock
    sysclock_init();
    init_systick();	    //Initialise systick
    Init_LED_PWM(PWM_PERIOD);
    Init_UART0(BAUD_RATE);		//Initialise UART with Baud rate 38400
    printf("\n\r \033[34mBy- Jayash A Raulkar\033[0m \n\r");  //used ANSI escape codes for formatting
    printf("\n\r\033[32mWelcome to SerialIO!\033[0m\n\r");

    char user_line[127];     	//for user string

    while (1) {
    	printf("$$ ");
        get_user_line(user_line);
        process_command(user_line);
        __asm volatile ("nop");
    }

    return 0;
}

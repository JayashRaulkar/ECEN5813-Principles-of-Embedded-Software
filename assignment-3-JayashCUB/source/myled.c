/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    myled.c
 * @brief   This file has fucntions to turn on or clear different leds
 * 			along with delay and startup test function
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    03 October 2023
 *
 */

#include "all.h"

/*Below is function to create delay
* source- Class ppt */
void mydelay(volatile unsigned int time_del)
{
	while(time_del--)
	{
		__asm volatile ("nop");    // no operation
	}
}

/* Below is the LED initialization function which enable the
 * clock gating for required ports, set pins as GPIO and as output
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void LED_init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK  | SIM_SCGC5_PORTD_MASK;		//enable clock for PORTB and D

	//make PTB18 PTB19 and PTD1 as GPIO
	    PORTB->PCR[RED_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;	//clear 8 9 10 location of MUX in PCR reg of pin 18 of port b
	    PORTB->PCR[RED_LED_SHIFT] |= PORT_PCR_MUX(1);		//Set pin 18 of port b as gpio
	    PORTB->PCR[GREEN_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;	//clear 8 9 10 location of MUX in PCR reg of pin 19 of port b
	    PORTB->PCR[GREEN_LED_SHIFT] |= PORT_PCR_MUX(1);		//set PTB19 as gpio
	    PORTD->PCR[BLUE_LED_SHIFT] &= ~PORT_PCR_MUX_MASK;	//clear 8 9 10 location of MUX in PCR reg of pin 1 of port d
	    PORTD->PCR[BLUE_LED_SHIFT] |= PORT_PCR_MUX(1);		//set PTD1 as gpio

	    //make PTB18 PTB19 and PTD1 as output using PDDR
	    PTB->PDDR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
	    PTD->PDDR |= MASK(BLUE_LED_SHIFT);
	    LED_clear();   // clear the values of all 3 pins connected to led
}

/*below function clears the pin 18 19 of port B and pin 1 of port D
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void LED_clear(void)
{
	//clear all leds using the pin set output reg as the anode of led is connected to 3V3
	PTB->PSOR |= MASK(RED_LED_SHIFT) | MASK(GREEN_LED_SHIFT);
	PTD->PSOR |= MASK(BLUE_LED_SHIFT);
}

void RED_on(void)    //function to turn RED led ON
{
	//turn ON RED
	PTB->PCOR |= MASK(RED_LED_SHIFT);    //using pin clear output register to clear pin 18 of port B
	LOG("RED is ON\r\n");    //prints status only in debug mode

}
void GREEN_on(void)    //function to turn led ON
{
	//turn ON GREEN
	PTB->PCOR |= MASK(GREEN_LED_SHIFT);    //using pin clear output register to clear pin 19 of port B
	LOG("GREEN is ON\r\n");    //prints status only in debug mode

}
void BLUE_on(void)    //function to turn led ON
{
	//turn ON BLUE
	PTD->PCOR |= MASK(BLUE_LED_SHIFT);    //using pin clear output register to clear pin 1 of port D
	LOG("BLUE is ON\r\n");    //prints status only in debug mode
}
void WHITE_on(void)    //function to turn led ON
{
	//Turns on all 3 leds red green and blue to show white
	RED_on();
	GREEN_on();
	BLUE_on();
	LOG("Thus White is ON\r\n");    //prints status only in debug mode
}
void YELLOW_on()     //function to turn led ON
{
	//Turns on all 2 leds red and green to show yellow
	RED_on();
	GREEN_on();
	LOG("Thus Yellow is ON\r\n");    //prints status only in debug mode
}

/* StartUp function showing the led sequence of White Blue Blue White
 * by keepin them on for aprrox 1000ms and off for 500ms using delay
 * functions in between
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none*/
void startup_LED_test(void)
{
	WHITE_on();
	mydelay(ms_1000);
	LED_clear();
	mydelay(ms_500);

	BLUE_on();
	mydelay(ms_1000);
	LED_clear();
	mydelay(ms_500);

	BLUE_on();
	mydelay(ms_1000);
	LED_clear();
	mydelay(ms_500);

	WHITE_on();
	mydelay(ms_1000);
	LED_clear();
	mydelay(ms_500);
}

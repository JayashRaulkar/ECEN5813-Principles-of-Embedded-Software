/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    myswitch.c
 * @brief   This file has fucntions to initialise external port pin
 * 			as an external switch, and emergency function to handle the emergency
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    17 October 2023
 *
 */

#include "all.h"

volatile uint8_t emergency_key = 0x00;  //variable to check if key is pressed


/* brief: Below is switch initialization function
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void ptd5_int_init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; //enable clock

	PORTD->PCR[PTD5_shift] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[PTD5_shift] |= PORT_PCR_MUX(1);	//make PD5 as gpio

	PTD->PDDR &= ~MASK(PTD5_shift);  //make PTD5 as input

	PORTD->PCR[PTD5_shift] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;  //pull enable & pulled up
	PORTD->PCR[PTD5_shift] |= PORT_PCR_IRQC(10);  //interrupt on falling edge

	NVIC_SetPriority(PORTD_IRQn, 4);
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	NVIC_EnableIRQ(PORTD_IRQn);
	__enable_irq();

}

/* brief: ISR of the Switch
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void PORTD_IRQHandler()
{
	if(PORTD->ISFR & MASK(PTD5_shift))
		{
			emergency_key = ~emergency_key;
			NVIC_ClearPendingIRQ(PORTD_IRQn);
			PORTD->ISFR = 0xFFFFFFFF;

		}
}


/* brief: Below is switch emergency function turning emergency light and current position led
 *
 *  Parameters:
 *  the led rgb value to blink with emergency light
 *
 * Returns:
 *  none
 */
void emergency_function(uint32_t cur_st_RGB)
{
	while(emergency_key)
	{
		LED_control(emergency_light);
		for(int i=0;i<5;i++)
		{
			delay_ms(100);
			if(!emergency_key) // Check if the flag is reset and break out of the while loop
			{
				break; // This will break out of the for loop
			}
		}
		if(!emergency_key) // Check if the flag is reset and break out of the while loop
		{
			break; // This will break out of the while loop
		}

		LED_control(cur_st_RGB);
		for(int i=0;i<5;i++)
		{
			delay_ms(100);
			if(!emergency_key) // Check if the flag is reset and break out of the while loop
			{
				break; // This will break out of the for loop
			}
		}
		if(!emergency_key) // Check if the flag is reset and break out of the while loop
		{
			break; // This will break out of the while loop
		}
	}
}

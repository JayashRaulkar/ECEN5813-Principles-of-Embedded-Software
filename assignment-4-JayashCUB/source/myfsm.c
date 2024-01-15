/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    myfsm.c
 * @brief   This file has fucntions to turn on or clear different leds
 * 			along with delay and startup test function
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    14 October 2023
 *
 */

#include "all.h"

volatile uint8_t return_journey = 0;		//variable to check the train direction


/* brief: Below is the FSM implementation function wherein i have created 4 states T A B and S
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void my_FSM(void)
{
	static enum {st_T,st_A,st_B,st_S}state=st_T;		//setting starting state as st_T

	switch(state)
	{
	case st_T:
		LED_control(st_T_RGB);		//Turn on T state Light
		LOG("state T WHITE\r\n");

		for(int i=0; i< T_delay_count;i++)
		{
			delay_ms(50);
			check_touch(st_T_RGB);	 //polling TSI module
			emergency_function(st_T_RGB);
			delay_ms(50);
		}
		LOG("msec since startup: %d \r\n",now());
		LOG("state T WHIte to state A BLUE\r\n");
		transition(st_T_RGB,st_A_RGB);		//Transition to next state
		LOG("msec since startup: %d \r\n",now());
		return_journey = 0;
		state=st_A;
		break;
	case st_A:
		if(!(return_journey))
		{
			LED_control(st_A_RGB);		//Turn on A state Light
			LOG("state A BLUE\r\n");

			for(int i=0; i< A_delay_count;i++)
			{
				delay_ms(50);
				check_touch(st_A_RGB);	 //polling TSI module
				emergency_function(st_A_RGB);
				delay_ms(50);
			}
			LOG("msec since startup: %d \r\n",now());
			LOG("state A BLUE to state B GREEN\r\n");
			transition(st_A_RGB,st_B_RGB);		//Transition to next state
			LOG("msec since startup: %d \r\n",now());
			state=st_B;
		}
		else
		{
			LED_control(st_A_RGB);		//Turn on A state Light
			LOG("state A BLUE Return j\r\n");

			for(int i=0; i< A_delay_count;i++)
			{
				delay_ms(50);
				check_touch(st_A_RGB);	 //polling TSI module
				emergency_function(st_A_RGB);
				delay_ms(50);
			}
			LOG("msec since startup: %d \r\n",now());
			LOG("state A BLUE to state T WHITE\r\n");
			transition(st_A_RGB,st_T_RGB);		//Transition to next state
			LOG("msec since startup: %d \r\n",now());
			state=st_T;
		}
		break;
	case st_B:
		if(!(return_journey))
		{
			LED_control(st_B_RGB);		//Turn on B state Light
			LOG("state B GREEN\r\n");

			for(int i=0; i< B_delay_count;i++)
			{
				delay_ms(50);
				check_touch(st_B_RGB);	 //polling TSI module
				emergency_function(st_B_RGB);
				delay_ms(50);
			}
			LOG("msec since startup: %d \r\n",now());
			LOG("state B GREEN to state S CYAN\r\n");
			transition(st_B_RGB,st_S_RGB);		//Transition to next state
			LOG("msec since startup: %d \r\n",now());
			state=st_S;
		}
		else
		{
			LED_control(st_B_RGB);		//Turn on B state Light
			LOG("state B GREEN Return J\r\n");

			for(int i=0; i< B_delay_count;i++)
			{
				delay_ms(50);
				check_touch(st_B_RGB);	 //polling TSI module
				emergency_function(st_B_RGB);
				delay_ms(50);
			}
			LOG("msec since startup: %d \r\n",now());
			LOG("state B GREEN to state A BLUE\r\n");
			transition(st_B_RGB,st_A_RGB);			//Transition to next state
			LOG("msec since startup: %d \r\n",now());
			state=st_A;
		}
		break;
	case st_S:
		LED_control(st_S_RGB);		//Turn on S state Light
		LOG("state S cyan\r\n");

		for(int i=0; i< S_delay_count;i++)
		{
			delay_ms(50);
			check_touch(st_S_RGB);	 //polling TSI module
			emergency_function(st_S_RGB);
			delay_ms(50);
		}
		LOG("msec since startup: %d \r\n",now());
		LOG("state S cyan to state B green\r\n");
		transition(st_S_RGB,st_B_RGB);		//Transition to next state
		LOG("msec since startup: %d \r\n",now());
		return_journey = 1;
		state=st_B;
		break;
	default:
		state=st_T;
		break;
	}
}


/* brief: Below is the transition function which changes the RGB colour from
 * 		  one state to another
 *
 *  Parameters:
 *  takes the from it has to transition and the value to which it happens
 *
 * Returns:
 *  none
 */
void transition(uint32_t from, uint32_t to)
{
    for (int i = 0; i < 4; i++)
    {
        // Adjust the MSB (leftmost byte)
        if ((from & 0xFF0000) < (to & 0xFF0000)) //compares the MSB Byte
        {
            if(i==1)
            {
                from += 0x3F0000;
            }
            else
            {
                from += 0x400000;
            }
        }
        else if ((from & 0xFF0000) > (to & 0xFF0000)) //compares the MSB Byte
        {
            if(i==2)
            {
                from -= 0x3F0000;
            }
            else
            {
                from -= 0x400000;
            }
        }

        // Adjust the middle byte
        if ((from & 0x00FF00) < (to & 0x00FF00)) //compares the middle Byte
        {
            if(i==1)
            {
                from += 0x003f00;
            }
            else
            {
                from += 0x004000;
            }
        }
        else if ((from & 0x00FF00) > (to & 0x00FF00)) //compares the middle Byt
        {
            if(i==2)
            {
                from -= 0x003F00;
            }
            else
            {
                from -= 0x004000;
            }
        }

        // Adjust the LSB (rightmost byte)
        if ((from & 0x0000FF) < (to & 0x0000FF)) //compares the LSB Byte
        {
            if(i==1)
            {
                from += 0x00003F;
            }
            else
            {
                from += 0x000040;
            }
        }
        else if ((from & 0x0000FF) > (to & 0x0000FF)) //compares the LSB Byte
        {
            if(i==2)
            {
                from -= 0x00003F;
            }
            else
            {
                from -= 0x000040;
            }
        }

        LED_control(from);
        for(int j=0;j<5;j++)
        {
        	delay_ms(50);
        	check_touch(from); //polling TSI module
        	emergency_function(from);
        	delay_ms(50);
        }
    }
}


 /* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    Assg3_Trafficlights_MKL25Z4_project.c
 * @brief   Blinkling led in  a specific pattern (R G Y) and poll touch sensor
 * 			in between to blink in a different way according to the position of the touch.
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    03 October 2023
 *
 */

#include "all.h"    //A single header file including necessary headers

int main(void) {

/*From line 27 to 34 is part of code written
  during creation of project*/
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif


        LED_init();    //led initialization function defined in myled.c
        Touch_Init();    //touch initialization function defined in mytouch.c
        PRINTF("Hello World\r\n");   //I like hello world in release build as well to check if initialisation is working or not

        startup_LED_test();    //led startup sequence function
        while(1)
        {

        	LED_clear();    //clears led (explain in myled.c)
        	RED_on();    //turn red led on
        	LOG("Start timer 1000ms\r\n");    //prints timer stats in debug mode
        	for(int i=0;i<10;i++)    //loop 10 times to check touch status every 100ms
        	{
        		mydelay(ms_100);
        		check_touch(touch_state,touch_val);    //check touch status (explained in mytouch.c)
        	}

            LED_clear();    //clears led
            GREEN_on();     //turn green led on
            LOG("Start timer 1000ms\r\n");    //prints timer stats in debug mode
            for(int i=0;i<10;i++)    //loop 10 times to check touch status every 100ms
            {
                mydelay(ms_100);
                check_touch(touch_state,touch_val);    //check touch status (explained in mytouch.c)
            }

            LED_clear();    //clears led
            YELLOW_on();    //turn yellow led on
            LOG("Start timer 1000ms\r\n");    //prints timer stats in debug mode
            for(int i=0;i<10;i++)    ////loop 10 times to check touch status every 100ms
        	{
        		mydelay(ms_100);
        		check_touch(touch_state,touch_val);    //check touch status (explained in mytouch.c)
        	}

        }
    return 0 ;
}

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
 * @brief   Denver International Airport Train monitoring system using finit state machines.
 * 			Used
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    14 October 2023
 *
 */

#include "all.h"  //A single header file including necessary headers

int main(void) {
	/*From line 24 to 33 is part of code written
	  during creation of project*/
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    init_systick();		//Systick Timer initialisation, defined in mysystick.c
    Init_LED_PWM(PWM_PERIOD);		//TPM initialisation, defined in mypwm.c
    Touch_Init();		//touch initialization function defined in mytouch.c
    ptd5_int_init();
    PRINTF("Hello World\r\n");		//I like hello world in release build as well to check if initialisation is working or not

    LOG("main loop starting\r\n");
    while(1)
    {
    	my_FSM();		//starting FSM, defined in myfsm.c
    }
    return 0 ;
}

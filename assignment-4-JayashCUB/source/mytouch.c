/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    mytouch.h
 * @brief   header file for TSI  Module
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    14 October 2023
 *
 */

#include "all.h"

volatile uint32_t touch_val = 0 ;
volatile uint8_t emergency_flag = 0;

void Touch_Init()
{
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; // enabling the clock

	TSI0->GENCS = TSI_GENCS_MODE(0u) |
			//operating in non-noise mode
			//clearing 27-24 bits for operating in non-noise mode

				  TSI_GENCS_REFCHRG(0u) |
				  //reference oscillator charge and discharge value 500nA
				  //clearing 23-21 bits for 500nA reference oscillator charge and discharge value

				TSI_GENCS_DVOLT(0u) |
				//oscillator voltage rails set to default
				//clearing 20-19 bits for DV = 1.03 V; VP = 1.33 V; Vm = 0.30 V. i.e. oscillator voltage rails set to default

				TSI_GENCS_EXTCHRG(0u) |
				//electrode oscillator charge and discharge value 500nA
				//clearing 18-16 bits for 500nA electrode oscillator charge and discharge value

				TSI_GENCS_PS(0u) |
				//clearing 15-13 for frequency clock divided by one

				TSI_GENCS_NSCN(31u) |
				//setting 12-8 for scanning the electrode 32 times

				TSI_GENCS_TSIEN_MASK |
				//setting 7th bit for enabling the TSI module

				TSI_GENCS_EOSF_MASK;
				// writing one in 3rd bit to clear the end of scan flag

}

/* brief: function to scan the value from TSI module DATA register
 *
 *  Parameters:
 *  none
 *
 * Returns:
 * returns int of scanned value minus the offset
 */
int Touch_Scan_LH(void)
{
	unsigned int scan = 0;   //a variable to read scan value
	TSI0->DATA = 	TSI_DATA_TSICH(10u);
	//putting 1010 in bits 31-28 for selecting channel 10 of TSI
	TSI0->DATA |= TSI_DATA_SWTS_MASK;
	//setting 22nd bit to Start a scan to determine which channel is specified by TSI_DATA[TSICH]
	while (!(TSI0->GENCS & TSI_GENCS_EOSF_MASK )) //checking EOSF flag to wait for the scan to complete 32 times
	;
	scan = TOUCH_DATA;   //put 15-0 bit value of TSI data register in scan
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK ;    //set EOSF to 1 to indicate scan is complete
	//writing one in 3rd bit of general control and status reg. to clear the end of scan flag
	return scan- TOUCH_OFFSET;  //return touch data value minus the offset
}

/* brief: function to check the touch for TSI module and enter the emergency
 * 	      and later on when touched the secound come out and resume with the state in FSM
 *
 *  Parameters:
 *  the RGB value of the current state in FSM in which emergency happened
 *
 * Returns:
 * none
 */
void check_touch(uint32_t cur_st_RGB)
{
    touch_val = Touch_Scan_LH();
    //PRINTF("Value of Touch Scan in check touch: %d \n\r", touch_val);
    if (touch_val > TOUCH_THRESHOLD && emergency_flag == 0)			//check for first touch
    {
        emergency_flag = 1; // Enter emergency mode
        LOG("in Emergency\r\n");

        while(emergency_flag) // Only check the flag to decide to remain in the loop
        {
            LED_control(emergency_light);		//turn on emergencgy light RED
            for(int i = 0; i < 5; i++)
            {
                delay_ms(50);
                touch_val = Touch_Scan_LH();		//poll tsi for secound touch
                delay_ms(50);
                //PRINTF("Value of 2nd time Touch Scan: %d \n\r", touch_val);
                if (touch_val > TOUCH_THRESHOLD)   //check for secound touch
                {
                    emergency_flag = 0;  // Exit emergency mode
                    LED_control(0x000000);
                    break; // This will break out of the for loop
                }
            }

            if(!emergency_flag) // Check if the flag is reset and break out of the while loop
            {
            	LOG("going out of Emergency\r\n");
            	break; // This will break out of the while loop
            }
            LED_control(cur_st_RGB);
            for(int i = 0; i < 5; i++)
            {
            	delay_ms(50);
                touch_val = Touch_Scan_LH();  ////poll tsi for secound touch
                delay_ms(50);
                //PRINTF("Value of 2nd time Touch Scan: %d \n\r", touch_val);
                if (touch_val > TOUCH_THRESHOLD)		//check for secound touch
                {
                    emergency_flag = 0; // Exit emergency mode
                    LED_control(0x000000);
                    break; // This will break out of the for loop
                }
            }
            if(!emergency_flag) // Check if the flag is reset and break out of the while loop
            {
                LOG("going out of Emergency\r\n") ;
                break; // This will break out of the while loop
            }
        }
    }
}

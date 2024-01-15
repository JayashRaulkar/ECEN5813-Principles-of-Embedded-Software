/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    mytouch.c
 * @brief   this file has functions to initialise TSI module, get touch value,
 * 			perform tasks and to check touch status
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    03 October 2023
 *
 */

#include "all.h"

volatile uint32_t touch_val = 0 ;   //defined touch_val and initialized it to zero
volatile TouchState touch_state = NOT_TOUCHED;   //defined touch_state and set it to NOT_TOUCHED

/*function to initialize TSI module by giving clock to TSI
 * and using general control and status register
 * source- Alexander dean Repo
 * link: https://github.com/alexander-g-dean/ESF/blob/master/NXP/Misc/Touch%20Sense/TSI/src/main.c
 *
 *  Parameters:
 *  none
 *
 * Returns:
 *  none
 */
void Touch_Init()
{
	//to enable clock of TSI module we have to set the 6th bit of SCGC5
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; // giving 0x20 to enable the clock

	TSI0->GENCS = TSI_GENCS_MODE(0u) |
			    //clearing 27-24 bits for operating in non-noise mode
				TSI_GENCS_REFCHRG(0u) |
				//clearing 23-21 bits for 500nA reference oscillator charge and discharge value
				TSI_GENCS_DVOLT(0u) |
				//clearing 20-19 bits for DV = 1.03 V; VP = 1.33 V; Vm = 0.30 V. i.e. oscillator voltage rails set to default
				TSI_GENCS_EXTCHRG(0u) |
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


/*function to scan the value from TSI module DATA register
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


/* function perform the task of blinking white and blue led when touch is detected
 *
 *  Parameters:
 *  takes the touch value as parameter
 *
 * Returns:
 *  none*/
void TouchTask(uint32_t touch_val)
{
    // Begin the task.
    LOG("Touch Detected! Running TouchTask...\n\r");

    touch_state = TASK_RUNNING; // Lock out any touch input during task execution

    if (touch_val > RIGHT_THRESHOLD)
    {
    	LOG("Value of Touch Scan: %d \n\r",touch_val);   //prints touch value only in debug mode
    	//blinks white led with 1000ms delay
    	for(int i=0;i<3;i++)
    	{
    		LED_clear();
    		WHITE_on();
    		mydelay(ms_1000);
    		LED_clear();
    		mydelay(ms_500);
    	}
    }
    else
    {
    	LOG("Value of Touch Scan: %d \n\r",touch_val);    //prints touch value only in debug mode
    	//blinks blue led with 1000ms delay
    	for(int i=0;i<3;i++)
    	{
    		LED_clear();
    		BLUE_on();
    		mydelay(ms_1000);
    		LED_clear();
    		mydelay(ms_500);
    	}
    }

    touch_state = NOT_TOUCHED; // Reset the state once the task is done.
}


/*function to check wheter the touch sensor has been touched
 * takes current touch_state and touch_val as params
 *  Parameters:
 *  takes the touch value and touch state as parameter
 *
 * Returns:
 *  none
 *
 *  note: remove the self explaintory comments as mentioned by code reviewer
*/
void check_touch(TouchState touch_state, uint32_t touch_val)
{
	if(touch_state != TASK_RUNNING)
	    	{
	    	    touch_val = Touch_Scan_LH();

	    	    if(touch_val > TOUCH_THRESHOLD && touch_state == NOT_TOUCHED)
	           {
	    	    	touch_state = TOUCHED;
	           }
	    	}

	    	 if(touch_state == TOUCHED)
	    	 {
	    		 TouchTask(touch_val);
	    	 }
}

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
 * @brief   Header file for TSI module
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    03 October 2023
 *
 */


#ifndef MYTOUCH_H_    //header guards
#define MYTOUCH_H_

#define TOUCH_OFFSET 550  // value when no touch is made to sensor
#define TOUCH_DATA (TSI0->DATA & 0xFFFF)//macro for extracting the count from data register
#define TOUCH_THRESHOLD 100  //min value to sense touch
#define RIGHT_THRESHOLD 1000	// min value for right touch sensing
								//note:value updated as it was suggested by my code reviewer to
								//solve the issueif touch sensor was touched very lightly)

extern volatile uint32_t touch_val;   //declared touch_val as extern as it is defined in other file

//enum to check the state of touch
typedef enum {
    NOT_TOUCHED,
    TOUCHED,
    TASK_RUNNING
} TouchState;

extern volatile TouchState touch_state;   //declared touch_state as extern as it is defined in other file

/*Declaration of functions defined in mytouch.c file*/
void Touch_Init();
int Touch_Scan_LH(void);
void TouchTask(uint32_t touch_val);
void check_touch(TouchState touch_state, uint32_t touch_val);

#endif

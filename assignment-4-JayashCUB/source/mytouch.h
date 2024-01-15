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
 * @brief   header file for TSI module
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    14 October 2023
 *
 */

#ifndef MYTOUCH_H_    //Header guards to avoid repetition of including multiple headers
#define MYTOUCH_H_

#define TOUCH_OFFSET 550  // offset value to be subtracted
#define TOUCH_DATA (TSI0->DATA & 0xFFFF)//macro for extracting the count from data register
#define TOUCH_THRESHOLD 100  //min value to sense touch

#define emergency_light (0xFF0000)

void Touch_Init(void);
int Touch_Scan_LH(void);
void check_touch(uint32_t cur_st_RGB);

#endif

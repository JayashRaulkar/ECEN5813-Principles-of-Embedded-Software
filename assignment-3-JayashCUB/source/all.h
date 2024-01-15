/* Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    all.h
 * @brief   all.h header file has all required headers included below
 *          some other header files required and were present for board startup
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    03 October 2023
 *
 */

#ifndef ALL_H_    //Header guards to avoid repetetion of including multiple headers
#define ALL_H_


#include <stdio.h>

#include "peripherals.h"

#include "clock_config.h"



#include "MKL25Z4.h"

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "pin_mux.h"

#include "mylog.h"
#include "myled.h"
#include "mytouch.h"


#endif

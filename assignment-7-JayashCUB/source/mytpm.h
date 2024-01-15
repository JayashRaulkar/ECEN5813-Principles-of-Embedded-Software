/*****************************************************************************
 * Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users
 * are permitted to modify this and use it to learn about the field of
 * embedded software. Jayash Arun Raulkar and the University of Colorado are not
 * liable for any misuse of this material.
 *****************************************************************************/

/**
 * @file    mytpm.h
 * @brief	header file for TPM init functions
 *
 * @author  Jayash Arun Raulkar
 * @date    29 November 2023
 *
 */

#ifndef _MYTPM_H_
#define _MYTPM_H_

#include <stdint.h>

#define CLOCK (48000000UL)
#define TPM_OVERFLOW (48000UL)
#define TPM_PERIOD 500


/* brief: Below is the intialization function of TPM timer
 *
 *  Parameters:
 *  period for the TPM0 timer
 *
 * Returns:
 *  none
 */
void timer_init_TMP0(uint32_t period);

/* brief: Below is the intialization function of TPM timer
 *
 *  Parameters:
 *  period for the TPM1 timer
 *
 * Returns:
 *  none
 */
void timer_init_TMP1();


#endif // _MYTPM_H_

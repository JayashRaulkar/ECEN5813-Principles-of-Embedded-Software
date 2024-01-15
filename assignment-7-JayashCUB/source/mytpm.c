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
 * @file    mytpm.c
 * @brief	This file has function defination for TPM initialisation
 *
 * @author  Jayash Arun Raulkar
 * @date    29 November 2023
 *
 */

#include "MKL25Z4.h"
#include "mytpm.h"


void timer_init_TMP0(uint32_t period)
{
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;    // Enable the TPM0 clock

    SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);     // Select MCGPLLCLK clock with fixed divide by two for TPM0

    TPM0->SC = 0;    // Disabling  TPM0 while configuring

    TPM0->MOD = TPM_MOD_MOD(period);    // Set MOD register value

    TPM0->SC = (TPM_SC_DMA_MASK | TPM_SC_PS(0));     // Set prescaler to divide clock by 2

    TPM0->SC |= TPM_SC_CMOD(1);    // Enable the TPM0 counter
}

void timer_init_TMP1() {
    // Enable clock to TPM1 module
    SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;

    // Set TPM1 clock source to the system clock and divide by 1
    SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK;

    // Disable TPM1 while configuring
    TPM1->SC = 0;

    // Set TPM1 modulo register to get desired frequency
    TPM1->MOD = (CLOCK/TPM_OVERFLOW)-1;

    // Set TPM1 prescaler to divide by 1
    TPM1->SC |= TPM_SC_PS(0);
	  TPM1->SC |= TPM_SC_CMOD(1);
}


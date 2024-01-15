/*******************************************************************************
 * Copyright (C) 2023 by <Student Name>
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. <Student Name> and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    main.c
 * @brief
 *
 *
 * @author  <Student Name>
 * @date    <Date>
 *
 */


#include "cbfifo.h"
#include "test_cbfifo.h"
#include "llfifo.h"
#include "test_llfifo.h"
#include <stdint.h>
#include <assert.h>
#include <stdio.h>


int main(int argc, char **argv)
{
	test_cbfifo();
	test_llfifo();
	return 0;
}

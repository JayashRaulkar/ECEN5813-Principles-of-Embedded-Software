/*******************************************************************************
 * Copyright (C) 2023 by Jayash Arun Raulkar
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Jayash Arun Raulkar and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    assignment1_f23.h
 * @brief
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    09/03/2023
 *
 */

#ifndef ASSIGNMENT1_F23_H
#define ASSIGNMENT1_F23_H

#include <stdint.h>     // for uint32_t and similar definitions
#include <stdlib.h>     // for size_t

// NOTE: FOR THIS ASSIGNMENT, YOU MAY NOT USE STANDARD C LIBRARY
//       FUNCTIONS, STRINGS FUNCTIONS, INCLUDING THE PRINTF FAMILY, IN YOUR
//       PRODUCTION CODE. HOWEVER, YOU MAY USE SUCH FUNCTIONS IN ANY OF THE
//       TEST CODE. USE THE MACRO DEBUG IN MAKEFILE TO SELECT BETWEEN PRODUCTION
//       VS TEST CODE.

unsigned int my_strlen(const char *s);
uint32_t binsubstr_to_uint(const char *str, int start_bit, size_t nbits);

char *asciistr_to_hexstr(const char *ascii_str, char *hex_str, size_t size);

uint32_t absolute_hamming(uint32_t b1,uint32_t b2);
uint32_t hamming_distance(uint32_t num, int byte1, int byte2);

typedef enum {
    CLEAR,    // Set the bits to 0
    SET,      // Set the bits to 1
    TOGGLE    // Change bit value 1 to 0 and vice versa
} operation_t;

uint32_t twiggle_some_bits(uint32_t num, int start_bit, int nbits, operation_t operation);

uint32_t grab_nbits(uint32_t num, int start_bit, int nbits);

int substring_alt(const char *str1, const char *str2);

#endif  /* ASSIGNMENT1_F23_H */

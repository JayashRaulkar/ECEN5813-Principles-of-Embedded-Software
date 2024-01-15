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
 * @file    fp_trig.c
 * @brief	This file the functions defined for calculating the triangle value and square value for x
 * 			also it has function to calculates the Sin values using taylor series.
 *
 * @author  Jayash Arun Raulkar
 * @date    29 November 2023
 *
 * @reference
 *
 * 	 1) Elecia White's MAKING EMBEDDED SYSTEMS which has explanation for taylor series implemetation of
 * 	 the sine function using only integer math.
 * 	 NOTE: My sin(x) function implemented CORRECTLY, using only integer operation and 5 term Taylor series
 * 	 but it DOESN'T meet the requirements stated about max error and sum-of-squares error
 */

#include <stdbool.h>
#include "fsl_debug_console.h"

#include "fp_trig.h"

//Below is the defines for multiplier and equivalent shift for calculation factorial of (3,5,7,9) for 5 term implementation
//I also tried to increase the multiplier to get more accurate result but I'm not getting it

//#define INVERSE_THREE_FACT_MULT 10923
//#define INVERSE_THREE_FACT_SHIFT 16
//#define INVERSE_THREE_FACT (INVERSE_THREE_FACT_MULT >> INVERSE_THREE_FACT_SHIFT)
#define INVERSE_THREE_FACT_MULT  2796203
#define INVERSE_THREE_FACT_SHIFT 24
#define INVERSE_THREE_FACT (INVERSE_THREE_FACT_MULT >> INVERSE_THREE_FACT_SHIFT)

//#define INVERSE_FIVE_FACT_MULT 546
//#define INVERSE_FIVE_FACT_SHIFT 16
//#define INVERSE_FIVE_FACT (INVERSE_FIVE_FACT_MULT >> INVERSE_FIVE_FACT_SHIFT)
#define INVERSE_FIVE_FACT_MULT 139810
#define INVERSE_FIVE_FACT_SHIFT 24
#define INVERSE_FIVE_FACT (INVERSE_FIVE_FACT_MULT >> INVERSE_FIVE_FACT_SHIFT)

//#define INVERSE_SEVEN_FACT_MULT 13
//#define INVERSE_SEVEN_FACT_SHIFT 16
//#define INVERSE_SEVEN_FACT (INVERSE_SEVEN_FACT_MULT >> INVERSE_SEVEN_FACT_SHIFT)
#define INVERSE_SEVEN_FACT_MULT 3328
#define INVERSE_SEVEN_FACT_SHIFT 24
#define INVERSE_SEVEN_FACT (INVERSE_SEVEN_FACT_MULT >> INVERSE_SEVEN_FACT_SHIFT)


#define INVERSE_NINE_FACT_MULT 46
#define INVERSE_NINE_FACT_SHIFT 24
#define INVERSE_NINE_FACT (INVERSE_NINE_FACT_MULT >> INVERSE_NINE_FACT_SHIFT)

#define TRIANGLE_SCALE_FACTOR 	(163UL) // scaling factor for Triangular wave

int32_t my_taylor_fp_sin(int32_t x)
{
    while (x < -PI) // when angle is less than 0, keep adding TWO_PI
    {
        x = x + TWO_PI;
    }

    while (x > PI)  // when angle is greater than TWO_PI, keep subtracting TWO_PI
    {
        x = x - TWO_PI;
    }

	if(x < -HALF_PI)
	{
		x = -x ;
		x = -(PI - x);
	}

	if(x > HALF_PI)
	{
		x = PI - x;
	}
	double y=x;

	y = y/TRIG_SCALE_FACTOR;

    double xSq = y * y;
    long double sinX = (y * (1 - (xSq * (INVERSE_THREE_FACT - (xSq * (INVERSE_FIVE_FACT - (xSq * (INVERSE_SEVEN_FACT - (xSq * (INVERSE_NINE_FACT)))))))))) * TRIG_SCALE_FACTOR;
    int32_t res = (sinX * (41718 >> 16));
    return res;
}

int32_t fp_triangle(int32_t x)
{
    int sign = 1; // set initial sign as positive

    while (x < -PI) //when angle less than -PI keep adding two_PI
    {
        x = x + TWO_PI;
    }

    while (x > PI)  //when angle greater than PI keep subtracting two_PI
    {
        x = x - TWO_PI;
    }

    if (x < 0) { // if angle less than zero
        x = -x; // modulus of value
        sign = -1; // set sign negative
    }

    if (x > HALF_PI) { // if angle greater than HALF_PI subtract it from PI
        x = PI - x;
    }

    int32_t result = x * TRIANGLE_SCALE_FACTOR; // scale the angle
    result >>= 8; // for dividing by 256
    //Explanation of the above: For HALF_PI we have 3200 and adding 2037(TRIG_SCALE_FACTOR) to it will give value more
    // than 4097 (our 12 bit DAC limit), so we are scaling 3200 down,down to 2037 .
    //now for 3200 scaling factor is 2037. thus for 2037 it will be 1297
    // thus multiplier becoming 1297/ 2037 = 0.639(~163/256) for which multiplier is kept 163 and equivalent shift of 8 (256)
    return sign * result;
}


int32_t fp_square(int32_t x)
{
	int sign = 1; // set initial sign as positive

    while (x < 0) //when angle less than 0 keep adding two_PI
    {
        x =x + TWO_PI;
    }

    while (x > TWO_PI)  //when angle greater than TWO_PI keep subtracting two_PI
    {
        x =x - TWO_PI;
    }

    if (x < PI) { // if angle less than PI
        x = -x; // modulus of value
        sign = -1; // set sign negative
    }

    int32_t result =  TRIG_SCALE_FACTOR; //for sq wave directly use scale factor

    return sign * result;
}

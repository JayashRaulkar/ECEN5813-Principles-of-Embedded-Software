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
 * @file    assignment1_f23.c
 * @brief
 *
 *
 * @author  Jayash Arun Raulkar
 * @date    09/04/2023
 *
 */
#include "assignment1_f23.h"
#include <stdio.h>

#define ERROR       0xFFFFFFFFU     // for any errors

//Below my_strlen function code snippet from- https://aticleworld.com/strlen-function-in-c-cpp/
unsigned int my_strlen(const char *s)
{
    unsigned int count = 0;
    while(*s!='\0')
    {
        count++;
        s++;
    }
    return count;
}
// code snippet end

/**
 * @brief      { This fumction extracts a substring from the input string.
                With start_bit and nbits we can get the exact position of the substring }
 *
 * @param[in]  str        The string
 * @param[in]  start_bit  The start bit
 * @param[in]  nbits      The nbits
 *
 * @return     {  we assigned a uint32_t variable called output in which we store the
                value to return if all conditions are valid else we return the macro ERROR }
 */
uint32_t binsubstr_to_uint(const char *str, int start_bit, size_t nbits)
{
    if(str==NULL || nbits < 1 || nbits > 32 || start_bit+nbits > my_strlen(str) )          //checks if parameters are invalid
    {
        return ERROR;
    }
    else
    {
        uint32_t output = 0x00;
        for(int i=(start_bit+nbits-1);i>=start_bit;i--)         //loop to start from MSB of string to LSB
        {
            output = output << 1;           //left shifts after taking each bit
            if(str[i]=='1')
            {
                output = output | 0x01;         //if bit is 1 then OR with 0x01
            }
            else if (str[i]=='0')
            {
                output = output | 0x00;         //if bit is 0 then OR with 0x00
            }
            else
            {
                output = ERROR;
            }
        }
    return output;
    }

}

uint32_t test_binsubstr_to_uint()
{
    printf("output is: %d\n",binsubstr_to_uint(NULL,0, 5));
    printf("output is: %d\n",binsubstr_to_uint("110011",0, 2));
    printf("output is: %d\n",binsubstr_to_uint("11011",1, 2));
    printf("output is: %d\n",binsubstr_to_uint("10101",2, 1));
    printf("output is: %d\n",binsubstr_to_uint("1101010100011",5, 3));
    printf("output is: %d\n",binsubstr_to_uint("11011",1, 2));
    printf("output is: %d\n",binsubstr_to_uint("10101011010101",32, 1));
    printf("output is: %d\n",binsubstr_to_uint("110011",0, 2));
    printf("output is: %d\n",binsubstr_to_uint("11011",1, 2));
    printf("output is: %d\n",binsubstr_to_uint("101011010101",25, 1));
    printf("bin to uint function is done\n\n\n");
    return 0;
}

/**
 * @brief      { function_description }
 *
 * @param[in]  ascii_str  The ascii string
 * @param      hex_str    The hexadecimal string
 * @param[in]  size       The size
 *
 * @return     { description_of_the_return_value }
 */
char *asciistr_to_hexstr(const char *ascii_str, char *hex_str, size_t size)
{
    return NULL;
}

/**
 * @brief      { This function will compare the 2 bytes by xor'ing and counting the number of 1's }
 *
 * @param[in]  num    The number
 * @param[in]  byte1  The byte 1
 * @param[in]  byte2  The byte 2
 *
 * @return     { the number of 1's will be stored in a variable count and it will will be returned }
 */
  uint32_t absolute_hamming(uint32_t b1,uint32_t b2)
{
    uint32_t xor_op = b1 ^ b2 ;         //we will XOR because if bit is different we get 1
    uint32_t count=0;           //to store the hamming distance that is the number of 1's in xor_op
    for(int i=0;i<8;i++)
    {
        uint32_t var = xor_op & 0x01;           //check bit by bit for 1 (8times because 8 bits)

        if (var == 0x01)
        {
            count++;            //if 1 increase count
        }
        xor_op = xor_op >>1;            //right shift by 1 to get all bits

    }

    return count;
}
/**
 * @brief      { This function will strip the Four bytes from the 32 bit parameter num
                and will store them in four different variable b0 to b3 and further into an array arr_of_bytes}
 *
 * @param[in]  num    The number
 * @param[in]  byte1  The byte 1
 * @param[in]  byte2  The byte 2
 *
 * @return     { the return will call another function called absolute_hamming which will take the
                elements of arr_of_bytes array that are meant to be comapred}
 */
uint32_t hamming_distance(uint32_t num, int byte1, int byte2)
{
    if(byte1<0 || byte1>3 || byte2<0 || byte2>3)            //check if byte1/2 value is between 0 and 3
    {
        return ERROR;
    }
    else
    {
        uint32_t arr_of_bytes[4];
        for(int i=0;i<4;i++)
        {
            arr_of_bytes[i] = num & 0xff;           //stores the bytes one by one arr_of_bytes
            num = num>>8;           //right by 1 byte= 8 bits
        }

        return absolute_hamming(arr_of_bytes[byte1],arr_of_bytes[byte2]);
    }
}

uint32_t test_hamming_distance()
{
    printf("ham dis is: %d\n",hamming_distance(0x12, 0, 0));
    printf("ham dis is: %d\n",hamming_distance(0x12, -5, 1));
    printf("ham dis is: %d\n",hamming_distance(0x12000012, 0, 3));
    printf("ham dis is: %d\n",hamming_distance(145, 0, 3));
    printf("ham dis is: %d\n",hamming_distance(0x12000012, 0, 3));
    printf("ham dis is: %d\n",hamming_distance(0xffceceff, 0, 3));
    printf("ham dis function is done\n\n\n");
    return 0;
}

/**
 * @brief      { This function performs operation (either SET/TOGGLE/CLEAR) on specific bits of input num
                according to the start_bit and nbits. The operation is decided according to enum operation_t }
 *
 * @param[in]  num        The number
 * @param[in]  start_bit  The start bit
 * @param[in]  nbits      The nbits
 * @param[in]  operation  The operation
 *
 * @return     { the return value will be num on which operation is performed }
 */
uint32_t twiggle_some_bits(uint32_t num, int start_bit, int nbits, operation_t operation)
{
    if(start_bit+nbits>32 || start_bit<0 || nbits<0)            //check if start_bit and nbits is valid
    {
        return ERROR;
    }
    else
    {
       for(int i=start_bit;i<start_bit+nbits;i++)
    {
        if(operation == SET)
        {
            num = num | (0x01 << i);            //if set OR with 1 left shifted by 1 for making that specific bit 1
        }
        else if(operation == TOGGLE)
        {
            num = num ^ (0x01 << i);            //if toogle XOR with 1 left shifted by 1 for making that specific bit toggle
        }
        else if (operation == CLEAR)
        {
            num = num & ~((0x01) << i);         //if clear and with negation of 1 left shifted by 1 (that is and with 0) for making that specific bit 0
        }

    }
    return num;
    }
}

uint32_t test_twiggle_some_bits()
{
    printf("twiggle output is: %d \n",twiggle_some_bits(0,0,4,SET));
    printf("twiggle output is: %d \n",twiggle_some_bits(0,2,3,TOGGLE));
    printf("twiggle output is: %d \n",twiggle_some_bits(3,1,1,CLEAR));
    printf("twiggle output is: %d \n",twiggle_some_bits(3,25,8,CLEAR));
    printf("twiggle output is: %d \n",twiggle_some_bits(3,25,-7,SET));
    printf("twiggle output is: %d \n",twiggle_some_bits(0x34,0,4,SET));
    printf("twiggle output is: %d \n",twiggle_some_bits(0xc0,2,3,TOGGLE));
    printf("twiggle output is: %d \n",twiggle_some_bits(0xff,1,1,CLEAR));
    printf("twiggle function is done\n\n\n");
    return 0;
}

/**
 * @brief      { This function exacts specific bits from num denoted by start bit and nbits }
 *
 * @param[in]  num        The number
 * @param[in]  start_bit  The start bit
 * @param[in]  nbits      The nbits
 *
 * @return     { the num is returned by after the shift operations are performed }
 */
uint32_t grab_nbits(uint32_t num, int start_bit, int nbits)
{
    if(start_bit+nbits>32 || start_bit<0 || nbits<0)            //check if start_bit and nbits is valid
    {
        return ERROR;
    }
    else
    {
        num = num << (32 - (start_bit+nbits));          //left shit to remove the MSB side bits
        num = num >> (32 - (start_bit+nbits) + start_bit);          //right shift to get the bits from starting location
        return num;
    }
}

uint32_t test_grab_nbits()
{
    printf("output is: %d \n",grab_nbits(0b111011, 2, 2));
    printf("output is: %d \n",grab_nbits(0b111011, -3, 3));
    printf("output is: %d \n",grab_nbits(0xabc1, 3, 3));
    printf("output is: %d \n",grab_nbits(0b1110100111, 25, 8));
    printf("output is: %d \n",grab_nbits(0x5435, 2, 2));
    printf("output is: %d \n",grab_nbits(0b111011, -3, 3));
    printf("output is: %d \n",grab_nbits(0b1101111000, 3, 3));
    printf("output is: %d \n",grab_nbits(0b11010100111, 1, 18));
    printf("grab function is done\n\n\n");
    return 0;
}

/**
 * @brief      {The function below compares str2 with str1 while ignoring the spaces and the case sensitive nature}
 *
 * @param[in]  str1       The string 1 from which str 2 is to be compared with
 * @param[in]  str2       The string 2 that is compared
 *
 * @return     { if a match the return value is the first index of the of str1 where match occured
                else it will return -1  }
 */
int substring_alt(const char *str1, const char *str2)
{
    int index=-1;           //used to store return value, initially assigned to -1(no match value)
    int flag=0;
    int j =0;
    
        while(str2[j]==0x20)            //ignore spaces in str 2 and increment location 
        {
            j++;
        }
        for(int i=0; str1[1]!='\0';i++)
        {
            while(str1[i]==0x20)            //ignore spaces in str 1 and increment location
            {
                i++;
            }
            while(str2[j]==0x20)            //ignore spaces in str 2 and increment location
            {
                j++;
            } 
            if (str2[j]==str1[i]  || str2[j] - str1[i] == 0x20 || str2[j] - str1[i] == -0x20)           //if match
            {
                if(!flag)
                {
                    index=i;            //store 1st match address location
                    flag =1;
                }

                j++;
                while(str2[j]==0x20)            //ignore spaces in str 2 and increment location
                {
                    j++;
                }
                if(str2[j]=='\0')           //check if str 2 has ended
                {
                    return index;
                }
            }
            else
            {
                flag =0;
                int index=-1;
                if(str2[j]=='\0')           //check if str 2 has ended
                {
                    return index;
                }
                if(str1[i]=='\0')           //check if str 2 has ended
                {
                    return index;
                }
            }
        }
        return index;

}

uint32_t test_substring_alt()
{
    printf("Index is: %d \n",substring_alt("  JaY a Sh"," y A s "));
    printf("Index is: %d \n",substring_alt("Cat is  ou  t of the bag","O u T"));
    printf("Index is: %d \n",substring_alt("President’s men","D o G"));
    printf("Index is: %d \n",substring_alt("0B0033","0 0"));
    printf("Index is: %d \n",substring_alt("embeddeddedd"," DeD "));
    printf("Index is: %d \n",substring_alt("ApAppleleGlele","le g le"));
    printf("Index is: %d \n",substring_alt("chocolate milk","chocolate milk is love"));
    printf("Index is: %d \n",substring_alt("0c0903io"," 0  33"));
    printf("Index is: %d \n",substring_alt("CU Boulder","b O    U"));
    printf("substring function is done\n\n\n");
    return 0;
}



/**
 * @brief      main
 *
 * @param[in]  argc  The count of arguments
 * @param      argv  The arguments array
 *
 * @return     always 0
 */
int32_t main(int32_t argc, char **argv)
{
    test_binsubstr_to_uint();
    test_hamming_distance();
    test_twiggle_some_bits();
    test_grab_nbits();
    test_substring_alt();
    return 0;
}

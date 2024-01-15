
/*******************************************************************************
 * Copyright (C) 2023 by <Jayash Arun Raulkar>
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. <Student Name> and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    cbfifo.c
 * @brief
 *
 *
 * @author  <Jayash Arun Raulkar>
 * @date    <September 19 2023>
 *
 * Credits:
 * TA (for reviewing concept, guidance to write test functions)
 * Classmate (for helping in debugging)
 */


#include "cbfifo.h"
#include <stdint.h>     //because using uint8_t for typecasting
#include <stdlib.h>     //because using size_t
//#include<stdio.h>

#define	max_capacity 127                //defining max size of circular buffer fifo       

unsigned char cbfifo[max_capacity];     //creating circular buffer array of size max_capacity(127)
int write = 0;                          //used to check position at which we have to enqueue 
int read = 0;                           //used to check position at which we have to dequeue    
size_t length=0;                        //used to see the current length of circular buffer fifo



/*The function cb_enqueue is used to insert the data into our circular buffer fifo from buf which is a pointer to the data to be enqueued.
buf is one of the paramter of the function and the secound parameter is nbyte which tell us how many bytes from the data to be enqueued*/

size_t cbfifo_enqueue(void *buf, size_t nbyte)  //function defination starts
{
    if(buf == NULL)                             //to check if buf itself is empty
    {
        return (size_t) -1;                     //if buf NULL return error
    }
    uint8_t *data=(uint8_t*)buf;                //becasue buf is void pointer, typecaste it to uint8_t 
                                                //as we need data byte by byte and point it by data pointer
    
    if(nbyte == 0)                              //if number of bytes to enqueue is 0 return 0
    {
        return 0;
    }

    if(length>=max_capacity)                    //if length has reached the max capacity we cannot enque more n thus return 0
    {
        return 0;
    }
    else
    {
    if ((max_capacity-length) > nbyte)          //checks if available space is greater than the byte to be enqueued
        {
            nbyte = nbyte;                      //if so we can enqueue nbyte
        }
        else
        {
            nbyte = (max_capacity-length);      //if not we have to enqueue bytes for which space is available
        }
    }
    for(int i=0; i<nbyte ; i++)                 //loop which will run nbyte times to insert nbyte
    {
        cbfifo[write]= *data;                   //insert data from data pointer  on to the write posistion Circular buffer array
        write++;                                //increment write position for next enqueue
        length++;                               //increment length
        if(write==(max_capacity))               //if write posistion reaches end of circular array point it back to 0 position of array
        {
            write=0;
        }
        data++;                                 //increment data pointer, which will increment by 1 byte for next byte to be enqueued
    }
    
    return nbyte;                               //return the number of bytes enqueued
}



/*the function cbfifo_dequeue is used to dequeue data from our buffer and copy the data into the buf pointer, which is one of 
the parameter of the function. the secound parameter is nbyte which tell us the number of bytes to be dequeued from the buffer*/

size_t cbfifo_dequeue(void *buf, size_t nbyte)  //function defination starts
{
    uint8_t *data= (uint8_t*)buf;               //becasue buf is void pointer, typecaste it to uint8_t 
                                                //as we need data byte by byte and point it by data pointer

    if(cbfifo == NULL || nbyte==0)              //checks if cbfifo is empty or if the bytes to dequeue is 0
    {
        return 0;                               //if so return 0
    }
    else
    {
        if(length==0)                           //check if length of circular array is 0
        {
            return 0;                           //if so return 0
        }
        else
        {
            if(nbyte <=length)                  //if the number of byte to dequeue is less the elements in circular array
            {
                nbyte=nbyte;                    //we will dequeue nbytes
            }
            else
            {
                nbyte=length;                   //we will dequeue all elements Circular aaray
            }
        }
        for(int i = 0; i<nbyte ; i++)           //loop which will run nbytes to dequque nbytes
        {
            *data=cbfifo[read];                 //we will put the dequeued data from read position fo circular buffer into dta pointer
            read++;                             //increment read pointer
            length--;                           //decrement lenght value
            if(read == (max_capacity))          //if read position reaches end of circular array point it back to 0 position of array
            {
                read = 0; 
            }
            data++;                             //increment data pointer and store next dequeued element
        }
    }
    return nbyte;                               //return the number of bytes dequeued   
}

/*this function returns the current length i.e. the number of bytes the circular buffer is holding */
size_t cbfifo_length()
{
    return length;
}

/*this function returns the capacity i.e. the size in bytes of the circular buffer */
size_t cbfifo_capacity()
{
    return max_capacity;
}

/*this function resets the circular buffer by setting the write,read and length all to zero, thus next time all old data will be overwritten */
void   cbfifo_reset()
{
    write=0;
    read=0;
    length=0;
}

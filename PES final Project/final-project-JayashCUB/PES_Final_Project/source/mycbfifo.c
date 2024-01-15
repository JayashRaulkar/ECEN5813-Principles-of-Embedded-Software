/*****************************************************************************
​ *​ ​Copyright​ ​(C)​ 2023 ​by​ Jayash Arun Raulkar
​ *
​ *​ ​Redistribution,​ ​modification​ ​or​ ​use​ ​of​ ​this​ ​software​ ​in​ ​source​ ​or​ ​binary
​ *​ ​forms​ ​is​ ​permitted​ ​as​ ​long​ ​as​ ​the​ ​files​ ​maintain​ ​this​ ​copyright.​ ​Users​ ​are
​ *​ ​permitted​ ​to​ ​modify​ ​this​ ​and​ ​use​ ​it​ ​to​ ​learn​ ​about​ ​the​ ​field​ ​of​ ​embedded
​ *​ ​software.​ Jayash Arun Raulkar ​and​ ​the​ ​University​ ​of​ ​Colorado​ ​are​ ​not​ ​liable​ ​for
​ *​ ​any​ ​misuse​ ​of​ ​this​ ​material.
​ *
*****************************************************************************/

/**
 * @file     mycbfifo.c
 * @brief    contains function definitions of circular buffer used for UART
 *
 * @author   Jayash Arun Raulkar
 * @date     10 December 2023
 *
 */
#include <mycbfifo.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

//Function to initialise Circular buffer
void cbfifo_init(CircularBuffer* cb) {
    cb->size = MAX_CAPACITY;
    cb->write = 0;
    cb->read = 0;
    cb->length = 0;
}


// Enqueue data onto the FIFO
// In assg 2 enqueue function the params were different, here i used
//the cbfifo in question as parameter, thus removed some checks for "nbytes"
//also there is not pointer to data now thus removed the typecasting
//could've used wrapped substraction but max size was 127 wiz not power of 2
uint8_t cbfifo_enqueue(CircularBuffer* cb, uint8_t data)
{
	if(cb==NULL){
		return 0;
	}
    if (cbfifo_is_full(cb)) {
        return 0;  // Buffer is full, unable to enqueue
    }

    cb->buffer[cb->write] = data;

    if (cb->write + 1 == cb->size) {
        cb->write = 0;
    }
    else {
        cb->write++;
    }

    cb->length++;
    return 1;  // Successfull enqueue
}


// Dequeue data from the FIFO
// In assg 2 dequeue functin the params were different, here I used
//the cbfifo in question as parameter, thus removed some checks for "nbytes"
//could've used wrapped substraction but max size was 127 wiz not power of 2
uint8_t cbfifo_dequeue(CircularBuffer* cb)
{
	if(cb==NULL){
		return 0;
	}
    if (cbfifo_is_empty(cb)) {
        return 0;  // Buffer is empty, unable to dequeue
    }

    uint8_t data = cb->buffer[cb->read];

    if (cb->read + 1 == cb->size) {
        cb->read = 0;
    }
    else {
        cb->read++;
    }

    cb->length--;
    return data;  // Return the dequeued data
}

// Get the current length of the FIFO
// same as assg 2, return the current length, i just added the NULL check
uint8_t cbfifo_length(const CircularBuffer* cb)
{
    if (cb == NULL) {
        return 0;
    }
    return cb->length;
}

// Get the capacity of the FIFO
// same as assg 2, return the max capacity, i just added the NULL check
uint8_t cbfifo_capacity(const CircularBuffer* cb)
{
    if (cb == NULL) {
        return 0;
    }
    return MAX_CAPACITY;
}

// Check if the FIFO is full
//This function was not prsent in Assg 2
uint8_t cbfifo_is_full(const CircularBuffer* cb)
{
    if (cb->length == cb->size) {
        return 1;
    }
    else {
        return 0;
    }
}

// Check if the FIFO is empty
//This function was not prsent in Assg 2
uint8_t cbfifo_is_empty(const CircularBuffer* cb)
{
    if (cb->length == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

// Reset the FIFO
// same as assg 2
void cbfifo_reset(CircularBuffer* cb)
{
    cb->write = 0;
    cb->read = 0;
    cb->length = 0;
}

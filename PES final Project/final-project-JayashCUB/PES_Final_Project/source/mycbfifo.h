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
 * @file    mycbfifo.h
 * @brief   contains function declarations of LED initialization and led control
 *
 * @author  Jayash Arun Raulkar
 * @date    10 December 2023
 *
 */
#ifndef _MYCBFIFO_H_
#define _MYCBFIFO_H_

#include <stdlib.h>  // for size_t
#include <stdint.h>
#include <stddef.h>  // for size_t

// Define the maximum capacity for the circular buffer
#define MAX_CAPACITY 127

typedef struct {
    uint8_t buffer[MAX_CAPACITY];
    uint8_t size;
    uint8_t write;  // Write position
    uint8_t read;  // Read position
    uint8_t length;
} CircularBuffer;


/**
 * @brief- Initialize the circular buffer
 *
 * param- the Circular buffer in question
 *
 * return- None.
 */
void cbfifo_init(CircularBuffer* cb);



/**
 * @brief- Enqueue data onto the FIFO
 *
 * param- the Circular buffer in question and the data to be enqueued
 *
 * return- 1 on successful enqueue else 0.
 */
uint8_t cbfifo_enqueue(CircularBuffer* cb, uint8_t data);



/**
 * @brief- Dequeue data from the FIFO
 *
 * param- the Circular buffer we want to dequeue
 *
 * return- the deququed elements on successful dequeue else zero.
 */
uint8_t cbfifo_dequeue(CircularBuffer* cb);



/**
 * @brief- Get the current length of the FIFO
 *
 * param- the Circular buffer in question
 *
 * return- current length of circular buffer.
 */
uint8_t cbfifo_length(const CircularBuffer* cb);



/**
 * @brief- Get the capacity of the FIFO
 *
 * param- the Circular buffer in question
 *
 * return- the maximum capacity
 */
uint8_t cbfifo_capacity(const CircularBuffer* cb);



/**
 * @brief- Check if the FIFO is full
 *
 * param- the Circular buffer in question
 *
 * return- 1 if full else 0.
 */
uint8_t cbfifo_is_full(const CircularBuffer* cb);



/**
 * @brief- Check if the FIFO is empty
 *
 * param- the Circular buffer in question
 *
 * return- 1 if empty else 0
 */
uint8_t cbfifo_is_empty(const CircularBuffer* cb);



/**
 * @brief- Reset the FIFO
 *
 * param- the Circular buffer in question
 *
 * return- None.
 */
void cbfifo_reset(CircularBuffer* cb);


#endif // _MYCBFIFO_H_

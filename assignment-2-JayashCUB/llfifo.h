/*
 * llfifo.h - a dynamically-growing FIFO
 * 
 * Author: Howdy Pierce/Lalit Pandit
 * 
 * DO NOT EDIT THIS FILE: You should check this file into your repo
 * exactly as it was delivered to you.
 */

#ifndef _LLFIFO_H_
#define _LLFIFO_H_

/* 
 * The llfifo's main data structure. 
 *
 * Defined here as an incomplete type, in order to hide the
 * implementation from the user. You will need to define this struct
 * in your .c file.
 */
typedef struct llfifo_s llfifo_t;


/*
 * Creates and initializes the FIFO
 *
 * Parameters:
 *   capacity  the initial size of the fifo, in number of elements. 
 *             Valid values are in the range of 0 to max_capacity(inclusive of both).
 *   max_capacity maximum capacity of the FIFO. Once the capacity equals
 *                max capacity, any further attempt to enqueue will discard
 *                the oldest element and reuse that node for storing the
 *                newly enqueued element. max_capacity > 0.
 * 
 * Returns: A pointer to a newly-created llfifo_t instance, or NULL in
 *   case of an error.
 */
llfifo_t *llfifo_create(int capacity, int max_capacity);


/*
 * Adds("enqueues") an element onto the FIFO, growing the FIFO by adding
 * additional elements, if necessary upto max_capacity. Thereafter,
 * it will recycle the oldest node tp enqueue the recent data.
 *
 * Parameters:
 *   fifo    The fifo in question
 *   element The element to enqueue, which cannot be NULL
 * 
 * Returns:
 *   The new length of the FIFO on success, -1 on failure. It is an error to attempt 
 *   to enqueue the NULL pointer.
 */
int llfifo_enqueue(llfifo_t *fifo, void *element);


/*
 * Removes ("dequeues") an element from the FIFO, and returns it
 *
 * Parameters:
 *   fifo  The fifo in question
 * 
 * Returns:
 *   The dequeued element, or NULL if the FIFO was empty
 */
void *llfifo_dequeue(llfifo_t *fifo);


/*
 * Returns the number of elements currently on the FIFO. 
 *
 * Parameters:
 *   fifo  The fifo in question
 * 
 * Returns:
 *   The number of elements currently on the FIFO.
 */
int llfifo_length(llfifo_t *fifo);


/*
 * Returns the FIFO's current capacity
 *
 * Parameters:
 *   fifo  The fifo in question
 * 
 * Returns:
 *   The current capacity, in number of elements, for the FIFO.
 */
int llfifo_capacity(llfifo_t *fifo);

/*
 * Returns the FIFO's max capacity
 *
 * Parameters:
 *   fifo  The fifo in question
 *
 * Returns:
 *   The max capacity, in number of elements, for the FIFO.
 */
int llfifo_max_capacity(llfifo_t *fifo);

/*
 * Teardown function: Frees all dynamically allocated
 * memory. After calling this function, the fifo should not be used
 * again!
 *
 * Parameters:
 *   fifo  The fifo in question
 * 
 * Returns: none
 */
void llfifo_destroy(llfifo_t *fifo);

#endif // _LLFIFO_H_
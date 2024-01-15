#include "llfifo.h"
#include "test_llfifo.h"
#include <stdint.h>
#include <assert.h>
#include <stdio.h>


void test_llfifo()
{
    char ele[10] = "abcdefghij";
    llfifo_t *llfifo=llfifo_create(5,10);

    assert(llfifo_enqueue(llfifo,&ele[1]) == 1);    //enqueue 1st time
    assert(llfifo_enqueue(llfifo,&ele[2]) == 2);
    assert(llfifo_enqueue(llfifo,&ele[3]) == 3);
    assert(llfifo_enqueue(llfifo,&ele[4]) == 4);
    assert(llfifo_enqueue(llfifo,&ele[5]) == 5);    //enqueue upto capacity
    assert(llfifo_length(llfifo) == 5);             //check length
    assert(llfifo_enqueue(llfifo,&ele[6]) == 6);
    assert(llfifo_enqueue(llfifo,&ele[7]) == 7);
    assert(llfifo_enqueue(llfifo,&ele[8]) == 8);
    assert(llfifo_enqueue(llfifo,&ele[9]) == 9);
    assert(llfifo_enqueue(llfifo,&ele[10]) == 10);  //enquue upto max capacity
    assert(llfifo_length(llfifo) == 10);            //check length again

    llfifo_dequeue(llfifo);
    assert(llfifo_length(llfifo) == 9);
    llfifo_dequeue(llfifo);
    llfifo_dequeue(llfifo);
    llfifo_dequeue(llfifo);
    llfifo_dequeue(llfifo);                         //dequeue 5 times
    assert(llfifo_length(llfifo) == 5);             //check length

    assert(llfifo_enqueue(NULL,&ele[10]) == -1);    //check if fifo is null
    assert(llfifo_dequeue(NULL) == NULL);           //check if null is dequeued



    printf(" all condition passed for llfifo \n");

}

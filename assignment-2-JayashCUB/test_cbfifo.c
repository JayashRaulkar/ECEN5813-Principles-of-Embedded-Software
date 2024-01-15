#include "cbfifo.h"
#include "test_cbfifo.h"
#include <stdint.h>
#include <assert.h>
#include <stdio.h>


void test_cbfifo()
{

    char*src = "abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefg";
    uint8_t des[127];

    // -----Positive/Normal Test Cases (Happy Path Testing):-----

    //enqueuing 50 elements and then dequeuing
    assert(cbfifo_enqueue(src, 50) == 50);
    assert(cbfifo_dequeue(des, 50) == 50);
    assert(cbfifo_length()==0);

    //enqueuing 100 elements and then dequeuing 50 and check length
    assert(cbfifo_enqueue(src, 100) == 100);
    assert(cbfifo_dequeue(des, 50) == 50);
    assert(cbfifo_length()==50);
    assert(cbfifo_dequeue(des, 50) == 50);
    assert(cbfifo_length()==0);

       // -----Negative Test Cases (Happy Path Testing):-----

    assert(cbfifo_enqueue(src, 0) == 0);
    assert(cbfifo_length()==0);
    assert(cbfifo_dequeue(des, 0) == 0);
    assert(cbfifo_length()==0);


    //-----Boundary/Edge Test Cases:-----
    //enqueuing 127 elements and dequeuing 127
    assert(cbfifo_enqueue(src, 127) == 127);
    assert(cbfifo_dequeue(des, 7) == 7);
    assert(cbfifo_length()==120);
    assert(cbfifo_dequeue(des, 120) == 120);
    assert(cbfifo_length()==0);


    //dequeuing more elements then required
    assert(cbfifo_enqueue(src, 127) == 127);
    assert(cbfifo_dequeue(des, 130) == 127);
    assert(cbfifo_length() == 0);

    printf(" all condition passed for cbfifo \n");


}

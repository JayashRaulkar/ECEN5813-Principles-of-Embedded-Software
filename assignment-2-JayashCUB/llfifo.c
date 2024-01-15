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
 * @file    llfifo.c
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
#include "llfifo.h"
#include <stdlib.h>         //for using malloc

/*below is the struct created for nodes of the linked list*/
struct node{

    void* data;                                //for the data element of the node
    struct node *next;                         //for pointing to the next node
};

typedef struct node node_t;                    //typedef as node_t


/*below struct is to hold information about the llfifo itself*/
struct llfifo_s{

    node_t *head;                               //the head node of the linked list fifo                                                           
    node_t *tail;                               //the tail node of the linked list fifo
    int capacity;                               //the capacity fo the fifo
    int max_capacity;                           //the max_capacity of the fifo
    int length;                                 //the current length i.e. nodes of llfifo which has element

};
//typedef struct llfifo_s llfifo_t;


/*this function creates the llfifo of llfif0_t struct type and initialises its members, the 
parameters capacity and max_capacity is used to set the respective member of the structure */

llfifo_t *llfifo_create(int capacity, int max_capacity)                 //function defination starts here
{
    if((capacity>=0 && max_capacity>0 && capacity<max_capacity))        //first check if parmeters is valid
    {
        llfifo_t *fifo= (llfifo_t *)malloc(sizeof(llfifo_t));           //assigns memory of struct llfifo_t size to llfifo_t pointer fifo

        fifo->capacity=capacity;                                        //set capacity member
        fifo->max_capacity=max_capacity;                                //set max_apacity member
        fifo->length=0;                                                 //set length member as 0
        fifo->head=NULL;                                                //assign head member to null
        fifo->tail=NULL;                                                //assign tail member to null
        for (int i=1;i<=capacity;i++)                                   //loop running capacity times to crete capacity number of nodes
        {
            llfifo_enqueue(fifo,NULL);                                  //calling enqueue function to create node upto capacity and give NULL for data
        }

        return fifo;                                                    //return fifo pointer
    }
    return NULL;                                                        //return NULL if error
}



/*this function is enqueues the element which is a parameter, in the llfifo
 another parameter is the pointer to the llfifo in which element is to be enqueued*/

int llfifo_enqueue(llfifo_t *fifo, void *element)                           //function defination starts
{
    if(fifo==NULL)                                                          //checks if fifo is NULL if so return -1
    {
        return -1;
    }
    if((fifo->length==0 && fifo->head==NULL) && fifo->max_capacity >0)      //checks if no node was created
    {
        node_t *new_node= (node_t *)malloc(sizeof(node_t));                 //(create new node)assigns memory of struct node_t size to node_t pointer new node
        new_node->data=element;                                             //put element in data of new node
        new_node->next=NULL;                                                //set next of new node i.e. address of next node as null
        fifo->head=new_node;                                                //make new node as head of llfifo
        fifo->tail=fifo->head;                                              //make head as tail
        if (element == NULL)
        {
            return -1;                                                      //if element to be enqueued is NULL return -1
        }
        fifo->length+=1;                                                    //increment length because node created
         
        return fifo->length;                                                //return the fifo length
    }
    if(fifo->length==0 && element == NULL)                                  //checks condition when creating queue
    {
        node_t *temp = fifo->head;                                          //create temp node and point it it head
        node_t *new_node= (node_t *)malloc(sizeof(node_t));                 //(create new node)assigns memory of struct node_t size to node_t pointer new node
        new_node->data=element;                                             //enter element in data member of new node
        new_node->next=NULL;                                                //set next of new node i.e. address of next node as null
        while(temp->next!=NULL)                                             //checks if next of head pointing to null
        {
                temp = temp->next;                                          //if not point it to next address
        }
        temp->next = new_node;                                              //put new node in temp
        return -1;                                                          //return -1
    }
    
    if(fifo->length < fifo->capacity && fifo->capacity<=fifo->max_capacity)     //checks condition for length less than cpapcity i.e. nodes available
    {
        if(fifo->length==0)                                             //if node present but no element
        {
            fifo->tail->data = element;                                 //add element to tail which is head also
            fifo->length+=1;                                            //increment length
        }
        else
        {
             if(fifo->tail->next != NULL)                               //check if next node of tail is not null i.e node is exixting already
            {
                 node_t *temp = fifo->tail->next;                       //point temp to the next node
                if (fifo->tail->next->next != NULL)                     //check if the node after the node to which tail points exits [tail-->node-->another node] 
                {
                    fifo->tail->next = fifo->tail->next->next;          //point tail to another node
                }
                else
                {
                    fifo->tail->next = NULL;                            //else point it to null
                }

                temp->data = element;                                   //enter element in data of temp
                temp->next =fifo->head;                                 //point next of temp to current head
                fifo->head=temp;                                        //make temp as head
                fifo->length += 1;                                      //increment length
            }
        }
        return fifo->length;                                            //return fifo length
    }

    if(fifo->length==fifo->capacity && fifo->capacity<fifo->max_capacity)       //checks if length has reached capacity
    {
        node_t *new_node= (node_t *)malloc(sizeof(node_t));                     //if si thern create new node
        new_node->data=element;                                                 //insert elemnet in data of new node
        new_node->next=fifo->head;                                              //point next of new node to head

        fifo->head=new_node;                                                    //make new node as head
        
        fifo->length += 1;                                                      //increment length                                 
        fifo->capacity += 1;                                                    //increment capacity too
        return fifo->length;                                                    //return fifo length
    }

    if(fifo->length == fifo->max_capacity)                                      //check if lenght has reached max caapcity i.e fifo full
    {
        llfifo_dequeue(fifo);                                                   //dequeue the oldest element
        llfifo_enqueue(fifo,element);                                           //enqueue the new element
        return fifo->length;                                                    //return fifo length
    }
    return -1;                                                                  //return -1 for error
}


/*this function dequeues the oldest element from our llfifo, and the parameter is pointer to that fifo which is to be dequeued*/

void *llfifo_dequeue(llfifo_t *fifo)
{
    if(fifo == NULL || fifo->head==NULL||fifo->head->data==NULL)        //check if fifo is null or head is null or data in first node is null
    {
        return NULL;                                                    //if so return null as nothing can be dequeued
    }
    
    node_t *ptr=fifo->head;                                             //point a ptr to head (used for tranversing the LinkedList)
    if(ptr->next == NULL || fifo->head == fifo->tail)                   //check for condition when only one node present
    {
      void *temp= fifo->head->data;                                     //store the data in a temp 
      fifo->head->data=NULL;                                            //make the data member null
      fifo->length-=1;                                                  //decremnet length
      return temp;                                                      //return the data dequeued
    }
    else
    {
        //fifo->tail->data=NULL;
        while((ptr->next)->data != NULL || (ptr->next) != NULL)         //to check we have reached the oldest element
        {
            if(ptr->next == fifo->tail)                                 //if reached the tail
            {
                
                void *temp= fifo->tail->data;                           //store the data in a temp
                fifo->tail->data=NULL;                                  //make the data member null
                fifo->tail = ptr;                                       //make the previous node as tail
                fifo->length -= 1;                                      //decremnet length
                return temp;                                            //return the data dequeued

            }
            else
            {
                ptr = ptr->next;                                        //keep pointing ptr to next node untill we reach tail
            }

        }
    }

    return NULL;                                                        //else return NULL
}


/*this function returns the number of elements currently on the fifo, and parameter is pointer pointing to the fifo */
int llfifo_length(llfifo_t *fifo)
{
    return fifo->length;
}

/*this function returns the current capacity of the fifo, and parameter is pointer pointing to the fifo */
int llfifo_capacity(llfifo_t *fifo)
{
    return fifo->capacity;
}

/*this function returns the max capacity of the fifo, and parameter is pointer pointing to the fifo */
int llfifo_max_capacity(llfifo_t *fifo)
{
    return fifo->max_capacity;
}

/*this function destroys the fifo as weel as the node of the fifo*/
void llfifo_destroy(llfifo_t *fifo)
{
    node_t *temp;                           //a temp node
    while(fifo->head != NULL)               //check if fifo head not null i.e fifo pexist
    {
        temp=fifo->head;                    //temp as head      
        fifo->head=fifo->head->next;        //point head to next node
        free(temp);                         //free temp (in loop all nodes will be freed)
    }
    free(fifo);                             //free fifo as well
}
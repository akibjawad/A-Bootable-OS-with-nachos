// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "variable.h"
#include "producer.h"
#include "consumer.h"
//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(void* which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times\n", *(int*)which, num);
        currentThread->Yield();
    }
}

//----------------------------------------------------------------------
// ThreadTest
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

Lock* buffLock=new Lock("BufferLock");
Condition* proLock=new Condition("ProducerLock");
Condition* consumeLock=new Condition("ConsumerLock");
buffer* buff=new buffer();

void
producerThread(void* which)
{
    /*
    int num;
    
    for (num = 0; num < 5; num++) {
    printf("*** thread %d looped %d times\n", *(int*)which, num);
    currentThread->Yield();
    } */
    producer *p=new producer(*(int*)which,buff);
    printf("*** producer %d started \n", *(int*)which);
    p->produce();   
}

void
consumerThread(void* which)
{
    /*
    int num;
    
    for (num = 0; num < 5; num++) {
    printf("*** thread %d looped %d times\n", *(int*)which, num);
    currentThread->Yield();
    }*/
    consumer *c=new consumer(*(int*)which,buff);
    printf("*** consumer %d started \n", *(int*)which);
    c->consume();    
}


void
ThreadTest()
{
    DEBUG('t', "Entering SimpleTest");
    for (int i = 0; i < 10; ++i)
    {
        int* j=new int(i+1);
        if(i>4)
        {
            Thread *c = new Thread("forked thread"+i);
            c->Fork(consumerThread,j);
        }
        else
        {
            Thread *p = new Thread("Producer thread"+i);
            p->Fork(producerThread, j);
        }
    }
    //Thread *t = new Thread("forked thread");
    //int* i=new int(1);
    //t->Fork(SimpleThread, i);
    //SimpleThread(i);
}


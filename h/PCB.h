/*
 * PC.h
 *
 *  Created on: Apr 8, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "Thread.h"
#include "Queue.h"
//class Thread;
class Queue;

 class PCB{
public:

	static ID Global_ID;
	ID id;

    Thread * myThread;
	 unsigned  sp,ss;
	unsigned* pcbStek;
	 static int vel;
	 static unsigned* st;

	static enum Stanje{NEW ,READY,BLOCKED,OVER};
	Stanje stanje;
	 Time  pcbtime;
	 Time time_count;
Time vreme_na_semaforu;
    StackSize pcb_stack_size;
   int povratna_vred;

    Queue* Qwait;
	PCB (Thread*t,StackSize size, Time time);

	void Stack_Create();
	~PCB();

};









#endif /* PCB_H_ */

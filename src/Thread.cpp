/*
 * Thread.cpp
 *
 *  Created on: Apr 9, 2020
 *      Author: OS1
 */
#include "Kernel.h"
#include "PCB.h"
#include "Thread.h"
#include "Schedule.h"
#include <dos.h>
#include <stdlib.h>

class Scheduler;
class Kernel;


ID Thread::getRunningId(){
	lock();

ID t=Kernel::running->id;

 unlock();
 return t;
}
ID Thread::getId(){
	lock();
	ID i= this->myPCB->id;
	unlock();
	return i;
}
Thread*Thread::getThreadById(ID id){
	lock();
    Thread*t= Kernel::red_niti->dohv_nit(id);
    unlock();
return t;
}


Thread::Thread(StackSize stackSize, Time timeSlice){
	lock();

	myPCB=new PCB(this,stackSize,timeSlice);
	Kernel::red_niti->put(this->myPCB);
	unlock();
}




Thread::~Thread(){
lock();
	waitToComplete();
	/*syncPrintf("Obrisana nit %d\n", getId());
	for (Elem *tek = Kernel::red_niti->prvi; tek; tek=tek->sled) {
		syncPrintf("%d %d | ", tek->pcb->id, tek->pcb->stanje);
	}
	syncPrintf("\n");*/
	//Kernel::red_niti->izbaci_nit(this->myPCB);

delete myPCB;

unlock();
}

void Thread::start(){
	lock();
	myPCB->stanje=PCB::READY;
	myPCB->Stack_Create();
	Scheduler::put(myPCB);

unlock();
}
void Thread::waitToComplete(){
	lock();
	if(myPCB->stanje== PCB::NEW || myPCB->stanje == PCB::OVER || myPCB==Kernel::running || this==Kernel::idle || this==Kernel::begin){
		unlock();
		return;
	}

Kernel::running->stanje=PCB::BLOCKED;
myPCB->Qwait->put(Kernel::running);
Kernel::dispatch();
unlock();



}
void dispatch(){
	lock();
	Kernel::dispatch();
unlock();
}

//void tick(){}


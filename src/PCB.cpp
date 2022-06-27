/*
 * PCB.cpp
 *
 *  Created on: Apr 9, 2020
 *      Author: OS1
 */

#include <stdlib.h>
#include <dos.h>

#include "Kernel.h"
#include "PCB.h"


ID PCB::Global_ID=0;
int PCB::vel=0;
unsigned* PCB::st=NULL;

PCB::PCB(Thread*t,StackSize size,Time time){
lock();
id=Global_ID++;
	myThread=t;
	pcbStek=NULL;
	pcbtime=time;
	Qwait=new Queue();
	pcb_stack_size=size;
	stanje=NEW;
	ss=0;
	sp=0;
povratna_vred=1;
	vreme_na_semaforu=0;
    time_count=0;

unlock();
}



PCB::~PCB(){
	lock();
	delete Qwait;
	delete pcbStek;

unlock();
}

void PCB::Stack_Create(){
lock();
  vel= pcb_stack_size/2;
  st=new unsigned[vel];
pcbStek=st;
st[vel-1]=0x200; //psw bit I=1
st[vel-2]=FP_SEG(&(Kernel::wrapper));
st[vel-3]=FP_OFF(&(Kernel::wrapper));

sp=FP_OFF(st + vel-12);
ss=FP_SEG(st + vel-12);

unlock();
}







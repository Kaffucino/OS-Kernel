/*
 * Idlethr.cpp
 *
 *  Created on: Apr 12, 2020
 *      Author: OS1
 */
#include "Kernel.h"
#include "Idlethr.h"
#include "PCB.h"
#include <iostream.h>


Idlethr::Idlethr(): Thread(128,defaultTimeSlice) {}






	void Idlethr ::run(){
		while(1){}





	}

void Idlethr::start(){
lock();
myPCB->stanje=PCB::READY;
myPCB->Stack_Create();
unlock();

}





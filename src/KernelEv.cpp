/*
 * KernelEv.cpp
 *
 *  Created on: May 7, 2020
 *      Author: OS1
 */
#include "KernelEv.h"
#include "Kernel.h"
#include "IVTEntry.h"
#include "KernelS.h"
#include <dos.h>
KernelEv::KernelEv(IVTNo ivtNo){
lock();
	master=Kernel::running->myThread;
	this->ivtNo=ivtNo;
	mysem=new KernelSem(0);
	IVTEntry::IVT[ivtNo]->dogadjaj=this;

unlock();

}
KernelEv::~KernelEv(){
	lock();
		IVTEntry::IVT[ivtNo]->dogadjaj=NULL;
	   delete mysem;
	unlock();
}
void KernelEv::wait(){
	lock();
	if(Kernel::running->myThread != master){
		unlock();
		return;
	}
	mysem->wait(0);

	unlock();
}
void KernelEv::signal(){
	lock();
	if(mysem->value==1){
		unlock();
		return;
	}
	mysem->signal();
	unlock();
}

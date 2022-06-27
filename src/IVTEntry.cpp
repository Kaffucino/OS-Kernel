/*
 * IVTEntry.cpp
 *
 *  Created on: May 7, 2020
 *      Author: OS1
 */
#include "IVTEntry.h"
#include "Kernel.h"
#include "KernelEv.h"
#include <dos.h>
IVTEntry* IVTEntry::IVT[256];

IVTEntry::IVTEntry(unsigned char ivtNo, Int_routine novi){
	lock();
	this->ivtNo=ivtNo;
	IVT[ivtNo]=this;

	old_keyboard=getvect(ivtNo);
	setvect(ivtNo,novi);
	dogadjaj=NULL;

	unlock();

}



IVTEntry::~IVTEntry(){
	lock();
	old_keyboard();
	setvect(ivtNo,old_keyboard);
	unlock();

}
void IVTEntry::signal(){
	if(dogadjaj!=NULL)
		dogadjaj->signal();

}
void IVTEntry::zovi_stari_keyboard(){
	old_keyboard();
}

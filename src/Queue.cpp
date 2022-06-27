/*
 * Queue.cpp
 *
 *  Created on: Apr 8, 2020
 *      Author: OS1
 */

#include <stdlib.h>
#include "Queue.h"
#include "Kernel.h"

Queue::Queue(){
	lock();
	prvi=NULL;
	broj=0;
unlock();
}

Queue::~Queue(){
	lock();
	Elem* stari=NULL;
	while(prvi!=NULL){
		stari=prvi;
		prvi=prvi->sled;
		delete stari;
	}
	broj=0;
unlock();
}
int Queue::get_broj() const{
	return broj;
}
void Queue::put(PCB* p){
	lock();


Elem * novi = new Elem(p);
   if(prvi==NULL)
	   prvi=novi;
   else{
	   Elem* temp=prvi;
	   while(temp->sled!=NULL)
		   temp=temp->sled;
	   temp->sled=novi;
   }
broj++;
unlock();
}



PCB* Queue::get() {
	lock();
	if(prvi==NULL){
	unlock();
		return NULL;
	}
	Elem * temp=prvi;
	prvi=prvi->sled;
	broj--;
	PCB* p=temp->pcb;
	temp->pcb=NULL;
delete temp;
	unlock();
	return p;
}



Thread* Queue::dohv_nit(ID id){
	lock();
Elem*tek=prvi;
while(tek->pcb->id != id && tek!=NULL)
	tek=tek->sled;
if(tek==NULL){
	unlock();
	return NULL;
}

Thread* t=tek->pcb->myThread;
unlock();
return t;

}



ID Queue::dohv_id(Thread*t){
	lock();
	Elem*tek=prvi;
	while(tek->pcb->myThread!=t && tek!=NULL)
		tek=tek->sled;
	if(tek==NULL){
		unlock();
		return NULL;
	}

ID i=tek->pcb->id;
	unlock();
return i;

}
/*void Queue::izbaci_nit(PCB*p){
	lock();
	Elem*stari=NULL;
	Elem*tek=prvi;
	Elem*pret=NULL;


	while(tek!=NULL){
		if(tek->pcb!=p){
		pret=tek;
		tek=tek->sled;
		}else
			break;

	}

	  if(tek!=NULL){
         stari=tek;
         tek=tek->sled;
	if(pret==NULL)
	prvi=tek;
	else
		pret->sled=tek;
	delete stari;
	broj--;
	  }
unlock();

}*/





/*
 * Kernel.cpp
 *
 *  Created on: Apr 11, 2020
 *      Author: OS1
 */
#include "Kernel.h"
#include "schedule.h"
#include "Queue.h"
#include "KernelS.h"
#include "ListaSem.h"
#include "Semaphore.h"
#include "IVTEntry.h"
#include <dos.h>
#include <stdlib.h>

int syncPrintf(const char *format, ...);

Prekidna_Rutina Kernel::old_interrupt=NULL;
Idlethr* Kernel::idle = NULL;
 PCB* Kernel::running=NULL;
Thread* Kernel::begin=NULL;
int Kernel::ekspl=0;
Queue*Kernel::red_niti=new Queue();
ListaSem*Kernel::lista_semafora=new ListaSem();

static unsigned pomss,pomsp;
static PCB* nova;

void Kernel::load(){
	lock();
	//lista_semafora=new ListaSem();

	//red_niti=new Queue();

	old_interrupt=getvect(0x08);

setvect(0x08,Kernel_Timer);

begin=new Thread(0x100,1);

begin->myPCB->stanje=PCB::READY;

running =begin->myPCB;

idle=new Idlethr();
idle->start();

unlock();
}
void Kernel::dispatch(){
	lock();
	ekspl=1;
	Kernel_Timer();
	ekspl=0;
	unlock();
}

 /*void Kernel::unblock_i_dekr(){

 Eleme*pom=lista_semafora->prvi;
 Elem*tek;
		while(pom!=NULL){
				   KernelSem*sem=pom->semafor->myImpl;
				   tek=sem->time_blocked->prvi;
				     while(tek!=NULL){
                           PCB*p=tek->pcb;
				        	p->vreme_na_semaforu--;
				        	if(p->vreme_na_semaforu==0){
				        		sem->time_blocked->izbaci_nit(p);
				        		sem->value++;
				        		p->stanje=PCB::READY;
				        	Scheduler::put(p);
				        	}
                          tek=tek->sled;


				        }


         pom=pom->sled;

		}

}
*/





void Kernel::azuriraj() {
	Eleme *pom=lista_semafora->prvi;

	while(pom!=0){
		Elem *cur = pom->semafor->myImpl->time_blocked->prvi, *prev = 0, *old = 0;

				while (cur) {
					cur->pcb->vreme_na_semaforu--;
					if (cur->pcb->vreme_na_semaforu > 0) {
						prev = cur;
						cur = cur->sled;
					} else {
						cur->pcb->stanje = PCB::READY;
						cur->pcb->povratna_vred = 0;
						Scheduler::put(cur->pcb);

						old = cur;
						cur = cur->sled;
						if (!prev)
							pom->semafor->myImpl->time_blocked->prvi = cur;
						else
							prev->sled = cur;
						delete old;
						pom->semafor->myImpl->value++;
					}
				}

		pom=pom->sled;
	}

	/*pom=lista_semafora->prvi;

		       while(pom!=NULL){
						   sem=pom->semafor->myImpl;
						   tek=sem->time_blocked->prvi;
						     while(tek!=NULL){
		                           p=tek->pcb;
						        	p->vreme_na_semaforu--;
						        	if(p->vreme_na_semaforu==0){
											   sem->time_blocked->izbaci_nit(p);
											sem->value++;

											p->stanje=PCB::READY;
										   p->povratna_vred=0;
									   Scheduler::put(p);
									   tek=sem->time_blocked->prvi;
						        	} else {
						        		tek=tek->sled;
						        	}

						        }


		         pom=pom->sled;

				}*/
}


   Eleme*pom;
   Elem*tek;
   KernelSem*sem;
   PCB*p;

void interrupt Kernel::Kernel_Timer(...){
 //static unsigned pomss,pomsp;
//static PCB* nova;



	if(ekspl==0){
		 tick();
		(*old_interrupt)();
	}
	if(ekspl==0){

		azuriraj();





	}





	if(ekspl==0 && running->pcbtime!=0 )
		running->time_count++;


	if(ekspl==0 && running->pcbtime==0)
		return;


if(ekspl==0 && running->time_count< running->pcbtime)
	return;










// ako je explicitan poziv


	ekspl=0;

	asm{
		  mov pomss,ss
		  mov pomsp,sp
	  }
	running->sp=pomsp;
	running->ss=pomss;

if(running!=idle->myPCB && running->stanje==PCB::READY)
Scheduler::put(running);


nova=Scheduler::get();

  if(nova==NULL)
nova=idle->myPCB;

running=nova;

  pomsp=running->sp;
  pomss=running->ss;
  asm{
	  mov sp,pomsp
	  mov ss,pomss
  }

running->time_count=0;
}





void Kernel::unload(){
	lock();
	if(running!=begin->myPCB){
		unlock();
		return;
	}
	setvect(0x08,old_interrupt);


	delete begin;
	delete idle;

	delete red_niti;
	delete lista_semafora;

unlock();

}

void Kernel::wrapper(){

	running->myThread->run();
	lock();
	running->stanje=PCB::OVER;
/*
	syncPrintf("Zavrsila %d\n", running->id);

	for (Elem *tek = Kernel::red_niti->prvi; tek; tek=tek->sled) {
		if (tek->pcb->stanje != PCB::OVER && tek->pcb->stanje < PCB::OVER) {
			syncPrintf("%d %d | ", tek->pcb->id, tek->pcb->stanje);
		}
	}
	syncPrintf("\n");*/

	PCB*pomm;
	pomm=running->Qwait->get();
	while(pomm){
		pomm->stanje=PCB::READY;
		Scheduler::put(pomm);
		//syncPrintf("Oslobodila se %d\n", pomm->id);
		pomm=running->Qwait->get();
	}

	dispatch();

	unlock();
}

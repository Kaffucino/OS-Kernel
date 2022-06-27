/*
 * KernelSem.cpp
 *
 *  Created on: May 1, 2020
 *      Author: OS1
 */

#include "KernelS.h"
#include "Schedule.h"
#include "Semaphor.h"

KernelSem::KernelSem(int init){
	lock();
	value=init;
	blocked=new Queue(); //za blokirane na neograniceno vreme
	time_blocked=new Queue();// za blokirane na vreme

unlock();
}

KernelSem::~KernelSem(){
	lock();
	while(blocked->prvi!=NULL){
		PCB* thr=blocked->get();
        // if(thr!=NULL){
		thr->stanje=PCB::READY;
		Scheduler::put(thr);
        // }

	}
	while(time_blocked->prvi!=NULL){
			PCB* thr=time_blocked->get();
       // if(thr!=NULL){
			thr->stanje=PCB::READY;
			Scheduler::put(thr);
       // }

		}


delete blocked;
delete time_blocked;

unlock();
}
int KernelSem::get_val() const{
	return value;
}





int KernelSem::signal(int n){
	lock();
	int ret=0;
	int i;

	if(n>=0){
		if(n==0)
			i=-1;
		else
			i=0;
		for(;i<n;i++){
			if(value++<0){
				ret++;
				PCB*thr=blocked->get();
				if(thr==NULL)
					thr=time_blocked->get();
				if(thr!=NULL){
				thr->stanje=PCB::READY;
				Scheduler::put(thr);
				}


			}


		}




	}else
		ret=n;

unlock();
return ret;

}
/*
int KernelSem::blokiraj(Time vreme){
	lock();
	int ret=1;

	if(vreme==0){
		Kernel::running->stanje=PCB::BLOCKED;
		blocked->put(Kernel::running);
		Kernel::dispatch();


	}else{
		Kernel::running->stanje=PCB::BLOCKED;
		Kernel::running->vreme_na_semaforu=vreme;
		time_blocked->put(Kernel::running);
		Kernel::dispatch();

		ret=0;
	}

unlock();
	return ret;

}
*/


int KernelSem::wait(Time maxTimeToWait){
lock();

  if(--value<0){
	  if(maxTimeToWait==0){
	  		Kernel::running->stanje=PCB::BLOCKED;
	  		blocked->put(Kernel::running);
	  		Kernel::dispatch();


	  	}else{
	  		Kernel::running->stanje=PCB::BLOCKED;
	  		Kernel::running->vreme_na_semaforu=maxTimeToWait;
	  		time_blocked->put(Kernel::running);
	  		Kernel::dispatch();

	  	}





  }




unlock();
return Kernel::running->povratna_vred;

}
















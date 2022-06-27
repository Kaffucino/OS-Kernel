/*
 * Semaphor.cpp
 *
 *  Created on: May 1, 2020
 *      Author: OS1
 */
#include "Semaphor.h"
#include "Kernel.h"
#include "KernelS.h"

class Kernel;


Semaphore::Semaphore(int init){
	lock();
	myImpl=new KernelSem(init);
	//Kernel::lista_semafora->dodaj(this);
	unlock();
}

Semaphore::~Semaphore(){
	lock();
	//Kernel::lista_semafora->izbaci_semafor(this);
	delete myImpl;

	unlock();
}
int Semaphore:: wait (Time maxTimeToWait){
	lock();

if(Kernel::lista_semafora->nalazi_se(this) == 0)
Kernel::lista_semafora->dodaj(this);


 int ret= myImpl->wait(maxTimeToWait);

 if(Kernel::lista_semafora->nalazi_se(this) == 1)
	 Kernel::lista_semafora->izbaci_semafor(this);

 unlock();
 return ret;
}
int Semaphore::signal(int n){
	lock();

	if(Kernel::lista_semafora->nalazi_se(this) ==0)
	Kernel::lista_semafora->dodaj(this);

	 int ret= myImpl->signal(n);

if(Kernel::lista_semafora->nalazi_se(this) == 1)
	 Kernel::lista_semafora->izbaci_semafor(this);

unlock();
return ret;


}
int Semaphore::val() const{
	return myImpl->value;

}




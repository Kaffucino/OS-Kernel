/*
 * ListaSem.cpp
 *
 *  Created on: May 3, 2020
 *      Author: OS1
 */

#include "ListaSem.h"
#include "Kernel.h"
#include "Semaphore.h"
ListaSem::ListaSem(){
	lock();
	prvi=NULL;
	num=0;
	unlock();
}


ListaSem::~ListaSem(){
	lock();
	num=0;
	while(prvi!=NULL){

		Eleme* stari=prvi;
		prvi=prvi->sled;
		delete stari;
	}
unlock();
}






void ListaSem::dodaj(Semaphore* s){ //dodaje na pocetak
	lock();
	Eleme*novi=new Eleme(s);
	if(prvi==NULL)
		prvi=novi;
	else{
        novi->sled=prvi;
        prvi=novi;

	}

	num++;
unlock();
}


void ListaSem::izbaci_semafor(Semaphore* s){
	lock();
	Eleme*tek=prvi;
	Eleme*pret=NULL;
	Eleme*stari=NULL;
	while(tek->semafor!=s){
		pret=tek;
		tek=tek->sled;
	}
	if(tek!=NULL){

        stari=tek;
        tek=tek->sled;
	if(pret==NULL)
		prvi=tek;
	else
		pret->sled=tek;
	num--;


	delete stari;

	}

unlock();

}



int ListaSem::dohv_broj() const{
	return num;
}

int ListaSem::nalazi_se(Semaphore*s){
	lock();
	int flag=0;
   Eleme*tek=prvi;

while(tek!=NULL){
	if(tek->semafor==s){
		flag=1;
		break;

	}

	tek=tek->sled;

}

unlock();
return flag;





}



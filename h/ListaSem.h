/*
 * ListaSem.h
 *
 *  Created on: May 3, 2020
 *      Author: OS1
 */

#ifndef LISTASEM_H_
#define LISTASEM_H_
#include "Semaphor.h"
#include <stdlib.h>
class Semaphore;
class KernelSem;

struct Eleme{
Eleme* sled;
Semaphore* semafor;
Eleme(Semaphore *s){
	semafor=s;
	sled=NULL;
}

};

class ListaSem{

public:
	Eleme *prvi;
	int num;


	ListaSem();
	~ListaSem();
void dodaj(Semaphore* s);
int dohv_broj() const;
void izbaci_semafor(Semaphore*s);
int nalazi_se(Semaphore*s);




};





#endif /* LISTASEM_H_ */

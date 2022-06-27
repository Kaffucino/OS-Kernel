/*
 * Queue.h
 *
 *  Created on: Apr 8, 2020
 *      Author: OS1
 */


#ifndef QUEUE_H_
#define QUEUE_H_
#include "PCB.h"
#include <stdlib.h>
class PCB;
struct Elem{
	PCB* pcb;
	Elem* sled;
	Elem(PCB*p){
		pcb=p;
		sled=NULL;
	}


};
class Queue{
public:
	int broj;
	Elem* prvi;

	Queue();
	~Queue();
	int get_broj() const;
 Thread* dohv_nit(ID id);
 ID dohv_id(Thread*t);
 //void izbaci_nit(PCB*p);
	PCB* get();
	void put(PCB* p);


};













#endif /* QUEUE_H_ */

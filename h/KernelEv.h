/*
 * KernelEv.h
 *
 *  Created on: May 7, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
#include "Event.h"
class Thread;
class KernelSem;
typedef unsigned char IVTNo;
class KernelEv{
private:
	IVTNo ivtNo;
	Thread* master;
	KernelSem*mysem;
public:
	KernelEv(IVTNo ivtNo);

   ~KernelEv();
void signal();
void wait();

protected:
friend class IVTEntry;


};




#endif /* KERNELEV_H_ */

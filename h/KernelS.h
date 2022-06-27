/*
 * KernelSem.h
 *
 *  Created on: May 1, 2020
 *      Author: OS1
 */

#ifndef KERNELS_H_
#define KERNELS_H_
#include "Queue.h"
#include "Kernel.h"


class KernelSem{
public:

int value;
Queue* blocked;
Queue *time_blocked;


KernelSem(int init=1);


 virtual ~KernelSem();
  virtual int wait (Time maxTimeToWait);
   virtual int signal(int n=0);
  int get_val() const;

//int blokiraj(Time vreme);
protected:

friend class Thread;
friend class PCB;
friend class Kernel;





};






#endif /* KERNELS_H_ */

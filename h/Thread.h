/*
 * Thread.h
 *
 *  Created on: Apr 9, 2020
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_


class PCB;
typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time;
const Time defaultTimeSlice = 2;
typedef int ID;

class Thread{
private:
 	PCB* myPCB;
public:
 	virtual void run(){}
 	void start();
 	void waitToComplete();
 		static ID getRunningId();
 		static Thread * getThreadById(ID id);
 		ID getId();
 		virtual ~Thread();

protected:
	friend class PCB;
friend class KernelSem;
		friend class Idlethr;
		friend class Kernel;
	 Thread (StackSize stackSize = defaultStackSize, Time timeSlice =defaultStackSize);










};
void dispatch();

extern void tick();







#endif /* THREAD_H_ */

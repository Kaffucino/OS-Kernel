/*
 * Kernel.h
 *
 *  Created on: Apr 9, 2020
 *      Author: OS1
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include "PCB.h"
#include "Idlethr.h"
#include "Thread.h"
#include "ListaSem.h"
class Idlethr;
class Thread;
int syncPrintf(const char *format, ...);
#define lock(){asm{pushf; cli;}}

#define unlock(){asm{popf;}}
typedef void interrupt (*Prekidna_Rutina)(...);

class Kernel{
public:
	static void dispatch();
	static void load();
	static void unload();
	static ListaSem*lista_semafora;
private:
	friend class Thread;
		friend class PCB;
		friend class Semaphore;
		friend class KernelSem;
		friend class KeyboardEvent;
		friend int userMain (int argc, char* argv[]);
friend class KernelEv;
	static void azuriraj();
	static Thread* begin;
	static  PCB* running;
	static Prekidna_Rutina old_interrupt;
	static void interrupt Kernel_Timer(...);
	static void wrapper();
	static int ekspl;
static Queue* red_niti;
   static Idlethr* idle;
};








#endif /* KERNEL_H_ */

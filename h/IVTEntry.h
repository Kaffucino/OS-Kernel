/*
 * IVTEntry.h
 *
 *  Created on: May 7, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
class KernelEv;
typedef void interrupt (*Int_routine)(...);

class IVTEntry{
public:
	static IVTEntry*IVT[];
	KernelEv* dogadjaj;
	unsigned char ivtNo;
	Int_routine old_keyboard;
	IVTEntry(unsigned char ivtNo ,Int_routine novi );
~IVTEntry();
void signal();
void zovi_stari_keyboard();

protected:
friend class KerneEv;



};





#endif /* IVTENTRY_H_ */

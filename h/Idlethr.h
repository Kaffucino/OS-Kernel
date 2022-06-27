/*
 * Idlethr.h
 *
 *  Created on: Apr 12, 2020
 *      Author: OS1
 */

#ifndef IDLETHR_H_
#define IDLETHR_H_

#include "Thread.h"

//class Thread;

class Idlethr : public Thread{

	friend class Thread;


public:
	Idlethr();
	virtual void run();
	void start();

};



#endif /* IDLETHR_H_ */

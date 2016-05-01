/*
 * writeworker.h
 *
 *  Created on: Apr 30, 2016
 *      Author: anhmt
 */

#ifndef THREAD_WRITEWORKER_HPP_
#define THREAD_WRITEWORKER_HPP_

#include "workerthread.hpp"

class WriteWorker: public WorkerThread
{
public:
	WriteWorker ();
	virtual ~WriteWorker ();

private:
	void PrivateThreadProc (void);
};

#endif /* THREAD_WRITEWORKER_HPP_ */

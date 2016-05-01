/*
 * writeworker.cpp
 *
 *  Created on: Apr 30, 2016
 *      Author: anhmt
 */

#include "writeworker.hpp"

WriteWorker::WriteWorker ()
: WorkerThread ()
{
}

WriteWorker::~WriteWorker ()
{
}

void WriteWorker::PrivateThreadProc ()
{
	while (m_threadState == THREAD_STATE_RUNNING)
	{
		fprintf (stderr, "State: %s\n", ThreadStateStr[(int)m_threadState]);
	}
}

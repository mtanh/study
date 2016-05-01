/*
 * worker_thread.cxx
 *
 *  Created on: Apr 30, 2016
 *      Author: anhmt
 */

#include "../common/defines.hpp"
#include "workerthread.hpp"

WorkerThread::WorkerThread (bool start)
: m_threadState (THREAD_STATE_STOPPED)
, m_threadPriority (THREAD_PRIORITY_NORMAL)
, m_threadProc (nullptr)
{
	if (start)
	{
		if (Start())
		{
			fprintf (stderr, "WorkerThread ctor failed\n");
		}
	}
}

WorkerThread::~WorkerThread ()
{
}

bool WorkerThread::Start ()
{
	do
	{
		if (Running())
		{
			WHICHLINE;
			break;
		}

		m_threadState = THREAD_STATE_RUNNING;
		m_threadProc = &WorkerThread::ThreadProc;
		// Thread Attributions ???
		b_thread tmp = boost::thread (m_threadProc, this);
		m_bThread.swap (tmp);

	} while (false);

	return (Running());
}

void WorkerThread::Stop ()
{
	if (Running() && m_bThread.joinable())
	{
		m_threadState = THREAD_STATE_PENDING;
		WHICHFUNC;
		m_bThread.interrupt ();

		fprintf (stderr, "State: %s\n", ThreadStateStr[(int)m_threadState]);
	}
}

void WorkerThread::Join ()
{
	if (m_bThread.joinable())
	{
		WHICHFUNC;
		m_threadState = THREAD_STATE_STOPPED;
		m_bThread.join ();
		fprintf (stderr, "State: %s\n", ThreadStateStr[(int)m_threadState]);
	}
}

void WorkerThread::ChangeThreadPriority (ThreadPriority p)
{
	// Not yet implement
}

void WorkerThread::ThreadProc ()
{
	try
	{
		PrivateThreadProc ();
	}
	catch (boost::thread_interrupted& ei)
	{
		fprintf (stderr, "Thread interrupted\n");
		Join();
	}
	catch (boost::thread_exception& ex)
	{
		fprintf (stderr, "%s\n", ex.what());
		Join();
	}
}

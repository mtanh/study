/*
 * WorkerThread.hpp
 *
 *  Created on: Apr 30, 2016
 *      Author: anhmt
 */

#ifndef THREAD_WORKERTHREAD_HPP_
#define THREAD_WORKERTHREAD_HPP_

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

typedef boost::thread b_thread;
enum ThreadState { THREAD_STATE_STOPPED = 0, THREAD_STATE_PENDING /* Ready to stop */, THREAD_STATE_RUNNING };
enum ThreadPriority {
	THREAD_PRIORITY_TIME_CRITICAL = 0,
	THREAD_PRIORITY_HIGHEST,
	THREAD_PRIORITY_ABOVE_NORMAL,
	THREAD_PRIORITY_NORMAL,
	THREAD_PRIORITY_BELOW_NORMAL,
	THREAD_PRIORITY_LOWEST,
	THREAD_PRIORITY_IDLE
};

static const char* ThreadStateStr[] = { "stopped", "pending", "running" };

class WorkerThread: boost::noncopyable
{
	typedef void (WorkerThread::*THREAD_PROC) (void);

public:
	explicit WorkerThread (bool autoStart = true);
	virtual ~WorkerThread ();

	inline bool Running() const { return (m_threadState == THREAD_STATE_RUNNING); }
	inline bool Pending() const { return (m_threadState == THREAD_STATE_PENDING); }
	inline bool Stopped() const { return (m_threadState == THREAD_STATE_STOPPED); }

	bool Start ();
	void Detach ();
	void Stop ();
	void ChangeThreadPriority (ThreadPriority p);
	const ThreadState GetThreadState () const { return m_threadState; }

protected:
	void ThreadProc (void);

protected:
	b_thread m_bThread;
	volatile ThreadState m_threadState;
	ThreadPriority m_threadPriority;

private:
	virtual void PrivateThreadProc (void) = 0;
	THREAD_PROC m_threadProc;
};


#endif /* THREAD_WORKERTHREAD_HPP_ */

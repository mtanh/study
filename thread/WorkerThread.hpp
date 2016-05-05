/*
 * WorkerThread.hpp
 *
 *  Created on: Apr 30, 2016
 *      Author: anhmt
 */

#ifndef THREAD_WORKERTHREAD_HPP_
#define THREAD_WORKERTHREAD_HPP_

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread.hpp>

typedef boost::thread BThread;
typedef BThread::id BThreadId;

enum ThreadState {
	THREAD_STATE_STOPPED = 0,
	THREAD_STATE_PENDING /* Ready to stop */,
	THREAD_STATE_RUNNING
};
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

class CallableBase: public boost::noncopyable
{
public:
	CallableBase(): m_arg(nullptr) {}
	CallableBase(void* arg): m_arg(arg) {}
	virtual ~CallableBase () {}

	void SetArg(void* arg) { m_arg = arg; }
	virtual void operator()() = 0;

protected:
	void* m_arg;
};

class WorkerThread: public boost::noncopyable {

	typedef void (WorkerThread::*THREAD_PROC)(void);

public:
	explicit WorkerThread(ThreadPriority thrPriority = THREAD_PRIORITY_NORMAL, bool autoStart = false);
	virtual ~WorkerThread();

	inline bool Running() const {
		return (m_threadState == THREAD_STATE_RUNNING);
	}
	inline bool Pending() const {
		return (m_threadState == THREAD_STATE_PENDING);
	}
	inline bool Stopped() const {
		return (m_threadState == THREAD_STATE_STOPPED);
	}

	inline void SetCallableObj(CallableBase* pCallable) { if(pCallable != nullptr) { m_pCallable = pCallable; } }
	inline BThreadId GetThreadId() const { return boost::this_thread::get_id(); }
	bool Start();
	void Detach();
	void Stop();
	void ChangeThreadPriority(ThreadPriority p);
	const ThreadState GetThreadState() const { return m_threadState; }

protected:
	void ThreadProc(void);

protected:
	BThread m_bThread;
	volatile ThreadState m_threadState;
	ThreadPriority m_threadPriority;
	CallableBase* m_pCallable;

private:
	virtual void PrivateThreadProc(void) /*= 0*/;
	THREAD_PROC m_threadProc;
};

#endif /* THREAD_WORKERTHREAD_HPP_ */

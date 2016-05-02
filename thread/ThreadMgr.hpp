/*
 * ThreadPool.h
 *
 *  Created on: May 2, 2016
 *      Author: anh.ma
 */

#ifndef THREAD_THREADMGR_HPP_
#define THREAD_THREADMGR_HPP_

#include <boost/container/vector.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/fusion/include/pair.hpp>
#include "WorkerThread.hpp"

typedef struct Synchable
{
	boost::timed_mutex mtx;
	boost::condition_variable cond_val;
} Synchable;

template <
	typename MonitorWorker
	, typename ThreadBase
	>
class ThreadMgr {
public:
	ThreadMgr();
	virtual ~ThreadMgr();

	void Start();
	void Stop();
	void Run(ThreadBase*);

private:
	void StartThread ();

private:
	typedef unsigned short small_value;
	small_value m_maxThreads; // A maximum thread object that ThreadMgr can support
	small_value m_minThreads; // A minimum thread object that ThreadMgr can start up
	small_value m_numIdleThreads;
	small_value m_numRunningThreads;

	typedef boost::ptr_deque <WorkerThread> PWORKER_THREAD_LIST;
	PWORKER_THREAD_LIST::iterator PWORKER_THREAD_ITER;
	PWORKER_THREAD_LIST m_RunnableQueue;

	typedef boost::fusion::pair <boost::thread::id, ThreadState> THRID_PAIR;
	typedef boost::container::vector <THRID_PAIR> THREAD_STATE_LIST;
	THREAD_STATE_LIST m_runningThreadsMap;

	Synchable m_synchAble;
	MonitorWorker m_threadsMonitor;
};

#endif /* THREAD_THREADMGR_HPP_ */

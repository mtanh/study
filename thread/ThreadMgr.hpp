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
#include <boost/variant.hpp>
#include <limits.h>
#include "WorkerThread.hpp"

typedef boost::thread::id BThreadId;
#define ERROR(str) \
	fprintf(stderr, (str)); \
	fprintf(stderr, "\n");

template<typename MonitorWorker, typename ThreadBaseType>
class ThreadMgr: public boost::noncopyable {

	typedef struct Synchable {
		boost::timed_mutex mtx;
		boost::condition_variable cond_val;
	} Synchable;

public:
	ThreadMgr();
	~ThreadMgr();

	bool Init(unsigned int maxThreadNum = (unsigned int)boost::thread::hardware_concurrency());
	void Start();
	void Stop();
	BThreadId Run(ThreadBaseType*);

private:
	void StartWorkerThread();

private:
	unsigned int m_maxThreads;
	int m_numRunningThreads;
	bool m_isStopped;
	bool m_initialized;

	typedef boost::ptr_deque<WorkerThread> PWORKER_THREAD_LIST;
	typedef PWORKER_THREAD_LIST::iterator PWORKER_THREAD_ITER;
	PWORKER_THREAD_LIST m_RunnableQueue;

	typedef boost::fusion::pair<boost::thread::id, ThreadState> THRID_PAIR;
	typedef boost::container::vector<THRID_PAIR> THREAD_STATE_LIST;
	THREAD_STATE_LIST m_runningThreadsMap;

	Synchable m_synchAble;
	MonitorWorker m_threadMonitor;
};

extern ThreadMgr gThreadManager;

template<typename MonitorWorker, typename ThreadBaseType>
inline ThreadMgr<MonitorWorker, ThreadBaseType>::ThreadMgr()
		: m_maxThreads((unsigned int)boost::thread::hardware_concurrency())
		, m_isStopped(true)
		, m_numRunningThreads(0)
		, m_initialized(false) {
}

template<typename MonitorWorker, typename ThreadBaseType>
inline bool ThreadMgr<MonitorWorker, ThreadBaseType>::Init(unsigned int maxThreadNum) {

	bool ret = true;
	do {

		if(maxThreadNum <= 0 || maxThreadNum >= UINT_MAX)
		{
			ret = false;
			break;
		}

		m_maxThreads = maxThreadNum;

	} while(false);

	m_initialized = ret;
	return m_initialized;
}

template<typename MonitorWorker, typename ThreadBaseType>
inline ThreadMgr<MonitorWorker, ThreadBaseType>::~ThreadMgr() {
}

template<typename MonitorWorker, typename ThreadBaseType>
inline void ThreadMgr<MonitorWorker, ThreadBaseType>::Start() {

	if(m_isStopped)
	{
		m_isStopped = false;


	}
}

template<typename MonitorWorker, typename ThreadBaseType>
inline void ThreadMgr<MonitorWorker, ThreadBaseType>::Stop() {
}

template<typename MonitorWorker, typename ThreadBaseType>
inline BThreadId ThreadMgr<MonitorWorker, ThreadBaseType>::Run(ThreadBaseType* arg) {
}

#endif /* THREAD_THREADMGR_HPP_ */

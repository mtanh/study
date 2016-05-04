/*
 * ThreadPool.h
 *
 *  Created on: May 2, 2016
 *      Author: anh.ma
 */

#ifndef THREAD_TASKPOOL_HPP_
#define THREAD_TASKPOOL_HPP_

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

template<typename CallableTask>
class TaskPool: public boost::noncopyable {

	typedef struct Synchable {
		boost::timed_mutex mtx;
		boost::condition_variable cond_val;
	} Synchable;

public:
	TaskPool();
	~TaskPool();

	bool Init(unsigned int maxThreadNum = (unsigned int)boost::thread::hardware_concurrency());
	void Start();
	void Stop();
	void Run(CallableTask* task);

	inline bool Stopped() const { return m_isStopped; }

private:
	void StartWorkerThread();

private:
	unsigned int m_maxThreads;
	int m_numRunningThreads;
	bool m_isStopped;
	bool m_isInitialized;

	typedef boost::ptr_deque<WorkerThread> PWORKER_THREAD_LIST;
	typedef PWORKER_THREAD_LIST::iterator PWORKER_THREAD_ITER;
	PWORKER_THREAD_LIST m_RunnableQueue;

	typedef boost::fusion::pair<boost::thread::id, ThreadState> THRID_PAIR;
	typedef boost::container::vector<THRID_PAIR> THREAD_STATE_LIST;
	THREAD_STATE_LIST m_runningThreadsMap;

	Synchable m_synchAble;
};

template<typename CallableTask>
TaskPool<CallableTask>::TaskPool()
: m_maxThreads((unsigned int)boost::thread::hardware_concurrency())
, m_isStopped(true)
, m_numRunningThreads(0)
, m_isInitialized(false) {
}

template<typename CallableTask>
bool TaskPool<CallableTask>::Init(unsigned int maxThreadNum) {

	bool ret = true;
	do {

		if(maxThreadNum <= 0 || maxThreadNum >= UINT_MAX)
		{
			ret = false;
			break;
		}

		m_maxThreads = maxThreadNum;

	} while(false);

	m_isInitialized = ret;
	return m_isInitialized;
}

template<typename CallableTask>
TaskPool<CallableTask>::~TaskPool() {
}

template<typename CallableTask>
inline void TaskPool<CallableTask>::Start() {

	if(m_isStopped)
	{
		m_isStopped = false;
	}
}

template<typename CallableTask>
void TaskPool<CallableTask>::Stop() {

}

template<typename CallableTask>
void TaskPool<CallableTask>::Run(CallableTask* task) {
}

#endif /* THREAD_TASKPOOL_HPP_ */

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
#include <boost/make_shared.hpp>
#include <limits.h>
#include <vector>
#include <algorithm>

#include "../common/defines.hpp"
#include "WorkerThread.hpp"

#define ERROR(str) \
	fprintf(stderr, (str)); \
	fprintf(stderr, "\n");

class TaskPool: public boost::noncopyable {

	typedef boost::ptr_deque<CallableBase> PTASK_LIST;
	typedef typename PTASK_LIST::iterator PTASK_ITER;
	typedef std::vector<WorkerThread*> THREAD_LIST;

	template<typename T>
	class ThreadStateCompare {
	public:
		bool operator()(const T* const t1, const T* const t2) {
			return StateLess(t1->GetThreadState(), t2->GetThreadState());
		}
		bool operator()(const T* const t, ThreadState state) {
			return StateLess(t->GetThreadState(), state);
		}
		bool operator()(ThreadState state, const T* const t) {
			return StateLess(t->GetThreadState(), state);
		}
	private:
		bool StateLess(ThreadState state1, ThreadState state2) const {
			return (state1 < state2);
		}
	};

	typedef struct Synchable {
		boost::mutex mtxPoolState;
		boost::condition_variable cond_val;
	} Synchable;

	class GetTask: public CallableBase {
	public:
		GetTask(): CallableBase() {}
		GetTask(void* arg): CallableBase(arg) {}
		virtual ~GetTask() { WHICHFUNC }
		virtual void operator()() {
			TaskPool* pTaskPool = (TaskPool*)m_arg;
			if(pTaskPool != nullptr) {
				while(!pTaskPool->m_isStopped) {

					// TODO Double check

					puts("Monitoring task queue and pop task ....");
					boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
				}
			}
		}
	};

	class ThreadMonitorTask: public CallableBase {
	public:
		ThreadMonitorTask(): CallableBase() {}
		ThreadMonitorTask(void* arg): CallableBase(arg) {}
		virtual ~ThreadMonitorTask() {}
		virtual void operator()() {
			TaskPool* pTaskPool = (TaskPool*)m_arg;
			if(pTaskPool != nullptr) {
				while(!pTaskPool->m_isStopped) {

					// TODO Double check

					puts("Monitoring ....");
					boost::this_thread::sleep_for(boost::chrono::milliseconds(150));
				}
			}
		}
	};

public:
	TaskPool();
	~TaskPool();

	bool Init(unsigned int maxThreadNum = (unsigned int) boost::thread::hardware_concurrency());
	void Start();
	void Stop();
	void Run(CallableBase* task);
	inline bool Stopped() const { return m_isStopped; }
	void TaskEnQueue(CallableBase* task);
	CallableBase* TaskDeQueue();

private:
	void StartThread();

private:
	unsigned int m_maxThreads;
	int m_numRunningThreads;
	bool m_isStopped;

	PTASK_LIST m_TaskQueue;
	THREAD_LIST m_runningThreadsMap;
	WorkerThread m_threadMonitoring;
	Synchable m_synchAble;
};


TaskPool::TaskPool()
: m_maxThreads((unsigned int) boost::thread::hardware_concurrency())
, m_isStopped(true)
, m_numRunningThreads(0) {
}

bool TaskPool::Init(unsigned int maxThreadNum) {

	bool ret = true;
	do {
		if (maxThreadNum <= 0 || maxThreadNum >= UINT_MAX) {
			ret = false;
			break;
		}
		m_maxThreads = maxThreadNum;
	} while (false);

	return ret;
}

TaskPool::~TaskPool() {

	WHICHFUNC
	THREAD_LIST::iterator it = m_runningThreadsMap.begin();
	for(; it != m_runningThreadsMap.end(); ++it) {
		delete (*it);
		(*it) = nullptr;
	}
}

inline void TaskPool::Start() {

	if (m_isStopped) {
		m_isStopped = false; // start or restart task pool
		StartThread();

		//boost::shared_ptr<ThreadMonitorTask> monitorTask(new ThreadMonitorTask(nullptr));
		ThreadMonitorTask* monitorTask = new ThreadMonitorTask(this);
		m_threadMonitoring.SetCallable(monitorTask);
		m_threadMonitoring.Start();
	}
}

void TaskPool::Stop() {

	{
		boost::lock_guard<boost::mutex> guard(m_synchAble.mtxPoolState);
		m_isStopped = true;
	}

	// TODO Signal the waiting threads
	m_threadMonitoring.Stop();
	THREAD_LIST::iterator it = m_runningThreadsMap.begin();
	for(; it != m_runningThreadsMap.end(); ++it) {
		(*it)->Stop();
	}
}

void TaskPool::Run(CallableBase* task) {

	if(!m_isStopped) {

	}
}

void TaskPool::TaskEnQueue(CallableBase* task) {
}

CallableBase* TaskPool::TaskDeQueue() {

	return nullptr;
}

void TaskPool::StartThread() {

	// protect the whole transaction utilize lock_guard
	boost::lock_guard<boost::mutex> guard(m_synchAble.mtxPoolState);
	if(!m_isStopped) {
		WorkerThread* thr = new WorkerThread(THREAD_PRIORITY_ABOVE_NORMAL, /*auto-run=*/false);
		GetTask* getTask = new GetTask(this);
		thr->SetCallable(getTask);
		(void)thr->Start();

		// TODO Leak ???
		//boost::shared_ptr<WorkerThread> thr(new WorkerThread(THREAD_PRIORITY_ABOVE_NORMAL, /*auto-run=*/false));
		//boost::shared_ptr<WorkerTask> w(new WorkerTask(this));
		//thr->SetCallableObj(w.get());

		std::cout << "[Started] Thread ID= " << thr->GetThreadId() << "\n";
		m_runningThreadsMap.push_back(thr);
		std::sort(m_runningThreadsMap.begin(), m_runningThreadsMap.end(), ThreadStateCompare<WorkerThread>());
		m_numRunningThreads++;
	}
}

extern TaskPool gTaskPool;

#endif /* THREAD_TASKPOOL_HPP_ */

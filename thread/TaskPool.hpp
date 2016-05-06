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
#include <boost/atomic.hpp>
#include <limits.h>
#include <vector>
#include <deque>
#include <algorithm>

#include "../common/defines.hpp"
#include "WorkerThread.hpp"

#define ERROR(str) \
	fprintf(stderr, (str)); \
	fprintf(stderr, "\n");

static const unsigned int MAX_TASK = 10;

class TaskPool: public boost::noncopyable {

	typedef std::deque<CallableBase*> TASK_LIST;
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

	typedef struct SynchSuite {
		boost::mutex mtxThreadsMap;
		boost::mutex mtxTaskQueue;
		boost::condition_variable cvTaskQueue;
	} SynchSuite;

	class GetTask: public CallableBase {
	public:
		GetTask(): CallableBase() {}
		GetTask(void* arg, CallablePriority priority = CALLABLE_PRIORITY_NORMAL): CallableBase(arg, priority) {}
		virtual ~GetTask() { WHICHFUNC }
		virtual void operator()() {
			TaskPool* pTaskPool = (TaskPool*)m_arg;
			if(pTaskPool != nullptr) {

				while(!pTaskPool->m_isStopped) {
					CallableBase* task = pTaskPool->PopTask();
					printf("Received task with priority: %d\n", task->Priority());
					printf("Processing task within: %u(ms)\n", 1000*task->Priority());
					boost::this_thread::sleep_for(boost::chrono::milliseconds(1000*task->Priority()));
				}
			}
		}
	};

	class ThreadMonitorTask: public CallableBase {
	public:
		ThreadMonitorTask(): CallableBase() {}
		ThreadMonitorTask(void* arg, CallablePriority priority = CALLABLE_PRIORITY_NORMAL): CallableBase(arg, priority) {}
		virtual ~ThreadMonitorTask() {}
		virtual void operator()() {
			TaskPool* pTaskPool = (TaskPool*)m_arg;
			if(pTaskPool != nullptr) {

				while(!pTaskPool->m_isStopped) {

					// TODO Double check

					//puts("Monitoring threads map ....");
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
	inline void Run(CallableBase* task);
	inline bool Stopped() const { return m_isStopped; }
	void PushTask(CallableBase* task);
	CallableBase* PopTask();

private:
	void CreateAndStartThread();

private:
	unsigned int m_maxThreads;
	boost::atomic<unsigned int> m_numRunningThreads;
	boost::atomic_bool m_isStopped;

	TASK_LIST m_taskQueue;
	THREAD_LIST m_runningThreadsMap;
	WorkerThread m_threadMonitoring;
	SynchSuite m_synchSuite;
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

	TASK_LIST::iterator it1 = m_taskQueue.begin();
	for(; it1 != m_taskQueue.end(); ++it1) {
		delete (*it1);
		(*it1) = nullptr;
	}
}

inline void TaskPool::Start() {

	if (m_isStopped) {
		m_isStopped = false; // start or restart task pool
		CreateAndStartThread();

		ThreadMonitorTask* monitorTask = new ThreadMonitorTask(this);
		m_threadMonitoring.SetCallable(monitorTask);
		m_threadMonitoring.Start();
		std::cout << "[Started] m_threadMonitoring ID= " << m_threadMonitoring.GetThreadId() << "\n";
	}
}

void TaskPool::Stop() {

	m_isStopped = true;

	// TODO Signal the waiting threads
	m_synchSuite.cvTaskQueue.notify_all();

	std::cout << "Thread: " << m_threadMonitoring.GetThreadId() << " stopped\n";
	m_threadMonitoring.Stop();

	THREAD_LIST::iterator it = m_runningThreadsMap.begin();
	for(; it != m_runningThreadsMap.end(); ++it) {
		std::cout << "Thread: " << (*it)->GetThreadId() << " stopped\n";
		(*it)->Stop();
	}
}

inline void TaskPool::Run(CallableBase* task) {

	if(!m_isStopped) {
		PushTask(task);
	}
}

void TaskPool::PushTask(CallableBase* task) {

	// check and start a thread in order to wait the incoming task
	if(m_numRunningThreads.load() < m_maxThreads) {
		CreateAndStartThread();
	}

	{
		boost::lock_guard<boost::mutex> guard(m_synchSuite.mtxTaskQueue);
		m_taskQueue.push_back(task);
		m_synchSuite.cvTaskQueue.notify_one();
	}
}

CallableBase* TaskPool::PopTask() {

	CallableBase* pTask = nullptr;
	{
		boost::unique_lock<boost::mutex> lock(m_synchSuite.mtxTaskQueue);
		/* Do not use while loop to check the condition, the thread callback 'GetTask' will do that */
		if(m_taskQueue.empty()) {
			puts("Wait for task ...");
			m_synchSuite.cvTaskQueue.wait(lock);
		}

		// Double check to avoid the fake notifications
		if(m_taskQueue.empty()) {
			lock.unlock();
			return pTask;
		}

		pTask = m_taskQueue.front();
		m_taskQueue.pop_front();
	}
	return pTask;
}

void TaskPool::CreateAndStartThread() {

	// protect the whole transaction utilize lock_guard
	if(!m_isStopped) {
		WorkerThread* thr = new WorkerThread(THREAD_PRIORITY_ABOVE_NORMAL, /*auto-run=*/false);
		GetTask* getTask = new GetTask(this);
		thr->SetCallable(getTask);
		(void)thr->Start();

		// TODO Leak ???
		//boost::shared_ptr<WorkerThread> thr(new WorkerThread(THREAD_PRIORITY_ABOVE_NORMAL, /*auto-run=*/false));
		//boost::shared_ptr<WorkerTask> w(new WorkerTask(this));
		//thr->SetCallableObj(w.get());

		{
			boost::lock_guard<boost::mutex> guard(m_synchSuite.mtxThreadsMap);
			std::cout << "[Started] thr ID= " << thr->GetThreadId() << "\n";
			m_runningThreadsMap.push_back(thr);
			std::sort(m_runningThreadsMap.begin(), m_runningThreadsMap.end(), ThreadStateCompare<WorkerThread>());
		}
		m_numRunningThreads++;
		printf("m_numRunningThreads: %u\n", m_numRunningThreads.load());
	}
}

extern TaskPool gTaskPool;

#endif /* THREAD_TASKPOOL_HPP_ */

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
	//typedef std::pair<WorkerThread, ThreadState> THR_STATE_PAIR;
	typedef std::vector<WorkerThread*> THREAD_LIST;

	template<typename T>
	class ThreadStateCompare {
	public:
		bool operator()(const T* const t1, const T* const t2) {
			return StateLess(t1->get()->GetThreadState(), t2->get()->GetThreadState());
		}
		bool operator()(const T* const t, ThreadState state) {
			return StateLess(t->get()->GetThreadState(), state);
		}
		bool operator()(ThreadState state, const T* const t) {
			return StateLess(t->get()->GetThreadState(), state);
		}
	private:
		bool StateLess(ThreadState state1, ThreadState state2) const {
			return (state1 < state2);
		}
	};

	template<typename T>
	class abc {

	public:
		bool operator()(T* t1, T* t2) {
			return (t1->get()->GetThreadState() < t2->get()->GetThreadState());
		}
	};

	typedef struct Synchable {
		boost::timed_mutex mtx;
		boost::condition_variable cond_val;
	} Synchable;

	class WorkerTask: public CallableBase {
	public:
		WorkerTask(): CallableBase() {}
		WorkerTask(void* arg): CallableBase(arg) {}
		virtual ~WorkerTask() { puts("~WT"); }
		virtual void operator()() {
			TaskPool* pTaskPool = (TaskPool*)m_arg;
			if(pTaskPool != nullptr) {
				while(!pTaskPool->m_isStopped) {
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
			if(!pTaskPool->m_isStopped) {
				puts("Monitoring ....");
				boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
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
	bool m_isInitialized;

	PTASK_LIST m_TaskQueue;
	THREAD_LIST m_runningThreadsMap;
	BThread m_threadMonitoring;
	Synchable m_synchAble;
};


TaskPool::TaskPool()
: m_maxThreads((unsigned int) boost::thread::hardware_concurrency())
, m_isStopped(true)
, m_numRunningThreads(0)
, m_isInitialized(false) {
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

	m_isInitialized = ret;
	return m_isInitialized;
}

TaskPool::~TaskPool() {

	puts("~TP");
	THREAD_LIST::iterator it = m_runningThreadsMap.begin();
	/*
	for(; it != m_runningThreadsMap.end(); ++it) {
		if((*it) != nullptr) {
			delete (*it);
			(*it) = nullptr;
		}
	}
	*/
}

inline void TaskPool::Start() {

	if (m_isStopped) {
		m_isStopped = false; // start or restart task pool
		StartThread();
	}
}

void TaskPool::Stop() {

	m_isStopped = true;
	THREAD_LIST::iterator it = m_runningThreadsMap.begin();
	for(; it != m_runningThreadsMap.end(); ++it) {
		(*it)->Stop();
	}
}

void TaskPool::Run(CallableBase* task) {
}

void TaskPool::TaskEnQueue(CallableBase* task) {
}

CallableBase* TaskPool::TaskDeQueue() {

	return nullptr;
}

void TaskPool::StartThread() {

	// protect the whole transaction utilize lock_guard
	boost::lock_guard<boost::timed_mutex> guard(m_synchAble.mtx);
	//WorkerThread* thr = new WorkerThread(THREAD_PRIORITY_ABOVE_NORMAL, /*auto-run=*/false);
	boost::shared_ptr<WorkerThread> thr(new WorkerThread(THREAD_PRIORITY_ABOVE_NORMAL, /*auto-run=*/false));
	boost::shared_ptr<WorkerTask> w(new WorkerTask(this));
	thr->SetCallableObj(w.get());

	if(thr->Start()) {
		std::cout << "[Started] Thread ID= " << thr->GetThreadId() << "\n";
		m_runningThreadsMap.push_back(thr.get());
		/*std::sort(m_runningThreadsMap.begin(), m_runningThreadsMap.end(),
				abc<boost::shared_ptr<WorkerThread> >());*/
		m_numRunningThreads++;
	}
}

extern TaskPool gTaskPool;

#endif /* THREAD_TASKPOOL_HPP_ */

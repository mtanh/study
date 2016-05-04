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

#include "../common/defines.hpp"
#include "WorkerThread.hpp"

#define ERROR(str) \
	fprintf(stderr, (str)); \
	fprintf(stderr, "\n");

//class TaskPool<CallableBase, WorkerThread>;

/*template<typename CallableTask = CallableBase,
		typename ThreadPolicy = WorkerThread>*/
class TaskPool: public boost::noncopyable {

	typedef boost::ptr_deque</*CallableTask*/CallableBase> PTASK_LIST;
	typedef typename PTASK_LIST::iterator PTASK_ITER;
	typedef boost::fusion::pair<BThreadId, ThreadState> THRID_PAIR;
	typedef boost::container::vector<THRID_PAIR> THREAD_STATE_MAP;

	typedef struct Synchable {
		boost::timed_mutex mtx;
		boost::condition_variable cond_val;
	} Synchable;

	class WorkerTask: public CallableBase {

		public:
			WorkerTask(): CallableBase() {}
			WorkerTask(void* arg): CallableBase(arg) {}
			virtual ~WorkerTask() {}

			virtual void operator()() {
				TaskPool* pTaskPool = (TaskPool*) m_arg;
				if (pTaskPool != nullptr) {
					while (!pTaskPool->m_isStopped) {
						puts("Monitoring task queue and pop task ....");
					}
				}
			}
		};

public:
	TaskPool();
	~TaskPool();

	bool Init(unsigned int maxThreadNum =
			(unsigned int) boost::thread::hardware_concurrency());
	void Start();
	void Stop();
	void Run(/*CallableTask**/CallableBase* task);
	inline bool Stopped() const {
		return m_isStopped;
	}

	void TaskEnQueue(/*CallableTask**/CallableBase* task);
	/*CallableTask**/CallableBase* TaskDeQueue();

private:
	void StartWorkerThread();

private:
	unsigned int m_maxThreads;
	int m_numRunningThreads;
	bool m_isStopped;
	bool m_isInitialized;

	PTASK_LIST m_TaskQueue;
	THREAD_STATE_MAP m_runningThreadsMap;
	Synchable m_synchAble;
};

extern TaskPool gTaskPool;

/*template<typename CallableTask = CallableBase,
		typename ThreadPolicy = WorkerThread>*/
TaskPool::TaskPool() :
		m_maxThreads((unsigned int) boost::thread::hardware_concurrency()), m_isStopped(
				true), m_numRunningThreads(0), m_isInitialized(false) {
}

/*template<typename CallableTask = CallableBase,
		typename ThreadPolicy = WorkerThread>*/
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

/*template<typename CallableTask = CallableBase,
		typename ThreadPolicy = WorkerThread>*/
TaskPool::~TaskPool() {

}

/*template<typename CallableTask = CallableBase,
		typename ThreadPolicy = WorkerThread>*/
inline void TaskPool::Start() {

	if (m_isStopped) {
		m_isStopped = false; // start or restart task pool
		WHICHFUNC

		WorkerThread thr(THREAD_PRIORITY_ABOVE_NORMAL, false /*auto-run*/);
		//CallableTask* wt = new WorkerTask((void*) this);
		thr.SetCallableObj(new WorkerTask(this));
		thr.Start();

		std::cout << "Thread ID: " << thr.GetThreadId() << "\n";
	}
}

/*template<typename CallableTask = CallableBase,
		typename ThreadPolicy = WorkerThread>*/
void TaskPool::Stop() {

}

/*template<typename CallableTask = CallableBase,
		typename ThreadPolicy = WorkerThread>*/
void TaskPool::Run(/*CallableTask**/CallableBase* task) {
}

/*template<typename CallableTask = CallableBase,
		typename ThreadPolicy = WorkerThread>*/
inline void TaskPool::TaskEnQueue(/*CallableTask**/CallableBase* task) {
}

/*template<typename CallableTask = CallableBase,
		typename ThreadPolicy = WorkerThread>*/
inline /*CallableTask**/CallableBase* TaskPool::TaskDeQueue() {
}

/*template<typename CallableTask = CallableBase,
		typename ThreadPolicy = WorkerThread>*/
inline void TaskPool::StartWorkerThread() {
}

#endif /* THREAD_TASKPOOL_HPP_ */

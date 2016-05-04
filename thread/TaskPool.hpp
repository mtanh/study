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

//class TaskPool<CallableBase, WorkerThread>;

/*template<typename CallableTask = CallableBase,
 typename ThreadPolicy = WorkerThread>*/
class TaskPool: public boost::noncopyable {

	typedef boost::ptr_deque</*CallableTask*/CallableBase> PTASK_LIST;
	typedef typename PTASK_LIST::iterator PTASK_ITER;
	typedef std::pair<BThreadId, ThreadState> THR_STATE_PAIR;
	typedef std::vector<THR_STATE_PAIR> THREAD_STATE_MAP;

	typedef struct ThreadStateCompare {
		bool operator()(const THR_STATE_PAIR& pair1,
				const THR_STATE_PAIR& pair2) {
			return StateLess(pair1.second, pair2.second);
		}
		bool operator()(const THR_STATE_PAIR& pair,
						const THR_STATE_PAIR::second_type& state) {
			return StateLess(pair.second, state);
		}
		bool operator()(const THR_STATE_PAIR::second_type& state,
						const THR_STATE_PAIR& pair) {
			return StateLess(state, pair.second);
		}
	private:
		bool StateLess(const THR_STATE_PAIR::second_type& state1,
				const THR_STATE_PAIR::second_type& state2) const {
			return (state1 < state2);
		}
	} ThreadStateCompare;

	typedef struct Synchable {
		boost::timed_mutex mtx;
		boost::condition_variable cond_val;
	} Synchable;

	class WorkerTask: public CallableBase {

	public:
		WorkerTask() :
				CallableBase() {
		}
		WorkerTask(void* arg) :
				CallableBase(arg) {
		}
		virtual ~WorkerTask() {
		}

		virtual void operator()() {
			TaskPool* pTaskPool = (TaskPool*) m_arg;
			if (pTaskPool != nullptr) {
				while (!pTaskPool->m_isStopped) {
					puts("Monitoring task queue and pop task ....");
					boost::this_thread::sleep_for(
							boost::chrono::milliseconds(10000));
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
	void StartThread();

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

		StartThread();
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
inline/*CallableTask**/CallableBase* TaskPool::TaskDeQueue() {

	return nullptr;
}

/*template<typename CallableTask = CallableBase,
 typename ThreadPolicy = WorkerThread>*/
inline void TaskPool::StartThread() {

	WorkerThread thr(THREAD_PRIORITY_ABOVE_NORMAL, /*auto-run=*/false);
	thr.SetCallableObj(new WorkerTask(this));
	std::cout << "Thread ID: " << thr.GetThreadId() << "\n";
	thr.Start();
	std::cout << "Thread ID: " << thr.GetThreadId() << "\n";

	THR_STATE_PAIR thr_state_pair = std::make_pair(thr.GetThreadId(),
			THREAD_STATE_RUNNING);
	m_runningThreadsMap.push_back(thr_state_pair);
	std::sort(m_runningThreadsMap.begin(), m_runningThreadsMap.end(), ThreadStateCompare());
}

#endif /* THREAD_TASKPOOL_HPP_ */

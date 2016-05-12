/*
 * test_main.cxx
 *
 *  Created on: Apr 30, 2016
 *      Author: anhmt
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdlib.h>
#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <limits>
#include <sys/mman.h>
#include <iostream>
#include <string>
#include <signal.h>
#include <semaphore.h>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/container/vector.hpp>
#include <boost/container/list.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/thread/locks.hpp>
#include <boost/type.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

#include "TaskPool.hpp"

LocalTaskPool gTaskPool;

class ATask: public CallableBase {
public:
	ATask(): CallableBase() {}
	ATask(void* arg, CallablePriority priority = CALLABLE_PRIORITY_NORMAL): CallableBase(arg, priority) {}
	virtual ~ATask() {}
	void operator()() {

	}
};

class ThreadSem: boost::noncopyable {

public:
	ThreadSem() {}
	~ThreadSem() {}

	void Init(int c) { counter = c; }

	void Wait() {
		boost::unique_lock<boost::mutex> lock(mtx);
		while(counter < 0) {
			cond.wait(lock);
		}
		counter--;
	}

	void Post() {
		boost::unique_lock<boost::mutex> lock(mtx);
		counter++;
		cond.notify_all();
	}

private:
	int counter;
	boost::condition_variable cond;
	boost::mutex mtx;
};

typedef struct rw_lock_t {
	int reader;
	ThreadSem sem;
	boost::mutex mtx;
} rw_lock_t;

void InitRWLock(rw_lock_t* rw_lock) {
	if(rw_lock != NULL) {
		rw_lock->reader = 0;
		rw_lock->sem.Init(/*num_of_writer=*/1);
	}
}

void ReadLockAcquire(rw_lock_t* rw_lock) {
	assert(rw_lock != NULL);
	boost::lock_guard<boost::mutex> lock(rw_lock->mtx);
	rw_lock->reader++;
	if(1 == rw_lock->reader) {
		rw_lock->sem.Wait();
	}
}

void ReadLockRelease(rw_lock_t* rw_lock) {
	assert(rw_lock != NULL);
	boost::lock_guard<boost::mutex> lock(rw_lock->mtx);
	rw_lock->reader--;
	if(0 == rw_lock->reader) {
		rw_lock->sem.Post();
	}
}

void WriteLockAcquire(rw_lock_t* rw_lock) {
	assert(rw_lock != NULL);
	rw_lock->sem.Wait();
}

void WriteLockRelease(rw_lock_t* rw_lock) {
	assert(rw_lock != NULL);
	rw_lock->sem.Post();
}

int main(int argc, char *argv[]) {

	//gTaskPool.Init(2);
	gTaskPool.Start();

	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_HIGHEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_BELOW_NORMAL));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_BELOW_NORMAL));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_HIGHEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_HIGHEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));

	/*
	sem_t job_queue_count;
	sem_init (&job_queue_count, 0, 0);
	sem_wait (&job_queue_count);

	using namespace boost::interprocess;
	shared_memory_object shdmem{open_or_create, "Boost", read_write};
	  shdmem.truncate(1024);
	  std::cout << shdmem.get_name() << '\n';
	  offset_t size;
	  if (shdmem.get_size(size))
	    std::cout << size << '\n';
	*/

	/*
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	WHICHLINE;
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	WHICHLINE;
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_BELOW_NORMAL));
	WHICHLINE;
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_HIGHEST));
	WHICHLINE;
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	WHICHLINE;
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	WHICHLINE;
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_BELOW_NORMAL));
	WHICHLINE;
	*/

	//boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
	while(1) {
	}

	gTaskPool.Stop();
	return (EXIT_SUCCESS);
}

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

void f1() {
	static boost::thread_specific_ptr<int> tls1;
	if(!tls1.get()) {
		tls1.reset(new int(1));
		std::cout << &tls1 << "\n";
		std::cout << *tls1 << "\n";
	}
}

void f2() {
	static boost::thread_specific_ptr<int> tls;
	if(!tls.get()) {
		tls.reset(new int(2));
		std::cout << &tls << "\n";
		std::cout << *tls << "\n";
	}
}

void cleaner(int* val) {
	return;
}

void f111() {
	boost::thread_specific_ptr<int> tmp(cleaner);
	if(!tmp.get()) {
		int a = 10;
		tmp.reset(&a);
	}
}

struct CallableSt {

	typedef struct thread_spec_data {
		boost::thread::id id;
	} thread_spec_data;
	boost::thread_specific_ptr<thread_spec_data> thread_spec_ptr_;

	void operator()() {
		if(thread_spec_ptr_.get() != NULL) {
			thread_spec_data data;
			data.id = boost::this_thread::get_id();
			thread_spec_ptr_.reset(&data);
			std::cout << "Thread ID: " << thread_spec_ptr_->id << "\n";
		}
	}

};

void thread()
{
	typedef struct thread_spec_data {
		boost::thread::id id;
	} thread_spec_data;
	boost::thread_specific_ptr<thread_spec_data> thread_spec_ptr_;

	try
	{
		if(thread_spec_ptr_.get() == NULL) {
			thread_spec_data data;
			data.id = boost::this_thread::get_id();
			thread_spec_ptr_.reset(&data);
			std::cout << "Thread ID: " << thread_spec_ptr_->id << "\n";
		}
	}
	catch (boost::thread_interrupted&) {}
}

int main(int argc, char *argv[]) {

	boost::thread t{thread};
	//t.interrupt();
	t.join();

	return (EXIT_SUCCESS);
}

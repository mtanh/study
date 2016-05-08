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
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/container/vector.hpp>
#include <boost/container/list.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/thread/locks.hpp>
#include <boost/type.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

//#include "WriteWorker.hpp"
#include "WorkerThread.hpp"
#include "TaskPool.hpp"

TaskPool gTaskPool;

class ATask: public CallableBase {
public:
	ATask(): CallableBase() {}
	ATask(void* arg, CallablePriority priority = CALLABLE_PRIORITY_NORMAL): CallableBase(arg, priority) {}
	virtual ~ATask() {}
	void operator()() {

	}
};

int main(int argc, char *argv[]) {

	gTaskPool.Init(3);
	gTaskPool.Start();

	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_HIGHEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_BELOW_NORMAL));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_HIGHEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_BELOW_NORMAL));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_HIGHEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_BELOW_NORMAL));


	//boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
	while(1) {

	}

	gTaskPool.Stop();

	/*
	boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_ABOVE_NORMAL));
	boost::this_thread::sleep_for(boost::chrono::milliseconds(3500));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_HIGHEST));
	*/

	/*
	void (*prev_handler)(int);
	prev_handler = signal (SIGINT, my_handler);
	*/

	/*
	puts("Here");
	puts("Here");
	puts("Here");
	puts("Here");
	puts("Here");
	*/

	//boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
	/*
	WriteWorker<Writeable> a;
	a.Init();
	boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
	a.Stop();

	boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
	a.Start();
	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	a.Stop();
	*/

	/*
	TaskPool<CallableBase> gThrMgr;
	gThrMgr.Start();

	WorkerThread w;
	Writeable* wa = new Writeable();
	wa->SetArg(&gThrMgr);
	w.SetCallableObj(wa);
	w.Start();
	boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
	w.Stop();
	*/

	/*
	WorkerThread w;
	w.Start();
	std::cout << w.GetThreadId() << "\n";

	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	w.Stop();
	std::cout << w.GetThreadId() << "\n";

	boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
	w.Start();
	std::cout << w.GetThreadId() << "\n";
	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	w.Stop();
	std::cout << w.GetThreadId() << "\n";
	*/

//	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
//
//	(void)a.Start();
//	boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
//	a.Stop();
//	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
//
//	(void)a.Start();
//	boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
//	a.Stop();
//	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
//
//	(void)a.Start();
//	boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
//	a.Stop();
//	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
//
//	(void)a.Start();
//	boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
//	a.Stop();
//	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
//
//	(void)a.Start();
//	boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
//	a.Stop();
//	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	/*
	boost::ptr_vector<WorkerThread> threadGroup;
	threadGroup.push_back(new WriteWorker());
	threadGroup.push_back(new WriteWorker());

	boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
	boost::ptr_vector<WorkerThread>::iterator iter = threadGroup.begin();
	for (; iter != threadGroup.end(); ++iter) {
		(*iter).Stop();
	}
	*/

	//boost::scoped_thread<boost::interrupt_and_join_if_joinable> th (boost::ref (f1));

	/*
	 funcntor1 f1;
	 boost::thread_attributes atts;
	 atts.set_stack_size(4096*10);

	 boost::thread th;
	 try
	 {
	 boost::thread tmp (atts, boost::ref (f1));
	 th.swap (tmp);

	 if (th.joinable())
	 {
	 main_thread = pthread_self();
	 th.join();
	 }

	 //boost::this_thread::sleep (boost::posix_time::seconds (2));
	 //th.interrupt();
	 }
	 catch (boost::thread_interrupted& e)
	 {
	 puts ("In catch");

	 if (th.joinable())
	 {
	 puts ("Joined");
	 main_thread = pthread_self();
	 th.join();
	 }
	 }

	 //boost::thread::native_handle_type type = th.native_handle();

	 //assert (!pthread_equal (child_thread, main_thread));
	 puts ("Done");
	 */

	return (EXIT_SUCCESS);
}

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
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/container/vector.hpp>
#include <boost/container/list.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/thread/locks.hpp>
#include <boost/type.hpp>

//#include "WriteWorker.hpp"
#include "WorkerThread.hpp"
#include "WriteAble.hpp"
#include "TaskMgr.hpp"

struct animal: public boost::intrusive::list_base_hook<> {
	std::string name;
	int legs;
	animal(std::string n, int l) :
			name { boost::move(n) }, legs { l } {
	}
};

/*
typedef boost::intrusive::list<animal> animal_list;
static animal_list animals;

static void f1() {
	animal a1 { "cat", 4 };
	animal a2 { "shark", 0 };
	animal a3 { "spider", 8 };

	animals.push_back(a1);
	animals.push_back(a2);
	animals.push_back(a3);
}
*/

int main(int argc, char *argv[]) {

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

	TaskMgr<CallableBase> gThrMgr;
	gThrMgr.Start();

	WorkerThread w;
	Writeable* wa = new Writeable();
	wa->SetArg(&gThrMgr);
	w.SetCallableObj(wa);
	w.Start();
	boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
	w.Stop();

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

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

	gTaskPool.Init(2);
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
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_LOWEST));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_BELOW_NORMAL));
	gTaskPool.Run(new ATask(nullptr, CALLABLE_PRIORITY_HIGHEST));

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

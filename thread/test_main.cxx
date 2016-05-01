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
#include <boost/container/vector.hpp>

#include "writeworker.hpp"

int main (int argc, char *argv[])
{

	WriteWorker w;
	boost::this_thread::sleep_for (boost::chrono::milliseconds (1000));
	w.Stop ();

	/*
	boost::container::vector <WorkerThread*> threadGroup;
	threadGroup.push_back (new WriteWorker ());
	//threadGroup.push_back (new WriteWorker ());

	boost::container::vector <WorkerThread*>::iterator iter = threadGroup.begin();
	for (; iter != threadGroup.end(); ++iter)
	{
		(*iter)->Stop();
		(*iter)->Join();
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

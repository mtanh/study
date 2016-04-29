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

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

typedef enum { True, False } Boolean;
#define WHICHFUNC \
	fprintf (stderr, "%s\n", __FUNCTION__);

template <typename T>
class ThreadGuard
{
public:
	ThreadGuard (T& _th)
	: thrRef (_th)
	{
	}

	~ThreadGuard ()
	{
		thrRef.Join();
	}

private:
	T& thrRef;
};

//template <class Interrupt = boost::join_if_joinable>
class Thread: public boost::noncopyable
{
	typedef void (Thread::*ThreadProc) (void);

public:
	enum ThreadState { Running, Spending, Stopping, Stopped };

	Thread ()
	: m_thrproc (nullptr)
	, m_arg (nullptr)
	, m_state (Stopped)
	{
	}

	virtual ~Thread ()
	{
		/*
		Interrupt itr;
		itr (m_thr);
		*/
		//Join();
	}

	void Join ()
	{
		if (m_thr.joinable())
		{
			m_thr.interrupt();
			m_thr.join();
		}
	}

	void ThreadProcess ()
	{
		try
		{
			PrivateThreadProc();
		}
		catch (boost::thread_interrupted& ei)
		{
			fprintf (stderr, "Thread interrupted\n");
			Join();
		}
		catch (boost::thread_exception& ex)
		{
			fprintf (stderr, "%s\n", ex.what());
			Join();
		}
	}

	void Start ()
	{
		if (m_state != Running)
		{
			m_thrproc = &Thread::ThreadProcess;
			m_thr = boost::thread (m_thrproc, this);

			// TODO ThreadGuard ???

			m_state = Running;
		}
	}

	void Stop ()
	{
		if (m_state != Stopping)
		{
			m_state = Stopping;
		}
	}

	const ThreadState GetThreadState () const
	{
		return m_state;
	}

protected:
	ThreadState m_state;

private:
	virtual void PrivateThreadProc () = 0;

private:
	boost::thread m_thr;
	ThreadProc m_thrproc;
	void* m_arg;
};

class AThread: public Thread
{
public:
	AThread ()
	: Thread ()
	{
	}

	virtual ~AThread ()
	{
	}

protected:
	virtual void PrivateThreadProc ()
	{
		while (m_state == Running)
		{
			WHICHFUNC;
		}
	}

};

static void f1 ()
{
	while (1)
	{
		WHICHFUNC;
	}
}

int main (int argc, char *argv[])
{
	AThread th;
	th.Start();
	ThreadGuard<Thread> thrguard (th);

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

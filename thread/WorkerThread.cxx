/*
 * worker_thread.cxx
 *
 *  Created on: Apr 30, 2016
 *      Author: anhmt
 */

#include "WorkerThread.hpp"

#include "../common/defines.hpp"

WorkerThread::WorkerThread(ThreadPriority thrPriority, bool autoStart)
: m_threadState(THREAD_STATE_STOPPED)
, m_threadPriority(thrPriority)
, m_threadProc(nullptr)
, m_pCallable(nullptr) {

	if (autoStart) {
		if (!Start()) {
			fprintf(stderr, "WorkerThread ctor failed\n");
		}
	}
}

WorkerThread::~WorkerThread() {

	if(m_pCallable != nullptr) {
		delete m_pCallable;
		m_pCallable = nullptr;
	}
}

bool WorkerThread::Start() {

	do {
		if (Running()) {
			break;
		}

		m_threadState = THREAD_STATE_RUNNING;
		m_threadProc = &WorkerThread::ThreadProc;
		/* thread attributions here */
		boost::thread tmp = boost::thread(m_threadProc, this);
		m_bThread.swap(tmp);

	} while (false);

	return (Running());
}

void WorkerThread::Detach() {

	if (Running()) {
		m_bThread.detach();
	}
}

void WorkerThread::Stop() {

	if (Running()) {
		m_threadState = THREAD_STATE_STOPPED;
	}

	if (m_bThread.joinable()) {
		m_bThread.join();
		//m_bThread.interrupt();
		fprintf(stdout, "State: %s\n", ThreadStateStr[(int) m_threadState]);
	}
}

void WorkerThread::ChangeThreadPriority(ThreadPriority p) {

	m_threadPriority = p;
}

void WorkerThread::PrivateThreadProc(void) {

	if(m_pCallable != nullptr) {
		(*m_pCallable)();
	}
}

void WorkerThread::ThreadProc() {

	try {
		PrivateThreadProc();
	} catch (boost::thread_interrupted& ei) {
		fprintf(stderr, "Thread interrupted\n");
	} catch (boost::thread_exception& ex) {
		fprintf(stderr, "%s\n", ex.what());
	} catch (...) {
		perror("Failed in WorkerThread::ThreadProc");
		Stop();
	}
}

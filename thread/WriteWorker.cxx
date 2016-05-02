/*
 * writeworker.cpp
 *
 *  Created on: Apr 30, 2016
 *      Author: anhmt
 */

#include "WriteWorker.hpp"

#include <iostream>

WriteWorker::WriteWorker() :
		WorkerThread() {
}

WriteWorker::~WriteWorker() {
}

void WriteWorker::PrivateThreadProc() {
	while (Running()) {
		//fprintf (stdout, "State: %s\n", ThreadStateStr[(int)m_threadState]);
		std::cout << boost::this_thread::get_id() << ": "
				<< ThreadStateStr[(int) m_threadState] << "\n";
		boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
	}
}

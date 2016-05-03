/*
 * writeworker.h
 *
 *  Created on: Apr 30, 2016
 *      Author: anhmt
 */

#ifndef THREAD_WRITEWORKER_HPP_
#define THREAD_WRITEWORKER_HPP_

#include "WorkerThread.hpp"

typedef struct Writeable: public CallableBase
{
	Writeable()
	: CallableBase() {}

	Writeable(void* arg)
	: CallableBase(arg) {}

	~Writeable() {}

	void operator()()
	{
		WorkerThread* pWorker = (WorkerThread*)m_arg;
		if(m_arg != nullptr)
		{
			while (pWorker->Running()) {
				std::cout << boost::this_thread::get_id() << ": "
						<< ThreadStateStr[(int)pWorker->GetThreadState()] << "\n";
				boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
			}
		}
	}
};

template <typename Callable>
class WriteWorker: public WorkerThread {
public:
	WriteWorker();
	virtual ~WriteWorker();

private:
	void PrivateThreadProc(void);
	Callable m_callable;
};

template<typename Callable>
inline WriteWorker<Callable>::WriteWorker()
: WorkerThread() {
}

template<typename Callable>
inline WriteWorker<Callable>::~WriteWorker() {
}

template<typename Callable>
inline void WriteWorker<Callable>::PrivateThreadProc(void) {

	while(Running())
	{

	}
}

#endif /* THREAD_WRITEWORKER_HPP_ */

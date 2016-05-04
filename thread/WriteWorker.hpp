/*
 * writeworker.h
 *
 *  Created on: Apr 30, 2016
 *      Author: anhmt
 */

#ifndef THREAD_WRITEWORKER_HPP_
#define THREAD_WRITEWORKER_HPP_

#include "../common/defines.hpp"
#include "WorkerThread.hpp"

typedef unsigned char Byte;

typedef struct Writeable: public CallableBase
{
	Writeable()
	: CallableBase() {}

	Writeable(void* arg)
	: CallableBase(arg) {}

	~Writeable() {}

	void operator()()
	{
		WorkerThread* pWorker = nullptr;
		pWorker = (WorkerThread*)m_arg;
		if(pWorker != nullptr)
		{
			while (pWorker->Running()) {
				std::cout << boost::this_thread::get_id() << ": "
						<< ThreadStateStr[(int)pWorker->GetThreadState()] << "\n";
				boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
			}
		}
	}
};

template <typename CallableType>
class WriteWorker: public WorkerThread {
public:
	WriteWorker();
	virtual ~WriteWorker();

	void Init(unsigned int bufSize);

private:
	void PrivateThreadProc(void);
	Byte* m_privateBuff;
};

template<typename CallableType>
inline WriteWorker<CallableType>::WriteWorker()
: WorkerThread()
, m_privateBuff(nullptr) {
}

template<typename CallableType>
inline WriteWorker<CallableType>::~WriteWorker() {

	if(m_pCallable != nullptr) {
		delete m_pCallable;
		m_pCallable = nullptr;
	}

	if(m_privateBuff != nullptr) {
		delete[] m_privateBuff;
		m_privateBuff = nullptr;
	}
}

template<typename CallableType>
inline void WriteWorker<CallableType>::Init(unsigned int bufSize) {

	if(nullptr == m_pCallable) {
		m_pCallable = new CallableType(this);
	}

	if(nullptr == m_privateBuff) {
		m_privateBuff = new Byte[bufSize];
	}
}

template<typename CallableType>
inline void WriteWorker<CallableType>::PrivateThreadProc(void) {

	if(m_pCallable != nullptr) {
		(*m_pCallable)();
	}
}

#endif /* THREAD_WRITEWORKER_HPP_ */

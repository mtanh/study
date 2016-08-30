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

typedef unsigned char BYTE;
#define MAX_BUFSZ 1024

typedef struct Writeable: public CallableBase {
	Writeable() :
			CallableBase() {
	}

	Writeable(void* arg) :
			CallableBase(arg) {
	}

	~Writeable() {
	}

	void operator()() {
		WorkerThread* pWorker = nullptr;
		pWorker = (WorkerThread*) m_arg;
		if (pWorker != nullptr) {
			while (pWorker->Running()) {
				std::cout << boost::this_thread::get_id() << ": "
						<< ThreadStateStr[(int) pWorker->GetThreadState()]
						<< "\n";
				boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
			}
		}
	}
};

template<typename CallableType, typename WritePolicy>
class WriteWorker: public WorkerThread {
public:
	WriteWorker();
	virtual
	~WriteWorker();

	void
	Init(unsigned int bufSize = MAX_BUFSZ, const WritePolicy& writePolicy);

private:
	void
	PrivateThreadProc(void);
	BYTE* m_privateBuff;
	WritePolicy* m_writePolicy;
};

template<typename CallableType, typename WritePolicy>
WriteWorker<CallableType, WritePolicy>::WriteWorker() :
		WorkerThread(), m_privateBuff(nullptr), m_writePolicy(nullptr) {
}

template<typename CallableType, typename WritePolicy>
WriteWorker<CallableType, WritePolicy>::~WriteWorker() {

	if (m_pCallable != nullptr) {
		delete m_pCallable;
		m_pCallable = nullptr;
	}

	if (m_privateBuff != nullptr) {
		delete[] m_privateBuff;
		m_privateBuff = nullptr;
	}
}

template<typename CallableType, typename WritePolicy>
void WriteWorker<CallableType, WritePolicy>::Init(unsigned int bufSize,
		const WritePolicy& writePolicy) {

	if (nullptr == m_pCallable) {
		m_pCallable = new CallableType(this);
	}

	if (nullptr == m_privateBuff) {
		m_privateBuff = new BYTE[bufSize];
	}

	if (writePolicy != nullptr) {
		m_writePolicy = writePolicy;
	}
}

template<typename CallableType, typename WritePolicy>
void WriteWorker<CallableType, WritePolicy>::PrivateThreadProc(void) {

	if (m_pCallable != nullptr) {
		(*m_pCallable)();
	}
}

#endif /* THREAD_WRITEWORKER_HPP_ */

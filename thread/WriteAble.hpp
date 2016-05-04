/*
 * WriteAble.hpp
 *
 *  Created on: May 4, 2016
 *      Author: anh.ma
 */

#ifndef THREAD_WRITEABLE_HPP_
#define THREAD_WRITEABLE_HPP_

#include "../common/defines.hpp"
#include "TaskMgr.hpp"
#include "WorkerThread.hpp"

typedef unsigned char BYTE;
#define MAX_BUFSZ 1024

class Writeable: public CallableBase
{
public:
	Writeable()
	: CallableBase() {}

	Writeable(void* arg)
	: CallableBase(arg) {}

	~Writeable() {}

	void operator()()
	{
		TaskMgr<CallableBase>* pThrMgr = nullptr;
		pThrMgr = (TaskMgr<CallableBase>*)m_arg;
		if(pThrMgr != nullptr)
		{
			while (!pThrMgr->Stopped()) {
//				std::cout << boost::this_thread::get_id() << ": "
//						<< ThreadStateStr[(int)pWorker->GetThreadState()] << "\n";
				puts ("Wait data ... Write to ...");
				boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
			}
		}
	}
};



#endif /* THREAD_WRITEABLE_HPP_ */

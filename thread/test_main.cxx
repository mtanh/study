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
#include <semaphore.h>
#include <map>
#include <queue>
#include <time.h>
#include <unordered_map>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/container/vector.hpp>
#include <boost/container/deque.hpp>
#include <boost/container/list.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/thread/locks.hpp>
#include <boost/type.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/heap/priority_queue.hpp>
#include <unordered_map>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "TaskPool.hpp"

LocalTaskPool gTaskPool;

class ThreadSem : boost::noncopyable
{
public:
  ThreadSem()
  {
  }
  ~ThreadSem()
  {
  }

  void
  Init(int c)
  {
    counter = c;
  }

  const int
  GetCount() const
  {
    return counter;
  }

  void
  Wait()
  {
    boost::unique_lock<boost::mutex> lock(mtx);
    while (counter == 0)
      {
        cond.wait(lock);
      }
    counter--;
  }

  void
  Post()
  {
    boost::unique_lock<boost::mutex> lock(mtx);
    counter++;
    cond.notify_all();
  }

private:
  int counter;
  boost::condition_variable cond;
  boost::mutex mtx;
};

typedef struct rw_lock_t
{
  int reader;
  ThreadSem sem;
  boost::mutex mtx;
} rw_lock_t;

void
InitRWLock(rw_lock_t* rw_lock)
{
  if (rw_lock != NULL)
    {
      rw_lock->reader = 0;
      rw_lock->sem.Init(/*num_of_writer=*/1);
    }
}

void
ReadLockAcquire(rw_lock_t* rw_lock)
{
  assert(rw_lock != NULL);
  boost::lock_guard<boost::mutex> lock(rw_lock->mtx);
  rw_lock->reader++;
  if (1 == rw_lock->reader)
    {
      rw_lock->sem.Wait();
    }
}

void
ReadLockRelease(rw_lock_t* rw_lock)
{
  assert(rw_lock != NULL);
  boost::lock_guard<boost::mutex> lock(rw_lock->mtx);
  rw_lock->reader--;
  if (0 == rw_lock->reader)
    {
      rw_lock->sem.Post();
    }
}

void
WriteLockAcquire(rw_lock_t* rw_lock)
{
  assert(rw_lock != NULL);
  rw_lock->sem.Wait();
}

void
WriteLockRelease(rw_lock_t* rw_lock)
{
  assert(rw_lock != NULL);
  rw_lock->sem.Post();
}

class ATask : public CallableBase
{
public:
  ATask() :
      CallableBase()
  {
  }
  ATask(void* arg, CallablePriority priority = CALLABLE_PRIORITY_NORMAL) :
      CallableBase(arg, priority)
  {
  }
  virtual
  ~ATask()
  {
  }
  virtual void
  operator()()
  {
    WHICHFUNC
    ;
  }
};

template<typename T>
  struct CAllablePriCompare
  {
  public:
    bool
    operator()(T* t1, T* t2)
    {
      return StateLess(t1->Priority(), t2->Priority());
    }
    bool
    operator()(const T* const t, CallablePriority pri)
    {
      return StateLess(t->Priority(), pri);
    }
    bool
    operator()(CallablePriority pri, const T* const t)
    {
      return StateLess(t->Priority(), pri);
    }
  private:
    bool
    StateLess(CallablePriority state1, CallablePriority state2)
    {
      return (state1 > state2);
    }
  };

ThreadSem gThreadSem;
static std::deque<int> gBuffer;
boost::mutex mtx;

#define MAX 10

void
producer(ThreadSem* thread_sem)
{
  for (;;)
    {
      while (gBuffer.size() == MAX)
        {
          puts("Producer wait ...");
          thread_sem->Wait();
        }

      if (gBuffer.size() < MAX)
        {
          int tmp = (int) rand() % 100;
          gBuffer.push_back(tmp);
          std::cout << "pushed: " << tmp << " " << gBuffer.size() << "\n";
          boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
          thread_sem->Post();
        }
    }
}

void
consumer(ThreadSem* thread_sem)
{
  for (;;)
    {
      while (gBuffer.empty())
        {
          puts("Consumer wait ...");
          thread_sem->Wait();
        }

      boost::unique_lock<boost::mutex> lock(mtx);
      if (!gBuffer.empty())
        {
          std::cout << boost::this_thread::get_id() << " poped: "
              << gBuffer.front() << " " << gBuffer.size() << "\n";
          gBuffer.pop_front();
          boost::this_thread::sleep_for(boost::chrono::milliseconds(5000));
        }
      thread_sem->Post();
      lock.unlock();
    }
}

int
main(int argc, char *argv[])
{
  gThreadSem.Init(MAX);

  boost::thread pro(&producer, &gThreadSem);
  //boost::thread pro2( &producer, &gThreadSem);
  //boost::thread pro3( &producer, &gThreadSem);

  boost::thread cons1(&consumer, &gThreadSem);
  boost::thread cons2(&consumer, &gThreadSem);
  /*boost::thread cons3( &consumer, &gThreadSem);
   boost::thread cons4( &consumer, &gThreadSem);
   boost::thread cons5( &consumer, &gThreadSem);
   boost::thread cons6( &consumer, &gThreadSem);*/

  pro.join();
  //pro2.join();
  //pro3.join();
  cons1.join();
  cons2.join();
  //cons3.join();
  /*cons4.join();
   cons5.join();
   cons6.join();*/

  /*
   srand ( time(NULL) );
   int i = 0;
   */

  /*
   std::unordered_multimap<int, CallableBase*> container;
   for(; i<10000;++i)
   {
   container.insert( std::make_pair( (CallablePriority)rand()%CALLABLE_PRIORITY_COUNT, new ATask(nullptr) ) );
   }
   */

  /*
   std::vector<CallableBase*> container;
   container.reserve(10000);
   for(i < 10000; ++i)
   {
   container.emplace_back(new ATask(nullptr, (CallablePriority)(rand()%CALLABLE_PRIORITY_COUNT)));
   }
   std::sort(container.begin(), container.end(), CAllablePriCompare<CallableBase>());
   */

  /*
   std::priority_queue<CallableBase*, std::vector<CallableBase*>, CAllablePriCompare<CallableBase> > container;
   for(; i < 10000; ++i)
   {
   container.emplace(new ATask(nullptr, (CallablePriority)(rand()%CALLABLE_PRIORITY_COUNT)));
   }
   */

  /*
   gTaskPool.Init(2);
   gTaskPool.Start();

   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_LOWEST) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_HIGHEST) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_ABOVE_NORMAL) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_LOWEST) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_HIGHEST) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_ABOVE_NORMAL) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_LOWEST) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_HIGHEST) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_ABOVE_NORMAL) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_LOWEST) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_HIGHEST) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_ABOVE_NORMAL) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_HIGHEST) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_ABOVE_NORMAL) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_LOWEST) );
   gTaskPool.Run( new ATask(NULL, CALLABLE_PRIORITY_HIGHEST) );

   while(1)
   {
   }
   gTaskPool.Stop();
   */

  return (EXIT_SUCCESS);
}

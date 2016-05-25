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

  void
  Wait()
  {
    boost::unique_lock<boost::mutex> lock(mtx);
    while (counter < 0)
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
      WHICHFUNC;
    }
  };

typedef struct CAllablePriCompare
    {
    public:
      bool
      operator()(CallableBase* t1, CallableBase* t2)
      {
        return StateLess( t1->Priority(), t2->Priority() );
      }
      bool
      operator()(const CallableBase* const t, CallablePriority pri)
      {
        return StateLess(t->Priority(), pri);
      }
      bool
      operator()(CallablePriority pri, const CallableBase* const t)
      {
        return StateLess(t->Priority(), pri);
      }
    private:
      bool
      StateLess(CallablePriority state1, CallablePriority state2)
      {
        return (state1 > state2);
      }
    } CAllablePriCompare;

int
main(int argc, char *argv[])
{
  //srand ( time(NULL) );

  std::unordered_map<int, CallableBase*> mymap = {
       {CALLABLE_PRIORITY_HIGHEST, new ATask(NULL, CALLABLE_PRIORITY_HIGHEST)},
       {CALLABLE_PRIORITY_NORMAL, new ATask(NULL, CALLABLE_PRIORITY_HIGHEST)},
       {CALLABLE_PRIORITY_HIGHEST, new ATask(NULL, CALLABLE_PRIORITY_NORMAL)} };

  std::unordered_map<int, CallableBase*>::const_iterator got = mymap.find (CALLABLE_PRIORITY_HIGHEST);

    if ( got == mymap.end() )
      std::cout << "not found";
    else
      std::cout << got->first << " is " << got->second->Priority();

    std::cout << std::endl;

  /*
  gTaskPool.Init(12);
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

  //std::priority_queue<CallableBase*, std::vector<CallableBase*>, CAllablePriCompare> pq;
  /*
  std::vector<CallableBase*> pq;
  pq.reserve(10000000);
  for(int i = 0; i < 10000000; ++i)
    {
      //pq.emplace(new ATask(nullptr, (CallablePriority)(rand()%CALLABLE_PRIORITY_COUNT)));
      pq.emplace_back(new ATask(nullptr, (CallablePriority)(rand()%CALLABLE_PRIORITY_COUNT)));
    }
  std::sort(pq.begin(), pq.end(), CAllablePriCompare());
  */

  //pq.push(new ATask(nullptr));
  //pq.push(new ATask(nullptr, CALLABLE_PRIORITY_ABOVE_NORMAL));

  /*
  while (!pq.empty())
    {
       CallableBase* p = pq.top();
       std::cout << p->Priority() << "\n";
       pq.pop();
    }
  */

  /*
  while(1)
    {
    }
  gTaskPool.Stop();
  */

  return (EXIT_SUCCESS);
}

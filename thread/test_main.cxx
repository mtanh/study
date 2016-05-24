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

template<typename T>
  class CallablePrioprityCompare
  {
  public:
    bool
    operator()(/*const*/ T* /*const*/ t1, /*const*/ T* /*const*/ t2)
    {
      return PriorityGreat(t1->Priority(), t2->Priority());
    }
    bool
    operator()(const T* const t, CallablePriority priority)
    {
      return PriorityGreat(t->Priority(), priority);
    }
    bool
    operator()(CallablePriority priority, const T* const t)
    {
      return PriorityGreat(t->Priority(), priority);
    }
  private:
    bool
    PriorityGreat(CallablePriority priority1, CallablePriority priority2) const
    {
      return (priority1 < priority2);
    }
  };

class ATask : public CallableBase
  {
  public:
    ATask() :
      CallableBase()
    {
    }
    ATask(char* taskName, void* arg, CallablePriority priority = CALLABLE_PRIORITY_NORMAL) :
      CallableBase(arg, priority)
    , m_taskName(taskName)
    {
    }
    virtual
    ~ATask()
    {
    }
    const char*
    GetName() const
    {
      return m_taskName;
    }
    virtual void
    operator()()
    {
      GetName();
    }

  private:
    char* m_taskName;
  };

int
main(int argc, char *argv[])
{
  /*
  gTaskPool.Init(2);
  gTaskPool.Start();
  */

  boost::heap::priority_queue<CallableBase*, boost::heap::compare<CallablePrioprityCompare<CallableBase> > > pq;
  pq.push(new ATask("A", nullptr, CALLABLE_PRIORITY_HIGHEST));
  pq.push(new ATask("B", nullptr));
  pq.push(new ATask("C", nullptr, CALLABLE_PRIORITY_ABOVE_NORMAL));

  /*
  while(1)
    {

    }
  gTaskPool.Stop();
  */

  return (EXIT_SUCCESS);
}

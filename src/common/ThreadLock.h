#pragma once

#include <pthread.h>
#include <stdio.h>

namespace SmartMet
{


class ThreadLock
{
  public:

    ThreadLock()
    {
      pthread_mutexattr_init(&attr);
      if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK))
        pthread_mutex_init(&threadLock,nullptr);
      else
        pthread_mutex_init(&threadLock,&attr);
    }


    ~ThreadLock()
    {
      pthread_mutex_destroy(&threadLock);
    }


    inline void lock()
    {
      if (pthread_mutex_lock(&threadLock))
        printf("ERROR ThreadLock.h: Possible re-locking trial from the same thread!\n");
    }



    inline bool tryLock()
    {
      if (pthread_mutex_trylock(&threadLock) == 0)
        return true;
      else
        return false;
    }


    inline void unlock()
    {
      pthread_mutex_unlock(&threadLock);
    }

  protected:

    pthread_mutexattr_t attr;
    pthread_mutex_t threadLock;
};


}

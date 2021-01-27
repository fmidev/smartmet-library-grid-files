#pragma once

#include <pthread.h>

namespace SmartMet
{


class ThreadLock
{
  public:

    ThreadLock()
    {
      pthread_mutex_init(&threadLock,nullptr);
    }


    ~ThreadLock()
    {
      pthread_mutex_destroy(&threadLock);
    }


    inline void lock()
    {
      pthread_mutex_lock(&threadLock);
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

    pthread_mutex_t threadLock;
};


}

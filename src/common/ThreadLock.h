#pragma once

#include <pthread.h>

namespace SmartMet
{


class ThreadLock
{
  public:
                    ThreadLock();
    virtual         ~ThreadLock();

    void            lock();
    bool            tryLock();
    void            unlock();

  protected:

    pthread_mutex_t threadLock;
};


}

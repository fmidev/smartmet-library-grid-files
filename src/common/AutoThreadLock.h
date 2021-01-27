#pragma once

#include "ThreadLock.h"

namespace SmartMet
{


class AutoThreadLock
{
  public:
    AutoThreadLock(ThreadLock *threadLock)
    {
      mThreadLock = threadLock;
      mThreadLock->lock();
    }


    ~AutoThreadLock()
    {
      mThreadLock->unlock();
    }

  protected:

    ThreadLock      *mThreadLock;
};


}

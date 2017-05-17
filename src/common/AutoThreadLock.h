#pragma once

#include "ThreadLock.h"

namespace SmartMet
{


class AutoThreadLock
{
  public:
                    AutoThreadLock(ThreadLock *threadLock);
    virtual         ~AutoThreadLock();

  protected:

    ThreadLock      *mThreadLock;
};


}

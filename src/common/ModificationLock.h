#pragma once

#include "ThreadLock.h"
#include <time.h>

// #define TRACE LOCK 1


namespace SmartMet
{


class ModificationLock
{
  public:

    ModificationLock()
    {
      mReadCounter = 0;
      mLockingEnabled = true;
      r1.tv_sec = 0;
      r1.tv_nsec = 100;
    }


    ~ModificationLock()
    {
    }


    inline void readLock()
    {
      if (!mLockingEnabled)
        return;

      mThreadLock.lock();
      mReadCounter++;
      mThreadLock.unlock();
    }


    inline void readUnlock()
    {
      if (!mLockingEnabled)
        return;

      mThreadLock.lock();
      mReadCounter--;
      mThreadLock.unlock();
    }


    inline void writeLock()
    {
      if (!mLockingEnabled)
        return;

      while (true)
      {
        mThreadLock.lock();
        if (mReadCounter == 0)
          return;

        mThreadLock.unlock();
        nanosleep(&r1,&r2);
      }
    }


    inline void writeLockWhenInsideReadLock()
    {
      if (!mLockingEnabled)
        return;

      while (true)
      {
        mThreadLock.lock();
        if (mReadCounter == 1)
          return;

        mThreadLock.unlock();
        nanosleep(&r1,&r2);
      }
    }


    inline void writeUnlock()
    {
      if (!mLockingEnabled)
        return;

      mThreadLock.unlock();
    }


    inline void lock()
    {
      if (!mLockingEnabled)
        return;

      mThreadLock.lock();
    }


    inline void unlock()
    {
      if (!mLockingEnabled)
        return;

      mThreadLock.unlock();
    }

    inline void setLockingEnabled(bool lockingEnabled)
    {
      mLockingEnabled = lockingEnabled;
    }

  protected:

    timespec        r1, r2;
    ThreadLock      mThreadLock;
    int             mReadCounter;
    bool            mLockingEnabled;
};


}

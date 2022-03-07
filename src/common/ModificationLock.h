#pragma once

#include "ThreadLock.h"
#include <time.h>
#include <atomic>



namespace SmartMet
{


class ModificationLock
{
  public:

    ModificationLock()
    {
      mReadCounter = 0;
      mWriteCounter = 0;
      mLockingEnabled = true;

      r1.tv_sec = 0;
      r1.tv_nsec = 100;
    }


    ModificationLock(const ModificationLock& modificationLock)
    {
      mReadCounter = 0;
      mWriteCounter = 0;
      mLockingEnabled = modificationLock.mLockingEnabled;

      r1.tv_sec = 0;
      r1.tv_nsec = 100;
    }


    ~ModificationLock()
    {
    }


    void operator=(const ModificationLock& modificationLock)
    {
      mReadCounter = 0;
      mWriteCounter = 0;
      mLockingEnabled = modificationLock.mLockingEnabled;

      r1.tv_sec = 0;
      r1.tv_nsec = 100;
    }


    inline void readLock()
    {
      if (!mLockingEnabled)
        return;

      if (mWriteCounter > 0)
      {
        mThreadLock.lock();
        mReadCounter++;
        mThreadLock.unlock();
      }
      else
      {
        mReadCounter++;
      }
    }


    inline void readUnlock()
    {
      if (!mLockingEnabled)
        return;

      mReadCounter--;
    }


    inline void writeLock()
    {
      if (!mLockingEnabled)
        return;

      mThreadLock.lock();
      mWriteCounter++;
      while (true)
      {
        if (mReadCounter == (mWriteCounter-1))
          return;

        nanosleep(&r1,&r2);
      }
    }


    inline void writeLockWhenInsideReadLock()
    {
      if (!mLockingEnabled)
        return;

      mWriteCounter++;
      mThreadLock.lock();
      while (true)
      {
        if (mReadCounter == mWriteCounter)
          return;

        nanosleep(&r1,&r2);
      }
    }


    inline void writeUnlock()
    {
      if (!mLockingEnabled)
        return;

      mThreadLock.unlock();
      mWriteCounter--;
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

    timespec          r1, r2;
    ThreadLock        mThreadLock;
    std::atomic<int>  mReadCounter;
    std::atomic<int>  mWriteCounter;
    bool              mLockingEnabled;
};


}

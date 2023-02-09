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
      mReadCounter.store(0);
      mWriteCounter.store(0);
      mLockingEnabled = true;

      r1.tv_sec = 0;
      r1.tv_nsec = 10;
    }


    ModificationLock(const ModificationLock& modificationLock)
    {
      mReadCounter.store(0);
      mWriteCounter.store(0);
      mLockingEnabled = modificationLock.mLockingEnabled;

      r1.tv_sec = 0;
      r1.tv_nsec = 100;
    }


    ~ModificationLock()
    {
    }


    void operator=(const ModificationLock& modificationLock)
    {
      mReadCounter.store(0);
      mWriteCounter.store(0);
      mLockingEnabled = modificationLock.mLockingEnabled;

      r1.tv_sec = 0;
      r1.tv_nsec = 100;
    }


    inline void readLock()
    {
      if (!mLockingEnabled)
        return;

      mReadCounter++;

      if (mWriteCounter.load() > 0)
      {
        mReadCounter--;
        mThreadLock.lock();
        mReadCounter++;
        mThreadLock.unlock();
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
        if (mReadCounter.load() == (mWriteCounter.load()-1))
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
        if (mReadCounter.load() == mWriteCounter.load())
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

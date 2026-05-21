#pragma once

#include "ThreadLock.h"
#include <time.h>
#include <atomic>



namespace SmartMet
{


// ====================================================================================
/*! \brief Reader-writer lock built on a `ThreadLock` and two atomic counters.
 *
 *  Multiple concurrent readers are allowed; a writer blocks until all readers
 *  have released and then holds exclusive access.  The `writeLockWhenInsideReadLock()`
 *  variant is used when a thread already holds a read lock and needs to upgrade to a
 *  write lock without releasing first.  Locking can be disabled globally via
 *  `setLockingEnabled(false)` for single-threaded code paths.
 *
 *  Prefer `AutoReadLock` / `AutoWriteLock` for scoped acquisition. */
// ====================================================================================

class ModificationLock
{
  public:

    /*! \brief Initialise counters and enable locking. */
    ModificationLock()
    {
      mReadCounter.store(0);
      mWriteCounter.store(0);
      mLockingEnabled = true;

      r1.tv_sec = 0;
      r1.tv_nsec = 10;
    }


    /*! \brief Copy constructor — initialises counters to zero (does not copy lock state). */
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


    /*! \brief Assignment — resets counters and copies locking-enabled flag. */
    void operator=(const ModificationLock& modificationLock)
    {
      mReadCounter.store(0);
      mWriteCounter.store(0);
      mLockingEnabled = modificationLock.mLockingEnabled;

      r1.tv_sec = 0;
      r1.tv_nsec = 100;
    }


    /*! \brief Acquire a shared read lock (blocks if a writer is active). */
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


    /*! \brief Release a previously acquired read lock. */
    inline void readUnlock()
    {
      if (!mLockingEnabled)
        return;

      mReadCounter--;
    }


    /*! \brief Acquire an exclusive write lock (spins until all readers have released). */
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


    /*! \brief Upgrade from a read lock to a write lock without releasing first.
     *
     *  The caller must already hold a read lock.  Blocks until all other readers
     *  have released before granting exclusive access. */
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


    /*! \brief Release a previously acquired write lock. */
    inline void writeUnlock()
    {
      if (!mLockingEnabled)
        return;

      mThreadLock.unlock();
      mWriteCounter--;
    }


    /*! \brief Acquire an exclusive mutex lock (bypasses the reader-writer logic). */
    inline void lock()
    {
      if (!mLockingEnabled)
        return;

      mThreadLock.lock();
    }


    /*! \brief Release an exclusively held mutex lock. */
    inline void unlock()
    {
      if (!mLockingEnabled)
        return;

      mThreadLock.unlock();
    }

    /*! \brief Enable or disable all locking operations.
     *  \param[in] lockingEnabled  False disables all lock/unlock calls (single-threaded mode). */
    inline void setLockingEnabled(bool lockingEnabled)
    {
      mLockingEnabled = lockingEnabled;
    }

  protected:

    timespec          r1, r2;         //!< nanosleep interval used while spinning in writeLock()
    ThreadLock        mThreadLock;    //!< Underlying POSIX mutex for exclusive access
    std::atomic<int>  mReadCounter;   //!< Number of active readers
    std::atomic<int>  mWriteCounter;  //!< Non-zero when a writer is waiting or active
    bool              mLockingEnabled; //!< When false all lock/unlock calls are no-ops
};


}

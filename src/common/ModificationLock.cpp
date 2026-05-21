#include "ModificationLock.h"
#include "AutoThreadLock.h"
#include "GeneralFunctions.h"
#include <macgyver/Exception.h>

namespace SmartMet
{

#if 0

/*! \brief Default constructor for ModificationLock. */

ModificationLock::ModificationLock()
{
  try
  {
    mReadCounter = 0;
    mLockingEnabled = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Destructor for ModificationLock. */

ModificationLock::~ModificationLock()
{
}




/*! \brief Acquires a shared read lock. */

void ModificationLock::readLock()
{
  try
  {
    if (!mLockingEnabled)
      return;

    mThreadLock.lock();
    mReadCounter++;
    mThreadLock.unlock();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Releases a previously acquired read lock. */

void ModificationLock::readUnlock()
{
  try
  {
    if (!mLockingEnabled)
      return;

    mThreadLock.lock();
    mReadCounter--;
    mThreadLock.unlock();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Acquires an exclusive write lock, waiting for readers to finish. */

void ModificationLock::writeLock()
{
  try
  {
    if (!mLockingEnabled)
      return;

    while (true)
    {
      mThreadLock.lock();
      if (mReadCounter == 0)
        return;

      mThreadLock.unlock();
      time_usleep(0,100);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Acquires a write lock while the current thread already holds a read lock. */

void ModificationLock::writeLockWhenInsideReadLock()
{
  try
  {
    if (!mLockingEnabled)
      return;

    while (true)
    {
      mThreadLock.lock();
      if (mReadCounter == 1)
        return;

      mThreadLock.unlock();
      time_usleep(0,100);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



/*! \brief Releases a previously acquired write lock. */

void ModificationLock::writeUnlock()
{
  try
  {
    if (!mLockingEnabled)
      return;

    mThreadLock.unlock();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Acquires the underlying mutex. */

void ModificationLock::lock()
{
  try
  {
    if (!mLockingEnabled)
      return;

    mThreadLock.lock();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Releases the underlying mutex. */

void ModificationLock::unlock()
{
  try
  {
    if (!mLockingEnabled)
      return;

    mThreadLock.unlock();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Enables or disables locking behaviour entirely. */

void ModificationLock::setLockingEnabled(bool lockingEnabled)
{
  try
  {
    mLockingEnabled = lockingEnabled;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

#endif

}

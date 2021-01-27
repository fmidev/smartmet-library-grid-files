#include "ModificationLock.h"
#include "AutoThreadLock.h"
#include "GeneralFunctions.h"
#include <macgyver/Exception.h>

namespace SmartMet
{

#if 0

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





ModificationLock::~ModificationLock()
{
}




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

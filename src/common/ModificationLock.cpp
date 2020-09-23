#include "ModificationLock.h"
#include "AutoThreadLock.h"
#include "GeneralFunctions.h"
#include <macgyver/Exception.h>

namespace SmartMet
{



ModificationLock::ModificationLock()
{
  try
  {
#ifdef TRACE_LOCK
    mLine = 0;
#endif
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
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
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





void ModificationLock::readLock(const char *filename,uint line)
{
  try
  {
    if (!mLockingEnabled)
      return;

    mThreadLock.lock();
#ifdef TRACE_LOCK
    mLine = line;
    mFilename = filename;
#endif
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
#ifdef TRACE_LOCK
    if (mLine > 0)
    {
      mFilename = "";
      mLine = 0;
    }
#endif
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



void ModificationLock::writeLock(const char *filename,uint line)
{
  try
  {
    if (!mLockingEnabled)
      return;

    while (true)
    {
      mThreadLock.lock();
      if (mReadCounter == 0)
      {
#ifdef TRACE_LOCK
        mLine = line;
        mFilename = filename;
#endif
        return;
      }

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

#ifdef TRACE_LOCK
    if (mLine > 0)
    {
      mFilename = "";
      mLine = 0;
    }
#endif
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




#ifdef TRACE_LOCK

std::string ModificationLock::getFilename()
{
  try
  {
    return mFilename;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint ModificationLock::getLine()
{
  try
  {
    return mLine;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}
#endif


}

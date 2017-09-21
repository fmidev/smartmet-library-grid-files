#include "ModificationLock.h"
#include "AutoThreadLock.h"
#include "Exception.h"
#include "GeneralFunctions.h"

namespace SmartMet
{


ModificationLock::ModificationLock()
{
  try
  {
    mLine = 0;
    mReadCounter = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





ModificationLock::~ModificationLock()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void ModificationLock::readLock()
{
  try
  {
    mThreadLock.lock();
    mReadCounter++;
    mThreadLock.unlock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void ModificationLock::readUnlock()
{
  try
  {
    mThreadLock.lock();
    mReadCounter--;
    mThreadLock.unlock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void ModificationLock::writeLock()
{
  try
  {
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void ModificationLock::writeLock(const char *filename,uint line)
{
  try
  {
    while (true)
    {
      mThreadLock.lock();
      if (mReadCounter == 0)
      {
        mLine = line;
        mFilename = filename;
        return;
      }

      mThreadLock.unlock();
      time_usleep(0,100);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void ModificationLock::writeUnlock()
{
  try
  {
    mFilename = "";
    mLine = 0;
    mThreadLock.unlock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void ModificationLock::lock()
{
  try
  {
    mThreadLock.lock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




void ModificationLock::unlock()
{
  try
  {
    mThreadLock.unlock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string ModificationLock::getFilename()
{
  try
  {
    return mFilename;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}

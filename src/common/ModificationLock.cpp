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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





ModificationLock::~ModificationLock()
{
  try
  {
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void ModificationLock::readLock(const char *filename,uint line)
{
  try
  {
    mThreadLock.lock();
    mLine = line;
    mFilename = filename;
    mReadCounter++;
    mThreadLock.unlock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void ModificationLock::readUnlock()
{
  try
  {
    mThreadLock.lock();
    if (mLine > 0)
    {
      mFilename = "";
      mLine = 0;
    }
    mReadCounter--;
    mThreadLock.unlock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void ModificationLock::writeUnlock()
{
  try
  {
    if (mLine > 0)
    {
      mFilename = "";
      mLine = 0;
    }
    mThreadLock.unlock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}

#include "AutoThreadLock.h"
#include "Exception.h"


namespace SmartMet
{



AutoThreadLock::AutoThreadLock(ThreadLock *threadLock)
{
  try
  {
    if (threadLock == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'threadLock' parameter points to nullptr!");

    mThreadLock = threadLock;
    mThreadLock->lock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}



AutoThreadLock::~AutoThreadLock()
{
  try
  {
    mThreadLock->unlock();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}


}

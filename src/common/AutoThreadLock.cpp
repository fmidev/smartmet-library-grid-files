#include "AutoThreadLock.h"
#include "Exception.h"


namespace SmartMet
{



AutoThreadLock::AutoThreadLock(ThreadLock *threadLock)
{
  try
  {
    if (threadLock == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'threadLock' parameter points to NULL!");

    mThreadLock = threadLock;
    mThreadLock->lock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}

#include "ThreadLock.h"
#include "Exception.h"


namespace SmartMet
{



ThreadLock::ThreadLock()
{
  try
  {
    pthread_mutex_init(&threadLock,nullptr);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





ThreadLock::~ThreadLock()
{
  try
  {
    pthread_mutex_destroy(&threadLock);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





void ThreadLock::lock()
{
  try
  {
    //printf("LOCK\n");
    pthread_mutex_lock(&threadLock);
    //printf("=> LOCKED\n");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ThreadLock::tryLock()
{
  try
  {
    if (pthread_mutex_trylock(&threadLock) == 0)
      return true;
    else
      return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void ThreadLock::unlock()
{
  try
  {
    //printf("UNLOCK\n");
    pthread_mutex_unlock(&threadLock);
    //printf("=> UNLOCKED\n");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}



}




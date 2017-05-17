#include "ThreadLock.h"
#include "Exception.h"


namespace SmartMet
{



ThreadLock::ThreadLock()
{
  try
  {
    pthread_mutex_init(&threadLock,NULL);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}



}




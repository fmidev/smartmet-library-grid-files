#include "ThreadLock.h"
#include <macgyver/Exception.h>


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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}




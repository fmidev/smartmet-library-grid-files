#include "ThreadLock.h"
#include <macgyver/Exception.h>


namespace SmartMet
{


#if 0

/*! \brief Default constructor that initializes the underlying mutex. */

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





/*! \brief Destructor that destroys the underlying mutex. */

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





/*! \brief Acquires the mutex, blocking until it becomes available. */

void ThreadLock::lock()
{
  try
  {
    pthread_mutex_lock(&threadLock);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Tries to acquire the mutex without blocking. */

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





/*! \brief Releases the held mutex. */

void ThreadLock::unlock()
{
  try
  {
    pthread_mutex_unlock(&threadLock);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

#endif

}




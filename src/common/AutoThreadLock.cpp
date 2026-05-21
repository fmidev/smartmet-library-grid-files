#include "AutoThreadLock.h"
#include <macgyver/Exception.h>


namespace SmartMet
{

#if 0

/*! \brief Constructs an AutoThreadLock and acquires the given thread lock. */

AutoThreadLock::AutoThreadLock(ThreadLock *threadLock)
{
  try
  {
    if (threadLock == nullptr)
      throw Fmi::Exception(BCP,"The 'threadLock' parameter points to nullptr!");

    mThreadLock = threadLock;
    mThreadLock->lock();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



/*! \brief Destructor that releases the held thread lock. */

AutoThreadLock::~AutoThreadLock()
{
  try
  {
    mThreadLock->unlock();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}

#endif
}

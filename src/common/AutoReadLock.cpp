#include "AutoReadLock.h"
#include <macgyver/Exception.h>


namespace SmartMet
{

#if 0

/*! \brief Constructs an AutoReadLock and acquires a read lock on the modification lock. */

AutoReadLock::AutoReadLock(ModificationLock *modificationLock)
{
  try
  {
    mModificationLock = modificationLock;
    mModificationLock->readLock();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Destructor that releases the held read lock. */

AutoReadLock::~AutoReadLock()
{
  try
  {
    mModificationLock->readUnlock();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}

#endif


}

#include "AutoWriteLock.h"
#include <macgyver/Exception.h>


namespace SmartMet
{

#if 0
/*! \brief Constructs an AutoWriteLock and acquires a write lock on the modification lock. */

AutoWriteLock::AutoWriteLock(ModificationLock *modificationLock)
{
  try
  {
    mModificationLock = modificationLock;
    mModificationLock->writeLock();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Destructor that releases the held write lock. */

AutoWriteLock::~AutoWriteLock()
{
  try
  {
    mModificationLock->writeUnlock();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}
#endif

}

#include "AutoWriteLock.h"
#include <macgyver/Exception.h>


namespace SmartMet
{

#if 0
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

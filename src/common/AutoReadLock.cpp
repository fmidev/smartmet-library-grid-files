#include "AutoReadLock.h"
#include <macgyver/Exception.h>


namespace SmartMet
{

#if 0

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

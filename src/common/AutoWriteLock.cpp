#include "AutoWriteLock.h"
#include <macgyver/Exception.h>


namespace SmartMet
{

AutoWriteLock::AutoWriteLock(ModificationLock *modificationLock)
{
  try
  {
    if (modificationLock == nullptr)
      throw Fmi::Exception(BCP,"The 'modificationLock' parameter points to nullptr!");

    mModificationLock = modificationLock;
    mModificationLock->writeLock();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





AutoWriteLock::AutoWriteLock(ModificationLock *modificationLock,const char *filename,uint line)
{
  try
  {
    if (modificationLock == nullptr)
      throw Fmi::Exception(BCP,"The 'modificationLock' parameter points to nullptr!");

    mModificationLock = modificationLock;
    mModificationLock->writeLock(filename,line);
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
    if (mModificationLock != nullptr)
      mModificationLock->writeUnlock();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}


}

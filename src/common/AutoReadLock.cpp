#include "AutoReadLock.h"
#include <macgyver/Exception.h>


namespace SmartMet
{

AutoReadLock::AutoReadLock(ModificationLock *modificationLock)
{
  try
  {
    if (modificationLock == nullptr)
      throw Fmi::Exception(BCP,"The 'modificationLock' parameter points to nullptr!");

    mModificationLock = modificationLock;
    mModificationLock->readLock();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





AutoReadLock::AutoReadLock(ModificationLock *modificationLock,const char *filename,uint line)
{
  try
  {
    if (modificationLock == nullptr)
      throw Fmi::Exception(BCP,"The 'modificationLock' parameter points to nullptr!");

    mModificationLock = modificationLock;
    mModificationLock->readLock(filename,line);
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
    if (mModificationLock != nullptr)
      mModificationLock->readUnlock();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}


}

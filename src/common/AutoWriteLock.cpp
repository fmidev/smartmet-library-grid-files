#include "AutoWriteLock.h"
#include "Exception.h"


namespace SmartMet
{

AutoWriteLock::AutoWriteLock(ModificationLock *modificationLock)
{
  try
  {
    if (modificationLock == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'modificationLock' parameter points to nullptr!");

    mModificationLock = modificationLock;
    mModificationLock->writeLock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





AutoWriteLock::AutoWriteLock(ModificationLock *modificationLock,const char *filename,uint line)
{
  try
  {
    if (modificationLock == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'modificationLock' parameter points to nullptr!");

    mModificationLock = modificationLock;
    mModificationLock->writeLock(filename,line);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}


}

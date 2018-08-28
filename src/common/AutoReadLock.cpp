#include "AutoReadLock.h"
#include "Exception.h"


namespace SmartMet
{

AutoReadLock::AutoReadLock(ModificationLock *modificationLock)
{
  try
  {
    if (modificationLock == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'modificationLock' parameter points to nullptr!");

    mModificationLock = modificationLock;
    mModificationLock->readLock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





AutoReadLock::AutoReadLock(ModificationLock *modificationLock,const char *filename,uint line)
{
  try
  {
    if (modificationLock == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'modificationLock' parameter points to nullptr!");

    mModificationLock = modificationLock;
    mModificationLock->readLock(filename,line);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}


}

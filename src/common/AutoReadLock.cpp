#include "AutoReadLock.h"
#include "Exception.h"


namespace SmartMet
{

AutoReadLock::AutoReadLock(ModificationLock *modificationLock)
{
  try
  {
    if (modificationLock == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'modificationLock' parameter points to NULL!");

    mModificationLock = modificationLock;
    mModificationLock->readLock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


AutoReadLock::~AutoReadLock()
{
  try
  {
    if (mModificationLock != NULL)
      mModificationLock->readUnlock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


}

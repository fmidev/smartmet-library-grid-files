#include "AutoWriteLock.h"
#include "Exception.h"


namespace SmartMet
{

AutoWriteLock::AutoWriteLock(ModificationLock *modificationLock)
{
  try
  {
    if (modificationLock == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'modificationLock' parameter points to NULL!");

    mModificationLock = modificationLock;
    mModificationLock->writeLock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





AutoWriteLock::AutoWriteLock(ModificationLock *modificationLock,const char *filename,uint line)
{
  try
  {
    if (modificationLock == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'modificationLock' parameter points to NULL!");

    mModificationLock = modificationLock;
    mModificationLock->writeLock(filename,line);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





AutoWriteLock::~AutoWriteLock()
{
  try
  {
    if (mModificationLock != NULL)
      mModificationLock->writeUnlock();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


}

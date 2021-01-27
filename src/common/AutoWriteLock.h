#pragma once

#include "ModificationLock.h"

namespace SmartMet
{


class AutoWriteLock
{
  public:
    AutoWriteLock(ModificationLock *modificationLock)
    {
      mModificationLock = modificationLock;
      mModificationLock->writeLock();
    }


    ~AutoWriteLock()
    {
      mModificationLock->writeUnlock();
    }

  protected:

    ModificationLock  *mModificationLock;
};


}

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
      if (mModificationLock)
        mModificationLock->writeLock();
    }


    ~AutoWriteLock()
    {
      if (mModificationLock)
        mModificationLock->writeUnlock();
    }

  protected:

    ModificationLock  *mModificationLock;
};


}

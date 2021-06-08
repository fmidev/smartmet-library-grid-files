#pragma once

#include "ModificationLock.h"

namespace SmartMet
{


class AutoReadLock
{
  public:
    AutoReadLock(ModificationLock *modificationLock)
    {
      mModificationLock = modificationLock;
      if (mModificationLock)
        mModificationLock->readLock();
    }


    ~AutoReadLock()
    {
      if (mModificationLock)
        mModificationLock->readUnlock();
    }

  protected:

    ModificationLock  *mModificationLock;
};


}

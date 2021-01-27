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
      mModificationLock->readLock();
    }


    ~AutoReadLock()
    {
      mModificationLock->readUnlock();
    }

  protected:

    ModificationLock  *mModificationLock;
};


}

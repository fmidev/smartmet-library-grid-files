#pragma once

#include "ModificationLock.h"

namespace SmartMet
{


class AutoReadLock
{
  public:
                      AutoReadLock(ModificationLock *modificationLock);
    virtual           ~AutoReadLock();

  protected:

    ModificationLock  *mModificationLock;
};


}

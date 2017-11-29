#pragma once

#include "ModificationLock.h"

namespace SmartMet
{


class AutoReadLock
{
  public:
                      AutoReadLock(ModificationLock *modificationLock);
                      AutoReadLock(ModificationLock *modificationLock,const char *filename,uint line);
    virtual           ~AutoReadLock();

  protected:

    ModificationLock  *mModificationLock;
};


}

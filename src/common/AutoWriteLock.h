#pragma once

#include "ModificationLock.h"

namespace SmartMet
{


class AutoWriteLock
{
  public:
                      AutoWriteLock(ModificationLock *modificationLock);
                      AutoWriteLock(ModificationLock *modificationLock,const char *filename,uint line);
    virtual           ~AutoWriteLock();

  protected:

    ModificationLock  *mModificationLock;
};


}

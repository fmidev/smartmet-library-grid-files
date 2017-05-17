#pragma once

#include "ThreadLock.h"
#include <string>

namespace SmartMet
{


class ModificationLock
{
  public:
                    ModificationLock();
    virtual         ~ModificationLock();

    void            readLock();
    void            readUnlock();
    void            writeLock();
    void            writeLock(const char *filename,uint line);
    void            writeUnlock();
    void            lock();
    void            unlock();

    std::string     getFilename();
    uint            getLine();

  protected:

    ThreadLock      mThreadLock;
    int             mReadCounter;
    std::string     mFilename;
    uint            mLine;
};


}

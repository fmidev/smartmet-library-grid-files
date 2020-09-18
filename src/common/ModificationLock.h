#pragma once

#include "ThreadLock.h"
#include <string>

// #define TRACE LOCK 1


namespace SmartMet
{


class ModificationLock
{
  public:
                    ModificationLock();
    virtual         ~ModificationLock();

    void            readLock();
    void            readLock(const char *filename,uint line);
    void            readUnlock();
    void            writeLock();
    void            writeLockWhenInsideReadLock();
    void            writeLock(const char *filename,uint line);
    void            writeUnlock();
    void            lock();
    void            unlock();
    void            setLockingEnabled(bool lockingEnabled);

#ifdef TRACE_LOCK
    std::string     getFilename();
    uint            getLine();
#endif

  protected:

    ThreadLock      mThreadLock;
    int             mReadCounter;
    bool            mLockingEnabled;
#ifdef TRACE_LOCK
    std::string     mFilename;
    uint            mLine;
#endif
};


}

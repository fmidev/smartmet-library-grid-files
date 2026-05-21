#pragma once

#include "ThreadLock.h"

namespace SmartMet
{


// ====================================================================================
/*! \brief RAII guard that acquires a `ThreadLock` on construction and releases it on
 *  destruction.  Unlike `AutoReadLock`/`AutoWriteLock` this targets the simpler
 *  exclusive `ThreadLock` without reader-writer semantics. */
// ====================================================================================

class AutoThreadLock
{
  public:
    /*! \brief Acquire \p threadLock.
     *  \param[in] threadLock  Mutex to lock; must not be nullptr. */
    AutoThreadLock(ThreadLock *threadLock)
    {
      mThreadLock = threadLock;
      mThreadLock->lock();
    }


    ~AutoThreadLock()
    {
      mThreadLock->unlock();
    }

  protected:

    ThreadLock      *mThreadLock; //!< Mutex being guarded
};


}

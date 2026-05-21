#pragma once

#include "ModificationLock.h"

namespace SmartMet
{


// ====================================================================================
/*! \brief RAII guard that acquires an exclusive write lock on construction and releases
 *  it on destruction.  Pass a pointer to a `ModificationLock`; nullptr is safe (no-op). */
// ====================================================================================

class AutoWriteLock
{
  public:
    /*! \brief Acquire a write lock on \p modificationLock.
     *  \param[in] modificationLock  Lock to acquire; nullptr disables the guard. */
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

    ModificationLock  *mModificationLock; //!< Lock being guarded (may be nullptr)
};


}

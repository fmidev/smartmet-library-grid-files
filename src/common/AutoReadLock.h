#pragma once

#include "ModificationLock.h"

namespace SmartMet
{


// ====================================================================================
/*! \brief RAII guard that acquires a shared read lock on construction and releases it
 *  on destruction.  Pass a pointer to a `ModificationLock`; nullptr is safe (no-op). */
// ====================================================================================

class AutoReadLock
{
  public:
    /*! \brief Acquire a read lock on \p modificationLock.
     *  \param[in] modificationLock  Lock to acquire; nullptr disables the guard. */
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

    ModificationLock  *mModificationLock; //!< Lock being guarded (may be nullptr)
};


}

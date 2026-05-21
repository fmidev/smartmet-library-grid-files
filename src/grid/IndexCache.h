#pragma once

#include "Typedefs.h"
#include "../common/ModificationLock.h"
#include "../common/AutoWriteLock.h"
#include "../common/AutoReadLock.h"

#include <vector>


namespace SmartMet
{
namespace GRID
{


// ====================================================================================
/*! \brief Thread-safe LRU cache mapping a 64-bit hash to an index vector.
 *
 *  Used to cache pre-computed grid-point index mappings so that repeated
 *  coordinate lookups avoid redundant computation. */
// ====================================================================================

class IndexCache
{
  public:
              IndexCache();
    virtual   ~IndexCache();

    /*! \brief Store an index vector in the cache under the given hash key.
     *  \param[in] hash        64-bit hash key identifying the index set.
     *  \param[in] indexVector The index vector to cache. */
    void      addIndexVector(Int64 hash,T::IndexVector& indexVector);

    /*! \brief Retrieve a cached index vector by hash key.
     *  \param[in]  hash        64-bit hash key.
     *  \param[out] indexVector Populated with the cached vector if found.
     *  \return True if the vector was found in the cache. */
    bool      getIndexVector(Int64 hash,T::IndexVector& indexVector);

    /*! \brief Check whether an index vector exists in the cache.
     *  \param[in] hash  64-bit hash key.
     *  \return True if an entry exists for the given hash. */
    bool      findIndexVector(Int64 hash);

    /*! \brief Retrieve a single index value from a cached vector.
     *  \param[in]  hash   64-bit hash key.
     *  \param[in]  pos    Position within the cached index vector.
     *  \param[out] index  The retrieved index value.
     *  \return True if the entry was found and pos is in range. */
    bool      getIndex(Int64 hash,uint pos,int& index);

    /*! \brief Return the cache slot index whose hash is closest to the given hash.
     *  \param[in] hash  64-bit hash key.
     *  \return Cache slot index, or -1 if the cache is empty. */
    int       getClosestIndexByHash(Int64 hash);

    /*! \brief Same as getClosestIndexByHash but without acquiring the lock.
     *  \param[in] hash  64-bit hash key.
     *  \return Cache slot index, or -1 if the cache is empty. */
    int       getClosestIndexByHashNoLock(Int64 hash);

  protected:

    void      removeOldest();

    std::vector<T::IndexVector> mVector;          //!< Cached index vectors
    std::vector<Int64>          mHashVector;       //!< Hash key for each cached entry
    std::vector<time_t>         mTimeVector;       //!< Insertion/access timestamps for LRU eviction
    ModificationLock            mModificationLock; //!< Reader/writer lock protecting the cache
    uint                        mMaxSize;          //!< Maximum number of entries before eviction

};


extern IndexCache indexCache;

}
}

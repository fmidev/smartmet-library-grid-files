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


class IndexCache
{
  public:
              IndexCache();
    virtual   ~IndexCache();

    void      addIndexVector(Int64 hash,T::IndexVector& indexVector);
    bool      getIndexVector(Int64 hash,T::IndexVector& indexVector);
    bool      findIndexVector(Int64 hash);
    bool      getIndex(Int64 hash,uint pos,int& index);
    int       getClosestIndexByHash(Int64 hash);
    int       getClosestIndexByHashNoLock(Int64 hash);

  protected:

    void      removeOldest();

    std::vector<T::IndexVector> mVector;
    std::vector<Int64>      mHashVector;
    std::vector<time_t>         mTimeVector;
    ModificationLock            mModificationLock;
    uint                        mMaxSize;

};


extern IndexCache indexCache;

}
}

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

    void      addIndexVector(long long hash,T::IndexVector& indexVector);
    bool      getIndexVector(long long hash,T::IndexVector& indexVector);
    bool      findIndexVector(long long hash);
    bool      getIndex(long long hash,uint pos,int& index);
    int       getClosestIndexByHash(long long hash);
    int       getClosestIndexByHashNoLock(long long hash);

  protected:

    void      removeOldest();

    std::vector<T::IndexVector> mVector;
    std::vector<long long>      mHashVector;
    std::vector<time_t>         mTimeVector;
    ModificationLock            mModificationLock;
    uint                        mMaxSize;

};


extern IndexCache indexCache;

}
}

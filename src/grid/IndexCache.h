#pragma once

#include "Typedefs.h"
#include "../common/ThreadLock.h"

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
    bool      getIndex(long long hash,uint pos,int& index);
    int       getClosestIndexByHash(long long hash);
    int       getClosestIndexByHashNoLock(long long hash);

  protected:

    void      removeOldest();

    std::vector<T::IndexVector> mVector;
    std::vector<long long>      mHashVector;
    std::vector<time_t>         mTimeVector;
    ThreadLock                  mThreadLock;
    uint                        mMaxSize;

};


extern IndexCache indexCache;

}
}

#include "IndexCache.h"
#include <macgyver/Exception.h>
#include "../common/AutoThreadLock.h"



namespace SmartMet
{
namespace GRID
{

IndexCache indexCache;


IndexCache::IndexCache()
{
  try
  {
    mMaxSize = 500;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





IndexCache::~IndexCache()
{
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





void IndexCache::addIndexVector(long long hash,T::IndexVector& indexVector)
{
  try
  {
    AutoWriteLock lock(&mModificationLock);

    if (mHashVector.size() == 0)
    {
      mHashVector.emplace_back(hash);
      mVector.emplace_back(indexVector);
      mTimeVector.emplace_back(time(nullptr));
      return;
    }

    int sz = C_INT(mHashVector.size());
    int idx = getClosestIndexByHashNoLock(hash);
    if (idx >= 0  &&  idx < sz  &&  mHashVector[idx] == hash)
      return;  // Already in cache

    if (idx < 0)
    {
      mHashVector.insert(mHashVector.begin(),hash);
      mTimeVector.insert(mTimeVector.begin(),time(nullptr));
      mVector.insert(mVector.begin(),indexVector);
      return;
    }

    if (idx >= C_INT(mHashVector.size()))
    {
      mHashVector.emplace_back(hash);
      mTimeVector.emplace_back(time(nullptr));
      mVector.emplace_back(indexVector);
      return;
    }

    mHashVector.insert(mHashVector.begin()+idx+1,hash);
    mTimeVector.insert(mTimeVector.begin()+idx+1,time(nullptr));
    mVector.insert(mVector.begin()+idx+1,indexVector);

    if (mVector.size() >  mMaxSize)
      removeOldest();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool IndexCache::getIndexVector(long long hash,T::IndexVector& indexVector)
{
  try
  {
    AutoReadLock lock(&mModificationLock);

    int sz = C_INT(mHashVector.size());
    int idx = getClosestIndexByHashNoLock(hash);

    if (idx >= 0  &&  idx < sz  &&  mHashVector[idx] == hash)
    {
      indexVector = mVector[idx];
      mTimeVector[idx] = time(nullptr);
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool IndexCache::findIndexVector(long long hash)
{
  try
  {
    AutoReadLock lock(&mModificationLock);

    int sz = C_INT(mHashVector.size());
    int idx = getClosestIndexByHashNoLock(hash);

    if (idx >= 0  &&  idx < sz  &&  mHashVector[idx] == hash)
    {
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool IndexCache::getIndex(long long hash,uint pos,int& index)
{
  try
  {
    AutoReadLock lock(&mModificationLock);
    int sz = C_INT(mHashVector.size());
    int idx = getClosestIndexByHashNoLock(hash);

    if (idx >= 0  &&  idx < sz  &&  mHashVector[idx] == hash)
    {
      if (mVector[idx].size() > pos)
      {
        index = mVector[idx][pos];
        mTimeVector[idx] = time(nullptr);
        return true;
      }
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




int IndexCache::getClosestIndexByHash(long long hash)
{
  try
  {
    AutoReadLock lock(&mModificationLock);
    return getClosestIndexByHashNoLock(hash);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




int IndexCache::getClosestIndexByHashNoLock(long long hash)
{
  try
  {
    int high = C_INT(mHashVector.size())-1;
    if (high < 0)
      return -1;

    int low = 0;

    while (low <= high)
    {
      int mid = low + (high-low) / 2;
      long long hh = mHashVector[mid];

      if (hash == hh)
        return mid;

      if (hash > hh)
        low = mid + 1;
      else
      if (hash < hh)
        high = mid-1;
    }

    if (low >= high)
      return high;

    while (low >= 0)
    {
      long long hh = mHashVector[low];
      if (hh < hash)
        return low;
      low--;
    }
    return -1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void IndexCache::removeOldest()
{
  try
  {
    uint sz = mTimeVector.size();
    if (sz == 0)
      return;

    time_t oldest = time(nullptr);
    uint idx = 0;

    for (uint t=0; t<sz; t++)
    {
      time_t tt = mTimeVector[t];
      if (tt < oldest)
      {
        oldest = tt;
        idx = t;
      }
    }

    mTimeVector.erase(mTimeVector.begin() + idx);
    mHashVector.erase(mHashVector.begin() + idx);
    mVector.erase(mVector.begin() + idx);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




}
}


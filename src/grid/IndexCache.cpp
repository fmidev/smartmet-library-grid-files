#include "IndexCache.h"
#include "common/Exception.h"
#include "common/AutoThreadLock.h"



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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





IndexCache::~IndexCache()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void IndexCache::addIndexVector(long long hash,T::IndexVector& indexVector)
{
  try
  {
    //printf("IndexCacheSize = %u\n",(uint)mHashVector.size());
    AutoThreadLock lock(&mThreadLock);

    if (mHashVector.size() == 0)
    {
      mHashVector.push_back(hash);
      mVector.push_back(indexVector);
      mTimeVector.push_back(time(0));
      return;
    }

    int sz = (int)mHashVector.size();
    int idx = getClosestIndexByHashNoLock(hash);
    if (idx >= 0  &&  idx < sz  &&  mHashVector[idx] == hash)
      return;  // Already in cache

    if (idx < 0)
    {
      mHashVector.insert(mHashVector.begin(),hash);
      mTimeVector.insert(mTimeVector.begin(),time(0));
      mVector.insert(mVector.begin(),indexVector);
      return;
    }

    if (idx >= (int)mHashVector.size())
    {
      mHashVector.push_back(hash);
      mTimeVector.push_back(time(0));
      mVector.push_back(indexVector);
      return;
    }

    mHashVector.insert(mHashVector.begin()+idx+1,hash);
    mTimeVector.insert(mTimeVector.begin()+idx+1,time(0));
    mVector.insert(mVector.begin()+idx+1,indexVector);

    if ((uint)mVector.size() >  mMaxSize)
      removeOldest();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool IndexCache::getIndexVector(long long hash,T::IndexVector& indexVector)
{
  try
  {
    AutoThreadLock lock(&mThreadLock);

    int sz = (int)mHashVector.size();
    int idx = getClosestIndexByHashNoLock(hash);

    if (idx >= 0  &&  idx < sz  &&  mHashVector[idx] == hash)
    {
      indexVector = mVector[idx];
      mTimeVector[idx] = time(0);
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool IndexCache::getIndex(long long hash,uint pos,int& index)
{
  try
  {
    AutoThreadLock lock(&mThreadLock);
    int sz = (int)mHashVector.size();
    int idx = getClosestIndexByHashNoLock(hash);

    if (idx >= 0  &&  idx < sz  &&  mHashVector[idx] == hash)
    {
      if (mVector[idx].size() > pos)
      {
        index = mVector[idx][pos];
        mTimeVector[idx] = time(0);
        return true;
      }
    }
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




int IndexCache::getClosestIndexByHash(long long hash)
{
  try
  {
    AutoThreadLock lock(&mThreadLock);
    return getClosestIndexByHash(hash);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




int IndexCache::getClosestIndexByHashNoLock(long long hash)
{
  try
  {
    int high = (int)mHashVector.size()-1;
    if (high < 0)
      return -1;

    int low = 0;

    while (low <= high)
    {
      int mid = low + (high-low) / 2;
      //printf(" --  %d < %d < %d\n",low,mid,high);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void IndexCache::removeOldest()
{
  try
  {
    uint sz = (uint)mTimeVector.size();
    if (sz == 0)
      return;

    time_t oldest = time(0);
    uint idx = 0;

    AutoThreadLock lock(&mThreadLock);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




}
}


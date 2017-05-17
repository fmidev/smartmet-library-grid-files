#include "ValueCache.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"


namespace SmartMet
{
namespace GRID
{

/*! \brief This is a global cache object. */
ValueCache valueCache;



/*! \brief The constructor of the class. */

ValueCache::ValueCache()
{
  try
  {
    mKeyCounter = 0;
    mValueList = NULL;
    mKeyList = NULL;
    mAccessTimeList = NULL;
    init(200,20);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The destructor of the class. */

ValueCache::~ValueCache()
{
  try
  {
    clear();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief This method can be used for reinitializing the cache size and the time limit
    for the data removal.

       \param size        The number of value vectors that can be in the cache at the same time.
       \param removeTime  The cached vector can be removed if its last access time is older
                          than the currentTime - removeTime. The remove time is given in seconds.
*/

void ValueCache::init(uint size,uint removeLimit)
{
  try
  {
    clear();
    mKeyCounter = 0;
    mSize = size;
    mRemoveLimit = removeLimit;

    mThreadLock.lock();
    mValueList = new T::ParamValue_vec_ptr[mSize];
    mKeyList = new uint[mSize];
    mAccessTimeList = new time_t[mSize];

    for (uint t=0; t<mSize; t++)
    {
      mKeyList[t] = 0;
      mValueList[t] = NULL;
      mAccessTimeList[t] = 0;
    }

    mThreadLock.unlock();
  }
  catch (...)
  {
    mThreadLock.unlock();
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method clears cached data which is older than 'maxAge' seconds.

       \param maxAge  The maximum allowed data age (in seconds).

*/

void ValueCache::clear(uint maxAge)
{
  try
  {
    time_t currentTime = time(0);
    time_t oldestTime = currentTime - maxAge;

    mThreadLock.lock();
    for (uint t=0; t<mSize; t++)
    {
      if (mAccessTimeList[t] < oldestTime)
      {
        mAccessTimeList[t] = 0;
        mKeyList[t] = 0;

        if (mValueList[t] != NULL)
        {
          delete mValueList[t];
          mValueList[t] = NULL;
        }
      }
    }
    mThreadLock.unlock();
  }
  catch (...)
  {
    mThreadLock.unlock();
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method clears all memory structures used by the cache. */

void ValueCache::clear()
{
  try
  {
    mThreadLock.lock();
    if (mValueList != NULL)
    {
      for (uint t=0; t<mSize; t++)
      {
        if (mValueList[t] != NULL)
        {
          delete mValueList[t];
          mValueList[t] = NULL;
        }
      }
      delete mValueList;
      mValueList = NULL;
    }

    if (mKeyList != NULL)
    {
      delete mKeyList;
      mKeyList = NULL;
    }

    if (mAccessTimeList)
    {
      delete mAccessTimeList;
      mAccessTimeList = NULL;
    }
    mThreadLock.unlock();
  }
  catch (...)
  {
    mThreadLock.unlock();
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




/*! \brief This method adds a new value vector into the cache.

       \param values      The value vector.
       \return            The key to the cached data.
*/

uint ValueCache::addValues(T::ParamValue_vec& values)
{
  try
  {
    time_t currentTime = time(0);
    uint counter = 0;
    uint idx = 0;

    // Lets jump over cached data that has been used during
    // the 'removeLimit' seconds. If all cached data is used
    // in this time frame then we just need to kick out the oldest.

    time_t oldestTime = currentTime;
    uint oldestCounter = 0;

    mThreadLock.lock();
    while (counter < mSize)
    {
      mKeyCounter++;
      idx = mKeyCounter % mSize;

      if ((currentTime - mAccessTimeList[idx]) > mRemoveLimit)
      {
        // The data in this position is so old that it can be removed. Let's
        // exit the loop by increasing the counter size by 10.

        counter = mSize + 10;
      }
      else
      {
        // The data in this position is not very old. However, it still might
        // be the oldest in the cache.

        if (mAccessTimeList[idx] < oldestTime)
        {
          oldestCounter = mKeyCounter;
          oldestTime = mAccessTimeList[idx];
        }
        counter++;
      }
    }

    if (counter == mSize)
    {
      // We should replace the oldest data, because we did not find any data which
      // was older than the 'mRemoveLimit'.

      mKeyCounter = oldestCounter;
      idx = mKeyCounter % mSize;
    }

    if (mValueList[idx] == NULL)
      mValueList[idx] = new T::ParamValue_vec();

    *mValueList[idx] = values;
    mKeyList[idx] = mKeyCounter;
    mAccessTimeList[idx] = time(0);

    mThreadLock.unlock();

    return mKeyCounter;
  }
  catch (...)
  {
    mThreadLock.unlock();
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief This method returns a value vector from the cache according to its cache key.

       \param key         The value vector's cache key.
       \param values      The returned value vector.
       \return            The method returns 'true' if the value vector was found
                          from the cache. Otherwise the method return false.
*/

bool ValueCache::getValues(uint key,T::ParamValue_vec& values)
{
  try
  {
    uint idx = key % mSize;

    mThreadLock.lock();
    if (mValueList[idx] == NULL  ||  mKeyList[idx] != key)
    {
      mThreadLock.unlock();
      return false;
    }

    values = *mValueList[idx];
    mAccessTimeList[idx] = time(0);
    mThreadLock.unlock();
    return true;
  }
  catch (...)
  {
    mThreadLock.unlock();
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief This method returns the minimum and the maximum values stored into
    the cached value vector.

       \param key         The value vector's cache key.
       \param minValue    The minimum value in the value vector.
       \param maxValue    The maxmum value in the value vector.
       \return            The method returns 'true' if the value vector was found
                          from the cache. Otherwise the method return false.
*/

bool ValueCache::getMinAndMaxValues(uint key,T::ParamValue& minValue,T::ParamValue& maxValue)
{
  try
  {
    minValue = 1000000000;
    maxValue = -1000000000;

    uint idx = key % mSize;

    mThreadLock.lock();
    if (mValueList[idx] == NULL  ||  mKeyList[idx] != key)
    {
      mThreadLock.unlock();
      return false;
    }

    T::ParamValue_vec *values = mValueList[idx];
    std::size_t sz = values->size();
    for (std::size_t t=0; t < sz; t++)
    {
      auto val = values->at(t);
      if (val != ParamValueMissing)
      {
        if (val > maxValue)
        {
          maxValue = val;
        }

        if (val < minValue)
        {
          minValue = val;
        }
      }
    }
    mAccessTimeList[idx] = time(0);
    mThreadLock.unlock();

    return true;
  }
  catch (...)
  {
    mThreadLock.unlock();
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


}
}

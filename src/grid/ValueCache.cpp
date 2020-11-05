#include "ValueCache.h"
#include <macgyver/Exception.h>
#include "../common/GeneralDefinitions.h"
#include "../common/GeneralFunctions.h"
#include "../common/AutoThreadLock.h"


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
    mAccessCounter = 0;
    mKeyCounter = 0;
    mValueList = nullptr;
    mKeyList = nullptr;
    mAccessCounterList = nullptr;
    mMaxSize = 1000;
    init(1000,1000);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief This method can be used for reinitializing the cache size and the time limit
    for the data removal.
*/

void ValueCache::init(uint maxLen,UInt64 maxSize)
{
  try
  {
    clear();
    mKeyCounter = 0;
    mMaxLength = maxLen;
    mMaxSize = maxSize;

    AutoWriteLock lock(&mModificationLock);
    mValueList = new T::ParamValue_vec_ptr[mMaxLength];
    mKeyList = new uint[mMaxLength];
    mAccessCounterList = new UInt64[mMaxLength];

    for (uint t=0; t<mMaxLength; t++)
    {
      mKeyList[t] = 0;
      mValueList[t] = nullptr;
      mAccessCounterList[t] = 0;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint ValueCache::getEmpty()
{
  try
  {
    UInt64 ac = mAccessCounter;
    uint idx = 0xFFFFFFFF;

    uint key = mKeyCounter;
    uint k = 0;

    for (uint t=0; t<mMaxLength; t++)
    {
      key++;
      uint i = key % mMaxLength;

      if (mValueList[i] == nullptr)
        return key;

      if (mAccessCounterList[i] < ac)
      {
        ac = mAccessCounterList[i];
        idx = i;
        k = key;
      }
    }

    if (mValueList[idx] != nullptr)
    {
      delete mValueList[idx];
      mValueList[idx] = nullptr;
    }

    return k;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ValueCache::deleteOldest()
{
  try
  {
    UInt64 ac = mAccessCounter;
    uint idx = 0xFFFFFFFF;

    for (uint t=0; t<mMaxLength; t++)
    {
      if (mValueList[t] != nullptr)
      {
        if (mAccessCounterList[t] < ac)
        {
          ac = mAccessCounterList[t];
          idx = t;
        }
      }
    }

    if (mValueList[idx] != nullptr)
    {
      delete mValueList[idx];
      mValueList[idx] = nullptr;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method clears all memory structures used by the cache. */

void ValueCache::clear()
{
  try
  {
    AutoWriteLock lock(&mModificationLock);

    if (mValueList != nullptr)
    {
      for (uint t=0; t<mMaxLength; t++)
      {
        if (mValueList[t] != nullptr)
        {
          delete mValueList[t];
          mValueList[t] = nullptr;
        }
      }
      delete[] mValueList;
      mValueList = nullptr;
    }

    if (mKeyList != nullptr)
    {
      delete[] mKeyList;
      mKeyList = nullptr;
    }

    if (mAccessCounterList)
    {
      delete[] mAccessCounterList;
      mAccessCounterList = nullptr;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




UInt64 ValueCache::getSizeInBytes()
{
  try
  {
    UInt64 memorySize = 0;

    if (mValueList != nullptr)
    {
      for (uint t=0; t<mMaxLength; t++)
      {
        if (mValueList[t] != nullptr)
        {
          UInt64 s = mValueList[t]->size() * sizeof(T::ParamValue);
          memorySize += s;
        }
      }
    }
    return memorySize;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ValueCache::checkLimits()
{
  try
  {
    AutoWriteLock lock(&mModificationLock);

    UInt64 memorySize = getSizeInBytes();

    while (memorySize > (mMaxSize*1000000))
    {
      deleteOldest();
      memorySize = getSizeInBytes();
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    if (values.size() == 0)
      return 0;

    checkLimits();

    AutoWriteLock lock(&mModificationLock);

    mKeyCounter = getEmpty();
    uint idx = mKeyCounter % mMaxLength;

    if (mValueList[idx] == nullptr)
      mValueList[idx] = new T::ParamValue_vec();

    *mValueList[idx] = values;
    mKeyList[idx] = mKeyCounter;
    mAccessCounterList[idx] = mAccessCounter++;

    return mKeyCounter;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    uint idx = key % mMaxLength;

    AutoReadLock lock(&mModificationLock);
    if (mKeyList[idx] != key)
      return false;

    if (mValueList[idx] == nullptr)
      return false;

    values = *mValueList[idx];
    mAccessCounterList[idx] = mAccessCounter++;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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

    uint idx = key % mMaxLength;

    AutoReadLock lock(&mModificationLock);
    if (mValueList[idx] == nullptr  ||  mKeyList[idx] != key)
    {
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
    mAccessCounterList[idx] = mAccessCounter++;

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}

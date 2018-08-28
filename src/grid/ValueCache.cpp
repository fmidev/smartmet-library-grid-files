#include "ValueCache.h"
#include "../common/Exception.h"
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
    mMaxUncompressedSize = 1000;
    init(1000,1000,1000);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief This method can be used for reinitializing the cache size and the time limit
    for the data removal.
*/

void ValueCache::init(uint len,std::size_t maxUncompressedSize,std::size_t maxCompressedSize)
{
  try
  {
    clear();
    mKeyCounter = 0;
    mLength = len;
    mMaxUncompressedSize = maxUncompressedSize;
    mMaxCompressedSize = maxCompressedSize;

    AutoThreadLock lock(&mThreadLock);
    mValueList = new T::ParamValue_vec_ptr[mLength];
    mKeyList = new uint[mLength];
    mAccessCounterList = new UInt64[mLength];

    mCompressedData = new puchar[mLength];
    mCompressedDataSize = new uint[mLength];


    for (uint t=0; t<mLength; t++)
    {
      mKeyList[t] = 0;
      mValueList[t] = nullptr;
      mAccessCounterList[t] = 0;
      mCompressedData[t] = nullptr;
      mCompressedDataSize[t] = 0;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ValueCache::compressOldestUncompressed()
{
  try
  {
    //AutoThreadLock lock(&mThreadLock);
    UInt64 ac = mAccessCounter;
    uint idx = 0xFFFFFFFF;

    for (uint t=0; t<mLength; t++)
    {
      if (mValueList[t] != nullptr  &&  mCompressedData[t] == nullptr  &&  mAccessCounterList[t] < ac)
      {
        ac = mAccessCounterList[t];
        idx = t;
      }
    }

    if (idx != 0xFFFFFFFF)
    {
      return compressCachedValues(idx);
    }
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

    for (uint t=0; t<mLength; t++)
    {
      key++;
      uint i = key % mLength;

      if (mValueList[i] == nullptr  &&  mCompressedData[i] == nullptr)
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

    if (mCompressedData[idx] != nullptr)
    {
      delete mCompressedData[idx];
      mCompressedData[idx] = nullptr;
    }

    return k;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ValueCache::compressOldestCompressed()
{
  try
  {
    //AutoThreadLock lock(&mThreadLock);
    UInt64 ac = mAccessCounter;
    uint idx = 0xFFFFFFFF;

    for (uint t=0; t<mLength; t++)
    {
      if (mCompressedData[t] != nullptr  &&  mValueList[t] != nullptr)
      {
        if (mAccessCounterList[t] < ac)
        {
          ac = mAccessCounterList[t];
          idx = t;
        }
      }
    }

    if (idx != 0xFFFFFFFF)
    {
      delete mValueList[idx];
      mValueList[idx] = nullptr;
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method clears all memory structures used by the cache. */

void ValueCache::clear()
{
  try
  {
    AutoThreadLock lock(&mThreadLock);
    if (mValueList != nullptr)
    {
      for (uint t=0; t<mLength; t++)
      {
        if (mValueList[t] != nullptr)
        {
          delete mValueList[t];
          mValueList[t] = nullptr;
        }
      }
      delete mValueList;
      mValueList = nullptr;
    }

    if (mKeyList != nullptr)
    {
      delete mKeyList;
      mKeyList = nullptr;
    }

    if (mAccessCounterList)
    {
      delete mAccessCounterList;
      mAccessCounterList = nullptr;
    }

    if (mCompressedDataSize != nullptr)
    {
      delete mCompressedDataSize;
      mCompressedDataSize = nullptr;
    }

    if (mCompressedData != nullptr)
    {
      for (uint t=0; t<mLength; t++)
      {
        if (mCompressedData[t] != nullptr)
          delete mCompressedData[t];
      }
      delete mCompressedData;
      mCompressedData = nullptr;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void ValueCache::getSizeInBytes(std::size_t& memorySize,std::size_t& compressedSize)
{
  try
  {
    uint compCount = 0;
    uint ncompCount = 0;

    memorySize = 0;
    compressedSize = 0;

    if (mValueList != nullptr)
    {
      for (uint t=0; t<mLength; t++)
      {
        if (mValueList[t] != nullptr)
        {
          std::size_t s = mValueList[t]->size() * sizeof (T::ParamValue);
          memorySize += s;

          if (mCompressedData[t] != nullptr)
            ncompCount++;
        }

        if (mCompressedData[t] != nullptr)
        {
          compressedSize += mCompressedDataSize[t];
          compCount++;
        }
      }
    }
    //printf("Compressed=%u Uncompressed=%u\n",compCount,ncompCount);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void ValueCache::checkLimits()
{
  try
  {
    AutoThreadLock lock(&mThreadLock);

    std::size_t memorySize = 0;
    std::size_t compressedSize = 0;
    getSizeInBytes(memorySize,compressedSize);

    while (memorySize > (mMaxUncompressedSize*1000000))
    {
      if (!compressOldestUncompressed())
      {
        compressOldestCompressed();
      }
      getSizeInBytes(memorySize,compressedSize);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    checkLimits();

    AutoThreadLock lock(&mThreadLock);

    mKeyCounter = getEmpty();
    uint idx = mKeyCounter % mLength;

    if (mValueList[idx] == nullptr)
      mValueList[idx] = new T::ParamValue_vec();

    *mValueList[idx] = values;
    mKeyList[idx] = mKeyCounter;
    mAccessCounterList[idx] = mAccessCounter++;

    //printf("ACCESS KEY %u (%u)\n",mKeyCounter,mKeyCounter % mLength);
    return mKeyCounter;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    uint idx = key % mLength;

    AutoThreadLock lock(&mThreadLock);
    if (mKeyList[idx] != key)
      return false;

    if (mValueList[idx] == nullptr  &&  mCompressedData[idx] != nullptr)
    {
      decompressCachedValues(idx);
    }

    if (mValueList[idx] == nullptr)
      return false;

    values = *mValueList[idx];
    mAccessCounterList[idx] = mAccessCounter++;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool ValueCache::compressCachedValues(uint index)
{
  try
  {
    if (index >= mLength)
      return false;

    if (mCompressedData[index] != nullptr  ||  mValueList[index] == nullptr)
      return false;

    std::size_t len = mValueList[index]->size();
    uint size = (uint)(len*sizeof(T::ParamValue));

    T::ParamValue data[len];
    uchar compressedData[size];

    for (uint t=0; t<len; t++)
      data[t] = mValueList[index]->at(t);

    uint compressedDataSize = (uint)size;

    int res = compressData(data,size,compressedData,compressedDataSize);
    if (res == 0)
    {
      if (compressedDataSize > 0)
      {
        mCompressedDataSize[index] = compressedDataSize;
        mCompressedData[index] = new uchar[compressedDataSize];
        memcpy(mCompressedData[index],compressedData,compressedDataSize);
        delete mValueList[index];
        mValueList[index] = nullptr;
        return true;
      }
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




bool ValueCache::decompressCachedValues(uint index)
{
  try
  {
    if (index >= mLength)
      return false;

    if (mCompressedData[index] == nullptr)
      return false;

    if (mValueList[index] != nullptr)
      return false;


    T::ParamValue *data = new T::ParamValue[10000000];
    uint decompressedDataSize = 10000000*sizeof(T::ParamValue);

    int res = decompressData(mCompressedData[index],mCompressedDataSize[index],data,decompressedDataSize);
    if (res == 0)
    {
      if (mValueList[index] == nullptr)
        mValueList[index] = new T::ParamValue_vec();

      uint len = decompressedDataSize / sizeof(T::ParamValue);
      for (uint t=0; t<len; t++)
      {
        mValueList[index]->push_back(data[t]);
      }
      delete data;

      //delete mCompressedData[index];
      //mCompressedData[index] = nullptr;
      //mCompressedDataSize[index] = 0;
      mAccessCounterList[index] = mAccessCounter++;
      compressOldestUncompressed();

      return true;
    }

    delete data;
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

    uint idx = key % mLength;

    AutoThreadLock lock(&mThreadLock);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}
}

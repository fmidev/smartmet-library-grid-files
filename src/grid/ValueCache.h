#pragma once

#include <string>
#include <vector>
#include "Typedefs.h"
#include "common/Exception.h"
#include "common/AutoThreadLock.h"
//#include <boost/thread.hpp>

namespace SmartMet
{
namespace GRID
{

// ====================================================================================
/*!
  \brief This class is used for caching grid values. This is usually needed in order
  to guarantee fast data processing.

  The basic idea behind the cache is that when grid values are stored into the cache
  by the "addValues()" method, the current method returns a cache key that can be
  used later to get the cached information. So, instead of saving the actual values
  the caller needs to save only the cache key.

  On the other hand, the caller does not need to fetch all the grid values at the same
  time, because its possible to request values by their index.
*/
// ====================================================================================

typedef unsigned long long UInt64;
typedef unsigned char uchar;
typedef uchar *puchar;


class ValueCache
{
  public:
                ValueCache();
    virtual     ~ValueCache();

    uint        addValues(T::ParamValue_vec& values);
    bool        getValues(uint key,T::ParamValue_vec& values);
    bool        getMinAndMaxValues(uint key,T::ParamValue& minValue,T::ParamValue& maxValue);
    void        init(uint len,std::size_t maxUncompressedSize,std::size_t maxCompressedSize);

  protected:

    void        checkLimits();
    void        clear();
    void        getSizeInBytes(std::size_t& memorySize,std::size_t& compressedSize);
    bool        compressCachedValues(uint index);
    bool        decompressCachedValues(uint index);
    bool        compressOldestUncompressed();
    bool        compressOldestCompressed();
    uint        getEmpty();


    /*! \brief The max number of value vectors that can be stored into the cache. */
    uint        mLength;

    /*! \brief The max size of value vectors expressed in mega bytes. */
    std::size_t mMaxUncompressedSize;
    std::size_t mMaxCompressedSize;

    /*! \brief The counter that is used for generating an access key when a new value vector is stored */
    uint        mKeyCounter;

    /*! \brief An array of the keys used for caching information. */
    uint*       mKeyList;

    puchar*     mCompressedData;
    uint*       mCompressedDataSize;

    /*! \brief An array of the access counters . */
    UInt64*    mAccessCounterList;
    UInt64     mAccessCounter;

    /*! \brief The cached data can be removed if it is not accessed during this time limit (seconds).
        Usually cached data is removed only if the cache is full and there is a need to cache newer data. */
    uint        mRemoveLimit;

    /*! \brief The cached value vectors. */
    T::ParamValue_vec_ptr *mValueList;

    ThreadLock  mThreadLock;

  public:

    /*! \brief This method can be used for fetching a single parameter value from the cache according
        to the cache key and the value index. If the grid values are still in the cache then the requested
        value is returned in the 'value' parameter and the method returns 'true'. However, if the grid
        values are not in the cache anymore then the method returns 'false'. In this case the caller should
        decode grid values again and possible store them to the cache again.

            \param key    The access key to the cached value vector
            \param index  The index of the cached value vector.
            \param value  The returned parameter value.
            \return       The method returns 'true' if the value vector is still in the cache.

     */

    inline bool getValue(uint key,uint index,T::ParamValue& value)
    {
      try
      {
        // The possible location of the cached value vector is "encoded" to the key. I.e when
        // the key is divided by the cache size, the remainder of this division is used as
        // a storage index.

        uint idx = key % mLength;

        AutoThreadLock lock(&mThreadLock);
        if (mKeyList[idx] != key)
        {
          // The value vector is cached with a different key.

          return false;
        }

        if (mValueList[idx] == NULL)
        {
          // The value vector is not cache in the memory.

          return false;
        }


        std::size_t sz = mValueList[idx]->size();
        if (index >= sz)
        {
          SmartMet::Spine::Exception exception(BCP,"Index is out of the range!");
          exception.addParameter("Index",std::to_string(index));
          exception.addParameter("Size",std::to_string(sz));
          throw exception;
        }

        value = mValueList[idx]->at(index);

        // Updating the access time of the current value vector.
        mAccessCounterList[idx] = mAccessCounter++;

        return true;
      }
      catch (...)
      {
        throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
      }
    }



    inline bool getCompressedCacheValue(uint key,uint index,T::ParamValue& value)
    {
      try
      {
        // The possible location of the cached value vector is "encoded" to the key. I.e when
        // the key is divided by the cache size, the remainder of this division is used as
        // a storage index.

        uint idx = key % mLength;

        AutoThreadLock lock(&mThreadLock);
        if (mKeyList[idx] != key)
        {
          // The value vector is cached with a different key.

          return false;
        }

        if (mValueList[idx] == NULL  &&  mCompressedData[idx] != NULL)
          decompressCachedValues(idx);


        if (mValueList[idx] == NULL)
        {
          // The value vector is not cache in the memory.

          return false;
        }


        std::size_t sz = mValueList[idx]->size();
        if (index >= sz)
        {
          SmartMet::Spine::Exception exception(BCP,"Index is out of the range!");
          exception.addParameter("Index",std::to_string(index));
          exception.addParameter("Size",std::to_string(sz));
          throw exception;
        }

        value = mValueList[idx]->at(index);

        // Updating the access time of the current value vector.
        mAccessCounterList[idx] = mAccessCounter++;

        return true;
      }
      catch (...)
      {
        throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
      }
    }
};



extern ValueCache valueCache;

}
}

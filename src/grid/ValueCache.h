#pragma once

#include "Typedefs.h"
#include <macgyver/Exception.h>
#include <macgyver/CacheStats.h>
#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include "../common/GeneralFunctions.h"
#include "../common/AutoReadLock.h"
#include "../common/AutoWriteLock.h"

#include <string>
#include <vector>

namespace SmartMet
{

typedef boost::iostreams::mapped_file_params MappedFileParams;
typedef boost::iostreams::mapped_file MappedFile;

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

#ifndef uchar
  typedef unsigned char uchar;
#endif

typedef uchar *puchar;


class ValueCacheEntry
{
  public:

    ValueCacheEntry()
    {
      mKey = 0;
      mAccessCounter = 0;
      mMappedFile = nullptr;
      mGrid = nullptr;
      mSize = 0;
    }

    ValueCacheEntry(uint key,T::ParamValue_vec& values,const char *fname)
    {
      mKey =  key;
      mAccessCounter = 0;
      mMappedFile = nullptr;
      mSize = values.size();
      if (mSize > 0)
      {
        if (fname)
        {
          mFilename = fname;
          FILE *file = fopen(fname,"w");
          if (!file)
          {
            Fmi::Exception exception(BCP,"Cannot create a cache file!");
            exception.addParameter("Cache file",fname);
            throw exception;
          }

          T::ParamValue *f = &values[0];
          fwrite(f,sizeof(T::ParamValue),mSize,file);
          fclose(file);

          long long fileSize = getFileSize(fname);
          if (fileSize < 0)
          {
            Fmi::Exception exception(BCP,"The file does not exist!");
            exception.addParameter("Filename",fname);
            throw exception;
          }

          if (fileSize == 0)
          {
            Fmi::Exception exception(BCP,"The file size is zero!");
            exception.addParameter("Filename",fname);
            throw exception;
          }

          MappedFileParams params(fname);
          params.flags = boost::iostreams::mapped_file::readonly;
          params.length = fileSize;
          mMappedFile = new MappedFile(params);
          mGrid = (T::ParamValue*)mMappedFile->const_data();
        }
        else
        {
          mGrid = new T::ParamValue[mSize];
          memcpy(mGrid,&values[0],mSize*sizeof(T::ParamValue));
        }
      }
    }

    ~ValueCacheEntry()
    {
      if (mMappedFile)
      {
        mMappedFile->close();
        remove(mFilename.c_str());
        delete mMappedFile;
        mMappedFile = nullptr;
      }
      else
      {
        if (mGrid)
        {
          delete[] mGrid;
          mGrid = nullptr;
        }
      }
    }

    uint               mKey;
    UInt64             mAccessCounter;
    std::string        mFilename;
    MappedFile*        mMappedFile;
    T::ParamValue*     mGrid;
    uint               mSize;
};


typedef ValueCacheEntry* ValueCacheEntry_ptr;


class ValueCache
{
  public:
                ValueCache();
    virtual     ~ValueCache();

    uint        addValues(T::ParamValue_vec& values);
    bool        getValues(uint key,T::ParamValue_vec& values);
    void        deleteValues(uint key);
    bool        getMinAndMaxValues(uint key,T::ParamValue& minValue,T::ParamValue& maxValue);
    void        getCacheStats(Fmi::Cache::CacheStatistics& statistics) const;
    void        init(uint maxLen,UInt64 maxSize);
    void        init(uint maxLen,UInt64 maxSize,bool fileCacheEnabled);
    void        setCacheDir(const char *cacheDir);

  protected:

    void        checkLimits();
    void        clear();
    void        deleteOldest();
    UInt64      getSizeInBytes();
    uint        getEmpty();


    /*! \brief The max number of value vectors that can be stored into the cache. */
    uint        mMaxLength;

    /*! \brief The max size of value vectors expressed in mega bytes. */
    UInt64      mMaxSize;

    /*! \brief The counter that is used for generating an access key when a new value vector is stored */
    uint        mKeyCounter;

    UInt64      mAccessCounter;

    bool        mFileCacheEnabled;

    ValueCacheEntry_ptr*    mEntryList;
    std::string             mCacheDir;
    Fmi::Cache::CacheStats  mCacheStats;

    ModificationLock        mModificationLock;


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

        uint idx = key % mMaxLength;

        AutoReadLock lock(&mModificationLock);
        ValueCacheEntry_ptr entry = mEntryList[idx];

        if (!entry || entry->mKey != key || !entry->mGrid)
        {
          // The value vector is cached with a different key.

          mCacheStats.misses++;
          return false;
        }


        if (index >= entry->mSize)
        {
          Fmi::Exception exception(BCP,"Index is out of the range!");
          exception.addParameter("Index",std::to_string(index));
          exception.addParameter("Size",std::to_string(entry->mSize));
          throw exception;
        }

        value = entry->mGrid[index];

        // Updating the access time of the current value vector.
        entry->mAccessCounter = mAccessCounter++;
        mCacheStats.hits++;

        return true;
      }
      catch (...)
      {
        throw Fmi::Exception(BCP,"Operation failed!",nullptr);
      }
    }

};



extern ValueCache valueCache;

}
}

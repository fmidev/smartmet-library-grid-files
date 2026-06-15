#pragma once

#include "Typedefs.h"
#include <macgyver/Exception.h>
#include <macgyver/CacheStats.h>
#include <macgyver/MappedFile.h>
#include <filesystem>
#include "../common/AttributeNode.h"
#include "../common/GeneralFunctions.h"
#include "../common/AutoReadLock.h"
#include "../common/AutoWriteLock.h"

#include <string>
#include <vector>

namespace SmartMet
{

typedef boost::iostreams::mapped_file_params MappedFileParams;
typedef Fmi::MappedFile MappedFile;

namespace GRID
{

// ====================================================================================
/*! \brief Cache for decoded grid value vectors.
 *
 *  Stores `T::ParamValue_vec` arrays keyed by an opaque integer handle returned by
 *  `addValues()`.  Callers retain the key and retrieve individual values via
 *  `getValue()` or the full vector via `getValues()`.  Eviction is LRU by access
 *  counter and is bounded by both entry count (`maxLen`) and total byte size
 *  (`maxSize`).  An optional file-backed mode writes each entry to a temporary
 *  memory-mapped file, reducing heap pressure for large grids. */
// ====================================================================================

typedef UInt64 UInt64;

#ifndef uchar
  typedef unsigned char uchar;
#endif

typedef uchar *puchar;


// ====================================================================================
/*! \brief Single entry in the ValueCache holding one decoded grid value array.
 *
 *  When a cache directory is set the values are written to a temporary file and
 *  memory-mapped read-only, so the heap is not charged for large grids.  Without
 *  a cache directory the values are held in a heap-allocated array.  The destructor
 *  closes and removes the backing file when the file-backed mode is used. */
// ====================================================================================

class ValueCacheEntry
{
  public:

    /*! \brief Construct an empty (invalid) entry. */
    ValueCacheEntry()
    {
      mKey = 0;
      mAccessCounter = 0;
      mMappedFile = nullptr;
      mGrid = nullptr;
      mSize = 0;
    }

    /*! \brief Construct an entry that stores \p values under \p key.
     *  \param[in] key     Opaque cache key assigned by ValueCache.
     *  \param[in] values  Grid values to store.
     *  \param[in] fname   If non-null, write values to this file and memory-map it;
     *                     otherwise copy values into a heap array. */
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

          Int64 fileSize = getFileSize(fname);
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

    uint               mKey;           //!< Opaque key assigned when the entry was inserted
    UInt64             mAccessCounter; //!< Logical access time; used for LRU eviction
    std::string        mFilename;      //!< Backing file path (non-empty only in file-cache mode)
    MappedFile*        mMappedFile;    //!< Memory-mapped view of the backing file (nullptr in heap mode)
    T::ParamValue*     mGrid;          //!< Pointer to the value array (mapped or heap)
    uint               mSize;         //!< Number of elements in mGrid
};


typedef ValueCacheEntry* ValueCacheEntry_ptr;


// ====================================================================================
/*! \brief Thread-safe LRU cache for decoded grid value vectors.
 *
 *  Decoded `T::ParamValue_vec` arrays are stored by `addValues()`, which returns an
 *  opaque integer key.  Individual values are retrieved with the inline `getValue()`
 *  and full arrays with `getValues()`.  The cache is bounded by both the maximum
 *  number of entries (`maxLen`) and total byte size (`maxSize`); the least-recently
 *  used entry is evicted when either limit is exceeded.  A global instance
 *  `valueCache` is defined at the bottom of this header. */
// ====================================================================================

class ValueCache
{
  public:
                ValueCache();
    virtual     ~ValueCache();

    /*! \brief Store a decoded grid value vector.
     *  \param[in] values  Values to cache.
     *  \return Opaque key for later retrieval; 0 on failure. */
    uint        addValues(T::ParamValue_vec& values);

    /*! \brief Retrieve a complete value vector by key.
     *  \param[in]  key     Key returned by addValues().
     *  \param[out] values  Populated with the cached values.
     *  \return True if the entry is still in the cache; false if it was evicted. */
    bool        getValues(uint key,T::ParamValue_vec& values);

    bool        getValuesByIndexList(uint key,std::vector<uint>& indexList,T::ParamValue_vec& values);

    /*! \brief Remove the entry with the given key from the cache.
     *  \param[in] key  Key returned by addValues(). */
    void        deleteValues(uint key);

    /*! \brief Compute the minimum and maximum of a cached value vector.
     *  \param[in]  key       Key returned by addValues().
     *  \param[out] minValue  Minimum value found (excluding missing values).
     *  \param[out] maxValue  Maximum value found (excluding missing values).
     *  \return True if the entry is still in the cache; false if it was evicted. */
    bool        getMinAndMaxValues(uint key,T::ParamValue& minValue,T::ParamValue& maxValue);

    /*! \brief Fill \p statistics with cache hit/miss counters.
     *  \param[out] statistics  Receives the current cache statistics. */
    void        getCacheStats(Fmi::Cache::CacheStatistics& statistics) const;

    /*! \brief Populate \p parent with an attribute sub-tree describing internal state.
     *  \param[in,out] parent  Attribute node that receives cache state attributes. */
    void        getStateAttributes(std::shared_ptr<T::AttributeNode> parent);

    /*! \brief Initialise the cache with given limits (heap mode).
     *  \param[in] maxLen   Maximum number of entries.
     *  \param[in] maxSize  Maximum total size in megabytes. */
    void        init(uint maxLen,UInt64 maxSize);

    /*! \brief Initialise the cache with given limits and optional file-cache mode.
     *  \param[in] maxLen            Maximum number of entries.
     *  \param[in] maxSize           Maximum total size in megabytes.
     *  \param[in] fileCacheEnabled  If true, values are written to temporary files. */
    void        init(uint maxLen,UInt64 maxSize,bool fileCacheEnabled);

    /*! \brief Set the directory used for temporary backing files (enables file-cache mode).
     *  \param[in] cacheDir  Path to an existing writable directory. */
    void        setCacheDir(const char *cacheDir);

  protected:

    void        checkLimits();
    void        clear();
    void        deleteOldest();
    UInt64      getSizeInBytes();
    uint        getEmpty();


    uint        mMaxLength;          //!< Maximum number of entries allowed in the cache
    UInt64      mMaxSize;            //!< Maximum total size of cached data in megabytes
    uint        mKeyCounter;         //!< Monotonically increasing counter used to generate cache keys
    UInt64      mAccessCounter;      //!< Global access clock; incremented on each cache hit
    bool        mFileCacheEnabled;   //!< True when values are written to temporary backing files
    ValueCacheEntry_ptr*    mEntryList;       //!< Fixed-size array of entry pointers (length = mMaxLength)
    std::string             mCacheDir;        //!< Directory for temporary backing files
    Fmi::Cache::CacheStats  mCacheStats;      //!< Hit/miss counters
    ModificationLock        mModificationLock; //!< Guards concurrent reads and writes


  public:

    /*! \brief Fetch a single value from a cached grid by key and element index.
     *  \param[in]  key    Key returned by addValues().
     *  \param[in]  index  Zero-based element index within the cached vector.
     *  \param[out] value  Receives the requested grid value.
     *  \return True if the entry is still in the cache; false if it was evicted
     *          (caller should re-decode and re-store). */
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

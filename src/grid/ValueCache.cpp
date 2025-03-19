#include "ValueCache.h"
#include "../common/GeneralDefinitions.h"
#include "../common/GeneralFunctions.h"
#include "../common/AutoThreadLock.h"
#include <macgyver/Exception.h>
#include <sys/stat.h>
#include <dirent.h>


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
    mMaxSize = 1000;
    mEntryList = nullptr;
    init(1000,1000);
    mFileCacheEnabled = false;

    mCacheStats.starttime = Fmi::SecondClock::universal_time();
    mCacheStats.maxsize = mMaxSize*1000000;
    mCacheStats.size = 0;
    mCacheStats.inserts = 0;
    mCacheStats.hits = 0;
    mCacheStats.misses = 0;

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
    init(maxLen,maxSize,false);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void ValueCache::init(uint maxLen,UInt64 maxSize,bool fileCacheEnabled)
{
  try
  {
    clear();
    mKeyCounter = 0;
    mMaxLength = maxLen;
    mMaxSize = maxSize;
    mCacheStats.maxsize = mMaxSize*1000000;
    mFileCacheEnabled = fileCacheEnabled;

    AutoWriteLock lock(&mModificationLock);

    mEntryList = new ValueCacheEntry_ptr[mMaxLength];
    for (uint t=0; t<mMaxLength; t++)
      mEntryList[t] = nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ValueCache::setCacheDir(const char *cacheDir)
{
  try
  {
    mCacheDir = cacheDir;
    char fname[200];
    sprintf(fname,"%s/GRID_%08u.dat",mCacheDir.c_str(),mKeyCounter);

    DIR *dp = opendir(cacheDir);
    if (dp == nullptr)
      return;

    bool ind = true;

    while (ind)
    {
      struct dirent *ep = readdir(dp);
      if (ep != nullptr)
      {
        if (ep->d_type == DT_REG)
        {
          if (strncmp(ep->d_name,"GRID_",5) == 0)
          {
            char fullName[2000];
            sprintf(fullName, "%s/%s", cacheDir, ep->d_name);
            remove(fullName);
          }
        }
      }
      else
      {
        ind = false;
      }
    }
    closedir(dp);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void ValueCache::getCacheStats(Fmi::Cache::CacheStatistics& statistics) const
{
  try
  {
    statistics.insert(std::make_pair("Grid-files::gridData_cache", mCacheStats));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ValueCache::getStateAttributes(std::shared_ptr<T::AttributeNode> parent)
{
  try
  {
    if (mFileCacheEnabled)
    {
      parent->addAttribute("Type","filesys");
      parent->addAttribute("Directory",mCacheDir);
    }
    else
      parent->addAttribute("Type","memory");

    parent->addAttribute("Current Size (Mb)",mCacheStats.size / 1000000);
    parent->addAttribute("Max Size (Mb)",mMaxSize);
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

      if (mEntryList[i] == nullptr)
        return key;

      if (mEntryList[i]->mAccessCounter < ac)
      {
        ac = mEntryList[i]->mAccessCounter;
        idx = i;
        k = key;
      }
    }

    if (idx != 0xFFFFFFFF &&  mEntryList[idx] != nullptr)
    {
      mCacheStats.size -= mEntryList[idx]->mSize * sizeof(T::ParamValue);
      delete mEntryList[idx];
      mEntryList[idx] = nullptr;
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
      if (mEntryList[t] != nullptr)
      {
        if (mEntryList[t]->mAccessCounter < ac)
        {
          ac = mEntryList[t]->mAccessCounter;
          idx = t;
        }
      }
    }

    if (idx != 0xFFFFFFFF  &&  mEntryList[idx] != nullptr)
    {
      mCacheStats.size -= mEntryList[idx]->mSize * sizeof(T::ParamValue);
      delete mEntryList[idx];
      mEntryList[idx] = nullptr;
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

    if (mEntryList != nullptr)
    {
      for (uint t=0; t<mMaxLength; t++)
      {
        if (mEntryList[t] != nullptr)
        {
          delete mEntryList[t];
          mEntryList[t] = nullptr;
        }
      }
      delete[] mEntryList;
      mEntryList = nullptr;
    }
    mAccessCounter = 0;
    mKeyCounter = 0;

    mCacheStats.size = 0;
    mCacheStats.inserts = 0;
    mCacheStats.hits = 0;
    mCacheStats.misses = 0;
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

    if (mEntryList != nullptr)
    {
      for (uint t=0; t<mMaxLength; t++)
      {
        if (mEntryList[t] != nullptr)
        {
          memorySize += mEntryList[t]->mSize;
        }
      }
    }
    return memorySize * sizeof(T::ParamValue);
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
    uint sz = values.size();
    if (sz == 0)
      return 0;

    checkLimits();

    AutoWriteLock lock(&mModificationLock);

    mKeyCounter = getEmpty();
    uint idx = mKeyCounter % mMaxLength;

    if (mEntryList[idx])
    {
      mCacheStats.size -= mEntryList[idx]->mSize * sizeof(T::ParamValue);
      delete mEntryList[idx];
      mEntryList[idx] = nullptr;
    }

    if (mFileCacheEnabled)
    {
      char fname[200];
      sprintf(fname,"%s/GRID_%08u.dat",mCacheDir.c_str(),mKeyCounter);
      mEntryList[idx] = new ValueCacheEntry(mKeyCounter,values,fname);
    }
    else
    {
      mEntryList[idx] = new ValueCacheEntry(mKeyCounter,values,nullptr);
    }

    mCacheStats.inserts++;
    mCacheStats.size += mEntryList[idx]->mSize * sizeof(T::ParamValue);
    mEntryList[idx]->mAccessCounter = mAccessCounter++;

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

    ValueCacheEntry_ptr entry = mEntryList[idx];

    if (!entry || entry->mKey != key || !entry->mGrid)
    {
      mCacheStats.misses++;
      return false;
    }

    mCacheStats.hits++;

    uint sz = entry->mSize;
    T::ParamValue *grid = entry->mGrid;

    values.reserve(sz);
    for (std::size_t t=0; t<sz; t++)
      values.emplace_back(grid[t]);

    entry->mAccessCounter = mAccessCounter++;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ValueCache::deleteValues(uint key)
{
  try
  {
    uint idx = key % mMaxLength;

    AutoWriteLock lock(&mModificationLock);
    ValueCacheEntry_ptr entry = mEntryList[idx];

    if (!entry || entry->mKey != key || !entry->mGrid)
      return;

    mCacheStats.size -= entry->mSize * sizeof(T::ParamValue);

    delete mEntryList[idx];
    mEntryList[idx] = nullptr;
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

    ValueCacheEntry_ptr entry = mEntryList[idx];

    if (!entry || entry->mKey != key || !entry->mGrid)
      return false;

    T::ParamValue *values = entry->mGrid;
    std::size_t sz = entry->mSize;
    for (std::size_t t=0; t < sz; t++)
    {
      auto val = values[t];
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
    entry ->mAccessCounter = mAccessCounter++;

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}

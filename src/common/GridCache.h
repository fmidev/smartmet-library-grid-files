#pragma once

// The cache class used for the process-wide caches of the library. ClockCache (CLOCK
// eviction, find() takes only a shared lock) is the default. Defining GRID_FILES_LRU_CACHE
// selects the exact LRU Fmi::Cache::Cache instead, for comparison.

#ifdef GRID_FILES_LRU_CACHE
#include <macgyver/Cache.h>
#else
#include <macgyver/ClockCache.h>
#endif

namespace SmartMet
{

#ifdef GRID_FILES_LRU_CACHE
template <class KeyType, class ValueType>
using GridCache = Fmi::Cache::Cache<KeyType, ValueType>;
#else
template <class KeyType, class ValueType>
using GridCache = Fmi::Cache::ClockCache<KeyType, ValueType>;
#endif

}  // namespace SmartMet

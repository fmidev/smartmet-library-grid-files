#pragma once

#include "Typedefs.h"
#include "ThreadLock.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <map>


#define POINT_CACHE_SIZE 2731


namespace SmartMet
{


typedef std::unordered_map<uint,uint> HitCounter;           //!< grid-index → hit count map
typedef std::map<uint,HitCounter> GeometryHitCounter;       //!< per-geometry hit counter map
typedef std::unordered_map<UInt64,uint> KeyCounter;         //!< arbitrary-key → hit count map
typedef std::multimap<uint,UInt64> TopList;                 //!< count → key sorted top-N list

// ====================================================================================
/*! \brief Thread-safe request counter for tracking data-access hot spots.
 *
 *  Maintains per-key hit counts (arbitrary `UInt64` keys) and per-geometry
 *  grid-index hit counts.  The top-N most requested keys are maintained in a
 *  sorted `TopList` for monitoring and prefetch decisions.  A global instance
 *  `requestCounter` is defined at the bottom of this header. */
// ====================================================================================

class RequestCounter
{
  public:

                        RequestCounter();
    virtual             ~RequestCounter();

    /*! \brief Reset all per-key counters to zero. */
    void                clearCounters();
    /*! \brief Clear the top-N sorted list without resetting per-key counters. */
    void                clearTopIndexes();
    /*! \brief Return the running total of all increment calls. */
    UInt64              getTotalRequests();
    /*! \brief Reset the total request counter to zero. */
    void                resetTotalRequests();

    /*! \brief Serialise all geometry hit counters to a file.
     *  \param[in] filename  Output path. */
    void                saveGeometryHitCounters(const char *filename);

    /*! \brief Load and merge geometry hit counters from a file.
     *  \param[in] filename  Input path. */
    void                loadGeometryHitCounters(const char *filename);

    /*! \brief Increment the hit counter for \p key.
     *  \param[in] key  Arbitrary 64-bit request key. */
    void                incCounter(UInt64 key);

    /*! \brief Increment the hit counter for a grid point.
     *  \param[in] geometryId  Geometry identifier.
     *  \param[in] index       Grid point index within the geometry. */
    void                incGeometryHitCounter(uint geometryId,uint index);

    /*! \brief Return true if counting is currently enabled. */
    bool                isCountingEnabled();

    /*! \brief Return the current hit count for \p key.
     *  \param[in] key  Request key to query.
     *  \return Hit count, or 0 if never seen. */
    uint                getCounter(UInt64 key);

    /*! \brief Return a snapshot of the top-N most-requested keys.
     *  \return Multimap sorted by hit count (highest first). */
    TopList             getTopRequestCounters();

    /*! \brief Return all grid-index hit counts for a geometry.
     *  \param[in] geometryId  Geometry to query.
     *  \return HitCounter map for the geometry. */
    HitCounter          getGeometryHitCounters(uint geometryId);

    /*! \brief Scale all counters by \p multiplier (for decay/aging).
     *  \param[in] multiplier  Factor to multiply each counter by. */
    void                multiplyCounters(double multiplier);

    /*! \brief Enable or disable counting.
     *  \param[in] _enabled  True to enable. */
    void                setCountingEnabled(bool _enabled);

    /*! \brief Rebuild the top-N sorted list from current counters. */
    void                updateTopCounters();

  protected:

    void                setGeometryHitCounter(uint geometryId,uint index,uint count);

    UInt64              mTotalRequests;          //!< Running total of all increments
    TopList             mTopRequestCounters;     //!< Sorted top-N list of (count, key) pairs
    bool                mCountingEnabled;        //!< True when counting is active
    ThreadLock          mThreadLock;             //!< Guards all counter structures
    KeyCounter          mRequestCounters;        //!< Per-key hit counts
    GeometryHitCounter  mGeometryHitCounter;     //!< Per-geometry, per-index hit counts
};


extern RequestCounter requestCounter;


}  // namespace SmartMet


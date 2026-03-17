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


typedef std::unordered_map<uint,uint> HitCounter;
typedef std::map<uint,HitCounter> GeometryHitCounter;
typedef std::unordered_map<UInt64,uint> KeyCounter;
typedef std::multimap<uint,UInt64> TopList;



class RequestCounter
{
  public:

                        RequestCounter();
    virtual             ~RequestCounter();

    void                clearCounters();
    void                clearTopIndexes();
    UInt64              getTotalRequests();
    void                resetTotalRequests();
    void                saveGeometryHitCounters(const char *filename);
    void                loadGeometryHitCounters(const char *filename);
    void                incCounter(UInt64 key);
    void                incGeometryHitCounter(uint geometryId,uint index);
    bool                isCountingEnabled();
    uint                getCounter(UInt64 key);
    TopList             getTopRequestCounters();
    HitCounter          getGeometryHitCounters(uint geometryId);
    void                multiplyCounters(double multiplier);
    void                setCountingEnabled(bool _enabled);
    void                updateTopCounters();

  protected:

    void                setGeometryHitCounter(uint geometryId,uint index,uint count);

    UInt64              mTotalRequests;
    TopList             mTopRequestCounters;
    bool                mCountingEnabled;
    ThreadLock          mThreadLock;
    KeyCounter          mRequestCounters;
    GeometryHitCounter  mGeometryHitCounter;
};


extern RequestCounter requestCounter;


}  // namespace SmartMet


#pragma once

#include "Typedefs.h"
#include "ThreadLock.h"

#include <vector>
#include <string>
#include <map>


#define POINT_CACHE_SIZE 2731


namespace SmartMet
{


typedef std::map<uint,uint> HitCounter;
typedef std::map<uint,HitCounter> GeometryHitCounter;
typedef std::map<ulonglong,uint> KeyCounter;
typedef std::multimap<uint,ulonglong> TopList;



class RequestCounter
{
  public:

                        RequestCounter();
    virtual             ~RequestCounter();

    void                clearCounters();
    void                clearTopIndexes();
    ulonglong           getTotalRequests();
    void                resetTotalRequests();
    void                saveGeometryHitCounters(const char *filename);
    void                loadGeometryHitCounters(const char *filename);
    void                incCounter(ulonglong key);
    void                incGeometryHitCounter(uint geometryId,uint index);
    bool                isCountingEnabled();
    uint                getCounter(ulonglong key);
    TopList             getTopRequestCounters();
    HitCounter          getGeometryHitCounters(uint geometryId);
    void                multiplyCounters(double multiplier);
    void                setCountingEnabled(bool _enabled);
    void                updateTopCounters();

  protected:

    void                setGeometryHitCounter(uint geometryId,uint index,uint count);

    ulonglong           mTotalRequests;
    TopList             mTopRequestCounters;
    bool                mCountingEnabled;
    ThreadLock          mThreadLock;
    KeyCounter          mRequestCounters;
    GeometryHitCounter  mGeometryHitCounter;
};


extern RequestCounter requestCounter;


}  // namespace SmartMet


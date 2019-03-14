#pragma once

#include "Typedefs.h"
#include "ThreadLock.h"

#include <vector>
#include <string>
#include <map>


#define POINT_CACHE_SIZE 2731


namespace SmartMet
{


typedef std::map<ulonglong,std::map<uint,uint>> PointCounter;
typedef std::map<ulonglong,std::vector<uint>> PointIndexList;
typedef std::multimap<uint,ulonglong> KeyCountList;



class RequestCounter
{
  public:

                        RequestCounter();
    virtual             ~RequestCounter();

    void                clearCounters();
    void                clearTopIndexes();
    ulonglong           getTotalRequests();
    void                resetTotalRequests();
    void                saveTopIndexes(const char *filename);
    void                loadTopIndexes(const char *filename);
    void                incCounter(ulonglong key,uint index);
    uint                getCounter(ulonglong key,uint index);
    std::vector<uint>   getTopRequestIndexes(ulonglong key);
    KeyCountList        getTopRequestCounters();
    void                multiplyCounters(double multiplier);
    void                multiplyCounters(ulonglong key,double multiplier);
    void                setCountingEnabled(bool _enabled);
    void                updateTopRequestIndexes();
    void                updateTopRequestIndexes(ulonglong key);

  protected:

    ulonglong           mTotalRequests;
    KeyCountList        mTopRequestCounters;

    bool                mCountingEnabled;
    ThreadLock          mThreadLock;
    PointCounter        mPointRequestCounter;
    PointIndexList      mTopRequestIndex;

};


extern RequestCounter requestCounter;


}  // namespace SmartMet


#pragma once

#include "Typedefs.h"
#include "ThreadLock.h"

#include <vector>
#include <string>
#include <map>


#define POINT_CACHE_SIZE 2731


namespace SmartMet
{


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
    void                saveTopCounters(const char *filename);
    void                loadTopCounters(const char *filename);
    void                incCounter(ulonglong key);
    bool                isCountingEnabled();
    uint                getCounter(ulonglong key);
    TopList             getTopRequestCounters();
    void                multiplyCounters(double multiplier);
    void                setCountingEnabled(bool _enabled);
    void                updateTopCounters();

  protected:

    ulonglong           mTotalRequests;
    TopList             mTopRequestCounters;
    bool                mCountingEnabled;
    ThreadLock          mThreadLock;
    KeyCounter          mRequestCounters;
};


extern RequestCounter requestCounter;


}  // namespace SmartMet


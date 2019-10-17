#include "RequestCounter.h"
#include "AutoThreadLock.h"
#include "ShowFunction.h"
#include "GeneralFunctions.h"
#include "Exception.h"


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{

RequestCounter requestCounter;



RequestCounter::RequestCounter()
{
  FUNCTION_TRACE
  try
  {
    mCountingEnabled = true;
    mTotalRequests = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





RequestCounter::~RequestCounter()
{
}





void RequestCounter::clearCounters()
{
  FUNCTION_TRACE
  try
  {
    AutoThreadLock lock(&mThreadLock);
    mPointRequestCounter.clear();
    mTotalRequests = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RequestCounter::clearTopIndexes()
{
  FUNCTION_TRACE
  try
  {
    AutoThreadLock lock(&mThreadLock);
    mTopRequestIndex.clear();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RequestCounter::multiplyCounters(double multiplier)
{
  FUNCTION_TRACE
  try
  {
    // This method can be used in order make sure that request counters get
    // smaller if they are not used for awhile.


    // Disable the request counting before calling this method.

    if (mCountingEnabled)
      return;

    AutoThreadLock lock(&mThreadLock);

    for (auto it = mPointRequestCounter.begin(); it != mPointRequestCounter.end(); ++it)
    {
      for (auto pp = it->second.begin(); pp != it->second.end(); ++pp)
      {
        pp->second = C_UINT(multiplier * C_DOUBLE(pp->second));
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RequestCounter::multiplyCounters(ulonglong key,double multiplier)
{
  FUNCTION_TRACE
  try
  {
    // This method can be used in order make sure that request counters get
    // smaller if they are not used for awhile.


    // Disable the request counting before calling this method.

    if (mCountingEnabled)
      return;

    AutoThreadLock lock(&mThreadLock);

    auto it = mPointRequestCounter.find(key);

    if (it != mPointRequestCounter.end())
    {
      for (auto pp = it->second.begin(); pp != it->second.end(); ++pp)
      {
        pp->second = C_UINT(multiplier * C_DOUBLE(pp->second));
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RequestCounter::updateTopRequestIndexes()
{
  FUNCTION_TRACE
  try
  {
    // Disable the request counting before calling this method.

    if (mCountingEnabled)
      return;

    uint minRequests = 10;

    AutoThreadLock lock(&mThreadLock);

    mTopRequestCounters.clear();

    for (auto it = mPointRequestCounter.begin(); it != mPointRequestCounter.end(); ++it)
    {
      std::multimap<uint,uint> cnt;
      uint count = 0;

      for (auto pp = it->second.begin(); pp != it->second.end(); ++pp)
      {
        count += pp->second;
        if (pp->second >= minRequests)
          cnt.insert(std::pair<uint,uint>(pp->second,pp->first));
      }

      mTopRequestCounters.insert(std::pair<uint,ulonglong>(count,it->first));

      uint sz = POINT_CACHE_SIZE;
      if (cnt.size() < sz)
        sz = cnt.size();

      auto tt = mTopRequestIndex.find(it->first);
      if (tt == mTopRequestIndex.end())
      {
        std::vector<uint> ivec;
        ivec.reserve(sz);
        uint c = 0;
        for (auto p = cnt.rbegin(); p != cnt.rend()  &&  c < sz; ++p)
        {
          ivec.push_back(p->second);
          c++;
        }
        mTopRequestIndex.insert(std::pair<ulonglong,std::vector<uint>>(it->first,ivec));
      }
      else
      {
        tt->second.clear();
        tt->second.reserve(sz);
        uint c = 0;
        for (auto p = cnt.rbegin(); p != cnt.rend()  &&  c < sz; ++p)
        {
          tt->second.push_back(p->second);
          c++;
        }
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RequestCounter::updateTopRequestIndexes(ulonglong key)
{
  FUNCTION_TRACE
  try
  {
    // Disable the request counting before calling this method.

    if (mCountingEnabled)
      return;

    uint minRequests = 4;

    AutoThreadLock lock(&mThreadLock);

    //std::map<uint,ulonglong> maxIndex;

    auto it = mPointRequestCounter.find(key);

    if (it != mPointRequestCounter.end())
    {
      std::multimap<uint,uint> cnt;
      for (auto pp = it->second.begin(); pp != it->second.end(); ++pp)
      {
        if (pp->second >= minRequests)
          cnt.insert(std::pair<uint,uint>(pp->second,pp->first));
      }

      //if (cnt.rbegin() != cnt.rend())
      //  maxIndex.insert(std::pair<uint,ulonglong>(cnt.rbegin()->first,it->first));

      uint sz = POINT_CACHE_SIZE;
      if (cnt.size() < sz)
        sz = cnt.size();

      auto tt = mTopRequestIndex.find(it->first);
      if (tt == mTopRequestIndex.end())
      {
        std::vector<uint> ivec;
        ivec.reserve(sz);
        uint c = 0;
        for (auto p = cnt.rbegin(); p != cnt.rend()  &&  c < sz; ++p)
        {
          ivec.push_back(p->second);
          c++;
        }
        mTopRequestIndex.insert(std::pair<ulonglong,std::vector<uint>>(it->first,ivec));
      }
      else
      {
        tt->second.clear();
        tt->second.reserve(sz);
        uint c = 0;
        for (auto p = cnt.rbegin(); p != cnt.rend()  &&  c < sz; ++p)
        {
          tt->second.push_back(p->second);
          c++;
        }
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





KeyCountList RequestCounter::getTopRequestCounters()
{
  FUNCTION_TRACE
  try
  {
    return mTopRequestCounters;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::vector<uint> RequestCounter::getTopRequestIndexes(ulonglong key)
{
  FUNCTION_TRACE
  try
  {
    if (mCountingEnabled)
    {
      AutoThreadLock lock(&mThreadLock);

      auto tt = mTopRequestIndex.find(key);
      if (tt != mTopRequestIndex.end())
        return tt->second;
    }

    std::vector<uint> empty;
    return empty;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






ulonglong RequestCounter::getTotalRequests()
{
  FUNCTION_TRACE
  try
  {
    return mTotalRequests;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RequestCounter::resetTotalRequests()
{
  FUNCTION_TRACE
  try
  {
    mTotalRequests = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RequestCounter::incCounter(ulonglong key,uint index)
{
  FUNCTION_TRACE
  try
  {
    if (!mCountingEnabled)
      return;

    AutoThreadLock lock(&mThreadLock);

    mTotalRequests++;

    auto cnt = mPointRequestCounter.find(key);
    if (cnt == mPointRequestCounter.end())
    {
      std::map<uint,uint> cc;
      cc.insert(std::pair<uint,uint>(index,1));
      mPointRequestCounter.insert(std::pair<ulonglong,std::map<uint,uint>>(key,cc));
    }
    else
    {
      auto pp = cnt->second.find(index);
      if (pp != cnt->second.end())
      {
        pp->second++;
      }
      else
      {
        cnt->second.insert(std::pair<uint,uint>(index,1));
      }
/*
      for (auto p = cnt->second.begin(); p != cnt->second.end(); ++p)
        printf("%llu:%u: %u\n",key,p->first,p->second);
*/
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint RequestCounter::getCounter(ulonglong key,uint index)
{
  FUNCTION_TRACE
  try
  {
    if (!mCountingEnabled)
      return 0;

    auto cnt = mPointRequestCounter.find(key);
    if (cnt == mPointRequestCounter.end())
      return 0;

    if (index < cnt->second.size())
      return cnt->second[index];

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RequestCounter::setCountingEnabled(bool _enabled)
{
  FUNCTION_TRACE
  try
  {
    mCountingEnabled = _enabled;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool RequestCounter::isCountingEnabled()
{
  FUNCTION_TRACE
  try
  {
    return mCountingEnabled;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RequestCounter::saveTopIndexes(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    AutoThreadLock lock(&mThreadLock);

    FILE *file = fopen(filename,"w");
    if (file == nullptr)
    {
      SmartMet::Spine::Exception exception(BCP,"File creation failed!");
      exception.addParameter("Filename",filename);
      throw exception;
    }

    for (auto rc = mTopRequestCounters.rbegin(); rc != mTopRequestCounters.rend(); ++rc)
    {
      auto it = mTopRequestIndex.find(rc->second);
      if (it != mTopRequestIndex.end())
      {
        fprintf(file,"%llu;%u;",it->first,rc->first);
        for (auto pp = it->second.begin(); pp != it->second.end(); ++pp)
        {
          fprintf(file,"%u;",*pp);
        }
        fprintf(file,"\n");
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RequestCounter::loadTopIndexes(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    AutoThreadLock lock(&mThreadLock);
    mTopRequestIndex.clear();
    mTopRequestCounters.clear();

    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      return;
      /*
      SmartMet::Spine::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
      */
    }

    char st[100000];

    while (!feof(file))
    {
      if (fgets(st,100000,file) != nullptr  &&  st[0] != '#')
      {
        char *field[10000];
        uint c = 1;
        field[0] = st;
        char *p = st;
        while (*p != '\0'  &&  c < 10000)
        {
          if (*p == ';'  || *p == '\n')
          {
            *p = '\0';
            p++;
            field[c] = p;
            c++;
          }
          else
          {
            p++;
          }
        }

        if (c > 2)
        {
          ulonglong key = toUInt64(field[0]);
          ulong count = toUInt32(field[1]);
          std::vector<uint> indexes;
          indexes.reserve(c);
          for (uint t=2; t<c; t++)
            indexes.push_back(toUInt32(field[t]));

          mTopRequestIndex.insert(std::pair<ulonglong,std::vector<uint>>(key,indexes));
          mTopRequestCounters.insert(std::pair<uint,ulonglong>(count,key));
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}



}

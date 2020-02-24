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
    mRequestCounters.clear();
    mTotalRequests = 0;
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

    for (auto it = mRequestCounters.begin(); it != mRequestCounters.end(); ++it)
    {
      it->second = C_UINT(multiplier * C_DOUBLE(it->second));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





TopList RequestCounter::getTopRequestCounters()
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





void RequestCounter::incCounter(ulonglong key)
{
  FUNCTION_TRACE
  try
  {
    if (!mCountingEnabled)
      return;

    AutoThreadLock lock(&mThreadLock);

    mTotalRequests++;

    auto cnt = mRequestCounters.find(key);
    if (cnt == mRequestCounters.end())
    {
      mRequestCounters.insert(std::pair<ulonglong,uint>(key,1));
    }
    else
    {
      cnt->second++;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RequestCounter::incGeometryHitCounter(uint geometryId,uint index)
{
  FUNCTION_TRACE
  try
  {
    if (!mCountingEnabled)
      return;

    AutoThreadLock lock(&mThreadLock);

    auto geom = mGeometryHitCounter.find(geometryId);
    if (geom != mGeometryHitCounter.end())
    {
      auto cnt = geom->second.find(index);
      if (cnt == geom->second.end())
      {
        geom->second.insert(std::pair<uint,uint>(index,1));
      }
      else
      {
        cnt->second++;
      }
    }
    else
    {
      HitCounter hitCounter;
      hitCounter.insert(std::pair<uint,uint>(index,1));
      mGeometryHitCounter.insert(std::pair<uint,HitCounter>(geometryId,hitCounter));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void RequestCounter::setGeometryHitCounter(uint geometryId,uint index,uint count)
{
  FUNCTION_TRACE
  try
  {
    if (!mCountingEnabled)
      return;

    auto geom = mGeometryHitCounter.find(geometryId);
    if (geom != mGeometryHitCounter.end())
    {
      auto cnt = geom->second.find(index);
      if (cnt == geom->second.end())
      {
        geom->second.insert(std::pair<uint,uint>(index,count));
      }
      else
      {
        cnt->second = count;
      }
    }
    else
    {
      HitCounter hitCounter;
      hitCounter.insert(std::pair<uint,uint>(index,count));
      mGeometryHitCounter.insert(std::pair<uint,HitCounter>(geometryId,hitCounter));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





HitCounter RequestCounter::getGeometryHitCounters(uint geometryId)
{
  FUNCTION_TRACE
  try
  {
    HitCounter hitCounter;
    if (!mCountingEnabled)
      return hitCounter;

    AutoThreadLock lock(&mThreadLock);

    auto geom = mGeometryHitCounter.find(geometryId);
    if (geom != mGeometryHitCounter.end())
      return geom->second;

    return hitCounter;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint RequestCounter::getCounter(ulonglong key)
{
  FUNCTION_TRACE
  try
  {
    if (!mCountingEnabled)
      return 0;

    auto cnt = mRequestCounters.find(key);
    if (cnt == mRequestCounters.end())
      return 0;

    return cnt->second;
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





void RequestCounter::updateTopCounters()
{
  FUNCTION_TRACE
  try
  {
    // Disable the request counting before calling this method.

    if (mCountingEnabled)
      return;

    AutoThreadLock lock(&mThreadLock);

    mTopRequestCounters.clear();

    for (auto it = mRequestCounters.begin(); it != mRequestCounters.end(); ++it)
    {
      mTopRequestCounters.insert(std::pair<uint,ulonglong>(it->second,it->first));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RequestCounter::saveGeometryHitCounters(const char *filename)
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

    for (auto geom = mGeometryHitCounter.rbegin(); geom != mGeometryHitCounter.rend(); ++geom)
    {
      for (auto it = geom->second.begin();it != geom->second.end();++it)
      {
        fprintf(file,"%u;%u;%u\n",geom->first,it->first,it->second);
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void RequestCounter::loadGeometryHitCounters(const char *filename)
{
  FUNCTION_TRACE
  try
  {
    AutoThreadLock lock(&mThreadLock);
    mGeometryHitCounter.clear();

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

        if (c >= 3)
        {
          uint geometryId = toUInt32(field[0]);
          uint index = toUInt32(field[1]);
          ulong count = toUInt32(field[2]);
          setGeometryHitCounter(geometryId,index,count);
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

#include "GeneralFunctions.h"
#include "GeneralDefinitions.h"
#include "Exception.h"

#include <stdlib.h>
#include <sstream>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


namespace SmartMet
{

std::string uint64_toHex(unsigned long long value)
{
  try
  {
    char st[25];
    sprintf(st,"0x%llX",value);
    return std::string(st);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





int uint_compare(uint v1,uint v2)
{
  try
  {
    if (v1 == v2)
      return 0;

    if (v1 < v2)
      return -1;

    return 1;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





int uint64_compare(unsigned long long v1,unsigned long long v2)
{
  try
  {
    if (v1 == v2)
      return 0;

    if (v1 < v2)
      return -1;

    return 1;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





int double_compare(double v1,double v2)
{
  try
  {
    if (v1 == v2)
      return 0;

    if (v1 < v2)
      return -1;

    return 1;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




int time_compare(time_t v1,time_t v2)
{
  try
  {
    if (v1 == v2)
      return 0;

    if (v1 < v2)
      return -1;

    return 1;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




void time_usleep(int _sec,int _usec)
{
  timespec r1,r2;
  r1.tv_sec = _sec;
  r1.tv_nsec = _usec; // * 1000;
  nanosleep(&r1,&r2);
}





double int_power(double x, int y)
{
  try
  {
    double value = 0;
    if (y < 0)
    {
      y = -y;
      x = 1.0 / x;
    }
    value = 1.0;

    while (y)
    {
      if (y & 1)
      {
        value *= x;
      }
      x = x * x;
      y >>= 1;
    }
    return value;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





double grib_power(long s,long n)
{
  try
  {
    double divisor = 1.0;
    while (s < 0)
    {
      divisor = divisor / (double)n;
      s++;
    }
    while (s > 0)
    {
      divisor = divisor * (double)n;
      s--;
    }
    return divisor;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string space(uint size)
{
  try
  {
    std::stringstream st;
    for (uint t=0; t<size; t++)
      st << "  ";

    return st.str();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





unsigned long long getTime()
{
  try
  {
    struct timeval tt;
    gettimeofday(&tt,NULL);
    return 1000000*tt.tv_sec + tt.tv_usec;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




time_t getFileModificationTime(const char *filename)
{
  try
  {
    struct stat buf;
    if (stat(filename,&buf) == 0)
      return buf.st_mtime;

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




uint stringToId(const char *str,uint len)
{
  try
  {
    if (str == NULL)
      return 0;

    unsigned long long id = 0;
    uint idx = 0;

    while (str[idx] != '\0'  &&  idx < len)
    {
      id = id + (uint)str[idx]*(idx+123) + (uint)str[idx];
      //printf("%u:%c:%llu\n",idx,str[idx],id);
      idx++;
    }
    return (uint)(id & 0xFFFFFFFF);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




time_t toTimeT(boost::posix_time::ptime tim)
{
  try
  {
    struct tm tt = boost::posix_time::to_tm(tim);
    return mktime(&tt);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(std::array<char,16> value)
{
  try
  {
    std::string str = "Array[16]";
    return str;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(std::int8_t value)
{
  try
  {
    return std::to_string((int)value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(std::int16_t value)
{
  try
  {
    return std::to_string((int)value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(std::int32_t value)
{
  try
  {
    return std::to_string((int)value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(std::int64_t value)
{
  try
  {
    return std::to_string((int)value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(std::uint8_t value)
{
  try
  {
    return std::to_string((uint)value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(std::uint16_t value)
{
  try
  {
    return std::to_string((uint)value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(std::uint32_t value)
{
  try
  {
    return std::to_string((uint)value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(std::uint64_t value)
{
  try
  {
    return std::to_string((uint)value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(float value)
{
  try
  {
    char tmp[20];
    sprintf(tmp,"%.3f",value);
    return std::string(tmp);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(double value)
{
  try
  {
    char tmp[20];
    sprintf(tmp,"%.3f",value);
    return std::string(tmp);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(std::string value)
{
  try
  {
    return value;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(T::UInt8_opt value)
{
  try
  {
    if (!value)
      return std::string("");

    return std::to_string((uint)(*value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(T::UInt16_opt value)
{
  try
  {
    if (!value)
      return std::string("");

    return std::to_string((uint)(*value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(T::UInt32_opt value)
{
  try
  {
    if (!value)
      return std::string("");

    return std::to_string((uint)(*value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(T::UInt64_opt value)
{
  try
  {
    if (!value)
      return std::string("");

    return std::to_string((uint)(*value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(T::Int8_opt value)
{
  try
  {
    if (!value)
      return std::string("");

    return std::to_string((int)(*value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(T::Int16_opt value)
{
  try
  {
    if (!value)
      return std::string("");

    return std::to_string((int)(*value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(T::Int32_opt value)
{
  try
  {
    if (!value)
      return std::string("");

    return std::to_string((int)(*value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(T::Int64_opt value)
{
  try
  {
    if (!value)
      return std::string("");

    return std::to_string((int)(*value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string toString(boost::posix_time::ptime time)
{
  try
  {
    return boost::posix_time::to_iso_string(time);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





boost::posix_time::ptime toTimeStamp(T::TimeString timeStr)
{
  try
  {
    return boost::posix_time::ptime(boost::posix_time::from_iso_string(timeStr));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





}


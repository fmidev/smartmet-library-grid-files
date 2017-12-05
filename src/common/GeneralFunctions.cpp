#include "GeneralFunctions.h"
#include "GeneralDefinitions.h"
#include "Exception.h"

#include <stdlib.h>
#include <sstream>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <zlib.h>


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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




long long getFileSize(const char *filename)
{
  try
  {
    struct stat buf;
    if (stat(filename,&buf) == 0)
      return (long long)buf.st_size;

    return -1;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint stringToId(const char *str)
{
  try
  {
    if (str == NULL)
      return 0;

    uint len = strlen(str);
    return stringToId(str,len);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




int getInt(const char *str,uint startIdx,uint len)
{
  char buf[100];
  strncpy(buf,str+startIdx,len);
  buf[len] = '\0';
  return atoi(buf);
}





time_t mktime_tz(struct tm *tm,const char *tzone)
{
  time_t ret;
  char *tz;
  tz = getenv("TZ");
  if (tz)
    tz = strdup(tz);
  setenv("TZ", tzone, 1);
  tzset();
  ret = mktime(tm);
  if (tz)
  {
    setenv("TZ", tz, 1);
    free(tz);
  }
  else
    unsetenv("TZ");
  tzset();
  return ret;
}





struct tm* localtime_tz(time_t t,struct tm *tt,const char *tzone)
{
  char *tz;
  tz = getenv("TZ");
  if (tz)
    tz = strdup(tz);
  setenv("TZ", tzone, 1);
  tzset();

  localtime_r(&t,tt);

  if (tz)
  {
    setenv("TZ", tz, 1);
    free(tz);
  }
  else
    unsetenv("TZ");
  tzset();

  return tt;
}





time_t localTimeToTimeT(std::string localTime,const char *tzone)
{
  try
  {
    if (localTime.length() != 15)
      throw SmartMet::Spine::Exception(BCP,"Invalid timestamp format (expected YYYYMMDDTHHMMSS)!");

    const char *str = localTime.c_str();

    struct tm tt;
    tt.tm_year = getInt(str,0,4) - 1900;   /* Year - 1900 */
    tt.tm_mon = getInt(str,4,2) - 1;    /* Month (0-11) */
    tt.tm_mday = getInt(str,6,2);   /* Day of the month (1-31) */
    tt.tm_hour = getInt(str,9,2);;   /* Hours (0-23) */
    tt.tm_min = getInt(str,11,2);;    /* Minutes (0-59) */
    tt.tm_sec = getInt(str,13,2);;    /* Seconds (0-60) */
    tt.tm_isdst = -1;  /* Daylight saving time */

    return mktime_tz(&tt,tzone);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





time_t utcTimeToTimeT(std::string utcTime)
{
  try
  {
    if (utcTime.length() != 15)
      throw SmartMet::Spine::Exception(BCP,"Invalid timestamp format (expected YYYYMMDDTHHMMSS)!");

    const char *str = utcTime.c_str();

    struct tm tt;
    tt.tm_year = getInt(str,0,4) - 1900;   /* Year - 1900 */
    tt.tm_mon = getInt(str,4,2) - 1;    /* Month (0-11) */
    tt.tm_mday = getInt(str,6,2);   /* Day of the month (1-31) */
    tt.tm_hour = getInt(str,9,2);;   /* Hours (0-23) */
    tt.tm_min = getInt(str,11,2);;    /* Minutes (0-59) */
    tt.tm_sec = getInt(str,13,2);;    /* Seconds (0-60) */
    tt.tm_isdst = -1;  /* Daylight saving time */

    return mktime_tz(&tt,"");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string localTimeFromTimeT(time_t t,const char *tzone)
{
  try
  {
    struct tm tt;
    localtime_tz(t,&tt,tzone);

    char buf[30];
    sprintf(buf,"%04d%02d%02dT%02d%02d%02d",tt.tm_year+1900,tt.tm_mon+1,tt.tm_mday,tt.tm_hour,tt.tm_min,tt.tm_sec);
    std::string str = buf;
    return str;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string utcTimeFromTimeT(time_t t)
{
  try
  {
    struct tm tt;
    gmtime_r(&t,&tt);

    char buf[30];
    sprintf(buf,"%04d%02d%02dT%02d%02d%02d",tt.tm_year+1900,tt.tm_mon+1,tt.tm_mday,tt.tm_hour,tt.tm_min,tt.tm_sec);
    std::string str = buf;
    return str;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string localTimeToUtcTime(std::string localTime,const char *tzone)
{
  try
  {
    time_t t = localTimeToTimeT(localTime,tzone);
    return utcTimeFromTimeT(t);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string utcTimeToLocalTime(std::string utcTime,const char *tzone)
{
  try
  {
    time_t t = utcTimeToTimeT(utcTime);
    return localTimeFromTimeT(t,tzone);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string toString(float value)
{
  try
  {
    char tmp[100];
    sprintf(tmp,"%.3f",value);
    return std::string(tmp);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string toString(double value)
{
  try
  {
    char tmp[100];
    sprintf(tmp,"%.3f",value);
    return std::string(tmp);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string toLowerString(std::string sourceString)
{
  try
  {
    std::string destinationString;

     // Allocate the destination space
     destinationString.resize(sourceString.size());

     // Convert the source string to lower case storing the result in destination string
     std::transform(sourceString.begin(),sourceString.end(), destinationString.begin(),::tolower);

     return destinationString;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




int compressData(void *_data,uint _dataSize,void *_compressedData,uint& _compressedDataSize)
{
  uLongf comprLen = (uLongf)_compressedDataSize;
  compress((Bytef*)_compressedData, &comprLen, (Bytef*)_data, (uLong)_dataSize);

  if (comprLen > 0)
  {
    _compressedDataSize = comprLen;
    return 0;
  }

  _compressedDataSize = 0;
  return -1;
}






int decompressData(void *_compressedData,uint _compressedDataSize,void *_decompressedData,uint& _decompressedDataSize)
{
  uLongf len = (uLongf)_decompressedDataSize;
  int res = uncompress((Bytef*)_decompressedData, &len, (Bytef*)_compressedData, (uLong)_compressedDataSize);
  //printf("UNCOMPRESS %d\n",res);
  _decompressedDataSize = len;

  if (res < 0)
  {
    _decompressedDataSize = 0;
    return -1;
  }

  return 0;
}




void parseLatLonCoordinates(std::string latLonCoordinates,std::vector<T::Coordinate>& coordinates)
{
  char st[10000];
  strcpy(st,latLonCoordinates.c_str());
  char *field[1000];
  uint c = 1;
  field[0] = st;
  char *p = st;
  while (*p != '\0'  &&  c < 1000)
  {
    if (*p == ';' ||  *p == ',')
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

  if ((c % 2) == 0)
  {
    for (uint t = 0; t<c; t = t + 2)
    {
      coordinates.push_back(T::Coordinate(atof(field[t+1]),atof(field[t])));
    }
  }
}





void splitString(const char *str,char separator,std::vector<std::string>& partList)
{
  try
  {
    char buf[10000];
    uint c = 0;
    char *p = (char*)str;

    bool ind = false;
    while (*p != '\0'  &&  *p != '\n'  &&  c < 10000)
    {
      if (*p == '"')
        ind = !ind;

      if (*p == separator  &&  !ind)
      {
        buf[c] = '\0';
        partList.push_back(std::string(buf));
        c = 0;
      }
      else
      {
        buf[c] = *p;
        c++;
      }
      p++;
    }
    if (c > 0)
    {
      buf[c] = '\0';
      partList.push_back(std::string(buf));
    }
  }
  catch (...)
  {
    throw Spine::Exception(BCP, "Operation failed!", NULL);
  }
}




void splitString(std::string str,char separator,std::vector<std::string>& partList)
{
  try
  {
    splitString(str.c_str(),separator,partList);
  }
  catch (...)
  {
    throw Spine::Exception(BCP, "Operation failed!", NULL);
  }
}





void splitString(const char *str,char separator,std::set<std::string>& partList)
{
  try
  {
    char buf[10000];
    uint c = 0;
    char *p = (char*)str;

    bool ind = false;
    while (*p != '\0'  &&  *p != '\n'  &&  c < 10000)
    {
      if (*p == '"')
        ind = !ind;

      if (*p == separator  &&  !ind)
      {
        buf[c] = '\0';
        partList.insert(std::string(buf));
        c = 0;
      }
      else
      {
        buf[c] = *p;
        c++;
      }
      p++;
    }
    if (c > 0)
    {
      buf[c] = '\0';
      partList.insert(std::string(buf));
    }
  }
  catch (...)
  {
    throw Spine::Exception(BCP, "Operation failed!", NULL);
  }
}




void splitString(std::string str,char separator,std::set<std::string>& partList)
{
  try
  {
    splitString(str.c_str(),separator,partList);
  }
  catch (...)
  {
    throw Spine::Exception(BCP, "Operation failed!", NULL);
  }
}
} // Namespace SmartMet



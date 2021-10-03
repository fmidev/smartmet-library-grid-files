#include "GeneralFunctions.h"
#include <arpa/inet.h>
#include <dirent.h>
#include <fnmatch.h>
#include <limits.h>
#include <macgyver/StringConversion.h>
#include <macgyver/TimeParser.h>
#include <macgyver/TimeZones.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <zlib.h>
#include <boost/algorithm/string.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/path.hpp>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "AutoThreadLock.h"
#include "GeneralDefinitions.h"

#define NUM(a) (a-'0')


namespace fs = boost::filesystem;

namespace SmartMet
{

Fmi::TimeZones itsTimeZones;


std::string uint64_toHex(unsigned long long value)
{
  try
  {
    char st[25];
    sprintf(st, "0x%llX", value);
    return std::string(st);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

#if 0
int num_compare(uint& v1, uint& v2)
{
  try
  {
    if (v1 == v2) return 0;

    if (v1 < v2) return -1;

    return 1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

int num_compare(char& v1, char& v2)
{
  try
  {
    if (v1 == v2) return 0;

    if (v1 < v2) return -1;

    return 1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

int num_compare(uchar& v1, uchar& v2)
{
  try
  {
    if (v1 == v2) return 0;

    if (v1 < v2) return -1;

    return 1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

int num_compare(short& v1, short& v2)
{
  try
  {
    if (v1 == v2) return 0;

    if (v1 < v2) return -1;

    return 1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

int num_compare(ushort& v1, ushort& v2)
{
  try
  {
    if (v1 == v2) return 0;

    if (v1 < v2) return -1;

    return 1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

int num_compare(int& v1, int& v2)
{
  try
  {
    if (v1 == v2) return 0;

    if (v1 < v2) return -1;

    return 1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

int num_compare(unsigned long long& v1, unsigned long long& v2)
{
  try
  {
    if (v1 == v2) return 0;

    if (v1 < v2) return -1;

    return 1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

int num_compare(long long& v1, long long& v2)
{
  try
  {
    if (v1 == v2) return 0;

    if (v1 < v2) return -1;

    return 1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

int num_compare(float& v1, float& v2)
{
  try
  {
    if (v1 == v2) return 0;

    if (v1 < v2) return -1;

    return 1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

int num_compare(double& v1, double& v2)
{
  try
  {
    if (v1 == v2) return 0;

    if (v1 < v2) return -1;

    return 1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

int time_compare(time_t v1, time_t v2)
{
  try
  {
    if (v1 == v2) return 0;

    if (v1 < v2) return -1;

    return 1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}
#endif


void time_usleep(int _sec, int _usec)
{
  timespec r1, r2;
  r1.tv_sec = _sec;
  r1.tv_nsec = _usec;  // * 1000;
  nanosleep(&r1, &r2);
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
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void ieee2ibm(void *to, void *from, int len)
{
  unsigned fr = 0; /* fraction */
  int exp = 0;     /* exponent */
  int sgn = 0;     /* sign */

  for (; len-- > 0; to = (char *)to + 4, from = (char *)from + 4)
  {
    /* split into sign, exponent, and fraction */
    fr = *(unsigned *)from; /* pick up value */
    sgn = fr >> 31;         /* save sign */
    fr <<= 1;               /* shift sign out */
    exp = fr >> 24;         /* save exponent */
    fr <<= 8;               /* shift exponent out */

    if (exp == 255)
    { /* infinity (or NAN) - map to largest */
      fr = 0xffffff00;
      exp = 0x7f;
      goto done;
    }
    else if (exp > 0) /* add assumed digit */
      fr = (fr >> 1) | 0x80000000;
    else if (fr == 0) /* short-circuit for zero */
      goto done;

    /* adjust exponent from base 2 offset 127 radix point after first digit
       to base 16 offset 64 radix point before first digit */
    exp += 130;
    fr >>= -exp & 3;
    exp = (exp + 3) >> 2;

    /* (re)normalize */
    while (fr < 0x10000000)
    { /* never executed for normalized input */
      --exp;
      fr <<= 4;
    }

  done:
    /* put the pieces back together and return it */
    fr = (fr >> 8) | (exp << 24) | (sgn << 31);
    *(unsigned *)to = htonl(fr);
  }
}



float ieee2ibm(float value)
{
  try
  {
    float f = 0;
    ieee2ibm(&f, &value, 1);
    return f;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



float ibm2ieee(float ibmFloat)
{
  try
  {
    unsigned char *v = reinterpret_cast<unsigned char *>(&ibmFloat);
    unsigned char a = v[0];
    unsigned char b = v[1];
    unsigned char c = v[2];
    unsigned char d = v[3];

    int mant = (b & 0xFF) << 16 | (c & 0xFF) << 8 | (d & 0xFF);
    if (mant == 0) return 0.0;

    int sgn = -(((a & 128) >> 6) - 1);
    int exp = (a & 127) - 64;

    return (float)(sgn * int_power(16.0, exp - 6) * mant);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



double grib_power(long s, long n)
{
  try
  {
    double divisor = 1.0;
    while (s < 0)
    {
      divisor = divisor / C_DOUBLE(n);
      s++;
    }
    while (s > 0)
    {
      divisor = divisor * C_DOUBLE(n);
      s--;
    }
    return divisor;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string space(uint size)
{
  try
  {
    std::stringstream st;
    for (uint t = 0; t < size; t++)
      st << "  ";

    return st.str();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



unsigned long long getTime()
{
  try
  {
    struct timeval tt;
    gettimeofday(&tt, nullptr);
    return 1000000 * tt.tv_sec + tt.tv_usec;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



time_t getFileModificationTime(const char *filename)
{
  try
  {
    struct stat buf;
    if (stat(filename, &buf) == 0) return buf.st_mtime;

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



long long getFileSize(const char *filename)
{
  try
  {
    struct stat buf;
    if (stat(filename, &buf) == 0) return (long long)buf.st_size;

    return -1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string stringReplaceAll(const std::string& st,const std::string& oldStr,std::string newStr)
{
  try
  {
    std::string s = st;
    std::size_t fp = s.find(oldStr);
    while (fp != std::string::npos)
    {
      s.replace(fp,oldStr.length(),newStr);
      fp = s.find(oldStr);
    }
    return s;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



uint stringToId(const char *str, uint len)
{
  try
  {
    if (str == nullptr) return 0;

    unsigned long long id = 0;
    uint idx = 0;

    while (str[idx] != '\0' && idx < len)
    {
      id = id + C_UINT(str[idx]) * (idx + 123) + str[idx];
      idx++;
    }
    return C_UINT(id & 0xFFFFFFFF);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



uint stringToId(const char *str)
{
  try
  {
    if (str == nullptr) return 0;

    uint len = strlen(str);
    return stringToId(str, len);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



int getInt(const char *str, uint startIdx, uint len)
{
  try
  {
    char buf[100];
    strncpy(buf, str + startIdx, len);
    buf[len] = '\0';
    return toInt32(buf);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



time_t mktime_tz(struct tm *tm, const char *tzone)
{
  try
  {
    const char *tzo = "UTC";
    if (tzone == nullptr || tzone[0] == '\0')
      tzone = getenv("TZ");

    if (tzone == nullptr || tzone[0] == '\0')
      tzone = (char*)tzo;

    auto zone = itsTimeZones.time_zone_from_string(tzone);

    boost::posix_time::time_duration td(tm->tm_hour,tm->tm_min,tm->tm_sec,0);
    boost::gregorian::date d(tm->tm_year + 1900,tm->tm_mon + 1,tm->tm_mday);
    boost::posix_time::ptime pt(d, td);

    boost::local_time::local_date_time ldt(pt.date(), pt.time_of_day(), zone, boost::local_time::local_date_time::EXCEPTION_ON_ERROR);
    boost::posix_time::ptime t = ldt.utc_time();

    time_t tt = (t - boost::posix_time::from_time_t(0)).total_seconds();
    return tt;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



struct tm *localtime_tz(time_t t, struct tm *tt, const char *tzone)
{
  try
  {
    const char *tzo = "UTC";
    if (tzone == nullptr || tzone[0] == '\0')
      tzone = getenv("TZ");

    if (tzone == nullptr || tzone[0] == '\0')
      tzone = (char*)tzo;

    auto zone = itsTimeZones.time_zone_from_string(tzone);

    boost::posix_time::ptime pt(boost::gregorian::date(1970,1,1));
    pt = pt + boost::posix_time::seconds(static_cast<long>(t));
    boost::local_time::local_date_time ldt(pt, zone);
    boost::posix_time::ptime ltp = ldt.local_time();


    std::tm timetm = boost::gregorian::to_tm(ltp.date());
    boost::posix_time::time_duration td = ltp.time_of_day();

    tt->tm_year = timetm.tm_year;
    tt->tm_mon = timetm.tm_mon;
    tt->tm_mday = timetm.tm_mday;
    tt->tm_year = timetm.tm_year;
    tt->tm_hour = static_cast<int>(td.hours());
    tt->tm_min = static_cast<int>(td.minutes());
    tt->tm_sec = static_cast<int>(td.seconds());
    tt->tm_isdst = timetm.tm_isdst; // -1; // -1 used when dst info is unknown

    return tt;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



time_t localTimeToTimeT(const std::string& localTime, const char *tzone)
{
  try
  {
    if (localTime.length() != 15)
    {
      Fmi::Exception exception(BCP,"Invalid timestamp format (expected YYYYMMDDTHHMMSS)!");
      exception.addParameter("timestamp", localTime);
      throw exception;
    }

    const char *str = localTime.c_str();

    struct tm tt;
    tt.tm_year = getInt(str, 0, 4) - 1900; /* Year - 1900 */
    tt.tm_mon = getInt(str, 4, 2) - 1;     /* Month (0-11) */
    tt.tm_mday = getInt(str, 6, 2);        /* Day of the month (1-31) */
    tt.tm_hour = getInt(str, 9, 2);
    ; /* Hours (0-23) */
    tt.tm_min = getInt(str, 11, 2);
    ; /* Minutes (0-59) */
    tt.tm_sec = getInt(str, 13, 2);
    ;                 /* Seconds (0-60) */
    tt.tm_isdst = -1; /* Daylight saving time */

    return mktime_tz(&tt, tzone);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



time_t utcTimeToTimeT(const std::string& utcTime)
{
  try
  {
    if (utcTime.length() != 15)
      throw Fmi::Exception(BCP, "Invalid timestamp format (expected YYYYMMDDTHHMMSS)!");

    const char *str = utcTime.c_str();

    struct tm tt;
    tt.tm_year = getInt(str, 0, 4) - 1900; /* Year - 1900 */
    tt.tm_mon = getInt(str, 4, 2) - 1;     /* Month (0-11) */
    tt.tm_mday = getInt(str, 6, 2);        /* Day of the month (1-31) */
    tt.tm_hour = getInt(str, 9, 2);
    ; /* Hours (0-23) */
    tt.tm_min = getInt(str, 11, 2);
    ; /* Minutes (0-59) */
    tt.tm_sec = getInt(str, 13, 2);
    ;                 /* Seconds (0-60) */
    tt.tm_isdst = -1; /* Daylight saving time */

    return mktime_tz(&tt, "");
  }
  catch (...)
  {
    Fmi::Exception exception(BCP, "Operation failed!", nullptr);
    exception.addParameter("utcTime",utcTime);
    throw exception;
  }
}



time_t utcTimeToTimeT(int year,int month,int day,int hour,int minute,int second)
{
  try
  {
    struct tm tt;
    tt.tm_year = year - 1900;
    tt.tm_mon = month - 1;
    tt.tm_mday = day;
    tt.tm_hour = hour;
    tt.tm_min = minute;
    tt.tm_sec = second;
    tt.tm_isdst = -1;

    return mktime_tz(&tt, "");
  }
  catch (...)
  {
    Fmi::Exception exception(BCP, "Operation failed!", nullptr);
    throw exception;
  }
}



void splitTimeString(const std::string& timeStr, int &year, int &month, int &day, int &hour, int &minute, int &second)
{
  try
  {
    if (timeStr.length() != 15)
      throw Fmi::Exception(BCP, "Invalid timestamp format (expected YYYYMMDDTHHMMSS)!");

    const char *str = timeStr.c_str();

    year = getInt(str, 0, 4);
    month = getInt(str, 4, 2);
    day = getInt(str, 6, 2);
    hour = getInt(str, 9, 2);
    minute = getInt(str, 11, 2);
    second = getInt(str, 13, 2);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitTimeString(const std::string& timeStr, short &year, uchar &month, uchar &day, uchar &hour, uchar &minute, uchar &second)
{
  try
  {
    if (timeStr.length() != 15)
      throw Fmi::Exception(BCP, "Invalid timestamp format (expected YYYYMMDDTHHMMSS)!");

    const char *str = timeStr.c_str();

    year = C_SHORT(getInt(str, 0, 4));
    month = C_UCHAR(getInt(str, 4, 2));
    day = C_UCHAR(getInt(str, 6, 2));
    hour = C_UCHAR(getInt(str, 9, 2));
    minute = C_UCHAR(getInt(str, 11, 2));
    second = C_UCHAR(getInt(str, 13, 2));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string localTimeFromTimeT(time_t t, const char *tzone)
{
  try
  {
    struct tm tt;
    localtime_tz(t, &tt, tzone);

    char buf[200];
    sprintf(buf,
            "%04d%02d%02dT%02d%02d%02d",
            tt.tm_year + 1900,
            tt.tm_mon + 1,
            tt.tm_mday,
            tt.tm_hour,
            tt.tm_min,
            tt.tm_sec);
    std::string str = buf;
    return str;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string utcTimeFromTimeT(time_t t)
{
  try
  {
    return Fmi::to_iso_string(t);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string localTimeToUtcTime(const std::string& localTime, const char *tzone)
{
  try
  {
    time_t t = localTimeToTimeT(localTime, tzone);
    return utcTimeFromTimeT(t);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string localTimeToUtc(const std::string& localTime, boost::local_time::time_zone_ptr tz)
{
  try
  {
    auto ptime = Fmi::TimeParser::parse_iso(localTime);
    boost::local_time::local_date_time localTime(ptime, tz);
    auto lTime = Fmi::TimeParser::make_time(localTime.date(), localTime.time_of_day(), tz);
    return Fmi::to_iso_string(lTime.utc_time());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string utcTimeToLocalTime(const std::string& utcTime, const char *tzone)
{
  try
  {
    time_t t = utcTimeToTimeT(utcTime);
    return localTimeFromTimeT(t, tzone);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



time_t toTimeT(boost::posix_time::ptime tim)
{
  try
  {
    return boost::posix_time::to_time_t(tim);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string addSeconds(const std::string& timeStr, int seconds)
{
  try
  {
    time_t t = utcTimeToTimeT(timeStr);
    t = t + seconds;
    return utcTimeFromTimeT(t);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



char toInt8(const char *str)
{
  try
  {
    if (str == nullptr) return 0;

    return static_cast<char>(atoll(str));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



short toInt16(const char *str)
{
  try
  {
    if (str == nullptr) return 0;

    return static_cast<short>(atoll(str));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



int toInt32(const char *str)
{
  try
  {
    if (str == nullptr) return 0;

    return static_cast<int>(atoll(str));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



long long toInt64(const char *str)
{
  try
  {
    if (str == nullptr) return 0;

    return atoll(str);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



size_t toSize_t(const char *str)
{
  try
  {
    if (str == nullptr) return 0;

    return static_cast<size_t>(atoll(str));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



uchar toUInt8(const char *str)
{
  try
  {
    if (str == nullptr) return 0;

    return static_cast<uchar>(atoll(str));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



ushort toUInt16(const char *str)
{
  try
  {
    if (str == nullptr) return 0;

    return static_cast<ushort>(atoll(str));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



uint toUInt32(const char *str)
{
  try
  {
    if (str == nullptr) return 0;

    return static_cast<uint>(atoll(str));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



ulonglong toUInt64(const char *str)
{
  try
  {
    if (str == nullptr) return 0;

    return static_cast<unsigned long long>(atoll(str));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



double toDouble2(const char* str)
{
  double result = 0;
  double sign = *str == '-' ? str++, -1 : 1;
  while (*str >= '0' && *str <= '9')
  {
    result *= 10;
    result += *str - '0';
    str++;
  }

  if (*str == ',' || *str == '.')
  {
    str++;
    double multiplier = 0.1;
    while (*str >= '0' && *str <= '9')
    {
      result += (*str - '0') * multiplier;
      multiplier /= 10;
      str++;
    }
  }
  result *= sign;
  if (*str == 'e' || *str == 'E')
  {
    str++;
    double powerer = *str == '-'? str++, 0.1 : 10;
    double power = 0;
    while (*str >= '0' && *str <= '9')
    {
      power *= 10;
      power += *str - '0';
      str++;
    }
    result *= pow(powerer, power);
  }
  return result;
}



float toFloat(const char *str)
{
  try
  {
    // Make sure that the environment variable LC_NUMERIC is defined
    // correctly (export LC_NUMERIC="en_US.UTF-8").

    if (str == nullptr)
      return 0.0;

    return C_FLOAT(atof(str));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}




double toDouble(const char *str)
{
  try
  {
    // Make sure that the environment variable LC_NUMERIC is defined
    // correctly (export LC_NUMERIC="en_US.UTF-8").

    if (str == nullptr)
      return 0.0;

    return atof(str);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}




char toInt8(const std::string &str)
{
  try
  {
    return toInt8(str.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



short toInt16(const std::string &str)
{
  try
  {
    return toInt16(str.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



int toInt32(const std::string &str)
{
  try
  {
    return toInt32(str.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



long long toInt64(const std::string &str)
{
  try
  {
    return toInt64(str.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



uchar toUInt8(const std::string &str)
{
  try
  {
    return toUInt8(str.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



ushort toUInt16(const std::string &str)
{
  try
  {
    return toUInt16(str.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



uint toUInt32(const std::string &str)
{
  try
  {
    return toUInt32(str.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



ulonglong toUInt64(const std::string &str)
{
  try
  {
    return toUInt64(str.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



float toFloat(const std::string &str)
{
  try
  {
    return toFloat(str.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



double toDouble(const std::string &str)
{
  try
  {
    return toDouble(str.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



size_t toSize_t(const std::string &str)
{
  try
  {
    return toSize_t(str.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(std::array<char, 16> value)
{
  try
  {
    std::string str = "Array[16]";
    return str;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(std::int8_t value)
{
  try
  {
    return Fmi::to_string(C_INT(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(std::int16_t value)
{
  try
  {
    return Fmi::to_string(value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(std::int32_t value)
{
  try
  {
    return Fmi::to_string(value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(std::int64_t value)
{
  try
  {
    return Fmi::to_string(value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(std::uint8_t value)
{
  try
  {
    return Fmi::to_string(C_UINT(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(std::uint16_t value)
{
  try
  {
    return Fmi::to_string(value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(std::uint32_t value)
{
  try
  {
    return Fmi::to_string(value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(std::uint64_t value)
{
  try
  {
    return Fmi::to_string(value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(float value)
{
  try
  {
    char tmp[100];
    sprintf(tmp, "%.3f", value);
    return std::string(tmp);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(double value)
{
  try
  {
    char tmp[100];
    sprintf(tmp, "%.3f", value);
    return std::string(tmp);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(const std::string& value)
{
  try
  {
    return value;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(T::UInt8_opt value)
{
  try
  {
    if (!value) return std::string("");

    return Fmi::to_string(C_UINT(*value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(T::UInt16_opt value)
{
  try
  {
    if (!value) return std::string("");

    return Fmi::to_string(*value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(T::UInt32_opt value)
{
  try
  {
    if (!value) return std::string("");

    return Fmi::to_string(*value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(T::UInt64_opt value)
{
  try
  {
    if (!value) return std::string("");

    return Fmi::to_string(*value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(T::Int8_opt value)
{
  try
  {
    if (!value) return std::string("");

    return Fmi::to_string(C_INT(*value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(T::Int16_opt value)
{
  try
  {
    if (!value) return std::string("");

    return Fmi::to_string(*value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(T::Int32_opt value)
{
  try
  {
    if (!value) return std::string("");

    return Fmi::to_string(*value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(T::Int64_opt value)
{
  try
  {
    if (!value) return std::string("");

    return Fmi::to_string(*value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}


std::string toString(boost::posix_time::ptime time)
{
  try
  {
    return Fmi::to_iso_string(time);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toLowerString(const char *sourceString)
{
  try
  {
    std::string s(sourceString);
    return toLowerString(s);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toLowerString(const std::string& sourceString)
{
  try
  {
    std::string destinationString;

    // Allocate the destination space
    destinationString.resize(sourceString.size());

    // Convert the source string to lower case storing the result in destination string
    std::transform(sourceString.begin(), sourceString.end(), destinationString.begin(), ::tolower);

    return destinationString;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toUpperString(const char *sourceString)
{
  try
  {
    std::string s(sourceString);
    return toUpperString(s);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toUpperString(const std::string& sourceString)
{
  try
  {
    std::string destinationString;

    // Allocate the destination space
    destinationString.resize(sourceString.size());

    // Convert the source string to lower case storing the result in destination string
    std::transform(sourceString.begin(), sourceString.end(), destinationString.begin(), ::toupper);

    return destinationString;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}




boost::posix_time::ptime toTimeStamp(T::TimeString timeStr)
{
  try
  {
    if (timeStr.length() <  15)
    {
      Fmi::Exception exception(BCP, "Invalid time string!");
      exception.addParameter("timeStr",timeStr);
      throw exception;
    }

    const char *s = timeStr.c_str();

    int year = NUM(s[0])*1000 + NUM(s[1])*100 + NUM(s[2])*10 + NUM(s[3]);
    int month = NUM(s[4])*10 + NUM(s[5]);
    int day = NUM(s[6])*10 + NUM(s[7]);
    int hour = NUM(s[9])*10 + NUM(s[10]);
    int minute = NUM(s[11])*10 + NUM(s[12]);
    int second = NUM(s[13])*10 + NUM(s[14]);

    return boost::posix_time::ptime(boost::gregorian::date(year, month, day),
                                      boost::posix_time::hours(hour) +
                                          boost::posix_time::minutes(minute) +
                                          boost::posix_time::seconds(second));
  }
  catch (...)
  {
    Fmi::Exception exception(BCP, "Operation failed!", nullptr);
    exception.addParameter("timeStr",timeStr);
    throw exception;
  }
}



int compressData(void *_data, uint _dataSize, void *_compressedData, uint &_compressedDataSize)
{
  try
  {
    uLongf comprLen = (uLongf)_compressedDataSize;
    compress((Bytef *)_compressedData, &comprLen, (Bytef *)_data, (uLong)_dataSize);

    if (comprLen > 0)
    {
      _compressedDataSize = comprLen;
      return 0;
    }

    _compressedDataSize = 0;
    return -1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



int decompressData(void *_compressedData,
                   uint _compressedDataSize,
                   void *_decompressedData,
                   uint &_decompressedDataSize)
{
  try
  {
    uLongf len = (uLongf)_decompressedDataSize;
    int res = uncompress((Bytef *)_decompressedData, &len, (Bytef *)_compressedData, (uLong)_compressedDataSize);
    _decompressedDataSize = len;

    if (res < 0)
    {
      _decompressedDataSize = 0;
      return -1;
    }

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void parseLatLonCoordinates(const std::string& latLonCoordinates, std::vector<T::Coordinate> &coordinates)
{
  try
  {
    char st[10000];
    strcpy(st, latLonCoordinates.c_str());
    char *field[1000];
    uint c = 1;
    field[0] = st;
    char *p = st;
    while (*p != '\0' && c < 1000)
    {
      if (*p == ';' || *p == ',')
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
      for (uint t = 0; t < c; t = t + 2)
      {
        coordinates.emplace_back(T::Coordinate(toDouble(field[t + 1]), toDouble(field[t])));
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void parseUnits(const char *unitString,double& value,std::string& units)
{
  try
  {
    const char *p = unitString;
    char val[100];
    char *v = val;
    char unit[100];
    char *u = unit;

    while (*p != '\0')
    {
      if (isdigit(*p))
      {
        *v = *p;
        v++;
      }

      if (isalpha(*p))
      {
        *u = *p;
        u++;
      }
      p++;
    }

    *u = '\0';
    *v = '\0';

    value = atof(val);
    units = unit;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}



void parseNetCdfTime(std::string& timeStr,int& year,int& month,int& day,int& hour,int& minute,int& second,time_t& unitSize)
{
  try
  {
    std::vector<std::string> partList;
    splitString(timeStr,' ',partList);

    if (partList.size() == 3 || partList.size() == 4)
    {
      if (strncasecmp(partList[0].c_str(),"day",3) == 0)
        unitSize = 3600*24;
      else
      if (strncasecmp(partList[0].c_str(),"hour",4) == 0)
        unitSize = 3600;
      else
      if (strncasecmp(partList[0].c_str(),"minute",6) == 0)
        unitSize = 60;
      if (strncasecmp(partList[0].c_str(),"second",6) == 0)
        unitSize = 1;


      std::vector<int> d;

      splitString(partList[2],'-',d);
      if (d.size() == 3)
      {
        year = d[0];
        month = d[1];
        day = d[2];
      }

      if (partList.size() == 4)
      {
        std::vector<float> t;
        splitString(partList[3],':',t);

        if (t.size() == 3)
        {
          hour = t[0];
          minute = t[1];
          second = (int)t[2];
        }
      }
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}




void splitString(const char *str, char separator, std::vector<std::string> &partList)
{
  try
  {
    char buf[10000];
    uint c = 0;
    char *p = const_cast<char *>(str);

    bool ind = false;
    while (*p != '\0' && *p != '\n' && c < 10000)
    {
      if (*p == '"') ind = !ind;

      if (*p == separator && !ind)
      {
        buf[c] = '\0';
        partList.emplace_back(std::string(buf));
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
      partList.emplace_back(std::string(buf));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const std::string& str, char separator, std::vector<std::string> &partList)
{
  try
  {
    splitString(str.c_str(), separator, partList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const char *str, char separator, std::set<std::string> &partList)
{
  try
  {
    char buf[10000];
    uint c = 0;
    char *p = const_cast<char *>(str);

    bool ind = false;
    while (*p != '\0' && *p != '\n' && c < 10000)
    {
      if (*p == '"') ind = !ind;

      if (*p == separator && !ind)
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
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const std::string& str, char separator, std::set<std::string> &partList)
{
  try
  {
    splitString(str.c_str(), separator, partList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const char *str, char separator, std::vector<uint> &partList)
{
  try
  {
    char buf[10000];
    uint c = 0;
    char *p = const_cast<char *>(str);

    bool ind = false;
    while (*p != '\0' && *p != '\n' && c < 10000)
    {
      if (*p == '"') ind = !ind;

      if (*p == separator && !ind)
      {
        buf[c] = '\0';
        partList.emplace_back(toUInt32(buf));
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
      partList.emplace_back(toUInt32(buf));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const std::string& str, char separator, std::vector<uint> &partList)
{
  try
  {
    splitString(str.c_str(), separator, partList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const char *str, char separator, std::vector<int> &partList)
{
  try
  {
    char buf[10000];
    uint c = 0;
    char *p = const_cast<char *>(str);

    bool ind = false;
    while (*p != '\0' && *p != '\n' && c < 10000)
    {
      if (*p == '"') ind = !ind;

      if (*p == separator && !ind)
      {
        buf[c] = '\0';
        partList.emplace_back(toInt32(buf));
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
      partList.emplace_back(toInt32(buf));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const std::string& str, char separator, std::vector<int> &partList)
{
  try
  {
    splitString(str.c_str(), separator, partList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const char *str, char separator, std::vector<double> &partList)
{
  try
  {
    char buf[10000];
    uint c = 0;
    char *p = const_cast<char *>(str);

    bool ind = false;
    while (*p != '\0' && *p != '\n' && c < 10000)
    {
      if (*p == '"') ind = !ind;

      if (*p == separator && !ind)
      {
        buf[c] = '\0';
        partList.emplace_back(toDouble(buf));
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
      partList.emplace_back(toDouble(buf));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const std::string& str, char separator, std::vector<double> &partList)
{
  try
  {
    splitString(str.c_str(), separator, partList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const char *str, char separator, std::vector<float> &partList)
{
  try
  {
    char buf[10000];
    uint c = 0;
    char *p = const_cast<char *>(str);

    bool ind = false;
    while (*p != '\0' && *p != '\n' && c < 10000)
    {
      if (*p == '"') ind = !ind;

      if (*p == separator && !ind)
      {
        buf[c] = '\0';
        partList.emplace_back(toDouble(buf));
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
      partList.emplace_back(toDouble(buf));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const std::string& str, char separator, std::vector<float> &partList)
{
  try
  {
    splitString(str.c_str(), separator, partList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const char *str, char separator, std::set<float> &partList)
{
  try
  {
    char buf[10000];
    uint c = 0;
    char *p = const_cast<char *>(str);

    bool ind = false;
    while (*p != '\0' && *p != '\n' && c < 10000)
    {
      if (*p == '"') ind = !ind;

      if (*p == separator && !ind)
      {
        buf[c] = '\0';
        partList.insert(toDouble(buf));
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
      partList.insert(toDouble(buf));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const std::string& str, char separator, std::set<float> &partList)
{
  try
  {
    splitString(str.c_str(), separator, partList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const char *str, char separator, std::set<int> &partList)
{
  try
  {
    char buf[10000];
    uint c = 0;
    char *p = const_cast<char *>(str);

    bool ind = false;
    while (*p != '\0' && *p != '\n' && c < 10000)
    {
      if (*p == '"') ind = !ind;

      if (*p == separator && !ind)
      {
        buf[c] = '\0';
        partList.insert(toInt32(buf));
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
      partList.insert(toInt32(buf));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const std::string& str, char separator, std::set<int> &partList)
{
  try
  {
    splitString(str.c_str(), separator, partList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const char *str, char separator, std::set<double> &partList)
{
  try
  {
    char buf[10000];
    uint c = 0;
    char *p = const_cast<char *>(str);

    bool ind = false;
    while (*p != '\0' && *p != '\n' && c < 10000)
    {
      if (*p == '"') ind = !ind;

      if (*p == separator && !ind)
      {
        buf[c] = '\0';
        partList.insert(toDouble(buf));
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
      partList.insert(toDouble(buf));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void splitString(const std::string& str, char separator, std::set<double> &partList)
{
  try
  {
    splitString(str.c_str(), separator, partList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string getAbsoluteFilePath(const std::string& filename)
{
  try
  {
    if (!filename.empty() && fs::exists(filename))
    {
      fs::path path(filename);
      if (!path.is_absolute())
      {
        path = fs::canonical(path);
        return path.string();
      }
      return path.string();
    }
    return filename;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string getFileDir(const std::string& filename)
{
  try
  {
    std::string fname = getAbsoluteFilePath(filename);
    std::string::size_type n = fname.rfind("/");
    if (n != std::string::npos) return fname.substr(0, n);

    n = fname.rfind("\\");
    if (n != std::string::npos) return fname.substr(0, n);

    return std::string("");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



bool patternMatch(const char *str, std::vector<std::string> &patterns)
{
  try
  {
    for (auto it = patterns.begin(); it != patterns.end(); ++it)
    {
      if (fnmatch(it->c_str(), str, 0) == 0) return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void getFileList(const char *dirName,
                 std::vector<std::string> &filePatterns,
                 bool includeSubDirs,
                 std::set<std::string> &dirList,
                 std::vector<std::pair<std::string, std::string>> &fileList)
{
  try
  {
    char *path = realpath(dirName, nullptr);
    if (path == nullptr)
    {
      return;
    }

    if (dirList.find(path) != dirList.end())
      return;  // Dir already processed

    DIR *dp = opendir(dirName);
    if (dp == nullptr)
    {
      return;
    }

    dirList.insert(std::string(dirName));

    bool ind = true;

    while (ind)
    {
      struct dirent *ep = readdir(dp);
      if (ep != nullptr)
      {
        char fullName[2000];
        sprintf(fullName, "%s/%s", path, ep->d_name);

        if (includeSubDirs && ep->d_type == DT_DIR && strcmp(ep->d_name, "..") != 0 &&
            strcmp(ep->d_name, ".") != 0)
        {
          getFileList(fullName, filePatterns, includeSubDirs, dirList, fileList);
        }
        else if (ep->d_type == DT_REG)
        {
          if (filePatterns.size() == 0 || patternMatch(ep->d_name, filePatterns))
            fileList.emplace_back(std::pair<std::string, std::string>(path, ep->d_name));
        }
        else if (ep->d_type == DT_UNKNOWN)
        {
          struct stat s;
          if (stat(fullName, &s) == 0)
          {
            if (includeSubDirs && (s.st_mode & S_IFDIR) != 0 && strcmp(ep->d_name, "..") != 0 &&
                strcmp(ep->d_name, ".") != 0)
            {
              getFileList(fullName, filePatterns, includeSubDirs, dirList, fileList);
            }
            else if (s.st_mode & S_IFREG)
            {
              if (filePatterns.size() == 0 || patternMatch(ep->d_name, filePatterns))
                fileList.emplace_back(std::pair<std::string, std::string>(path, ep->d_name));
            }
          }
        }
      }
      else
      {
        ind = false;
      }
    }
    closedir(dp);
    free(path);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



int timePeriodToSeconds(const char *timePeriod)
{
  try
  {
    char tmp[100];
    strcpy(tmp, timePeriod);
    char *p = strcasestr(tmp, "s");
    if (p != nullptr)
    {
      *p = '\0';
      return atoi(tmp);
    }
    else
    {
      char *p = strcasestr(tmp, "m");
      if (p != nullptr)
      {
        *p = '\0';
        return (atoi(tmp) * 60);
      }
      else
      {
        char *p = strcasestr(tmp, "h");
        if (p != nullptr)
        {
          *p = '\0';
          return (atoi(tmp) * 3600);
        }
        else
        {
          char *p = strcasestr(tmp, "d");
          if (p != nullptr)
          {
            *p = '\0';
            return (atoi(tmp) * 3600 * 24);
          }
          else
          {
            return (atoi(tmp) * 60);
          }
        }
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(std::list<std::string> &parts, char separator)
{
  try
  {
    std::ostringstream output;
    for (auto s = parts.begin(); s != parts.end(); ++s)
    {
      if (s != parts.begin()) output << separator;

      output << *s;
    }
    return output.str();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(std::set<int> &parts, char separator)
{
  try
  {
    std::ostringstream output;
    for (auto s = parts.begin(); s != parts.end(); ++s)
    {
      if (s != parts.begin()) output << separator;

      output << *s;
    }
    return output.str();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(std::set<float> &parts, char separator)
{
  try
  {
    std::ostringstream output;
    for (auto s = parts.begin(); s != parts.end(); ++s)
    {
      if (s != parts.begin()) output << separator;

      output << *s;
    }
    return output.str();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string toString(T::AreaCoordinates &coordinates, char separator1, char separator2)
{
  try
  {
    std::ostringstream output;
    for (auto s = coordinates.begin(); s != coordinates.end(); ++s)
    {
      if (s != coordinates.begin()) output << separator2;

      for (auto a = s->begin(); a != s->end(); ++a)
      {
        if (a != s->begin()) output << separator1;

        output << a->x() << separator1 << a->y();
      }
    }
    return output.str();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void parseCoordinates(const std::string& coordinateStr,
                      char separator1,
                      char separator2,
                      T::AreaCoordinates &coordinates)
{
  try
  {
    std::vector<std::string> partList;

    splitString(coordinateStr, separator2, partList);
    for (auto it = partList.begin(); it != partList.end(); ++it)
    {
      T::Coordinate_vec coordinateList;

      std::vector<double> cList;
      splitString(*it, separator1, cList);
      size_t sz = cList.size();
      if ((sz % 2) == 0)
      {
        for (size_t t = 0; t < sz; t = t + 2)
          coordinateList.emplace_back(T::Coordinate(cList[t], cList[t + 1]));
      }
      coordinates.emplace_back(coordinateList);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void tuneLevels(int &level1, int &level2, int newLevel)
{
  if (level1 <= newLevel && newLevel <= level2) return;

  int l1 = level1;
  int l2 = level2;

  while (newLevel > l2)
  {
    l1 = l1 * 10;
    l2 = l2 * 10;

    if (l1 <= newLevel && newLevel <= l2)
    {
      level1 = l1;
      level2 = l2;
      return;
    }
  }

  while (newLevel < l1)
  {
    l1 = l1 / 10;
    l2 = l2 / 10;

    if (l1 <= newLevel && newLevel <= l2)
    {
      level1 = l1;
      level2 = l2;
      return;
    }
  }
}



std::string base64_encode(unsigned char *data, size_t dataSize)
{
  try
  {
    namespace bai = boost::archive::iterators;

    const std::string base64_padding[] = {"", "==", "="};
    std::stringstream os;

    // convert binary values to base64 characters
    using base64_enc = bai::base64_from_binary<bai::transform_width<const char *, 6, 8>>;

    std::copy(base64_enc(data), base64_enc(data + dataSize), std::ostream_iterator<char>(os));

    os << base64_padding[dataSize % 3];
    return os.str();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string fileToBase64(const char *filename)
{
  try
  {
    long long size = getFileSize(filename);
    if (size <= 0)
    {
      Fmi::Exception exception(BCP, "Invalid file size!");
      exception.addParameter("Filename", filename);
      exception.addParameter("Size", std::to_string(size));
      throw exception;
    }

    FILE *file = fopen(filename, "r");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP, "Cannot open the file!");
      exception.addParameter("Filename", filename);
      throw exception;
    }

    unsigned char *data = new unsigned char[size + 1];
    size_t n = fread(data, 1, size, file);
    if (n <= 0)
    {
      fclose(file);
      delete[] data;
      Fmi::Exception exception(BCP, "File read failed!");
      exception.addParameter("Filename", filename);
      throw exception;
    }

    fclose(file);

    std::string st = base64_encode(data, size);
    delete[] data;

    return st;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





void readCsvFile(const char *filename,std::vector<std::vector<std::string>>& records)
{
  try
  {
    FILE *file = fopen(filename,"re");
    if (file == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot open file!");
      exception.addParameter("Filename",std::string(filename));
      throw exception;
    }

    char st[10000];

    while (!feof(file))
    {
      if (fgets(st,10000,file) != nullptr  &&  st[0] != '#')
      {
        std::vector<std::string> fields;
        bool ind = false;
        char *field[1000];
        uint c = 1;
        field[0] = st;
        char *p = st;
        while (*p != '\0'  &&  c < 100)
        {
          if (*p == '"')
            ind = !ind;

          if ((*p == ';'  || *p == '\n') && !ind)
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

        if (c > 1)
        {
          for (uint t=0; t<c; t++)
            fields.emplace_back(std::string(field[t]));

          records.emplace_back(fields);
        }
      }
    }
    fclose(file);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




std::uint8_t read_uint8(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos)
{
  try
  {
    if ((readPos + 1) > dataSize)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      exception.addParameter("Read position",uint64_toHex(readPos));
      exception.addParameter("Data size",std::to_string(dataSize));
      exception.addParameter("Bytes requested","1");
      throw exception;
    }

    unsigned char* rPtr = dataPtr + readPos;
    unsigned char val = rPtr[0];

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::uint16_t read_uint16(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos)
{
  try
  {
    if ((readPos + 2) > dataSize)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      exception.addParameter("Read position",uint64_toHex(readPos));
      exception.addParameter("Data size",std::to_string(dataSize));
      exception.addParameter("Bytes requested","2");
      throw exception;
    }

    unsigned char* rPtr = dataPtr + readPos;
    unsigned short a = rPtr[0];
    unsigned short b = rPtr[1];
    unsigned short val = static_cast<unsigned short>((a << 8 | b));

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::uint32_t read_uint24(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos)
{
  try
  {
    if ((readPos + 3) > dataSize)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      exception.addParameter("Read position",uint64_toHex(readPos));
      exception.addParameter("Data size",std::to_string(dataSize));
      exception.addParameter("Bytes requested","3");
      throw exception;
    }

    unsigned char* rPtr = dataPtr + readPos;
    uint a = rPtr[0];
    uint b = rPtr[1];
    uint c = rPtr[2];
    uint val =  static_cast<unsigned int>((a << 16 | b << 8 | c));

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::uint32_t read_uint32(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos)
{
  try
  {
    if ((readPos + 4) > dataSize)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      exception.addParameter("Read position",uint64_toHex(readPos));
      exception.addParameter("Data size",std::to_string(dataSize));
      exception.addParameter("Bytes requested","4");
      throw exception;
    }

    unsigned char* rPtr = dataPtr + readPos;

    uint a = rPtr[0];
    uint b = rPtr[1];
    uint c = rPtr[2];
    uint d = rPtr[3];
    uint val =  static_cast<unsigned int>((a << 24 | b << 16 | c << 8 | d));

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::uint64_t read_uint64(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos)
{
  try
  {
    if ((readPos + 8) > dataSize)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      exception.addParameter("Read position",uint64_toHex(readPos));
      exception.addParameter("Data size",std::to_string(dataSize));
      exception.addParameter("Bytes requested","8");
      throw exception;
    }

    unsigned char* rPtr = dataPtr + readPos;

    ulonglong a = rPtr[0];
    ulonglong b = rPtr[1];
    ulonglong c = rPtr[2];
    ulonglong d = rPtr[3];
    ulonglong e = rPtr[4];
    ulonglong f = rPtr[5];
    ulonglong g = rPtr[6];
    ulonglong h = rPtr[7];
    ulonglong val =  (a << 56 | b << 48 | c << 40 | d << 32 | e << 24 | f << 16 | g << 8 | h);

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::int8_t read_int8(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos)
{
  try
  {
    if ((readPos + 1) > dataSize)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      exception.addParameter("Read position",uint64_toHex(readPos));
      exception.addParameter("Data size",std::to_string(dataSize));
      exception.addParameter("Bytes requested","1");
      throw exception;
    }

    unsigned char* rPtr = dataPtr + readPos;
    unsigned char a = rPtr[0];
    unsigned char val = static_cast<char>((1 - ((a & 128) >> 6)) * (a & 127));

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::int16_t read_int16(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos)
{
  try
  {
    if ((readPos + 2) > dataSize)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      exception.addParameter("Read position",uint64_toHex(readPos));
      exception.addParameter("Data size",std::to_string(dataSize));
      exception.addParameter("Bytes requested","2");
      throw exception;
    }

    unsigned char* rPtr = dataPtr + readPos;

    unsigned char a = rPtr[0];
    unsigned char b = rPtr[1];
    short val = static_cast<short>((1 - ((a & 128) >> 6)) * ((a & 127) << 8 | b));

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::int32_t read_int24(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos)
{
  try
  {
    if ((readPos + 3) > dataSize)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      exception.addParameter("Read position",uint64_toHex(readPos));
      exception.addParameter("Data size",std::to_string(dataSize));
      exception.addParameter("Bytes requested","3");
      throw exception;
    }

    unsigned char* rPtr = dataPtr + readPos;
    unsigned char a = rPtr[0];
    unsigned char b = rPtr[1];
    unsigned char c = rPtr[2];
    int val =  static_cast<int>((1 - ((a & 128) >> 6)) * ((a & 127) << 24 | b << 16 | c << 8));

    val = val / 256;

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::int32_t read_int32(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos)
{
  try
  {
    if ((readPos + 4) > dataSize)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      exception.addParameter("Read position",uint64_toHex(readPos));
      exception.addParameter("Data size",std::to_string(dataSize));
      exception.addParameter("Bytes requested","4");
      throw exception;
    }

    unsigned char* rPtr = dataPtr + readPos;
    unsigned char a = rPtr[0];
    unsigned char b = rPtr[1];
    unsigned char c = rPtr[2];
    unsigned char d = rPtr[3];
    int val =  static_cast<int>((1 - ((a & 128) >> 6)) * ((a & 127) << 24 | b << 16 | c << 8 | d));

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::float_t read_float(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos)
{
  try
  {
    if ((readPos + 4) > dataSize)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      exception.addParameter("Read position",uint64_toHex(readPos));
      exception.addParameter("Data size",std::to_string(dataSize));
      exception.addParameter("Bytes requested","4");
      throw exception;
    }

    float val = 0.0;

    unsigned char* f = reinterpret_cast<unsigned char*>(&val);

    unsigned char* rPtr = dataPtr + readPos;

    f[0] = rPtr[3];
    f[1] = rPtr[2];
    f[2] = rPtr[1];
    f[3] = rPtr[0];

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::double_t read_double(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos)
{
  try
  {
    if ((readPos + 8) > dataSize)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      exception.addParameter("Read position",uint64_toHex(readPos));
      exception.addParameter("Data size",std::to_string(dataSize));
      exception.addParameter("Bytes requested","8");
      throw exception;
    }

    double val = 0.0;

    unsigned char* f = reinterpret_cast<unsigned char*>(&val);

    unsigned char* rPtr = dataPtr + readPos;

    f[0] = rPtr[7];
    f[1] = rPtr[6];
    f[2] = rPtr[5];
    f[3] = rPtr[4];
    f[4] = rPtr[3];
    f[5] = rPtr[2];
    f[6] = rPtr[1];
    f[7] = rPtr[0];

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




std::float_t read_ibmFloat(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos)
{
  try
  {
    if ((readPos + 4) > dataSize)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      exception.addParameter("Read position",uint64_toHex(readPos));
      exception.addParameter("Data size",std::to_string(dataSize));
      exception.addParameter("Bytes requested","4");
      throw exception;
    }

    unsigned char* rPtr = dataPtr + readPos;

    unsigned char a = rPtr[0];
    unsigned char b = rPtr[1];
    unsigned char c = rPtr[2];
    unsigned char d = rPtr[3];

    int mant = ( b &0xFF) << 16 | (c & 0xFF ) << 8 | ( d & 0xFF);
    if (mant == 0)
      return 0.0;

    int sgn = -(((a & 128) >> 6) - 1);
    int exp = (a & 127) - 64;

    return (float) (sgn * int_power(16.0, exp - 6) * mant);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




double mod(double x,double y)
{
  return (x - y * floor(x / y));
}



bool isGregorianLeapYear(int year)
{
    return ((year % 4) == 0) && (!(((year % 100) == 0) && ((year % 400) != 0)));
}




double gregorian_to_jd(int year, int month, int day)
{
  try
  {
    return (1721425.5 - 1) +
           (365 * (year - 1)) +
           floor((year - 1) / 4) +
           (-floor((year - 1) / 100)) +
           floor((year - 1) / 400) +
           floor((((367 * month) - 362) / 12) +
           ((month <= 2) ? 0 : (isGregorianLeapYear(year) ? -1 : -2)) +
           day);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



// Calculate Gregorian calendar date from Julian day number

void jdnToGregorian(double jd,int& year, int& month, int& day)
{
  try
  {
    double wjd = floor(jd - 0.5) + 0.5;
    double depoch = wjd - 1721425.5;
    double quadricent = floor(depoch / 146097);
    double dqc = mod(depoch, 146097);
    double cent = floor(dqc / 36524);
    double dcent = mod(dqc, 36524);
    double quad = floor(dcent / 1461);
    double dquad = mod(dcent, 1461);
    double yindex = floor(dquad / 365);

    year = (quadricent * 400) + (cent * 100) + (quad * 4) + yindex;
    if (!((cent == 4) || (yindex == 4)))
      year++;

    double yearday = wjd - gregorian_to_jd(year, 1, 1);
    double leapadj = 0;
    if (wjd >= gregorian_to_jd(year, 3, 1))
    {
      if (isGregorianLeapYear(year))
        leapadj = 1;
      else
        leapadj = 2;
    }

    month = floor((((yearday + leapadj) * 12) + 373) / 367);
    day = (wjd - gregorian_to_jd(year, month, 1)) + 1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




double gregorianToJdn(int year, int month, int day)
{
  try
  {
    return (1461 * (year + 4800 + (month - 14)/12))/4 +(367 * (month - 2 - 12 * ((month - 14)/12)))/12 - (3 * ((year + 4900 + (month - 14)/12)/100))/4 + day - 32075;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




double julianToJdn(int year, int month, int day)
{
  try
  {
    return (367 * year - (7 * (year + 5001 + (month - 9)/7))/4 + (275 * month)/9 + day + 1729777);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void jdnToJulian(double J,int& year, int& month, int& day)
{
  try
  {
    int y = 4716;
    int v = 3;
    int j = 1401;
    int u = 5;
    int m = 2;
    int s = 153;
    int n = 12;
    int w = 2;
    int r = 4;
    //int B = 274277;
    int p = 1461;
    //int C = -38;
    int f =  J + j;
    int e = r * f + v;
    int g = mod(e, p) / r;
    int h = u * g + w;
    day = (mod(h, s)) / u + 1;
    month = mod(h / s + m, n) + 1;
    year = (e / p) - y + (n + m - month) / n;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




time_t getGregorianTimeT(int refYear, int refMonth, int refDay,int refHour, int refMinute, int refSecond,time_t plusSeconds)
{
  try
  {
    if (refYear > 1582 || (refYear == 1582  &&  refMonth > 10) || (refYear == 1582  &&  refMonth == 10  && refDay >= 15))
    {
      // The rererence time is Gregorian

      time_t tt = utcTimeToTimeT(refYear,refMonth,refDay,refHour,refMinute,refSecond);
      return (tt + plusSeconds);
    }


    // The rererence time is Julian

    double jdn = julianToJdn(refYear,refMonth,refDay);

    time_t refSec = refHour*3600 + refMinute*60 + refSecond;
    time_t dayLen = 24*3600;
    time_t plusDays = plusSeconds / dayLen;
    time_t plusSec = plusSeconds % dayLen;
    time_t additionalSec = refSec + plusSec;

    if (additionalSec >= dayLen)
    {
      plusDays++;
      additionalSec = additionalSec - dayLen;
    }

    double newJdn = jdn + (double)plusDays;

    int year = 0;
    int month = 0;
    int day = 0;
    jdnToGregorian(newJdn,year,month,day);
    int hour = additionalSec / 3600;
    time_t t = additionalSec % 3600;
    int minute = t / 60;
    int second = t % 60;

    time_t tt = utcTimeToTimeT(year,month,day,hour,minute,second);
    return tt;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





int getClosestIndexPos(FloatVec& values,float value)
{
  try
  {
    int low = 0;
    int len = values.size();
    int high = len-1;
    int mid = 0;

    while (low <= high)
    {
      mid = (low + high) / 2;

      int res = num_compare(values[mid],value);

      if (res == 0)
        return mid;

      if (res < 0)
        low = mid + 1;
      else
        high = mid - 1;
    }

    if (mid >= 0  &&  mid < len)
    {
      if (num_compare(values[mid],value) < 0)
      {
        while (mid < len  &&  num_compare(values[mid],value) < 0)
          mid++;

        return mid-1;
      }
      else
      {
        while (mid > 0  &&  num_compare(values[mid],value) > 0)
          mid--;

        return mid;
      }
    }
    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




int getClosestIndexNeg(FloatVec& values,float value)
{
  //FUNCTION_TRACE
  try
  {
    int low = 0;
    int len = values.size();
    int high = len-1;
    int mid = 0;

    while (low <= high)
    {
      mid = (low + high) / 2;

      int res = num_compare(value,values[mid]);

      if (res == 0)
        return mid;

      if (res < 0)
        low = mid + 1;
      else
        high = mid - 1;
    }

    if (mid >= 0  &&  mid < len)
    {
      if (num_compare(value,values[mid]) < 0)
      {
        while (mid < len  &&  num_compare(value,values[mid]) < 0)
          mid++;

        return mid-1;
      }
      else
      {
        while (mid > 0  &&  num_compare(value,values[mid]) > 0)
          mid--;

        return mid;
      }
    }
    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




int getClosestIndex(FloatVec& values,float value)
{
  try
  {
    if (values.size() == 0)
      return 0;

    if (values[0] >= values[values.size()-1])
      return getClosestIndexPos(values,value);

    return getClosestIndexNeg(values,value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // Namespace SmartMet

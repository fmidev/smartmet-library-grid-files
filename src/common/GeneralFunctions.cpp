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
#include "Exception.h"
#include "GeneralDefinitions.h"

namespace fs = boost::filesystem;

namespace SmartMet
{
//ThreadLock timeThreadLock;
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ieee2ibm(void *to, void *from, int len)
{
  register unsigned fr; /* fraction */
  register int exp;     /* exponent */
  register int sgn;     /* sign */

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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string stringReplaceAll(std::string st,std::string oldStr,std::string newStr)
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
      // printf("%u:%c:%llu\n",idx,str[idx],id);
      idx++;
    }
    return C_UINT(id & 0xFFFFFFFF);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

int getInt(const char *str, uint startIdx, uint len)
{
  try
  {
    char buf[100];
    strncpy(buf, str + startIdx, len);
    buf[len] = '\0';
    return toInt64(buf);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    // boost::local_time::local_date_time t(utc_ptime, tz);

    boost::posix_time::time_duration td(tm->tm_hour,tm->tm_min,tm->tm_sec,0);
    boost::gregorian::date d(tm->tm_year + 1900,tm->tm_mon + 1,tm->tm_mday);
    boost::posix_time::ptime pt(d, td);

    boost::local_time::local_date_time ldt(pt.date(), pt.time_of_day(), zone, boost::local_time::local_date_time::EXCEPTION_ON_ERROR);
    boost::posix_time::ptime t = ldt.utc_time();

    time_t tt = (t - boost::posix_time::from_time_t(0)).total_seconds();
    return tt;

/*
    AutoThreadLock lock(&timeThreadLock);

    time_t ret;
    char *tz;
    tz = getenv("TZ");
    if (tz) tz = strdup(tz);
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

    printf("TIME %lu %lu (%s)\n",tt,ret,tzone);
    return ret;
*/
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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

    /*
    printf("%04d%02d%02dT%02d%02d%02d  ",
            tt->tm_year + 1900,
            tt->tm_mon + 1,
            tt->tm_mday,
            tt->tm_hour,
            tt->tm_min,
            tt->tm_sec);
*/
    return tt;

    /*
    AutoThreadLock lock(&timeThreadLock);

    char *tz;
    tz = getenv("TZ");
    if (tz) tz = strdup(tz);
    setenv("TZ", tzone, 1);
    tzset();

    localtime_r(&t, tt);

    if (tz)
    {
      setenv("TZ", tz, 1);
      free(tz);
    }
    else
      unsetenv("TZ");
    tzset();


    printf("%04d%02d%02dT%02d%02d%02d\n",
            tt->tm_year + 1900,
            tt->tm_mon + 1,
            tt->tm_mday,
            tt->tm_hour,
            tt->tm_min,
            tt->tm_sec);

    return tt;
    */
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

time_t localTimeToTimeT(std::string localTime, const char *tzone)
{
  try
  {
    if (localTime.length() != 15)
    {
      SmartMet::Spine::Exception exception(BCP,"Invalid timestamp format (expected YYYYMMDDTHHMMSS)!");
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

time_t utcTimeToTimeT(std::string utcTime)
{
  try
  {
    //printf("utcTimeToTimeT %s\n",utcTime.c_str());
    if (utcTime.length() != 15)
      throw SmartMet::Spine::Exception(BCP, "Invalid timestamp format (expected YYYYMMDDTHHMMSS)!");

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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void splitTimeString(const std::string& timeStr, int &year, int &month, int &day, int &hour, int &minute, int &second)
{
  try
  {
    if (timeStr.length() != 15)
      throw SmartMet::Spine::Exception(BCP, "Invalid timestamp format (expected YYYYMMDDTHHMMSS)!");

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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void splitTimeString(const std::string& timeStr, short &year, uchar &month, uchar &day, uchar &hour, uchar &minute, uchar &second)
{
  try
  {
    if (timeStr.length() != 15)
      throw SmartMet::Spine::Exception(BCP, "Invalid timestamp format (expected YYYYMMDDTHHMMSS)!");

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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string localTimeFromTimeT(time_t t, const char *tzone)
{
  try
  {
    struct tm tt;
    localtime_tz(t, &tt, tzone);

    char buf[30];
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string utcTimeFromTimeT(time_t t)
{
  try
  {
    struct tm tt;
    gmtime_r(&t, &tt);

    char buf[30];
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string localTimeToUtcTime(std::string localTime, const char *tzone)
{
  try
  {
    time_t t = localTimeToTimeT(localTime, tzone);
    return utcTimeFromTimeT(t);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string localTimeToUtc(std::string localTime, boost::local_time::time_zone_ptr tz)
{
  try
  {
    auto ptime = boost::posix_time::from_iso_string(localTime);
    boost::local_time::local_date_time localTime(ptime, tz);
    auto lTime = Fmi::TimeParser::make_time(localTime.date(), localTime.time_of_day(), tz);
    return Fmi::to_iso_string(lTime.utc_time());
  }
  catch (...)
  {
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
  }
}

std::string utcTimeToLocalTime(std::string utcTime, const char *tzone)
{
  try
  {
    time_t t = utcTimeToTimeT(utcTime);
    return localTimeFromTimeT(t, tzone);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string addSeconds(std::string timeStr, int seconds)
{
  try
  {
    time_t t = utcTimeToTimeT(timeStr);
    t = t + seconds;
    return utcTimeFromTimeT(t);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    float multiplier = 0.1;
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
    float powerer = *str == '-'? str++, 0.1 : 10;
    float power = 0;
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


double toDouble(const char *str)
{
  try
  {
    // Make sure that the environment variable LC_NUMERIC is defined
    // correctly (export LC_NUMERIC="en_US.UTF-8").

    if (str == nullptr)
      return 0.0;

    return atof(str);
    //return toDouble2(str);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(std::int8_t value)
{
  try
  {
    return std::to_string(C_INT(value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(std::int16_t value)
{
  try
  {
    return std::to_string(value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(std::int32_t value)
{
  try
  {
    return std::to_string(value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(std::int64_t value)
{
  try
  {
    return std::to_string(value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(std::uint8_t value)
{
  try
  {
    return std::to_string(C_UINT(value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(std::uint16_t value)
{
  try
  {
    return std::to_string(value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(std::uint32_t value)
{
  try
  {
    return std::to_string(value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(std::uint64_t value)
{
  try
  {
    return std::to_string(value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(T::UInt8_opt value)
{
  try
  {
    if (!value) return std::string("");

    return std::to_string(C_UINT(*value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(T::UInt16_opt value)
{
  try
  {
    if (!value) return std::string("");

    return std::to_string(*value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(T::UInt32_opt value)
{
  try
  {
    if (!value) return std::string("");

    return std::to_string(*value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(T::UInt64_opt value)
{
  try
  {
    if (!value) return std::string("");

    return std::to_string(*value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(T::Int8_opt value)
{
  try
  {
    if (!value) return std::string("");

    return std::to_string(C_INT(*value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(T::Int16_opt value)
{
  try
  {
    if (!value) return std::string("");

    return std::to_string(*value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(T::Int32_opt value)
{
  try
  {
    if (!value) return std::string("");

    return std::to_string(*value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toString(T::Int64_opt value)
{
  try
  {
    if (!value) return std::string("");

    return std::to_string(*value);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    std::transform(sourceString.begin(), sourceString.end(), destinationString.begin(), ::tolower);

    return destinationString;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

std::string toUpperString(std::string sourceString)
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    int res = uncompress(
        (Bytef *)_decompressedData, &len, (Bytef *)_compressedData, (uLong)_compressedDataSize);
    // printf("UNCOMPRESS %d\n",res);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void parseLatLonCoordinates(std::string latLonCoordinates, std::vector<T::Coordinate> &coordinates)
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
        coordinates.push_back(T::Coordinate(toDouble(field[t + 1]), toDouble(field[t])));
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
        partList.push_back(toUInt32(buf));
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
      partList.push_back(toUInt32(buf));
    }
  }
  catch (...)
  {
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
        partList.push_back(toInt32(buf));
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
      partList.push_back(toInt32(buf));
    }
  }
  catch (...)
  {
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
        partList.push_back(toDouble(buf));
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
      partList.push_back(toDouble(buf));
    }
  }
  catch (...)
  {
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
        partList.push_back(toDouble(buf));
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
      partList.push_back(toDouble(buf));
    }
  }
  catch (...)
  {
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
  }
}

std::string getAbsoluteFilePath(std::string filename)
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
  }
}

std::string getFileDir(std::string filename)
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
      // printf("Cannot find the dir [%s]\n", dirName);
      return;
    }

    if (dirList.find(path) != dirList.end()) return;  // Dir already processed

    // printf("DIR [%s]\n", path);

    DIR *dp = opendir(dirName);
    if (dp == nullptr)
    {
      // printf("Cannot open dir : %s\n",dirName);
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
            fileList.push_back(std::pair<std::string, std::string>(path, ep->d_name));
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
                fileList.push_back(std::pair<std::string, std::string>(path, ep->d_name));
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
  }
}

void parseCoordinates(std::string coordinateStr,
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
          coordinateList.push_back(T::Coordinate(cList[t], cList[t + 1]));
      }
      coordinates.push_back(coordinateList);
    }
  }
  catch (...)
  {
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
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
    typedef bai::base64_from_binary
        // retrieve 6 bit integers from a sequence of 8 bit bytes
        <bai::transform_width<const char *, 6, 8>>
            base64_enc;

    std::copy(base64_enc(data), base64_enc(data + dataSize), std::ostream_iterator<char>(os));

    os << base64_padding[dataSize % 3];
    return os.str();
  }
  catch (...)
  {
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
  }
}

std::string fileToBase64(const char *filename)
{
  try
  {
    long long size = getFileSize(filename);
    if (size <= 0)
    {
      Spine::Exception exception(BCP, "Invalid file size!");
      exception.addParameter("Filename", filename);
      exception.addParameter("Size", std::to_string(size));
      throw exception;
    }

    FILE *file = fopen(filename, "r");
    if (file == nullptr)
    {
      Spine::Exception exception(BCP, "Cannot open the file!");
      exception.addParameter("Filename", filename);
      throw exception;
    }

    unsigned char *data = new unsigned char[size + 1];
    size_t n = fread(data, 1, size, file);
    if (n <= 0)
    {
      fclose(file);
      delete[] data;
      Spine::Exception exception(BCP, "File read failed!");
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
    throw Spine::Exception(BCP, "Operation failed!", nullptr);
  }
}

}  // Namespace SmartMet

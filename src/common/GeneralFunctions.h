#pragma once

#include "Coordinate.h"
#include "../grid/Typedefs.h"

#include <string>
#include <set>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <macgyver/Exception.h>
#include <arpa/inet.h>


namespace SmartMet
{

typedef std::vector<float> FloatVec;

std::string uint64_toHex(unsigned long long value);
double int_power(double x, int y);
double grib_power(long s,long n);
unsigned long long getTime();
/*
int num_compare(char& v1,char& v2);
int num_compare(uchar& v1,uchar& v2);
int num_compare(short& v1,short& v2);
int num_compare(ushort& v1,ushort& v2);
int num_compare(int& v1,int& v2);
int num_compare(uint& v1,uint& v2);
int num_compare(unsigned long long& v1,unsigned long long& v2);
int num_compare(long long& v1,long long& v2);
int num_compare(float& v1,float& v2);
int num_compare(double& v1,double& v2);
int time_compare(time_t v1,time_t v2);
*/


void time_usleep(int _sec,int _usec);
uint stringToId(const char *str,uint len);
uint stringToId(const char *str);

float ibm2ieee(float ibmFloat);
float ieee2ibm(float value);

int timePeriodToSeconds(const char *timePeriod);

time_t localTimeToTimeT(const std::string& localTime,const char *tzone);
/*
std::string localTimeToUtcTime(std::string localTime,const char *tzone);
std::string utcTimeToLocalTime(std::string utcTime,const char *tzone);
*/

std::string utcTimeFromTimeT(time_t t);
time_t      utcTimeToTimeT(const std::string& utcTime);
time_t      utcTimeToTimeT(const char *utcTime);
time_t      utcTimeToTimeT(int year,int month,int day,int hour,int minute,int second);
std::string localTimeFromTimeT(time_t t,const char *tzone);
boost::posix_time::ptime toTimeStamp(T::TimeString timeStr);
std::string localTimeToUtc(const std::string& localTime,boost::local_time::time_zone_ptr tz);
void splitTimeString(const std::string& timeStr,int& year,int& month,int& day,int& hour,int& minute,int& second);
void splitTimeString(const std::string& timeStr, short &year, uchar &month, uchar &day, uchar &hour, uchar &minute, uchar &second);

std::string addSeconds(const std::string& timeStr,int seconds);
time_t mktime_tz(struct tm *tm, const char *tzone);
struct tm *localtime_tz(time_t t, struct tm *tt, const char *tzone);

time_t timeToValue(uint year,uint month,uint day,uint hour,uint min,uint sec,uint usec);
void valueToTime(time_t value,uint& year,uint& month,uint& day,uint& hour,uint& min,uint& sec,uint& usec);


time_t toTimeT(boost::posix_time::ptime tim);
time_t getFileModificationTime(const char *filename);
long long getFileSize(const char *filename);
std::string getAbsoluteFilePath(const std::string& filename);
std::string getFileDir(const std::string& filename);
int getInt(const char *str, uint startIdx, uint len);
long long getCsvInt64Field(const char *csv,uint fieldIndex);
int getCsvCompare(const char *csv,uint fieldIndex,const char *value);
int getCsvCaseCompare(const char *csv,uint fieldIndex,const char *value);

std::string space(uint size);

char        toInt8(const char *str);
short       toInt16(const char *str);
int         toInt32(const char *str);
long long   toInt64(const char *str);
uchar       toUInt8(const char *str);
ushort      toUInt16(const char *str);
uint        toUInt32(const char *str);
ulonglong   toUInt64(const char *str);
float       toFloat(const char *str);
double      toDouble(const char *str);
size_t      toSize_t(const char *str);

char        toInt8(const std::string& str);
short       toInt16(const std::string& str);
int         toInt32(const std::string& str);
long long   toInt64(const std::string& str);
uchar       toUInt8(const std::string& str);
ushort      toUInt16(const std::string& str);
uint        toUInt32(const std::string& str);
ulonglong   toUInt64(const std::string& str);
float       toFloat(const std::string& str);
double      toDouble(const std::string& str);
size_t      toSize_t(const std::string& str);


std::string toString(std::int8_t value);
std::string toString(std::int16_t value);
std::string toString(std::int32_t value);
std::string toString(std::int64_t value);
std::string toString(std::uint8_t value);
std::string toString(std::uint16_t value);
std::string toString(std::uint32_t value);
std::string toString(std::uint64_t value);
std::string toString(const std::string& value);
std::string toString(float value);
std::string toString(double value);
std::string toString(std::array<char,16> value);
std::string toString(T::UInt8_opt value);
std::string toString(T::UInt16_opt value);
std::string toString(T::UInt32_opt value);
std::string toString(T::UInt64_opt value);
std::string toString(T::Int8_opt value);
std::string toString(T::Int16_opt value);
std::string toString(T::Int32_opt value);
std::string toString(T::Int64_opt value);

std::string toString(boost::posix_time::ptime time);

std::string toLowerString(const char *sourceString);
std::string toLowerString(const std::string& sourceString);
std::string toUpperString(const char *sourceString);
std::string toUpperString(const std::string& sourceString);


int compressData(void *_data,uint _dataSize,void *_compressedData,uint& _compressedDataSize);
int decompressData(void *_compressedData,uint _compressedDataSize,void *_decompressedData,uint& _decompressedDataSize);

void parseLatLonCoordinates(const std::string& latLonCoordinates,std::vector<T::Coordinate>& coordinates);
void parseUnits(const char *unitString,double& value,std::string& units);

std::string stringReplaceAll(const std::string& st,const std::string& oldStr,std::string newStr);

void splitString(const char *str,char separator,std::vector<uint>& partList);
void splitString(const std::string& str,char separator,std::vector<uint>& partList);
void splitString(const char *str,char separator,std::vector<int>& partList);
void splitString(const std::string& str,char separator,std::vector<int>& partList);
void splitString(const char *str,char separator,std::vector<float>& partList);
void splitString(const std::string& str,char separator,std::vector<float>& partList);
void splitString(const char *str,char separator,std::vector<double>& partList);
void splitString(const std::string& str,char separator,std::vector<double>& partList);
void splitString(const char *str,char separator,std::vector<std::string>& partList);
void splitString(const std::string& str,char separator,std::vector<std::string>& partList);
void splitString(const char *str,char separator,std::set<std::string>& partList);
void splitString(const std::string& str,char separator,std::set<std::string>& partList);
void splitString(const char *str,char separator,std::set<float>& partList);
void splitString(const std::string& str,char separator,std::set<float>& partList);
void splitString(const char *str,char separator,std::set<double>& partList);
void splitString(const std::string& str,char separator,std::set<double>& partList);
void splitString(const char *str,char separator,std::set<int>& partList);
void splitString(const std::string& str,char separator,std::set<int>& partList);

void lineSplit(const char *str,std::vector<std::string> &lines);

std::string toString(std::list<std::string>& parts,char separator);
std::string toString(std::set<int>& parts,char separator);
std::string toString(std::set<float>& parts,char separator);
std::string toString(T::AreaCoordinates& coordinates,char separator1,char separator2);

void parseCoordinates(const std::string& coordinateStr,char separator1,char separator2,T::AreaCoordinates& coordinates);


bool patternMatch(const char *str,std::vector<std::string>& patterns);
void getFileList(const char *dirName,std::vector<std::string>& filePatterns,bool includeSubDirs,std::set<std::string>& dirList,std::vector<std::pair<std::string,std::string>>& fileList);
void tuneLevels(int& level1,int& level2,int newLevel);

std::string fileToBase64(const char *filename);
std::string base64_encode(unsigned char *data,size_t dataSize);

void readCsvFile(const char *filename,std::vector<std::vector<std::string>>& records);
void readEofLines(const char *filename,uint numberOfLines,std::vector<std::string>& lines);


std::uint8_t  read_uint8(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos);
std::uint16_t read_uint16(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos);
std::uint32_t read_uint24(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos);
std::uint32_t read_uint32(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos);
std::uint64_t read_uint64(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos);
std::int8_t   read_int8(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos);
std::int16_t  read_int16(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos);
std::int32_t  read_int24(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos);
std::int32_t  read_int32(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos);
std::float_t  read_float(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos);
std::double_t read_double(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos);
std::float_t  read_ibmFloat(unsigned char *dataPtr,ulonglong dataSize,ulonglong readPos);


void    jdnToGregorian(double jd,int& year, int& month, int& day);
double  gregorianToJdn(int year, int month, int day);
double  julianToJdn(int year, int month, int day);
void    jdnToJulian(double J,int& year, int& month, int& day);
time_t  getGregorianTimeT(int refYear, int refMonth, int refDay,int refHour, int refMinute, int refSecond,time_t plusSeconds);
void    parseNetCdfTime(std::string& timeStr,int& year,int& month,int& day,int& hour,int& minute,int& second,time_t& unitSize);


int getClosestIndexPos(FloatVec& values,float value);
int getClosestIndexNeg(FloatVec& values,float value);
int getClosestIndex(FloatVec& values,float value);

int hmac_sha256(const uint8_t *secretKey,int secretKeyLen,const uint8_t *input,int inputSize,uint8_t *output);

int signature_aws_s3_v4(const char *username,
                 const char *password,
                 const char *date,
                 const char *dateRegion,
                 const char *dateRegionService,
                 const char *stringToSign,
                 char *hexSignature);

void hash_sha256(uchar *input,int inputLen,char *hexHash);

std::string replaceVariables(const std::string& str,std::map<std::string,std::string>& variables);


inline int ptr_compare(char *v1, char *v2)
{
  if (v1 == v2)
    return 0;

  if (v1 < v2)
    return -1;

  return 1;
}




inline int num_compare(uint& v1, uint& v2)
{
  if (v1 == v2)
    return 0;

  if (v1 < v2)
    return -1;

  return 1;
}



inline int num_compare(char& v1, char& v2)
{
  if (v1 == v2)
    return 0;

  if (v1 < v2)
    return -1;

  return 1;
}



inline int num_compare(uchar& v1, uchar& v2)
{
  if (v1 == v2)
    return 0;

  if (v1 < v2)
    return -1;

  return 1;
}



inline int num_compare(short& v1, short& v2)
{
  if (v1 == v2)
    return 0;

  if (v1 < v2)
    return -1;

  return 1;
}



inline int num_compare(ushort& v1, ushort& v2)
{
  if (v1 == v2)
    return 0;

  if (v1 < v2)
    return -1;

  return 1;
}



inline int num_compare(int& v1, int& v2)
{
  if (v1 == v2)
    return 0;

  if (v1 < v2)
    return -1;

  return 1;
}



inline int num_compare(unsigned long long& v1, unsigned long long& v2)
{
  if (v1 == v2)
    return 0;

  if (v1 < v2)
    return -1;

  return 1;
}



inline int num_compare(long long& v1, long long& v2)
{
  if (v1 == v2)
    return 0;

  if (v1 < v2)
    return -1;

  return 1;
}



inline int num_compare(float& v1, float& v2)
{
  if (v1 == v2)
    return 0;

  if (v1 < v2)
    return -1;

  return 1;
}



inline int num_compare(double& v1, double& v2)
{
  if (v1 == v2)
    return 0;

  if (v1 < v2)
    return -1;

  return 1;
}



inline int time_compare(time_t v1, time_t v2)
{
  if (v1 == v2)
    return 0;

  if (v1 < v2)
    return -1;

  return 1;
}



inline long long htonll(long long value)
{
  static const int num = 42;

  if (*reinterpret_cast<const char*>(&num) == num)
    return ((long long)htonl((value & 0xFFFFFFFF) << 32) | htonl(value >> 32));

  return value;
}




inline long long ntohll(long long value)
{
  static const int num = 42;

  if (*reinterpret_cast<const char*>(&num) == num)
    return ((long long)ntohl((value & 0xFFFFFFFF) << 32) | ntohl(value >> 32));

  return value;
}

}

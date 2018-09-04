#pragma once

#include "Coordinate.h"
#include "../grid/Typedefs.h"

#include <string>
#include <set>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>


namespace SmartMet
{

std::string uint64_toHex(unsigned long long value);
double int_power(double x, int y);
double grib_power(long s,long n);
unsigned long long getTime();

int uint_compare(uint v1,uint v2);
int int_compare(int v1,int v2);
int uint64_compare(unsigned long long v1,unsigned long long v2);
int int64_compare(long long v1,long long v2);
int double_compare(double v1,double v2);
int time_compare(time_t v1,time_t v2);
void time_usleep(int _sec,int _usec);
uint stringToId(const char *str,uint len);
uint stringToId(const char *str);

float ibm2ieee(float ibmFloat);
float ieee2ibm(float value);


/*
time_t      localTimeToTimeT(std::string localTime,const char *tzone);
time_t      utcTimeToTimeT(std::string utcTime);
std::string utcTimeFromTimeT(time_t t);
std::string localTimeToUtcTime(std::string localTime,const char *tzone);
std::string utcTimeToLocalTime(std::string utcTime,const char *tzone);
*/
std::string localTimeFromTimeT(time_t t,const char *tzone);
boost::posix_time::ptime toTimeStamp(T::TimeString timeStr);
std::string localTimeToUtc(std::string localTime,boost::local_time::time_zone_ptr tz);


time_t toTimeT(boost::posix_time::ptime tim);
time_t getFileModificationTime(const char *filename);
long long getFileSize(const char *filename);
std::string getAbsoluteFilePath(std::string filename);
std::string getFileDir(std::string filename);

std::string space(uint size);

char        toInt8(const char *str);
short       toInt16(const char *str);
int         toInt32(const char *str);
long long   toInt64(const char *str);

uchar       toUInt8(const char *str);
ushort      toUInt16(const char *str);
uint        toUInt32(const char *str);
ulonglong   toUInt64(const char *str);

double      toDouble(const char *str);

std::string toString(std::int8_t value);
std::string toString(std::int16_t value);
std::string toString(std::int32_t value);
std::string toString(std::int64_t value);
std::string toString(std::uint8_t value);
std::string toString(std::uint16_t value);
std::string toString(std::uint32_t value);
std::string toString(std::uint64_t value);
std::string toString(std::string value);
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

std::string toLowerString(std::string sourceString);


int compressData(void *_data,uint _dataSize,void *_compressedData,uint& _compressedDataSize);
int decompressData(void *_compressedData,uint _compressedDataSize,void *_decompressedData,uint& _decompressedDataSize);

void parseLatLonCoordinates(std::string latLonCoordinates,std::vector<T::Coordinate>& coordinates);
void splitString(const char *str,char separator,std::vector<float>& partList);
void splitString(std::string str,char separator,std::vector<float>& partList);
void splitString(const char *str,char separator,std::vector<double>& partList);
void splitString(std::string str,char separator,std::vector<double>& partList);
void splitString(const char *str,char separator,std::vector<std::string>& partList);
void splitString(std::string str,char separator,std::vector<std::string>& partList);
void splitString(const char *str,char separator,std::set<std::string>& partList);
void splitString(std::string str,char separator,std::set<std::string>& partList);


bool patternMatch(const char *str,std::vector<std::string>& patterns);
void getFileList(const char *dirName,std::vector<std::string>& filePatterns,bool includeSubDirs,std::set<std::string>& dirList,std::vector<std::pair<std::string,std::string>>& fileList);

}

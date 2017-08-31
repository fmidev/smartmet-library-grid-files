#pragma once

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "grid/Typedefs.h"


namespace SmartMet
{

std::string uint64_toHex(unsigned long long value);
double int_power(double x, int y);
double grib_power(long s,long n);
unsigned long long getTime();

int uint_compare(uint v1,uint v2);
int uint64_compare(unsigned long long v1,unsigned long long v2);
int double_compare(double v1,double v2);
int time_compare(time_t v1,time_t v2);
void time_usleep(int _sec,int _usec);
uint stringToId(const char *str,uint len);


boost::posix_time::ptime toTimeStamp(T::TimeString timeStr);

time_t toTimeT(boost::posix_time::ptime tim);
time_t getFileModificationTime(const char *filename);
long long getFileSize(const char *filename);

std::string space(uint size);

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


int compressData(void *_data,uint _dataSize,void *_compressedData,uint& _compressedDataSize);
int decompressData(void *_compressedData,uint _compressedDataSize,void *_decompressedData,uint& _decompressedDataSize);

}

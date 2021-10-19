#pragma once

#include <vector>
#include <set>
#include <string>
#include <array>
#include <cstdint>
#include <cmath>


namespace SmartMet
{

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;
typedef std::float_t ibmfloat;

typedef std::set<std::string> string_set;
typedef std::vector<std::string> string_vec;
typedef std::vector<double> double_vec;
typedef std::vector<uchar> uchar_vec;
typedef std::vector<uint> uint_vec;

template <typename A>
bool missing(const A& obj)
{
  return !obj;
}

namespace T
{
  typedef std::vector<uchar> ByteData;
  typedef std::vector<ByteData> ByteData_vec;
}

}




namespace std
{
  typedef int32_t int24_t;
  typedef uint32_t uint24_t;
}




#define C_CHAR(x) static_cast<char>(x)
#define C_SHORT(x) static_cast<short>(x)
#define C_INT(x) static_cast<int>(x)
#define C_LONG(x) static_cast<long>(x)
#define C_INT64(x) static_cast<long long>(x)
#define C_UCHAR(x) static_cast<uchar>(x)
#define C_UCHAR_PTR(x) static_cast<uchar*>(x)
#define C_USHORT(x) static_cast<ushort>(x)
#define C_UINT(x) static_cast<uint>(x)
#define C_ULONG(x) static_cast<ulong>(x)
#define C_UINT64(x) static_cast<unsigned long long>(x)
#define C_DOUBLE(_x) static_cast<double>(_x)
#define C_FLOAT(x) static_cast<float>(x)

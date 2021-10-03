#pragma once

#include <vector>
#include <set>
#include <string>
#include <array>
#include <cstdint>
#include <cmath>


namespace SmartMet
{

using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long;
using longlong = long long;
using ulonglong = unsigned long long;
using ibmfloat = std::float_t;

using string_set = std::set<std::string>;
using string_vec = std::vector<std::string>;
using double_vec = std::vector<double>;
using uchar_vec = std::vector<uchar>;

template <typename A>
bool missing(const A& obj)
{
  return !obj;
}

namespace T
{
  using ByteData = std::vector<uchar>;
  using ByteData_vec = std::vector<ByteData>;
}

}




namespace std
{
  using int24_t = int32_t;
  using uint24_t = uint32_t;
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

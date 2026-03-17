#pragma once

#include <vector>
#include <set>
#include <string>
#include <array>
#include <cstdint>
#include <cmath>

namespace std
{
  typedef int32_t int24_t;
  typedef uint32_t uint24_t;
}

namespace SmartMet
{

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef std::float_t ibmfloat;


typedef std::int8_t Int8;
typedef std::int16_t Int16;
typedef std::int32_t Int32;
typedef std::int64_t Int64;
typedef std::uint8_t UInt8;
typedef std::uint16_t UInt16;
typedef std::uint32_t UInt32;
typedef std::uint64_t UInt64;

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

  typedef std::optional<std::int8_t> Int8_opt;
  typedef std::optional<std::int16_t> Int16_opt;
  typedef std::optional<std::int32_t> Int32_opt;
  typedef std::optional<std::int64_t> Int64_opt;
  typedef std::optional<std::uint8_t> UInt8_opt;
  typedef std::optional<std::uint16_t> UInt16_opt;
  typedef std::optional<std::uint24_t> UInt24_opt;
  typedef std::optional<std::uint32_t> UInt32_opt;
  typedef std::optional<std::uint64_t> UInt64_opt;
  typedef std::optional<std::float_t> Float_opt;
}

}







#define C_CHAR(x) static_cast<char>(x)
#define C_SHORT(x) static_cast<short>(x)
#define C_INT(x) static_cast<int>(x)
#define C_LONG(x) static_cast<long>(x)
#define C_INT64(x) static_cast<Int64>(x)
#define C_UCHAR(x) static_cast<uchar>(x)
#define C_UCHAR_PTR(x) static_cast<uchar*>(x)
#define C_USHORT(x) static_cast<ushort>(x)
#define C_UINT(x) static_cast<uint>(x)
#define C_ULONG(x) static_cast<ulong>(x)
#define C_UINT64(x) static_cast<UInt64>(x)
#define C_DOUBLE(_x) static_cast<double>(_x)
#define C_FLOAT(x) static_cast<float>(x)

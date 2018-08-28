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
typedef unsigned long long ulonglong;
typedef std::float_t ibmfloat;

typedef std::set<std::string> string_set;
typedef std::vector<std::string> string_vec;
typedef std::vector<double> double_vec;

template <typename A>
bool missing(const A& obj)
{
  return !obj;
}


}


namespace std
{
  typedef int32_t int24_t;
  typedef uint32_t uint24_t;
};

#pragma once

#include <vector>
#include <set>
#include <string>
#include <array>
#include <cstdint>
#include <cmath>
#include <optional>

/*! \brief Portable 24-bit integer aliases injected into std for uniform numeric handling. */
namespace std
{
  using int24_t = int32_t;  //!< Signed 24-bit integer stored in 32 bits
  using uint24_t = uint32_t; //!< Unsigned 24-bit integer stored in 32 bits
}

/*! \brief Root namespace for the SmartMet Server framework and all sub-libraries. */
namespace SmartMet
{

using uchar = unsigned char;   //!< Byte alias used throughout the codebase
using ushort = unsigned short; //!< 16-bit unsigned alias
using uint = unsigned int;     //!< 32-bit unsigned alias
using ulong = unsigned long;   //!< Platform-width unsigned alias
using ibmfloat = std::float_t; //!< IBM 360 floating-point value stored as a native float


using Int8 = std::int8_t;    //!< Signed 8-bit integer
using Int16 = std::int16_t;  //!< Signed 16-bit integer
using Int32 = std::int32_t;  //!< Signed 32-bit integer
using Int64 = std::int64_t;  //!< Signed 64-bit integer
using UInt8 = std::uint8_t;  //!< Unsigned 8-bit integer
using UInt16 = std::uint16_t; //!< Unsigned 16-bit integer
using UInt32 = std::uint32_t; //!< Unsigned 32-bit integer
using UInt64 = std::uint64_t; //!< Unsigned 64-bit integer

using string_set = std::set<std::string>;   //!< Set of unique strings
using string_vec = std::vector<std::string>; //!< Ordered list of strings
using double_vec = std::vector<double>;      //!< Ordered list of doubles
using uchar_vec = std::vector<uchar>;        //!< Byte vector
using uint_vec = std::vector<uint>;          //!< Unsigned-int vector

/*! \brief Return true if \p obj is a disengaged optional (or a nullptr-like null state).
 *  \tparam A  Type that is contextually convertible to bool.
 *  \param[in] obj  Value to test.
 *  \return True when \p obj evaluates to false. */
template <typename A>
bool missing(const A& obj)
{
  return !obj;
}

/*! \brief Sub-namespace for SmartMet grid type aliases and strongly-typed identifiers. */
namespace T
{
  using ByteData = std::vector<uchar>;          //!< Raw byte buffer
  using ByteData_vec = std::vector<ByteData>;   //!< List of raw byte buffers

  using Int8_opt = std::optional<std::int8_t>;      //!< Optional signed 8-bit integer
  using Int16_opt = std::optional<std::int16_t>;    //!< Optional signed 16-bit integer
  using Int32_opt = std::optional<std::int32_t>;    //!< Optional signed 32-bit integer
  using Int64_opt = std::optional<std::int64_t>;    //!< Optional signed 64-bit integer
  using UInt8_opt = std::optional<std::uint8_t>;    //!< Optional unsigned 8-bit integer
  using UInt16_opt = std::optional<std::uint16_t>;  //!< Optional unsigned 16-bit integer
  using UInt24_opt = std::optional<std::uint24_t>;  //!< Optional unsigned 24-bit integer
  using UInt32_opt = std::optional<std::uint32_t>;  //!< Optional unsigned 32-bit integer
  using UInt64_opt = std::optional<std::uint64_t>;  //!< Optional unsigned 64-bit integer
  using Float_opt = std::optional<std::float_t>;    //!< Optional single-precision float
}

}







/** @name Explicit-cast convenience macros
 *  Suppress implicit-conversion warnings for numeric narrowing operations. @{ */
#define C_CHAR(x)     static_cast<char>(x)    //!< Cast to char
#define C_SHORT(x)    static_cast<short>(x)   //!< Cast to short
#define C_INT(x)      static_cast<int>(x)     //!< Cast to int
#define C_LONG(x)     static_cast<long>(x)    //!< Cast to long
#define C_INT64(x)    static_cast<Int64>(x)   //!< Cast to Int64
#define C_UCHAR(x)    static_cast<uchar>(x)   //!< Cast to uchar
#define C_UCHAR_PTR(x) static_cast<uchar*>(x) //!< Cast to uchar*
#define C_USHORT(x)   static_cast<ushort>(x)  //!< Cast to ushort
#define C_UINT(x)     static_cast<uint>(x)    //!< Cast to uint
#define C_ULONG(x)    static_cast<ulong>(x)   //!< Cast to ulong
#define C_UINT64(x)   static_cast<UInt64>(x)  //!< Cast to UInt64
#define C_DOUBLE(_x)  static_cast<double>(_x) //!< Cast to double
#define C_FLOAT(x)    static_cast<float>(x)   //!< Cast to float
/** @} */

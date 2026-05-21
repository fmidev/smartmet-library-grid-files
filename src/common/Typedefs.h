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
  typedef int32_t int24_t;  //!< Signed 24-bit integer stored in 32 bits
  typedef uint32_t uint24_t; //!< Unsigned 24-bit integer stored in 32 bits
}

/*! \brief Root namespace for the SmartMet Server framework and all sub-libraries. */
namespace SmartMet
{

typedef unsigned char uchar;   //!< Byte alias used throughout the codebase
typedef unsigned short ushort; //!< 16-bit unsigned alias
typedef unsigned int uint;     //!< 32-bit unsigned alias
typedef unsigned long ulong;   //!< Platform-width unsigned alias
typedef std::float_t ibmfloat; //!< IBM 360 floating-point value stored as a native float


typedef std::int8_t Int8;    //!< Signed 8-bit integer
typedef std::int16_t Int16;  //!< Signed 16-bit integer
typedef std::int32_t Int32;  //!< Signed 32-bit integer
typedef std::int64_t Int64;  //!< Signed 64-bit integer
typedef std::uint8_t UInt8;  //!< Unsigned 8-bit integer
typedef std::uint16_t UInt16; //!< Unsigned 16-bit integer
typedef std::uint32_t UInt32; //!< Unsigned 32-bit integer
typedef std::uint64_t UInt64; //!< Unsigned 64-bit integer

typedef std::set<std::string> string_set;   //!< Set of unique strings
typedef std::vector<std::string> string_vec; //!< Ordered list of strings
typedef std::vector<double> double_vec;      //!< Ordered list of doubles
typedef std::vector<uchar> uchar_vec;        //!< Byte vector
typedef std::vector<uint> uint_vec;          //!< Unsigned-int vector

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
  typedef std::vector<uchar> ByteData;          //!< Raw byte buffer
  typedef std::vector<ByteData> ByteData_vec;   //!< List of raw byte buffers

  typedef std::optional<std::int8_t> Int8_opt;      //!< Optional signed 8-bit integer
  typedef std::optional<std::int16_t> Int16_opt;    //!< Optional signed 16-bit integer
  typedef std::optional<std::int32_t> Int32_opt;    //!< Optional signed 32-bit integer
  typedef std::optional<std::int64_t> Int64_opt;    //!< Optional signed 64-bit integer
  typedef std::optional<std::uint8_t> UInt8_opt;    //!< Optional unsigned 8-bit integer
  typedef std::optional<std::uint16_t> UInt16_opt;  //!< Optional unsigned 16-bit integer
  typedef std::optional<std::uint24_t> UInt24_opt;  //!< Optional unsigned 24-bit integer
  typedef std::optional<std::uint32_t> UInt32_opt;  //!< Optional unsigned 32-bit integer
  typedef std::optional<std::uint64_t> UInt64_opt;  //!< Optional unsigned 64-bit integer
  typedef std::optional<std::float_t> Float_opt;    //!< Optional single-precision float
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

#include "MemoryReader.h"
#include "Exception.h"
#include "GeneralFunctions.h"

namespace SmartMet
{


/*! \brief The constructor of the class. */

MemoryReader::MemoryReader(unsigned char *_startPtr,ulonglong _size)
{
  try
  {
    if (_startPtr == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The '_startPtr' parameter points to nullptr!");

    if (_size == 0)
      throw SmartMet::Spine::Exception(BCP,"The value of the '_size' parameter is 0!");

    parentPtr = _startPtr;
    startPtr = _startPtr;
    endPtr = _startPtr + _size;
    readPtr = _startPtr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The constructor of the class. */

MemoryReader::MemoryReader(unsigned char *_startPtr,unsigned char *_endPtr)
{
  try
  {
    if (_startPtr == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The '_startPtr' parameter points to nullptr!");

    if (_endPtr == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The '_endPtr' parameter points to nullptr!");

    if (_endPtr < _startPtr)
      throw SmartMet::Spine::Exception(BCP,"The value of the '_endPtr' parameter is smaller than '_startPtr'!");

    parentPtr = _startPtr;
    startPtr = _startPtr;
    endPtr = _endPtr;
    readPtr = _startPtr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The destructor of the class. */

MemoryReader::~MemoryReader()
{
  try
  {
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





ulonglong MemoryReader::getDataSize()
{
  try
  {
    return C_UINT64(endPtr-startPtr);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MemoryReader::setParentPtr(unsigned char *_parentPtr)
{
  try
  {
    parentPtr = _parentPtr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





unsigned char* MemoryReader::getParentPtr()
{
  try
  {
    return parentPtr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





unsigned char* MemoryReader::getStartPtr()
{
  try
  {
    return startPtr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





unsigned char* MemoryReader::getEndPtr()
{
  try
  {
    return endPtr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





unsigned char* MemoryReader::getReadPtr()
{
  try
  {
    return readPtr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MemoryReader::setReadPtr(unsigned char *_readPtr)
{
  try
  {
    if (_readPtr == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The '_readPtr' parameter points to nullptr!");

    if (_readPtr < startPtr  ||  _readPtr > endPtr)
      throw SmartMet::Spine::Exception(BCP,"The value of the '_readPtr' parameter is out of the range!");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





ulonglong MemoryReader::getReadPosition()
{
  try
  {
    return C_UINT64(readPtr-startPtr);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





ulonglong MemoryReader::getGlobalReadPosition()
{
  try
  {
    return C_UINT64(readPtr-parentPtr);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MemoryReader::setReadPosition(ulonglong _pos)
{
  try
  {
    if ((startPtr + _pos) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"The value of the '_pos' parameter is out of the range!");

    readPtr = startPtr + _pos;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





unsigned char MemoryReader::getByte(ulonglong _pos)
{
  try
  {
    if ((startPtr + _pos) >= endPtr)
    {
      SmartMet::Spine::Exception exception(BCP,"The value of the '_pos' parameter is out of the range!");
      exception.addParameter("Pos",std::to_string(_pos));
      exception.addParameter("Size",std::to_string(getDataSize()));
      throw exception;
    }

    return *(startPtr+_pos);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





unsigned char MemoryReader::getByte(unsigned char *_posPtr)
{
  try
  {
    if (_posPtr < startPtr || _posPtr >= endPtr)
      throw SmartMet::Spine::Exception(BCP,"The value of the '_posPtr' parameter is out of the range!");

    return *_posPtr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool MemoryReader::peek_string(const char *_str)
{
  try
  {
    if (_str == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The '_str' parameter points to nullptr!");

    ulonglong len = strlen(_str);
    if ((readPtr + len) > endPtr)
      return false;

    if (memcmp(readPtr,_str,len) == 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::uint8_t MemoryReader::read_uint8()
{
  try
  {
    if ((readPtr + 1) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    unsigned char val = readPtr[0];

    readPtr++;

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::uint16_t MemoryReader::read_uint16()
{
  try
  {
    if ((readPtr + 2) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    unsigned short a = readPtr[0];
    unsigned short b = readPtr[1];
    unsigned short val = static_cast<unsigned short>((a << 8 | b));

    readPtr += 2;

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::uint32_t MemoryReader::read_uint24()
{
  try
  {
    if ((readPtr + 3) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    uint a = readPtr[0];
    uint b = readPtr[1];
    uint c = readPtr[2];
    uint val =  static_cast<unsigned int>((a << 16 | b << 8 | c));

    readPtr += 3;

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::uint32_t MemoryReader::read_uint32()
{
  try
  {
    if ((readPtr + 4) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    uint a = readPtr[0];
    uint b = readPtr[1];
    uint c = readPtr[2];
    uint d = readPtr[3];
    uint val =  static_cast<unsigned int>((a << 24 | b << 16 | c << 8 | d));

    readPtr += 4;

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::uint64_t MemoryReader::read_uint64()
{
  try
  {
    if ((readPtr + 8) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    ulonglong a = readPtr[0];
    ulonglong b = readPtr[1];
    ulonglong c = readPtr[2];
    ulonglong d = readPtr[3];
    ulonglong e = readPtr[4];
    ulonglong f = readPtr[5];
    ulonglong g = readPtr[6];
    ulonglong h = readPtr[7];
    ulonglong val =  (a << 56 | b << 48 | c << 40 | d << 32 | e << 24 | f << 16 | g << 8 | h);

    readPtr += 8;

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::int8_t MemoryReader::read_int8()
{
  try
  {
    if ((readPtr + 1) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    unsigned char a = readPtr[0];
    unsigned char val = static_cast<char>((1 - ((a & 128) >> 6)) * (a & 127));

    readPtr++;

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::int16_t MemoryReader::read_int16()
{
  try
  {
    if ((readPtr + 2) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    unsigned char a = readPtr[0];
    unsigned char b = readPtr[1];
    short val = static_cast<short>((1 - ((a & 128) >> 6)) * ((a & 127) << 8 | b));

    readPtr += 2;

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::int32_t MemoryReader::read_int24()
{
  try
  {
    if ((readPtr + 3) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    unsigned char a = readPtr[0];
    unsigned char b = readPtr[1];
    unsigned char c = readPtr[2];
    int val =  static_cast<int>((1 - ((a & 128) >> 6)) * ((a & 127) << 24 | b << 16 | c << 8));
    val = val / 256;


    readPtr += 3;

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::int32_t MemoryReader::read_int32()
{
  try
  {
    if ((readPtr + 4) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    unsigned char a = readPtr[0];
    unsigned char b = readPtr[1];
    unsigned char c = readPtr[2];
    unsigned char d = readPtr[3];
    int val =  static_cast<int>((1 - ((a & 128) >> 6)) * ((a & 127) << 24 | b << 16 | c << 8 | d));

    readPtr += 4;

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::float_t MemoryReader::read_float()
{
  try
  {
    if ((readPtr + 4) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    float val = 0.0;

    unsigned char* f = reinterpret_cast<unsigned char*>(&val);

    f[0] = readPtr[3];
    f[1] = readPtr[2];
    f[2] = readPtr[1];
    f[3] = readPtr[0];

    readPtr += 4;

    return val;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::float_t MemoryReader::read_ibmFloat()
{
  try
  {
    if ((readPtr + 4) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    unsigned char a = readPtr[0];
    unsigned char b = readPtr[1];
    unsigned char c = readPtr[2];
    unsigned char d = readPtr[3];

    readPtr += 4;

    int mant = ( b &0xFF) << 16 | (c & 0xFF ) << 8 | ( d & 0xFF);
    if (mant == 0)
      return 0.0;

    int sgn = -(((a & 128) >> 6) - 1);
    int exp = (a & 127) - 64;

    return (float) (sgn * int_power(16.0, exp - 6) * mant);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::array<char,16> MemoryReader::read_uuid()
{
  try
  {
    if ((readPtr + 16) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    std::array<char, 16> ret;
    for (auto i = 0; i < 16; i++)
      ret[i] = readPtr[i];

    readPtr += 16;

    return ret;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::UInt8_opt MemoryReader::read_UInt8_opt()
{
  try
  {
    if ((readPtr + 1) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    unsigned char val = readPtr[0];

    readPtr++;

    if (!(val == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::UInt16_opt MemoryReader::read_UInt16_opt()
{
  try
  {
    if ((readPtr + 2) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    unsigned short a = readPtr[0];
    unsigned short b = readPtr[1];
    unsigned short val = static_cast<unsigned short>((a << 8 | b));

    readPtr += 2;

    if (!(a == 0xFF  &&  b == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::UInt32_opt MemoryReader::read_UInt24_opt()
{
  try
  {
    if ((readPtr + 3) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    uint a = readPtr[0];
    uint b = readPtr[1];
    uint c = readPtr[2];
    uint val =  static_cast<unsigned int>((a << 16 | b << 8 | c));

    readPtr += 3;

    if (!(a == 0xFF  &&  b == 0xFF  &&  c == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::UInt32_opt MemoryReader::read_UInt32_opt()
{
  try
  {
    if ((readPtr + 4) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    uint a = readPtr[0];
    uint b = readPtr[1];
    uint c = readPtr[2];
    uint d = readPtr[3];
    uint val =  static_cast<unsigned int>((a << 24 | b << 16 | c << 8 | d));

    readPtr += 4;

    if (!(a == 0xFF  &&  b == 0xFF  &&  c == 0xFF  &&  d == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::UInt64_opt MemoryReader::read_UInt64_opt()
{
  try
  {
    if ((readPtr + 8) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    ulonglong a = readPtr[0];
    ulonglong b = readPtr[1];
    ulonglong c = readPtr[2];
    ulonglong d = readPtr[3];
    ulonglong e = readPtr[4];
    ulonglong f = readPtr[5];
    ulonglong g = readPtr[6];
    ulonglong h = readPtr[7];
    ulonglong val =  (a << 56 | b << 48 | c << 40 | d << 32 | e << 24 | f << 16 | g << 8 | h);

    readPtr += 8;

    if (!(a == 0xFF  &&  b == 0xFF  &&  c == 0xFF  &&  d == 0xFF  &&  e == 0xFF  &&  f == 0xFF  &&  g == 0xFF  &&  h == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::Int8_opt MemoryReader::read_Int8_opt()
{
  try
  {
    if ((readPtr + 1) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    unsigned char a = readPtr[0];
    unsigned char val = static_cast<char>((1 - ((a & 128) >> 6)) * (a & 127));

    readPtr++;

    if (!(a == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::Int16_opt MemoryReader::read_Int16_opt()
{
  try
  {
    if ((readPtr + 2) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    unsigned char a = readPtr[0];
    unsigned char b = readPtr[1];
    short val = static_cast<short>((1 - ((a & 128) >> 6)) * ((a & 127) << 8 | b));

    readPtr += 2;

    if (!(a == 0xFF  &&  b == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::Int32_opt MemoryReader::read_Int24_opt()
{
  try
  {
    if ((readPtr + 3) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    unsigned char a = readPtr[0];
    unsigned char b = readPtr[1];
    unsigned char c = readPtr[2];
    int val =  static_cast<int>((1 - ((a & 128) >> 6)) * ((a & 127) << 24 | b << 16 | c << 8));
    val = val / 256;

    readPtr += 3;


    if (!(a == 0xFF  &&  b == 0xFF  &&  c == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::Int32_opt MemoryReader::read_Int32_opt()
{
  try
  {
    if ((readPtr + 4) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    unsigned char a = readPtr[0];
    unsigned char b = readPtr[1];
    unsigned char c = readPtr[2];
    unsigned char d = readPtr[3];
    int val =  static_cast<int>((1 - ((a & 128) >> 6)) * ((a & 127) << 24 | b << 16 | c << 8 | d));

    readPtr += 4;

    if (!(a == 0xFF  &&  b == 0xFF  &&  c == 0xFF  &&  d == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::Float_opt MemoryReader::read_Float_opt()
{
  try
  {
    if ((readPtr + 4) > endPtr)
      throw SmartMet::Spine::Exception(BCP,"Trying to read outside of the given memory area!");

    float val = 0.0;

    unsigned char* f = reinterpret_cast<unsigned char*>(&val);

    f[0] = readPtr[3];
    f[1] = readPtr[2];
    f[2] = readPtr[1];
    f[3] = readPtr[0];

    readPtr += 4;

    if (!(f[0] == 0xFF  &&  f[1] == 0xFF  &&  f[2] == 0xFF  &&  f[3] == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MemoryReader::read_data(unsigned char *_data,ulonglong _size)
{
  try
  {
    if ((readPtr + _size) > endPtr)
    {
      SmartMet::Spine::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested",std::to_string(_size));
      throw exception;
    }

    for (uint t=0; t<_size; t++)
      _data[t] = readPtr[t];

    readPtr += _size;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MemoryReader::read_null(ulonglong _size)
{
  try
  {
    if ((readPtr + _size) > endPtr)
    {
      SmartMet::Spine::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested",std::to_string(_size));
      throw exception;
    }
    readPtr += _size;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(std::uint8_t& _value)
{
  try
  {
    _value = read_uint8();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(std::uint16_t& _value)
{
  try
  {
    _value = read_uint16();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(std::uint32_t& _value)
{
  try
  {
    _value = read_uint32();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(std::uint64_t& _value)
{
  try
  {
    _value = read_uint64();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(std::int8_t& _value)
{
  try
  {
    _value = read_int8();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(std::int16_t& _value)
{
  try
  {
    _value = read_int16();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(std::int32_t& _value)
{
  try
  {
    _value = read_int32();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(std::float_t& _value)
{
  try
  {
    _value = read_float();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(T::UInt8_opt& _value)
{
  try
  {
    _value = read_UInt8_opt();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(T::UInt16_opt& _value)
{
  try
  {
    _value = read_UInt16_opt();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(T::UInt32_opt& _value)
{
  try
  {
    _value = read_UInt32_opt();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(T::UInt64_opt& _value)
{
  try
  {
    _value = read_UInt64_opt();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(T::Int8_opt& _value)
{
  try
  {
    _value = read_Int8_opt();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(T::Int16_opt& _value)
{
  try
  {
    _value = read_Int16_opt();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(T::Int32_opt& _value)
{
  try
  {
    _value = read_Int32_opt();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(T::Float_opt& _value)
{
  try
  {
    _value = read_Float_opt();
    return *this;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}

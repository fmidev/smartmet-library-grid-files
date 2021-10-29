#include "MemoryReader.h"
#include "GeneralFunctions.h"
#include <macgyver/Exception.h>
#include <arpa/inet.h>

namespace SmartMet
{


/*! \brief The constructor of the class. */

MemoryReader::MemoryReader(unsigned char *_startPtr,ulonglong _size)
{
  try
  {
    if (_startPtr == nullptr)
      throw Fmi::Exception(BCP,"The '_startPtr' parameter points to nullptr!");

    if (_size == 0)
      throw Fmi::Exception(BCP,"The value of the '_size' parameter is 0!");

    parentPtr = _startPtr;
    startPtr = _startPtr;
    endPtr = _startPtr + _size;
    readPtr = _startPtr;
    dataRelease = false;
    littleEndian = false;
    networkByteOrder = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The constructor of the class. */

MemoryReader::MemoryReader(unsigned char *_startPtr,ulonglong _size,bool _dataRelease)
{
  try
  {
    if (_startPtr == nullptr)
      throw Fmi::Exception(BCP,"The '_startPtr' parameter points to nullptr!");

    if (_size == 0)
      throw Fmi::Exception(BCP,"The value of the '_size' parameter is 0!");

    parentPtr = _startPtr;
    startPtr = _startPtr;
    endPtr = _startPtr + _size;
    readPtr = _startPtr;
    dataRelease = _dataRelease;
    littleEndian = false;
    networkByteOrder = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The constructor of the class. */

MemoryReader::MemoryReader(unsigned char *_startPtr,unsigned char *_endPtr)
{
  try
  {
    if (_startPtr == nullptr)
      throw Fmi::Exception(BCP,"The '_startPtr' parameter points to nullptr!");

    if (_endPtr == nullptr)
      throw Fmi::Exception(BCP,"The '_endPtr' parameter points to nullptr!");

    if (_endPtr < _startPtr)
      throw Fmi::Exception(BCP,"The value of the '_endPtr' parameter is smaller than '_startPtr'!");

    parentPtr = _startPtr;
    startPtr = _startPtr;
    endPtr = _endPtr;
    readPtr = _startPtr;
    dataRelease = false;
    littleEndian = false;
    networkByteOrder = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

MemoryReader::~MemoryReader()
{
  try
  {
    if (dataRelease  &&  startPtr != nullptr)
      delete [] startPtr;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryReader::setReadPtr(unsigned char *_readPtr)
{
  try
  {
    if (_readPtr == nullptr)
      throw Fmi::Exception(BCP,"The '_readPtr' parameter points to nullptr!");

    if (_readPtr < startPtr  ||  _readPtr > endPtr)
      throw Fmi::Exception(BCP,"The value of the '_readPtr' parameter is out of the range!");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryReader::setReadPosition(ulonglong _pos)
{
  try
  {
    if ((startPtr + _pos) > endPtr)
      throw Fmi::Exception(BCP,"The value of the '_pos' parameter is out of the range!");

    readPtr = startPtr + _pos;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryReader::setLittleEndian(bool _littleEndian)
{
  try
  {
    littleEndian = _littleEndian;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryReader::setNetworkByteOrder(bool _networkByteOrder)
{
  try
  {
    networkByteOrder = _networkByteOrder;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





unsigned char MemoryReader::getByte(ulonglong _pos)
{
  try
  {
    if ((startPtr + _pos) >= endPtr)
    {
      Fmi::Exception exception(BCP,"The value of the '_pos' parameter is out of the range!");
      exception.addParameter("Pos",std::to_string(_pos));
      exception.addParameter("Size",std::to_string(getDataSize()));
      throw exception;
    }

    return *(startPtr+_pos);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





unsigned char MemoryReader::getByte(unsigned char *_posPtr)
{
  try
  {
    if (_posPtr < startPtr || _posPtr >= endPtr)
      throw Fmi::Exception(BCP,"The value of the '_posPtr' parameter is out of the range!");

    return *_posPtr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool MemoryReader::peek_string(const char *_str)
{
  try
  {
    if (_str == nullptr)
      throw Fmi::Exception(BCP,"The '_str' parameter points to nullptr!");

    ulonglong len = strlen(_str);
    if ((readPtr + len) > endPtr)
      return false;

    if (memcmp(readPtr,_str,len) == 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool MemoryReader::read_string(uchar _endChar,char *_str,uint _maxLen)
{
  try
  {
    if (_str == nullptr)
      throw Fmi::Exception(BCP,"The '_str' parameter points to nullptr!");

    uchar *s = (uchar*)_str;
    uchar *r = readPtr;
    uchar *e = readPtr + _maxLen;
    if (e > endPtr)
      e = endPtr;

    while (r < e)
    {
      if (*r == _endChar)
      {
        *s = '\0';
        while (s > (uchar*)_str  &&  *s <= ' ')
        {
          *s = '\0';
          s--;
        }

        readPtr = r+1;
        return true;
      }
      *s = *r;
      s++;
      r++;
    }
    *_str = '\0';
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





int MemoryReader::search_string(const char *_str)
{
  try
  {
    if (_str == nullptr)
      throw Fmi::Exception(BCP,"The '_str' parameter points to nullptr!");

    uchar *p = (uchar*)_str;
    uchar *r = readPtr;
    while (*p != '\0' && r < endPtr)
    {
      if (*p == *r)
        p++;
      else
        p = (uchar*)_str;

      r++;
    }

    if (*p != '\0')
      return -1;

    return C_INT(r - readPtr) - strlen(_str);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::uint8_t MemoryReader::read_uint8()
{
  try
  {
    if ((readPtr + 1) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","1");
      throw exception;
    }

    unsigned char val = readPtr[0];

    readPtr++;

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::uint16_t MemoryReader::read_uint16()
{
  try
  {
    if ((readPtr + 2) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","2");
      throw exception;
    }

    if (networkByteOrder)
    {
      ushort *v = (ushort*)readPtr;
      ushort val = ntohs(*v);
      readPtr += 2;
      return val;
    }

    unsigned short a = readPtr[0];
    unsigned short b = readPtr[1];
    unsigned short val = static_cast<unsigned short>((a << 8 | b));
    if (littleEndian)
      val = static_cast<unsigned short>((b << 8 | a));

    readPtr += 2;
    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::uint32_t MemoryReader::read_uint24()
{
  try
  {
    if ((readPtr + 3) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","3");
      throw exception;
    }

    uint a = readPtr[0];
    uint b = readPtr[1];
    uint c = readPtr[2];
    uint val =  static_cast<unsigned int>((a << 16 | b << 8 | c));
    if (littleEndian)
      val =  static_cast<unsigned int>((c << 16 | b << 8 | a));

    readPtr += 3;

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::uint32_t MemoryReader::read_uint32()
{
  try
  {
    if ((readPtr + 4) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","4");
      throw exception;
    }

    if (networkByteOrder)
    {
      uint *v = (uint*)readPtr;
      uint val = ntohl(*v);
      readPtr += 4;
      return val;
    }

    uint a = readPtr[0];
    uint b = readPtr[1];
    uint c = readPtr[2];
    uint d = readPtr[3];
    uint val =  static_cast<unsigned int>((a << 24 | b << 16 | c << 8 | d));
    if (littleEndian)
      val =  static_cast<unsigned int>((d << 24 | c << 16 | b << 8 | a));

    readPtr += 4;
    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::uint64_t MemoryReader::read_uint64()
{
  try
  {
    if ((readPtr + 8) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","8");
      throw exception;
    }

    ulonglong a = readPtr[0];
    ulonglong b = readPtr[1];
    ulonglong c = readPtr[2];
    ulonglong d = readPtr[3];
    ulonglong e = readPtr[4];
    ulonglong f = readPtr[5];
    ulonglong g = readPtr[6];
    ulonglong h = readPtr[7];
    ulonglong val =  (a << 56 | b << 48 | c << 40 | d << 32 | e << 24 | f << 16 | g << 8 | h);
    if (littleEndian)
      val =  (h << 56 | g << 48 | f << 40 | e << 32 | d << 24 | c << 16 | b << 8 | a);

    readPtr += 8;

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::int8_t MemoryReader::read_int8()
{
  try
  {
    if ((readPtr + 1) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","1");
      throw exception;
    }

    unsigned char a = readPtr[0];
    unsigned char val = static_cast<char>((1 - ((a & 128) >> 6)) * (a & 127));

    readPtr++;

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::int16_t MemoryReader::read_int16()
{
  try
  {
    if ((readPtr + 2) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","2");
      throw exception;
    }

    if (networkByteOrder)
    {
      short *v = (short*)readPtr;
      short val = ntohs(*v);
      readPtr += 2;
      return val;
    }

    unsigned char a = readPtr[0];
    unsigned char b = readPtr[1];
    short val = static_cast<short>((1 - ((a & 128) >> 6)) * ((a & 127) << 8 | b));
    if (littleEndian)
      val = static_cast<short>((1 - ((b & 128) >> 6)) * ((b & 127) << 8 | a));

    readPtr += 2;
    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::int32_t MemoryReader::read_int24()
{
  try
  {
    if ((readPtr + 3) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","3");
      throw exception;
    }

    unsigned char a = readPtr[0];
    unsigned char b = readPtr[1];
    unsigned char c = readPtr[2];
    int val =  static_cast<int>((1 - ((a & 128) >> 6)) * ((a & 127) << 24 | b << 16 | c << 8));
    if (littleEndian)
      val =  static_cast<int>((1 - ((c & 128) >> 6)) * ((c & 127) << 24 | b << 16 | a << 8));

    val = val / 256;


    readPtr += 3;

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::int32_t MemoryReader::read_int32()
{
  try
  {
    if ((readPtr + 4) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","4");
      throw exception;
    }

    if (networkByteOrder)
    {
      int *v = (int*)readPtr;
      int val = htonl(*v);
      readPtr += 4;
      return val;
    }

    unsigned char a = readPtr[0];
    unsigned char b = readPtr[1];
    unsigned char c = readPtr[2];
    unsigned char d = readPtr[3];
    int val =  static_cast<int>((1 - ((a & 128) >> 6)) * ((a & 127) << 24 | b << 16 | c << 8 | d));
    if (littleEndian)
       val =  static_cast<int>((1 - ((d & 128) >> 6)) * ((d & 127) << 24 | c << 16 | b << 8 | a));

    readPtr += 4;
    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::float_t MemoryReader::read_float()
{
  try
  {
    if ((readPtr + 4) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","4");
      throw exception;
    }

    float val = 0.0;

    unsigned char* f = reinterpret_cast<unsigned char*>(&val);

    f[0] = readPtr[3];
    f[1] = readPtr[2];
    f[2] = readPtr[1];
    f[3] = readPtr[0];

    if (littleEndian)
    {
      f[0] = readPtr[0];
      f[1] = readPtr[1];
      f[2] = readPtr[2];
      f[3] = readPtr[3];
    }

    readPtr += 4;

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::double_t MemoryReader::read_double()
{
  try
  {
    if ((readPtr + 8) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","8");
      throw exception;
    }

    double val = 0.0;

    unsigned char* f = reinterpret_cast<unsigned char*>(&val);

    f[0] = readPtr[7];
    f[1] = readPtr[6];
    f[2] = readPtr[5];
    f[3] = readPtr[4];
    f[4] = readPtr[3];
    f[5] = readPtr[2];
    f[6] = readPtr[1];
    f[7] = readPtr[0];

    if (littleEndian)
    {
      f[0] = readPtr[0];
      f[1] = readPtr[1];
      f[2] = readPtr[2];
      f[3] = readPtr[3];
      f[4] = readPtr[4];
      f[5] = readPtr[5];
      f[6] = readPtr[6];
      f[7] = readPtr[7];
    }

    readPtr += 8;

    return val;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




std::float_t MemoryReader::read_ibmFloat()
{
  try
  {
    if ((readPtr + 4) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","4");
      throw exception;
    }

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::array<char,16> MemoryReader::read_uuid()
{
  try
  {
    if ((readPtr + 16) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","16");
      throw exception;
    }

    std::array<char, 16> ret;
    for (auto i = 0; i < 16; i++)
      ret[i] = readPtr[i];

    readPtr += 16;

    return ret;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::UInt8_opt MemoryReader::read_UInt8_opt()
{
  try
  {
    if ((readPtr + 1) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","1");
      throw exception;
    }

    unsigned char val = readPtr[0];

    readPtr++;

    if (!(val == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::UInt16_opt MemoryReader::read_UInt16_opt()
{
  try
  {
    if ((readPtr + 2) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","2");
      throw exception;
    }

    unsigned short val = read_uint16();

    if (val != 0xFFFF)
      return val;

    return {};
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::UInt32_opt MemoryReader::read_UInt24_opt()
{
  try
  {
    if ((readPtr + 3) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","3");
      throw exception;
    }

    uint val =  read_uint24();
    if (val != 0xFFFFFF)
      return val;

    return {};
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::UInt32_opt MemoryReader::read_UInt32_opt()
{
  try
  {
    if ((readPtr + 4) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","4");
      throw exception;
    }

    uint val =  read_uint32();
    if (val != 0xFFFFFFFF)
      return val;

    return {};
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::UInt64_opt MemoryReader::read_UInt64_opt()
{
  try
  {
    if ((readPtr + 8) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","8");
      throw exception;
    }

    ulonglong val = read_uint64();
    if (val != 0xFFFFFFFFFFFFFFFF)
      return val;

    return {};
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::Int8_opt MemoryReader::read_Int8_opt()
{
  try
  {
    if ((readPtr + 1) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","1");
      throw exception;
    }

    unsigned char a = readPtr[0];
    char val = read_int8();

    if (!(a == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::Int16_opt MemoryReader::read_Int16_opt()
{
  try
  {
    if ((readPtr + 2) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","2");
      throw exception;
    }

    unsigned char a = readPtr[0];
    unsigned char b = readPtr[1];
    short val = static_cast<short>((1 - ((a & 128) >> 6)) * ((a & 127) << 8 | b));
    if (littleEndian)
      val = static_cast<short>((1 - ((b & 128) >> 6)) * ((b & 127) << 8 | a));

    readPtr += 2;

    if (!(a == 0xFF  &&  b == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::Int32_opt MemoryReader::read_Int24_opt()
{
  try
  {
    if ((readPtr + 3) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","3");
      throw exception;
    }

    unsigned char a = readPtr[0];
    unsigned char b = readPtr[1];
    unsigned char c = readPtr[2];
    int val =  static_cast<int>((1 - ((a & 128) >> 6)) * ((a & 127) << 24 | b << 16 | c << 8));
    if (littleEndian)
      val =  static_cast<int>((1 - ((c & 128) >> 6)) * ((c & 127) << 24 | b << 16 | a << 8));

    val = val / 256;

    readPtr += 3;

    if (!(a == 0xFF  &&  b == 0xFF  &&  c == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::Int32_opt MemoryReader::read_Int32_opt()
{
  try
  {
    if ((readPtr + 4) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","4");
      throw exception;
    }

    unsigned char a = readPtr[0];
    unsigned char b = readPtr[1];
    unsigned char c = readPtr[2];
    unsigned char d = readPtr[3];
    int val =  static_cast<int>((1 - ((a & 128) >> 6)) * ((a & 127) << 24 | b << 16 | c << 8 | d));
    if (littleEndian)
      val =  static_cast<int>((1 - ((d & 128) >> 6)) * ((d & 127) << 24 | c << 16 | b << 8 | a));

    readPtr += 4;

    if (!(a == 0xFF  &&  b == 0xFF  &&  c == 0xFF  &&  d == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::Float_opt MemoryReader::read_Float_opt()
{
  try
  {
    if ((readPtr + 4) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
      if (startPtr != parentPtr)
        exception.addParameter("Global read position",uint64_toHex(getGlobalReadPosition()));
      exception.addParameter("Local read position",uint64_toHex(getReadPosition()));
      exception.addParameter("Local data size",std::to_string(getDataSize()));
      exception.addParameter("Bytes requested","4");
      throw exception;
    }

    float val = 0.0;

    unsigned char* f = reinterpret_cast<unsigned char*>(&val);

    f[0] = readPtr[3];
    f[1] = readPtr[2];
    f[2] = readPtr[1];
    f[3] = readPtr[0];

    if (littleEndian)
    {
      f[0] = readPtr[0];
      f[1] = readPtr[1];
      f[2] = readPtr[2];
      f[3] = readPtr[3];
    }

    readPtr += 4;

    if (!(f[0] == 0xFF  &&  f[1] == 0xFF  &&  f[2] == 0xFF  &&  f[3] == 0xFF))
      return val;

    return {};
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryReader::read_data(unsigned char *_data,ulonglong _size)
{
  try
  {
    if ((readPtr + _size) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryReader::read_null(ulonglong _size)
{
  try
  {
    if ((readPtr + _size) > endPtr)
    {
      Fmi::Exception exception(BCP,"Trying to read outside of the given memory area!");
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





MemoryReader& MemoryReader::operator>>(std::double_t& _value)
{
  try
  {
    _value = read_double();
    return *this;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}

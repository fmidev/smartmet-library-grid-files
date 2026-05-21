#include "DataWriter.h"
#include "GeneralFunctions.h"
#include <arpa/inet.h>


namespace SmartMet
{


/*! \brief Constructs the DataWriter with big-endian byte order as the default. */

DataWriter::DataWriter()
{
  try
  {
    littleEndian = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Destructor for the DataWriter base class. */

DataWriter::~DataWriter()
{
}





/*! \brief Returns the current write position; must be implemented by subclasses. */

UInt64 DataWriter::getWritePosition()
{
  throw Fmi::Exception(BCP,"Not implemented!",nullptr);
}





/*! \brief Returns the highest write position reached so far; must be implemented by subclasses. */

UInt64 DataWriter::getMaxWritePosition()
{
  throw Fmi::Exception(BCP,"Not implemented!",nullptr);
}





/*! \brief Selects little-endian (true) or big-endian (false) byte ordering for subsequent writes. */

void DataWriter::setLittleEndian(bool _littleEndian)
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





/*! \brief Sets the current write position; must be implemented by subclasses. */

void DataWriter::setWritePosition(UInt64 _pos)
{
  throw Fmi::Exception(BCP,"Not implemented!",nullptr);
}





/*! \brief Writes a raw block of bytes; must be implemented by subclasses. */

void DataWriter::write_data(void *_data,UInt64 _size)
{
  throw Fmi::Exception(BCP,"Not implemented!",nullptr);
}





/*! \brief Writes the given byte value _size times to the output. */

void DataWriter::write_nTimes(uchar _val,uint _size)
{
  try
  {
    for (uint t=0; t<_size; t++)
      write_data(&_val,1);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an unsigned 8-bit integer to the output. */

void DataWriter::write_uint8(std::uint8_t _value)
{
  try
  {
    write_data(&_value,sizeof(_value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an unsigned 16-bit integer using the configured byte order. */

void DataWriter::write_uint16(std::uint16_t _value)
{
  try
  {
    uchar v[2];
    if (littleEndian)
    {
      v[1] = C_UCHAR((_value & 0xFF00) >> 8);
      v[0] = C_UCHAR((_value & 0xFF));
    }
    else
    {
      v[0] = C_UCHAR((_value & 0xFF00) >> 8);
      v[1] = C_UCHAR((_value & 0xFF));
    }

    write_data(v,2);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an unsigned 24-bit integer using the configured byte order. */

void DataWriter::write_uint24(std::uint32_t _value)
{
  try
  {
    uchar v[3];
    if (littleEndian)
    {
      v[2] = C_UCHAR((_value & 0xFF0000) >> 16);
      v[1] = C_UCHAR((_value & 0xFF00) >> 8);
      v[0] = C_UCHAR((_value & 0xFF));
    }
    else
    {
      v[0] = C_UCHAR((_value & 0xFF0000) >> 16);
      v[1] = C_UCHAR((_value & 0xFF00) >> 8);
      v[2] = C_UCHAR((_value & 0xFF));
    }

    write_data(v,3);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an unsigned 32-bit integer using the configured byte order. */

void DataWriter::write_uint32(std::uint32_t _value)
{
  try
  {
    uchar v[4];
    if (littleEndian)
    {
      v[3] = C_UCHAR((_value & 0xFF000000) >> 24);
      v[2] = C_UCHAR((_value & 0xFF0000) >> 16);
      v[1] = C_UCHAR((_value & 0xFF00) >> 8);
      v[0] = C_UCHAR((_value & 0xFF));
    }
    else
    {
      v[0] = C_UCHAR((_value & 0xFF000000) >> 24);
      v[1] = C_UCHAR((_value & 0xFF0000) >> 16);
      v[2] = C_UCHAR((_value & 0xFF00) >> 8);
      v[3] = C_UCHAR((_value & 0xFF));
    }

    write_data(v,4);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an unsigned 64-bit integer using the configured byte order. */

void DataWriter::write_uint64(std::uint64_t _value)
{
  try
  {
    uchar v[8];
    if (littleEndian)
    {
      v[7] = C_UCHAR((_value & 0xFF000000) >> 56);
      v[6] = C_UCHAR((_value & 0xFF000000) >> 48);
      v[5] = C_UCHAR((_value & 0xFF000000) >> 40);
      v[4] = C_UCHAR((_value & 0xFF000000) >> 32);
      v[3] = C_UCHAR((_value & 0xFF000000) >> 24);
      v[2] = C_UCHAR((_value & 0xFF0000) >> 16);
      v[1] = C_UCHAR((_value & 0xFF00) >> 8);
      v[0] = C_UCHAR((_value & 0xFF));
    }
    else
    {
      v[0] = C_UCHAR((_value & 0xFF000000) >> 56);
      v[1] = C_UCHAR((_value & 0xFF000000) >> 48);
      v[2] = C_UCHAR((_value & 0xFF000000) >> 40);
      v[3] = C_UCHAR((_value & 0xFF000000) >> 32);
      v[4] = C_UCHAR((_value & 0xFF000000) >> 24);
      v[5] = C_UCHAR((_value & 0xFF0000) >> 16);
      v[6] = C_UCHAR((_value & 0xFF00) >> 8);
      v[7] = C_UCHAR((_value & 0xFF));
    }

    write_data(v,8);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes a signed 8-bit integer using sign-magnitude representation. */

void DataWriter::write_int8(std::int8_t _value)
{
  try
  {
    char val = _value;
    if (val < 0)
    {
      val = -val;
      val = val & 0x80;
    }

    write_data(&val,1);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes a signed 16-bit integer using sign-magnitude representation and the configured byte order. */

void DataWriter::write_int16(std::int16_t _value)
{
  try
  {
    short val = _value;
    if (val < 0)
      val = -val;

    uchar v[2];
    if (littleEndian)
    {
      v[1] = C_UCHAR((val & 0xFF00) >> 8);
      v[0] = C_UCHAR((val & 0xFF));

      if (_value < 0)
        v[1] = v[1] | 0x80;
    }
    else
    {
      v[0] = C_UCHAR((val & 0xFF00) >> 8);
      v[1] = C_UCHAR((val & 0xFF));

      if (_value < 0)
        v[0] = v[0] | 0x80;
    }

    write_data(v,2);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes a signed 24-bit integer using sign-magnitude representation and the configured byte order. */

void DataWriter::write_int24(std::int32_t _value)
{
  try
  {
    int val = _value;
    if (val < 0)
      val = -val;

    uchar v[3];
    if (littleEndian)
    {
      v[2] = C_UCHAR((val & 0xFF0000) >> 16);
      v[1] = C_UCHAR((val & 0xFF00) >> 8);
      v[0] = C_UCHAR((val & 0xFF));

      if (_value < 0)
        v[2] = v[2] | 0x80;
    }
    else
    {
      v[0] = C_UCHAR((val & 0xFF0000) >> 16);
      v[1] = C_UCHAR((val & 0xFF00) >> 8);
      v[2] = C_UCHAR((val & 0xFF));

      if (_value < 0)
        v[0] = v[0] | 0x80;
    }

    write_data(v,3);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes a signed 32-bit integer using sign-magnitude representation and the configured byte order. */

void DataWriter::write_int32(std::int32_t _value)
{
  try
  {
    int val = _value;
    if (val < 0)
      val = -val;

    uchar v[4];
    if (littleEndian)
    {
      v[3] = C_UCHAR((val & 0xFF000000) >> 24);
      v[2] = C_UCHAR((val & 0xFF0000) >> 16);
      v[1] = C_UCHAR((val & 0xFF00) >> 8);
      v[0] = C_UCHAR((val & 0xFF));

      if (_value < 0)
        v[3] = v[3] | 0x80;
    }
    else
    {
      v[0] = C_UCHAR((val & 0xFF000000) >> 24);
      v[1] = C_UCHAR((val & 0xFF0000) >> 16);
      v[2] = C_UCHAR((val & 0xFF00) >> 8);
      v[3] = C_UCHAR((val & 0xFF));

      if (_value < 0)
        v[0] = v[0] | 0x80;
    }

    write_data(v,4);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes a 32-bit IEEE float byte-by-byte in the configured byte order. */

void DataWriter::write_float(std::float_t _value)
{
  try
  {
    unsigned char* f = reinterpret_cast<unsigned char*>(&_value);

    if (littleEndian)
    {
      write_data(&f[0],1);
      write_data(&f[1],1);
      write_data(&f[2],1);
      write_data(&f[3],1);
    }
    else
    {
      write_data(&f[3],1);
      write_data(&f[2],1);
      write_data(&f[1],1);
      write_data(&f[0],1);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Writes a 64-bit IEEE double byte-by-byte in the configured byte order. */

void DataWriter::write_double(std::double_t _value)
{
  try
  {
    unsigned char* f = reinterpret_cast<unsigned char*>(&_value);

    if (littleEndian)
    {
      write_data(&f[0],1);
      write_data(&f[1],1);
      write_data(&f[2],1);
      write_data(&f[3],1);
      write_data(&f[4],1);
      write_data(&f[5],1);
      write_data(&f[6],1);
      write_data(&f[7],1);
    }
    else
    {
      write_data(&f[7],1);
      write_data(&f[6],1);
      write_data(&f[5],1);
      write_data(&f[4],1);
      write_data(&f[3],1);
      write_data(&f[2],1);
      write_data(&f[1],1);
      write_data(&f[0],1);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Writes an IEEE float converted to IBM/hex floating-point format. */

void DataWriter::write_ibmFloat(std::float_t _value)
{
  try
  {

    float f = ieee2ibm(_value);
    write_data(&f,sizeof(f));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes a 16-byte UUID to the output. */

void DataWriter::write_uuid(std::array<char,16> _value)
{
  try
  {
    for (auto i = 0; i < 16; i++)
    {
      char val = _value[i];
      write_int8(val);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an optional uint8 value, emitting an all-ones marker when the optional is empty. */

void DataWriter::write_UInt8_opt(T::UInt8_opt _value)
{
  try
  {
    uchar nullChar = 0xFF;
    if (!_value)
      write_nTimes(nullChar,1);
    else
      write_uint8(*_value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an optional uint16 value, emitting an all-ones marker when the optional is empty. */

void DataWriter::write_UInt16_opt(T::UInt16_opt _value)
{
  try
  {
    uchar nullChar = 0xFF;
    if (!_value)
      write_nTimes(nullChar,2);
    else
      write_uint16(*_value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an optional uint24 value, emitting an all-ones marker when the optional is empty. */

void DataWriter::write_UInt24_opt(T::UInt32_opt _value)
{
  try
  {
    uchar nullChar = 0xFF;
    if (!_value)
      write_nTimes(nullChar,3);
    else
      write_uint24(*_value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an optional uint32 value, emitting an all-ones marker when the optional is empty. */

void DataWriter::write_UInt32_opt(T::UInt32_opt _value)
{
  try
  {
    uchar nullChar = 0xFF;
    if (!_value)
      write_nTimes(nullChar,4);
    else
      write_uint32(*_value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an optional uint64 value, emitting an all-ones marker when the optional is empty. */

void DataWriter::write_UInt64_opt(T::UInt64_opt _value)
{
  try
  {
    uchar nullChar = 0xFF;
    if (!_value)
      write_nTimes(nullChar,8);
    else
      write_uint64(*_value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an optional int8 value, emitting an all-ones marker when the optional is empty. */

void DataWriter::write_Int8_opt(T::Int8_opt _value)
{
  try
  {
    uchar nullChar = 0xFF;
    if (!_value)
      write_nTimes(nullChar,1);
    else
      write_int8(*_value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an optional int16 value, emitting an all-ones marker when the optional is empty. */

void DataWriter::write_Int16_opt(T::Int16_opt _value)
{
  try
  {
    uchar nullChar = 0xFF;
    if (!_value)
      write_nTimes(nullChar,2);
    else
      write_int16(*_value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an optional int24 value, emitting an all-ones marker when the optional is empty. */

void DataWriter::write_Int24_opt(T::Int32_opt _value)
{
  try
  {
    uchar nullChar = 0xFF;
    if (!_value)
      write_nTimes(nullChar,3);
    else
      write_int24(*_value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an optional int32 value, emitting an all-ones marker when the optional is empty. */

void DataWriter::write_Int32_opt(T::Int32_opt _value)
{
  try
  {
    uchar nullChar = 0xFF;
    if (!_value)
      write_nTimes(nullChar,4);
    else
      write_int32(*_value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes an optional float value, emitting an all-ones marker when the optional is empty. */

void DataWriter::write_Float_opt(T::Float_opt _value)
{
  try
  {
    uchar nullChar = 0xFF;
    if (!_value)
      write_nTimes(nullChar,4);
    else
      write_float(*_value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes an unsigned 8-bit integer. */

DataWriter& DataWriter::operator<<(std::uint8_t _value)
{
  try
  {
    write_uint8(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes an unsigned 16-bit integer. */

DataWriter& DataWriter::operator<<(std::uint16_t _value)
{
  try
  {
    write_uint16(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes an unsigned 32-bit integer. */

DataWriter& DataWriter::operator<<(std::uint32_t _value)
{
  try
  {
    write_uint32(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes an unsigned 64-bit integer. */

DataWriter& DataWriter::operator<<(std::uint64_t _value)
{
  try
  {
    write_uint64(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes a signed 8-bit integer. */

DataWriter& DataWriter::operator<<(std::int8_t _value)
{
  try
  {
    write_int8(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes a signed 16-bit integer. */

DataWriter& DataWriter::operator<<(std::int16_t _value)
{
  try
  {
    write_int16(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes a signed 32-bit integer. */

DataWriter& DataWriter::operator<<(std::int32_t _value)
{
  try
  {
    write_int32(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes a 32-bit float. */

DataWriter& DataWriter::operator<<(std::float_t _value)
{
  try
  {
    write_float(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes a 64-bit double. */

DataWriter& DataWriter::operator<<(std::double_t _value)
{
  try
  {
    write_double(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes an optional uint8. */

DataWriter& DataWriter::operator<<(T::UInt8_opt _value)
{
  try
  {
    write_UInt8_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes an optional uint16. */

DataWriter& DataWriter::operator<<(T::UInt16_opt _value)
{
  try
  {
    write_UInt16_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes an optional uint32. */

DataWriter& DataWriter::operator<<(T::UInt32_opt _value)
{
  try
  {
    write_UInt32_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes an optional uint64. */

DataWriter& DataWriter::operator<<(T::UInt64_opt _value)
{
  try
  {
    write_UInt64_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes an optional int8. */

DataWriter& DataWriter::operator<<(T::Int8_opt _value)
{
  try
  {
    write_Int8_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes an optional int16. */

DataWriter& DataWriter::operator<<(T::Int16_opt _value)
{
  try
  {
    write_Int16_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes an optional int32. */

DataWriter& DataWriter::operator<<(T::Int32_opt _value)
{
  try
  {
    write_Int32_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes an optional float. */

DataWriter& DataWriter::operator<<(T::Float_opt _value)
{
  try
  {
    write_Float_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Stream-insertion operator that writes a 16-byte UUID. */

DataWriter& DataWriter::operator<<(std::array<char, 16> _value)
{
  try
  {
    write_uuid(_value);
    return (*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace SmartMet

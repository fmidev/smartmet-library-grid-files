#include "DataWriter.h"
#include "GeneralFunctions.h"
#include <arpa/inet.h>


namespace SmartMet
{


DataWriter::DataWriter()
{
}





DataWriter::~DataWriter()
{
}





ulonglong DataWriter::getWritePosition()
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!",nullptr);
}





void DataWriter::setWritePosition(ulonglong _pos)
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!",nullptr);
}





void DataWriter::write_data(void *_data,ulonglong _size)
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!",nullptr);
}





void DataWriter::write_nTimes(uchar _val,uint _size)
{
  try
  {
    for (uint t=0; t<_size; t++)
      write_data(&_val,1);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataWriter::write_uint8(std::uint8_t _value)
{
  try
  {
    write_data(&_value,sizeof(_value));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataWriter::write_uint16(std::uint16_t _value)
{
  try
  {
    uchar v[2];
    v[0] = (uchar)((_value & 0xFF00) >> 8);
    v[1] = (uchar)((_value & 0xFF));

    write_data(v,2);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataWriter::write_uint24(std::uint32_t _value)
{
  try
  {
    uchar v[3];
    v[0] = (uchar)((_value & 0xFF0000) >> 16);
    v[1] = (uchar)((_value & 0xFF00) >> 8);
    v[2] = (uchar)((_value & 0xFF));

    write_data(v,3);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataWriter::write_uint32(std::uint32_t _value)
{
  try
  {
    uchar v[4];
    v[0] = (uchar)((_value & 0xFF000000) >> 24);
    v[1] = (uchar)((_value & 0xFF0000) >> 16);
    v[2] = (uchar)((_value & 0xFF00) >> 8);
    v[3] = (uchar)((_value & 0xFF));

    write_data(v,4);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataWriter::write_uint64(std::uint64_t _value)
{
  try
  {
    uchar v[8];
    v[0] = (uchar)((_value & 0xFF000000) >> 56);
    v[1] = (uchar)((_value & 0xFF000000) >> 48);
    v[2] = (uchar)((_value & 0xFF000000) >> 40);
    v[3] = (uchar)((_value & 0xFF000000) >> 32);
    v[4] = (uchar)((_value & 0xFF000000) >> 24);
    v[5] = (uchar)((_value & 0xFF0000) >> 16);
    v[6] = (uchar)((_value & 0xFF00) >> 8);
    v[7] = (uchar)((_value & 0xFF));

    write_data(v,8);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataWriter::write_int16(std::int16_t _value)
{
  try
  {
    short val = _value;
    if (val < 0)
      val = -val;

    uchar v[2];
    v[0] = (uchar)((val & 0xFF00) >> 8);
    v[1] = (uchar)((val & 0xFF));

    if (_value < 0)
      v[0] = v[0] | 0x80;

    write_data(v,2);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataWriter::write_int24(std::int32_t _value)
{
  try
  {
    int val = _value;
    if (val < 0)
      val = -val;

    uchar v[3];
    v[0] = (uchar)((val & 0xFF0000) >> 16);
    v[1] = (uchar)((val & 0xFF00) >> 8);
    v[2] = (uchar)((val & 0xFF));

    if (_value < 0)
      v[0] = v[0] | 0x80;

    write_data(v,3);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataWriter::write_int32(std::int32_t _value)
{
  try
  {
    int val = _value;
    if (val < 0)
      val = -val;

    uchar v[4];
    v[0] = (uchar)((val & 0xFF000000) >> 24);
    v[1] = (uchar)((val & 0xFF0000) >> 16);
    v[2] = (uchar)((val & 0xFF00) >> 8);
    v[3] = (uchar)((val & 0xFF));

    if (_value < 0)
      v[0] = v[0] | 0x80;

    write_data(v,4);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataWriter::write_float(std::float_t _value)
{
  try
  {
    unsigned char* f = (unsigned char*)(&_value);

    write_data(&f[3],1);
    write_data(&f[2],1);
    write_data(&f[1],1);
    write_data(&f[0],1);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void DataWriter::write_ibmFloat(std::float_t _value)
{
  try
  {

    float f = ieee2ibm(_value);
    write_data(&f,sizeof(f));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(std::uint8_t _value)
{
  try
  {
    write_uint8(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(std::uint16_t _value)
{
  try
  {
    write_uint16(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(std::uint32_t _value)
{
  try
  {
    write_uint32(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(std::uint64_t _value)
{
  try
  {
    write_uint64(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(std::int8_t _value)
{
  try
  {
    write_int8(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(std::int16_t _value)
{
  try
  {
    write_int16(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(std::int32_t _value)
{
  try
  {
    write_int32(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(std::float_t _value)
{
  try
  {
    write_float(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(T::UInt8_opt _value)
{
  try
  {
    write_UInt8_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(T::UInt16_opt _value)
{
  try
  {
    write_UInt16_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(T::UInt32_opt _value)
{
  try
  {
    write_UInt32_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(T::UInt64_opt _value)
{
  try
  {
    write_UInt64_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(T::Int8_opt _value)
{
  try
  {
    write_Int8_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(T::Int16_opt _value)
{
  try
  {
    write_Int16_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(T::Int32_opt _value)
{
  try
  {
    write_Int32_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(T::Float_opt _value)
{
  try
  {
    write_Float_opt(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataWriter& DataWriter::operator<<(std::array<char, 16> _value)
{
  try
  {
    write_uuid(_value);
    return (*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace SmartMet

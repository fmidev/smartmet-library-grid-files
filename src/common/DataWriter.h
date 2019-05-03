#pragma once

#include "../grid/Typedefs.h"


namespace SmartMet
{


class DataWriter
{
  public:
                      DataWriter();
    virtual           ~DataWriter();

    virtual ulonglong getWritePosition();
    virtual ulonglong getMaxWritePosition();

    virtual void      setLittleEndian(bool _littleEndian);
    virtual void      setWritePosition(ulonglong _pos);

    virtual void      write_data(void *_data,ulonglong _size);
    virtual void      write_nTimes(uchar _val,uint _size);

    virtual void      write_uint8(std::uint8_t _value);
    virtual void      write_uint16(std::uint16_t _value);
    virtual void      write_uint24(std::uint32_t _value);
    virtual void      write_uint32(std::uint32_t _value);
    virtual void      write_uint64(std::uint64_t _value);
    virtual void      write_int8(std::int8_t _value);
    virtual void      write_int16(std::int16_t _value);
    virtual void      write_int24(std::int32_t _value);
    virtual void      write_int32(std::int32_t _value);
    virtual void      write_float(std::float_t _value);
    virtual void      write_double(std::double_t _value);
    virtual void      write_ibmFloat(std::float_t _value);

    virtual void      write_uuid(std::array<char,16> _value);

    virtual void      write_UInt8_opt(T::UInt8_opt _value);
    virtual void      write_UInt16_opt(T::UInt16_opt _value);
    virtual void      write_UInt24_opt(T::UInt32_opt _value);
    virtual void      write_UInt32_opt(T::UInt32_opt _value);
    virtual void      write_UInt64_opt(T::UInt64_opt _value);
    virtual void      write_Int8_opt(T::Int8_opt _value);
    virtual void      write_Int16_opt(T::Int16_opt _value);
    virtual void      write_Int24_opt(T::Int32_opt _value);
    virtual void      write_Int32_opt(T::Int32_opt _value);
    virtual void      write_Float_opt(T::Float_opt _value);

    DataWriter&       operator<<(std::uint8_t _value);
    DataWriter&       operator<<(std::uint16_t _value);
    DataWriter&       operator<<(std::uint32_t _value);
    DataWriter&       operator<<(std::uint64_t _value);
    DataWriter&       operator<<(std::int8_t _value);
    DataWriter&       operator<<(std::int16_t _value);
    DataWriter&       operator<<(std::int32_t _value);
    DataWriter&       operator<<(std::float_t _value);
    DataWriter&       operator<<(std::double_t _value);

    DataWriter&       operator<<(T::UInt8_opt _value);
    DataWriter&       operator<<(T::UInt16_opt _value);
    DataWriter&       operator<<(T::UInt32_opt _value);
    DataWriter&       operator<<(T::UInt64_opt _value);
    DataWriter&       operator<<(T::Int8_opt _value);
    DataWriter&       operator<<(T::Int16_opt _value);
    DataWriter&       operator<<(T::Int32_opt _value);
    DataWriter&       operator<<(T::Float_opt _value);

    DataWriter&       operator<<(std::array<char, 16> _value);

  protected:

    bool              littleEndian;
};


}  // namespace SmartMet

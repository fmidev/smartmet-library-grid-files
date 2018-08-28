#pragma once

#include "../grid/Typedefs.h"


namespace SmartMet
{


class MemoryReader
{
  public:
                        MemoryReader(unsigned char *_startPtr,ulonglong _size);
                        MemoryReader(unsigned char *_startPtr,unsigned char *_endPtr);
    virtual             ~MemoryReader();

    ulonglong           getDataSize();
    unsigned char*      getStartPtr();
    unsigned char*      getEndPtr();
    unsigned char*      getReadPtr();
    void                setReadPtr(unsigned char *_readPtr);
    ulonglong           getReadPosition();
    ulonglong           getGlobalReadPosition();
    void                setReadPosition(ulonglong _pos);
    void                setParentPtr(unsigned char *_parentPtr);
    unsigned char*      getParentPtr();

    unsigned char       getByte(ulonglong _pos);
    unsigned char       getByte(unsigned char *_posPtr);

    bool                peek_string(const char *_str);

    void                read_data(unsigned char *_data,ulonglong _size);
    void                read_null(ulonglong _size);

    MemoryReader&       operator>>(std::uint8_t& _value);
    MemoryReader&       operator>>(std::uint16_t& _value);
    MemoryReader&       operator>>(std::uint32_t& _value);
    MemoryReader&       operator>>(std::uint64_t& _value);
    MemoryReader&       operator>>(std::int8_t& _value);
    MemoryReader&       operator>>(std::int16_t& _value);
    MemoryReader&       operator>>(std::int32_t& _value);
    MemoryReader&       operator>>(std::float_t& _value);

    MemoryReader&       operator>>(T::UInt8_opt& _value);
    MemoryReader&       operator>>(T::UInt16_opt& _value);
    MemoryReader&       operator>>(T::UInt32_opt& _value);
    MemoryReader&       operator>>(T::UInt64_opt& _value);
    MemoryReader&       operator>>(T::Int8_opt& _value);
    MemoryReader&       operator>>(T::Int16_opt& _value);
    MemoryReader&       operator>>(T::Int32_opt& _value);
    MemoryReader&       operator>>(T::Float_opt& _value);

    std::uint8_t        read_uint8();
    std::uint16_t       read_uint16();
    std::uint32_t       read_uint24();
    std::uint32_t       read_uint32();
    std::uint64_t       read_uint64();
    std::int8_t         read_int8();
    std::int16_t        read_int16();
    std::int32_t        read_int24();
    std::int32_t        read_int32();
    std::float_t        read_float();
    std::float_t        read_ibmFloat();

    std::array<char,16> read_uuid();

    T::UInt8_opt        read_UInt8_opt();
    T::UInt16_opt       read_UInt16_opt();
    T::UInt32_opt       read_UInt24_opt();
    T::UInt32_opt       read_UInt32_opt();
    T::UInt64_opt       read_UInt64_opt();
    T::Int8_opt         read_Int8_opt();
    T::Int16_opt        read_Int16_opt();
    T::Int32_opt        read_Int24_opt();
    T::Int32_opt        read_Int32_opt();
    T::Float_opt        read_Float_opt();

  protected:

    unsigned char*      startPtr;
    unsigned char*      endPtr;
    unsigned char*      readPtr;
    unsigned char*      parentPtr;
};


}  // namespace SmartMet

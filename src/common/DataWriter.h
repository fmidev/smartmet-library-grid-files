#pragma once

#include "../grid/Typedefs.h"


namespace SmartMet
{


// ====================================================================================
/*! \brief Abstract base class for sequential binary output (to memory or file).
 *
 *  Provides typed write methods (`write_uint8()`, `write_float()`, …) and
 *  stream-style `operator<<` overloads.  Concrete implementations are
 *  `MemoryWriter` (in-memory buffer) and `FileWriter` (stdio FILE*).
 *  Byte-order conversion (little-endian) is controlled via `setLittleEndian()`. */
// ====================================================================================

class DataWriter
{
  public:
                      DataWriter();
    virtual           ~DataWriter();

    /*! \brief Return the current write offset in bytes. */
    virtual UInt64    getWritePosition();
    /*! \brief Return the highest write offset reached (high-water mark). */
    virtual UInt64    getMaxWritePosition();

    /*! \brief Enable or disable little-endian byte-order conversion.
     *  \param[in] _littleEndian  True to write in little-endian order. */
    virtual void      setLittleEndian(bool _littleEndian);

    /*! \brief Seek to an absolute write offset.
     *  \param[in] _pos  Byte offset from the start. */
    virtual void      setWritePosition(UInt64 _pos);

    /*! \brief Write \p _size bytes from \p _data.
     *  \param[in] _data  Source buffer.
     *  \param[in] _size  Number of bytes to write. */
    virtual void      write_data(void *_data,UInt64 _size);

    /*! \brief Write \p _size copies of the byte \p _val.
     *  \param[in] _val   Byte value to repeat.
     *  \param[in] _size  Repeat count. */
    virtual void      write_nTimes(uchar _val,uint _size);

    /** @name Typed write methods
     *  Each encodes one value and advances the write position. @{ */
    virtual void      write_uint8(std::uint8_t _value);
    virtual void      write_uint16(std::uint16_t _value);
    virtual void      write_uint24(std::uint32_t _value);  //!< Write the low 24 bits
    virtual void      write_uint32(std::uint32_t _value);
    virtual void      write_uint64(std::uint64_t _value);
    virtual void      write_int8(std::int8_t _value);
    virtual void      write_int16(std::int16_t _value);
    virtual void      write_int24(std::int32_t _value);    //!< Write the low 24 bits (signed)
    virtual void      write_int32(std::int32_t _value);
    virtual void      write_float(std::float_t _value);
    virtual void      write_double(std::double_t _value);
    virtual void      write_ibmFloat(std::float_t _value); //!< Convert IEEE float to IBM 360 and write
    virtual void      write_uuid(std::array<char,16> _value); //!< Write a 16-byte UUID
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
    /** @} */

    /** @name Stream insertion operators
     *  Write one value of the given type and advance the write position. @{ */
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
    /** @} */

  protected:

    bool              littleEndian; //!< True when writes use little-endian byte order
};


}  // namespace SmartMet

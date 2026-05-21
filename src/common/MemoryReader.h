#pragma once

#include "../grid/Typedefs.h"


namespace SmartMet
{


// ====================================================================================
/*! \brief Sequential binary reader over a contiguous memory buffer.
 *
 *  Provides typed extraction methods (`read_uint8()`, `read_float()`, …) and
 *  stream-style `operator>>` overloads for reading GRIB, NetCDF, and QueryData
 *  binary fields.  Byte-order conversion (little-endian, network/big-endian) is
 *  handled transparently.  An optional `parentPtr` allows sub-readers scoped to
 *  a sub-buffer to report absolute positions relative to the parent file mapping. */
// ====================================================================================

class MemoryReader
{
  public:
    /*! \brief Construct a reader over a size-bounded buffer.
     *  \param[in] _startPtr  Start of the readable region.
     *  \param[in] _size      Number of readable bytes. */
                        MemoryReader(unsigned char *_startPtr,UInt64 _size);

    /*! \brief Construct a reader over a size-bounded buffer with optional ownership.
     *  \param[in] _startPtr    Start of the readable region.
     *  \param[in] _size        Number of readable bytes.
     *  \param[in] _dataRelease If true, `delete[]` the buffer on destruction. */
                        MemoryReader(unsigned char *_startPtr,UInt64 _size,bool _dataRelease);

    /*! \brief Construct a reader over a pointer-bounded buffer.
     *  \param[in] _startPtr  Start of the readable region.
     *  \param[in] _endPtr    One-past-the-end of the readable region. */
                        MemoryReader(unsigned char *_startPtr,unsigned char *_endPtr);
    virtual             ~MemoryReader();

    /*! \brief Return the total buffer size in bytes. */
    UInt64              getDataSize();
    /*! \brief Return the start of the buffer. */
    unsigned char*      getStartPtr();
    /*! \brief Return one-past-the-end of the buffer. */
    unsigned char*      getEndPtr();
    /*! \brief Return the current read position pointer. */
    unsigned char*      getReadPtr();

    /*! \brief Set the read position to an arbitrary pointer.
     *  \param[in] _readPtr  New read position; must be within [startPtr, endPtr]. */
    void                setReadPtr(unsigned char *_readPtr);

    /*! \brief Return the current read offset from startPtr. */
    UInt64              getReadPosition();

    /*! \brief Return the read offset relative to parentPtr (if set), otherwise from startPtr. */
    UInt64              getGlobalReadPosition();

    /*! \brief Set the current read offset from startPtr.
     *  \param[in] _pos  New byte offset. */
    void                setReadPosition(UInt64 _pos);

    /*! \brief Set the parent buffer start pointer used by getGlobalReadPosition().
     *  \param[in] _parentPtr  Base address of the enclosing memory map. */
    void                setParentPtr(unsigned char *_parentPtr);

    /*! \brief Return the parent pointer (set via setParentPtr()). */
    unsigned char*      getParentPtr();

    /*! \brief Enable or disable little-endian byte-order conversion on reads.
     *  \param[in] _littleEndian  True to enable little-endian mode. */
    void                setLittleEndian(bool _littleEndian);

    /*! \brief Enable or disable network (big-endian) byte-order conversion on reads.
     *  \param[in] _networkByteOrder  True to enable network byte order. */
    void                setNetworkByteOrder(bool _networkByteOrder);

    /*! \brief Return the byte at absolute offset \p _pos without advancing the read pointer.
     *  \param[in] _pos  Byte offset from startPtr. */
    unsigned char       getByte(UInt64 _pos);

    /*! \brief Return the byte at pointer \p _posPtr without advancing the read pointer.
     *  \param[in] _posPtr  Pointer into the buffer. */
    unsigned char       getByte(unsigned char *_posPtr);

    /*! \brief Check whether the next bytes in the buffer match \p _str without advancing.
     *  \param[in] _str  Null-terminated string to compare.
     *  \return True if the buffer at readPtr starts with \p _str. */
    bool                peek_string(const char *_str);

    /*! \brief Advance the read pointer until \p _str is found.
     *  \param[in] _str  Null-terminated string to search for.
     *  \return Offset of the match from the current position, or -1 if not found. */
    int                 search_string(const char *_str);

    /*! \brief Read characters until \p _endChar is found or \p _maxLen is reached.
     *  \param[in]  _endChar  Terminating character.
     *  \param[out] _str      Buffer to write into (null-terminated on success).
     *  \param[in]  _maxLen   Maximum characters to read.
     *  \return True if the terminator was found before the limit. */
    bool                read_string(uchar _endChar,char *_str,uint _maxLen);

    /*! \brief Read \p _size raw bytes into \p _data and advance the read pointer.
     *  \param[out] _data  Destination buffer (caller-allocated, at least \p _size bytes).
     *  \param[in]  _size  Number of bytes to read. */
    void                read_data(unsigned char *_data,UInt64 _size);

    /*! \brief Advance the read pointer by \p _size bytes without copying data.
     *  \param[in] _size  Number of bytes to skip. */
    void                read_null(UInt64 _size);

    /** @name Stream extraction operators
     *  Read one value of the given type and advance the read pointer. @{ */
    MemoryReader&       operator>>(std::uint8_t& _value);
    MemoryReader&       operator>>(std::uint16_t& _value);
    MemoryReader&       operator>>(std::uint32_t& _value);
    MemoryReader&       operator>>(std::uint64_t& _value);
    MemoryReader&       operator>>(std::int8_t& _value);
    MemoryReader&       operator>>(std::int16_t& _value);
    MemoryReader&       operator>>(std::int32_t& _value);
    MemoryReader&       operator>>(std::float_t& _value);
    MemoryReader&       operator>>(std::double_t& _value);
    MemoryReader&       operator>>(T::UInt8_opt& _value);
    MemoryReader&       operator>>(T::UInt16_opt& _value);
    MemoryReader&       operator>>(T::UInt32_opt& _value);
    MemoryReader&       operator>>(T::UInt64_opt& _value);
    MemoryReader&       operator>>(T::Int8_opt& _value);
    MemoryReader&       operator>>(T::Int16_opt& _value);
    MemoryReader&       operator>>(T::Int32_opt& _value);
    MemoryReader&       operator>>(T::Float_opt& _value);
    /** @} */

    /** @name Typed read methods
     *  Each reads one value of the corresponding type and advances the read pointer. @{ */
    std::uint8_t        read_uint8();
    std::uint16_t       read_uint16();
    std::uint32_t       read_uint24();   //!< Read a 3-byte unsigned integer
    std::uint32_t       read_uint32();
    std::uint64_t       read_uint64();
    std::int8_t         read_int8();
    std::int16_t        read_int16();
    std::int32_t        read_int24();    //!< Read a 3-byte signed integer
    std::int32_t        read_int32();
    std::float_t        read_float();
    std::double_t       read_double();
    std::float_t        read_ibmFloat(); //!< Read an IBM 360 32-bit float and convert to IEEE
    std::array<char,16> read_uuid();     //!< Read a 16-byte UUID
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
    /** @} */

  protected:

    unsigned char*      startPtr;         //!< Start of the readable memory region
    unsigned char*      endPtr;           //!< One-past-the-end of the readable region
    unsigned char*      readPtr;          //!< Current read position
    unsigned char*      parentPtr;        //!< Base of the enclosing memory map (for global positions)
    bool                dataRelease;      //!< True if the buffer should be delete[]'d on destruction
    bool                littleEndian;     //!< True when reads use little-endian byte order
    bool                networkByteOrder; //!< True when reads use network (big-endian) byte order
};


}  // namespace SmartMet

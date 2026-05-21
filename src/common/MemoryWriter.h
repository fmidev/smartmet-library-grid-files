#pragma once

#include "DataWriter.h"


namespace SmartMet
{


// ====================================================================================
/*! \brief DataWriter implementation that writes into a caller-supplied memory buffer. */
// ====================================================================================

class MemoryWriter : public DataWriter
{
  public:
    /*! \brief Construct a writer over a fixed-size memory buffer.
     *  \param[in] _data         Destination buffer.
     *  \param[in] _dataSize     Size of the buffer in bytes.
     *  \param[in] _dataRelease  If true, `delete[]` the buffer on destruction. */
                MemoryWriter(uchar *_data,UInt64 _dataSize,bool _dataRelease);
    virtual     ~MemoryWriter();

    /*! \brief Return a pointer to the start of the buffer. */
    uchar*      getDataPtr();

    //! \overload DataWriter::getWritePosition()
    UInt64      getWritePosition();
    //! \overload DataWriter::getMaxWritePosition()
    UInt64      getMaxWritePosition();
    //! \overload DataWriter::setWritePosition()
    void        setWritePosition(UInt64 _pos);
    //! \overload DataWriter::write_data()
    void        write_data(void *_data,UInt64 _size);

  protected:

    uchar       *mData;            //!< Destination buffer base address
    UInt64      mDataSize;         //!< Total buffer capacity in bytes
    bool        mDataRelease;      //!< True if the buffer should be delete[]'d on destruction
    UInt64      mWritePosition;    //!< Current write offset from mData
    UInt64      mMaxWritePosition; //!< Highest write offset reached (high-water mark)
};


}  // namespace SmartMet

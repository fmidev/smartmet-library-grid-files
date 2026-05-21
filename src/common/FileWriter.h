#pragma once

#include "DataWriter.h"


namespace SmartMet
{


// ====================================================================================
/*! \brief DataWriter implementation that writes to a stdio FILE*.
 *
 *  Call `createFile()` to open the output path before writing.  `closeFile()` flushes
 *  and closes the handle; the destructor also closes it if still open. */
// ====================================================================================

class FileWriter : public DataWriter
{
  public:
                FileWriter();
    virtual     ~FileWriter();

    /*! \brief Open (or create) a file for writing.
     *  \param[in] _filename  Path to the output file. */
    void        createFile(const char *_filename);

    /*! \brief Flush and close the output file. */
    void        closeFile();

    //! \overload DataWriter::getWritePosition()
    UInt64      getWritePosition();
    //! \overload DataWriter::getMaxWritePosition()
    UInt64      getMaxWritePosition();
    //! \overload DataWriter::setWritePosition()
    void        setWritePosition(UInt64 _pos);
    //! \overload DataWriter::write_data()
    void        write_data(void *_data,UInt64 _size);

  protected:

    std::string mFilename;        //!< Path to the output file
    FILE*       mFileHandle;      //!< Open file handle (nullptr when not open)
    UInt64      mMaxFilePosition; //!< Highest byte offset written (high-water mark)
};


}  // namespace SmartMet

#pragma once

#include "DataWriter.h"


namespace SmartMet
{


class FileWriter : public DataWriter
{
  public:
                FileWriter();
    virtual     ~FileWriter();

    void        createFile(const char *_filename);
    void        closeFile();
    UInt64      getWritePosition();
    UInt64      getMaxWritePosition();
    void        setWritePosition(UInt64 _pos);
    void        write_data(void *_data,UInt64 _size);

  protected:

    std::string mFilename;
    FILE*       mFileHandle;
    UInt64      mMaxFilePosition;
};


}  // namespace SmartMet

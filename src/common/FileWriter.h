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
    ulonglong   getWritePosition();
    ulonglong   getMaxWritePosition();
    void        setWritePosition(ulonglong _pos);
    void        write_data(void *_data,ulonglong _size);

  protected:

    std::string mFilename;
    FILE*       mFileHandle;
    ulonglong   mMaxFilePosition;
};


}  // namespace SmartMet

#pragma once

#include "DataWriter.h"


namespace SmartMet
{


class FileWriter : public DataWriter
{
  public:
                FileWriter();
        ~FileWriter() override;

    void        createFile(const char *_filename);
    void        closeFile();
    ulonglong   getWritePosition() override;
    ulonglong   getMaxWritePosition() override;
    void        setWritePosition(ulonglong _pos) override;
    void        write_data(void *_data,ulonglong _size) override;

  protected:

    std::string mFilename;
    FILE*       mFileHandle;
    ulonglong   mMaxFilePosition;
};


}  // namespace SmartMet

#pragma once

#include "grid/GridFile.h"
#include "Message.h"


namespace SmartMet
{
namespace GRIB2
{

class GribFile : public GRID::GridFile
{
  public:

                        GribFile();
    virtual             ~GribFile();

    // ### Common methods for all file types

    uint                getFileId() const;
    uint                getGroupFlags() const;
    uint                getProducerId() const;
    uint                getGenerationId() const;
    std::string         getFileName() const;
    time_t              getCheckTime() const;

    void                setFileId(uint fileId);
    void                setGroupFlags(uint groupFlags);
    void                setProducerId(uint producerId);
    void                setGenerationId(uint generationId);
    void                setFileName(std::string  fileName);
    void                setCheckTime(time_t checkTime);

    T::FileType         getFileType() const;
    std::string         getFileTypeString() const;
    GRID::Message*      getMessageByIndex(std::size_t index) const;
    std::size_t         getNumberOfMessages() const;
    void                print(std::ostream& stream,uint level,uint optionFlags) const;
    void                read(const bf::path& path);
    void                read(MemoryReader& memoryReader);

  private:

    T::Data_ptr_vec     searchMessageLocations(MemoryReader& memoryReader);
    void                readMessage(MemoryReader& memoryReader,uint messageIndex);

    /*! \brief  The message object pointers. */
    std::vector<Message*> mMessages;
};

}  // namespace GRID
}  // namespace SmartMet

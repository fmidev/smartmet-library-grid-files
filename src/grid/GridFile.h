#pragma once

#include "Message.h"
#include "GridPointValue.h"
#include "Typedefs.h"
#include "../common/MemoryReader.h"

#include <memory>
#include <vector>


namespace SmartMet
{
namespace GRID
{


// ====================================================================================
/*! \brief The main purpose of this class is to hide differences of different grib/grid
    files (GRIB1, GRIB2, etc) so that applications do not need to know what kind
    of grib/grid files they are using.

    The class maps the current file into the memory and redirects incoming requests to
    the actual implementation. */
// ====================================================================================


typedef std::map<uint,Message*> Message_ptr_map;


class GridFile
{
  public:
                          GridFile();
                          GridFile(const GridFile& other);
                          GridFile(GridFile *gridFile);
    virtual               ~GridFile();

    virtual void          addDependence(uint fileId);
    virtual void          addMessage(Message *message);
    virtual void          addUser(uint fileId);

    virtual GridFile*     createGridFile();

    virtual void          deleteUsers();

    virtual time_t        getCheckTime() const;
    virtual time_t        getDeletionTime() const;
    virtual std::string   getDeletionTimeStr() const;
    virtual uint          getFileId() const;
    virtual std::string   getFileName() const;
    virtual T::FileType   getFileType() const;
    virtual std::string   getFileTypeString() const;
    virtual uint          getGenerationId() const;
    virtual uint          getGroupFlags() const;
    virtual char*         getMemoryPtr();
    virtual Message*      getMessageByIndex(std::size_t index);
    virtual time_t        getModificationTime() const;
    virtual std::size_t   getNumberOfMessages();

    virtual uint          getProducerId() const;
    virtual long long     getSize();
    virtual uint          getSourceId() const;
    virtual void          getUsers(std::set<uint>& userList);

    virtual bool          hasDependence(uint fileId);
    virtual bool          hasMessagePositionError() const;

    virtual bool          isPhysical() const;
    virtual bool          isVirtual() const;
    virtual bool          isMemoryMapped() const;

    virtual void          mapToMemory();

    virtual Message*      newMessage(T::FileType fileType);
    virtual Message*      newMessage(uint messageIndex,MessageInfo& messageInfo);

    virtual void          print(std::ostream& stream,uint level,uint optionFlags) const;

    virtual void          read(const std::string& filename);

    virtual void          setCheckTime(time_t checkTime);
    virtual void          setDeletionTime(time_t deletionTime);
    virtual void          setDeletionTime(const std::string& deletionTime);
    virtual void          setFileId(uint fileId);
    virtual void          setFileName(const std::string& fileName);
    virtual void          setGenerationId(uint generationId);
    virtual void          setGroupFlags(uint groupFlags);
    virtual void          setProducerId(uint producerId);
    virtual void          setSourceId(uint sourceId);

    virtual void          write(const std::string& filename);
    virtual void          write(DataWriter& dataWriter);

  protected:

    time_t                mCheckTime;
    time_t                mDeletionTime;      // The file should not be accessed after this time
    uint                  mFileId;
    time_t                mFileModificationTime;
    std::string           mFileName;
    uint                  mGenerationId;
    uint                  mGroupFlags;
    MessageInfo_map       mMessagePositions;
    Message_ptr_map       mMessages;
    uint                  mProducerId;
    bool                  mRequestCounterEnabled;
    uint                  mSourceId;
    std::set<uint>        mUserList;

};


typedef std::shared_ptr<GridFile> GridFile_sptr;
typedef std::vector<GridFile_sptr> GridFile_sptr_vec;


}  // namespace GRID
}  // namespace SmartMet

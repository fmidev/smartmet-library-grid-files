#pragma once

#include "common/MemoryReader.h"
#include "Message.h"
#include <memory>
#include <vector>
#include "GridPointValue.h"
#include "Typedefs.h"


namespace SmartMet
{
namespace GRID
{


// ====================================================================================
/*! \brief The main purpose of this class is to hide differences of different grib/grid
    files (GRIB1, GRIB2, etc) so that applications do not need to know what kind
    of grib/grid files they are using.

    The class maps the current file into the memory and redirects incoming requests to
    the actual implementation. On the other hand this class is the parent class for
    the implementation classes (GRIB1::GribFile, GRIB2::GribFile, etc.).

    The child classes (GRIB1::GribFile, GRIB2::GribFile, etc.) can be used also
    independently, but in this case the user should recognize the file type by
    itself. When using this class the file type is recognized automatically.
*/
// ====================================================================================


class GridFile
{
  public:
                                GridFile();
                                GridFile(GridFile *gridFile);
    virtual                     ~GridFile();

    virtual uint                getFileId() const;
    virtual uint                getGroupFlags() const;
    virtual uint                getProducerId() const;
    virtual uint                getGenerationId() const;
    virtual std::string         getFileName() const;
    virtual time_t              getModificationTime() const;
    virtual T::FileType         getFileType() const;
    virtual std::string         getFileTypeString() const;
    virtual time_t              getCheckTime() const;
    virtual uint                getSourceId() const;

    virtual bool                isPhysical() const;
    virtual bool                isVirtual() const;
    virtual bool                isMemoryMapped() const;
    virtual void                mapToMemory();

    virtual void                addDependence(uint fileId);
    virtual bool                hasDependence(uint fileId);

    virtual void                addUser(uint fileId);
    virtual void                getUsers(std::set<uint>& userList);

    virtual void                setGridFile(GridFile *gridFile);
    virtual void                setFileId(uint fileId);
    virtual void                setGroupFlags(uint groupFlags);
    virtual void                setProducerId(uint producerId);
    virtual void                setGenerationId(uint generationId);
    virtual void                setFileName(std::string  fileName);
    virtual void                setCheckTime(time_t checkTime);
    virtual void                setSourceId(uint sourceId);

    std::shared_ptr<GridFile>   getGridFile();
    virtual Message*            getMessageByIndex(std::size_t index);
    virtual std::size_t         getNumberOfMessages();

    virtual void                print(std::ostream& stream,uint level,uint optionFlags) const;
    virtual void                read(std::string filename);

  protected:

    std::shared_ptr<GridFile>   mGridFile;    // The actual implementation of GRIB1/GRIB2/Virtual-file.
    std::string                 mFileName;
    uint                        mFileId;
    time_t                      mFileModificationTime;
    uint                        mGroupFlags;
    uint                        mProducerId;
    uint                        mGenerationId;
    uint                        mSourceId;
    time_t                      mCheckTime;
    std::set<uint>              mUserList;
};


typedef std::shared_ptr<GridFile> GridFile_sptr;



}  // namespace GRID
}  // namespace SmartMet

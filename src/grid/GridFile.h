#pragma once

#include "common/MemoryReader.h"
#include "Message.h"
#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <memory>
#include <vector>
#include "GridPointValue.h"
#include "Typedefs.h"

namespace bf = boost::filesystem;

typedef boost::iostreams::mapped_file_params MappedFileParams;
typedef boost::iostreams::mapped_file MappedFile;



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

    virtual bool                isMemoryMapped();

    virtual void                setFileId(uint fileId);
    virtual void                setGroupFlags(uint groupFlags);
    virtual void                setProducerId(uint producerId);
    virtual void                setGenerationId(uint generationId);
    virtual void                setFileName(std::string  fileName);
    virtual void                setCheckTime(time_t checkTime);
    virtual void                setSourceId(uint sourceId);

    std::shared_ptr<GridFile>   getGridFile();
    T::ParamLevel_vec           getLevelsByParameterId(T::ParamId parameterId) const;
    virtual Message*            getMessageByIndex(std::size_t index) const;
    T::Index_vec                getMessagesIndexListByParameterId(T::ParamId parameterId) const;
    T::Index_vec                getMessagesIndexListByParameterIdAndLevel(T::ParamId parameterId,T::ParamLevel level) const;
    virtual std::size_t         getNumberOfMessages() const;
    std::size_t                 getNumberOfMessagesByParameterIdAndLevel(T::ParamId parameterId,T::ParamLevel level) const;
    T::ParamId_vec              getParameterIdentifiers() const;
    void                        getParameterMinAndMaxValues(T::ParamId parameterId,T::ParamValue& minValue,T::ParamValue& maxValue) const;
    // T::GridPointValue_vec       getParameterValuesByGridArea(T::ParamId parameterId,T::TimeString startTime,T::TimeString endTime,uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end) const;
    T::GridPointValue_vec       getParameterValuesByLatLon(T::ParamId parameterId,T::TimeString startTime,T::TimeString endTime,double lat,double lon,T::InterpolationMethod interpolationMethod) const;
    T::GridPointValue_vec       getParameterValuesByLatLon(T::ParamId parameterId,T::TimeString startTime,T::TimeString endTime,double lat,double lon) const;
    T::GridPointValue_vec       getParameterValuesByLatLon(T::ParamId parameterId,T::ParamLevel level,T::TimeString startTime,T::TimeString endTime,double lat,double lon,T::InterpolationMethod interpolationMethod) const;
    T::GridPointValue_vec       getParameterValuesByLatLon(T::ParamId parameterId,T::ParamLevel level,T::TimeString startTime,T::TimeString endTime,double lat,double lon) const;
    void                        getTimeRangeByParameterIdAndLevel(T::ParamId parameterId,T::ParamLevel level,T::TimeString& startTime,T::TimeString& endTime,std::size_t& messages) const;
    virtual void                print(std::ostream& stream,uint level,uint optionFlags) const;

    virtual void                read(const bf::path& path);

  private:

    T::FileType                 getFileType(MemoryReader& memoryReader);
    unsigned long long          searchFileStartPosition(MemoryReader& memoryReader);

  protected:

    std::shared_ptr<GridFile>   mGridFile;    // The actual implementation of GRIB1/GRIB2-file.
    boost::filesystem::path     mPath = {};

    std::string                 mFileName;
    uint                        mFileId;
    time_t                      mFileModificationTime;
    uint                        mGroupFlags;
    uint                        mProducerId;
    uint                        mGenerationId;
    uint                        mSourceId;
    std::unique_ptr<MappedFile> mMappedFile;

    bool                        mIsMemoryMapped;
    time_t                      mCheckTime;
};


typedef std::shared_ptr<GridFile> GridFile_sptr;



}  // namespace GRID
}  // namespace SmartMet

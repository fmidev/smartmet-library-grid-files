#pragma once

#include "GridFile.h"

#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>


namespace bf = boost::filesystem;

typedef boost::iostreams::mapped_file_params MappedFileParams;
typedef boost::iostreams::mapped_file MappedFile;



namespace SmartMet
{
namespace GRID
{


// ====================================================================================
/*! \brief The main purpose of this class is ...
*/
// ====================================================================================


class PhysicalGridFile : public GridFile
{
  public:
                    PhysicalGridFile();
    virtual         ~PhysicalGridFile();

    virtual bool    isPhysical() const;
    virtual bool    isVirtual() const;
    virtual bool    isMemoryMapped() const;
    virtual void    mapToMemory();

    virtual void    print(std::ostream& stream,uint level,uint optionFlags) const;
    virtual void    read(std::string filename);

  private:

    T::FileType     readFileType(MemoryReader& memoryReader);
    ulonglong       searchFileStartPosition(MemoryReader& memoryReader);

  protected:

    bool            mIsMemoryMapped;

    std::unique_ptr<MappedFile> mMappedFile;
};



}  // namespace GRID
}  // namespace SmartMet

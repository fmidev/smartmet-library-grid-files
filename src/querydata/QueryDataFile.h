#pragma once

#include "../grid/Message.h"
#include "Message.h"
#include <newbase/NFmiFastQueryInfo.h>


namespace SmartMet
{
namespace QueryData
{

// ====================================================================================
/*! \brief Adapter that opens an NFmiQueryData file and enumerates its parameter/level/
 *  time slices as GRID messages.
 *
 *  Loads the file via newbase NFmiFastQueryInfo on construction.  A MessageInfoVec
 *  is produced by read(), one entry per slice.  QueryData::Message objects then call
 *  back into getGridValue() to retrieve individual data values at runtime. */
// ====================================================================================

class QueryDataFile
{
  public:

                        QueryDataFile(const char *filename);
    virtual             ~QueryDataFile();

    void                read(MessageInfoVec& messageInfoList);
    void                print(std::ostream& stream,uint level,uint optionFlags) const;
    //T::ParamValue       getGridValue(uint paramIndex,uint levelIndex,uint timeIndex,uint grid_i,uint grid_j) const;

    inline T::ParamValue getGridValue(uint paramIndex,uint levelIndex,uint timeIndex,uint grid_i,uint grid_j) const
    {
      try
      {
        if (mFastQueryInfo == nullptr)
          return ParamValueMissing;

        std::size_t locationIndex = mFastQueryInfo->PeekLocationIndex(grid_i,grid_j);
        std::size_t idx = mFastQueryInfo->Index(paramIndex,locationIndex,levelIndex,timeIndex);

        float val = mFastQueryInfo->PeekValue(idx);
        if (val == 32700.0)
          return ParamValueMissing;

        return val;
      }
      catch (...)
      {
        Fmi::Exception exception(BCP,"Operation failed!",nullptr);
        throw exception;
      }
    }


  protected:

    uint                getGeometryId();


    NFmiQueryData*      mQueryDataFile;  //!< Loaded newbase QueryData object.
    NFmiFastQueryInfo*  mFastQueryInfo;  //!< Fast index over mQueryDataFile for O(1) slice access.
    std::string         mFilename;       //!< Path to the QueryData file.
};



typedef QueryDataFile* QueryDataFilePtr;  //!< Non-owning pointer to a QueryDataFile.


}  // namespace QueryData
}  // namespace SmartMet


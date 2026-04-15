#pragma once

#include "../grid/Message.h"
#include "Message.h"
#include <newbase/NFmiFastQueryInfo.h>


namespace SmartMet
{
namespace QueryData
{

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


    NFmiQueryData*      mQueryDataFile;
    NFmiFastQueryInfo*  mFastQueryInfo;
    std::string         mFilename;
};



typedef QueryDataFile* QueryDataFilePtr;


}  // namespace QueryData
}  // namespace SmartMet


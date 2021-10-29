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
    T::ParamValue       getGridValue(uint paramIndex,uint levelIndex,uint timeIndex,uint grid_i,uint grid_j) const;

  protected:

    uint                getGeometryId();


    NFmiQueryData*      mQueryDataFile;
    NFmiFastQueryInfo*  mFastQueryInfo;
    std::string         mFilename;
};



typedef QueryDataFile* QueryDataFilePtr;


}  // namespace QueryData
}  // namespace SmartMet


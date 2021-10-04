#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{

typedef std::vector<std::pair<uint,std::string>> ParameterList;


class FmiLevelId_grib
{
  public:
                    FmiLevelId_grib();
    virtual         ~FmiLevelId_grib();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    uint            mFmiLevelId;
    ParameterList   mParameterList;
};


typedef std::vector<FmiLevelId_grib> FmiLevelId_grib_vec;
typedef const FmiLevelId_grib* FmiLevelId_grib_cptr;


}
}


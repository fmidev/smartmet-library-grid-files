#pragma once

#include "grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class FmiLevelId_grib
{
  public:
                    FmiLevelId_grib();
                    FmiLevelId_grib(const FmiLevelId_grib& level);
    virtual         ~FmiLevelId_grib();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    uint            mFmiProducerId;
    uint            mGeneratingProcessIdentifier;
    uint            mCentre;
    uint            mGribLevelId;
    uint            mFmiLevelId;
};


typedef std::vector<FmiLevelId_grib> FmiLevelId_grib_vec;
typedef const FmiLevelId_grib* FmiLevelId_grib_cptr;


}
}


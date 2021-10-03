#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class FmiLevelId_grib
{
  public:
                    FmiLevelId_grib();
    virtual         ~FmiLevelId_grib();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    uint            mFmiProducerId;
    uint            mGeneratingProcessIdentifier;
    uint            mCentre;
    uint            mGribLevelId;
    uint            mFmiLevelId;
};


using FmiLevelId_grib_vec = std::vector<FmiLevelId_grib>;
using FmiLevelId_grib_cptr = const FmiLevelId_grib *;


}
}


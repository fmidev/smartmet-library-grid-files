#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class FmiProducerId_grib
{
  public:
                    FmiProducerId_grib();
    virtual         ~FmiProducerId_grib();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    uint            mProducerId;  // Radon producer id
    uint            mType;
    uint            mCentre;
    uint            mIdent;
    std::string     mProducerName;
    std::string     mProducerDescription;
};


using FmiProducerId_grib_vec = std::vector<FmiProducerId_grib>;
using FmiProducerId_grib_cptr = const FmiProducerId_grib *;


}
}


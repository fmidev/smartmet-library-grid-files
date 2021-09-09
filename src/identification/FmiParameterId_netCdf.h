#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class FmiParameterId_netCdf
{
  public:
                      FmiParameterId_netCdf();
    virtual           ~FmiParameterId_netCdf();

    void              print(std::ostream& stream,uint level,uint optionFlags) const;

    T::FmiParamId     mFmiParameterId;
    std::string       mNetCdfParameterName;
    std::string       mConversionFunction;
    std::string       mReverseConversionFunction;
};


typedef std::vector<FmiParameterId_netCdf> FmiParamId_netCdf_vec;
typedef const FmiParameterId_netCdf* FmiParamId_netCdf_cptr;


}
}


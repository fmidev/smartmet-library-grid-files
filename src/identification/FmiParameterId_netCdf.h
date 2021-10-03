#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

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


using FmiParamId_netCdf_vec = std::vector<FmiParameterId_netCdf>;
using FmiParamId_netCdf_umap = std::unordered_map<uint, FmiParameterId_netCdf>;
using FmiParamId_netCdf_cptr = const FmiParameterId_netCdf *;


}
}


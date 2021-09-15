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


typedef std::vector<FmiParameterId_netCdf> FmiParamId_netCdf_vec;
typedef std::unordered_map<uint,FmiParameterId_netCdf> FmiParamId_netCdf_umap;
typedef const FmiParameterId_netCdf* FmiParamId_netCdf_cptr;


}
}


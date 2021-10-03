#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

namespace SmartMet
{
namespace Identification
{


class FmiParameterId_newbase
{
  public:
                      FmiParameterId_newbase();
    virtual           ~FmiParameterId_newbase();

    void              print(std::ostream& stream,uint level,uint optionFlags) const;

    T::FmiParamId     mFmiParameterId;
    T::NewbaseParamId mNewbaseParameterId;
    std::string       mConversionFunction;
    std::string       mReverseConversionFunction;
};


using FmiParamId_newbase_vec = std::vector<FmiParameterId_newbase>;
using FmiParamId_newbase_umap = std::unordered_map<uint, FmiParameterId_newbase>;
using FmiParamId_newbase_cptr = const FmiParameterId_newbase *;


}
}


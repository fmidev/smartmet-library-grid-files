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


typedef std::vector<FmiParameterId_newbase> FmiParamId_newbase_vec;
typedef std::unordered_map<uint,FmiParameterId_newbase> FmiParamId_newbase_umap;
typedef const FmiParameterId_newbase* FmiParamId_newbase_cptr;


}
}


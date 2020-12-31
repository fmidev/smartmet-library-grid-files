#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class FmiParameterId_newbase
{
  public:
                    FmiParameterId_newbase();
                    //FmiParameterId_newbase(const FmiParameterId_newbase& parameter);
    virtual         ~FmiParameterId_newbase();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::ParamId      mFmiParameterId;
    T::ParamId      mNewbaseParameterId;
    std::string     mConversionFunction;
    std::string     mReverseConversionFunction;
};


typedef std::vector<FmiParameterId_newbase> FmiParamId_newbase_vec;
typedef const FmiParameterId_newbase* FmiParamId_newbase_cptr;


}
}


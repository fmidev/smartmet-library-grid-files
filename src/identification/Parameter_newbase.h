#pragma once

#include "grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class Parameter_newbase
{
  public:

                  Parameter_newbase();
                  Parameter_newbase(const Parameter_newbase& parameter);
    virtual       ~Parameter_newbase();

    void          print(std::ostream& stream,uint level,uint optionFlags) const;

    T::ParamId    mNewbaseParameterId;
    std::string   mParameterName;
};

typedef const Parameter_newbase* Parameter_newbase_cptr;
typedef std::vector<Parameter_newbase> Parameter_newbase_vec;


}
}


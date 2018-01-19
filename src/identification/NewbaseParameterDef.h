#pragma once

#include "grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class NewbaseParameterDef
{
  public:

                  NewbaseParameterDef();
                  NewbaseParameterDef(const NewbaseParameterDef& parameter);
    virtual       ~NewbaseParameterDef();

    void          print(std::ostream& stream,uint level,uint optionFlags) const;

    T::ParamId    mNewbaseParameterId;
    std::string   mParameterName;
};

typedef const NewbaseParameterDef* NewbaseParamDef_cptr;
typedef std::vector<NewbaseParameterDef> NewbaseParamDef_vec;


}
}


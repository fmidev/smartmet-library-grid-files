#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

namespace SmartMet
{
namespace Identification
{


class NewbaseParameterDef
{
  public:

                  NewbaseParameterDef();
    virtual       ~NewbaseParameterDef();

    void          print(std::ostream& stream,uint level,uint optionFlags) const;

    T::NewbaseParamId mNewbaseParameterId;
    std::string       mParameterName;
};

using NewbaseParamDef_cptr = const NewbaseParameterDef *;
using NewbaseParamDef_vec = std::vector<NewbaseParameterDef>;
using NewbaseParamDef_umap = std::unordered_map<uint, NewbaseParameterDef>;


}
}


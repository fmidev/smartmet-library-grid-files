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

typedef const NewbaseParameterDef* NewbaseParamDef_cptr;
typedef std::vector<NewbaseParameterDef> NewbaseParamDef_vec;
typedef std::unordered_map<uint,NewbaseParameterDef> NewbaseParamDef_umap;


}
}


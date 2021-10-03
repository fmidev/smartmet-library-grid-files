#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

namespace SmartMet
{
namespace Identification
{


class NetCdfParameterDef
{
  public:

                  NetCdfParameterDef();
    virtual       ~NetCdfParameterDef();

    void          print(std::ostream& stream,uint level,uint optionFlags) const;

    std::string   mParameterName;
    std::string   mFmiLevelId;
    std::string   mParameterUnits;
};

using NetCdfParamDef_cptr = const NetCdfParameterDef *;
using NetCdfParamDef_vec = std::vector<NetCdfParameterDef>;
using NetCdfParamDef_umap = std::unordered_map<std::string, NetCdfParameterDef>;


}
}


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

typedef const NetCdfParameterDef* NetCdfParamDef_cptr;
typedef std::vector<NetCdfParameterDef> NetCdfParamDef_vec;
typedef std::unordered_map<std::string,NetCdfParameterDef> NetCdfParamDef_umap;


}
}


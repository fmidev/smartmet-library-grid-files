#pragma once

#include "../grid/Typedefs.h"

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
    std::string   mParameterUnits;
};

typedef const NetCdfParameterDef* NetCdfParamDef_cptr;
typedef std::vector<NetCdfParameterDef> NetCdfParamDef_vec;


}
}


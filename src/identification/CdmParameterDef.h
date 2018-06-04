#pragma once

#include "../grid/Typedefs.h"


namespace SmartMet
{
namespace Identification
{


class CdmParameterDef
{
  public:
                    CdmParameterDef();
                    CdmParameterDef(const CdmParameterDef& parameter);
    virtual         ~CdmParameterDef();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    uint            mParameterNumber;
    std::string     mParameterName;
    std::string     mParameterDescription;
    std::string     mParameterUnits;
};


typedef std::vector<CdmParameterDef> CdmParameterDef_vec;
typedef const CdmParameterDef* CdmParameterDef_cptr;


}
}


#pragma once

#include "grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class ProducerDef_fmi
{
  public:
                    ProducerDef_fmi();
                    ProducerDef_fmi(const ProducerDef_fmi& producer);
    virtual         ~ProducerDef_fmi();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    uint            mProducerId;  // Radon producer id
    uint            mType;
    uint            mCentre;
    uint            mIdent;
    std::string     mProducerName;
    std::string     mProducerDescription;
};


typedef std::vector<ProducerDef_fmi> ProducerDef_fmi_vec;
typedef const ProducerDef_fmi* ProducerDef_fmi_cptr;


}
}


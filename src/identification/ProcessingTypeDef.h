#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class ProcessingTypeDef
{
  public:
                    ProcessingTypeDef();
    virtual         ~ProcessingTypeDef();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    int             mProcessingTypeId;
    std::string     mName;
    std::string     mDescription;
};


typedef std::vector<ProcessingTypeDef> ProcessingTypeDef_vec;
typedef const ProcessingTypeDef* ProcessingTypeDef_cptr;


}
}


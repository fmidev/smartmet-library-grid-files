#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class ForecastTypeDef
{
  public:
                    ForecastTypeDef();
    virtual         ~ForecastTypeDef();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    int             mForecastTypeId;
    std::string     mName;
    std::string     mDescription;
};


typedef std::vector<ForecastTypeDef> ForecastTypeDef_vec;
typedef const ForecastTypeDef* ForecastTypeDef_cptr;


}
}


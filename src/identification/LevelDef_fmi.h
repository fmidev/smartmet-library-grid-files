#pragma once

#include "grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class LevelDef_fmi
{
  public:
                    LevelDef_fmi();
                    LevelDef_fmi(const LevelDef_fmi& level);
    virtual         ~LevelDef_fmi();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    uint            mFmiProducerId;
    uint            mGeneratingProcessIdentifier;
    uint            mCentre;
    uint            mGribLevelId;
    uint            mFmiLevelId;
};


typedef std::vector<LevelDef_fmi> LevelDef_fmi_vec;
typedef const LevelDef_fmi* LevelDef_fmi_cptr;


}
}


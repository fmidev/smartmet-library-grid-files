#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class LevelDef
{
  public:
                    LevelDef();
    virtual         ~LevelDef();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    uint            mLevelId;
    std::string     mName;
    std::string     mDescription;
};


using LevelDef_vec = std::vector<LevelDef>;
using LevelDef_cptr = const LevelDef *;


}
}


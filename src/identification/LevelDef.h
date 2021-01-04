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
                    //LevelDef(const LevelDef& levelDef);
    virtual         ~LevelDef();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    uint            mLevelId;
    std::string     mName;
    std::string     mDescription;
};


typedef std::vector<LevelDef> LevelDef_vec;
typedef const LevelDef* LevelDef_cptr;


}
}


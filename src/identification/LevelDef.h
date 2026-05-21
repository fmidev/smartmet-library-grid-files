#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief FMI level type definition record loaded from the level definitions CSV.
 *
 *  Describes a vertical level type (e.g. pressure, height-above-ground, model hybrid
 *  level) with a numeric identifier, a short name, physical units, a type code,
 *  and a human-readable description. */
// ====================================================================================

class LevelDef
{
  public:
                      LevelDef();
    virtual           ~LevelDef();

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void              print(std::ostream& stream,uint level,uint optionFlags) const;

    uint              mLevelId;       //!< Numeric FMI level type identifier
    std::string       mName;          //!< Short name (e.g. "pressure", "height", "hybrid")
    uchar             mType;          //!< Level type code
    std::string       mUnits;         //!< Physical units of the level coordinate (e.g. "hPa", "m")
    std::string       mDescription;   //!< Human-readable description
};


typedef std::vector<LevelDef> LevelDef_vec;  //!< Ordered list of level definitions
typedef const LevelDef* LevelDef_cptr;       //!< Non-owning const pointer


}
}

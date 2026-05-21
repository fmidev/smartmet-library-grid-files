#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief Geometry group definition loaded from the FMI geometry group definitions CSV.
 *
 *  Groups a set of geometry IDs that belong to the same producer and group type, so
 *  that callers can request all geometries for a given domain (e.g. all resolutions
 *  produced by a named NWP model) without enumerating them individually. */
// ====================================================================================

class FmiGeometryGroupDef
{
  public:
                      FmiGeometryGroupDef();
    virtual           ~FmiGeometryGroupDef();

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void              print(std::ostream& stream,uint level,uint optionFlags) const;

    uint              mGeometryGroupId;      //!< Numeric geometry group identifier
    uint              mGroupType;            //!< Group type code (domain category)
    std::string       mProducerName;         //!< Name of the NWP producer that owns this group
    std::vector<int>  mGeometryIdList;       //!< Geometry IDs that belong to this group
};

typedef std::vector<FmiGeometryGroupDef> FmiGeomGroupDef_vec;              //!< Ordered list of geometry group definitions
typedef std::unordered_map<uint,FmiGeometryGroupDef> FmiGeomGroupDef_umap; //!< Hash map keyed by geometry group ID
typedef const FmiGeometryGroupDef* FmiGeomGroupDef_cptr;                   //!< Non-owning const pointer

}
}

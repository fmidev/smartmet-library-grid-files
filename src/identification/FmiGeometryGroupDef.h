#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

namespace SmartMet
{
namespace Identification
{


class FmiGeometryGroupDef
{
  public:
                      FmiGeometryGroupDef();
    virtual           ~FmiGeometryGroupDef();

    void              print(std::ostream& stream,uint level,uint optionFlags) const;

    uint              mGeometryGroupId;
    uint              mGroupType;
    std::string       mProducerName;
    std::vector<int>  mGeometryIdList;
};

typedef std::vector<FmiGeometryGroupDef> FmiGeomGroupDef_vec;
typedef std::unordered_map<uint,FmiGeometryGroupDef> FmiGeomGroupDef_umap;
typedef const FmiGeometryGroupDef* FmiGeomGroupDef_cptr;

}
}


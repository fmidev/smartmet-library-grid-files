#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{

// This class is needed in order to find a correct "parameterId" that identifies
// the grid data. In other words, there are no unique parameterIds in place, so
// we try to identify the grid data by using fields defined in the "paramDef_grib2.csv" file.
// This file is generated from several "paramId.def" files.

typedef std::vector<std::pair<uint,std::string>> ParameterList;

class Grib2ParameterDef
{
  public:

                    Grib2ParameterDef();
    virtual         ~Grib2ParameterDef();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::GribParamId  mGribParameterId;
    ParameterList   mParameterList;
};

typedef const Grib2ParameterDef* Grib2ParamDef_cptr;
typedef std::vector<Grib2ParameterDef> Grib2ParamDef_vec;
typedef std::list<Grib2ParameterDef> Grib2ParamDef_list;


}
}


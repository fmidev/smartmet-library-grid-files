#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{

typedef std::vector<std::pair<uint,std::string>> ParameterList;

class Grib1ParameterDef
{
  public:

                    Grib1ParameterDef();
    virtual         ~Grib1ParameterDef();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::GribParamId  mGribParameterId;
    ParameterList   mParameterList;
};

typedef const Grib1ParameterDef* Grib1ParamDef_cptr;
typedef std::vector<Grib1ParameterDef> Grib1ParamDef_vec;
typedef std::list<Grib1ParameterDef> Grib1ParamDef_list;


}
}


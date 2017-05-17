#pragma once

#include "grid/Typedefs.h"
#include "common/MemoryReader.h"
#include <ostream>

namespace SmartMet
{
namespace GRIB2
{

// Base class for data definitions

class DataDefinition
{
  public:
                  DataDefinition();
    virtual       ~DataDefinition();

    virtual void  print(std::ostream& stream,uint level,uint optionFlags) const;
};

}  // namespace GRIB2
}  // namespace SmartMet

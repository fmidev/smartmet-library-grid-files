#pragma once

#include "../grid/Typedefs.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include <ostream>

namespace SmartMet
{
namespace GRIB2
{

// ====================================================================================
/*! \brief Abstract base class for GRIB 2 data-packing strategy tags.
 *
 *  Concrete subclasses in the implementation/ directory (e.g. GridDataRepresentation,
 *  JpegGridDataRepresentation, PngGridDataRepresentation, etc.) supply a
 *  getTemplateNumber() matching a Data Representation Template 5.x number.
 *  The RepresentationSection owns one DataDefinition and uses it only to query
 *  the template number for serialisation. */
// ====================================================================================

class DataDefinition
{
  public:
                  DataDefinition();
                  DataDefinition(const DataDefinition& other);
    virtual       ~DataDefinition();

    virtual uint  getTemplateNumber() const;
    virtual void  print(std::ostream& stream,uint level,uint optionFlags) const;
};

}  // namespace GRIB2
}  // namespace SmartMet

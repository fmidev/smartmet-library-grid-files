#pragma once

#include "../grid/Typedefs.h"
#include "../common/Dimensions.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/AttributeList.h"


namespace SmartMet
{
namespace GRIB1
{

class Message;


// ====================================================================================
/*! \brief Packing algorithm used to encode grid values in a GRIB 1 Data Section. */
// ====================================================================================

enum class PackingMethod
{
  UNKNOWN,                             //!< Unknown or unsupported packing.
  SIMPLE_PACKING,                      //!< Standard simple packing (uniform bit-width).
  SECOND_ORDER_PACKING,                //!< Second-order (complex) packing.
  SPHERICAL_HARMONICS_SIMPLE_PACKING,  //!< Spherical harmonics, simple packing.
  SPHERICAL_HARMONICS_COMPLEX_PACKING  //!< Spherical harmonics, complex packing.
};


// ====================================================================================
/*! \brief Abstract base class for GRIB 1 data-packing strategies.
 *
 *  Concrete subclasses (SimplePacking, SecondOrderPacking, etc.) implement the
 *  packing-specific decode/encode logic.  The DataSection owns one DataDefinition
 *  and delegates all value-level I/O to it. */
// ====================================================================================

class DataDefinition
{
  public:
                            DataDefinition();
                            DataDefinition(const DataDefinition& other);
    virtual                 ~DataDefinition();

    virtual DataDefinition* createDataDefinition() const;
    virtual void            getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    virtual PackingMethod   getPackingMethod() const;
    virtual bool            getValueByIndex(Message *message,uint index,T::ParamValue& value) const;
    virtual void            decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    virtual void            encodeValues(Message *message,T::ParamValue_vec& values);

    virtual void            getProperties(T::PropertySettingVec& properties);

    virtual void            read(MemoryReader& memoryReader);
    virtual void            write(DataWriter& dataWriter);
    virtual void            print(std::ostream& stream,uint level,uint optionFlags) const;
};


typedef std::unique_ptr<DataDefinition> DataDefintionUptr;  //!< Owning pointer to a DataDefinition.

}  // namespace GRIB1
}  // namespace SmartMet

#pragma once

#include "grid/Typedefs.h"
#include "grid/Dimensions.h"
#include "common/MemoryReader.h"
#include "common/AttributeList.h"


namespace SmartMet
{
namespace GRIB1
{

class Message;

enum class PackingMethod
{
  UNKNOWN,
  SIMPLE_PACKING,
  SECOND_ORDER_PACKING,
  SPHERICAL_HARMONICS_SIMPLE_PACKING,
  SPHERICAL_HARMONICS_COMPLEX_PACKING
};


class DataDefinition
{
  public:
                  DataDefinition();
    virtual       ~DataDefinition();

    virtual void  getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    virtual PackingMethod getPackingMethod() const;
    virtual bool  getValueByIndex(Message *message,uint index,T::ParamValue& value) const;
    virtual void  decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    virtual void  print(std::ostream& stream,uint level,uint optionFlags) const;
    virtual void  read(MemoryReader& memoryReader);
};


typedef std::unique_ptr<DataDefinition> DataDefintionUptr;

}  // namespace GRIB1
}  // namespace SmartMet

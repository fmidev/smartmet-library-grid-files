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


typedef std::unique_ptr<DataDefinition> DataDefintionUptr;

}  // namespace GRIB1
}  // namespace SmartMet

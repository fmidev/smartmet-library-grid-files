#pragma once

#include "../grid/Typedefs.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/AttributeList.h"
#include "../grib2/definition/PackingSettings.h"
#include "../grib2/definition/OriginalValuesSettings.h"


namespace SmartMet
{
namespace GRIB2
{

class Message;

// ====================================================================================
/*! \brief Abstract base class for GRIB 2 data representation templates (Section 5).
 *
 *  Concrete subclasses implement Data Representation Template 5.x encoding schemes
 *  (grid data, JPEG2000, PNG, spectral, etc.).  The RepresentationSection owns one
 *  RepresentationDefinition and delegates decode/encode operations to it.
 *  Sub-structure access is provided through PackingSettings and OriginalValuesSettings. */
// ====================================================================================

class RepresentationDefinition
{
  public:
                  RepresentationDefinition();
                  //RepresentationDefinition(const RepresentationDefinition& other);
    virtual       ~RepresentationDefinition();

    virtual void  decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    virtual void  encodeValues(Message *message,T::ParamValue_vec& values);
    virtual void  getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    virtual uint  getTemplateNumber() const;
    virtual bool  getValueByIndex(Message *message,uint index,T::ParamValue& value) const;

    virtual bool  getProperty(uint propertyId,Int64& value);
    virtual bool  getProperty_Packing(uint propertyId,Int64& value);
    virtual bool  getProperty_OriginalValues(uint propertyId,Int64& value);
    virtual void  getProperties(T::PropertySettingVec& properties);
    virtual void  getProperties_Packing(T::PropertySettingVec& properties);
    virtual void  getProperties_OriginalValues(T::PropertySettingVec& properties);

    virtual bool  setProperty(uint propertyId,Int64 value);
    virtual bool  setProperty_Packing(uint propertyId,Int64 value);
    virtual bool  setProperty_OriginalValues(uint propertyId,Int64 value);

    virtual void  read(MemoryReader& memoryReader);
    virtual void  write(DataWriter& dataWriter);
    virtual void  print(std::ostream& stream,uint level,uint optionFlags) const;

    virtual PackingSettings*          getPacking() const;
    virtual OriginalValuesSettings*   getOriginalValues() const;
    virtual RepresentationDefinition* createRepresentationDefinition() const;
};


typedef std::shared_ptr<RepresentationDefinition> RepresentationDefinition_sptr;  //!< Shared ownership pointer to a RepresentationDefinition.

}  // namespace GRIB2
}  // namespace SmartMet

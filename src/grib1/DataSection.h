#pragma once

#include "DataDefinition.h"
#include "../common/DataWriter.h"
#include "../grid/MessageSection.h"
#include "../grid/Typedefs.h"

#include <memory>


namespace SmartMet
{
namespace GRIB1
{

class Message;


// ====================================================================================
/*!
  \brief This class is used for accessing information that is found from
  the Data section in a GRIB file.

  When a message in a GRIB file is read, the Message class creates a new DataSection
  object and calls its read() method in order to read the section information into
  the object. After that the section information can be easily accessed through
  the current object.
*/
// ====================================================================================

/*
  --------------------------------------------------------------------------------------
  Section 4 - Binary data section
  --------------------------------------------------------------------------------------
  Octet   Contents
  --------------------------------------------------------------------------------------
  1-3     Length of section (octets)
  4       Flag (see Code table 11) (first 4 bits).
          Number of unused bits at end of Section 4 (last 4 bits)
  5-6     Scale factor (E)
  7-10    Reference value (minimum of packed values)
  11      Number of bits containing each packed value
  12-     Variable, depending on the flag value in octet 4
  --------------------------------------------------------------------------------------
*/



class DataSection : public GRID::MessageSection
{
  public:

                      DataSection();
                      DataSection(const DataSection& other);
              ~DataSection() override;

    // ### Common methods for all message sections

    void              getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const override;
    T::FilePosition   getFilePosition() const override;
    std::uint32_t     getSectionLength() const override;
    std::string       getSectionName() const override;
    std::uint8_t      getSectionNumber() const override;

    // ### Section specific methods

    void              decodeValues(T::ParamValue_vec& decodedValues) const;
    void              encodeValues(T::ParamValue_vec& values);
    std::uint8_t      getFlags() const;
    std::int16_t      getBinaryScaleFactor() const;
    std::float_t      getReferenceValue() const;
    std::uint8_t      getBitsPerValue() const;
    T::Data_ptr       getDataPtr() const;
    std::size_t       getDataSize() const;
    std::size_t       getDataSizeMax() const;
    PackingMethod     getPackingMethod() const;
    bool              getValueByIndex(uint index,T::ParamValue& value) const;

    void              setFlags(std::uint8_t flags);
    void              setBinaryScaleFactor(std::int16_t binaryScaleFactor);
    void              setReferenceValue(std::float_t referenceValue);
    void              setBitsPerValue(std::uint8_t bitsPerValue);
    void              setData(T::Data_ptr data,std::size_t size);
    void              setDataDefinition(ushort compressionMethod);
    void              setDataDefinition(DataDefinition *dataDefinition);
    void              setMessagePtr(Message *message);

    bool              getProperty(uint propertyId,long long& value);

    bool              setProperty(uint propertyId,long long value);
    bool              setProperty(uint propertyId,double value);

    void              read(MemoryReader& memoryReader);
    void              write(DataWriter& dataWriter);
    void              print(std::ostream& stream,uint level,uint optionFlags) const override;

  private:

    /*! \brief The pointer to the message object. */
    Message*          mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition   mFilePosition;

    /*! \brief The length of the section. */
    std::uint32_t     mSectionLength;

    std::uint8_t      mFlags;
    std::int16_t      mBinaryScaleFactor;
    std::float_t      mReferenceValue;
    std::uint8_t      mBitsPerValue;
    DataDefintionUptr mDataDefinition;
    T::Data_ptr       mDataPtr;
    std::size_t       mDataSize;
    std::size_t       mDataSizeMax;
    bool              mReleaseData;
};



enum DataSection_flags
{
  SphercicalHarmonicCoefficients = 1 << 7,
  ComplexPacking                 = 1 << 6,
  IntegerValues                  = 1 << 5,
  AdditionalFlags                = 1 << 4
};


/*
 Undocumented use of octet 14 extededFlags (in second order packing)
 -------------------------------------------------------------------
 R------- only bit 1 is reserved.
 -0------ single datum at each grid point.
 -1------ matrix of values at each grid point.
 --0----- no secondary bit map.
 --1----- secondary bit map present.
 ---0---- second order values have constant width.
 ---1---- second order values have different widths.
 ----0--- no general extended second order packing.
 ----1--- general extended second order packing used.
 -----0-- standard field ordering in section 4.
 -----1-- boustrophedonic ordering in section 4.
 ------00 no spatial differencing used.
 ------01 1st-order spatial differencing used.
 ------10 2nd-order    "         "         " .
 ------11 3rd-order    "         "         " .
*/

enum DataSection_additionalFlags
{
  MatrixOfValues                 = 64,
  SecondaryBitmapsPresent        = 32,
  DifferentValueWidths           = 16,
  GeneralExtendedPacking         = 8,
  BoustrophedonicOrdering        = 4,
  SpatialDifferencingPlus2       = 2,
  SpatialDifferencingPlus1       = 1
};


using DataSect_sptr = std::shared_ptr<DataSection>;


}  // namespace GRIB1
}  // namespace SmartMet

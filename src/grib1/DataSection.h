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
    virtual           ~DataSection();

    // ### Common methods for all message sections

    void              getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    T::FilePosition   getFilePosition() const;
    std::uint32_t     getSectionLength() const;
    std::string       getSectionName() const;
    std::uint8_t      getSectionNumber() const;

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

    bool              getProperty(uint propertyId,Int64& value);
    void              getProperties(T::PropertySettingVec& properties);

    bool              setProperty(uint propertyId,Int64 value);
    bool              setProperty(uint propertyId,double value);

    void              read(MemoryReader& memoryReader);
    void              write(DataWriter& dataWriter);
    void              print(std::ostream& stream,uint level,uint optionFlags) const;

  private:

    /*! \brief The pointer to the message object. */
    Message*          mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition   mFilePosition;

    /*! \brief The length of the section. */
    std::uint32_t     mSectionLength;

    std::uint8_t      mFlags;             //!< Packing/encoding flags (Code Table 11, octet 4 high nibble).
    std::int16_t      mBinaryScaleFactor; //!< Binary scale factor E (octet 5-6).
    std::float_t      mReferenceValue;    //!< Reference value R — minimum of packed values (octets 7-10).
    std::uint8_t      mBitsPerValue;      //!< Number of bits per packed value (octet 11).
    DataDefintionUptr mDataDefinition;    //!< Packing strategy (SimplePacking, SecondOrderPacking, etc.).
    T::Data_ptr       mDataPtr;           //!< Pointer to the (memory-mapped) packed binary data.
    std::size_t       mDataSize;          //!< Actual size of the packed data in bytes.
    std::size_t       mDataSizeMax;       //!< Allocated (maximum) buffer size in bytes.
    bool              mReleaseData;       //!< If true, free the data buffer on destruction.
};



/*! \brief High-nibble flag bits in the Data Section flags octet (Code Table 11). */
enum DataSection_flags
{
  SphercicalHarmonicCoefficients = 1 << 7,  //!< Data contains spherical harmonic coefficients.
  ComplexPacking                 = 1 << 6,  //!< Complex (second-order) packing is used.
  IntegerValues                  = 1 << 5,  //!< Grid values are integers rather than floats.
  AdditionalFlags                = 1 << 4   //!< Additional flags present in octet 14.
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

/*! \brief Bit flags for the extended flags byte (octet 14) in second-order packing. */
enum DataSection_additionalFlags
{
  MatrixOfValues                 = 64,  //!< Matrix of values at each grid point.
  SecondaryBitmapsPresent        = 32,  //!< Secondary bit-map present.
  DifferentValueWidths           = 16,  //!< Second-order values have different bit-widths.
  GeneralExtendedPacking         = 8,   //!< General extended second-order packing in use.
  BoustrophedonicOrdering        = 4,   //!< Boustrophedonic (zigzag) ordering in Section 4.
  SpatialDifferencingPlus2       = 2,   //!< 2nd-order spatial differencing applied.
  SpatialDifferencingPlus1       = 1    //!< 1st-order spatial differencing applied.
};


typedef std::shared_ptr<DataSection> DataSect_sptr;  //!< Shared ownership pointer to a DataSection.


}  // namespace GRIB1
}  // namespace SmartMet

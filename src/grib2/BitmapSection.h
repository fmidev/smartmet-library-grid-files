#pragma once

#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../grid/MessageSection.h"

namespace SmartMet
{
namespace GRIB2
{

class Message;


// ====================================================================================
/*!
  \brief This class is used for accessing information that is found from
  the Bitmap section in a GRIB file.

  When a message in a GRIB file is read, the Message class creates
  a new BitmapSection object and calls its read() method in order to read
  the section information into the object. After that the section information
  can be easily accessed through the current object.
*/
// ====================================================================================

/*
  --------------------------------------------------------------------------------------
  SECTION 6 - BIT-MAP SECTION
  --------------------------------------------------------------------------------------
  Octet   Contents
  --------------------------------------------------------------------------------------
  1-4     Length of section in octets (nn)
  5       Number of section (6)
  6       Bit-map indicator (see Code Table 6.0)
  7-nn    Bit-map
  --------------------------------------------------------------------------------------
*/


class BitmapSection : public GRID::MessageSection
{
  public:

                    BitmapSection();
                    BitmapSection(const BitmapSection& other);
    virtual         ~BitmapSection();

    // ### Common methods for all message sections

    void            getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    T::FilePosition getFilePosition() const;
    std::uint32_t   getSectionLength() const;
    std::string     getSectionName() const;
    std::uint8_t    getSectionNumber() const;

    // ### Section specific methods

    std::uint8_t    getNumberOfSection() const;
    T::UInt8_opt    getBitMapIndicator() const;
    T::Data_ptr     getBitmapDataPtr() const;
    std::size_t     getBitmapDataSizeInBytes() const;
    long long       getHash();
    void            getIndexVector(uint numOfValues,T::IndexVector& indexVector);

    void            setBitMapIndicator(uchar ind);
    void            setBitmapData(T::Data_ptr data,std::size_t size);
    void            setMessagePtr(Message *message);

    bool            getProperty(uint propertyId,long long& value);
    bool            setProperty(uint propertyId,long long value);

    void            read(MemoryReader& memoryReader);
    void            write(DataWriter& dataWriter);
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

  private:

    /*! \brief The pointer to the message object. */
    Message*        mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition mFilePosition;

    /*! \brief The length of the section. */
    T::UInt32_opt   mSectionLength;

    /*! \brief The section number. */
    T::UInt8_opt    mNumberOfSection;

    /*! \brief The Bitmap indicator (see Code Table 6.0) */
    T::UInt8_opt    mBitmapIndicator;

    /*! \brief The pointer to the bitmap. */
    T::Data_ptr     mBitmapDataPtr;

    /*! \brief  The bitmap size in bytes. */
    std::size_t     mBitmapDataSizeInBytes;

    long long       mHash;

    bool            mReleaseData;
};


typedef std::shared_ptr<BitmapSection> BitmapSect_sptr;

}  // namespace GRIB2
}  // namespace SmartMet

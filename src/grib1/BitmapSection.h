#pragma once

#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../grid/MessageSection.h"

#include <vector>


namespace SmartMet
{
namespace GRIB1
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
  Section 3 - Bitmap section
  --------------------------------------------------------------------------------------
  Octet   Contents
  --------------------------------------------------------------------------------------
  1-3     Length of section (octets)
  4       Number of unused bits at end of Section 3
  5-6     Table reference:
          If the octets contain zero, a bit-map follows
          If the octets contain a number, it refers to a predetermined bit-map provided
          by the center
  7-      The bit-map - contiguous bits with a bit to data point correspondance, ordered
          as defined in the grid definition
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

    T::Data_ptr     getBitmapDataPtr() const;
    std::size_t     getBitmapDataSizeInBytes() const;
    long long       getHash();
    void            getIndexVector(uint numOfValues,T::IndexVector& indexVector);

    void            setNumberOfUnusedBits(std::uint8_t unusedBits);
    void            setTableReference(std::uint16_t reference);
    void            setBitmapData(T::Data_ptr data,std::size_t size);
    void            setMessagePtr(Message *message);

    void            read(MemoryReader& memoryReader);
    void            write(DataWriter& dataWriter);
    void            print(std::ostream& stream,uint level,uint optionFlags) const;


  private:

    /*! \brief The pointer to the message object. */
    Message*        mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition mFilePosition;

    /*! \brief The length of the section. */
    std::uint32_t   mSectionLength;

    /*! \brief The number of unused bits at end of the section. */
    std::uint8_t    mNumberOfUnusedBits;

    /*! \brief The table reference. If the value is zero, a bitmap follows. If the octets contain a number,
        it refers to a predetermined bitmap provided. */
    std::uint16_t   mTableReference;

    /*! \brief The pointer to the (memory mapped) bitmap. */
    T::Data_ptr     mBitmapDataPtr;

    /*! \brief The bitmap size in bytes. */
    std::size_t     mBitmapDataSizeInBytes;

    long long       mHash;

    bool            mReleaseData;
};


typedef std::shared_ptr<BitmapSection> BitmapSect_sptr;

}  // namespace GRIB1
}  // namespace SmartMet

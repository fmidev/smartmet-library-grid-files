#pragma once

#include "DataDefinition.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/BitArrayReader.h"

namespace SmartMet
{
namespace GRIB1
{


// ====================================================================================
/*! \brief GRIB 1 simple-packing decoder/encoder.
 *
 *  Implements the standard GRIB 1 packing scheme where all grid values are encoded
 *  with a uniform bit-width after applying a linear scale:
 *    value = (R + 2^E * packed_value) * 10^(-D)
 *  Scale parameters are read lazily from the owning Message on the first decode call
 *  and cached in the mutable fields. */
// ====================================================================================

class SimplePacking : public DataDefinition
{
  public:
                    SimplePacking();
                    SimplePacking(const SimplePacking& other);
    virtual         ~SimplePacking();

    DataDefinition* createDataDefinition() const;
    void            decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void            encodeValues(Message *message,T::ParamValue_vec& encodeValues);
    PackingMethod   getPackingMethod() const;
    bool            getValueByIndex(Message *message,uint index,T::ParamValue& value) const;

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

  protected:

    void            init(Message *message) const;

    mutable std::size_t     mNumOfValues;          //!< Number of grid values.
    mutable T::Data_ptr     mData;                 //!< Pointer to the packed binary data.
    mutable std::size_t     mDataSize;             //!< Size of the packed data in bytes.
    mutable std::int16_t    mBinaryScaleFactor;    //!< Binary scale factor E.
    mutable std::uint16_t   mDecimalScaleFactor;   //!< Decimal scale factor D.
    mutable std::float_t    mReferenceValue;       //!< Reference value R (minimum packed value).
    mutable std::uint8_t    mBitsPerValue;         //!< Number of bits used for each packed value.
    mutable double          mEfac;                 //!< Precomputed 2^E.
    mutable double          mDfac;                 //!< Precomputed 10^(-D).
    mutable double          mRDfac;                //!< Precomputed R * 10^(-D).
    mutable double          mEDfac;                //!< Precomputed 2^E * 10^(-D).
    mutable bool            mInitialized;          //!< True after lazy init() has run.


};

}  // namespace GRIB1
}  // namespace SmartMet

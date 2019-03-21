#pragma once

#include "DataDefinition.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/BitArrayReader.h"

namespace SmartMet
{
namespace GRIB1
{


class SimplePacking : public DataDefinition
{
  public:
                    SimplePacking();
                    SimplePacking(const SimplePacking& other);
    virtual         ~SimplePacking();

    DataDefinition* createDataDefinition() const;
    void            decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    PackingMethod   getPackingMethod() const;
    bool            getValueByIndex(Message *message,uint index,T::ParamValue& value) const;

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

  protected:

    void            init(Message *message) const;

    mutable std::size_t     mNumOfValues;
    mutable T::Data_ptr     mData;
    mutable std::size_t     mDataSize;
    mutable std::int16_t    mBinaryScaleFactor;
    mutable std::uint16_t   mDecimalScaleFactor;
    mutable std::float_t    mReferenceValue;
    mutable std::uint8_t    mBitsPerValue;
    mutable double          mEfac;
    mutable double          mDfac;
    mutable double          mRDfac;
    mutable double          mEDfac;
    mutable bool            mInitialized;


};

}  // namespace GRIB1
}  // namespace SmartMet

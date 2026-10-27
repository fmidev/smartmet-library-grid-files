#pragma once

#include "../definition/GridDataRepresentation.h"
#include "../../common/BitArrayReader.h"


namespace SmartMet
{
namespace GRIB2
{

class GridDataRepresentationImpl : public GridDataRepresentation
{
  public:
              GridDataRepresentationImpl();
              GridDataRepresentationImpl(const GridDataRepresentationImpl& other);
    ~GridDataRepresentationImpl() override;
    GridDataRepresentationImpl& operator=(const GridDataRepresentationImpl&) = default;

    RepresentationDefinition* createRepresentationDefinition() const override;

    bool      getValueByIndex(Message *message,uint index,T::ParamValue& value) const override;
    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    void      encodeValues(Message *message,T::ParamValue_vec& values) override;
    void      read(MemoryReader& memoryReader) override;

  protected:

    void      init(Message *message) const;


    mutable T::Data_ptr     mData = nullptr;
    mutable std::size_t     mDataSize = 0;
    mutable std::int16_t    mBinaryScaleFactor = 0;
    mutable std::uint16_t   mDecimalScaleFactor = 0;
    mutable std::float_t    mReferenceValue = 0.0F;
    mutable std::uint8_t    mBitsPerValue = 0;
    mutable double          mEfac = 0.0;
    mutable double          mDfac = 0.0;
    mutable double          mRDfac = 0.0;
    mutable double          mEDfac = 0.0;
    mutable bool            mInitialized = false;
    mutable T::Data_ptr     mBitmap = nullptr;


};

}
}

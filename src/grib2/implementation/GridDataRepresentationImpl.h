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
    virtual   ~GridDataRepresentationImpl();

    RepresentationDefinition* createRepresentationDefinition() const;

    bool      getValueByIndex(Message *message,uint index,T::ParamValue& value) const;
    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      encodeValues(Message *message,T::ParamValue_vec& values);
    void      read(MemoryReader& memoryReader);

  protected:

    void      init(Message *message) const;


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

}
}

#pragma once

#include "Typedefs.h"

#include <tron/FmiBuilder.h>
#include <tron/Tron.h>


namespace SmartMet
{



class SimpleDataMatrixAdapter
{
  public:
    typedef float value_type;
    typedef double coord_type;
    typedef NFmiDataMatrix<float>::size_type size_type;


    SimpleDataMatrixAdapter(std::vector<float>& values,std::vector<T::Coordinate> *coordinates,uint width,uint height)
    {
      mValues = &values;
      mCoordinates = coordinates;
      mWidth = width;
      mHeight = height;
      mReleaseData = false;
      mMissingValue = NAN;
    }

    SimpleDataMatrixAdapter(const SimpleDataMatrixAdapter& other)
    {
      mValues = nullptr;
      mCoordinates = nullptr;
      mWidth = other.mWidth;
      mHeight = other.mHeight;
      mMissingValue = NAN;
      mReleaseData = true;

      if (other.mValues != nullptr)
      {
        mValues = new std::vector<float>();
        *mValues = *other.mValues;
      }

      if (other.mCoordinates != nullptr)
      {
        mCoordinates = new std::vector<T::Coordinate>();
        *mCoordinates = *other.mCoordinates;
      }
    }

    virtual ~SimpleDataMatrixAdapter()
    {
      if (mReleaseData)
      {
        if (mValues != nullptr)
          delete mValues;

        if (mCoordinates != nullptr)
          delete mCoordinates;
      }
    }

    const float& operator()(uint i, uint j) const
    {
      uint pos = (j % mHeight)*mWidth + (i % mWidth);
      if (mCoordinates != nullptr  &&  (*mCoordinates)[pos].x() == ParamValueMissing)
        return mMissingValue;

      if ((*mValues)[pos] == ParamValueMissing)
        return mMissingValue;

      return (*mValues)[pos];
    }

    float& operator()(uint i, uint j)
    {
      uint pos = (j % mHeight)*mWidth + (i % mWidth);
      if (mCoordinates != nullptr  &&  (*mCoordinates)[pos].x() == ParamValueMissing)
        return mMissingValue;

      if ((*mValues)[pos] == ParamValueMissing)
        return mMissingValue;

      return (*mValues)[pos];
    }

    double x(uint i, uint j) const
    {
      if (mCoordinates == nullptr)
        return i;

      if (i < mWidth  &&  j < mHeight)
        return (*mCoordinates)[(j % mHeight)*mWidth + i].x();

      return 360;
    }

    double y(uint i, uint j) const
    {
      if (mCoordinates == nullptr)
        return j;

      if (i < mWidth  &&  j < mHeight)
        return (*mCoordinates)[(j % mHeight)*mWidth + i].y();

      return 90;
    }

    uint width() const
    {
      return mWidth;
    }

    uint height() const
    {
      return mHeight;
    }

    bool valid(uint i, uint j) const
    {
      return true;
    }
  
    void swap(SimpleDataMatrixAdapter& other)
    {
      mWidth = other.mWidth;
      mHeight = other.mHeight;

      if (other.mValues != nullptr  &&  mValues != nullptr)
      {
        *mValues = *other.mValues;
      }

      if (other.mCoordinates != nullptr  &&  mCoordinates != nullptr)
      {
        mCoordinates = new std::vector<T::Coordinate>();
      }
    }


  private:
    std::vector<float>          *mValues;
    std::vector<T::Coordinate>  *mCoordinates;
    uint                        mWidth;
    uint                        mHeight;
    bool                        mReleaseData;
    float                       mMissingValue;
};



}

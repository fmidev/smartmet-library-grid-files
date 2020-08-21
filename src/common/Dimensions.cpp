#include "Dimensions.h"
#include "Exception.h"
#include "GeneralFunctions.h"
#include <macgyver/StringConversion.h>


namespace SmartMet
{
namespace T
{


Dimensions::Dimensions()
{
  try
  {
    mDimensions = 0;
    mSizes = nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Dimensions::Dimensions(const Dimensions& dimensions)
{
  try
  {
    mDimensions = dimensions.mDimensions;
    if (mDimensions > 0)
    {
      mSizes = new uint[mDimensions];
      memcpy(mSizes,dimensions.mSizes,mDimensions*sizeof(uint));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






Dimensions::Dimensions(uint nx)
{
  try
  {
    mDimensions = 1;
    mSizes = new uint[mDimensions];
    mSizes[0] = nx;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Dimensions::Dimensions(uint nx,uint ny)
{
  try
  {
    mDimensions = 2;
    mSizes = new uint[mDimensions];
    mSizes[0] = nx;
    mSizes[1] = ny;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Dimensions::Dimensions(uint nx,uint ny,uint nz)
{
  try
  {
    mDimensions = 3;
    mSizes = new uint[mDimensions];
    mSizes[0] = nx;
    mSizes[1] = ny;
    mSizes[2] = nz;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Dimensions::Dimensions(uint dimensions,uint *sizeArray)
{
  try
  {
    mDimensions = dimensions;
    mSizes = new uint[mDimensions];
    for (uint t=0; t<mDimensions; t++)
      mSizes[t] = sizeArray[t];
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Dimensions::~Dimensions()
{
  try
  {
    if (mSizes != nullptr)
      delete[] mSizes;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





uint Dimensions::nx() const
{
  try
  {
    if (mDimensions >= 1)
      return mSizes[0];

    SmartMet::Spine::Exception exception(BCP,"No such dimension!");
    exception.addParameter("Dimensions",Fmi::to_string(mDimensions));
    throw exception;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint Dimensions::ny() const
{
  try
  {
    if (mDimensions >= 2)
      return mSizes[1];

    throw SmartMet::Spine::Exception(BCP,"No such dimension!");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint Dimensions::nz() const
{
  try
  {
    if (mDimensions >= 3)
      return mSizes[2];

    throw SmartMet::Spine::Exception(BCP,"No such dimension!");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint Dimensions::getDimensions() const
{
  try
  {
    return mDimensions;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint Dimensions::getSize(uint dimension) const
{
  try
  {
    if (dimension < mDimensions)
      return mSizes[dimension];

    throw SmartMet::Spine::Exception(BCP,"No such dimension!");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void Dimensions::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "Dimensions\n";
    stream << space(level) << "- mDimensions  = " << mDimensions << "\n";

    for (uint t=0; t<mDimensions; t++)
      stream << space(level) << "   [" << t << "] = " << mSizes[t] << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}
}  // namespace SmartMet

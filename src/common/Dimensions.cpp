#include "Dimensions.h"
#include "GeneralFunctions.h"
#include <macgyver/StringConversion.h>
#include <macgyver/Exception.h>


namespace SmartMet
{
namespace T
{


Dimensions::Dimensions()
{
  try
  {
    mDimensions = 0;
    mSizes[0] = 0;
    mSizes[1] = 0;
    mSizes[2] = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Dimensions::Dimensions(const Dimensions& dimensions)
{
  try
  {
    mDimensions = dimensions.mDimensions;
    mSizes[0] = dimensions.mSizes[0];
    mSizes[1] = dimensions.mSizes[1];
    mSizes[2] = dimensions.mSizes[2];
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






Dimensions::Dimensions(uint nx)
{
  try
  {
    mDimensions = 1;
    mSizes[0] = nx;
    mSizes[1] = 0;
    mSizes[2] = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Dimensions::Dimensions(uint nx,uint ny)
{
  try
  {
    mDimensions = 2;
    mSizes[0] = nx;
    mSizes[1] = ny;
    mSizes[2] = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Dimensions::Dimensions(uint nx,uint ny,uint nz)
{
  try
  {
    mDimensions = 3;
    mSizes[0] = nx;
    mSizes[1] = ny;
    mSizes[2] = nz;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Dimensions::~Dimensions()
{
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





uint Dimensions::nx() const
{
  try
  {
    if (mDimensions >= 1)
      return mSizes[0];

    Fmi::Exception exception(BCP,"No such dimension!");
    exception.addParameter("Dimensions",Fmi::to_string(mDimensions));
    throw exception;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint Dimensions::ny() const
{
  try
  {
    if (mDimensions >= 2)
      return mSizes[1];

    throw Fmi::Exception(BCP,"No such dimension!");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint Dimensions::nz() const
{
  try
  {
    if (mDimensions >= 3)
      return mSizes[2];

    throw Fmi::Exception(BCP,"No such dimension!");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint Dimensions::getSize(uint dimension) const
{
  try
  {
    if (dimension < mDimensions)
      return mSizes[dimension];

    throw Fmi::Exception(BCP,"No such dimension!");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}  // namespace SmartMet

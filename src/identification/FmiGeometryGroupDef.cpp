#include "FmiGeometryGroupDef.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{



/*! \brief The constructor of the class. */

FmiGeometryGroupDef::FmiGeometryGroupDef()
{
  try
  {
    mGeometryGroupId = 0;
    mGroupType = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The destructor of the class. */

FmiGeometryGroupDef::~FmiGeometryGroupDef()
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





/*! \brief Prints the content of the object into the given stream. */

void FmiGeometryGroupDef::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "FmiGeometryGroupDef\n";
    stream << space(level) << "- mGeometryGroupId   = " << mGeometryGroupId << "\n";
    stream << space(level) << "- mGroupType         = " << mGroupType << "\n";
    stream << space(level) << "- mProducerName      = " << mProducerName << "\n";
    stream << space(level) << "- mGeometryIdList    = \n";

    for (auto it = mGeometryIdList.begin(); it != mGeometryIdList.end(); ++it)
      stream << space(level) << "    * " << *it << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}


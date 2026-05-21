#include "AggregationDef.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


/*! \brief The constructor of the class. */

AggregationDef::AggregationDef()
{
  try
  {
    mAggregationId = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The destructor of the class. */

AggregationDef::~AggregationDef()
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

void AggregationDef::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "AggregationDef\n";
    stream << space(level) << "- mAggregationId = " << mAggregationId << "\n";
    stream << space(level) << "- mName          = " << mName << "\n";
    stream << space(level) << "- mDescription   = " << mDescription << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}
}


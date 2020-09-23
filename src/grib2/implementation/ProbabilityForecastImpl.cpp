#include "ProbabilityForecastImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

ProbabilityForecastImpl::ProbabilityForecastImpl()
{
}





/*! \brief The copy constructor of the class. */

ProbabilityForecastImpl::ProbabilityForecastImpl(const ProbabilityForecastImpl& other)
:ProbabilityForecast(other)
{
}





/*! \brief The destructor of the class. */

ProbabilityForecastImpl::~ProbabilityForecastImpl()
{
}





/*! \brief The method creates a duplicate of the current object. */

ProductDefinition* ProbabilityForecastImpl::createProductDefinition() const
{
  try
  {
    return (ProductDefinition*)new ProbabilityForecastImpl(*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method reads and initializes all data related to the current object.
    The purpose of this method is to get access to the read operation that takes place
    in the parent class (which is automatically generated). This means in practice that
    we first call the read operation in the parent class. After that we can ensure that
    the result of the read operation was correct (i.e. attribute values are valid, etc).
    We can also modify or update some attribute values if needed.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ProbabilityForecastImpl::read(MemoryReader& memoryReader)
{
  try
  {
    ProbabilityForecast::read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the parameter level.

         \return   The parameter level.
*/

T::ParamLevel ProbabilityForecastImpl::getGribParameterLevel() const
{
  try
  {
    if (mHorizontal.getScaledValueOfFirstFixedSurface())
      return *mHorizontal.getScaledValueOfFirstFixedSurface();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





/*! \brief The method returns the type of the parameter level.

         \return   The parameter level type (= enum value).
*/

T::ParamLevelId ProbabilityForecastImpl::getGribParameterLevelId() const
{
  try
  {
    if (mHorizontal.getScaledValueOfFirstFixedSurface())
      return *mHorizontal.getTypeOfFirstFixedSurface();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



}  // namespace GRIB2
}  // namespace SmartMet

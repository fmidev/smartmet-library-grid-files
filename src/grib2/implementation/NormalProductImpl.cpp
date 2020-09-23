#include "NormalProductImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

NormalProductImpl::NormalProductImpl()
{
}





/*! \brief The copy constructor of the class. */

NormalProductImpl::NormalProductImpl(const NormalProductImpl& other)
:NormalProduct(other)
{
}




/*! \brief The destructor of the class. */

NormalProductImpl::~NormalProductImpl()
{
}





/*! \brief The method creates a duplicate of the current object. */

ProductDefinition* NormalProductImpl::createProductDefinition() const
{
  try
  {
    return (ProductDefinition*)new NormalProductImpl(*this);
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

void NormalProductImpl::read(MemoryReader& memoryReader)
{
  try
  {
    NormalProduct::read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the parameter level.

         \return   The parameter level.
*/

T::ParamLevel NormalProductImpl::getGribParameterLevel() const
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

T::ParamLevelId NormalProductImpl::getGribParameterLevelId() const
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

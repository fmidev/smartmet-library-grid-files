#include "Product_73Impl.h"
#include "../../common/Exception.h"
#include "../../common/GeneralFunctions.h"

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

Product_73Impl::Product_73Impl()
{
}





/*! \brief The copy constructor of the class. */

Product_73Impl::Product_73Impl(const Product_73Impl& other)
:Product_73(other)
{
}




/*! \brief The destructor of the class. */

Product_73Impl::~Product_73Impl()
{
}





/*! \brief The method creates a duplicate of the current object. */

ProductDefinition* Product_73Impl::createProductDefinition() const
{
  try
  {
    return (ProductDefinition*)new Product_73Impl(*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

void Product_73Impl::read(MemoryReader& memoryReader)
{
  try
  {
    Product_73::read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the parameter level.

         \return   The parameter level.
*/

T::ParamLevel Product_73Impl::getGribParameterLevel() const
{
  try
  {
    if (mHorizontal.getScaledValueOfFirstFixedSurface())
      return *mHorizontal.getScaledValueOfFirstFixedSurface();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}





/*! \brief The method returns the type of the parameter level.

         \return   The parameter level type (= enum value).
*/

T::ParamLevelId Product_73Impl::getGribParameterLevelId() const
{
  try
  {
    if (mHorizontal.getScaledValueOfFirstFixedSurface())
      return *mHorizontal.getTypeOfFirstFixedSurface();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}


}  // namespace GRIB2
}  // namespace SmartMet

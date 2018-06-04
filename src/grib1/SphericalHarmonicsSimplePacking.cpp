#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"
#include "SphericalHarmonicsSimplePacking.h"


namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

SphericalHarmonicsSimplePacking::SphericalHarmonicsSimplePacking()
{
}





/*! \brief The destructor of the class. */

SphericalHarmonicsSimplePacking::~SphericalHarmonicsSimplePacking()
{
}





PackingMethod SphericalHarmonicsSimplePacking::getPackingMethod() const
{
  try
  {
    return PackingMethod::SPHERICAL_HARMONICS_SIMPLE_PACKING;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




void SphericalHarmonicsSimplePacking::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    throw SmartMet::Spine::Exception(BCP,"SphericalHarmonicsSimplePacking not implemented!");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void SphericalHarmonicsSimplePacking::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "SphericalHarmonicsSimplePacking\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet

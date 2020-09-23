#include <macgyver/Exception.h>
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





/*! \brief The copy constructor of the class. */

SphericalHarmonicsSimplePacking::SphericalHarmonicsSimplePacking(const SphericalHarmonicsSimplePacking& other)
:DataDefinition(other)
{
}





/*! \brief The destructor of the class. */

SphericalHarmonicsSimplePacking::~SphericalHarmonicsSimplePacking()
{
}





DataDefinition* SphericalHarmonicsSimplePacking::createDataDefinition() const
{
  try
  {
    return (DataDefinition*) new SphericalHarmonicsSimplePacking(*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





PackingMethod SphericalHarmonicsSimplePacking::getPackingMethod() const
{
  try
  {
    return PackingMethod::SPHERICAL_HARMONICS_SIMPLE_PACKING;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void SphericalHarmonicsSimplePacking::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    throw Fmi::Exception(BCP,"SphericalHarmonicsSimplePacking not implemented!");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet

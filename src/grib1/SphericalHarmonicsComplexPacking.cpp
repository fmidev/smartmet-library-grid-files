#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"
#include "SphericalHarmonicsComplexPacking.h"


namespace SmartMet
{
namespace GRIB1
{



/*! \brief The constructor of the class. */

SphericalHarmonicsComplexPacking::SphericalHarmonicsComplexPacking()
{
  try
  {
    mN = 0;
    mIP = 0;
    mJ1 = 0;
    mK1 = 0;
    mM1 = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The copy constructor of the class. */

SphericalHarmonicsComplexPacking::SphericalHarmonicsComplexPacking(const SphericalHarmonicsComplexPacking& other)
:DataDefinition(other)
{
  try
  {
    mN = other.mN;
    mIP = other.mIP;
    mJ1 = other.mJ1;
    mK1 = other.mK1;
    mM1 = other.mM1;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The destructor of the class. */

SphericalHarmonicsComplexPacking::~SphericalHarmonicsComplexPacking()
{
}





PackingMethod SphericalHarmonicsComplexPacking::getPackingMethod() const
{
  try
  {
    return PackingMethod::SPHERICAL_HARMONICS_COMPLEX_PACKING;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





DataDefinition* SphericalHarmonicsComplexPacking::createDataDefinition() const
{
  try
  {
    return (DataDefinition*) new SphericalHarmonicsComplexPacking(*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void SphericalHarmonicsComplexPacking::read(MemoryReader& memoryReader)
{
  try
  {
    memoryReader >> mN;
    memoryReader >> mIP;
    memoryReader >> mJ1;
    memoryReader >> mK1;
    memoryReader >> mM1;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void SphericalHarmonicsComplexPacking::write(DataWriter& dataWriter)
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void SphericalHarmonicsComplexPacking::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    throw SmartMet::Spine::Exception(BCP,"SphericalHarmonicsComplexPacking not implemented!");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void SphericalHarmonicsComplexPacking::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "SphericalHarmonicsComplexPacking\n";
    stream << space(level) << "- N  = " << toString(mN) << "\n";
    stream << space(level) << "- IP = " << toString(mIP) << "\n";
    stream << space(level) << "- J1 = " << toString(mJ1) << "\n";
    stream << space(level) << "- K1 = " << toString(mK1) << "\n";
    stream << space(level) << "- M1 = " << toString(mM1) << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet

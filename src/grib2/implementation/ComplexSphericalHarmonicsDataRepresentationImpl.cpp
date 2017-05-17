#include "ComplexSphericalHarmonicsDataRepresentationImpl.h"
#include "common/Exception.h"


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

ComplexSphericalHarmonicsDataRepresentationImpl::ComplexSphericalHarmonicsDataRepresentationImpl()
{
}





/*! \brief The copy constructor of the class. */

ComplexSphericalHarmonicsDataRepresentationImpl::ComplexSphericalHarmonicsDataRepresentationImpl(const ComplexSphericalHarmonicsDataRepresentationImpl& other)
:ComplexSphericalHarmonicsDataRepresentation(other)
{
}





/*! \brief The destructor of the class. */

ComplexSphericalHarmonicsDataRepresentationImpl::~ComplexSphericalHarmonicsDataRepresentationImpl()
{
}





/*! \brief The method reads and initializes all data related to the current object.
    The purpose of this method is to get access to the read operation that takes place
    in the parent class (which is automatically generated). This means in practice that
    we first call the read operation in the parent class. After that we can ensure that
    the result of the read operation was correct (i.e. attribute values are valid, etc).
    We can also modify or update some attribute values if needed.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ComplexSphericalHarmonicsDataRepresentationImpl::read(MemoryReader& memoryReader)
{
  try
  {
    ComplexSphericalHarmonicsDataRepresentation::read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void ComplexSphericalHarmonicsDataRepresentationImpl::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  throw SmartMet::Spine::Exception(BCP,"The method not implemented!");
}


}
}

#include "SpectralDataRepresentationImpl.h"
#include "../../common/Exception.h"

namespace SmartMet
{
namespace GRIB2
{

/*! \brief The constructor of the class. */

SpectralDataRepresentationImpl::SpectralDataRepresentationImpl()
{
}





/*! \brief The copy constructor of the class. */

SpectralDataRepresentationImpl::SpectralDataRepresentationImpl(const SpectralDataRepresentationImpl& other)
:SpectralDataRepresentation(other)
{
}





/*! \brief The destructor of the class. */

SpectralDataRepresentationImpl::~SpectralDataRepresentationImpl()
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

void SpectralDataRepresentationImpl::read(MemoryReader& memoryReader)
{
  try
  {
    SpectralDataRepresentation::read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void SpectralDataRepresentationImpl::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  throw SmartMet::Spine::Exception(BCP,"The method not implemented!");
}


}
}

#include "MatrixDataRepresentationImpl.h"
#include <macgyver/Exception.h>


namespace SmartMet
{
namespace GRIB2
{



/*! \brief The constructor of the class. */

MatrixDataRepresentationImpl::MatrixDataRepresentationImpl()
{
}





/*! \brief The copy constructor of the class. */

MatrixDataRepresentationImpl::MatrixDataRepresentationImpl(const MatrixDataRepresentationImpl& other)
:MatrixDataRepresentation(other)
{
}





/*! \brief The destructor of the class. */

MatrixDataRepresentationImpl::~MatrixDataRepresentationImpl()
{
}





/*! \brief The method creates a duplicate of the current object. */

RepresentationDefinition* MatrixDataRepresentationImpl::createRepresentationDefinition() const
{
  try
  {
    return (RepresentationDefinition*) new MatrixDataRepresentationImpl(*this);
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

void MatrixDataRepresentationImpl::read(MemoryReader& memoryReader)
{
  try
  {
    MatrixDataRepresentation::read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MatrixDataRepresentationImpl::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  throw Fmi::Exception(BCP,"The method not implemented!");
}


}
}

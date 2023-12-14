#include "FloatingPointGridDataRepresentationImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/MemoryReader.h"
#include "../Message.h"

namespace SmartMet
{
namespace GRIB2
{

const int bitmask[] = {128, 64, 32, 16, 8, 4, 2, 1};

/*! \brief The constructor of the class. */

FloatingPointGridDataRepresentationImpl::FloatingPointGridDataRepresentationImpl()
{
}





/*! \brief The copy constructor of the class. */

FloatingPointGridDataRepresentationImpl::FloatingPointGridDataRepresentationImpl(const FloatingPointGridDataRepresentationImpl& other)
:FloatingPointGridDataRepresentation(other)
{
}





/*! \brief The destructor of the class. */

FloatingPointGridDataRepresentationImpl::~FloatingPointGridDataRepresentationImpl()
{
}





/*! \brief The method creates a duplicate of the current object. */

RepresentationDefinition* FloatingPointGridDataRepresentationImpl::createRepresentationDefinition() const
{
  try
  {
    return (RepresentationDefinition*) new FloatingPointGridDataRepresentationImpl(*this);
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

void FloatingPointGridDataRepresentationImpl::read(MemoryReader& memoryReader)
{
  try
  {
    FloatingPointGridDataRepresentation::read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void FloatingPointGridDataRepresentationImpl::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    T::Data_ptr bitmap = message->getBitmapDataPtr();

    if (numOfValues == 0)
      return;

    decodedValues.clear();
    decodedValues.reserve(numOfValues);

    MemoryReader memoryReader(data,dataSize);

    switch (*mPrecision)
    {
      case 1: // 32 bits
        if (bitmap == nullptr)
        {
          for (std::uint32_t i = 0; i < numOfValues; i++)
          {
            float val = memoryReader.read_float();
            decodedValues.emplace_back(val);
          }
        }
        else
        {
          for (std::uint32_t i = 0; i < numOfValues; i++)
          {
            if ((bitmap[i / 8] & bitmask[i % 8]) == 0)
            {
              decodedValues.emplace_back(ParamValueMissing);
            }
            else
            {
              float val = memoryReader.read_float();
              decodedValues.emplace_back(val);
            }
          }
        }
        break;

        case 2: // 64 bits
          if (bitmap == nullptr)
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              double val = memoryReader.read_double();
              decodedValues.emplace_back(val);
            }
          }
          else
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              if ((bitmap[i / 8] & bitmask[i % 8]) == 0)
              {
                decodedValues.emplace_back(ParamValueMissing);
              }
              else
              {
                double val = memoryReader.read_double();
                decodedValues.emplace_back(val);
              }
            }
          }
          break;

        case 3: // 128 bits
          break;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}

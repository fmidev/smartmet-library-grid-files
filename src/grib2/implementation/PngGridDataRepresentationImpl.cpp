#include "PngGridDataRepresentationImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"
#include "../../common/BitArrayReader.h"
#include "../Message.h"

#include <png.h>


namespace SmartMet
{
namespace GRIB2
{



using png_read_callback_data = struct png_read_callback_data
{
    unsigned char* buffer;
    size_t         length;
    size_t         offset;
};





static void png_read_callback(png_structp png,png_bytep data, png_size_t length)
{
  auto* p = (png_read_callback_data*)png_get_io_ptr(png);
  memcpy(data,p->buffer+p->offset,length);
  p->offset += length;
}





/*! \brief The constructor of the class. */

PngGridDataRepresentationImpl::PngGridDataRepresentationImpl()
{
}





/*! \brief The copy constructor of the class. */

PngGridDataRepresentationImpl::PngGridDataRepresentationImpl(const PngGridDataRepresentationImpl& other)
:PngGridDataRepresentation(other)
{
}





/*! \brief The destructor of the class. */

PngGridDataRepresentationImpl::~PngGridDataRepresentationImpl()
{
}






/*! \brief The method creates a duplicate of the current object. */

RepresentationDefinition* PngGridDataRepresentationImpl::createRepresentationDefinition() const
{
  try
  {
    return (RepresentationDefinition*) new PngGridDataRepresentationImpl(*this);
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

void PngGridDataRepresentationImpl::read(MemoryReader& memoryReader)
{
  try
  {
    PngGridDataRepresentation::read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void PngGridDataRepresentationImpl::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    T::Data_ptr bitmap = message->getBitmapDataPtr();
    std::size_t bitmapSizeInBytes = message->getBitmapDataSizeInBytes();

    //if (data == nullptr)
      //throw Fmi::Exception(BCP,"The 'data' pointer points to nullptr!");

    long bits_per_value = *mPacking.getBitsPerValue();
    double reference_value = mPacking.getReferenceValue();

    if (dataSize == 0 || data == nullptr ||  bits_per_value == 0)
    {
      if (bitmap != nullptr  &&  bitmapSizeInBytes > 0)
      {
        // There is no data, but there is a bitmap available.
        BitArrayReader bitmapReader(bitmap,bitmapSizeInBytes*8);
        for (std::uint32_t i=0; i<numOfValues; i++)
        {
          if (bitmapReader.readBit())
          {
            decodedValues.emplace_back(reference_value);
          }
          else
          {
            decodedValues.emplace_back(ParamValueMissing);
          }
        }
        return;
      }
      else
      {
        // All values are set to "reference_value".
        for (std::uint32_t i=0; i<numOfValues; i++)
        {
          decodedValues.emplace_back(reference_value);
        }
        return;
      }
    }


    if (png_sig_cmp(data,0,8) != 0)
    {
      throw Fmi::Exception(BCP,"Invalid PNG!");
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (png == nullptr)
    {
      throw Fmi::Exception(BCP,"PNG decoding failed!");
    }

    png_infop info = png_create_info_struct(png);
    if (info == nullptr)
    {
      png_destroy_read_struct(&png,&info,nullptr);
      throw Fmi::Exception(BCP,"PNG decoding error!");
    }

    png_infop theEnd = png_create_info_struct(png);
    if (theEnd == nullptr)
    {
      png_destroy_read_struct(&png,&info,&theEnd);
      throw Fmi::Exception(BCP,"PNG decoding error!");
    }

    if (setjmp(png_jmpbuf(png)))
    {
      png_destroy_read_struct(&png,&info,&theEnd);
      throw Fmi::Exception(BCP,"PNG decoding error!");
    }

    png_uint_32 width = 0;
    png_uint_32 height = 0;
    int interlace = 0;
    int colour = 0;
    int compression = 0;
    int filter = 0;
    int depth = 0;
    png_read_callback_data callback_data;

    callback_data.buffer = data;
    callback_data.offset = 0;
    callback_data.length = dataSize;

    png_set_read_fn(png,&callback_data,png_read_callback);
    png_read_png(png, info, PNG_TRANSFORM_IDENTITY, nullptr);
    png_bytepp rows = png_get_rows(png, info);
    png_get_IHDR(png, info, &width, &height,&depth, &colour,&interlace,&compression,&filter);

    long binary_scale_factor = *mPacking.getBinaryScaleFactor();
    long decimal_scale_factor = *mPacking.getDecimalScaleFactor();
    double bscale = grib_power(binary_scale_factor,2);
    double dscale = grib_power(-decimal_scale_factor,10);

    size_t len = width*bits_per_value;
    for (uint j=0; j<height; j++)
    {
      BitArrayReader dataReader(rows[j],len);
      for (uint k = 0 ; k < width; k++)
      {
        unsigned int value = 0;
        dataReader.readBits(bits_per_value,value);
        double val = (((value*bscale) + reference_value) * dscale);
        decodedValues.emplace_back(val);
      }
    }

    png_destroy_read_struct(&png,&info,&theEnd);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}
}

#include "JpegGridDataRepresentationImpl.h"
#include "common/Exception.h"
#include "common/BitArrayReader.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include "grib2/Message.h"
#include <jasper/jasper.h>

//#include <openjpeg-1.5/openjpeg.h>
#include <cstring>
#include <iostream>
#include <memory>

// TODO: See from FreeImage code for how to do this with openjpeg 2

namespace SmartMet
{
namespace GRIB2
{

/*! \brief The constructor of the class. */

JpegGridDataRepresentationImpl::JpegGridDataRepresentationImpl()
{
  if (jas_init())
  {
    abort();
  }
}





/*! \brief The copy constructor of the class. */

JpegGridDataRepresentationImpl::JpegGridDataRepresentationImpl(const JpegGridDataRepresentationImpl& other)
:JpegGridDataRepresentation(other)
{
}





/*! \brief The destructor of the class. */

JpegGridDataRepresentationImpl::~JpegGridDataRepresentationImpl()
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

void JpegGridDataRepresentationImpl::read(MemoryReader& memoryReader)
{
  try
  {
    JpegGridDataRepresentation::read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void JpegGridDataRepresentationImpl::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    T::Data_ptr bitmap = message->getBitmapDataPtr();
    std::size_t bitmapSizeInBytes = message->getBitmapDataSizeInBytes();

    char filename[100];
    sprintf(filename,"/tmp/smartmet-library-grid_jpg2000_decoding_%llu.jpg",getTime());
    FILE *file = fopen(filename,"w");
    fwrite(data,dataSize,1,file);
    fclose(file);

    jas_stream_t *instream = jas_stream_fopen(filename, "rb");
    if (instream == NULL)
    {
      SmartMet::Spine::Exception exception(BCP, "Cannot open the JPG-2000 file!");
      exception.addParameter("Filename",filename);
      throw exception;
    }

    int fmtid = jas_image_getfmt(instream);
    if (fmtid < 0)
    {
      SmartMet::Spine::Exception exception(BCP, "Not a JPG-2000 image!");
      exception.addParameter("Filename",filename);
      throw exception;
    }


    /* Decode the image. */

    jas_image_t *image = jas_image_decode(instream, fmtid, 0);

    /* Close the image file. */
    jas_stream_close(instream);
    remove(filename);

    if (image == NULL)
    {
      SmartMet::Spine::Exception exception(BCP, "Cannot decode the JPG-2000 image!");
      exception.addParameter("Filename",filename);
      throw exception;
    }

    //int numcmpts = jas_image_numcmpts(image);
    int width = jas_image_cmptwidth(image, 0);
    int height = jas_image_cmptheight(image, 0);
    int depth = jas_image_cmptprec(image, 0);

    int sz = width*height;

    // int rawsz = jas_image_rawsize(image);
    // printf("IMAGE %d x %d x %d => %d (%d)\n",width,height,depth,sz,rawsz);


    jas_matrix_t *matrix = jas_matrix_create(height,width);
    jas_image_readcmpt(image,0,0,0,width,height,matrix);

    // Vector to return
    decodedValues.clear();
    decodedValues.reserve(numOfValues);

    if (numOfValues == 0)
      return;

    // Sanity checks
    auto bits_per_value = mPacking.getBitsPerValue();
    if (!bits_per_value)
      throw SmartMet::Spine::Exception(BCP,"GridDataRepresentation number of bits per value must be > 0");

    // Number of bits per value
    //const unsigned int nbits = *bits_per_value;

    // Reference value R, IEEE 32-bit floating point value
    // TODO: GRIB1 USES IBM-FLOATS INSTEAD OF IEEE-754!!!!!
    double R = mPacking.getReferenceValue();

    // Binary scale factor E, possibly negative
    std::int16_t E = (mPacking.getBinaryScaleFactor() ? *mPacking.getBinaryScaleFactor() : 0);

    // Decimal scale factor D, possibly negative
    std::int16_t D = (mPacking.getDecimalScaleFactor() ? *mPacking.getDecimalScaleFactor() : 0);

    // Optimization: (R + X * Efac) * Dfac = RDfac + X * EDFac

    const double Efac = std::pow(2.0, E);
    const double Dfac = std::pow(10, -D);

    const double RDfac = R * Dfac;
    const double EDfac = Efac * Dfac;

    if (bitmapSizeInBytes > 0)
    {
      T::Data_ptr bmap = bitmap;
      unsigned char tmp = 0;
      if (bmap == NULL)
        bmap = &tmp;

      BitArrayReader bitmapReader(bmap,bitmapSizeInBytes*8);

      uint pos = 0;
      for (int i = 0; i < sz; i++)
      {
        if (bitmapReader.readBit())
        {
          int X = matrix->data_[pos];
          double Y = RDfac + X * EDfac;
          decodedValues.push_back((T::ParamValue)Y);
          pos++;
        }
        else
        {
          decodedValues.push_back(ParamValueMissing);
        }
      }
    }
    else
    {
      for (int i = 0; i < sz; i++)
      {
        int X = matrix->data_[i];
        double Y = RDfac + X * EDfac;
        decodedValues.push_back((T::ParamValue)Y);
      }
    }

    jas_matrix_destroy(matrix);
    jas_image_destroy(image);
    jas_image_clearfmts();

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "JPEG decodeValues failed!", NULL);
  }
}






#if 0

// **********************************************************************************'
//
//   NOTICE: The open-jpeg library is not very stable. It crashes quite often.
//   That's why we are using jasper -library instead.
//
// **********************************************************************************'



/*! \brief Decompression error call back */

void jpeg_error_callback(const char* msg, void* data)
{
  throw SmartMet::Spine::Exception(BCP, "JPEG Error: " + std::string(msg));
}





/*! \brief Decompression error call back */

void jpeg_warning_callback(const char* msg, void* data)
{
  throw SmartMet::Spine::Exception(BCP, "JPEG Warning: " + std::string(msg));
}





/*! \brief Decode raw decompressed JPEG data to actual values */

void decode_raw_jpeg_values(T::ParamValue_vec& values,
                            opj_image_t* image,
                            std::size_t numOfValues,
                            unsigned int nbits,
                            T::Data_ptr bitmap,
                            std::size_t bitmapSizeInBytes,
                            double RDfac,
                            double EDfac)
{
  try
  {
    T::Data_ptr bmap = bitmap;
    unsigned char tmp = 0;
    if (bmap == NULL)
      bmap = &tmp;

    BitArrayReader bitmapReader(bmap,bitmapSizeInBytes*8);

#ifdef DEBUG
    std::cout << "JPEG IMAGE METADATA:\n"
              << "x0 = " << image->x0 << "\n"
              << "y0 = " << image->y0 << "\n"
              << "x1 = " << image->x1 << "\n"
              << "y1 = " << image->y1 << "\n"
              << "numcomps = " << image->numcomps << "\n"
              << "profile_len = " << image->icc_profile_len << "\n";

    std::cout << "color_space = " << static_cast<int>(image->color_space) << " = ";
    switch (image->color_space)
    {
      case CLRSPC_UNKNOWN:
        std::cout << "UNKNOWN\n";
        break;
      case CLRSPC_UNSPECIFIED:
        std::cout << "UNSPECIFIED\n";
        break;
      case CLRSPC_SRGB:
        std::cout << "SRGB\n";
        break;
      case CLRSPC_GRAY:
        std::cout << "GRAY\n";
        break;
      case CLRSPC_SYCC:
        std::cout << "SYCC\n";
        break;
    }

    std::cout << "\nnumOfValues = " << numOfValues << "\n"
              << "w*h = " << image->x1 * image->y1 << "\n";
#endif

    if (image->x0 != 0)
      throw SmartMet::Spine::Exception(BCP,"Expecting JPEG x0 to be zero in grib data");

    if (image->y0 != 0)
      throw SmartMet::Spine::Exception(BCP,"Expecting JPEG y0 to be zero in grib data");

    if (image->numcomps != 1)
      throw SmartMet::Spine::Exception(BCP,"Expecting JPEG numcomps to be one in grib data");

    //if (image->icc_profile_len != 0)
    //  throw SmartMet::Spine::Exception(BCP,"Expecting JPEG not to have a color profile in grib data");

    std::size_t sz = static_cast<std::size_t>(image->x1 * image->y1);
    if (numOfValues != sz  &&  (bitmap == NULL || (bitmapSizeInBytes*8) < sz))
      throw SmartMet::Spine::Exception(BCP,"Expecting " + std::to_string(numOfValues) + " JPEG values, got " +
                               std::to_string(image->x1) + "*" + std::to_string(image->y1) + "=" +
                               std::to_string(image->x1 * image->y1) + " instead");

    // How many bytes does a single value take. Note: by definition nbits>0, so below is correct
    // unsigned int nbytes = (nbits - 1) / 8 + 1;
    // However, in openjpeg v1.5 the output data is int *, hence we do not need to know the number
    // of
    // bytes

    // Calculate actual values from the bytes. Here we assume numcomps=1
    auto comps = image->comps[0];

#ifdef DEBUG
    std::cout << "\nCOMPONENTS:\n"
              << "dx = " << comps.dx << "\n"
              << "dy = " << comps.dy << "\n"
              << "w = " << comps.w << "\n"
              << "h = " << comps.h << "\n"
              << "x0 = " << comps.x0 << "\n"
              << "y0 = " << comps.y0 << "\n"
              << "prec = " << comps.prec << "\n"
              << "bpp = " << comps.bpp << "\n"
              << "sgnd = " << comps.sgnd << "\n"
              << "resno_decoded = " << comps.resno_decoded << "\n"
              << "factor = " << comps.factor << std::endl;
#endif

    if (bitmap != NULL)
    {
      uint pos = 0;
      for (std::uint32_t i = 0; i < numOfValues; i++)
      {
        if (bitmapReader.readBit())
        {
          int X = comps.data[pos];
          double Y = RDfac + X * EDfac;
          values.push_back((T::ParamValue)Y);
          pos++;
        }
        else
        {
          values.push_back(ParamValueMissing);
        }
      }
    }
    else
    {
      for (std::uint32_t i = 0; i < numOfValues; i++)
      {
        int X = comps.data[i];
        double Y = RDfac + X * EDfac;
        values.push_back((T::ParamValue)Y);
      }
    }

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "Jpeg decoder failed!", NULL);
  }
}





void JpegGridDataRepresentationImpl::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    T::Data_ptr bitmap = message->getBitmapDataPtr();
    std::size_t bitmapSizeInBytes = message->getBitmapDataSizeInBytes();

    // The GRIB specs permit using a bitmap, but then suggest that the data should
    // be of height 1 and width equal to the total number of points. Without sample
    // data this will not be supported.

    //if (bitmap != nullptr)
    //  throw SmartMet::Spine::Exception(BCP,"Bitmap + jpeg2000 encoded grib data not supported");

    // Vector to return
    decodedValues.clear();
    decodedValues.reserve(numOfValues);

    if (numOfValues == 0)
      return;

    // Sanity checks
    auto bits_per_value = mPacking.getBitsPerValue();
    if (!bits_per_value)
      throw SmartMet::Spine::Exception(BCP,"GridDataRepresentation number of bits per value must be > 0");

    // Number of bits per value
    const unsigned int nbits = *bits_per_value;

    // Reference value R, IEEE 32-bit floating point value
    // TODO: GRIB1 USES IBM-FLOATS INSTEAD OF IEEE-754!!!!!
    double R = mPacking.getReferenceValue();

    // Binary scale factor E, possibly negative
    std::int16_t E = (mPacking.getBinaryScaleFactor() ? *mPacking.getBinaryScaleFactor() : 0);

    // Decimal scale factor D, possibly negative
    std::int16_t D = (mPacking.getDecimalScaleFactor() ? *mPacking.getDecimalScaleFactor() : 0);

    // Optimization: (R + X * Efac) * Dfac = RDfac + X * EDFac

    const double Efac = std::pow(2.0, E);
    const double Dfac = std::pow(10, -D);

    const double RDfac = R * Dfac;
    const double EDfac = Efac * Dfac;

#ifdef DEBUG
    std::cout << "JPEG decompression:\n"
              << "nbits = " << nbits << "\n"
              << "EDfac = " << EDfac << "\n"
              << "RDfac = " << RDfac << "\n";
#endif


    if (dataSize == 0)
    {
      if (bitmap != NULL  &&  bitmapSizeInBytes > 0)
      {
        // There is no data, but there is a bitmap available.
        BitArrayReader bitmapReader(bitmap,bitmapSizeInBytes*8);
        for (std::uint32_t i=0; i<numOfValues; i++)
        {
          if (bitmapReader.readBit())
          {
            decodedValues.push_back((T::ParamValue)R);
          }
          else
          {
            decodedValues.push_back(ParamValueMissing);
          }
        }
        return;
      }
      else
      {
        // All values are set to "reference_value".
        for (std::uint32_t i=0; i<numOfValues; i++)
        {
          decodedValues.push_back((T::ParamValue)R);
        }
        return;
      }
    }

    // Prepare jpeg decompression event manager

    opj_event_mgr_t event_mgr;
    memset(&event_mgr, 0, sizeof(opj_event_mgr_t));
    event_mgr.error_handler = jpeg_error_callback;
    event_mgr.warning_handler = jpeg_warning_callback;
    event_mgr.info_handler = NULL;

    // set default decoder
    opj_dparameters_t parameters;
    opj_set_default_decoder_parameters(&parameters);

    // Deallocate these in the catch block if necessary
    opj_image_t* image = nullptr;
    opj_cio_t* cio = nullptr;
    opj_dinfo_t* dinfo = nullptr;

    try
    {
      dinfo = opj_create_decompress(CODEC_J2K);

      opj_set_event_mgr((opj_common_ptr)dinfo, &event_mgr, nullptr);
      opj_setup_decoder(dinfo, &parameters);

      // open the jpeg stream
      // TODO: USE REAL SIZE!
      const int datalength = (int)(dataSize & 0xFFFFFFFF); // 999999;
      cio = opj_cio_open((opj_common_ptr)dinfo, const_cast<unsigned char*>(data), datalength);

      // Decode the stream into an image structure
      image = opj_decode(dinfo, cio);

      if (!image)
        throw SmartMet::Spine::Exception(BCP,"Failed to decode JPEG data");

      // Unpack the values

      decode_raw_jpeg_values(decodedValues, image, numOfValues, nbits, bitmap, bitmapSizeInBytes, RDfac, EDfac);

      // close the jpeg stream
      opj_cio_close(cio);
      cio = nullptr;

      // free the codec context
      opj_destroy_decompress(dinfo);
      dinfo = nullptr;

      // free image data structure
      opj_image_destroy(image);
      image = nullptr;
    }
    catch (...)
    {
      if (cio)
        opj_cio_close(cio);
      if (dinfo)
        opj_destroy_decompress(dinfo);
      if (image)
        opj_image_destroy(image);
      throw;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, "JPEG decodeValues failed!", NULL);
  }
}
#endif



}  // namespace GRIB2
}  // namespace SmartMet

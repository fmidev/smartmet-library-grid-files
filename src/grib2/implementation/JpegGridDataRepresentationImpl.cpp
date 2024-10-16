#include "JpegGridDataRepresentationImpl.h"

#include "../../common/BitArrayReader.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include "../Message.h"

#ifdef JASPER
  #include <jasper/jas_image.h>
  #include <jasper/jas_init.h>
#else
#include "openjpeg-2.4/openjpeg.h"
#endif

//#include <openjpeg-1.5/openjpeg.h>
#include <cstring>
#include <iostream>
#include <memory>

namespace SmartMet
{
namespace GRIB2
{
/*! \brief The constructor of the class. */

JpegGridDataRepresentationImpl::JpegGridDataRepresentationImpl()
{
}

/*! \brief The copy constructor of the class. */

JpegGridDataRepresentationImpl::JpegGridDataRepresentationImpl(const JpegGridDataRepresentationImpl &other) :
    JpegGridDataRepresentation(other)
{
}

/*! \brief The destructor of the class. */

JpegGridDataRepresentationImpl::~JpegGridDataRepresentationImpl()
{
}

/*! \brief The method creates a duplicate of the current object. */

RepresentationDefinition* JpegGridDataRepresentationImpl::createRepresentationDefinition() const
{
  try
  {
    return (RepresentationDefinition*) new JpegGridDataRepresentationImpl(*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
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

void JpegGridDataRepresentationImpl::read(MemoryReader &memoryReader)
{
  try
  {
    JpegGridDataRepresentation::read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void JpegGridDataRepresentationImpl::encodeValues(Message *message, T::ParamValue_vec &values)
{
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

#ifdef JASPER




void JpegGridDataRepresentationImpl::decodeValues(Message* message,
                                                  T::ParamValue_vec& decodedValues) const
{
  try
  {
    if (jas_init()) return;

    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    T::Data_ptr bitmap = message->getBitmapDataPtr();
    std::size_t bitmapSizeInBytes = message->getBitmapDataSizeInBytes();

    if (numOfValues == 0 || data == nullptr || dataSize == 0) return;
    /*
        char filename[100];
        sprintf(filename,"/tmp/smartmet-library-grid_jpg2000_decoding_%llu.jpg",getTime());
        FILE *file = fopen(filename,"we");
        fwrite(data,dataSize,1,file);
        fclose(file);
        jas_stream_t *instream = jas_stream_fopen(filename, "rb");
        */

    jas_stream_t* instream = jas_stream_memopen((char*)data, (size_t)dataSize);
    if (instream == nullptr)
    {
      // remove(filename);
      Fmi::Exception exception(BCP, "Cannot open the JPG-2000 file!");
      // exception.addParameter("Filename",filename);
      throw exception;
    }

    int fmtid = jas_image_getfmt(instream);
    if (fmtid < 0)
    {
      jas_stream_close(instream);
      // remove(filename);
      Fmi::Exception exception(BCP, "Not a JPG-2000 image!");
      // exception.addParameter("Filename",filename);
      throw exception;
    }

    /* Decode the image. */

    jas_image_t* image = jas_image_decode(instream, fmtid, 0);

    if (image == nullptr)
    {
      jas_stream_close(instream);
      // remove(filename);
      Fmi::Exception exception(BCP, "Cannot decode the JPG-2000 image!");
      // exception.addParameter("Filename",filename);
      throw exception;
    }

    // int numcmpts = jas_image_numcmpts(image);
    int width = jas_image_cmptwidth(image, 0);
    int height = jas_image_cmptheight(image, 0);
    // int depth = jas_image_cmptprec(image, 0);

    // int sz = width*height;

    // int rawsz = jas_image_rawsize(image);
    // printf("IMAGE %d x %d x %d => %d (%d)\n",width,height,depth,sz,rawsz);

    jas_matrix_t* matrix = jas_matrix_create(height, width);
    jas_image_readcmpt(image, 0, 0, 0, width, height, matrix);

    // Vector to return
    decodedValues.clear();
    decodedValues.reserve(numOfValues);

    // Sanity checks
    auto bits_per_value = mPacking.getBitsPerValue();
    if (!bits_per_value)
      throw Fmi::Exception(
          BCP, "GridDataRepresentation number of bits per value must be > 0");

    // Number of bits per value
    // const unsigned int nbits = *bits_per_value;

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
      if (bmap == nullptr) bmap = &tmp;

      BitArrayReader bitmapReader(bmap, bitmapSizeInBytes * 8);

      uint pos = 0;
      for (int i = 0; i < C_INT(numOfValues); i++)
      {
        if (bitmapReader.readBit())
        {
          int X = matrix->data_[pos];
          double Y = RDfac + X * EDfac;
          decodedValues.emplace_back(Y);
          pos++;
        }
        else
        {
          decodedValues.emplace_back(ParamValueMissing);
        }
      }
    }
    else
    {
      for (int i = 0; i < C_INT(numOfValues); i++)
      {
        int X = matrix->data_[i];
        double Y = RDfac + X * EDfac;
        decodedValues.emplace_back(Y);
      }
    }

    jas_matrix_destroy(matrix);
    jas_image_destroy(image);
    jas_image_clearfmts();
    jas_stream_close(instream);
    // remove(filename);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "JPEG decodeValues failed!", nullptr);
  }
}

#endif

#ifndef JASPER




typedef struct
{
  opj_stream_t *stream;
  OPJ_UINT8 *data;
  OPJ_SIZE_T dataSize;
  OPJ_SIZE_T offset;
} StreamHandle;




static OPJ_SIZE_T readMemoryStream(void *data, OPJ_SIZE_T dataSize, void *handle)
{
  StreamHandle *streamHandle = (StreamHandle*)handle;
  if (streamHandle->offset >= streamHandle->dataSize)
    return (OPJ_SIZE_T)-1;

  OPJ_SIZE_T n = dataSize;

  if ((streamHandle->offset + dataSize) > streamHandle->dataSize)
    n = streamHandle->dataSize - streamHandle->offset;

  memcpy(data, streamHandle->data + streamHandle->offset, n);
  streamHandle->offset += n;
  return n;
}




static OPJ_OFF_T moveMemoryStreamOffset(OPJ_OFF_T bytes, void *handle)
{
  if (bytes < 0)
    return -1;

  StreamHandle *streamHandle = (StreamHandle*)handle;
  OPJ_SIZE_T n = (OPJ_SIZE_T)bytes;

  if ((streamHandle->offset + bytes) > streamHandle->dataSize)
    n = streamHandle->dataSize - streamHandle->offset;

  streamHandle->offset += n;
  return (OPJ_OFF_T)n;
}



static OPJ_BOOL seekMemoryStream(OPJ_OFF_T position, void *handle)
{
  StreamHandle *streamHandle = (StreamHandle*)handle;

  if (position < 0)
    return OPJ_FALSE;

  if (position > (OPJ_OFF_T) streamHandle->dataSize)
    return OPJ_FALSE;

  streamHandle->offset = (OPJ_SIZE_T)position;
  return OPJ_TRUE;
}



static void nopMemoryStream(void *handle)
{
  OPJ_ARG_NOT_USED(handle);
}



static opj_stream_t* createMemoryStream(StreamHandle& streamHandle)
{
  if (!(streamHandle.stream = opj_stream_default_create(true)))
    return (NULL);

  opj_stream_set_read_function(streamHandle.stream, readMemoryStream);
  opj_stream_set_seek_function(streamHandle.stream, seekMemoryStream);
  opj_stream_set_skip_function(streamHandle.stream, moveMemoryStreamOffset);
  opj_stream_set_user_data(streamHandle.stream, &streamHandle, nopMemoryStream);
  opj_stream_set_user_data_length(streamHandle.stream, streamHandle.dataSize);

  return streamHandle.stream;
}



void openjpeg_error_callback(const char *msg, void*)
{
  //std::cerr << "OpenJPEG error: " << msg << std::endl;
  throw Fmi::Exception(BCP, "JPEG Error: " + std::string(msg));
}


void openjpeg_warning_callback(const char *msg, void*)
{
  //std::cerr << "OpenJPEG warning: " << msg << std::endl;
  throw Fmi::Exception(BCP, "JPEG Warning: " + std::string(msg));
}


void openjpeg_info_callback(const char *msg, void*)
{
  //std::cout << "OpenJPEG info: " << msg << std::endl;
}


void JpegGridDataRepresentationImpl::decodeValues(Message *message, T::ParamValue_vec &decodedValues) const
{
  try
  {
    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    T::Data_ptr bitmap = message->getBitmapDataPtr();
    std::size_t bitmapSizeInBytes = message->getBitmapDataSizeInBytes();

    if (numOfValues == 0 || data == nullptr || dataSize == 0)
      return;

    opj_stream_t *stream = nullptr;
    opj_codec_t *codec = nullptr;
    opj_image_t *image = nullptr;

    try
    {
      // ### STREAM INITIALIZATION

      StreamHandle streamHandle;
      streamHandle.data = (OPJ_UINT8*)data;
      streamHandle.dataSize = (OPJ_SIZE_T)dataSize;
      streamHandle.offset = 0;
      streamHandle.stream = nullptr;

      stream =  createMemoryStream(streamHandle);
      if (!stream)
        throw Fmi::Exception(BCP, "Cannot create OpenJPEG stream from memory!");


      // ### CODEC INITIALIZATION

      codec = opj_create_decompress(OPJ_CODEC_J2K);
      if (!codec)
        throw Fmi::Exception(BCP, "Cannot create OpenJPEG codec!");

      opj_set_info_handler(codec, openjpeg_info_callback, nullptr);
      opj_set_warning_handler(codec, openjpeg_warning_callback, nullptr);
      opj_set_error_handler(codec, openjpeg_error_callback, nullptr);


      // ### DECODING JPEG-2000

      opj_dparameters_t l_param;
      memset(&l_param, 0, sizeof(l_param));
      opj_set_default_decoder_parameters(&l_param);
      l_param.decod_format = 0;

      if (!opj_setup_decoder(codec, &l_param))
        throw Fmi::Exception(BCP, "Failed to set up OpenJPEG decoder!");

      if (!opj_read_header(stream, codec, &image))
        throw Fmi::Exception(BCP, "Cannot read JPEG-2000 header!");

      if (!image)
        throw Fmi::Exception(BCP, "Image not created!");

      // printf("IMAGE %u,%u,%u,%u  %u  %d\n",image->x0,image->y0,image->x1,image->y1,image->numcomps,l_param.decod_format);

      if (!image->comps)
        throw Fmi::Exception(BCP, "Image comps points to NULL!");

      // printf("COMPS %u,%u  %u,%u  %u\n",image->comps->w,image->comps->h,image->comps->dx,image->comps->dy,image->comps->prec);

      if (!opj_decode(codec, stream, image))
        throw Fmi::Exception(BCP, "Cannot decode JPEG-2000!");

      if (!opj_end_decompress(codec, stream))
        throw Fmi::Exception(BCP, "Cannot finish JPEG-2000 decompression!");


      // ### PROCESSING DECODED DATA FOR THE GRIB

      // Get data dimensions

      int width = 0;
      int height = 0;

      if (image->comps)
      {
        width = image->comps->w;
        height = image->comps->h;
      }

      // Sanity check for matching value count
      if (width * height != numOfValues)
        throw Fmi::Exception(BCP, "Decoded data size does not match expected value count!");

      // Clear the output vector and reserve space
      decodedValues.clear();
      decodedValues.reserve(numOfValues);

      // Get reference and scale factors
      auto bits_per_value = mPacking.getBitsPerValue();
      if (!bits_per_value)
        throw Fmi::Exception(BCP, "GridDataRepresentation number of bits per value must be > 0");

      double R = mPacking.getReferenceValue();
      std::int16_t E = (mPacking.getBinaryScaleFactor() ? *mPacking.getBinaryScaleFactor() : 0);
      std::int16_t D = (mPacking.getDecimalScaleFactor() ? *mPacking.getDecimalScaleFactor() : 0);

      const double Efac = std::pow(2.0, E);
      const double Dfac = std::pow(10, -D);
      const double RDfac = R * Dfac;
      const double EDfac = Efac * Dfac;

      // Decode and store values based on the presence of a bitmap
      if (bitmapSizeInBytes > 0)
      {
        T::Data_ptr bmap = bitmap;
        unsigned char tmp = 0;
        if (bmap == nullptr)
          bmap = &tmp;

        BitArrayReader bitmapReader(bmap, bitmapSizeInBytes * 8);

        uint pos = 0;
        for (int t = 0; t < static_cast<int>(numOfValues); t++)
        {
          if (bitmapReader.readBit())
          {
            int X = image->comps->data[pos];
            double Y = RDfac + X * EDfac;
            decodedValues.emplace_back(Y);
            pos++;
          }
          else
          {
            decodedValues.emplace_back(ParamValueMissing);
          }
        }
      }
      else
      {
        for (int t = 0; t < static_cast<int>(numOfValues); t++)
        {
          int X = image->comps->data[t];
          double Y = RDfac + X * EDfac;
          decodedValues.emplace_back(Y);
        }
      }

      opj_stream_destroy(stream);
      opj_destroy_codec(codec);
      opj_image_destroy(image);
    }
    catch (...)
    {
      if (stream)
        opj_stream_destroy(stream);

      if (codec)
        opj_destroy_codec(codec);

      if (image)
        opj_image_destroy(image);

      throw;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "JPEG decodeValues failed!", nullptr);
  }
}

#endif

}  // namespace GRIB2
}  // namespace SmartMet

#include "GeneralFunctions.h"
#include "ImageFunctions.h"
#include "ImagePaint.h"
#include "MemoryReader.h"
#include "ShowFunction.h"
#include <macgyver/Exception.h>
#include <gis/OGR.h>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


extern "C"
{
  #include <stdlib.h>
  #include <stdio.h>
  #include <jpeglib.h>
  #include <math.h>
  #include <png.h>
  #include <setjmp.h>
  #include <webp/encode.h>
  #include <webp/mux.h>
};


namespace SmartMet
{


typedef unsigned char uchar;



int compare_coordinates(const void *p1, const void *p2)
{
  const double *v1 = (const double*)p1;
  const double *v2 = (const double*)p2;

  if (*v1 < *v2)
    return -1;

  if (*v1 > *v2)
    return 1;

  return 0;
}





int int_min(int _val1,int _val2)
{
  if (_val1 < _val2)
    return _val1;

  return _val2;
}




uint rgb(uint red, uint green, uint blue)
{
  try
  {
    return (red << 16) + (green << 8) + blue;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint rgb(uchar red, uchar green, uchar blue)
{
  try
  {
    return rgb(C_UINT(red),C_UINT(green),C_UINT(blue));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




uint cmyk2rgb(double _c, double _m, double _y, double _k)
{
  double r = (255.0 - _c*255) * (1.0 - _k);
  double g = (255.0 - _m*255) * (1.0 - _k);
  double b = (255.0 - _y*255) * (1.0 - _k);

  return rgb(C_UINT(r),C_UINT(g),C_UINT(b));
}




uint hsv_to_rgb(unsigned char hue, unsigned char saturation, unsigned char value)
{
  try
  {
    if (saturation == 0)
    {
      /* color is grayscale */
      return rgb(value,value,value);
    }

    /* make hue 0-5 */
    uint region = hue / 43;
    /* find remainder part, make it from 0-255 */
    uint fpart = (hue - (region * 43)) * 6;

    /* calculate temp vars, doing integer multiplication */
    uint p = (value * (255 - saturation)) >> 8;
    uint q = (value * (255 - ((saturation * fpart) >> 8))) >> 8;
    uint t = (value * (255 - ((saturation * (255 - fpart)) >> 8))) >> 8;

    uint val = C_UINT(value);

    /* assign temp vars based on color cone region */
    switch(region)
    {
      case 0:
        return rgb(val,t,p);
      case 1:
        return rgb(q,val,p);
      case 2:
        return rgb(p,val,t);
      case 3:
        return rgb(p,q,val);
      case 4:
        return rgb(t,p,val);
      default:
        return rgb(val,p,q);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



// ********************************************* JPEG *********************************************************


void jpeg_save(const char *filename, uint *image, int image_height,int image_width, int quality)
{
  try
  {
    int size = image_width * image_height;
    unsigned char *image_buffer = new unsigned char[size*3];
    uint c = 0;
    uint p = 0;

    for (int y=0; y<image_height; y++)
    {
      for (int x=0; x<image_width; x++)
      {
        uint col = image[c];
        image_buffer[p++] = C_UCHAR((col & 0xFF0000) >> 16);
        image_buffer[p++] = C_UCHAR((col & 0x00FF00) >> 8);
        image_buffer[p++] = C_UCHAR(col & 0xFF);
        c++;
      }
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE * outfile = nullptr;
    JSAMPROW row_pointer[1];
    int row_stride = 0;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    if ((outfile = fopen(filename, "wbe")) == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot create the JPG file!");
      exception.addParameter("Filename",filename);
      throw exception;
    }

    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = image_width;
    cinfo.image_height = image_height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);

    jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);
    jpeg_start_compress(&cinfo, TRUE);
    row_stride = image_width * 3; /* JSAMPLEs per row in image_buffer */

    while (cinfo.next_scanline < cinfo.image_height)
    {
      row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
      (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);

    jpeg_destroy_compress(&cinfo);
    delete[] image_buffer;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






// ### Here's the extended error handler struct:

struct my_error_mgr
{
  struct jpeg_error_mgr pub;  // ### "public" fields
  jmp_buf setjmp_buffer;      // ### for return to caller
};

typedef struct my_error_mgr* my_error_ptr;




// ### Here's the routine that will replace the standard error_exit method:



METHODDEF(void) my_error_exit (j_common_ptr cinfo)
{
  // ### cinfo->err really points to a my_error_mgr struct, so coerce pointer

  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  // ### Always display the message.
  // ### We could postpone this until after returning, if we chose.

  (*cinfo->err->output_message) (cinfo);

  // ### Return control to the setjmp point

  longjmp(myerr->setjmp_buffer, 1);
}





int jpg_load(const char *_filename,CImage& _image)
{
  try
  {
    if (getFileSize(_filename) <= 0)
    {
      Fmi::Exception exception(BCP,"File is empty or missing!");
      exception.addParameter("Filename",_filename);
      throw exception;
    }
    // ### This struct contains the JPEG decompression parameters and pointers to
    // ### working space (which is allocated as needed by the JPEG library).

    struct jpeg_decompress_struct cinfo;

    // ### We use our private extension JPEG error handler.
    // ### Note that this struct must live as long as the main JPEG parameter
    // ### struct, to avoid dangling-pointer problems.

    struct my_error_mgr jerr;

    JSAMPARRAY buffer;  // ### Output row buffer
    int row_stride;     // ###  physical row width in output buffer

    FILE *infile = fopen(_filename, "rbe");
    if (infile == nullptr)
    {
  //    fprintf(moutput, "ERROR; Cannot open file (%s)!\n", _filename);
      return - 1;
    }


    // ### Step 1: allocate and initialize JPEG decompression object

    // ### We set up the normal JPEG error routines, then override error_exit.

    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;

    // ### Establish the setjmp return context for my_error_exit to use.

    if (setjmp(jerr.setjmp_buffer))
    {
      // ### If we get here, the JPEG code has signaled an error.
      // ### We need to clean up the JPEG object, close the input file, and return.

      jpeg_destroy_decompress(&cinfo);
      fclose(infile);
      return - 2;
    }

    // ### Now we can initialize the JPEG decompression object.

    jpeg_create_decompress(&cinfo);


    // ### Step 2: specify data source (eg, a file)

    jpeg_stdio_src(&cinfo, infile);


    // ### Step 3: read file parameters with jpeg_read_header()

    jpeg_read_header(&cinfo, TRUE);

    //printf("DataPrecision %d\n",cinfo.data_precision);
    //printf("ColorComponents %d\n",cinfo.num_components);
    //printf("ColorSpace %d\n",cinfo.jpeg_color_space);


    // ### Step 4: set parameters for decompression

    // ### We don't need to change any of the defaults set by jpeg_read_header(), so we do nothing here.


    // ### Step 5: Start decompressor

    jpeg_start_decompress(&cinfo);


    // ### We may need to do some setup of our own at this point before reading
    // ### the data.  After jpeg_start_decompress() we have the correct scaled
    // ### output image dimensions available, as well as the output colormap
    // ### if we asked for color quantization.
    // ### In this example, we need to make an output work buffer of the right size.

    // ### JSAMPLEs per row in output buffer:

    row_stride = cinfo.output_width * cinfo.output_components;

    // ### Make a one-row-high sample array that will go away when done with image:

    buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);


    // ### Step 6: while (scan lines remain to be read) jpeg_read_scanlines(...);

    // ###  Here we use the library's state variable cinfo.output_scanline as the
    // ### loop counter, so that we don't have to keep track ourselves.

  //  setSize(cinfo.output_width,cinfo.output_height);

    _image.width = cinfo.output_width;
    _image.height = cinfo.output_height;
    _image.pixel = new uint[_image.width * _image.height];

    int y = 0;

    //printf("MCOLORSPACE : %d\n",cinfo.jpeg_color_space);

    while (cinfo.output_scanline < cinfo.output_height)
    {
      // ### jpeg_read_scanlines expects an array of pointers to scanlines.
      // ### Here the array is only one element long, but you could ask for
      // ### more than one scanline at a time if that's more convenient.

      jpeg_read_scanlines(&cinfo, buffer, 1);

      // ### Assume put_scanline_someplace wants a pointer and sample count.

      int p = 0;
      uchar *data = (uchar*)buffer[0];
      for (uint x=0; x<cinfo.output_width; x++)
      {
        uchar cc[10] = {0};
        uint color = 0;
        for (int a=0; a < cinfo.output_components; a++)
        {
          cc[a] = data[p];
          //color = color << 8;
          //color = color + data[p];
          p++;
        }

        //if (cinfo.jpeg_color_space == JCS_RGB /* &&  cinfo.num_components == 3*/)
        {
          color = rgb(cc[0],cc[1],cc[2]);
        }

        if (cinfo.jpeg_color_space == JCS_GRAYSCALE  &&  cinfo.num_components == 1)
        {
          /*
          double h = 0.0, s = 0.0, v = 0.0;
          color_rgb2hsv(color,h,s,v);
          */
          color = rgb(cc[0],cc[0],cc[0]);
        }

        if (cinfo.jpeg_color_space == JCS_CMYK  &&  cinfo.num_components == 4)
        {
          color = cmyk2rgb(C_DOUBLE(cc[0])/255,C_DOUBLE(cc[1])/255,C_DOUBLE(cc[2])/255,C_DOUBLE(cc[3])/255);
        }

        if (cinfo.jpeg_color_space == JCS_YCCK  &&  cinfo.num_components == 4)
        {

          uchar r = 255 - int_min(255, cc[0] + cc[3]);
          uchar g = 255 - int_min(255, cc[1] + cc[3]);
          uchar b = 255 - int_min(255, cc[2] + cc[3]);

  /*
          double R = (double)cc[0] + 1.402*(double)cc[2] - 179.456;
          double G = (double)cc[0] - 0.34414*(double)cc[1] - 0.71414*(double)cc[2] + 135.45984;
          double B = (double)cc[0] + 1.772*(double)cc[1] - 226.816;

          double C = 255 - (int)R;
          double M = 255 - (int)G;
          double Y = 255 - (int)B;

          color = color_cmyk2rgb(C/255,M/255,Y/255,(double)cc[3]/255);
          printf("CMYK %f %f % %f %f => %06x\n",C/255,M/255,Y/255,cc[3]/255,color);

          //color = color_rgb((uchar)(255-cc[0]),(uchar)(255-cc[1]),(uchar)(255-cc[2]));
           */

          color = rgb(r,g,b);
        }

        _image.pixel[y*_image.width + x] = color;
      }
      y++;
    }

    // ### Step 7: Finish decompression */

    (void) jpeg_finish_decompress(&cinfo);


    // ### Step 8: Release JPEG decompression object

    // ### This is an important step since it will release a good deal of memory.

    jpeg_destroy_decompress(&cinfo);

    // ### After finish_decompress, we can close the input file.


    fclose(infile);

    // ### At this point you may want to check to see whether any corrupt-data
    // ### warnings occurred (test whether jerr.pub.num_warnings is nonzero).

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






// ********************************************* PNG **********************************************************



static png_structp png_ptr = nullptr;
static png_infop info_ptr = nullptr;

png_uint_32 width = 0, height = 0;
int bit_depth = 0, color_type = 0;
uchar *image_data = nullptr;




void readpng_version_info(void)
{
//  fprintf(moutput,"Compiled with libpng %s; using libpng %s.\n",PNG_LIBPNG_VER_STRING, png_libpng_ver);
//  fprintf(moutput,"Compiled with zlib %s; using zlib %s.\n",ZLIB_VERSION, zlib_version);
}






int readpng_init(FILE *infile, uint *pWidth, uint *pHeight)
{
  uchar sig[8];

  if (fread(sig, 1, 8, infile) != 8 || !png_check_sig(sig, 8))
    return -1;   /* bad signature */


  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (!png_ptr)
    return -2;   /* out of memory */

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
    png_destroy_read_struct(&png_ptr, nullptr, nullptr);
    return -3;   /* out of memory */
  }

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return -4;
  }


  png_init_io(png_ptr, infile);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,nullptr, nullptr, nullptr);

  *pWidth = width;
  *pHeight = height;

  return 0;
}





int readpng_get_bgcolor(uchar *red, uchar *green, uchar *blue)
{
  png_color_16p pBackground;

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 2;
  }


  if (!png_get_valid(png_ptr, info_ptr, PNG_INFO_bKGD))
    return 1;

  png_get_bKGD(png_ptr, info_ptr, &pBackground);

  if (bit_depth == 16)
  {
    *red   = pBackground->red   >> 8;
    *green = pBackground->green >> 8;
    *blue  = pBackground->blue  >> 8;
  }
  else
  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
  {
    if (bit_depth == 1)
      *red = *green = *blue = pBackground->gray? 255 : 0;
    else
    if (bit_depth == 2)
      *red = *green = *blue = (255/3) * pBackground->gray;
    else /* bit_depth == 4 */
      *red = *green = *blue = (255/15) * pBackground->gray;
  }
  else
  {
    *red   = C_UCHAR(pBackground->red);
    *green = C_UCHAR(pBackground->green);
    *blue  = C_UCHAR(pBackground->blue);
  }
  return 0;
}






uchar *readpng_get_image(double display_exponent, int *pChannels, uint *pRowbytes)
{
  double gamma;
  png_uint_32 i, rowbytes;


  if (setjmp(png_jmpbuf(png_ptr)))
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return nullptr;
  }

  if (color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_expand(png_ptr);

  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand(png_ptr);

  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    png_set_expand(png_ptr);

  if (bit_depth == 16)
    png_set_strip_16(png_ptr);

  if (color_type == PNG_COLOR_TYPE_GRAY  ||  color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png_ptr);

  if (png_get_gAMA(png_ptr, info_ptr, &gamma))
    png_set_gamma(png_ptr, display_exponent, gamma);


  png_read_update_info(png_ptr,info_ptr);

  *pRowbytes = rowbytes = png_get_rowbytes(png_ptr, info_ptr);
  *pChannels = C_INT(png_get_channels(png_ptr, info_ptr));

  if ((image_data = (uchar *)malloc(rowbytes*height)) == nullptr)
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return nullptr;
  }

  png_bytepp row_pointers = (png_bytepp)malloc(height*sizeof(png_bytep));
  if (row_pointers == nullptr)
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    free(image_data);
    image_data = nullptr;
    return nullptr;
  }

  for (i = 0;  i < height;  ++i)
    row_pointers[i] = image_data + i*rowbytes;


  png_read_image(png_ptr, row_pointers);

  free(row_pointers);
  row_pointers = nullptr;

  png_read_end(png_ptr, nullptr);

  return image_data;
}





void readpng_cleanup(int free_image_data)
{
  if (free_image_data && image_data)
  {
    free(image_data);
    image_data = nullptr;
  }

  if (png_ptr && info_ptr)
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    png_ptr = nullptr;
    info_ptr = nullptr;
  }
}





int png_load(const char *_filename,CImage& _image)
{
  try
  {
    if (getFileSize(_filename) <= 0)
    {
      Fmi::Exception exception(BCP,"File is empty or missing!");
      exception.addParameter("Filename",_filename);
      throw exception;
    }

    double LUT_exponent = 1.0;
    double CRT_exponent = 2.2;
    double display_exponent = LUT_exponent * CRT_exponent;
    int image_channels = 0;
    uint image_rowbytes = 0;

    uint width = 0;
    uint height = 0;


    FILE *infile = fopen(_filename, "rbe");
    if (infile == nullptr)
      return -1;

    if (readpng_init(infile, &width, &height) != 0)
      return -2;

    _image.width = width;
    _image.height = height;

    uchar *pixel = readpng_get_image(display_exponent, &image_channels,&image_rowbytes);
    if (pixel == nullptr)
      return -3;

    int size = width * height;
    _image.pixel = (uint*)pixel;

    _image.pixel = new uint[size];

    int p1 = 0;
    int p2 = 0;

    uchar *ptr = (uchar*)_image.pixel;

    for (int t=0; t<size; t++)
    {
      ptr[p2+0] = pixel[p1+2];
      ptr[p2+1] = pixel[p1+1];
      ptr[p2+2] = pixel[p1+0];

      if (image_channels == 4)
      {
        ptr[p2+3] = pixel[p1+3];
        /*
        if (pixel[p1+3] == 0)
        {
          ptr[p2+3] = 0x01;
        }
        else
          ptr[p2+3] = 0;
          */
      }

      p1 = p1 + image_channels;
      p2 = p2 + 4;
    }

    free(pixel);

    readpng_cleanup(0);
    fclose(infile);

    if (!_image.pixel)
      return -4;

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




struct CImageHandle_png
{
  png_structp   png_ptr;
  png_infop     info_ptr;
  FILE          *file;
};



/* local prototype */

static void writepng_error_handler(png_structp png_ptr, png_const_charp msg);



void writepng_version_info(void)
{
}



void* png_writeOpen(const char *_filename,int image_width,int image_height)
{
  CImageHandle_png *handle = new CImageHandle_png;

  handle->file = fopen(_filename,"wb");
  if (handle->file == nullptr)
  {
    delete handle;
    return nullptr;
  }

  handle->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr,writepng_error_handler, nullptr);
  if (!handle->png_ptr)
  {
    delete handle;
    return nullptr;   // out of memory
  }

  handle->info_ptr = png_create_info_struct(handle->png_ptr);
  if (!handle->info_ptr)
  {
    png_destroy_write_struct(&handle->png_ptr, nullptr);
    return nullptr;   // out of memory
  }

  png_init_io(handle->png_ptr,handle->file);
  png_set_compression_level(handle->png_ptr, 9 /*Z_BEST_COMPRESSION*/);
  png_set_IHDR(handle->png_ptr,handle->info_ptr,image_width,image_height,8,PNG_COLOR_TYPE_RGBA,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  png_write_info(handle->png_ptr, handle->info_ptr);
  png_set_packing(handle->png_ptr);

  return handle;
}





int png_writeImageRow(void *_handle,uchar *_row)
{
  CImageHandle_png *handle = (CImageHandle_png*)_handle;
  png_write_row(handle->png_ptr,_row);
  return 0;
}





int png_writeClose(void *_handle)
{
  CImageHandle_png *handle = (CImageHandle_png*)_handle;
  png_write_end(handle->png_ptr, nullptr);

  fclose(handle->file);
  delete handle;

  return 0;
}





static void writepng_error_handler(png_structp png_ptr, png_const_charp msg)
{
  exit(-1);
}





int png_save(const char *filename,uint *image,int image_width,int image_height)
{
  void *handle = png_writeOpen(filename,image_width,image_height);
  if (handle == nullptr)
  {
    return -1;
  }

  int psize = sizeof(uint);

  int len = image_width * psize;

  uchar *pixel = new uchar[len];

  uchar *ptr = (uchar*)image;

  for (int y=0; y<image_height; y++)
  {
    int p1 = 0;
    int p2 = 0;

    for (int x=0; x<image_width; x++)
    {
      pixel[p1+3] = ptr[p2+3];
      /*
      if (ptr[p2+3] != 0)
        pixel[p1+3] = 0;
      else
        pixel[p1+3] = 0xFF;
*/
      pixel[p1+2] = ptr[p2+0];
      pixel[p1+1] = ptr[p2+1];
      pixel[p1+0] = ptr[p2+2];

      p1 = p1 + 4;
      p2 = p2 + psize;
    }
    png_writeImageRow(handle,pixel);

    ptr = (uchar*)image + y * image_width * psize;
  }

  delete[] pixel;

  png_writeClose(handle);

  return 0;
}




int webp_anim_save(const char *filename,uint **image,int image_width,int image_height,int numberOfImages,int timeStepMsec)
{
  try
  {
    WebPAnimEncoderOptions enc_options;
    WebPAnimEncoderOptionsInit(&enc_options);
    WebPAnimEncoder* enc = WebPAnimEncoderNew(image_width, image_height, &enc_options);

    int dt = timeStepMsec;
    int ts = dt;
    uint sz = image_width * image_height;
    uint *newImage = new uint[sz];

    for (int t=0; t<numberOfImages; t++)
    {
      WebPConfig config;
      WebPConfigInit(&config);
      WebPPicture frame;

      WebPPictureInitInternal(&frame, WEBP_ENCODER_ABI_VERSION);
      frame.width = image_width;
      frame.height= image_height;

      // Converting RGB colors to WEBP colors

      uint *img = image[t];
      for (uint i = 0; i < sz; i++)
      {
        uint col = img[i];
        if (col & 0xFF000000)
          newImage[i] = 0; // Transparent
        else
          newImage[i] = 0xFF000000 + ((col & 0xFF0000) >> 16) + (col & 0x00FF00) + ((col & 0xFF) << 16);
      }

      WebPPictureImportRGBA(&frame,(uint8_t*)newImage,image_width*4);
      WebPAnimEncoderAdd(enc,&frame,ts, &config);
      ts = ts + dt;
    }
    delete [] newImage;

    WebPData out;
    out.size = 0;
    out.bytes = nullptr;
    WebPAnimEncoderAssemble(enc,&out);
    WebPAnimEncoderDelete(enc);

    if (out.size &&  out.bytes)
    {
      FILE *file = fopen(filename,"w");
      if (!file)
      {
        Fmi::Exception exception (BCP,"Cannot create a file!",nullptr);
        exception.addParameter("Filename",filename);
      }
      fwrite(out.bytes,1,out.size,file);
      fclose(file);
    }
    return 0;
  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void mergePngFiles(const char *newFile,std::vector<std::string>& fileList)
{
  try
  {
    uint size = fileList.size();

    if (size == 0)
    {
      Fmi::Exception exception(BCP,"No files defined!");
      throw exception;
    }

    CImage image;
    if (png_load(fileList[0].c_str(),image) != 0)
    {
      Fmi::Exception exception(BCP,"PNG load failed!");
      exception.addParameter("Filename",fileList[0]);
      throw exception;
    }

    int sz = image.width * image.height;

    for (uint t = 1; t < size; t++)
    {
      CImage img;
      if (png_load(fileList[t].c_str(),img) != 0  ||  img.width != image.width ||  img.height != image.height)
      {
        Fmi::Exception exception(BCP,"PNG load failed!");
        exception.addParameter("Filename",fileList[t]);
        throw exception;
      }

      if (img.width != image.width ||  img.height != image.height)
      {
        Fmi::Exception exception(BCP,"Image sizes are not equal!");
        exception.addParameter("Filename",fileList[t]);
        throw exception;
      }

      for (int a=0; a<sz; a++)
      {
        unsigned long col = img.pixel[a];
        if ((col & 0xFF000000) == 0)
          image.pixel[a] = col;
      }
    }

    // The function writes an image data to the PNG file.

    png_save(newFile,image.pixel,image.width,image.height);
  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void saveGeometryAsJpeg(const char *_filename,int width,int height,uint backgroundColor,uint drawColor,uint fillColor,const OGRGeometry *geom,bool autoscale)
{
  try
  {
    unsigned char* out = new unsigned char[geom->WkbSize()+10];
    geom->exportToWkb(wkbNDR,out,wkbVariantOldOgc);

    //std::string st = Fmi::OGR::exportToWkt(*geom);
    ImagePaint imagePaint(width, height,backgroundColor,drawColor,fillColor,false,true);

    double dx = 0;
    double dy = 0;

    double ww = width;
    double hh = height;

    double ss = 1;

    if (autoscale)
    {
      double minX = 0, minY = 0, maxX = 0, maxY = 0;
      imagePaint.countPaintWkbArea(out,geom->WkbSize(),minX,minY,maxX,maxY);

      dx = -minX;
      dy = -minY;

      ww = maxX - minX;
      hh = maxY - minY;

      double sx = (width-20)/ww;
      double sy = (height-20)/hh;

      ss = sx;
      if (sy < sx)
        ss = sy;
    }

    imagePaint.paintWkb(ss, ss, dx+10/ss, dy+10/ss,out,geom->WkbSize());

    CPLFree(out);
    imagePaint.saveJpgImage(_filename);
  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void saveGeometryAsJpeg(const char *_filename,int width,int height,uint backgroundColor,uint drawColor,uint fillColor,std::vector<std::shared_ptr<OGRGeometry>> geomVec,bool autoscale)
{
  try
  {
    double ww = width;
    double hh = height;
    double dx = 0;
    double dy = 0;
    double ss = 1;

    ImagePaint imagePaint(width, height,backgroundColor,drawColor,fillColor,false,true);

    double tminX = 0, tminY = 0, tmaxX = 0, tmaxY = 0;
    if (autoscale)
    {
      tminX = 1000000000;
      tminY = 1000000000;
      tmaxX = -1000000000;
      tmaxY = -1000000000;

      for (auto g = geomVec.begin();g != geomVec.end(); ++g)
      {
        auto gg = g->get();
        unsigned char* out = new unsigned char[gg->WkbSize()+10];
        gg->exportToWkb(wkbNDR,out,wkbVariantOldOgc);

      //std::string st = Fmi::OGR::exportToWkt(*g);

        double minX = 0, minY = 0, maxX = 0, maxY = 0;
        imagePaint.countPaintWkbArea(out,gg->WkbSize(),minX,minY,maxX,maxY);
        CPLFree(out);

        printf("PAINT %f %f %f %f\n",minX,minY,maxX,maxY);

        if (minX < tminX)
          tminX = minX;

        if (minY < tminY)
          tminY = minY;

        if (maxX > tmaxX)
          tmaxX = maxX;

        if (maxY > tmaxY)
          tmaxY = maxY;
      }
    }

    printf("*** PAINT %f %f %f %f\n",tminX,tminY,tmaxX,tmaxY);

    if (autoscale)
    {
      dx = -tminX;
      dy = -tminY;

      ww = tmaxX - tminX;
      hh = tmaxY - tminY;
    }

    double sx = (width-20)/ww;
    double sy = (height-20)/hh;

    ss = sx;
    if (sy < sx)
      ss = sy;

    for (auto g = geomVec.begin();g != geomVec.end(); ++g)
    {
      auto gg = g->get();
      unsigned char* out = new unsigned char[gg->WkbSize()+10];
      gg->exportToWkb(wkbNDR,out,wkbVariantOldOgc);
      imagePaint.paintWkb(ss, ss, dx+10/ss, dy+10/ss,out,gg->WkbSize());
      CPLFree(out);
    }

    imagePaint.saveJpgImage(_filename);
  }
  catch (Fmi::Exception& e)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}

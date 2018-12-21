#include "ImageFunctions.h"
#include "Exception.h"
#include "MemoryReader.h"
#include "ShowFunction.h"


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


extern "C"
{
  #include <stdlib.h>
  #include <stdio.h>
  #include <jpeglib.h>
  #include <math.h>
  #include <png.h>
  #include <setjmp.h>
};


namespace SmartMet
{


typedef unsigned char uchar;



extern void paintWkb(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,MemoryReader& _memoryReader,uint _color);



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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
      SmartMet::Spine::Exception exception(BCP,"Cannot create the JPG file!");
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
      if (pixel[p1+3] == 0)
      {
        ptr[p2+3] = 0x01;
      }
      else
        ptr[p2+3] = 0;
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
    return nullptr;   // out of memory

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
      if (ptr[p2+3] != 0)
        pixel[p1+3] = 0;
      else
        pixel[p1+3] = 0xFF;

      pixel[p1+2] = ptr[p2+0];
      pixel[p1+1] = ptr[p2+1];
      pixel[p1+0] = ptr[p2+2];

      p1 = p1 + 4;
      p2 = p2 + psize;
    }
    png_writeImageRow(handle,pixel);

    ptr = (uchar*)image + y * image_width * psize;
  }

  delete pixel;

  png_writeClose(handle);

  return 0;
}








#if 0
void paintPixel(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,int _x,int _y,uint _color)
{
  try
  {
    if (_x >= 0  &&  _x < _width  &&  _y >=0  &&  _y < _height)
    {
      if (_rotatedY)
        _y = _height-_y-1;

      if (_rotatedX)
        _x = _width-_x-1;

     _image[_y*_width + _x] = _color;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintLine(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,int _x1,int _y1,int _x2,int _y2,uint _color)
{
  FUNCTION_TRACE
  try
  {
    if (_x1 == -2147483648 || _y1 == -2147483648 || _x2 == -2147483648 || _y2 == -2147483648)
      return;

    int x1 = (int)_x1;
    int y1 = (int)_y1;
    int x2 = (int)_x2;
    int y2 = (int)_y2;

    //printf("Line %d,%d - %d,%d\n",x1,y1,x2,y2);

    int dy = (y2 - y1);
    int dx = (x2 - x1);
    int stepx = 1;
    int stepy = 1;

    if (dy < 0)
    {
      dy = -dy;
      stepy = -1;
    }

    if (dx < 0)
    {
      dx = -dx;
      stepx = -1;
    }

    dy <<= 1;
    dx <<= 1;


    paintPixel(_image,_width,_height,_rotatedX,_rotatedY,x1,y1,_color);

    if (dx > dy)
    {
      int fraction = dy - (dx >> 1);
      while (x1 != x2)
      {
        if (fraction >= 0)
        {
          y1 += stepy;
          fraction -= dx;
        }
        x1 += stepx;
        fraction += dy;
        paintPixel(_image,_width,_height,_rotatedX,_rotatedY,x1,y1,_color);
      }
    }
    else
    {
      int fraction = dx - (dy >> 1);
      while (y1 != y2)
      {
        if (fraction >= 0)
        {
          x1 += stepx;
          fraction -= dy;
        }
        y1 += stepy;
        fraction += dx;
        paintPixel(_image,_width,_height,_rotatedX,_rotatedY,x1,y1,_color);
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintSvgPath(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,NFmiSvgPath& _svgPath,uint _color)
{
  try
  {
    double x1 = 0;
    double y1 = 0;
    double x2 = 0;
    double y2 = 0;
    double xx = 0;
    double yy = 0;

    for (auto it=_svgPath.begin(); it!=_svgPath.end(); ++it)
    {
      switch (it->itsType)
      {
        case NFmiSvgPath::kElementMoveto:
          x1 = it->itsX + _dx;
          y1 = it->itsY + _dy;
          xx = x1;
          yy = y1;
          break;

        case NFmiSvgPath::kElementClosePath:
          paintLine(_image,_width,_height,_rotatedX,_rotatedY,x1,y1,xx,yy,_color);
          x1 = xx;
          y1 = yy;
          break;

        case NFmiSvgPath::kElementLineto:
          x2 = it->itsX + _dx;
          y2 = it->itsY + _dy;
          paintLine(_image,_width,_height,_rotatedX,_rotatedY,x1,y1,x2,y2,_color);
          x1 = x2;
          y1 = y2;
          break;

        case NFmiSvgPath::kElementNotValid:
          return;
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintPolygon(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,std::vector<T::Coordinate>& polygonPoints,uint _color)
{
  try
  {
    std::set<uint long> cList;
    uint numOfPoints = polygonPoints.size();
    if (numOfPoints == 0)
      return;

    // It the last polygon point is not same than the first point, then we should add it to the list.

    if (polygonPoints[0].x() != polygonPoints[numOfPoints-1].x()  ||  polygonPoints[0].y() != polygonPoints[numOfPoints-1].y())
    {
      polygonPoints.push_back(polygonPoints[0]);
      numOfPoints++;
    }


    // Painting points that are below the polygon line.

    for (uint t=1; t<numOfPoints; t++)
    {
      paintLine(_image,_width,_height,_rotatedX,_rotatedY,polygonPoints[t-1].x(),polygonPoints[t-1].y(),polygonPoints[t].x(),polygonPoints[t].y(),_color);
    }

    // Painting points that are inside the polygon line.

    int maxY = 0;
    int minY = _height-1;
    int minX = 0;
    int maxX = _width-1;

    for (auto it = polygonPoints.begin(); it != polygonPoints.end(); ++it)
    {
      double yp = round(it->y());

      if (yp < minY)
        minY = yp;

      if (yp > maxY)
        maxY = yp;
    }

    if (minY < 0)
      minY = 0;

    if (maxY >= _height)
      maxY = _height - 1;

    double nodeX[10000] = {0};

    for (int y = minY; y <= maxY; y++)
    {
      int nodes = 0;
      int cnt = numOfPoints;
      int j = cnt - 1;
      for (int i = 0; i<cnt; i++)
      {
        double xi = polygonPoints[i].x();
        double yi = polygonPoints[i].y();

        double xj = polygonPoints[j].x();
        double yj = polygonPoints[j].y();

        double dy = C_DOUBLE(y);

        if ((yi < dy  &&  yj >= dy)  ||  (yj < dy &&  yi >= dy))
        {
          double xx = C_DOUBLE(xi + (y - yi)/(yj - yi)*(xj - xi));
          nodeX[nodes++] = C_DOUBLE(xx);
        }
        j = i;
      }

      qsort(&nodeX, nodes, sizeof(double),compare_coordinates);

      for (int i=0; i<nodes; i+=2)
      {
        if (nodeX[i] >= maxX  ||  (i+1) > nodes)
          break;

        if (nodeX[i+1] > minX)
        {
          if (nodeX[i] < minX)
            nodeX[i] = minX;

          if (nodeX[i+1] > maxX)
            nodeX[i+1] = maxX;

          //printf("Line %f,%d - %f,%d\n",nodeX[i],y,nodeX[i+1],y);
          int xStart = C_INT(nodeX[i]);
          int xEnd = C_INT(nodeX[i+1]);

          if ((nodeX[i] - xStart) > 0)
            xStart++;

          if ((xEnd - nodeX[i+1]) > 0)
            xEnd--;

          for (int x=xStart; x<=xEnd; x++)
          {
            paintPixel(_image,_width,_height,_rotatedX,_rotatedY,x,y,_color);
          }
        }
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






void paintPolygonPath(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,std::vector<std::vector<T::Coordinate>>& polygonPath,uint _color)
{
  try
  {
    if (polygonPath.size() == 0)
      return;

    std::set<uint long> cList;

    int minY = _height-1;
    int maxY = 0;
    int minX = 0;
    int maxX = _width-1;
    double nodeX[10000] = {0};
    double pointsX[200000];
    double pointsY[200000];

    for (auto polygonPoints = polygonPath.begin(); polygonPoints != polygonPath.end(); ++polygonPoints)
    {
      uint numOfPoints = polygonPoints->size();

      if (numOfPoints > 0)
      {
        // It the last polygon point is not same than the first point, then we should add it to the list.

        if ((*polygonPoints)[0].x() != (*polygonPoints)[numOfPoints-1].x()  ||  (*polygonPoints)[0].y() != (*polygonPoints)[numOfPoints-1].y())
        {
          (*polygonPoints).push_back((*polygonPoints)[0]);
          numOfPoints++;
        }

        // Adding points that are below the polygon line.

        for (uint t=1; t<numOfPoints; t++)
        {
          paintLine(_image,_width,_height,_rotatedX,_rotatedY,(*polygonPoints)[t-1].x(),(*polygonPoints)[t-1].y(),(*polygonPoints)[t].x(),(*polygonPoints)[t].y(),_color);
        }

        // Adding points that are inside the polygon line.

        for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
        {
          double yp = round(it->y());

          if (yp < minY)
            minY = yp;

          if (yp > maxY)
            maxY = yp;
        }
      }
    }

    if (minY < 0)
      minY = 0;

    if (maxY >= _height)
      maxY = _height - 1;


    //  Loop through the rows of the image.
    for (int y = minY; y <= maxY; y++)
    {
      //  Build a list of nodes.
      int nodes = 0;
      for (auto polygonPoints = polygonPath.begin(); polygonPoints != polygonPath.end(); ++polygonPoints)
      {
        uint numOfPoints = polygonPoints->size();

        uint c = 0;
        for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
        {
          pointsX[c] = it->x();
          pointsY[c] = it->y();
          c++;

          if (c >= 200000)
          {
            throw SmartMet::Spine::Exception(BCP,"Not enough space for the point list!",nullptr);
          }
        }

        int cnt = numOfPoints;
        int j = cnt - 1;
        for (int i = 0; i<cnt; i++)
        {
          double xi = pointsX[i];
          double yi = pointsY[i];

          double xj = pointsX[j];
          double yj = pointsY[j];

          double dy = C_DOUBLE(y);

          if ((yi < dy  &&  yj >= dy)  ||  (yj < dy &&  yi >= dy))
          {
            double xx = C_DOUBLE(xi + (y - yi)/(yj - yi)*(xj - xi));
            nodeX[nodes++] = C_DOUBLE(xx);
          }
          j = i;
        }
      }
      //printf("Nodes %d %u\n",y,nodes);
      qsort(&nodeX, nodes, sizeof(double),compare_coordinates);

      //  Fill the pixels between node pairs.

      for (int i=0; i<nodes; i+=2)
      {
        if (nodeX[i] >= maxX  ||  (i+1) > nodes)
          break;

        if (nodeX[i+1] > minX)
        {
          if (nodeX[i] < minX)
            nodeX[i] = minX;

          if (nodeX[i+1] > maxX)
            nodeX[i+1] = maxX;

          //printf("Line %f,%d - %f,%d\n",nodeX[i],y,nodeX[i+1],y);
          int xStart = C_INT(nodeX[i]);
          int xEnd = C_INT(nodeX[i+1]);

          if ((nodeX[i] - xStart) > 0)
            xStart++;

          if ((xEnd - nodeX[i+1]) > 0)
            xEnd--;

          for (int x=xStart; x<=xEnd; x++)
          {
            paintPixel(_image,_width,_height,_rotatedX,_rotatedY,x,y,_color);
          }
        }
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintWkbPoint(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,MemoryReader& _memoryReader,uint _color)
{
  FUNCTION_TRACE
  try
  {
    std::uint8_t byteOrder = _memoryReader.read_uint8();
    _memoryReader.setLittleEndian((bool)byteOrder);
    /*std::uint32_t wkbType =*/ _memoryReader.read_uint32();

    double x = (_memoryReader.read_double() + _dx);
    double y = (_memoryReader.read_double() + _dy);

    x = x * _mp;
    y = y*_mp;

    paintPixel(_image,_width,_height,_rotatedX,_rotatedY,C_INT(x),C_INT(y),_color);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintWkbLine(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,MemoryReader& _memoryReader,uint _color)
{
  FUNCTION_TRACE
  try
  {
    double xp = 0;
    double yp = 0;

    std::uint32_t pointCount = _memoryReader.read_uint32();
    //printf("Point count %u\n",pointCount);
    for (std::uint32_t t=0; t<pointCount; t++)
    {
      double x = (_memoryReader.read_double() + _dx);
      double y = (_memoryReader.read_double() + _dy);

      //printf("%f,%f\n",x,y);
      x = x * _mp;
      y = y*_mp;

      if (t > 0)
        paintLine(_image,_width,_height,_rotatedX,_rotatedY,C_INT(xp),C_INT(yp),C_INT(x),C_INT(y),_color);

      xp = x;
      yp = y;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintWkbRing(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,MemoryReader& _memoryReader,uint _color)
{
  FUNCTION_TRACE
  try
  {
    std::vector<T::Coordinate> polygonPoints;

    std::uint32_t pointCount = _memoryReader.read_uint32();
    for (std::uint32_t t=0; t<pointCount; t++)
    {
      double x = (_memoryReader.read_double() + _dx);
      x = x *_mp;
      double y = (_memoryReader.read_double() + _dy);
      y = y*_mp;

      polygonPoints.push_back(T::Coordinate(x,y));
    }

    paintPolygon(_image,_width,_height,_rotatedX,_rotatedY,polygonPoints,_color);

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintWkbPolygon(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,MemoryReader& _memoryReader,uint _color)
{
  FUNCTION_TRACE
  try
  {
    std::uint32_t ringCount = _memoryReader.read_uint32();

    for (std::uint32_t t=0; t<ringCount; t++)
    {
      paintWkbRing(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,_memoryReader,_color);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintWkbMultiPoint(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,MemoryReader& _memoryReader,uint _color)
{
  FUNCTION_TRACE
  try
  {
    std::uint32_t pointCount = _memoryReader.read_uint32();
    //printf("STRINGS %u\n",stringCount);
    for (std::uint32_t t=0; t<pointCount; t++)
    {
      paintWkbPoint(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,_memoryReader,_color);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintWkbMultiLineString(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,MemoryReader& _memoryReader,uint _color)
{
  FUNCTION_TRACE
  try
  {
    std::uint32_t lineCount = _memoryReader.read_uint32();
    for (std::uint32_t a=0; a<lineCount; a++)
    {
      std::uint8_t byteOrder = _memoryReader.read_uint8();
      _memoryReader.setLittleEndian((bool)byteOrder);
      /*std::uint32_t wkbType =*/ _memoryReader.read_uint32();
      paintWkbLine(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,_memoryReader,_color);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintWkbMultiPolygon(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,MemoryReader& _memoryReader,uint _color)
{
  FUNCTION_TRACE
  try
  {

    std::uint32_t polygonCount = _memoryReader.read_uint32();
    //printf("PolygonCount %u\n",polygonCount);
    for (std::uint32_t t=0; t<polygonCount; t++)
    {
      std::uint8_t byteOrder = _memoryReader.read_uint8();
      _memoryReader.setLittleEndian((bool)byteOrder);
      /*std::uint32_t wkbType =*/ _memoryReader.read_uint32();

      std::uint32_t ringCount = _memoryReader.read_uint32();
      //printf("RingCount %d\n",ringCount);
      std::vector<std::vector<T::Coordinate>> polygonPath;

      for (std::uint32_t t=0; t<ringCount; t++)
      {
        std::vector<T::Coordinate> polygonPoints;

        std::uint32_t pointCount = _memoryReader.read_uint32();
        for (std::uint32_t t=0; t<pointCount; t++)
        {
          double x = (_memoryReader.read_double() + _dx);
          x = x *_mp;
          double y = (_memoryReader.read_double() + _dy);
          y = y*_mp;

          polygonPoints.push_back(T::Coordinate(x,y));
        }

        polygonPath.push_back(polygonPoints);
      }
      paintPolygonPath(_image,_width,_height,_rotatedX,_rotatedY,polygonPath,_color);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintWkbGeometryCollection(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,MemoryReader& _memoryReader,uint _color)
{
  FUNCTION_TRACE
  try
  {
    std::uint32_t geometryCount = _memoryReader.read_uint32();
    //printf("GeometryCount %u\n",geometryCount);
    for (std::uint32_t t=0; t<geometryCount; t++)
    {
      paintWkb(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,_memoryReader,_color);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintWkb(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,MemoryReader& _memoryReader,uint _color)
{
  FUNCTION_TRACE
  try
  {
    while (_memoryReader.getReadPosition() < _memoryReader.getDataSize())
    {
      std::uint8_t byteOrder = _memoryReader.read_uint8();
      //printf("Byte order %u\n",byteOrder);
      _memoryReader.setLittleEndian((bool)byteOrder);

      std::uint32_t wkbType = _memoryReader.read_uint32();
      //printf("WKB_TYPE %u\n",wkbType);

      switch (wkbType)
      {
        case 1:
          paintWkbPoint(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,_memoryReader,_color);
          break;

        case 2:
          paintWkbLine(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,_memoryReader,_color);
          break;

        case 3:
          paintWkbPolygon(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,_memoryReader,_color);
          break;

        case 4:
          paintWkbMultiPoint(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,_memoryReader,_color);
          break;

        case 5:
          paintWkbMultiLineString(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,_memoryReader,_color);
          break;

        case 6:
          paintWkbMultiPolygon(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,_memoryReader,_color);
          break;

        case 7:
          paintWkbGeometryCollection(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,_memoryReader,_color);
          break;
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintWkb(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,uchar *_wkb,uint _size,uint _color)
{
  FUNCTION_TRACE
  try
  {
    if (_size == 0)
      return;

    MemoryReader memoryReader(_wkb,_size);
    paintWkb(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,memoryReader,_color);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintWkb(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,T::WkbData& _wkb,uint _color)
{
  FUNCTION_TRACE
  try
  {
    size_t sz = _wkb.size();
    //printf("** SIZE %lu\n",sz);
    if (sz == 0)
      return;

    uchar *buf = new uchar[sz];
    MemoryReader memoryReader(buf,sz,true);

    for (size_t t=0; t<sz; t++)
      buf[t] = _wkb[t];

    paintWkb(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,memoryReader,_color);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void paintWkb(uint *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,T::WkbData_vec& _wkbVec,uint _color)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = _wkbVec.begin(); it != _wkbVec.end(); ++it)
    {
      paintWkb(_image,_width,_height,_rotatedX,_rotatedY,_mp,_dx,_dy,*it,_color);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}

#endif













}

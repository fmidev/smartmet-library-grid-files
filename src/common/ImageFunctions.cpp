#include "Exception.h"

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <jpeglib.h>
#include <math.h>

namespace SmartMet
{


void jpeg_save(const char *filename, unsigned long *image, int image_height,int image_width, int quality)
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
        unsigned long col = image[c];
        image_buffer[p++] = (unsigned char)((col & 0xFF0000) >> 16);
        image_buffer[p++] = (unsigned char)((col & 0x00FF00) >> 8);
        image_buffer[p++] = (unsigned char)(col & 0xFF);
        c++;
      }
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE * outfile = NULL;
    JSAMPROW row_pointer[1];
    int row_stride = 0;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    if ((outfile = fopen(filename, "wb")) == NULL)
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
    delete image_buffer;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint rgb(uint red, uint green, uint blue)
{
  try
  {
    return (red << 16) + (green << 8) + blue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
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

    /* assign temp vars based on color cone region */
    switch(region)
    {
      case 0:
        return rgb(value,t,p);
      case 1:
        return rgb(q,value,p);
      case 2:
        return rgb(p,value,t);
      case 3:
        return rgb(p,q,value);
      case 4:
        return rgb(t,p,value);
      default:
        return rgb(value,p,q);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




}

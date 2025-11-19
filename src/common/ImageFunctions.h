#pragma once

#include "Typedefs.h"
#include "../grid/Typedefs.h"

#include <newbase/NFmiSvgPath.h>
#include <macgyver/Exception.h>
#include <ogr_geometry.h>


namespace SmartMet
{

extern int compare_coordinates(const void *p1, const void *p2);


class CImage
{
  public:
    CImage()
    {
      width = 0;
      height = 0;
      pixel = nullptr;
    }

    CImage(const CImage& image)
    {
      width = image.width;
      height = image.height;
      pixel = nullptr;
      if (image.pixel != nullptr  &&  width != 0  &&  height != 0)
      {
        int sz = width*height;
        pixel = new uint[sz];
        memcpy(pixel,image.pixel,sz*sizeof(uint));
      }
    }

    CImage(int _width,int _height)
    {
      width = _width;
      height = _height;
      pixel = nullptr;
      if (width != 0  &&  height != 0)
      {
        int sz = width*height;
        pixel = new uint[sz];
        for (int t=0; t<sz; t++)
          pixel[t] = 0xFFFFFFFF;
      }
    }

    virtual ~CImage()
    {
      if (pixel != nullptr)
        delete[] pixel;
    }

    CImage& operator=(const CImage& image)
    {
      if (pixel != nullptr)
        delete[] pixel;

      pixel = nullptr;
      width = image.width;
      height = image.height;

      if (image.pixel != nullptr  &&  width != 0  &&  height != 0)
      {
        int sz = width*height;
        pixel = new uint[sz];
        memcpy(pixel,image.pixel,sz*sizeof(uint));
      }
      return *this;
    }

    int       width;
    int       height;
    uint      *pixel;
};



// The function reads a JPG image into the memory.

int  jpg_load(const char *_filename,CImage& _image);


// The function writes an image data to the JPEG file.

void jpeg_save(const char *filename,uint *image,int image_height,int image_width,int quality);

// The function reads a PNG image into the memory.

int  png_load(const char *_filename,CImage& _image);
int  png_load(const char *_filename,std::vector<uint>& _image,uint& _width,uint& _height);

// The function writes an image data to the PNG file.

int  png_save(const char *filename,uint *image,int image_width,int image_height);
int  png_save(const char *filename,uint *image,int image_width,int image_height,int compressionLevel);

int  png_saveMem(char *buffer,int bufferSize,uint *image,int image_width,int image_height);
int  png_saveMem(char *buffer,int bufferSize,uint *image,int image_width,int image_height,int compressionLevel);

void mergePngFiles(const char *newFile,std::vector<std::string>& fileList);
void merge_ARGB_arrays(uint32_t *top, uint32_t *bottom, uint32_t *newArray,uint32_t size);

int  webp_anim_save(const char *filename,uint **image,int image_width,int image_height,int numberOfImages,int timeStepMsec);


// The function converts RGB color component (Red,Green,Blue) to a single RGB value.
// An individual color should have a value that is the range 0..255.

uint rgb(uint red, uint green, uint blue);


// The function converts HSV (Hue, Saturatio, Value) color to a RGB color. Each
// HSV component should have value that is in the range 0..255.

void saveGeometryAsJpeg(const char *_filename,int width,int height,uint backgroundColor,uint drawColor,uint fillColor,const OGRGeometry *geom,bool autoscale);
void saveGeometryAsJpeg(const char *_filename,int width,int height,uint backgroundColor,uint drawColor,uint fillColor,std::vector<std::shared_ptr<OGRGeometry>> geomVec,bool autoscale);

inline uint32_t merge_ARGB(uint32_t top, uint32_t bottom)
{
  float At = ((top >> 24) & 0xFF) / 255.0f;
  float Rt = ((top >> 16) & 0xFF) / 255.0f;
  float Gt = ((top >> 8)  & 0xFF) / 255.0f;
  float Bt = (top         & 0xFF) / 255.0f;

  float Ab = ((bottom >> 24) & 0xFF) / 255.0f;
  float Rb = ((bottom >> 16) & 0xFF) / 255.0f;
  float Gb = ((bottom >> 8)  & 0xFF) / 255.0f;
  float Bb = (bottom         & 0xFF) / 255.0f;

  float Aout = At + Ab * (1.0f - At);

  float Rout = (Rt * At + Rb * Ab * (1.0f - At));
  float Gout = (Gt * At + Gb * Ab * (1.0f - At));
  float Bout = (Bt * At + Bb * Ab * (1.0f - At));

  if (Aout > 0.0f)
  {
    Rout /= Aout;
    Gout /= Aout;
    Bout /= Aout;
  }

  uint8_t A = (uint8_t)roundf(Aout * 255.0f);
  uint8_t R = (uint8_t)roundf(Rout * 255.0f);
  uint8_t G = (uint8_t)roundf(Gout * 255.0f);
  uint8_t B = (uint8_t)roundf(Bout * 255.0f);

  return (A << 24) | (R << 16) | (G << 8) | B;
}


inline uint rgb(uint red, uint green, uint blue)
{
  return (red << 16) + (green << 8) + blue;
}


inline uint rgb(uchar red, uchar green, uchar blue)
{
  return rgb(C_UINT(red),C_UINT(green),C_UINT(blue));
}


inline uint cmyk2rgb(double _c, double _m, double _y, double _k)
{
  double r = (255.0 - _c*255) * (1.0 - _k);
  double g = (255.0 - _m*255) * (1.0 - _k);
  double b = (255.0 - _y*255) * (1.0 - _k);

  return rgb(C_UINT(r),C_UINT(g),C_UINT(b));
}




inline uint hsv_to_rgb(unsigned char hue, unsigned char saturation, unsigned char value)
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



}


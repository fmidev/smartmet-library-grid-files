#pragma once

#include "Exception.h"
#include "Typedefs.h"
#include "../grid/Typedefs.h"

#include <newbase/NFmiSvgPath.h>


namespace SmartMet
{


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

int jpg_load(const char *_filename,CImage& _image);


// The function writes an image data to the JPEG file.

void jpeg_save(const char *filename,unsigned long *image,int image_height,int image_width,int quality);

// The function reads a PNG image into the memory.

int png_load(const char *_filename,CImage& _image);

// The function converts RGB color component (Red,Green,Blue) to a single RGB value.
// An individual color should have a value that is the range 0..255.

uint rgb(uint red, uint green, uint blue);


// The function converts HSV (Hue, Saturatio, Value) color to a RGB color. Each
// HSV component should have value that is in the range 0..255.

uint hsv_to_rgb(unsigned char hue, unsigned char saturation, unsigned char value);

void paintPixel(unsigned long *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,int _x,int _y,uint _color);
void paintLine(unsigned long *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,int _x1,int _y1,int _x2,int _y2,uint _color);
void paintSvgPath(unsigned long *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,NFmiSvgPath& _svgPath,uint _color);
void paintWkb(unsigned long *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,uchar *_wkb,uint _size,uint _color);
void paintWkb(unsigned long *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,T::WkbData& _wkb,uint _color);
void paintWkb(unsigned long *_image,int _width,int _height,bool _rotatedX,bool _rotatedY,double _mp,double _dx,double _dy,T::WkbData_vec& _wkbVec,uint _color);

}


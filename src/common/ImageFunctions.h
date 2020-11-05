#pragma once

#include "Typedefs.h"
#include "../grid/Typedefs.h"

#include <newbase/NFmiSvgPath.h>
#include <macgyver/Exception.h>


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

int jpg_load(const char *_filename,CImage& _image);


// The function writes an image data to the JPEG file.

void jpeg_save(const char *filename,uint *image,int image_height,int image_width,int quality);

// The function reads a PNG image into the memory.

int png_load(const char *_filename,CImage& _image);

// The function writes an image data to the PNG file.

int png_save(const char *filename,uint *image,int image_width,int image_height);

void mergePngFiles(const char *newFile,std::vector<std::string>& fileList);


// The function converts RGB color component (Red,Green,Blue) to a single RGB value.
// An individual color should have a value that is the range 0..255.

uint rgb(uint red, uint green, uint blue);


// The function converts HSV (Hue, Saturatio, Value) color to a RGB color. Each
// HSV component should have value that is in the range 0..255.

uint hsv_to_rgb(unsigned char hue, unsigned char saturation, unsigned char value);


}


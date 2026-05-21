#pragma once

#include "Typedefs.h"
#include "../grid/Typedefs.h"

#include <newbase/NFmiSvgPath.h>
#include <macgyver/Exception.h>
#include <ogr_geometry.h>


namespace SmartMet
{

/*! \brief qsort-compatible comparator for coordinate pairs (x,y doubles). */
extern int compare_coordinates(const void *p1, const void *p2);


// ====================================================================================
/*! \brief Simple RGBA pixel buffer holding width×height 32-bit pixels (ARGB layout).
 *
 *  Manages heap-allocated pixel memory; owns the buffer except when constructed from
 *  an external `_pixel` pointer. */
// ====================================================================================

class CImage
{
  public:
    /*! \brief Construct an empty (0×0) image with no pixel buffer. */
    CImage()
    {
      width = 0;
      height = 0;
      pixel = nullptr;
    }

    /*! \brief Deep-copy constructor. */
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

    /*! \brief Allocate a width×height pixel buffer filled with opaque white (0xFFFFFFFF).
     *  \param[in] _width   Image width in pixels.
     *  \param[in] _height  Image height in pixels. */
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

    /*! \brief Wrap an external pixel buffer (does NOT take ownership).
     *  \param[in] _width   Image width.
     *  \param[in] _height  Image height.
     *  \param[in] _pixel   Existing pixel array (caller retains ownership). */
    CImage(int _width,int _height,uint *_pixel)
    {
      width = _width;
      height = _height;
      pixel = _pixel;
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

    int       width;   //!< Image width in pixels
    int       height;  //!< Image height in pixels
    uint      *pixel;  //!< ARGB pixel buffer (row-major, top-to-bottom)
};



/*! \brief Load a JPEG file into a CImage.  \return 0 on success. */
int  jpg_load(const char *_filename,CImage& _image);

/*! \brief Write a pixel buffer to a JPEG file at the given quality (1–100). */
void jpeg_save(const char *filename,uint *image,int image_height,int image_width,int quality);

/*! \brief Load a PNG file into a CImage.  \return 0 on success. */
int  png_load(const char *_filename,CImage& _image);
//! \overload (loads into a vector with separate width/height output)
int  png_load(const char *_filename,std::vector<uint>& _image,uint& _width,uint& _height);

/*! \brief Write a pixel buffer to a PNG file (default compression).  \return 0 on success. */
int  png_save(const char *filename,uint *image,int image_width,int image_height);
//! \overload (with explicit zlib compression level 0–9)
int  png_save(const char *filename,uint *image,int image_width,int image_height,int compressionLevel);

/*! \brief Encode a pixel buffer as PNG into a pre-allocated memory buffer.
 *  \return Encoded byte count, or -1 on error. */
int  png_saveMem(char *buffer,int bufferSize,uint *image,int image_width,int image_height);
//! \overload (with explicit compression level)
int  png_saveMem(char *buffer,int bufferSize,uint *image,int image_width,int image_height,int compressionLevel);

/*! \brief Alpha-composite and merge a list of PNG files into a single output PNG. */
void mergePngFiles(const char *newFile,std::vector<std::string>& fileList);

/*! \brief Alpha-composite two ARGB pixel arrays element-wise into \p newArray.
 *  \param[in]  top       Foreground pixel array.
 *  \param[in]  bottom    Background pixel array.
 *  \param[out] newArray  Composited output.
 *  \param[in]  size      Number of pixels. */
void merge_ARGB_arrays(uint32_t *top, uint32_t *bottom, uint32_t *newArray,uint32_t size);

/*! \brief Save a multi-frame WebP animation (RGB channels). */
int  webp_anim_save(const char *filename,uint **image,int image_width,int image_height,int numberOfImages,std::vector<int>& timeStepMsec);
/*! \brief Save a multi-frame WebP animation (ARGB with alpha channel). */
int  webp_anim_save_ARGB(const char *filename,uint **image,int image_width,int image_height,int numberOfImages,std::vector<int>& timeStepMsec);

/*! \brief Pack red, green, blue components (0–255 each) into a single 32-bit RGB value. */
uint rgb(uint red, uint green, uint blue);

/*! \brief Render a single OGR geometry into a JPEG image file. */
void saveGeometryAsJpeg(const char *_filename,int width,int height,uint backgroundColor,uint drawColor,uint fillColor,const OGRGeometry *geom,bool autoscale);
//! \overload (renders a list of geometries)
void saveGeometryAsJpeg(const char *_filename,int width,int height,uint backgroundColor,uint drawColor,uint fillColor,std::vector<std::shared_ptr<OGRGeometry>> geomVec,bool autoscale);

/*! \brief Alpha-composite two ARGB pixels using standard "over" blending.
 *  \param[in] top     Foreground ARGB pixel.
 *  \param[in] bottom  Background ARGB pixel.
 *  \return Composited ARGB pixel. */
inline uint32_t merge_ARGB(uint32_t top, uint32_t bottom)
{
  if (!(top & 0xFF000000))
    return bottom;

  if (!(bottom & 0xFF000000))
    return top;

  float At = ((top >> 24) & 0xFF) / 255.0f;
  float Rt = ((top >> 16) & 0xFF) / 255.0f;
  float Gt = ((top >> 8)  & 0xFF) / 255.0f;
  float Bt = (top         & 0xFF) / 255.0f;

  float Ab = ((bottom >> 24) & 0xFF) / 255.0f;
  float Rb = ((bottom >> 16) & 0xFF) / 255.0f;
  float Gb = ((bottom >> 8)  & 0xFF) / 255.0f;
  float Bb = (bottom         & 0xFF) / 255.0f;

  float k = Ab*(1.0f - At);
  float Aout = At + k;
  float Rout = (Rt * At + Rb * k);
  float Gout = (Gt * At + Gb * k);
  float Bout = (Bt * At + Bb * k);

  if (Aout > 0.0f)
  {
    Rout /= Aout;
    Gout /= Aout;
    Bout /= Aout;
  }

  uint8_t A = (uint8_t)(Aout * 255.0f + 0.49);
  uint8_t R = (uint8_t)(Rout * 255.0f + 0.49);
  uint8_t G = (uint8_t)(Gout * 255.0f + 0.49);
  uint8_t B = (uint8_t)(Bout * 255.0f + 0.49);

  return (A << 24) | (R << 16) | (G << 8) | B;
}


/*! \brief Parse a colour string (e.g. "0xFF8800", "#FF8800", "255,128,0") into ARGB. */
uint argb(const char *colStr);

inline uint argb(std::string& colStr)
{
  return argb(colStr.c_str());
}


inline uint rgb(uint red, uint green, uint blue)
{
  return (red << 16) + (green << 8) + blue;
}


inline uint rgb(uchar red, uchar green, uchar blue)
{
  return rgb(C_UINT(red),C_UINT(green),C_UINT(blue));
}


/*! \brief Convert CMYK components (0.0–1.0 each) to a packed RGB value. */
inline uint cmyk2rgb(double _c, double _m, double _y, double _k)
{
  double r = (255.0 - _c*255) * (1.0 - _k);
  double g = (255.0 - _m*255) * (1.0 - _k);
  double b = (255.0 - _y*255) * (1.0 - _k);

  return rgb(C_UINT(r),C_UINT(g),C_UINT(b));
}




/*! \brief Convert HSV components (0–255 each) to a packed RGB value.
 *  \param[in] hue        Hue (0–255, maps to 0°–360°).
 *  \param[in] saturation Saturation (0–255).
 *  \param[in] value      Value/brightness (0–255).
 *  \return Packed RGB value. */
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


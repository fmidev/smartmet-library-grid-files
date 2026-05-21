#pragma once

#include "ImageFunctions.h"
#include "MemoryReader.h"
#include "ShowFunction.h"
#include <macgyver/Exception.h>

namespace SmartMet
{


// ====================================================================================
/*! \brief Raster painter that renders geographic vector geometries (WKB, polygons,
 *  lines, points) into a 32-bit ARGB pixel buffer.
 *
 *  The coordinate system is controlled by map-plane origin (`_mpx`, `_mpy`) and pixel
 *  scale factors (`_dx`, `_dy`).  X and/or Y axes can optionally be flipped. */
// ====================================================================================

class ImagePaint
{
  public:

    /*! \brief Construct and allocate a fresh pixel buffer.
     *  \param[in] _imageWidth  Image width in pixels.
     *  \param[in] _imageHeight Image height in pixels.
     *  \param[in] _backColor   Background fill colour (ARGB).
     *  \param[in] _drawColor   Initial draw/outline colour (ARGB).
     *  \param[in] _fillColor   Initial polygon fill colour (ARGB).
     *  \param[in] _rotatedX    Flip X axis if true.
     *  \param[in] _rotatedY    Flip Y axis if true. */
            ImagePaint(int _imageWidth,int _imageHeight,uint _backColor,uint _drawColor,uint _fillColor,bool _rotatedX,bool _rotatedY);

    /*! \brief Construct a painter over an externally supplied pixel buffer.
     *  \param[in] _image       Pixel buffer (caller owns; not freed on destruction).
     *  \param[in] _imageWidth  Image width.
     *  \param[in] _imageHeight Image height.
     *  \param[in] _backColor   Background colour.
     *  \param[in] _drawColor   Outline colour.
     *  \param[in] _fillColor   Fill colour.
     *  \param[in] _rotatedX    Flip X axis.
     *  \param[in] _rotatedY    Flip Y axis. */
            ImagePaint(uint *_image,int _imageWidth,int _imageHeight,uint _backColor,uint _drawColor,uint _fillColor,bool _rotatedX,bool _rotatedY);
    virtual ~ImagePaint();

    /*! \brief Scan a WKB geometry and compute its bounding box.
     *  \param[in]  _wkb   WKB byte buffer.
     *  \param[in]  _size  Buffer size in bytes.
     *  \param[out] _minX,_minY,_maxX,_maxY  Bounding box in native coordinates. */
    void    countPaintWkbArea(uchar *_wkb,uint _size,double& _minX,double& _minY,double& _maxX,double& _maxY);

    /*! \brief Set the outline draw colour.  \param[in] _color  ARGB colour value. */
    void    setDrawColor(uint _color);
    /*! \brief Set the polygon fill colour.  \param[in] _color  ARGB colour value. */
    void    setFillColor(uint _color);
    /*! \brief Return the pixel at (x,y).  \return ARGB value, or 0 if out of bounds. */
    uint    getPixel(int _x,int _y);
    /*! \brief Return a pointer to the raw pixel buffer. */
    uint*   getImage();

    /*! \brief Paint a single pixel.
     *  \param[in] _x,_y  Pixel coordinates.
     *  \param[in] _color ARGB colour. */
    void    paintPixel(int _x,int _y,uint _color);

    /*! \brief Draw an integer-coordinate line using Bresenham's algorithm. */
    void    paintLine(int _x1,int _y1,int _x2,int _y2,uint _color);
    //! \overload (floating-point coordinates)
    void    paintLine(double _x1,double _y1,double _x2,double _y2,uint _color);

    /*! \brief Fill and outline a simple polygon.
     *  \param[in] polygonPoints  Polygon vertices in image coordinates.
     *  \param[in] _drawColor     Outline colour.
     *  \param[in] _fillColor     Fill colour. */
    void    paintPolygon(std::vector<T::Coordinate>& polygonPoints,uint _drawColor,uint _fillColor);

    /*! \brief Fill and outline a multi-ring polygon path.
     *  \param[in] polygonPath  Outer ring + hole rings.
     *  \param[in] _drawColor   Outline colour.
     *  \param[in] _fillColor   Fill colour. */
    void    paintPolygonPath(std::vector<std::vector<T::Coordinate>>& polygonPath,uint _drawColor,uint _fillColor);

    /*! \brief Parse and paint a WKB geometry from a MemoryReader.
     *  \param[in] _mpx           Map-plane origin x in geographic coordinates.
     *  \param[in] _mpy           Map-plane origin y in geographic coordinates.
     *  \param[in] _dx            Pixels-per-coordinate-unit x scale factor.
     *  \param[in] _dy            Pixels-per-coordinate-unit y scale factor.
     *  \param[in] _memoryReader  Reader positioned at the start of the WKB data. */
    void    paintWkb(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader);
    //! \overload (WKB from a raw byte buffer)
    void    paintWkb(double _mpx,double _mpy,double _dx,double _dy,uchar *_wkb,uint _size);
    //! \overload (WKB from a ByteData vector)
    void    paintWkb(double _mpx,double _mpy,double _dx,double _dy,T::ByteData& _wkb);
    //! \overload (multiple WKB geometries from a ByteData_vec)
    void    paintWkb(double _mpx,double _mpy,double _dx,double _dy,T::ByteData_vec& _wkbVec);

    /*! \brief Encode and save the current pixel buffer as a JPEG file.
     *  \param[in] _filename  Output path. */
    void    saveJpgImage(const char *_filename);

    /*! \brief Encode and save the current pixel buffer as a PNG file.
     *  \param[in] _filename  Output path. */
    void    savePngImage(const char *_filename);

  protected:

    void    paintWkbPoint(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader);
    void    paintWkbLine(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader);
    void    paintWkbRing(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader);
    void    paintWkbPolygon(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader);
    void    paintWkbMultiPoint(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader);
    void    paintWkbMultiLineString(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader);
    void    paintWkbMultiPolygon(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader);
    void    paintWkbGeometryCollection(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader);

    int     mImageWidth;      //!< Image width in pixels
    int     mImageHeight;     //!< Image height in pixels
    uint    *mImage;          //!< Pixel buffer (ARGB, row-major)
    bool    mReleaseImage;    //!< True when the pixel buffer was allocated by this object
    bool    mRotatedX;        //!< True to flip the X axis
    bool    mRotatedY;        //!< True to flip the Y axis
    uint    mBackColor;       //!< Background colour
    uint    mDrawColor;       //!< Current outline colour
    uint    mFillColor;       //!< Current fill colour
    double  mMinX;            //!< Bounding-box min X (updated during countPaintWkbArea)
    double  mMinY;            //!< Bounding-box min Y
    double  mMaxX;            //!< Bounding-box max X
    double  mMaxY;            //!< Bounding-box max Y
    bool    mCountingActive;  //!< True during countPaintWkbArea to suppress actual painting
};


}


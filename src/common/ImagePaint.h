#pragma once

#include "ImageFunctions.h"
#include "MemoryReader.h"
#include "ShowFunction.h"
#include <macgyver/Exception.h>

namespace SmartMet
{


class ImagePaint
{
  public:

            ImagePaint(int _imageWidth,int _imageHeight,uint _backColor,uint _drawColor,uint _fillColor,bool _rotatedX,bool _rotatedY);
    virtual ~ImagePaint();

    void    countPaintWkbArea(uchar *_wkb,uint _size,double& _minX,double& _minY,double& _maxX,double& _maxY);

    void    setDrawColor(uint _color);
    void    setFillColor(uint _color);
    uint*   getImage();
    void    paintPixel(int _x,int _y,uint _color);
    void    paintLine(int _x1,int _y1,int _x2,int _y2,uint _color);
    void    paintLine(double _x1,double _y1,double _x2,double _y2,uint _color);
    void    paintPolygon(std::vector<T::Coordinate>& polygonPoints,uint _drawColor,uint _fillColor);
    void    paintPolygonPath(std::vector<std::vector<T::Coordinate>>& polygonPath,uint _drawColor,uint _fillColor);

    void    paintWkb(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader);
    void    paintWkb(double _mpx,double _mpy,double _dx,double _dy,uchar *_wkb,uint _size);
    void    paintWkb(double _mpx,double _mpy,double _dx,double _dy,T::ByteData& _wkb);
    void    paintWkb(double _mpx,double _mpy,double _dx,double _dy,T::ByteData_vec& _wkbVec);

    void    saveJpgImage(const char *_filename);
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

    int     mImageWidth;
    int     mImageHeight;
    uint    *mImage;
    bool    mRotatedX;
    bool    mRotatedY;
    uint    mBackColor;
    uint    mDrawColor;
    uint    mFillColor;
    double  mMinX;
    double  mMinY;
    double  mMaxX;
    double  mMaxY;
    bool    mCountingActive;
};


}


#pragma once

#include "ImageFunctions.h"
#include "Exception.h"
#include "MemoryReader.h"
#include "ShowFunction.h"

namespace SmartMet
{


class ImagePaint
{
  public:

            ImagePaint(int _imageWidth,int _imageHeight,uint _backColor,bool _rotatedX,bool _rotatedY);
    virtual ~ImagePaint();

    void    paintPixel(int _x,int _y,uint _color);
    void    paintLine(int _x1,int _y1,int _x2,int _y2,uint _color);
    void    paintLine(double _x1,double _y1,double _x2,double _y2,uint _color);
    void    paintPolygon(std::vector<T::Coordinate>& polygonPoints,uint _color);
    void    paintPolygonPath(std::vector<std::vector<T::Coordinate>>& polygonPath,uint _color);

    void    paintWkb(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader,uint _color);
    void    paintWkb(double _mpx,double _mpy,double _dx,double _dy,uchar *_wkb,uint _size,uint _color);
    void    paintWkb(double _mpx,double _mpy,double _dx,double _dy,T::ByteData& _wkb,uint _color);
    void    paintWkb(double _mpx,double _mpy,double _dx,double _dy,T::ByteData_vec& _wkbVec,uint _color);

    void    saveJpgImage(const char *_filename);
    void    savePngImage(const char *_filename);

  protected:

    void    paintWkbPoint(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader,uint _color);
    void    paintWkbLine(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader,uint _color);
    void    paintWkbRing(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader,uint _color);
    void    paintWkbPolygon(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader,uint _color);
    void    paintWkbMultiPoint(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader,uint _color);
    void    paintWkbMultiLineString(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader,uint _color);
    void    paintWkbMultiPolygon(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader,uint _color);
    void    paintWkbGeometryCollection(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader,uint _color);

    int     mImageWidth;
    int     mImageHeight;
    uint    *mImage;
    bool    mRotatedX;
    bool    mRotatedY;
    uint    mBackColor;

};


}


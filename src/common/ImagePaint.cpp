#include "ImagePaint.h"
#include "ImageFunctions.h"
#include "MemoryReader.h"
#include "ShowFunction.h"
#include <macgyver/Exception.h>

#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{



ImagePaint::ImagePaint(int _imageWidth,int _imageHeight,uint _backColor,uint _drawColor,uint _fillColor,bool _rotatedX,bool _rotatedY)
{
  try
  {
    if (_imageWidth <= 0)
      throw Fmi::Exception(BCP,"Illegal image width!");

    if (_imageHeight <= 0)
      throw Fmi::Exception(BCP,"Illegal image height!");

    mImageWidth = _imageWidth;
    mImageHeight = _imageHeight;
    mRotatedX = _rotatedX;
    mRotatedY = _rotatedY;
    mBackColor = _backColor;
    mDrawColor = _drawColor;
    mFillColor = _fillColor;
    mMinX = 0;
    mMinY = 0;
    mMaxX = 0;
    mMaxY = 0;
    mCountingActive = false;

    int sz = _imageWidth * _imageHeight;
    mImage = new uint[sz];
    for (int t=0; t<sz; t++)
      mImage[t] = _backColor;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




ImagePaint::~ImagePaint()
{
  try
  {
    if (mImage != nullptr)
      delete[] mImage;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}




uint* ImagePaint::getImage()
{
  try
  {
    return mImage;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::setDrawColor(uint _color)
{
  try
  {
    mDrawColor = _color;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void ImagePaint::setFillColor(uint _color)
{
  try
  {
    mFillColor = _color;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void ImagePaint::paintPixel(int _x,int _y,uint _color)
{
  try
  {
    if (mCountingActive)
      return;

    if (_x >= 0  &&  _x < mImageWidth  &&  _y >=0  &&  _y < mImageHeight)
    {
      if (mRotatedY)
        _y = mImageHeight-_y-1;

      if (mRotatedX)
        _x = mImageWidth-_x-1;

     mImage[_y*mImageWidth + _x] = _color;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintLine(double _x1,double _y1,double _x2,double _y2,uint _color)
{
  try
  {
    if (mCountingActive)
      return;

    //printf("PaintLine %f,%f  =>  %f,%f\n",_x1,_y1,_x2,_y2);
    paintLine(C_INT(round(_x1)),C_INT(round(_y1)),C_INT(round(_x2)),C_INT(round(_y2)),_color);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintLine(int _x1,int _y1,int _x2,int _y2,uint _color)
{
  FUNCTION_TRACE
  try
  {
    if (mCountingActive)
      return;

    //printf("PaintLine %d,%d  =>  %d,%d\n",_x1,_y1,_x2,_y2);

    if (_x1 == -2147483648 || _y1 == -2147483648 || _x2 == -2147483648 || _y2 == -2147483648)
      return;


    if (_x1 == _x2  &&  _y1 == _y2)
    {
      paintPixel(_x1,_y1,_color);
      return;
    }

    int x1 = (int)_x1;
    int y1 = (int)_y1;
    int x2 = (int)_x2;
    int y2 = (int)_y2;

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
        paintPixel(x1,y1,_color);
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
        paintPixel(x1,y1,_color);
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintPolygon(std::vector<T::Coordinate>& polygonPoints,uint _drawColor,uint _fillColor)
{
  try
  {
    if (mCountingActive)
      return;

    std::set<unsigned long long> cList;
    uint numOfPoints = polygonPoints.size();
    if (numOfPoints == 0)
      return;

    // It the last polygon point is not same than the first point, then we should add it to the list.

    if (polygonPoints[0].x() != polygonPoints[numOfPoints-1].x()  ||  polygonPoints[0].y() != polygonPoints[numOfPoints-1].y())
    {
      polygonPoints.emplace_back(polygonPoints[0]);
      numOfPoints++;
    }


    // Painting points that are below the polygon line.

    for (uint t=1; t<numOfPoints; t++)
    {
      paintLine(polygonPoints[t-1].x(),polygonPoints[t-1].y(),polygonPoints[t].x(),polygonPoints[t].y(),_drawColor);
    }

    // Painting points that are inside the polygon line.

    int maxY = 0;
    int minY = mImageHeight-1;
    int minX = 0;
    int maxX = mImageWidth-1;

    for (auto it = polygonPoints.begin(); it != polygonPoints.end(); ++it)
    {
      double yp = round(it->y());

      if (yp < minY)
        minY = C_INT(yp);

      if (yp > maxY)
        maxY = C_INT(yp);
    }

    if (minY < 0)
      minY = 0;

    if (maxY >= mImageHeight)
      maxY = mImageHeight - 1;

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

          int xStart = C_INT(nodeX[i]);
          int xEnd = C_INT(nodeX[i+1]);

          if ((nodeX[i] - xStart) > 0)
            xStart++;

          if ((xEnd - nodeX[i+1]) > 0)
            xEnd--;

          for (int x=xStart; x<=xEnd; x++)
          {
            paintPixel(x,y,_fillColor);
          }
        }
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






void ImagePaint::paintPolygonPath(std::vector<std::vector<T::Coordinate>>& polygonPath,uint _drawColor,uint _fillColor)
{
  try
  {
    if (mCountingActive)
      return;

    if (polygonPath.size() == 0)
      return;

    std::set<unsigned long long> cList;

    int minY = mImageHeight-1;
    int maxY = 0;
    int minX = 0;
    int maxX = mImageWidth-1;
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
          (*polygonPoints).emplace_back((*polygonPoints)[0]);
          numOfPoints++;
        }

        // Adding points that are below the polygon line.

        for (uint t=1; t<numOfPoints; t++)
        {
          paintLine((*polygonPoints)[t-1].x(),(*polygonPoints)[t-1].y(),(*polygonPoints)[t].x(),(*polygonPoints)[t].y(),_drawColor);
        }

        // Adding points that are inside the polygon line.

        for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
        {
          double yp = round(it->y());

          if (yp < minY)
            minY = C_INT(yp);

          if (yp > maxY)
            maxY = C_INT(yp);
        }
      }
    }

    if (minY < 0)
      minY = 0;

    if (maxY >= mImageHeight)
      maxY = mImageHeight - 1;


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
            throw Fmi::Exception(BCP,"Not enough space for the point list!",nullptr);
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

          int xStart = C_INT(nodeX[i]);
          int xEnd = C_INT(nodeX[i+1]);

          if ((nodeX[i] - xStart) > 0)
            xStart++;

          if ((xEnd - nodeX[i+1]) > 0)
            xEnd--;

          for (int x=xStart; x<=xEnd; x++)
          {
            paintPixel(x,y,_fillColor);
          }
        }
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintWkbPoint(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader)
{
  FUNCTION_TRACE
  try
  {
    std::uint8_t byteOrder = _memoryReader.read_uint8();
    _memoryReader.setLittleEndian((bool)byteOrder);
    /*std::uint32_t wkbType =*/ _memoryReader.read_uint32();

    double x = (_memoryReader.read_double() + _dx);
    double y = (_memoryReader.read_double() + _dy);

    x = x * _mpx;
    y = y*_mpy;

    if (mCountingActive)
    {
      if (x < mMinX)
        mMinX = x;

      if (x > mMaxX)
        mMaxX = x;

      if (y < mMinY)
        mMinY = y;

      if (y > mMaxY)
        mMaxY = y;
    }
    else
    {
      paintPixel(C_INT(round(x)),C_INT(round(y)),mDrawColor);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintWkbLine(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader)
{
  FUNCTION_TRACE
  try
  {
    double xp = 0;
    double yp = 0;

    std::uint32_t pointCount = _memoryReader.read_uint32();
    for (std::uint32_t t=0; t<pointCount; t++)
    {
      double x = (_memoryReader.read_double() + _dx);
      double y = (_memoryReader.read_double() + _dy);

      x = x * _mpx;
      y = y*_mpy;

      if (mCountingActive)
      {
        if (x < mMinX)
          mMinX = x;

        if (x > mMaxX)
          mMaxX = x;

        if (y < mMinY)
          mMinY = y;

        if (y > mMaxY)
          mMaxY = y;
      }
      else
      {
        if (t > 0)
          paintLine(C_INT(round(xp)),C_INT(round(yp)),C_INT(round(x)),C_INT(round(y)),mDrawColor);
      }

      xp = x;
      yp = y;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void ImagePaint::paintWkbRing(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader)
{
  FUNCTION_TRACE
  try
  {
    std::vector<T::Coordinate> polygonPoints;

    std::uint32_t pointCount = _memoryReader.read_uint32();
    for (std::uint32_t t=0; t<pointCount; t++)
    {
      double x = (_memoryReader.read_double() + _dx);
      x = x *_mpx;
      double y = (_memoryReader.read_double() + _dy);
      y = y*_mpy;

      if (mCountingActive)
      {
        if (x < mMinX)
          mMinX = x;

        if (x > mMaxX)
          mMaxX = x;

        if (y < mMinY)
          mMinY = y;

        if (y > mMaxY)
          mMaxY = y;
      }
      else
      {
        polygonPoints.emplace_back(T::Coordinate(x,y));
      }
    }

    if (!mCountingActive)
      paintPolygon(polygonPoints,mDrawColor,mFillColor);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintWkbPolygon(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader)
{
  FUNCTION_TRACE
  try
  {
    std::uint32_t ringCount = _memoryReader.read_uint32();

    for (std::uint32_t t=0; t<ringCount; t++)
    {
      paintWkbRing(_mpx,_mpy,_dx,_dy,_memoryReader);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintWkbMultiPoint(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader)
{
  FUNCTION_TRACE
  try
  {
    std::uint32_t pointCount = _memoryReader.read_uint32();
    for (std::uint32_t t=0; t<pointCount; t++)
    {
      paintWkbPoint(_mpx,_mpy,_dx,_dy,_memoryReader);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintWkbMultiLineString(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader)
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
      paintWkbLine(_mpx,_mpy,_dx,_dy,_memoryReader);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintWkbMultiPolygon(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader)
{
  FUNCTION_TRACE
  try
  {

    std::uint32_t polygonCount = _memoryReader.read_uint32();
    for (std::uint32_t t=0; t<polygonCount; t++)
    {
      std::uint8_t byteOrder = _memoryReader.read_uint8();
      _memoryReader.setLittleEndian((bool)byteOrder);
      /*std::uint32_t wkbType =*/ _memoryReader.read_uint32();

      std::uint32_t ringCount = _memoryReader.read_uint32();
      std::vector<std::vector<T::Coordinate>> polygonPath;

      for (std::uint32_t t=0; t<ringCount; t++)
      {
        std::vector<T::Coordinate> polygonPoints;

        std::uint32_t pointCount = _memoryReader.read_uint32();
        for (std::uint32_t t=0; t<pointCount; t++)
        {
          double x = (_memoryReader.read_double() + _dx);
          x = x *_mpx;
          double y = (_memoryReader.read_double() + _dy);
          y = y*_mpy;

          if (mCountingActive)
          {
            if (x < mMinX)
              mMinX = x;

            if (x > mMaxX)
              mMaxX = x;

            if (y < mMinY)
              mMinY = y;

            if (y > mMaxY)
              mMaxY = y;
          }
          else
          {
            polygonPoints.emplace_back(T::Coordinate(x,y));
          }
        }

        if (!mCountingActive)
          polygonPath.emplace_back(polygonPoints);
      }
      if (!mCountingActive)
        paintPolygonPath(polygonPath,mDrawColor,mFillColor);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintWkbGeometryCollection(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader)
{
  FUNCTION_TRACE
  try
  {
    std::uint32_t geometryCount = _memoryReader.read_uint32();
    for (std::uint32_t t=0; t<geometryCount; t++)
    {
      paintWkb(_mpx,_mpy,_dx,_dy,_memoryReader);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintWkb(double _mpx,double _mpy,double _dx,double _dy,MemoryReader& _memoryReader)
{
  FUNCTION_TRACE
  try
  {
    while (_memoryReader.getReadPosition() < _memoryReader.getDataSize())
    {
      std::uint8_t byteOrder = _memoryReader.read_uint8();
      _memoryReader.setLittleEndian((bool)byteOrder);

      std::uint32_t wkbType = _memoryReader.read_uint32();

      printf("Type:%u\n",wkbType);
      switch (wkbType)
      {
        case 1:
          paintWkbPoint(_mpx,_mpy,_dx,_dy,_memoryReader);
          break;

        case 2:
          paintWkbLine(_mpx,_mpy,_dx,_dy,_memoryReader);
          break;

        case 3:
          paintWkbPolygon(_mpx,_mpy,_dx,_dy,_memoryReader);
          break;

        case 4:
          paintWkbMultiPoint(_mpx,_mpy,_dx,_dy,_memoryReader);
          break;

        case 5:
          paintWkbMultiLineString(_mpx,_mpy,_dx,_dy,_memoryReader);
          break;

        case 6:
          paintWkbMultiPolygon(_mpx,_mpy,_dx,_dy,_memoryReader);
          break;

        case 7:
          paintWkbGeometryCollection(_mpx,_mpy,_dx,_dy,_memoryReader);
          break;
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintWkb(double _mpx,double _mpy,double _dx,double _dy,uchar *_wkb,uint _size)
{
  FUNCTION_TRACE
  try
  {
    if (_size == 0)
      return;

    MemoryReader memoryReader(_wkb,_size);
    paintWkb(_mpx,_mpy,_dx,_dy,memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintWkb(double _mpx,double _mpy,double _dx,double _dy,T::ByteData& _wkb)
{
  FUNCTION_TRACE
  try
  {
    size_t sz = _wkb.size();
    if (sz == 0)
      return;

    uchar *buf = new uchar[sz];
    MemoryReader memoryReader(buf,sz,true);

    for (size_t t=0; t<sz; t++)
      buf[t] = _wkb[t];

    paintWkb(_mpx,_mpy,_dx,_dy,memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::paintWkb(double _mpx,double _mpy,double _dx,double _dy,T::ByteData_vec& _wkbVec)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = _wkbVec.begin(); it != _wkbVec.end(); ++it)
    {
      paintWkb(_mpx,_mpy,_dx,_dy,*it);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::countPaintWkbArea(uchar *_wkb,uint _size,double& _minX,double& _minY,double& _maxX,double& _maxY)
{
  FUNCTION_TRACE
  try
  {
    mMinX = 2000000000;
    mMinY = 2000000000;
    mMaxX = -2000000000;
    mMaxY = -2000000000;
    mCountingActive = true;
    paintWkb(1,1,0,0,_wkb,_size);
    mCountingActive = false;
    _minX = mMinX;
    _minY = mMinY;
    _maxX = mMaxX;
    _maxY = mMaxY;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void ImagePaint::saveJpgImage(const char *_filename)
{
  FUNCTION_TRACE
  try
  {
    jpeg_save(_filename,mImage,mImageHeight,mImageWidth,100);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ImagePaint::savePngImage(const char *_filename)
{
  FUNCTION_TRACE
  try
  {
    png_save(_filename,mImage,mImageWidth,mImageHeight);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}


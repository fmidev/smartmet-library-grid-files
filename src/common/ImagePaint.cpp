#include "ImagePaint.h"
#include "ImageFunctions.h"
#include "MemoryReader.h"
#include "ShowFunction.h"
#include <algorithm>
#include <vector>
#include <macgyver/Exception.h>

#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{



/*! \brief Constructs an ImagePaint that owns a newly allocated image buffer of the given size. */

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

    mReleaseImage = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Constructs an ImagePaint that uses the externally owned image buffer. */

ImagePaint::ImagePaint(uint *_image,int _imageWidth,int _imageHeight,uint _backColor,uint _drawColor,uint _fillColor,bool _rotatedX,bool _rotatedY)
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
    mImage = _image;
    mReleaseImage = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



/*! \brief Destructor. Frees the image buffer if this object owns it. */

ImagePaint::~ImagePaint()
{
  try
  {
    if (mReleaseImage  &&  mImage != nullptr)
      delete[] mImage;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}




/*! \brief Returns the underlying image buffer. */

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





/*! \brief Sets the color used for drawing lines and outlines. */

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




/*! \brief Sets the color used for filling polygon interiors. */

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




/*! \brief Returns the color of the pixel at the given coordinates, honouring axis rotations. */

uint ImagePaint::getPixel(int _x,int _y)
{
  try
  {
    if (_x >= 0  &&  _x < mImageWidth  &&  _y >=0  &&  _y < mImageHeight)
    {
      if (mRotatedY)
        _y = mImageHeight-_y-1;

      if (mRotatedX)
        _x = mImageWidth-_x-1;

     return mImage[_y*mImageWidth + _x];
    }
    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief Sets the color of the pixel at the given coordinates, honouring axis rotations. */

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





/*! \brief Draws a line between two floating-point endpoints by rounding to pixel coordinates. */

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





/*! \brief Draws a line between two integer pixel coordinates using Bresenham's algorithm. */

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

    int x1 = _x1;
    int y1 = _y1;
    int x2 = _x2;
    int y2 = _y2;

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





namespace
{

/*! \brief Appends the first point of the polygon to its end unless the polygon is already closed. */

void closePolygon(std::vector<T::Coordinate>& polygonPoints)
{
  uint numOfPoints = polygonPoints.size();
  if (polygonPoints[0].x() != polygonPoints[numOfPoints-1].x()  ||  polygonPoints[0].y() != polygonPoints[numOfPoints-1].y())
    polygonPoints.emplace_back(polygonPoints[0]);
}





/*! \brief Draws the outline of a closed polygon. */

void paintOutline(ImagePaint& paint,const std::vector<T::Coordinate>& polygonPoints,uint _drawColor)
{
  uint numOfPoints = polygonPoints.size();
  for (uint t=1; t<numOfPoints; t++)
  {
    paint.paintLine(polygonPoints[t-1].x(),polygonPoints[t-1].y(),polygonPoints[t].x(),polygonPoints[t].y(),_drawColor);
  }
}





/*! \brief Extends the rounded y-range [minY,maxY] to cover the given polygon points. */

void updateYRange(const std::vector<T::Coordinate>& polygonPoints,int& minY,int& maxY)
{
  for (const auto& polygonPoint : polygonPoints)
  {
    double yp = round(polygonPoint.y());

    if (yp < minY)
      minY = C_INT(yp);

    if (yp > maxY)
      maxY = C_INT(yp);
  }
}





/*! \brief Adds the x-coordinates where the polygon edges cross the image row y into the node list. */

template <class XAt,class YAt>
void addRowCrossings(int cnt,int y,XAt xAt,YAt yAt,std::vector<double>& nodeX,int& nodes)
{
  int j = cnt - 1;
  for (int i = 0; i<cnt; i++)
  {
    double xi = xAt(i);
    double yi = yAt(i);

    double xj = xAt(j);
    double yj = yAt(j);

    auto dy = C_DOUBLE(y);

    if ((yi < dy  &&  yj >= dy)  ||  (yj < dy &&  yi >= dy))
    {
      auto xx = C_DOUBLE(xi + (y - yi)/(yj - yi)*(xj - xi));
      if (nodes >= C_INT(nodeX.size()))
        nodeX.resize(2 * nodeX.size());
      nodeX[nodes++] = C_DOUBLE(xx);
    }
    j = i;
  }
}





/*! \brief Sorts the row crossings and fills the pixels between the node pairs. */

void fillRow(ImagePaint& paint,std::vector<double>& nodeX,int nodes,int y,int minX,int maxX,uint _fillColor)
{
  qsort(nodeX.data(), nodes, sizeof(double),compare_coordinates);

  for (int i=0; i<nodes; i+=2)
  {
    if (nodeX[i] >= maxX  ||  (i + 1) >= nodes)
      break;

    if (nodeX[i+1] > minX)
    {
      nodeX[i] = std::max<double>(nodeX[i], minX);

      nodeX[i+1] = std::min<double>(nodeX[i+1], maxX);

      int xStart = C_INT(nodeX[i]);
      int xEnd = C_INT(nodeX[i+1]);

      if ((nodeX[i] - xStart) > 0)
        xStart++;

      if ((xEnd - nodeX[i+1]) > 0)
        xEnd--;

      for (int x=xStart; x<=xEnd; x++)
      {
        paint.paintPixel(x,y,_fillColor);
      }
    }
  }
}

}  // namespace





/*! \brief Draws the outline of a polygon and fills its interior with the given colors. */

void ImagePaint::paintPolygon(std::vector<T::Coordinate>& polygonPoints,uint _drawColor,uint _fillColor)
{
  try
  {
    if (mCountingActive)
      return;

    if (polygonPoints.empty())
      return;

    // It the last polygon point is not same than the first point, then we should add it to the list.

    closePolygon(polygonPoints);
    int numOfPoints = polygonPoints.size();

    // Painting points that are below the polygon line.

    paintOutline(*this,polygonPoints,_drawColor);

    // Painting points that are inside the polygon line.

    int maxY = 0;
    int minY = mImageHeight-1;
    int minX = 0;
    int maxX = mImageWidth-1;

    updateYRange(polygonPoints,minY,maxY);

    minY = std::max(minY, 0);

    if (maxY >= mImageHeight)
      maxY = mImageHeight - 1;

    std::vector<double> nodeX(10000, 0.0);

    auto xAt = [&polygonPoints](int i) { return polygonPoints[i].x(); };
    auto yAt = [&polygonPoints](int i) { return polygonPoints[i].y(); };

    for (int y = minY; y <= maxY; y++)
    {
      int nodes = 0;
      addRowCrossings(numOfPoints,y,xAt,yAt,nodeX,nodes);
      fillRow(*this,nodeX,nodes,y,minX,maxX,_fillColor);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief Draws the outlines and fills all polygons in the given polygon path. */

void ImagePaint::paintPolygonPath(std::vector<std::vector<T::Coordinate>>& polygonPath,uint _drawColor,uint _fillColor)
{
  try
  {
    if (mCountingActive)
      return;

    if (polygonPath.empty())
      return;

    int minY = mImageHeight-1;
    int maxY = 0;
    int minX = 0;
    int maxX = mImageWidth-1;
    std::vector<double> nodeX(10000, 0.0);
    std::vector<double> pointsX(200000);
    std::vector<double> pointsY(200000);

    for (auto& polygonPoints : polygonPath)
    {
      if (!polygonPoints.empty())
      {
        // It the last polygon point is not same than the first point, then we should add it to the list.

        closePolygon(polygonPoints);

        // Adding points that are below the polygon line.

        paintOutline(*this,polygonPoints,_drawColor);

        // Adding points that are inside the polygon line.

        updateYRange(polygonPoints,minY,maxY);
      }
    }

    minY = std::max(minY, 0);

    if (maxY >= mImageHeight)
      maxY = mImageHeight - 1;

    auto xAt = [&pointsX](int i) { return pointsX[i]; };
    auto yAt = [&pointsY](int i) { return pointsY[i]; };

    //  Loop through the rows of the image.
    for (int y = minY; y <= maxY; y++)
    {
      //  Build a list of nodes.
      int nodes = 0;
      for (auto& polygonPoints : polygonPath)
      {
        uint numOfPoints = polygonPoints.size();

        uint c = 0;
        for (auto it = polygonPoints.begin(); it != polygonPoints.end(); ++it)
        {
          pointsX[c] = it->x();
          pointsY[c] = it->y();
          c++;

          if (c >= 200000)
          {
            throw Fmi::Exception(BCP,"Not enough space for the point list!",nullptr);
          }
        }

        addRowCrossings(numOfPoints,y,xAt,yAt,nodeX,nodes);
      }

      //  Fill the pixels between node pairs.

      fillRow(*this,nodeX,nodes,y,minX,maxX,_fillColor);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Draws a WKB point geometry from the given memory reader. */

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
      mMinX = std::min(x, mMinX);

      mMaxX = std::max(x, mMaxX);

      mMinY = std::min(y, mMinY);

      mMaxY = std::max(y, mMaxY);
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





/*! \brief Draws a WKB line string geometry from the given memory reader. */

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
        mMinX = std::min(x, mMinX);

        mMaxX = std::max(x, mMaxX);

        mMinY = std::min(y, mMinY);

        mMaxY = std::max(y, mMaxY);
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



/*! \brief Draws a WKB linear ring (polygon ring) geometry from the given memory reader. */

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
        mMinX = std::min(x, mMinX);

        mMaxX = std::max(x, mMaxX);

        mMinY = std::min(y, mMinY);

        mMaxY = std::max(y, mMaxY);
      }
      else
      {
        polygonPoints.emplace_back(x,y);
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





/*! \brief Draws a WKB polygon geometry by painting each of its rings. */

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





/*! \brief Draws a WKB multipoint geometry from the given memory reader. */

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





/*! \brief Draws a WKB multilinestring geometry from the given memory reader. */

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





/*! \brief Draws a WKB multipolygon geometry from the given memory reader. */

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
            mMinX = std::min(x, mMinX);

            mMaxX = std::max(x, mMaxX);

            mMinY = std::min(y, mMinY);

            mMaxY = std::max(y, mMaxY);
          }
          else
          {
            polygonPoints.emplace_back(x,y);
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





/*! \brief Draws a WKB geometry collection by recursively painting each contained geometry. */

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





/*! \brief Dispatches WKB geometries from the reader to their type-specific painters until the buffer is consumed. */

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

      //printf("Type:%u\n",wkbType);
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
        default:
          break;
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Draws the WKB geometry stored in the given raw byte buffer. */

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





/*! \brief Draws the WKB geometry stored in the given byte vector. */

void ImagePaint::paintWkb(double _mpx,double _mpy,double _dx,double _dy,T::ByteData& _wkb)
{
  FUNCTION_TRACE
  try
  {
    size_t sz = _wkb.size();
    if (sz == 0)
      return;

    auto *buf = new uchar[sz];
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





/*! \brief Draws every WKB geometry stored in the given vector of byte buffers. */

void ImagePaint::paintWkb(double _mpx,double _mpy,double _dx,double _dy,T::ByteData_vec& _wkbVec)
{
  FUNCTION_TRACE
  try
  {
    for (auto& it : _wkbVec)
    {
      paintWkb(_mpx,_mpy,_dx,_dy,it);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Computes the bounding box of a WKB geometry without actually drawing it. */

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



/*! \brief Saves the current image buffer as a JPEG file. */

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





/*! \brief Saves the current image buffer as a PNG file. */

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


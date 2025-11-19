#include "GraphFunctions.h"
#include "ImageFunctions.h"
#include "ImagePaint.h"
#include "MemoryReader.h"
#include "MemoryWriter.h"
#include "GeneralFunctions.h"
#include "AutoThreadLock.h"
#include "ShowFunction.h"
#include "InterpolationFunctions.h"

#include <trax/Grid.h>
#include <trax/Contour.h>
#include <trax/IsolineValues.h>
#include <trax/IsobandLimits.h>
#include <fmt/format.h>
#include <cmath>
#include <vector>

#include <math.h>
#include <sstream>
#include <stack>

#include <geos/io/WKBWriter.h>
#include <geos/version.h>
#include <macgyver/Exception.h>
#include <macgyver/FastMath.h>
#include <macgyver/Cache.h>
#include <boost/algorithm/string/replace.hpp>
#include <macgyver/Hash.h>

#define FUNCTION_TRACE FUNCTION_TRACE_OFF

namespace SmartMet
{

typedef std::shared_ptr<geos::geom::Geometry> GeometryPtr;

Fmi::Cache::Cache<std::size_t, std::vector<T::Point>> gridPointsCache(300);

class TraxGrid: public Trax::Grid
{
  public:
    TraxGrid(std::vector<float> *gridData, std::vector<T::Coordinate> *coordinates, long width, long height)
    {
      mGridData = gridData;
      mCoordinates = coordinates;
      mWidth = width;
      mHeight = height;
    }

    std::size_t width() const override
    {
      return mWidth;
    }

    std::size_t height() const override
    {
      return mHeight;
    }

    double x(long i, long j) const override
    {
      if (mCoordinates == nullptr)
        return i;

      return (*mCoordinates)[i + mWidth * j].x();
    }

    double y(long i, long j) const override
    {
      if (mCoordinates == nullptr)
        return j;

      return (*mCoordinates)[i + mWidth * j].y();
    }

    float operator()(long i, long j) const override
    {
      T::ParamValue v = (*mGridData)[i + mWidth * j];
      if (v == ParamValueMissing)
        return NAN;

      return v;
    }

    float get(long i, long j) const
    {
      T::ParamValue v = (*mGridData)[i + mWidth * j];
      if (v == ParamValueMissing)
        return NAN;

      return v;
    }

    void set(long i, long j, float z) override
    {
      (*mGridData)[i + mWidth * j] = z;
    }

    void set(long i, long j, double x, double y)
    {
      (*mCoordinates)[i + mWidth * j].set(x, y);
    }

    bool valid(long i, long j) const override
    {
      return !std::isnan(get(i, j)) && !std::isnan(get(i + 1, j)) && !std::isnan(get(i, j + 1)) && !std::isnan(get(i + 1, j + 1)) && !std::isnan(x(i, j))
          && !std::isnan(x(i + 1, j)) && !std::isnan(x(i, j + 1)) && !std::isnan(x(i + 1, j + 1)) && !std::isnan(y(i, j)) && !std::isnan(y(i + 1, j)) && !std::isnan(y(i, j + 1))
          && !std::isnan(y(i + 1, j + 1));
    }

    std::string dump(const std::string &indent) const
    {
      std::string out;
      for (long j = mHeight - 1; j >= 0; j--)
      {
        for (long i = 0; i < mWidth; i++)
        {
          if (i == 0)
            out += indent;
          else
            out += ' ';
          out += fmt::format("{}", (*this)(i, j));
        }
        out += '\n';
      }
      return out;
    }

  private:
    std::vector<float> *mGridData;
    std::vector<T::Coordinate> *mCoordinates;
    long mWidth;
    long mHeight;
};

extern void convertWkbCoordinates(MemoryReader &_memoryReader, MemoryWriter &_memoryWriter, OGRCoordinateTransformation &_transformation);

static int compare_points(const void *p1, const void *p2)
{
  const double *v1 = (const double*) p1;
  const double *v2 = (const double*) p2;

  if (*v1 < *v2)
    return -1;

  if (*v1 > *v2)
    return 1;

  return 0;
}



void addLine(double x1, double y1, double x2, double y2, std::set<unsigned long long> &cList)
{
  try
  {
    if (y2 < y1)
    {
      double tx = x1;
      double ty = y1;
      x1 = x2;
      y1 = y2;
      x2 = tx;
      y2 = ty;
    }

    if (x1 == x2 && (x1 - round(x1)) == 0)
    {
      int yStart = C_INT(y1 + 0.5);
      if ((y1 - yStart) > 0)
        yStart++;

      int yEnd = Fmi::floor(y2);

      for (int y = yStart; y <= yEnd; y++)
      {
        unsigned long long p = (((unsigned long long) y) << 32) + (unsigned long long) x1;
        //if (cList.find(p) == cList.end())
        cList.insert(p);
      }

      return;
    }

    if (y1 == y2 && (y1 - round(y1)) == 0)
    {
      if (x2 < x1)
      {
        double tx = x1;
        x1 = x2;
        x2 = tx;
      }

      int xStart = C_INT(x1 + 0.5);
      if ((x1 - xStart) > 0)
        xStart++;

      int xEnd = C_INT(Fmi::floor(x2));

      for (int x = xStart; x <= xEnd; x++)
      {
        unsigned long long p = (((unsigned long long) round(y1)) << 32) + (unsigned long long) x;
        //if (cList.find(p) == cList.end())
        cList.insert(p);
      }

      return;
    }

    double dy = (y2 - y1);
    double dx = (x2 - x1);

    double dd = dx / dy;

    int yStart = C_INT(y1 + 0.5);
    if ((y1 - yStart) > 0)
      yStart++;

    int yEnd = C_INT(Fmi::floor(y2));

    for (int y = yStart; y < yEnd; y++)
    {
      double diff = C_DOUBLE(y)- y1;
      double xx = x1 + diff * dd;

      if ((xx - C_INT(xx)) == 0)
      {
        unsigned long long p = (((unsigned long long)y) << 32) + (unsigned long long)xx;
        //if (cList.find(p) == cList.end())
        cList.insert(p);
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void getPointsInsidePolygon(int gridWidth, int gridHeight, T::Coordinate_vec &polygonPoints, std::vector<T::Point> &gridPoints)
{
  try
  {
    uint numOfPoints = polygonPoints.size();
    if (numOfPoints == 0)
      return;

    std::size_t hash = 0;
    Fmi::hash_merge(hash, gridWidth);
    Fmi::hash_merge(hash, gridHeight);

    for (uint t = 0; t < numOfPoints; t++)
    {
      Fmi::hash_merge(hash, polygonPoints[t].x());
      Fmi::hash_merge(hash, polygonPoints[t].y());
    }

    auto it = gridPointsCache.find(hash);
    if (it)
    {
      gridPoints = *it;
      return;
    }

    std::set<unsigned long long> cList;

    // It the last polygon point is not same than the first point, then we should add it to the list.

    if (polygonPoints[0].x() != polygonPoints[numOfPoints - 1].x() || polygonPoints[0].y() != polygonPoints[numOfPoints - 1].y())
    {
      polygonPoints.emplace_back(polygonPoints[0]);
      numOfPoints++;
    }

    // Adding points that are below the polygon line.

    for (uint t = 1; t < numOfPoints; t++)
    {
      addLine(polygonPoints[t - 1].x(), polygonPoints[t - 1].y(), polygonPoints[t].x(), polygonPoints[t].y(), cList);
    }

    // Adding points that are inside the polygon line.

    int maxY = 0;
    int minY = gridHeight - 1;
    int minX = 0;
    int maxX = gridWidth - 1;

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

    if (maxY >= gridHeight)
      maxY = gridHeight - 1;

    double nodeX[10000] =
      { 0 };

    for (int y = minY; y <= maxY; y++)
    {
      int nodes = 0;
      int cnt = numOfPoints;
      int j = cnt - 1;
      for (int i = 0; i < cnt; i++)
      {
        double xi = polygonPoints[i].x();
        double yi = polygonPoints[i].y();

        double xj = polygonPoints[j].x();
        double yj = polygonPoints[j].y();

        double dy = C_DOUBLE(y);

        if ((yi < dy && yj >= dy) || (yj < dy && yi >= dy))
        {
          double xx = C_DOUBLE(xi + (y - yi) / (yj - yi) * (xj - xi));
          nodeX[nodes++] = C_DOUBLE(xx);
        }
        j = i;
      }

      qsort(&nodeX, nodes, sizeof(double), compare_points);

      for (int i = 0; i < nodes; i += 2)
      {
        if (nodeX[i] >= maxX || (i + 1) > nodes)
          break;

        if (nodeX[i + 1] > minX)
        {
          if (nodeX[i] < minX)
            nodeX[i] = minX;

          if (nodeX[i + 1] > maxX)
            nodeX[i + 1] = maxX;

          int xStart = C_INT(nodeX[i]);
          int xEnd = C_INT(nodeX[i + 1]);

          if ((nodeX[i] - xStart) > 0)
            xStart++;

          if ((xEnd - nodeX[i + 1]) > 0)
            xEnd--;

          for (int x = xStart; x <= xEnd; x++)
          {
            unsigned long long p = (C_UINT64(y)<< 32) + (unsigned long long)x;
            //if (cList.find(p) == cList.end())
            cList.insert(p);
          }
        }
      }
    }

    // Converting the list to the actual PointList.

    for (auto it = cList.begin(); it != cList.end(); ++it)
    {
      int y = C_INT((*it) >> 32);
      int x = C_INT((*it) & 0xFFFFFFFF);

      gridPoints.emplace_back(x, y);
    }

    gridPointsCache.insert(hash, gridPoints);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void getPointsInsidePolygonPath(int gridWidth, int gridHeight, T::Polygon_vec &polygonPath, std::vector<T::Point> &gridPoints)
{
  try
  {
    if (polygonPath.size() == 0)
      return;

    std::size_t hash = 0;
    Fmi::hash_merge(hash, gridWidth);
    Fmi::hash_merge(hash, gridHeight);
    for (auto polygonPoints = polygonPath.begin(); polygonPoints != polygonPath.end(); ++polygonPoints)
    {
      uint numOfPoints = polygonPoints->size();
      for (uint t = 0; t < numOfPoints; t++)
      {
        Fmi::hash_merge(hash, (*polygonPoints)[t].x());
        Fmi::hash_merge(hash, (*polygonPoints)[t].y());
      }
    }

    auto it = gridPointsCache.find(hash);
    if (it)
    {
      gridPoints = *it;
      return;
    }

    std::set<unsigned long long> cList;

    int minY = gridHeight - 1;
    int maxY = 0;
    int minX = 0;
    int maxX = gridWidth - 1;
    double nodeX[10000] =
      { 0 };
    double pointsX[200000];
    double pointsY[200000];

    for (auto polygonPoints = polygonPath.begin(); polygonPoints != polygonPath.end(); ++polygonPoints)
    {
      uint numOfPoints = polygonPoints->size();

      if (numOfPoints > 0)
      {
        // It the last polygon point is not same than the first point, then we should add it to the list.

        if ((*polygonPoints)[0].x() != (*polygonPoints)[numOfPoints - 1].x() || (*polygonPoints)[0].y() != (*polygonPoints)[numOfPoints - 1].y())
        {
          (*polygonPoints).emplace_back((*polygonPoints)[0]);
          numOfPoints++;
        }

        // Adding points that are below the polygon line.

        for (uint t = 1; t < numOfPoints; t++)
        {
          addLine((*polygonPoints)[t - 1].x(), (*polygonPoints)[t - 1].y(), (*polygonPoints)[t].x(), (*polygonPoints)[t].y(), cList);
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

    if (maxY >= gridHeight)
      maxY = gridHeight - 1;

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
            throw Fmi::Exception(BCP, "Not enough space for the point list!", nullptr);
          }
        }

        int cnt = numOfPoints;
        int j = cnt - 1;
        for (int i = 0; i < cnt; i++)
        {
          double xi = pointsX[i];
          double yi = pointsY[i];

          double xj = pointsX[j];
          double yj = pointsY[j];

          double dy = C_DOUBLE(y);

          if ((yi < dy && yj >= dy) || (yj < dy && yi >= dy))
          {
            double xx = C_DOUBLE(xi + (y - yi) / (yj - yi) * (xj - xi));
            nodeX[nodes++] = C_DOUBLE(xx);
          }
          j = i;
        }
      }
      qsort(&nodeX, nodes, sizeof(double), compare_points);

      //  Fill the pixels between node pairs.

      for (int i = 0; i < nodes; i += 2)
      {
        if (nodeX[i] >= maxX || (i + 1) > nodes)
          break;

        if (nodeX[i + 1] > minX)
        {
          if (nodeX[i] < minX)
            nodeX[i] = minX;

          if (nodeX[i + 1] > maxX)
            nodeX[i + 1] = maxX;

          int xStart = C_INT(nodeX[i]);
          int xEnd = C_INT(nodeX[i + 1]);

          if ((nodeX[i] - xStart) > 0)
            xStart++;

          if ((xEnd - nodeX[i + 1]) > 0)
            xEnd--;

          for (int x = xStart; x <= xEnd; x++)
          {
            unsigned long long p = (C_UINT64(y)<< 32) + x;
            //if (cList.find(p) == cList.end())
            cList.insert(p);
          }
        }
      }
    }

    // Converting the list to the actual PointList.

    for (auto it = cList.begin(); it != cList.end(); ++it)
    {
      int y = C_INT((*it) >> 32);
      int x = C_INT((*it) & 0xFFFFFFFF);

      gridPoints.emplace_back(x, y);
    }

    gridPointsCache.insert(hash, gridPoints);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void getPointsInsideCircle(int gridWidth, int gridHeight, double origoX, double origoY, double radius, std::vector<T::Point> &gridPoints)
{
  try
  {
    double x1 = origoX - radius;
    double y1 = origoY - radius;
    double x2 = origoX + radius;
    double y2 = origoY + radius;

    double rr = radius * radius;

    if (x1 < 0)
      x1 = 0;

    if (y1 < 0)
      y1 = 0;

    if (x2 >= gridWidth)
      x2 = gridWidth - 1;

    if (y2 >= gridHeight)
      y2 = gridHeight - 1;

    int xx1 = C_INT(x1);
    int xx2 = C_INT(x2);
    int yy1 = C_INT(y1);
    int yy2 = C_INT(y2);

    for (int y = yy1; y <= yy2; y++)
    {
      double dy = C_DOUBLE(y)-origoY;
      for (int x=xx1; x<=xx2; x++)
      {
        double dx = C_DOUBLE(x)-origoX;
        double r2 = dx*dx + dy*dy;

        if (r2 <= rr)
        {
          // Point is inside the circle.
          gridPoints.emplace_back(x,y);
        }
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



std::size_t getPolygonPathLength(T::Polygon_vec &polygonPath)
{
  try
  {
    std::size_t s = 0;
    for (auto coordinates = polygonPath.begin(); coordinates != polygonPath.end(); ++coordinates)
    {
      s = s + coordinates->size();
    }
    return s;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void convertToPointVector(T::Polygon_vec &polygonPath, T::Coordinate_vec &polygonPoints)
{
  try
  {
    for (auto coordinates = polygonPath.begin(); coordinates != polygonPath.end(); ++coordinates)
    {
      for (auto cc = coordinates->begin(); cc != coordinates->end(); ++cc)
        polygonPoints.emplace_back(*cc);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void convertSvgPathToPolygonPath(NFmiSvgPath &svgPath, T::Polygon_vec &polygonPath)
{
  try
  {
    T::Coordinate_vec polygonPoints;

    for (auto it = svgPath.begin(); it != svgPath.end(); ++it)
    {
      switch (it->itsType)
      {
        case NFmiSvgPath::kElementMoveto:
          if (polygonPoints.size() > 0)
          {
            polygonPath.emplace_back(polygonPoints);
            polygonPoints.clear();
          }
          polygonPoints.emplace_back(it->itsX, it->itsY);
          break;

        case NFmiSvgPath::kElementClosePath:
          if (polygonPoints.size() > 0)
          {
            int t = C_INT(polygonPoints.size())-1;
            if (t > 0 && (polygonPoints[0].x() != polygonPoints[t].x() || polygonPoints[0].y() != polygonPoints[t].y()))
            polygonPoints.emplace_back(polygonPoints[0]);

            polygonPath.emplace_back(polygonPoints);
            polygonPoints.clear();
          }

          polygonPoints.clear();
          break;

          case NFmiSvgPath::kElementLineto:
          polygonPoints.emplace_back(it->itsX,it->itsY);
          break;

          case NFmiSvgPath::kElementNotValid:
          return;
        }
      }
    if (polygonPoints.size() > 0)
      polygonPath.emplace_back(polygonPoints);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



std::string convertWktMultiPolygonToSvgString(const std::string &wktString)
{
  try
  {
    std::string svgString = wktString;
    boost::algorithm::replace_all(svgString, "MULTIPOLYGON ", "");
    boost::algorithm::replace_all(svgString, "POLYGON ", "");
    boost::algorithm::replace_all(svgString, "),(", " Z M ");
    boost::algorithm::replace_all(svgString, ",", " L ");
    boost::algorithm::replace_all(svgString, "(", "");
    boost::algorithm::replace_all(svgString, ")", "");
    svgString.insert(0, "\"M ");
    svgString.append(" Z\"\n");

    return svgString;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void convertWktMultipolygonToSvgPath(const std::string &wktString, NFmiSvgPath &svgPath)
{
  try
  {
    std::string svgString = convertWktMultiPolygonToSvgString(wktString);
    std::stringstream svgStringStream(svgString);

    svgPath.Read(svgStringStream);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void convertWktMultipolygonToPolygonPath(const std::string &wktString, T::Polygon_vec &polygonPath)
{
  try
  {
    std::string svgString = convertWktMultiPolygonToSvgString(wktString);
    std::stringstream svgStringStream(svgString);

    NFmiSvgPath svgPath;
    svgPath.Read(svgStringStream);
    convertSvgPathToPolygonPath(svgPath, polygonPath);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



bool getLineIntersection(double ax1, double ay1, double ax2, double ay2, double bx1, double by1, double bx2, double by2, double &x, double &y)
{
  try
  {
    if (ax1 == ax2 && ay1 == ay2)
      return false; // Undefined line a

    if (bx1 == bx2 && by1 == by2)
      return false; // Undefined line b

    //  Translate the lines so that point x1,y1 is on the origin.

    ax2 -= ax1;
    ay2 -= ay1;
    bx1 -= ax1;
    by1 -= ay1;
    bx2 -= ax1;
    by2 -= ay1;

    double da = sqrt(ax2 * ax2 + ay2 * ay2);
    double aCos = ax2 / da;
    double aSin = ay2 / da;
    double newX = bx1 * aCos + by1 * aSin;

    by1 = by1 * aCos - bx1 * aSin;
    bx1 = newX;
    newX = bx2 * aCos + by2 * aSin;
    by2 = by2 * aCos - bx2 * aSin;
    bx2 = newX;

    if (by1 == by2)
      return false;  // The lines are parallel

    double pos = bx2 + (bx1 - bx2) * by2 / (by2 - by1);

    x = ax1 + pos * aCos;
    y = ay1 + pos * aSin;

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



bool getLineIntersection(std::pair<T::Coordinate, T::Coordinate> line1, std::pair<T::Coordinate, T::Coordinate> line2, T::Coordinate &intersection)
{
  try
  {
    double ix = 0;
    double iy = 0;

    bool res = getLineIntersection(line1.first.x(), line1.first.y(), line1.second.x(), line1.second.y(), line2.first.x(), line2.first.y(), line2.second.x(), line2.second.y(), ix,
        iy);
    if (res)
      intersection.set(ix, iy);
    return res;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void getPointMovement(double x1, double y1, double x2, double y2, double areaExtensionX, double areaExtensionY, double &mx, double &my)
{
  try
  {
    double PI = 3.1415927;

    double dx = fabs(x2 - x1);
    double dy = fabs(y2 - y1);

    double a = atan(dx / dy);
    double b = PI / 2 - a;

    double areaExtension_y = cos(b) * areaExtensionY;
    double areaExtension_x = sin(b) * areaExtensionX;

    if (x1 == x2)
    {
      if (y1 > y2)
      {
        mx = areaExtensionX;
        my = 0;
        return;
      }
      else
      {
        mx = -areaExtensionX;
        my = 0;
        return;
      }
    }

    if (y1 == y2)
    {
      if (x1 > x2)
      {
        mx = 0;
        my = -areaExtensionY;
        return;
      }
      else
      {
        mx = 0;
        my = areaExtensionY;
        return;
      }
    }

    if (x1 < x2)
    {
      if (y1 > y2)
      {
        mx = areaExtension_x;
        my = areaExtension_y;
        return;
      }
      else
      {
        mx = -areaExtension_x;
        my = areaExtension_y;
        return;
      }
    }

    if (x1 > x2)
    {
      if (y1 > y2)
      {
        mx = areaExtension_x;
        my = -areaExtension_y;
        return;
      }
      else
      {
        mx = -areaExtension_x;
        my = -areaExtension_y;
        return;
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void getPointMovementRev(double x1, double y1, double x2, double y2, double areaExtensionX, double areaExtensionY, double &mx, double &my)
{
  try
  {
    double PI = 3.1415927;

    double dx = fabs(x2 - x1);
    double dy = fabs(y2 - y1);

    double a = atan(dx / dy);
    double b = PI / 2 - a;

    double areaExtension_y = cos(b) * areaExtensionY;
    double areaExtension_x = sin(b) * areaExtensionX;

    if (x1 == x2)
    {
      if (y1 > y2)
      {
        mx = -areaExtensionX;
        my = 0;
        return;
      }
      else
      {
        mx = areaExtensionX;
        my = 0;
        return;
      }
    }

    if (y1 == y2)
    {
      if (x1 > x2)
      {
        mx = 0;
        my = areaExtensionY;
        return;
      }
      else
      {
        mx = 0;
        my = -areaExtensionY;
        return;
      }
    }

    if (x1 < x2)
    {
      if (y1 > y2)
      {
        mx = -areaExtension_x;
        my = -areaExtension_y;
        return;
      }
      else
      {
        mx = areaExtension_x;
        my = -areaExtension_y;
        return;
      }
    }

    if (x1 > x2)
    {
      if (y1 > y2)
      {
        mx = -areaExtension_x;
        my = areaExtension_y;
        return;
      }
      else
      {
        mx = areaExtension_x;
        my = areaExtension_y;
        return;
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



T::Coordinate_vec getEnlargedPolygon(T::Coordinate_vec &oldCoordinates, double areaExtensionX, double areaExtensionY, bool rev)
{
  try
  {
    T::Coordinate_vec newCoordinates;

    std::vector<std::pair<T::Coordinate, T::Coordinate>> tmpLines;
    int points = C_INT(oldCoordinates.size());
    for (int t = 0; t < points - 1; t++)
    {
      auto p1 = oldCoordinates[t];
      auto p2 = oldCoordinates[t + 1];

      double mx = 0;
      double my = 0;

      if (rev)
        getPointMovementRev(p1.x(), p1.y(), p2.x(), p2.y(), areaExtensionX, areaExtensionY, mx, my);
      else
        getPointMovement(p1.x(), p1.y(), p2.x(), p2.y(), areaExtensionX, areaExtensionY, mx, my);

      T::Coordinate n1(p1.x() + mx, p1.y() + my);
      T::Coordinate n2(p2.x() + mx, p2.y() + my);

      tmpLines.emplace_back(n1, n2);
    }

    int lines = C_INT(tmpLines.size());
    for (int t = 0; t < lines; t++)
    {
      T::Coordinate point;
      if ((t + 1) < lines)
      {
        if (getLineIntersection(tmpLines[t], tmpLines[t + 1], point))
          newCoordinates.emplace_back(point);
      }
      else
      {
        if (getLineIntersection(tmpLines[t], tmpLines[0], point))
        {
          newCoordinates.emplace_back(point);
          newCoordinates.insert(newCoordinates.begin(), point);
        }
      }
    }

    return newCoordinates;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



double getPolygonLen(T::Coordinate_vec &coordinates)
{
  try
  {
    int points = C_INT(coordinates.size());
    double len = 0;
    for (int t = 0; t < points - 1; t++)
    {
      auto p1 = coordinates[t];
      auto p2 = coordinates[t + 1];

      double dx = p2.x() - p1.x();
      double dy = p2.y() - p1.y();

      len = len + sqrt(dx * dx + dy * dy);
    }
    return len;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



T::Coordinate_vec getEnlargedPolygon(T::Coordinate_vec &oldCoordinates, double areaExtensionX, double areaExtensionY)
{
  try
  {
    std::vector<T::Coordinate> newCoordinates;

    double oldLen = getPolygonLen(oldCoordinates);
    newCoordinates = getEnlargedPolygon(oldCoordinates, areaExtensionX, areaExtensionY, false);
    double newLen = getPolygonLen(newCoordinates);

    if (areaExtensionX > 0 && newLen < oldLen)
      return getEnlargedPolygon(oldCoordinates, areaExtensionX, areaExtensionY, true);

    if (areaExtensionX < 0 && newLen > oldLen)
      return getEnlargedPolygon(oldCoordinates, areaExtensionX, areaExtensionY, true);

    return newCoordinates;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



T::Polygon_vec getEnlargedPolygonPath(T::Polygon_vec &oldPath, double areaExtensionX, double areaExtensionY)
{
  try
  {
    T::Polygon_vec newPath;

    for (auto coordinates = oldPath.begin(); coordinates != oldPath.end(); ++coordinates)
    {
      T::Coordinate_vec newCoordinates = getEnlargedPolygon(*coordinates, areaExtensionX, areaExtensionY);
      newPath.emplace_back(newCoordinates);
    }
    return newPath;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void getIsolines(std::vector<float> &gridData, T::Coordinate_vec *coordinates, int width, int height, std::vector<float> &contourValues, short interpolationMethod,
    size_t smooth_size, size_t smooth_degree, T::ByteData_vec &contours)
{
  try
  {
    size_t sz = gridData.size();
    size_t requiredSize = width * height;
    size_t csz = 0;
    if (coordinates)
      csz = coordinates->size();

    if (sz == 0 || sz != requiredSize || sz != csz)
      return;

    Trax::Contour contourer;
    contourer.interpolation((Trax::InterpolationType) interpolationMethod);

    TraxGrid grid(&gridData, coordinates, width, height);

    Trax::IsolineValues isolineValues;
    for (auto v = contourValues.begin(); v != contourValues.end(); v++)
      isolineValues.add(*v);

    auto result = contourer.isolines(grid, isolineValues);

    //ImagePaint paint(3600,1800,0xFFFFFF,0xFF0000,0x0000FF,false,false);
    if (result.size() > 0)
    {
      for (auto g = result.begin(); g != result.end(); ++g)
      {
        std::ostringstream out;
        g->wkb(out);
        const auto &wkb = out.str();
        size_t size = wkb.length();

        T::ByteData wkbData;
        if (size > 0)
        {
          const auto &wkb = out.str();
          unsigned char *data = reinterpret_cast<unsigned char*>(const_cast<char*>(wkb.c_str()));

          //paint.paintWkb(1,1,0,0,data,size);

          wkbData.reserve(size);
          for (size_t t = 0; t < size; t++)
            wkbData.emplace_back(data[t]);
        }
        contours.emplace_back(wkbData);
      }
    }

    //paint.saveJpgImage("/tmp/TEST.jpg");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void getIsobands(std::vector<float> &gridData, std::vector<T::Coordinate> *coordinates, int width, int height, std::vector<float> &contourLowValues,
    std::vector<float> &contourHighValues, short interpolationMethod, size_t smooth_size, size_t smooth_degree, T::ByteData_vec &contours)
{
  try
  {
    size_t sz = gridData.size();
    size_t requiredSize = width * height;
    size_t csz = 0;
    if (coordinates)
      csz = coordinates->size();

    if (sz == 0 || sz != requiredSize || sz != csz)
      return;

    Trax::Contour contourer;
    contourer.interpolation((Trax::InterpolationType) interpolationMethod);

    TraxGrid grid(&gridData, coordinates, width, height);
    Trax::IsobandLimits limits;

    uint cnt = contourLowValues.size();
    for (uint t = 0; t < cnt; t++)
      limits.add(contourLowValues[t], contourHighValues[t]);

    auto result = contourer.isobands(grid, limits);

#if 0
    width = width*2;
    height = height*2;

    bool autoscale = true;
    double ww = width;
    double hh = height;
    double dx = 0;
    double dy = 0;
    double ss = 1;

    ImagePaint paint(width,height,0xFFFFFF,0xFF0000,0x0000FF,false,true);
    if (result.size() > 0)
    {
      double tminX = 0, tminY = 0, tmaxX = 0, tmaxY = 0;
      if (autoscale)
      {
        tminX = 1000000000;
        tminY = 1000000000;
        tmaxX = -1000000000;
        tmaxY = -1000000000;

        std::ostringstream out;

        for (auto g = result.begin(); g != result.end(); ++g)
        {
          g->wkb(out);
          const auto &wkb = out.str();
          unsigned char *data = reinterpret_cast<unsigned char *>(const_cast<char *>(wkb.c_str()));
          size_t size = wkb.length();

          double minX = 0, minY = 0, maxX = 0, maxY = 0;
          paint.countPaintWkbArea(data,size,minX,minY,maxX,maxY);


          if (minX < tminX)
            tminX = minX;

          if (minY < tminY)
            tminY = minY;

          if (maxX > tmaxX)
            tmaxX = maxX;

          if (maxY > tmaxY)
            tmaxY = maxY;
        }
      }

      if (autoscale)
      {
        dx = -tminX;
        dy = -tminY;

        ww = tmaxX - tminX;
        hh = tmaxY - tminY;
      }

      double sx = (width-20)/ww;
      double sy = (height-20)/hh;

      ss = sx;
      if (sy < sx)
        ss = sy;

      ImagePaint ipaint(width,height,0xFFFFFF,0xFF0000,0x0000FF,false,true);

      uint c = 0;
      for (auto g = result.begin(); g != result.end(); ++g)
      {
        std::ostringstream out;

        g->wkb(out);
        const auto &wkb = out.str();
        size_t size = wkb.length();

        if (size > 0)
        {
          unsigned char *data = reinterpret_cast<unsigned char *>(const_cast<char *>(wkb.c_str()));

          uint fillCol = (rand() << 8) + rand();
          ipaint.setDrawColor(fillCol);
          ipaint.setFillColor(fillCol);

          ipaint.paintWkb(ss, ss, dx+10/ss, dy+10/ss,data,size);
        }
/*
        char filename[100];
        sprintf(filename,"/tmp/TEST_%04u.jpg",c);
        ipaint.saveJpgImage(filename);
        c++;
        */
      }
      ipaint.saveJpgImage("/tmp/TEST.jpg");
    }

#endif

    if (result.size() > 0)
    {
      for (auto g = result.begin(); g != result.end(); ++g)
      {
        std::ostringstream out;

        g->wkb(out);
        const auto &wkb = out.str();
        size_t size = wkb.length();

        T::ByteData wkbData;
        if (size > 0)
        {
          const auto &wkb = out.str();
          unsigned char *data = reinterpret_cast<unsigned char*>(const_cast<char*>(wkb.c_str()));

          wkbData.reserve(size);
          for (size_t t = 0; t < size; t++)
            wkbData.emplace_back(data[t]);
        }
        contours.emplace_back(wkbData);
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



bool getLineIntersectionPoint(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double &x, double &y)
{
  try
  {
    //printf("getLineIntersectionPoint(%f,%f - %f,%f    %f,%f - %f,%f\n",x1,y1,x2,y2,x3,y3,x4,y4);

    int k1 = (int) (10000 * (x2 - x1) / (y2 - y1));
    int k2 = (int) (10000 * (x4 - x3) / (y4 - y3));
    if (k1 == k2)  // No intersection
      return false;

    double a = (x1 * y2 - y1 * x2);
    double b = (x3 * y4 - y3 * x4);
    double c = ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

    x = (a * (x3 - x4) - (x1 - x2) * b) / c;
    y = (a * (y3 - y4) - (y1 - y2) * b) / c;

    //printf("*** getLineIntersectionPoint(%f,%f - %f,%f    %f,%f - %f,%f     %f,%f\n",x1,y1,x2,y2,x3,y3,x4,y4,x,y);

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



int findPath(std::vector<float> &direction, bool *visited, int width, int height, int maxLength, double x1, double y1, int level, uint cellCount,
    std::vector<T::Coordinate> &coordinates)
{
  try
  {
    float PI = 3.14159265358979;
    if (level == maxLength)
    {
      //printf("MAXLEN %u\n\n",level);
      return cellCount;
    }

    int xx = (int) x1;
    int yy = (int) y1;
    double xo = xx;
    double yo = yy;

    if (xx >= width || yy >= height)
    {
      //printf("OUT %u\n\n",level);
      return cellCount;
    }

    int idx = yy * width + xx;
    if (visited[idx])
    {
      //printf("COLLISION %u\n\n",level);
      return cellCount;
    }

    // Original angle indicates "the from direction". For example, wind blows
    // from that direction - not to that direction. Notice also that the starting
    // point of the angle is different than usual.
    //
    //
    //                      N = 0
    //                        |   /
    //                        |  /
    //                        |a/
    //       W = 270 ---------+--------- E = 90
    //                        |
    //                        |
    //                        |
    //                      S=180
    //

    double dat = direction[idx];  // "From direction"
    if (dat == ParamValueMissing)
      return cellCount;

    coordinates.push_back(T::Coordinate(x1, y1));

    if (!visited[idx])
      cellCount++;

    visited[idx] = true;

    double a = (dat + 180); // "To direction"
    if (a > 360)
      a = a - 360;

    // Defining a line

    double angle = 2 * PI * a / 360;  // "To direction" in radians.
    double step = 10;
    double x2 = x1 + sin(angle) * step;
    double y2 = y1 - cos(angle) * step;

    double ix;
    double iy;
    bool sec;

    /*

     sec[0] =  getLineIntersectionPoint(x1,y1,x2,y2,xo-0.001,0,xo-0.001,10,ix[0],iy[0]);     // Left
     sec[1] =  getLineIntersectionPoint(x1,y1,x2,y2,xo+1.001,0,xo+1.001,10,ix[1],iy[1]);     // Right
     sec[2] =  getLineIntersectionPoint(x1,y1,x2,y2,0,yo-0.001,10,yo-0.001,ix[2],iy[2]);     // Top
     sec[3] =  getLineIntersectionPoint(x1,y1,x2,y2,0,yo+1.001,10,yo+1.001,ix[3],iy[3]);     // Bottom

     double dist[4];
     dist[0] = (x1-ix[0])*(x1-ix[0]) + (y1-iy[0])*(y1-iy[0]);
     dist[1] = (x1-ix[1])*(x1-ix[1]) + (y1-iy[1])*(y1-iy[1]);
     dist[2] = (x1-ix[2])*(x1-ix[2]) + (y1-iy[2])*(y1-iy[2]);
     dist[3] = (x1-ix[3])*(x1-ix[3]) + (y1-iy[3])*(y1-iy[3]);

     for (uint t=0; t<4; t++)
     {
     printf("-- Intersec %f,%f-%f,%f  %f,%f  %d  angle %f %f  dist %f\n",x1,y1,x2,y2,ix[t],iy[t],sec[t],angle,direction[idx],dist[t]);
     }
     */

    if (a >= 0 && a < 180)
    {
      sec = getLineIntersectionPoint(x1, y1, x2, y2, xo + 1.001, 0, xo + 1.001, 10, ix, iy);
      if (sec && (int) iy == (int) y1)
      {
        // Right
        //printf("RIGHT %f   %f,%f => %f,%f\n",a,x1,y1,ix,iy);
        return findPath(direction, visited, width, height, maxLength, ix, iy, level + 1, cellCount, coordinates);
      }

      if (a >= 0 && a < 90)
      {
        // Top
        sec = getLineIntersectionPoint(x1, y1, x2, y2, 0, yo - 0.001, 10, yo - 0.001, ix, iy);
        if (sec && (int) ix == (int) x1)
        {
          //printf("UP %f   %f,%f => %f,%f\n",a,x1,y1,ix,iy);
          return findPath(direction, visited, width, height, maxLength, ix, iy, level + 1, cellCount, coordinates);
        }
      }
      else
      {
        sec = getLineIntersectionPoint(x1, y1, x2, y2, 0, yo + 1.001, 10, yo + 1.001, ix, iy);
        if (sec && (int) ix == (int) x1)
        {
          //printf("DOWN %f   %f,%f => %f,%f\n",a,x1,y1,ix,iy);
          return findPath(direction, visited, width, height, maxLength, ix, iy, level + 1, cellCount, coordinates);
        }
      }
    }
    else
    {
      sec = getLineIntersectionPoint(x1, y1, x2, y2, xo - 0.001, 0, xo - 0.001, 10, ix, iy);
      if (sec && (int) iy == (int) y1)
      {
        // Left
        //printf("LEFT %f   %f,%f => %f,%f\n",a,x1,y1,ix,iy);
        return findPath(direction, visited, width, height, maxLength, ix, iy, level + 1, cellCount, coordinates);
      }

      if (a >= 270 && a < 360)
      {
        sec = getLineIntersectionPoint(x1, y1, x2, y2, 0, yo - 0.001, 10, yo - 0.001, ix, iy);
        if (sec && (int) ix == (int) x1)
        {
          //printf("XUP %f   %f,%f => %f,%f\n",a,x1,y1,ix,iy);
          return findPath(direction, visited, width, height, maxLength, ix, iy, level + 1, cellCount, coordinates);
        }
      }
      else
      {
        sec = getLineIntersectionPoint(x1, y1, x2, y2, 0, yo + 1.001, 10, yo + 1.001, ix, iy);
        if (sec && (int) ix == (int) x1)
        {
          //printf("XDOWN %f   %f,%f => %f,%f\n",a,x1,y1,ix[3],iy[3]);
          return findPath(direction, visited, width, height, maxLength, ix, iy, level + 1, cellCount, coordinates);
        }
      }
    }

    //printf("EXIT %u\n\n",level);
    return cellCount;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



double diff(double a, double b)
{
  if ((int) a == (int) b)
    return 0;

  if (a < b)
    return b - a;

  return a - b;
}



int findPath(float *direction, uint *image, int width, int height, int maxLength, uint backColor, double x1, double y1, int level, uint cellCount,
    std::vector<T::Coordinate> &coordinates)
{
  try
  {
    float PI = 3.14159265358979;
    if (level == maxLength)
      return cellCount;

    uint visited = 0xFFFFFFFE;
    int xx = (int) x1;
    int yy = (int) y1;
    double xo = xx;
    double yo = yy;

    if (xx >= width || yy >= height)
      return cellCount;

    int idx = yy * width + xx;
    if (image[idx] != backColor && image[idx] != visited)
    {
      //Collison
      return cellCount;
    }

    // Original angle indicates "the from direction". For example, wind blows
    // from that direction - not to that direction. Notice also that the starting
    // point of the angle is different than usual.
    //
    //
    //                      N = 0
    //                        |   /
    //                        |  /
    //                        |a/
    //       W = 270 ---------+--------- E = 90
    //                        |
    //                        |
    //                        |
    //                      S=180
    //

    double dat = direction[idx];  // "From direction"
    if (dat == ParamValueMissing)
      return cellCount;

    coordinates.push_back(T::Coordinate(x1, y1));

    if (image[idx] != visited)
      cellCount++;

    image[idx] = visited;

    double a = (dat + 180); // "To direction"
    if (a > 360)
      a = a - 360;

    // Defining a line

    double angle = 2 * PI * a / 360;  // "To direction" in radians.
    double step = 10;
    double x2 = x1 + sin(angle) * step;
    double y2 = y1 - cos(angle) * step;

    double ix;
    double iy;
    bool sec;
    double d0 = 0.000001;
    double d1 = 1.000001;
    double aa = 0.001;

    if (a >= 0 && a < 180)
    {
      sec = getLineIntersectionPoint(x1, y1, x2, y2, xo + d1, 0, xo + d1, 10, ix, iy);
      if (sec && diff(iy, y1) < aa)
      {
        // Right
        return findPath(direction, image, width, height, maxLength, backColor, ix, iy, level + 1, cellCount, coordinates);
      }

      if (a >= 0 && a < 90)
      {
        // Top
        sec = getLineIntersectionPoint(x1, y1, x2, y2, 0, yo - d0, 10, yo - d0, ix, iy);
        if (sec && diff(ix, x1) < aa)
        {
          // Up
          return findPath(direction, image, width, height, maxLength, backColor, ix, iy, level + 1, cellCount, coordinates);
        }
      }
      else
      {
        sec = getLineIntersectionPoint(x1, y1, x2, y2, 0, yo + d1, 10, yo + d1, ix, iy);
        if (sec && diff(ix, x1) < aa)
        {
          // Down
          return findPath(direction, image, width, height, maxLength, backColor, ix, iy, level + 1, cellCount, coordinates);
        }
      }
    }
    else
    {
      sec = getLineIntersectionPoint(x1, y1, x2, y2, xo - d0, 0, xo - d0, 10, ix, iy);
      if (sec && diff(iy, y1) < aa)
      {
        // Left
        return findPath(direction, image, width, height, maxLength, backColor, ix, iy, level + 1, cellCount, coordinates);
      }

      if (a >= 270 && a < 360)
      {
        sec = getLineIntersectionPoint(x1, y1, x2, y2, 0, yo - d0, 10, yo - d0, ix, iy);
        if (sec && diff(ix, x1) < aa)
        {
          // Up
          return findPath(direction, image, width, height, maxLength, backColor, ix, iy, level + 1, cellCount, coordinates);
        }
      }
      else
      {
        sec = getLineIntersectionPoint(x1, y1, x2, y2, 0, yo + d1, 10, yo + d1, ix, iy);
        if (sec && diff(ix, x1) < aa)
        {
          // Down
          return findPath(direction, image, width, height, maxLength, backColor, ix, iy, level + 1, cellCount, coordinates);
        }
      }
    }

    return cellCount;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



int findPath(std::vector<float>& direction, uint *image, int width, int height, int maxLength, uint backColor, double x1, double y1, int level, uint cellCount,
    std::vector<T::Coordinate> &coordinates)
{
  try
  {
    float PI = 3.14159265358979;
    if (level == maxLength)
      return cellCount;

    uint visited = 0xFFFFFFFE;
    int xx = (int) x1;
    int yy = (int) y1;
    double xo = xx;
    double yo = yy;

    if (xx >= width || yy >= height)
      return cellCount;

    int idx = yy * width + xx;
    if (image[idx] != backColor && image[idx] != visited)
    {
      // Collison
      return cellCount;
    }

    // Original angle indicates "the from direction". For example, wind blows
    // from that direction - not to that direction. Notice also that the starting
    // point of the angle is different than usual.
    //
    //
    //                      N = 0
    //                        |   /
    //                        |  /
    //                        |a/
    //       W = 270 ---------+--------- E = 90
    //                        |
    //                        |
    //                        |
    //                      S=180
    //

    double dat = direction[idx];  // "From direction"
    if (dat == ParamValueMissing)
      return cellCount;

    coordinates.push_back(T::Coordinate(x1, y1));

    if (image[idx] != visited)
      cellCount++;

    image[idx] = visited;

    double a = (dat + 180); // "To direction"
    if (a > 360)
      a = a - 360;

    // Defining a line

    double angle = 2 * PI * a / 360;  // "To direction" in radians.
    double step = 10;
    double x2 = x1 + sin(angle) * step;
    double y2 = y1 - cos(angle) * step;

    double ix;
    double iy;
    bool sec;

    double d0 = 0.000001;
    double d1 = 1.000001;
    double aa = 0.001;

    if (a >= 0 && a < 180)
    {
      sec = getLineIntersectionPoint(x1, y1, x2, y2, xo + d1, 0, xo + d1, 10, ix, iy);
      if (sec && diff(iy, y1) < aa)
      {
        // Right
        return findPath(direction, image, width, height, maxLength, backColor, ix, iy, level + 1, cellCount, coordinates);
      }

      if (a >= 0 && a < 90)
      {
        // Top
        sec = getLineIntersectionPoint(x1, y1, x2, y2, 0, yo - d0, 10, yo - d0, ix, iy);
        if (sec && diff(ix, x1) < aa)
        {
          // Up
          return findPath(direction, image, width, height, maxLength, backColor, ix, iy, level + 1, cellCount, coordinates);
        }
      }
      else
      {
        sec = getLineIntersectionPoint(x1, y1, x2, y2, 0, yo + d1, 10, yo + d1, ix, iy);
        if (sec && diff(ix, x1) < aa)
        {
          // Down
          return findPath(direction, image, width, height, maxLength, backColor, ix, iy, level + 1, cellCount, coordinates);
        }
      }
    }
    else
    {
      sec = getLineIntersectionPoint(x1, y1, x2, y2, xo - d0, 0, xo - d0, 10, ix, iy);
      if (sec && diff(iy, y1) < aa)
      {
        // Left
        return findPath(direction, image, width, height, maxLength, backColor, ix, iy, level + 1, cellCount, coordinates);
      }

      if (a >= 270 && a < 360)
      {
        sec = getLineIntersectionPoint(x1, y1, x2, y2, 0, yo - d0, 10, yo - d0, ix, iy);
        if (sec && diff(ix, x1) < aa)
        {
          return findPath(direction, image, width, height, maxLength, backColor, ix, iy, level + 1, cellCount, coordinates);
        }
      }
      else
      {
        sec = getLineIntersectionPoint(x1, y1, x2, y2, 0, yo + d1, 10, yo + d1, ix, iy);
        if (sec && diff(ix, x1) < aa)
        {
          return findPath(direction, image, width, height, maxLength, backColor, ix, iy, level + 1, cellCount, coordinates);
        }
      }
    }
    return cellCount;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void getStreamlineImage(float *direction, float *value, uint *image, int width, int height, int xStep, int yStep, int minLength, int maxLength, float valueRangeStart,
    float valueRangeEnd, int startColor, int endColor, uint backColor)
{
  try
  {
    float valueStep = 255.0 / (valueRangeEnd - valueRangeStart);
    int colorStep = (endColor - startColor) / maxLength;

    int size = width * height;
    for (int t = 0; t < size; t++)
    {
      image[t] = backColor;
    }

    for (int y = 0; y < height; y = y + yStep)
    {
      for (int x = 0; x < width; x = x + xStep)
      {
        std::vector<T::Coordinate> coordinates;
        int cellCount = findPath(direction, image, width, height, maxLength, backColor, (double) x + 0.5, (double) y + 0.5, 0, 0, coordinates);

        float avg = valueRangeStart;
        float total = 0;
        uint c = 0;
        if (cellCount >= minLength && value)
        {
          for (auto it = coordinates.rbegin(); it != coordinates.rend(); ++it)
          {
            int xx = (int) it->x();
            int yy = (int) it->y();
            int idx = yy * width + xx;

            float val = value[idx];
            if (val != ParamValueMissing)
            {
              total = total + val;
              c++;
            }
          }

          if (c > 0)
            avg = total / c;
        }

        c = 0;
        for (auto it = coordinates.rbegin(); it != coordinates.rend(); ++it)
        {
          int xx = (int) it->x();
          int yy = (int) it->y();

          int idx = yy * width + xx;
          if (idx < size)
          {
            if (cellCount < minLength || avg < valueRangeStart)
            {
              image[idx] = backColor;
            }
            else
            {
              float val = valueRangeStart;
              if (value)
                val = value[idx];

              // val = avg;
              if (val == ParamValueMissing || val < valueRangeStart)
                val = valueRangeStart;

              double hh = valueStep * (val - valueRangeStart);
              if (hh > 0xFF)
                hh = 0xFF;

              unsigned char hue = (unsigned char) hh;
              unsigned char saturation = hue;

              // uint pos = c % maxLength;
              uchar v = (uchar) (startColor + (c * colorStep));
              uint col = hsv_to_rgb(hue, saturation, v);

              image[idx] = col;
            }
          }
          c++;
        }
      }
    }

  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void getStreamlineImage(float *direction, float *value, uint *image, int width, int height, int xStep, int yStep, int minLength, int maxLength)
{
  try
  {
    int size = width * height;
    for (int t = 0; t < size; t++)
    {
      image[t] = 0;
    }

    for (int y = 0; y < height; y = y + yStep)
    {
      for (int x = 0; x < width; x = x + xStep)
      {
        std::vector<T::Coordinate> coordinates;
        int cellCount = findPath(direction, image, width, height, maxLength, 0, (double) x + 0.5, (double) y + 0.5, 0, 0, coordinates);

        uint c = 1;
        for (auto it = coordinates.rbegin(); it != coordinates.rend(); ++it)
        {
          int xx = (int) it->x();
          int yy = (int) it->y();

          int idx = yy * width + xx;
          if (idx < size)
          {
            if (cellCount < minLength)
            {
              image[idx] = 0;
            }
            else
            {
              image[idx] = c;
            }
          }
          c++;
        }
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void getStreamlineImage(std::vector<float>& direction, float *value, uint *image, int width, int height, int xStep, int yStep, int minLength, int maxLength)
{
  try
  {
    int size = width * height;
    for (int t = 0; t < size; t++)
    {
      image[t] = 0;
    }

    for (int y = 0; y < height; y = y + yStep)
    {
      for (int x = 0; x < width; x = x + xStep)
      {
        std::vector<T::Coordinate> coordinates;
        int cellCount = findPath(direction, image, width, height, maxLength, 0, (double) x + 0.5, (double) y + 0.5, 0, 0, coordinates);

        uint c = 1;
        for (auto it = coordinates.rbegin(); it != coordinates.rend(); ++it)
        {
          int xx = (int) it->x();
          int yy = (int) it->y();

          int idx = yy * width + xx;
          if (idx < size)
          {
            if (cellCount < minLength)
            {
              image[idx] = 0;
            }
            else
            {
              image[idx] = c;
            }
          }
          c++;
        }
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}



void getStreamlines(T::ParamValue_vec &gridValues, std::vector<T::Coordinate> *coordinates, int width, int height, int minStreamLen, int maxStreamLen, int lineLen, int xStep,
    int yStep, T::ByteData_vec &streamlines)
{
  try
  {
    int sz = width * height;
    float *direction = new float[sz];
    uint *image = new uint[sz];

    for (int t = 0; t < sz; t++)
      image[t] = 0;

    uint idx = 0;
    for (int y = 0; y < height; y++)
    {
      uint idx2 = (height - y - 1) * width;
      for (int x = 0; x < width; x++)
      {
        direction[idx] = gridValues[idx2];
        idx++;
        idx2++;
      }
    }

    uint dataSize = 100000;
    uchar data[dataSize];

    for (int y = 0; y <= height; y = y + yStep)
    {
      for (int t = 0; t < sz; t++)
        image[t] = 0;

      if (y >= height)
        y = height - 1;

      for (int x = 0; x <= width; x = x + xStep)
      {
        if (x >= width)
          x = width - 1;

        std::vector<T::Coordinate> lineCoordinates;
        int cellCount = findPath(direction, image, width, height, maxStreamLen, 0, (double) x + 0.5, (double) y + 0.5, 0, 0, lineCoordinates);
        if ((int) lineCoordinates.size() >= minStreamLen && cellCount >= minStreamLen)
        {
          MemoryWriter memoryWrite(data, dataSize, false);

          int cnt = lineCoordinates.size();
          for (int t = 0; t < cnt; t = t + lineLen)
          {
            int points = lineLen - 4;
            if ((t + points) > cnt)
              points = cnt - t;

            memoryWrite.write_uint8(0);       // Byte order
            memoryWrite.write_uint32(2);      // WkbLine
            memoryWrite.write_uint32(points); // Number of points

            for (int a = 0; a < points; a++)
            {
              int idx = (t + a);
              double ax = lineCoordinates[idx].x();
              double ay = lineCoordinates[idx].y();

              if (ay >= height)
                ay = height - 1;

              if (ax >= width)
                ax = width - 1;

              int xx = (int) ax;
              int yy = (int) ay;

              double dx = ax - (double) xx;
              double dy = ay - (double) yy;

              int i[4];
              i[0] = (height - yy - 1) * width + xx;
              i[1] = i[0];
              i[2] = i[0];
              i[3] = i[0];

              if ((xx + 1) < width)
              {
                i[1] = i[0] + 1;
                i[2] = i[1];
                if ((yy + 1) < height)
                {
                  i[3] = i[0] - width;
                  i[2] = i[1] - width;
                }
              }

              double cx = linearInterpolation(dx, dy, 0, 0, 1, 1, (*coordinates)[i[0]].x(), (*coordinates)[i[1]].x(), (*coordinates)[i[2]].x(), (*coordinates)[i[3]].x());
              double cy = linearInterpolation(dx, dy, 0, 0, 1, 1, (*coordinates)[i[0]].y(), (*coordinates)[i[1]].y(), (*coordinates)[i[2]].y(), (*coordinates)[i[3]].y());
              memoryWrite.write_double(cx);
              memoryWrite.write_double(cy);
            }
            uint bytes = memoryWrite.getWritePosition();
            if (bytes > 0)
            {
              std::vector<uchar> wkb;

              wkb.reserve(bytes);
              for (uint t = 0; t < bytes; t++)
                wkb.emplace_back(data[t]);

              streamlines.emplace_back(wkb);
              memoryWrite.setWritePosition(0);
            }
          }

          uint bytes = memoryWrite.getWritePosition();
          if (bytes > 0)
          {
            std::vector<uchar> wkb;
            wkb.reserve(bytes);
            for (uint t = 0; t < bytes; t++)
              wkb.emplace_back(data[t]);

            streamlines.emplace_back(wkb);
          }
        }
        else
        {
          for (auto point = lineCoordinates.begin(); point != lineCoordinates.end(); ++point)
          {
            int idx = ((int) point->y()) * width + (int) point->x();
            if (idx >= 0 && idx < sz)
              image[idx] = 0;
          }
        }
      }
    }

    delete[] direction;
    delete[] image;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

} // namespace SmartMet

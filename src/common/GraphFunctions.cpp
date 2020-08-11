#include "GraphFunctions.h"
#include "Exception.h"
#include "ImageFunctions.h"
#include "MemoryReader.h"
#include "MemoryWriter.h"
#include "GeneralFunctions.h"
#include "AutoThreadLock.h"
#include "ShowFunction.h"
#include "SimpleDataMatrixAdapter.h"

#include <math.h>
#include <sstream>
#include <stack>

#include <geos/io/WKBWriter.h>
#include <tron/FmiBuilder.h>
#include <tron/Tron.h>
#include <tron/SavitzkyGolay2D.h>



#define FUNCTION_TRACE FUNCTION_TRACE_OFF



namespace SmartMet
{


std::vector<std::pair<long long,T::ByteData>> wkbCache;
ThreadLock wkbCacheThreadLock;


#define GRID_POINT_CACHE_SIZE 300

std::vector<T::Point> gridPointsCache[GRID_POINT_CACHE_SIZE];
std::size_t gridPointCacheHash[GRID_POINT_CACHE_SIZE] = {0};
uint hashCounter = 0;
ThreadLock pointCacheThreadLock;




extern void convertWkbCoordinates(MemoryReader& _memoryReader,MemoryWriter& _memoryWriter,OGRCoordinateTransformation& _transformation);



static int compare_points(const void *p1, const void *p2)
{
  const double *v1 = (const double*)p1;
  const double *v2 = (const double*)p2;

  if (*v1 < *v2)
    return -1;

  if (*v1 > *v2)
    return 1;

  return 0;
}





void addLine(double x1,double y1,double x2,double y2,std::set<unsigned long long>&  cList)
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

    if (x1 == x2  && (x1 - round(x1)) == 0)
    {
      int yStart = round(y1);
      if ((y1 - yStart) > 0)
        yStart++;

      int yEnd = floor(y2);

      for (int y=yStart; y<=yEnd; y++)
      {
        //printf("VLinePoint %d,%d\n",(int)x1,y);
        unsigned long long p = (((unsigned long long)y) << 32) + (unsigned long long)x1;
        if (cList.find(p) == cList.end())
          cList.insert(p);
      }

      return;
    }

    if (y1 == y2  && (y1 - round(y1)) == 0)
    {
      if (x2 < x1)
      {
        double tx = x1;
        x1 = x2;
        x2 = tx;
      }

      int xStart = round(x1);
      if ((x1 - xStart) > 0)
        xStart++;

      int xEnd = floor(x2);

      for (int x=xStart; x<=xEnd; x++)
      {
        //printf("HLinePoint %d,%d\n",x,(int)y1);
        unsigned long long p = (((unsigned long long)round(y1)) << 32) + (unsigned long long)x;
        if (cList.find(p) == cList.end())
          cList.insert(p);
      }

      return;
    }


    double dy = (y2 - y1);
    double dx = (x2 - x1);

    double dd = dx/dy;

    int yStart = round(y1);
    if ((y1 - yStart) > 0)
      yStart++;

    int yEnd = floor(y2);

    for (int y=yStart; y<yEnd; y++)
    {
      double diff = C_DOUBLE(y) - y1;
      double xx = x1 + diff * dd;

      if ((xx - C_INT(xx)) == 0)
      {
        //printf("LinePoint %d,%d\n",(int)xx,y);
        unsigned long long p = (((unsigned long long)y) << 32) + (unsigned long long)xx;
        if (cList.find(p) == cList.end())
          cList.insert(p);
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void getPointsInsidePolygon(int gridWidth,int gridHeight,T::Coordinate_vec& polygonPoints,std::vector<T::Point>& gridPoints)
{
  try
  {
    uint numOfPoints = polygonPoints.size();
    if (numOfPoints == 0)
      return;

    std::size_t hash = 0;
    boost::hash_combine(hash,gridWidth);
    boost::hash_combine(hash,gridHeight);

    for (uint t=0; t<numOfPoints; t++)
    {
      boost::hash_combine(hash,polygonPoints[t].x());
      boost::hash_combine(hash,polygonPoints[t].y());
    }

    for (uint t=0; t<GRID_POINT_CACHE_SIZE; t++)
    {
      if (gridPointCacheHash[t] == hash)
      {
        AutoThreadLock lock(&pointCacheThreadLock);
        if (gridPointCacheHash[t] == hash)
        {
          gridPoints = gridPointsCache[t];
          return;
        }
      }
    }

    std::set<unsigned long long> cList;

    // It the last polygon point is not same than the first point, then we should add it to the list.

    if (polygonPoints[0].x() != polygonPoints[numOfPoints-1].x()  ||  polygonPoints[0].y() != polygonPoints[numOfPoints-1].y())
    {
      polygonPoints.push_back(polygonPoints[0]);
      numOfPoints++;
    }


    // Adding points that are below the polygon line.

    for (uint t=1; t<numOfPoints; t++)
    {
      addLine(polygonPoints[t-1].x(),polygonPoints[t-1].y(),polygonPoints[t].x(),polygonPoints[t].y(),cList);
    }

    // Adding points that are inside the polygon line.

    int maxY = 0;
    int minY = gridHeight-1;
    int minX = 0;
    int maxX = gridWidth - 1;

    for (auto it = polygonPoints.begin(); it != polygonPoints.end(); ++it)
    {
      double yp = round(it->y());

      if (yp < minY)
        minY = yp;

      if (yp > maxY)
        maxY = yp;
    }

    if (minY < 0)
      minY = 0;

    if (maxY >= gridHeight)
      maxY = gridHeight - 1;

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

      qsort(&nodeX, nodes, sizeof(double),compare_points);

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

          //printf("Line %f,%d - %f,%d\n",nodeX[i],y,nodeX[i+1],y);
          int xStart = C_INT(nodeX[i]);
          int xEnd = C_INT(nodeX[i+1]);

          if ((nodeX[i] - xStart) > 0)
            xStart++;

          if ((xEnd - nodeX[i+1]) > 0)
            xEnd--;

          for (int x=xStart; x<=xEnd; x++)
          {
            unsigned long long p = (C_UINT64(y) << 32) + (unsigned long long)x;
            if (cList.find(p) == cList.end())
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

      gridPoints.push_back(T::Point(x,y));
    }

    AutoThreadLock lock(&pointCacheThreadLock);
    uint idx = hashCounter % GRID_POINT_CACHE_SIZE;
    gridPointsCache[idx] = gridPoints;
    gridPointCacheHash[idx] = hash;
    hashCounter++;;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






void getPointsInsidePolygonPath(int gridWidth,int gridHeight,T::Polygon_vec& polygonPath,std::vector<T::Point>& gridPoints)
{
  try
  {
    if (polygonPath.size() == 0)
      return;

    std::size_t hash = 0;
    boost::hash_combine(hash,gridWidth);
    boost::hash_combine(hash,gridHeight);
    for (auto polygonPoints = polygonPath.begin(); polygonPoints != polygonPath.end(); ++polygonPoints)
    {
      uint numOfPoints = polygonPoints->size();
      for (uint t=0; t<numOfPoints; t++)
      {
        boost::hash_combine(hash,(*polygonPoints)[t].x());
        boost::hash_combine(hash,(*polygonPoints)[t].y());
      }
    }

    for (uint t=0; t<GRID_POINT_CACHE_SIZE; t++)
    {
      if (gridPointCacheHash[t] == hash)
      {
        AutoThreadLock lock(&pointCacheThreadLock);
        if (gridPointCacheHash[t] == hash)
        {
          gridPoints = gridPointsCache[t];
          return;
        }
      }
    }

    std::set<unsigned long long> cList;

    int minY = gridHeight-1;
    int maxY = 0;
    int minX = 0;
    int maxX = gridWidth - 1;
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
          (*polygonPoints).push_back((*polygonPoints)[0]);
          numOfPoints++;
        }

        // Adding points that are below the polygon line.

        for (uint t=1; t<numOfPoints; t++)
        {
          addLine((*polygonPoints)[t-1].x(),(*polygonPoints)[t-1].y(),(*polygonPoints)[t].x(),(*polygonPoints)[t].y(),cList);
        }

        // Adding points that are inside the polygon line.

        for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
        {
          double yp = round(it->y());

          if (yp < minY)
            minY = yp;

          if (yp > maxY)
            maxY = yp;
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
            throw SmartMet::Spine::Exception(BCP,"Not enough space for the point list!",nullptr);
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
      //printf("Nodes %d %u\n",y,nodes);
      qsort(&nodeX, nodes, sizeof(double),compare_points);

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

          //printf("Line %f,%d - %f,%d\n",nodeX[i],y,nodeX[i+1],y);
          int xStart = C_INT(nodeX[i]);
          int xEnd = C_INT(nodeX[i+1]);

          if ((nodeX[i] - xStart) > 0)
            xStart++;

          if ((xEnd - nodeX[i+1]) > 0)
            xEnd--;

          for (int x=xStart; x<=xEnd; x++)
          {
            unsigned long long p = (C_UINT64(y) << 32) + x;
            if (cList.find(p) == cList.end())
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

      gridPoints.push_back(T::Point(x,y));
    }

    AutoThreadLock lock(&pointCacheThreadLock);
    uint idx = hashCounter % GRID_POINT_CACHE_SIZE;
    gridPointsCache[idx] = gridPoints;
    gridPointCacheHash[idx] = hash;
    hashCounter++;;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void getPointsInsideCircle(int gridWidth,int gridHeight,double origoX,double origoY,double radius,std::vector<T::Point>& gridPoints)
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

    for (int y=yy1; y<=yy2; y++)
    {
      double dy = C_DOUBLE(y)-origoY;
      for (int x=xx1; x<=xx2; x++)
      {
        double dx = C_DOUBLE(x)-origoX;
        double r2 = dx*dx + dy*dy;

        if (r2 <= rr)
        {
          // Point is inside the circle.
          gridPoints.push_back(T::Point(x,y));
        }
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void convertSvgPathToPolygonPath(NFmiSvgPath& svgPath,T::Polygon_vec& polygonPath)
{
  try
  {
    T::Coordinate_vec polygonPoints;

    for (auto it=svgPath.begin(); it!=svgPath.end(); ++it)
    {
      switch (it->itsType)
      {
        case NFmiSvgPath::kElementMoveto:
          if (polygonPoints.size() > 0)
          {
            polygonPath.push_back(polygonPoints);
            polygonPoints.clear();
          }
          polygonPoints.push_back(T::Coordinate(it->itsX,it->itsY));
          break;

        case NFmiSvgPath::kElementClosePath:
          if (polygonPoints.size() > 0)
          {
            int t = C_INT(polygonPoints.size()) -1;
            if (t > 0  &&  (polygonPoints[0].x() != polygonPoints[t].x() || polygonPoints[0].y() != polygonPoints[t].y()))
              polygonPoints.push_back(polygonPoints[0]);

            polygonPath.push_back(polygonPoints);
            polygonPoints.clear();
          }

          polygonPoints.clear();
          break;

        case NFmiSvgPath::kElementLineto:
          polygonPoints.push_back(T::Coordinate(it->itsX,it->itsY));
          break;

        case NFmiSvgPath::kElementNotValid:
          return;
      }
    }
    if (polygonPoints.size() > 0)
      polygonPath.push_back(polygonPoints);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string convertWktMultiPolygonToSvgString(const std::string& wktString)
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void convertWktMultipolygonToSvgPath(const std::string& wktString,NFmiSvgPath& svgPath)
{
  try
  {
    std::string svgString = convertWktMultiPolygonToSvgString(wktString);
    std::stringstream svgStringStream(svgString);

    svgPath.Read(svgStringStream);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void convertWktMultipolygonToPolygonPath(const std::string& wktString,T::Polygon_vec& polygonPath)
{
  try
  {
    std::string svgString = convertWktMultiPolygonToSvgString(wktString);
    std::stringstream svgStringStream(svgString);

    NFmiSvgPath svgPath;
    svgPath.Read(svgStringStream);
    convertSvgPathToPolygonPath(svgPath,polygonPath);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool getLineIntersection(double ax1, double ay1,double ax2, double ay2,double bx1, double by1,double bx2, double by2,double& x, double& y)
{
  try
  {
    if (ax1 == ax2  &&  ay1 == ay2)
      return false; // Undefined line a

    if (bx1 == bx2  &&  by1 == by2)
      return false; // Undefined line b

    //  Translate the lines so that point x1,y1 is on the origin.

    ax2 -= ax1;
    ay2 -= ay1;
    bx1 -= ax1;
    by1 -= ay1;
    bx2 -= ax1;
    by2 -= ay1;

    double da = sqrt(ax2*ax2 + ay2*ay2);
    double aCos = ax2/da;
    double aSin = ay2/da;
    double newX = bx1*aCos + by1*aSin;

    by1 = by1*aCos - bx1*aSin;
    bx1 = newX;
    newX = bx2*aCos + by2*aSin;
    by2 = by2*aCos - bx2*aSin;
    bx2 = newX;

    if (by1 == by2)
      return false;  // The lines are parallel

    double pos = bx2 + (bx1-bx2)*by2 / (by2-by1);

    x = ax1 + pos*aCos;
    y = ay1 + pos*aSin;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool getLineIntersection(std::pair<T::Coordinate,T::Coordinate> line1,std::pair<T::Coordinate,T::Coordinate> line2,T::Coordinate& intersection)
{
  try
  {
    double ix = 0;
    double iy = 0;

    bool res = getLineIntersection(line1.first.x(),line1.first.y(),line1.second.x(),line1.second.y(),line2.first.x(),line2.first.y(),line2.second.x(),line2.second.y(),ix,iy);
    if (res)
      intersection.set(ix,iy);
    return res;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void getPointMovement(double x1,double y1,double x2,double y2,double areaExtensionX,double areaExtensionY,double& mx,double& my)
{
  try
  {
     //printf("Line %f,%f - %f,%f  Ext %f\n",x1,y1,x2,y2,areaExtension);
    double PI = 3.1415927;

    double dx = fabs(x2-x1);
    double dy = fabs(y2-y1);

    double a = atan(dx/dy);
    double b = PI/2 - a;

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void getPointMovementRev(double x1,double y1,double x2,double y2,double areaExtensionX,double areaExtensionY,double& mx,double& my)
{
  try
  {
    // printf("LineRev %f,%f - %f,%f\n",x1,y1,x2,y2);
    double PI = 3.1415927;

    double dx = fabs(x2-x1);
    double dy = fabs(y2-y1);

    double a = atan(dx/dy);
    double b = PI/2 - a;

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::Coordinate_vec getEnlargedPolygon(T::Coordinate_vec& oldCoordinates,double areaExtensionX,double areaExtensionY,bool rev)
{
  try
  {
    T::Coordinate_vec newCoordinates;

    std::vector<std::pair<T::Coordinate,T::Coordinate>> tmpLines;
    int points = C_INT(oldCoordinates.size());
    for (int t = 0; t < points-1; t++)
    {
      auto p1 = oldCoordinates[t];
      auto p2 = oldCoordinates[t+1];

      double mx = 0;
      double my = 0;

      if (rev)
        getPointMovementRev(p1.x(),p1.y(),p2.x(),p2.y(),areaExtensionX,areaExtensionY,mx,my);
      else
        getPointMovement(p1.x(),p1.y(),p2.x(),p2.y(),areaExtensionX,areaExtensionY,mx,my);


      //printf("Move %f,%f\n",mx,my);

      T::Coordinate n1(p1.x() + mx,p1.y() + my);
      T::Coordinate n2(p2.x() + mx,p2.y() + my);

      tmpLines.push_back(std::pair<T::Coordinate,T::Coordinate>(n1,n2));
    }

    int lines = C_INT(tmpLines.size());
    for (int t=0; t<lines; t++)
    {
      T::Coordinate point;
      if ((t+1) < lines)
      {
        // printf("  Line1(%f,%f,%f,%f) - Line2(%f,%f,%f,%f)\n",tmpLines[t].first.x(),tmpLines[t].first.y(),tmpLines[t].second.x(),tmpLines[t].second.y(),tmpLines[t+1].first.x(),tmpLines[t+1].first.y(),tmpLines[t+1].second.x(),tmpLines[t+1].second.y());
        if (getLineIntersection(tmpLines[t],tmpLines[t+1],point))
          newCoordinates.push_back(point);
      }
      else
      {
        if (getLineIntersection(tmpLines[t],tmpLines[0],point))
        {
          newCoordinates.push_back(point);
          newCoordinates.insert(newCoordinates.begin(),point);
        }
      }
    }

    return newCoordinates;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





double getPolygonLen(T::Coordinate_vec& coordinates)
{
  try
  {
    int points = C_INT(coordinates.size());
    double len = 0;
    for (int t = 0; t < points-1; t++)
    {
      auto p1 = coordinates[t];
      auto p2 = coordinates[t+1];

      double dx = p2.x() - p1.x();
      double dy = p2.y() - p1.y();

      len = len + sqrt(dx*dx + dy*dy);
    }
    return len;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




T::Coordinate_vec getEnlargedPolygon(T::Coordinate_vec& oldCoordinates,double areaExtensionX,double areaExtensionY)
{
  try
  {
    //for (auto it = oldCoordinates.begin(); it != oldCoordinates.end(); ++it)
    //  printf(" ++ %f %f\n",it->x(),it->y());


    std::vector<T::Coordinate> newCoordinates;

    double oldLen = getPolygonLen(oldCoordinates);
    newCoordinates = getEnlargedPolygon(oldCoordinates,areaExtensionX,areaExtensionY,false);
    double newLen = getPolygonLen(newCoordinates);

    //for (auto it = newCoordinates.begin(); it != newCoordinates.end(); ++it)
    //  printf(" -- %f %f\n",it->x(),it->y());

//    printf("LEN = %f  NEW = %f\n",oldLen,newLen);

    if (areaExtensionX > 0  &&  newLen < oldLen)
      return getEnlargedPolygon(oldCoordinates,areaExtensionX,areaExtensionY,true);

    if (areaExtensionX < 0  &&  newLen > oldLen)
      return getEnlargedPolygon(oldCoordinates,areaExtensionX,areaExtensionY,true);

    return newCoordinates;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






T::Polygon_vec getEnlargedPolygonPath(T::Polygon_vec& oldPath,double areaExtensionX,double areaExtensionY)
{
  try
  {
    T::Polygon_vec newPath;

    for (auto coordinates = oldPath.begin(); coordinates != oldPath.end(); ++coordinates)
    {
      T::Coordinate_vec newCoordinates = getEnlargedPolygon(*coordinates,areaExtensionX,areaExtensionY);
      newPath.push_back(newCoordinates);
    }
    return newPath;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


#if 0


class DataMatrixAdapter
{
  public:
    typedef float value_type;
    typedef double coord_type;
    typedef NFmiDataMatrix<float>::size_type size_type;


    DataMatrixAdapter(std::vector<float>& values,std::vector<T::Coordinate> *coordinates,uint width,uint height)
    {
      mValues = &values;
      mCoordinates = coordinates;
      mWidth = width;
      mHeight = height;
      mReleaseData = false;
      mMissingValue = NAN;
    }

    DataMatrixAdapter(const DataMatrixAdapter& other)
    {
      mValues = nullptr;
      mCoordinates = nullptr;
      mWidth = other.mWidth;
      mHeight = other.mHeight;
      mMissingValue = NAN;
      mReleaseData = true;

      if (other.mValues != nullptr)
      {
        mValues = new std::vector<float>();
        *mValues = *other.mValues;
      }

      if (other.mCoordinates != nullptr)
      {
        mCoordinates = new std::vector<T::Coordinate>();
        *mCoordinates = *other.mCoordinates;
      }
    }

    virtual ~DataMatrixAdapter()
    {
      if (mReleaseData)
      {
        if (mValues != nullptr)
          delete mValues;

        if (mCoordinates != nullptr)
          delete mCoordinates;
      }
    }

    const float& operator()(uint i, uint j) const
    {
      uint pos = (j % mHeight)*mWidth + (i % mWidth);
      if (mCoordinates != nullptr  &&  (*mCoordinates)[pos].x() == ParamValueMissing)
        return mMissingValue;

      if ((*mValues)[pos] == ParamValueMissing)
        return mMissingValue;

      return (*mValues)[pos];
    }

    float& operator()(uint i, uint j)
    {
      uint pos = (j % mHeight)*mWidth + (i % mWidth);
      if (mCoordinates != nullptr  &&  (*mCoordinates)[pos].x() == ParamValueMissing)
        return mMissingValue;

      if ((*mValues)[pos] == ParamValueMissing)
        return mMissingValue;

      return (*mValues)[pos];
    }

    double x(uint i, uint j) const
    {
      if (mCoordinates == nullptr)
        return i;

      if (i < mWidth  &&  j < mHeight)
        return (*mCoordinates)[(j % mHeight)*mWidth + i].x();

      return 360;
    }

    double y(uint i, uint j) const
    {
      if (mCoordinates == nullptr)
        return j;

      if (i < mWidth  &&  j < mHeight)
        return (*mCoordinates)[(j % mHeight)*mWidth + i].y();

      return 90;
    }

    uint width() const
    {
      return mWidth;
    }

    uint height() const
    {
      return mHeight;
    }

    void swap(DataMatrixAdapter& other)
    {
      mWidth = other.mWidth;
      mHeight = other.mHeight;

      if (other.mValues != nullptr  &&  mValues != nullptr)
      {
        *mValues = *other.mValues;
      }

      if (other.mCoordinates != nullptr  &&  mCoordinates != nullptr)
      {
        mCoordinates = new std::vector<T::Coordinate>();
      }
    }


  private:
    std::vector<float>          *mValues;
    std::vector<T::Coordinate>  *mCoordinates;
    uint                        mWidth;
    uint                        mHeight;
    bool                        mReleaseData;
    float                       mMissingValue;
};

#endif



typedef boost::shared_ptr<geos::geom::Geometry> GeometryPtr;

typedef Tron::Traits<double, double, Tron::InfMissing> MyTraits;
typedef Tron::Contourer<SimpleDataMatrixAdapter, Tron::FmiBuilder, MyTraits, Tron::LinearInterpolation>  MyLinearContourer;
typedef Tron::Contourer<SimpleDataMatrixAdapter, Tron::FmiBuilder, MyTraits, Tron::LogLinearInterpolation> MyLogLinearContourer;
typedef Tron::Contourer<SimpleDataMatrixAdapter, Tron::FmiBuilder, MyTraits, Tron::NearestNeighbourInterpolation>  MyNearestContourer;
typedef Tron::Contourer<SimpleDataMatrixAdapter, Tron::FmiBuilder, MyTraits, Tron::DiscreteInterpolation> MyDiscreteContourer;
typedef Tron::Hints<SimpleDataMatrixAdapter, MyTraits> MyHints;




void getIsolines(std::vector<float>& gridData,T::Coordinate_vec *coordinates,int width,int height,std::vector<float>& contourValues,short interpolationMethod,size_t smooth_size,size_t smooth_degree,T::ByteData_vec& contours)
{
  try
  {
    size_t sz = gridData.size();
    if (sz == 0)
      return;

    double minValue = gridData[0];
    double maxValue = gridData[0];

    for (size_t t=0; t<sz; t++)
    {
      if (gridData[t] < minValue)
        minValue = gridData[t];

      if (gridData[t] > maxValue)
        maxValue = gridData[t];
    }

    std::vector<float> *gridDataPtr = &gridData;
    std::vector<float> tmpGridData;
    if (smooth_size > 0 || smooth_degree > 0)
    {
      tmpGridData = gridData;
      SimpleDataMatrixAdapter tmpData(tmpGridData,nullptr,width,height);
      Tron::SavitzkyGolay2D::smooth(tmpData, smooth_size, smooth_degree);
      gridDataPtr = &tmpGridData;
    }
    SimpleDataMatrixAdapter data(*gridDataPtr,coordinates,width,height);

    std::unique_ptr<MyHints> hints;

    hints.reset(new MyHints(data));

    bool worldwrap = false;

    boost::shared_ptr<geos::geom::GeometryFactory> itsGeomFactory;
    itsGeomFactory.reset(new geos::geom::GeometryFactory());
    Tron::FmiBuilder builder(itsGeomFactory);


    auto len = contourValues.size();
    for (size_t c = 0; c<len; c++)
    {
      double isovalue = contourValues[c];
      T::ByteData wkbData;

      if (isovalue >= minValue  &&  isovalue <= maxValue)
      {
        switch (interpolationMethod)
        {
          case T::AreaInterpolationMethod::Linear:
            MyLinearContourer::line(builder, data, isovalue, worldwrap, *hints);
            break;
/*
          case T::AreaInterpolationMethod::Nearest:
            MyNearestContourer::line(builder, data, isovalue, worldwrap, *hints);
            MyNearestContourer::fill(builder, data, lo, hi, worldwrap, hints);
            break;
*/
          case T::LevelInterpolationMethod::Logarithmic:
            MyLogLinearContourer::line(builder, data, isovalue, worldwrap, *hints);
            break;

          default:
            MyLinearContourer::line(builder, data, isovalue, worldwrap, *hints);
            break;
        }

        auto geom = builder.result();

        std::ostringstream out;
        geos::io::WKBWriter writer;

        writer.write(*geom, out);


        const auto &wkb = out.str();
        unsigned char *data = reinterpret_cast<unsigned char *>(const_cast<char *>(wkb.c_str()));
        size_t size = wkb.length();

        if (size > 0)
        {
          wkbData.reserve(size);

          for (size_t t=0; t<size; t++)
            wkbData.push_back(data[t]);
        }
      }
      contours.push_back(wkbData);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






void getIsobands(std::vector<float>& gridData,std::vector<T::Coordinate> *coordinates,int width,int height,std::vector<float>& contourLowValues,std::vector<float>& contourHighValues,short interpolationMethod,size_t smooth_size,size_t smooth_degree,T::ByteData_vec& contours)
{
  try
  {
    size_t sz = gridData.size();
    if (sz == 0 ||  (coordinates != nullptr  &&  sz != coordinates->size()))
      return;

    long long hash = 0;

    double minValue = gridData[0];
    double maxValue = gridData[0];

    for (size_t t=0; t<sz; t++)
    {
      if (gridData[t] < minValue)
        minValue = gridData[t];

      if (gridData[t] > maxValue)
        maxValue = gridData[t];

      hash += C_INT64(gridData[t]*1000000);
      if (coordinates != nullptr)
      {
        hash += C_INT64((*coordinates)[t].x()*1000000);
        hash += C_INT64((*coordinates)[t].y()*1000000);
      }
    }

    hash += smooth_size;
    hash += smooth_degree;



    std::vector<float> *gridDataPtr = &gridData;
    std::vector<float> tmpGridData;

    if (smooth_size > 0 || smooth_degree > 0)
    {
      tmpGridData = gridData;
      SimpleDataMatrixAdapter tmpData(tmpGridData,nullptr,width,height);
      Tron::SavitzkyGolay2D::smooth(tmpData, smooth_size, smooth_degree);
      gridDataPtr = &tmpGridData;
    }

    SimpleDataMatrixAdapter data(*gridDataPtr,coordinates,width,height);

    std::unique_ptr<MyHints> hints;
    hints.reset(new MyHints(data));


    bool worldwrap = false;

    auto len = contourLowValues.size();
    if (contourHighValues.size() != len)
    {
      throw SmartMet::Spine::Exception(BCP,"There should be the same number of contour high and low values!");
    }

    boost::shared_ptr<geos::geom::GeometryFactory> itsGeomFactory;
    itsGeomFactory.reset(new geos::geom::GeometryFactory());
    Tron::FmiBuilder builder(itsGeomFactory);


    for (size_t c = 0; c<len; c++)
    {
      double low = contourLowValues[c];
      double high = contourHighValues[c];

      long long hh = hash + low*1000000 + high*1000000 + interpolationMethod;
      bool found = false;

      {
        AutoThreadLock lock(&wkbCacheThreadLock);
        if (wkbCache.size() >= 5000)
          wkbCache.erase(wkbCache.begin(), wkbCache.begin() + 1000);

        for (auto it = wkbCache.rbegin(); it != wkbCache.rend()  &&  !found; ++it)
        {
          if (it->first == hh)
          {
            contours.push_back(it->second);
            found = true;
          }
        }
      }

      if (!found)
      {
        T::ByteData wkbData;


        if (high >= minValue && low <= maxValue)
        {
          switch (interpolationMethod)
          {
            case T::AreaInterpolationMethod::Linear:
              MyLinearContourer::fill(builder, data, low,high, worldwrap, *hints);
              break;
            case T::AreaInterpolationMethod::Nearest:
              MyNearestContourer::fill(builder, data, low,high, worldwrap, *hints);
              break;

            case T::LevelInterpolationMethod::Logarithmic:
              MyLogLinearContourer::fill(builder, data, low, high, worldwrap, *hints);
              break;

            default:
              MyLinearContourer::fill(builder, data, low,high, worldwrap, *hints);
              break;
          }

          auto geom = builder.result();

          std::ostringstream out;
          geos::io::WKBWriter writer;

          writer.write(*geom, out);


          const auto &wkb = out.str();
          unsigned char *data = reinterpret_cast<unsigned char *>(const_cast<char *>(wkb.c_str()));
          size_t size = wkb.length();

          if (size > 0)
          {
            wkbData.reserve(size);

            for (size_t t=0; t<size; t++)
              wkbData.push_back(data[t]);
          }
        }
        contours.push_back(wkbData);

        AutoThreadLock lock(&wkbCacheThreadLock);
        if (wkbCache.size() >= 5000)
          wkbCache.erase(wkbCache.begin(), wkbCache.begin() + 1000);

        wkbCache.push_back(std::pair<long long,T::ByteData>(hh,wkbData));
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




#if 0
void convertWkbPoint(MemoryReader& _memoryReader,MemoryWriter& _memoryWriter,OGRCoordinateTransformation& _transformation)
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void convertWkbLine(MemoryReader& _memoryReader,MemoryWriter& _memoryWriter,OGRCoordinateTransformation& _transformation)
{
  FUNCTION_TRACE
  try
  {
    std::uint32_t pointCount = _memoryReader.read_uint32();
    _memoryWriter.write_uint32(pointCount);

    for (std::uint32_t t=0; t<pointCount; t++)
    {
      double x = _memoryReader.read_double();
      double y = _memoryReader.read_double();

      _transformation.Transform(1,&x,&y);

      _memoryWriter.write_double(x);
      _memoryWriter.write_double(y);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void convertWkbRing(MemoryReader& _memoryReader,MemoryWriter& _memoryWriter,OGRCoordinateTransformation& _transformation)
{
  FUNCTION_TRACE
  try
  {
    std::uint32_t pointCount = _memoryReader.read_uint32();
    _memoryWriter.write_uint32(pointCount);

    for (std::uint32_t t=0; t<pointCount; t++)
    {
      double x = _memoryReader.read_double();
      double y = _memoryReader.read_double();

      _transformation.Transform(1,&x,&y);

      _memoryWriter.write_double(x);
      _memoryWriter.write_double(y);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void convertWkbPolygon(MemoryReader& _memoryReader,MemoryWriter& _memoryWriter,OGRCoordinateTransformation& _transformation)
{
  FUNCTION_TRACE
  try
  {
    std::uint32_t ringCount = _memoryReader.read_uint32();
    _memoryWriter.write_uint32(ringCount);

    for (std::uint32_t t=0; t<ringCount; t++)
    {
      convertWkbRing(_memoryReader,_memoryWriter,_transformation);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void convertWkbMultiPoint(MemoryReader& _memoryReader,MemoryWriter& _memoryWriter,OGRCoordinateTransformation& _transformation)
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void convertWkbMultiLineString(MemoryReader& _memoryReader,MemoryWriter& _memoryWriter,OGRCoordinateTransformation& _transformation)
{
  FUNCTION_TRACE
  try
  {
    std::uint32_t stringCount = _memoryReader.read_uint32();
    _memoryWriter.write_uint32(stringCount);

    for (std::uint32_t t=0; t<stringCount; t++)
    {
      std::uint8_t byteOrder = _memoryReader.read_uint8();
      _memoryWriter.write_uint8(byteOrder);

      _memoryReader.setLittleEndian((bool)byteOrder);
      _memoryWriter.setLittleEndian((bool)byteOrder);

      std::uint32_t wkbType = _memoryReader.read_uint32();
      _memoryWriter.write_uint32(wkbType);

      convertWkbLine(_memoryReader,_memoryWriter,_transformation);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void convertWkbMultiPolygon(MemoryReader& _memoryReader,MemoryWriter& _memoryWriter,OGRCoordinateTransformation& _transformation)
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void convertWkbGeometryCollection(MemoryReader& _memoryReader,MemoryWriter& _memoryWriter,OGRCoordinateTransformation& _transformation)
{
  FUNCTION_TRACE
  try
  {
    std::uint32_t geometryCount = _memoryReader.read_uint32();
    for (std::uint32_t t=0; t<geometryCount; t++)
    {
      convertWkbCoordinates(_memoryReader,_memoryWriter,_transformation);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void convertWkbCoordinates(MemoryReader& _memoryReader,MemoryWriter& _memoryWriter,OGRCoordinateTransformation& _transformation)
{
  FUNCTION_TRACE
  try
  {
    while (_memoryReader.getReadPosition() < _memoryReader.getDataSize())
    {
      std::uint8_t byteOrder = _memoryReader.read_uint8();
      _memoryWriter.write_uint8(byteOrder);

      _memoryReader.setLittleEndian((bool)byteOrder);
      _memoryWriter.setLittleEndian((bool)byteOrder);

      std::uint32_t wkbType = _memoryReader.read_uint32();
      _memoryWriter.write_uint32(wkbType);

      switch (wkbType)
      {
        case 1:
          convertWkbPoint(_memoryReader,_memoryWriter,_transformation);
          break;

        case 2:
          convertWkbLine(_memoryReader,_memoryWriter,_transformation);
          break;

        case 3:
          convertWkbPolygon(_memoryReader,_memoryWriter,_transformation);
          break;

        case 4:
          convertWkbMultiPoint(_memoryReader,_memoryWriter,_transformation);
          break;

        case 5:
          convertWkbMultiLineString(_memoryReader,_memoryWriter,_transformation);
          break;

        case 6:
          convertWkbMultiPolygon(_memoryReader,_memoryWriter,_transformation);
          break;

        case 7:
          convertWkbGeometryCollection(_memoryReader,_memoryWriter,_transformation);
          break;
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void convertWkbCoordinates(T::ByteData& _wkb,T::ByteData& _newWkb,OGRCoordinateTransformation& _transformation)
{
  FUNCTION_TRACE
  try
  {
    size_t sz = _wkb.size();
    if (sz == 0)
      return;

    uchar *buf = new uchar[sz];
    MemoryReader memoryReader(buf,sz,true);

    uchar *bufnew = new uchar[sz];
    MemoryWriter memoryWriter(buf,sz,true);

    for (size_t t=0; t<sz; t++)
      buf[t] = _wkb[t];

    convertWkbCoordinates(memoryReader,memoryWriter,_transformation);

    ulonglong nsize = memoryWriter.getWritePosition();

    for (ulonglong t=0; t<nsize; t++)
      _newWkb.push_back(bufnew[t]);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void convertWkbCoordinates(T::ByteData_vec& _wkbVec,T::ByteData_vec& _newWkbVec,OGRCoordinateTransformation& _transformation)
{
  FUNCTION_TRACE
  try
  {
    for (auto it = _wkbVec.begin(); it != _wkbVec.end(); ++ it)
    {
      T::ByteData newWkb;
      convertWkbCoordinates(*it,newWkb,_transformation);
      _newWkbVec.push_back(newWkb);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}
#endif


}


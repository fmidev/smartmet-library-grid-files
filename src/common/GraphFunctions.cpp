#include "GraphFunctions.h"
#include "Exception.h"
#include "Typedefs.h"
#include <math.h>
#include <sstream>


namespace SmartMet
{


#ifndef MIN
  #define MIN(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef MAX
  #define MAX(a,b) (((a)>(b))?(a):(b))
#endif




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





void getPointsInsidePolygon(int gridWidth,int gridHeight,std::vector<T::Coordinate>& polygonPoints,std::vector<T::Point>& gridPoints)
{
  try
  {
    std::set<unsigned long long> cList;
    uint numOfPoints = polygonPoints.size();
    if (numOfPoints == 0)
      return;

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
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






void getPointsInsidePolygonPath(int gridWidth,int gridHeight,std::vector<std::vector<T::Coordinate>>& polygonPath,std::vector<T::Point>& gridPoints)
{
  try
  {
    if (polygonPath.size() == 0)
      return;

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





void convertSvgPathToPolygonPath(NFmiSvgPath& svgPath,std::vector<std::vector<T::Coordinate>>& polygonPath)
{
  try
  {
    std::vector<T::Coordinate> polygonPoints;

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





void convertWktMultipolygonToPolygonPath(const std::string& wktString,std::vector<std::vector<T::Coordinate>>& polygonPath)
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





std::vector<T::Coordinate> getEnlargedPolygon(std::vector<T::Coordinate>& oldCoordinates,double areaExtensionX,double areaExtensionY,bool rev)
{
  try
  {
    std::vector<T::Coordinate> newCoordinates;

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





double getPolygonLen(std::vector<T::Coordinate>& coordinates)
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




std::vector<T::Coordinate> getEnlargedPolygon(std::vector<T::Coordinate>& oldCoordinates,double areaExtensionX,double areaExtensionY)
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






std::vector<std::vector<T::Coordinate>> getEnlargedPolygonPath(std::vector<std::vector<T::Coordinate>>& oldPath,double areaExtensionX,double areaExtensionY)
{
  try
  {
    std::vector<std::vector<T::Coordinate>> newPath;

    for (auto coordinates = oldPath.begin(); coordinates != oldPath.end(); ++coordinates)
    {
      std::vector<T::Coordinate> newCoordinates = getEnlargedPolygon(*coordinates,areaExtensionX,areaExtensionY);
      newPath.push_back(newCoordinates);
    }
    return newPath;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint getIsolines(std::vector<float>& d,int width,int height,int ilb,int iub,int jlb,int jub,std::vector<float>& z,T::ContourLine *line,uint maxLines)
{
#define xsect(p1,p2) (h[p2]*xh[p1]-h[p1]*xh[p2])/(h[p2]-h[p1])
#define ysect(p1,p2) (h[p2]*yh[p1]-h[p1]*yh[p2])/(h[p2]-h[p1])
#define pos(xx,yy) ((yy)*width+(xx))

  try
  {
    uint lineCount = 0;
    int nc = (int)z.size();
    double x1=0,x2=0,y1=0,y2=0;
    int m1 = 0;
    int m2 = 0;
    int m3 = 0;
    int case_value = 0;

    double h[5];
    int sh[5];
    double xh[5],yh[5];
    int im[4] = {0,1,1,0},jm[4]={0,0,1,1};
    int castab[3][3][3] = {
      { {0,0,8},{0,2,5},{7,6,9} },
      { {0,3,4},{1,3,1},{4,3,0} },
      { {9,6,7},{5,2,0},{8,0,0} }
    };

    for (int j=(jub-1);j>=jlb;j--)
    {
      for (int i=ilb;i<=iub-1;i++)
      {
        double temp1 = MIN(d[pos(i,j)],d[pos(i,j+1)]);
        double temp2 = MIN(d[pos(i+1,j)],d[pos(i+1,j+1)]);
        double dmin  = MIN(temp1,temp2);
        temp1 = MAX(d[pos(i,j)],d[pos(i,j+1)]);
        temp2 = MAX(d[pos(i+1,j)],d[pos(i+1,j+1)]);
        double  dmax  = MAX(temp1,temp2);
        if (dmax < z[0] || dmin > z[nc-1])
          continue;

        for (int k=0; k<nc; k++)
        {
          if (z[k] < dmin || z[k] > dmax)
            continue;

          for (int m=4; m>=0; m--)
          {
            if (m > 0)
            {
              h[m]  = d[pos(i+im[m-1],j+jm[m-1])]-z[k];
              xh[m] = i+im[m-1];
              yh[m] = j+jm[m-1];
            }
            else
            {
              h[0]  = 0.25 * (h[1]+h[2]+h[3]+h[4]);
              xh[0] = 0.50 * (i+i+1);
              yh[0] = 0.50 * (j+j+1);
            }

            if (h[m] > 0.0)
              sh[m] = 1;
            else
            if (h[m] < 0.0)
              sh[m] = -1;
            else
              sh[m] = 0;
          }

          for (int m=1; m<=4; m++)
          {
            m1 = m;
            m2 = 0;

            if (m != 4)
              m3 = m + 1;
            else
              m3 = 1;

            if ((case_value = castab[sh[m1]+1][sh[m2]+1][sh[m3]+1]) == 0)
              continue;

            switch (case_value)
            {
              case 1:
                x1 = xh[m1];
                y1 = yh[m1];
                x2 = xh[m2];
                y2 = yh[m2];
                break;

              case 2:
                x1 = xh[m2];
                y1 = yh[m2];
                x2 = xh[m3];
                y2 = yh[m3];
                break;

              case 3:
                x1 = xh[m3];
                y1 = yh[m3];
                x2 = xh[m1];
                y2 = yh[m1];
                break;

              case 4:
                x1 = xh[m1];
                y1 = yh[m1];
                x2 = xsect(m2,m3);
                y2 = ysect(m2,m3);
                break;

              case 5:
                x1 = xh[m2];
                y1 = yh[m2];
                x2 = xsect(m3,m1);
                y2 = ysect(m3,m1);
                break;

              case 6:
                x1 = xh[m3];
                y1 = yh[m3];
                x2 = xsect(m1,m2);
                y2 = ysect(m1,m2);
                break;

              case 7:
                x1 = xsect(m1,m2);
                y1 = ysect(m1,m2);
                x2 = xsect(m2,m3);
                y2 = ysect(m2,m3);
                break;

              case 8:
                x1 = xsect(m2,m3);
                y1 = ysect(m2,m3);
                x2 = xsect(m3,m1);
                y2 = ysect(m3,m1);
                break;

              case 9:
                x1 = xsect(m3,m1);
                y1 = ysect(m3,m1);
                x2 = xsect(m1,m2);
                y2 = ysect(m1,m2);
                break;

              default:
                break;
            }

            /* Finally draw the line */

            line[lineCount].mX1 = x1;
            line[lineCount].mY1 = y1;
            line[lineCount].mX2 = x2;
            line[lineCount].mY2 = y2;

            //line[lineCount].mLevel = k;
            //line[lineCount].mValue = z[k];
            lineCount++;

            if (lineCount == maxLines)
              return lineCount;

            //lineVectorVector[k].push_back(T::Line(x1,y1,x2,y2));
            //drawLine(x1,y1,x2,y2,z[k]);
          }
        }
      }
    }
    return lineCount;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint getIsolines(std::vector<double>& d,int width,int height,int ilb,int iub,int jlb,int jub,std::vector<double>& z,T::ContourLine *line,uint maxLines)
{
#define xsect(p1,p2) (h[p2]*xh[p1]-h[p1]*xh[p2])/(h[p2]-h[p1])
#define ysect(p1,p2) (h[p2]*yh[p1]-h[p1]*yh[p2])/(h[p2]-h[p1])
#define pos(xx,yy) ((yy)*width+(xx))

  try
  {
    uint lineCount = 0;
    int nc = (int)z.size();
    double x1=0,x2=0,y1=0,y2=0;
    int m1 = 0;
    int m2 = 0;
    int m3 = 0;
    int case_value = 0;
    double h[5];
    int sh[5];
    double xh[5],yh[5];

    int im[4] = {0,1,1,0},jm[4]={0,0,1,1};
    int castab[3][3][3] = {
      { {0,0,8},{0,2,5},{7,6,9} },
      { {0,3,4},{1,3,1},{4,3,0} },
      { {9,6,7},{5,2,0},{8,0,0} }
    };

    for (int j=(jub-1);j>=jlb;j--)
    {
      for (int i=ilb;i<=iub-1;i++)
      {
        double temp1 = MIN(d[pos(i,j)],d[pos(i,j+1)]);
        double temp2 = MIN(d[pos(i+1,j)],d[pos(i+1,j+1)]);
        double dmin  = MIN(temp1,temp2);
        temp1 = MAX(d[pos(i,j)],d[pos(i,j+1)]);
        temp2 = MAX(d[pos(i+1,j)],d[pos(i+1,j+1)]);
        double  dmax  = MAX(temp1,temp2);
        if (dmax < z[0] || dmin > z[nc-1])
          continue;

        for (int k=0; k<nc; k++)
        {
          if (z[k] < dmin || z[k] > dmax)
            continue;

          for (int m=4; m>=0; m--)
          {
            if (m > 0)
            {
              h[m]  = d[pos(i+im[m-1],j+jm[m-1])]-z[k];
              xh[m] = i+im[m-1];
              yh[m] = j+jm[m-1];
            }
            else
            {
              h[0]  = 0.25 * (h[1]+h[2]+h[3]+h[4]);
              xh[0] = 0.50 * (i+i+1);
              yh[0] = 0.50 * (j+j+1);
            }

            if (h[m] > 0.0)
              sh[m] = 1;
            else
            if (h[m] < 0.0)
              sh[m] = -1;
            else
              sh[m] = 0;
          }

          for (int m=1; m<=4; m++)
          {
            m1 = m;
            m2 = 0;

            if (m != 4)
              m3 = m + 1;
            else
              m3 = 1;

            if ((case_value = castab[sh[m1]+1][sh[m2]+1][sh[m3]+1]) == 0)
              continue;

            switch (case_value)
            {
              case 1:
                x1 = xh[m1];
                y1 = yh[m1];
                x2 = xh[m2];
                y2 = yh[m2];
                break;

              case 2:
                x1 = xh[m2];
                y1 = yh[m2];
                x2 = xh[m3];
                y2 = yh[m3];
                break;

              case 3:
                x1 = xh[m3];
                y1 = yh[m3];
                x2 = xh[m1];
                y2 = yh[m1];
                break;

              case 4:
                x1 = xh[m1];
                y1 = yh[m1];
                x2 = xsect(m2,m3);
                y2 = ysect(m2,m3);
                break;

              case 5:
                x1 = xh[m2];
                y1 = yh[m2];
                x2 = xsect(m3,m1);
                y2 = ysect(m3,m1);
                break;

              case 6:
                x1 = xh[m3];
                y1 = yh[m3];
                x2 = xsect(m1,m2);
                y2 = ysect(m1,m2);
                break;

              case 7:
                x1 = xsect(m1,m2);
                y1 = ysect(m1,m2);
                x2 = xsect(m2,m3);
                y2 = ysect(m2,m3);
                break;

              case 8:
                x1 = xsect(m2,m3);
                y1 = ysect(m2,m3);
                x2 = xsect(m3,m1);
                y2 = ysect(m3,m1);
                break;

              case 9:
                x1 = xsect(m3,m1);
                y1 = ysect(m3,m1);
                x2 = xsect(m1,m2);
                y2 = ysect(m1,m2);
                break;

              default:
                break;
            }

            /* Finally draw the line */

            line[lineCount].mX1 = x1;
            line[lineCount].mY1 = y1;
            line[lineCount].mX2 = x2;
            line[lineCount].mY2 = y2;
            //line[lineCount].mLevel = k;
            //line[lineCount].mValue = z[k];
            lineCount++;

            if (lineCount == maxLines)
              return lineCount;

            //lineVectorVector[k].push_back(T::Line(x1,y1,x2,y2));
            //drawLine(x1,y1,x2,y2,z[k]);
          }
        }
      }
    }
    return lineCount;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






uint getIsolines(std::vector<float>& d,int width,int height,int ilb,int iub,int jlb,int jub,std::vector<float>& z,std::vector<T::ContourLine_vec>& lineVecVec)
{
#define xsect(p1,p2) (h[p2]*xh[p1]-h[p1]*xh[p2])/(h[p2]-h[p1])
#define ysect(p1,p2) (h[p2]*yh[p1]-h[p1]*yh[p2])/(h[p2]-h[p1])
#define pos(xx,yy) ((yy)*width+(xx))

  try
  {
    uint lineCount = 0;
    int nc = (int)z.size();
    for (int t=0; t<nc; t++)
    {
      T::ContourLine_vec vec;
      lineVecVec.push_back(vec);
    }

    double x1=0,x2=0,y1=0,y2=0;
    int m1 = 0;
    int m2 = 0;
    int m3 = 0;
    int case_value = 0;

    double h[5];
    int sh[5];
    double xh[5],yh[5];
    int im[4] = {0,1,1,0},jm[4]={0,0,1,1};
    int castab[3][3][3] = {
      { {0,0,8},{0,2,5},{7,6,9} },
      { {0,3,4},{1,3,1},{4,3,0} },
      { {9,6,7},{5,2,0},{8,0,0} }
    };

    for (int j=(jub-1);j>=jlb;j--)
    {
      for (int i=ilb;i<=iub-1;i++)
      {
        double temp1 = MIN(d[pos(i,j)],d[pos(i,j+1)]);
        double temp2 = MIN(d[pos(i+1,j)],d[pos(i+1,j+1)]);
        double dmin  = MIN(temp1,temp2);
        temp1 = MAX(d[pos(i,j)],d[pos(i,j+1)]);
        temp2 = MAX(d[pos(i+1,j)],d[pos(i+1,j+1)]);
        double  dmax  = MAX(temp1,temp2);
        if (dmax < z[0] || dmin > z[nc-1])
          continue;

        for (int k=0; k<nc; k++)
        {
          if (z[k] < dmin || z[k] > dmax)
            continue;

          for (int m=4; m>=0; m--)
          {
            if (m > 0)
            {
              h[m]  = d[pos(i+im[m-1],j+jm[m-1])]-z[k];
              xh[m] = i+im[m-1];
              yh[m] = j+jm[m-1];
            }
            else
            {
              h[0]  = 0.25 * (h[1]+h[2]+h[3]+h[4]);
              xh[0] = 0.50 * (i+i+1);
              yh[0] = 0.50 * (j+j+1);
            }

            if (h[m] > 0.0)
              sh[m] = 1;
            else
            if (h[m] < 0.0)
              sh[m] = -1;
            else
              sh[m] = 0;
          }

          for (int m=1; m<=4; m++)
          {
            m1 = m;
            m2 = 0;

            if (m != 4)
              m3 = m + 1;
            else
              m3 = 1;

            if ((case_value = castab[sh[m1]+1][sh[m2]+1][sh[m3]+1]) == 0)
              continue;

            switch (case_value)
            {
              case 1:
                x1 = xh[m1];
                y1 = yh[m1];
                x2 = xh[m2];
                y2 = yh[m2];
                break;

              case 2:
                x1 = xh[m2];
                y1 = yh[m2];
                x2 = xh[m3];
                y2 = yh[m3];
                break;

              case 3:
                x1 = xh[m3];
                y1 = yh[m3];
                x2 = xh[m1];
                y2 = yh[m1];
                break;

              case 4:
                x1 = xh[m1];
                y1 = yh[m1];
                x2 = xsect(m2,m3);
                y2 = ysect(m2,m3);
                break;

              case 5:
                x1 = xh[m2];
                y1 = yh[m2];
                x2 = xsect(m3,m1);
                y2 = ysect(m3,m1);
                break;

              case 6:
                x1 = xh[m3];
                y1 = yh[m3];
                x2 = xsect(m1,m2);
                y2 = ysect(m1,m2);
                break;

              case 7:
                x1 = xsect(m1,m2);
                y1 = ysect(m1,m2);
                x2 = xsect(m2,m3);
                y2 = ysect(m2,m3);
                break;

              case 8:
                x1 = xsect(m2,m3);
                y1 = ysect(m2,m3);
                x2 = xsect(m3,m1);
                y2 = ysect(m3,m1);
                break;

              case 9:
                x1 = xsect(m3,m1);
                y1 = ysect(m3,m1);
                x2 = xsect(m1,m2);
                y2 = ysect(m1,m2);
                break;

              default:
                break;
            }

            /* Finally draw the line */

            T::ContourLine line;
            line.mX1 = x1;
            line.mY1 = y1;
            line.mX2 = x2;
            line.mY2 = y2;
            //line.mLevel = k;
            //line.mValue = z[k];
            lineVecVec[k].push_back(line);
            lineCount++;

            //lineVectorVector[k].push_back(T::Line(x1,y1,x2,y2));
            //drawLine(x1,y1,x2,y2,z[k]);
          }
        }
      }
    }
    return lineCount;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}

}


#include "GraphFunctions.h"
#include "Exception.h"
#include <math.h>


namespace SmartMet
{


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
        unsigned long long p = (((unsigned long long)x1) << 32) + y;
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
        unsigned long long p = (((unsigned long long)x) << 32) + round(y1);
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
      double diff = (double)y - y1;
      double xx = x1 + diff * dd;

      if ((xx - (int)xx) == 0)
      {
        //printf("LinePoint %d,%d\n",(int)xx,y);
        unsigned long long p = (((unsigned long long)xx) << 32) + y;
        if (cList.find(p) == cList.end())
          cList.insert(p);
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void getPointsInsidePolygon(int gridWidth,int gridHeight,std::vector<T::Coordinate>& polygonPoints,std::vector<T::Point>& gridPoints)
{
  try
  {
    std::set<unsigned long long> cList;
    uint numOfPoints = (uint)polygonPoints.size();
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
      double yp = (int)it->y();

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

        if ((yi < (double)(y)  &&  yj >= (double)(y))  ||  (yj < (double)(y) &&  yi >= (double)(y)))
        {
          double xx = (double)(xi + (y - yi)/(yj - yi)*(xj - xi));
          nodeX[nodes++] = (double)xx;
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
          int xStart = (int)nodeX[i];
          int xEnd = (int)nodeX[i+1];

          if (((double)nodeX[i] - xStart) > 0)
            xStart++;

          if ((xEnd - (double)nodeX[i+1]) > 0)
            xEnd--;

          for (int x=xStart; x<=xEnd; x++)
          {
            unsigned long long p = (((unsigned long long)x) << 32) + y;
            if (cList.find(p) == cList.end())
              cList.insert(p);
          }
        }
      }
    }

    // Converting the list to the actual PointList.

    for (auto it = cList.begin(); it != cList.end(); ++it)
    {
      int x = (int)((*it) >> 32);
      int y = (int)((*it) & 0xFFFFFFFF);

      gridPoints.push_back(T::Point(x,y));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






void getPointsInsidePolygonPath(int gridWidth,int gridHeight,std::vector<std::vector<T::Coordinate>>& polygonPath,std::vector<T::Point>& gridPoints)
{
  try
  {
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
      uint numOfPoints = (uint)polygonPoints->size();

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
          double yp = (int)it->y();

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
        uint numOfPoints = (uint)polygonPoints->size();

        uint c = 0;
        for (auto it = polygonPoints->begin(); it != polygonPoints->end(); ++it)
        {
          pointsX[c] = it->x();
          pointsY[c] = it->y();
          c++;

          if (c >= 200000)
          {
            throw SmartMet::Spine::Exception(BCP,"Not enough space for the point list!",NULL);
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

          if ((yi < (double)(y)  &&  yj >= (double)(y))  ||  (yj < (double)(y) &&  yi >= (double)(y)))
          {
            double xx = (double)(xi + (y - yi)/(yj - yi)*(xj - xi));
            nodeX[nodes++] = (double)xx;
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
          int xStart = (int)nodeX[i];
          int xEnd = (int)nodeX[i+1];

          if (((double)nodeX[i] - xStart) > 0)
            xStart++;

          if ((xEnd - (double)nodeX[i+1]) > 0)
            xEnd--;

          for (int x=xStart; x<=xEnd; x++)
          {
            unsigned long long p = (((unsigned long long)x) << 32) + y;
            if (cList.find(p) == cList.end())
              cList.insert(p);
          }
        }
      }
    }

    // Converting the list to the actual PointList.

    for (auto it = cList.begin(); it != cList.end(); ++it)
    {
      int x = (int)((*it) >> 32);
      int y = (int)((*it) & 0xFFFFFFFF);

      gridPoints.push_back(T::Point(x,y));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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


    int xx1 = (int)x1;
    int xx2 = (int)x2;
    int yy1 = (int)y1;
    int yy2 = (int)y2;

    for (int y=yy1; y<=yy2; y++)
    {
      double dy = (double)y-origoY;
      for (int x=xx1; x<=xx2; x++)
      {
        double dx = (double)x-origoX;
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
            int t = (int)polygonPoints.size() -1;
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::vector<T::Coordinate> getEnlargedPolygon(std::vector<T::Coordinate>& oldCoordinates,double areaExtensionX,double areaExtensionY,bool rev)
{
  try
  {
    std::vector<T::Coordinate> newCoordinates;

    std::vector<std::pair<T::Coordinate,T::Coordinate>> tmpLines;
    int points = (int)oldCoordinates.size();
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

    int lines = (int)tmpLines.size();
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





double getPolygonLen(std::vector<T::Coordinate>& coordinates)
{
  try
  {
    int points = (int)coordinates.size();
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}

}

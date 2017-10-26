#include "GraphFunctions.h"
#include "Exception.h"


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

    if (x1 == x2  && (x1 - (int)x1) == 0)
    {
      int yStart = (int)y1;
      if ((y1 - yStart) > 0)
        yStart++;

      int yEnd = (int)y2;

      for (int y=yStart; y<=yEnd; y++)
      {
        //printf("VLinePoint %d,%d\n",(int)x1,y);
        unsigned long long p = (((unsigned long long)x1) << 32) + y;
        if (cList.find(p) == cList.end())
          cList.insert(p);
      }

      return;
    }

    if (y1 == y2  && (y1 - (int)y1) == 0)
    {
      if (x2 < x1)
      {
        double tx = x1;
        x1 = x2;
        x2 = tx;
      }

      int xStart = (int)x1;
      if ((x1 - xStart) > 0)
        xStart++;

      int xEnd = (int)x2;

      for (int x=xStart; x<=xEnd; x++)
      {
        //printf("HLinePoint %d,%d\n",x,(int)y1);
        unsigned long long p = (((unsigned long long)x) << 32) + (int)y1;
        if (cList.find(p) == cList.end())
          cList.insert(p);
      }

      return;
    }


    double dy = (y2 - y1);
    double dx = (x2 - x1);

    double dd = dx/dy;

    int yStart = (int)y1;
    if ((y1 - yStart) > 0)
      yStart++;

    int yEnd = (int)y2;

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
            polygonPoints.push_back(polygonPoints[0]);
            polygonPath.push_back(polygonPoints);
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


}

#include "ImageFunctions.h"
#include "Exception.h"

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <jpeglib.h>
#include <math.h>
#include <set>

namespace SmartMet
{


void jpeg_save(const char *filename, unsigned long *image, int image_height,int image_width, int quality)
{
  try
  {
    int size = image_width * image_height;
    unsigned char *image_buffer = new unsigned char[size*3];
    uint c = 0;
    uint p = 0;

    for (int y=0; y<image_height; y++)
    {
      for (int x=0; x<image_width; x++)
      {
        unsigned long col = image[c];
        image_buffer[p++] = (unsigned char)((col & 0xFF0000) >> 16);
        image_buffer[p++] = (unsigned char)((col & 0x00FF00) >> 8);
        image_buffer[p++] = (unsigned char)(col & 0xFF);
        c++;
      }
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE * outfile = NULL;
    JSAMPROW row_pointer[1];
    int row_stride = 0;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    if ((outfile = fopen(filename, "wb")) == NULL)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot create the JPG file!");
      exception.addParameter("Filename",filename);
      throw exception;
    }

    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = image_width;
    cinfo.image_height = image_height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);

    jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);
    jpeg_start_compress(&cinfo, TRUE);
    row_stride = image_width * 3; /* JSAMPLEs per row in image_buffer */

    while (cinfo.next_scanline < cinfo.image_height)
    {
      row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
      (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);

    jpeg_destroy_compress(&cinfo);
    delete image_buffer;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint rgb(uint red, uint green, uint blue)
{
  try
  {
    return (red << 16) + (green << 8) + blue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint hsv_to_rgb(unsigned char hue, unsigned char saturation, unsigned char value)
{
  try
  {
    if (saturation == 0)
    {
      /* color is grayscale */
      return rgb(value,value,value);
    }

    /* make hue 0-5 */
    uint region = hue / 43;
    /* find remainder part, make it from 0-255 */
    uint fpart = (hue - (region * 43)) * 6;

    /* calculate temp vars, doing integer multiplication */
    uint p = (value * (255 - saturation)) >> 8;
    uint q = (value * (255 - ((saturation * fpart) >> 8))) >> 8;
    uint t = (value * (255 - ((saturation * (255 - fpart)) >> 8))) >> 8;

    /* assign temp vars based on color cone region */
    switch(region)
    {
      case 0:
        return rgb(value,t,p);
      case 1:
        return rgb(q,value,p);
      case 2:
        return rgb(p,value,t);
      case 3:
        return rgb(p,q,value);
      case 4:
        return rgb(t,p,value);
      default:
        return rgb(value,p,q);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





static int compare_points(const void *p1, const void *p2)
{
  double *v1 = (double*)p1;
  double *v2 = (double*)p2;

  if (*v1 < *v2)
    return -1;

  if (*v1 > *v2)
    return 1;

  return 0;
}




void addLine(int _x1,int _y1,int _x2,int _y2,std::set<unsigned long long>&  cList)
{
  try
  {
    unsigned long long p = 0;

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

    p = (((unsigned long long)x1) << 32) + y1;
    if (cList.find(p) == cList.end())
      cList.insert(p);

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

        p = (((unsigned long long)x1) << 32) + y1;
        if (cList.find(p) == cList.end())
          cList.insert(p);
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

        p = (((unsigned long long)x1) << 32) + y1;
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
      polygonPoints.push_back(polygonPoints[0]);


    // Adding points that are below the polygon line.

    for (uint t=0; t<numOfPoints; t++)
    {
      addLine(polygonPoints[t].x(),polygonPoints[t].y(),polygonPoints[t+1].x(),polygonPoints[t+1].y(),cList);
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

          int xStart = (int)nodeX[i];
          int xEnd = (int)nodeX[i+1];

          for (int x=xStart; x<xEnd; x++)
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



}

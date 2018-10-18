#pragma once

#include "Exception.h"
#include "Point.h"
#include "Coordinate.h"

#include <newbase/NFmiSvgPath.h>
#include <set>


namespace SmartMet
{


namespace T
{


struct ContourLine
{
  double mX1;
  double mY1;
  double mX2;
  double mY2;
  //double mValue;
  //uint mLevel;
};

typedef std::vector<ContourLine> ContourLine_vec;
}



void getPointsInsideCircle(int gridWidth,int gridHeight,double origoX,double origoY,double radius,std::vector<T::Point>& gridPoints);
void getPointsInsidePolygon(int gridWidth,int gridHeight,std::vector<T::Coordinate>& polygonPoints,std::vector<T::Point>& gridPoints);
void getPointsInsidePolygonPath(int gridWidth,int gridHeight,std::vector<std::vector<T::Coordinate>>& polygonPath,std::vector<T::Point>& gridPoints);

void convertSvgPathToPolygonPath(NFmiSvgPath& svgPath,std::vector<std::vector<T::Coordinate>>& polygonPath);

std::string convertWktMultiPolygonToSvgString(const std::string& wktString);
void convertWktMultipolygonToSvgPath(const std::string& wktString,NFmiSvgPath& svgPath);

void convertWktMultipolygonToPolygonPath(const std::string& wktString,std::vector<std::vector<T::Coordinate>>& polygonPath);

std::vector<T::Coordinate> getEnlargedPolygon(std::vector<T::Coordinate>& oldCoordinates,double areaExtensionX,double areaExtensionY);
std::vector<std::vector<T::Coordinate>> getEnlargedPolygonPath(std::vector<std::vector<T::Coordinate>>& oldPath,double areaExtensionX,double areaExtensionY);


uint getIsolines(std::vector<float>& d,int width,int height,int ilb,int iub,int jlb,int jub,std::vector<float>& z,T::ContourLine *line,uint maxLines);
uint getIsolines(std::vector<double>& d,int width,int height,int ilb,int iub,int jlb,int jub,std::vector<double>& z,T::ContourLine *line,uint maxLines);
uint getIsolines(std::vector<float>& d,int width,int height,int ilb,int iub,int jlb,int jub,std::vector<float>& z,std::vector<T::ContourLine_vec>& lineVecVec);

}


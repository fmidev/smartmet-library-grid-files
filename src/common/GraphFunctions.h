#pragma once

#include "Exception.h"
#include "Point.h"
#include "Coordinate.h"

#include <newbase/NFmiSvgPath.h>
#include <set>


namespace SmartMet
{

void getPointsInsideCircle(int gridWidth,int gridHeight,double origoX,double origoY,double radius,std::vector<T::Point>& gridPoints);
void getPointsInsidePolygon(int gridWidth,int gridHeight,std::vector<T::Coordinate>& polygonPoints,std::vector<T::Point>& gridPoints);
void getPointsInsidePolygonPath(int gridWidth,int gridHeight,std::vector<std::vector<T::Coordinate>>& polygonPath,std::vector<T::Point>& gridPoints);

void convertSvgPathToPolygonPath(NFmiSvgPath& svgPath,std::vector<std::vector<T::Coordinate>>& polygonPath);

std::vector<T::Coordinate> getEnlargedPolygon(std::vector<T::Coordinate>& oldCoordinates,double areaExtensionX,double areaExtensionY);
std::vector<std::vector<T::Coordinate>> getEnlargedPolygonPath(std::vector<std::vector<T::Coordinate>>& oldPath,double areaExtensionX,double areaExtensionY);

}


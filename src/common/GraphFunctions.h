#pragma once

#include "Exception.h"
#include "Point.h"
#include "Coordinate.h"
#include "Typedefs.h"

#include <newbase/NFmiSvgPath.h>
#include <set>
#include <gdal/ogr_spatialref.h>


namespace SmartMet
{


void getPointsInsideCircle(
    int gridWidth,
    int gridHeight,
    double origoX,
    double origoY,
    double radius,
    std::vector<T::Point>& gridPoints);

void getPointsInsidePolygon(
    int gridWidth,
    int gridHeight,
    T::Coordinate_vec& polygonPoints,
    std::vector<T::Point>& gridPoints);

void getPointsInsidePolygonPath(
    int gridWidth,
    int gridHeight,
    T::Polygon_vec&
    polygonPath,
    std::vector<T::Point>& gridPoints);

void convertSvgPathToPolygonPath(
    NFmiSvgPath& svgPath,
    T::Polygon_vec& polygonPath);

std::string convertWktMultiPolygonToSvgString(
    const std::string& wktString);

void convertWktMultipolygonToSvgPath(
    const std::string& wktString,
    NFmiSvgPath& svgPath);

void convertWktMultipolygonToPolygonPath(
    const std::string& wktString,
    T::Polygon_vec& polygonPath);

T::Coordinate_vec getEnlargedPolygon(
    T::Coordinate_vec& oldCoordinates,
    double areaExtensionX,
    double areaExtensionY);

T::Polygon_vec getEnlargedPolygonPath(
    T::Polygon_vec& oldPath,
    double areaExtensionX,
    double areaExtensionY);

void getIsolines(
    std::vector<float>& gridData,
    std::vector<T::Coordinate> *coordinates,
    int width,
    int height,
    std::vector<float>& contourValues,
    short interpolationMethod,
    size_t smooth_size,
    size_t smooth_degree,
    T::WkbData_vec& contours);

void getIsobands(
    std::vector<float>& gridData,
    std::vector<T::Coordinate> *coordinates,
    int width,
    int height,
    std::vector<float>& contourLowValues,
    std::vector<float>& contourHighValues,
    short interpolationMethod,
    size_t smooth_size,
    size_t smooth_degree,
    T::WkbData_vec& contours);

/*
void convertWkbCoordinates(
    T::WkbData& _wkb,
    T::WkbData& _newWkb,
    OGRCoordinateTransformation& _transformation);

void convertWkbCoordinates(
    T::WkbData_vec& _wkbVec,
    T::WkbData_vec& _newWkbVec,
    OGRCoordinateTransformation& _transformation);
*/

}


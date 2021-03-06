#pragma once

#include "Point.h"
#include "Coordinate.h"
#include "Typedefs.h"

#include <macgyver/Exception.h>
#include <newbase/NFmiSvgPath.h>
#include <set>
#include <ogr_spatialref.h>


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


std::size_t getPolygonPathLength(T::Polygon_vec& polygonPath);

void convertToPointVector(
    T::Polygon_vec& polygonPath,
    T::Coordinate_vec& polygonPoints);

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
    T::ByteData_vec& contours);

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
    T::ByteData_vec& contours);

}


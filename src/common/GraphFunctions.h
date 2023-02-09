#pragma once

#include "Point.h"
#include "Coordinate.h"
#include "Typedefs.h"
#include "../grid/Typedefs.h"

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

bool getLineIntersectionPoint(
    double x1,double y1,double x2,double y2,  // Line 1
    double x3,double y3,double x4,double y4,  // Line 2
    double& x,double& y);                     // Intesection point

int findPath(
    std::vector<float>& direction,
    bool *visited,
    int width,int height,
    int maxLength,
    double x1,double y1,
    int level,
    uint cellCount,
    std::vector<T::Coordinate>& coordinates);

int findPath(
    float *direction,
    uint *image,
    int width,int height,
    int maxLength,
    uint backColor,
    double x1,double y1,
    int level,
    uint cellCount,
    std::vector<T::Coordinate>& coordinates);

void getStreamlineImage(
    float *direction,                           // Grid of directions in degrees (size = width x height). For example "wind direction".
    float *value,                               // Grid of values (size = width x height). For example "wind speed"
    uint *image,                                // RGB image (size = width x height). Values >= 0xFF000000 mean tranparent pixels).
    int width,int height,                       // Size of the grids / the image
    int xStep,int yStep,                        // Counting steps
    int minLength,int maxLength,                // Min / max line lengths
    float valueRangeStart,float valueRangeEnd,  // Value range of the "value" grid. Needed for color scaling.
    int startColor,int endColor,                // Start / end of color gradient (0 .. 255).
    uint backColor);                            // Backcolor of the image

void getStreamlineImage(
    float *direction,                           // Grid of directions in degrees (size = width x height). For example "wind direction".
    float *value,                               // Grid of values (size = width x height). For example "wind speed"
    uint *image,                                // RGB image (size = width x height). Values >= 0xFF000000 mean tranparent pixels).
    int width,int height,                       // Size of the grids / the image
    int xStep,int yStep,                        // Counting steps
    int minLength,int maxLength);               // Min / max line lengths


void getStreamlines(
    T::ParamValue_vec& gridValues,
    std::vector<T::Coordinate> *coordinates,
    int width,
    int height,
    int minStreamLen,
    int maxStreamLen,
    int lineLen,
    int xStep,
    int yStep,
    T::ByteData_vec& streamlines);



}

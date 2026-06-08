#pragma once

/*! \file GraphFunctions.h
 *  \brief Geometric helper functions for working with polygons, SVG paths, and WKT
 *  geometries: point-in-polygon tests, grid-point enumeration, and format conversions. */

#include "Point.h"
#include "Coordinate.h"
#include "Typedefs.h"
#include "../grid/Typedefs.h"

#include <macgyver/Exception.h>
#include <newbase/NFmiSvgPath.h>
#include <trax/SmoothOptions.h>
#include <set>
#include <ogr_spatialref.h>


namespace SmartMet
{


/*! \brief Enumerate grid points within a circle.
 *  \param[in]  gridWidth   Grid column count.
 *  \param[in]  gridHeight  Grid row count.
 *  \param[in]  origoX      Circle centre X (grid coordinates).
 *  \param[in]  origoY      Circle centre Y (grid coordinates).
 *  \param[in]  radius      Circle radius in grid units.
 *  \param[out] gridPoints  Receives all (x,y) grid points inside the circle. */
void getPointsInsideCircle(
    int gridWidth,
    int gridHeight,
    double origoX,
    double origoY,
    double radius,
    std::vector<T::Point>& gridPoints);

/*! \brief Enumerate grid points inside a polygon.
 *  \param[in]  gridWidth    Grid column count.
 *  \param[in]  gridHeight   Grid row count.
 *  \param[in]  polygonPoints  Polygon vertices in grid coordinates.
 *  \param[out] gridPoints   Receives all (x,y) grid points inside the polygon. */
void getPointsInsidePolygon(
    int gridWidth,
    int gridHeight,
    T::Coordinate_vec& polygonPoints,
    std::vector<T::Point>& gridPoints);

/*! \brief Enumerate grid points inside a multi-ring polygon path.
 *  \param[in]  gridWidth   Grid column count.
 *  \param[in]  gridHeight  Grid row count.
 *  \param[in]  polygonPath Multi-ring polygon (outer ring + holes).
 *  \param[out] gridPoints  Receives all (x,y) grid points inside the path. */
void getPointsInsidePolygonPath(
    int gridWidth,
    int gridHeight,
    T::Polygon_vec& polygonPath,
    std::vector<T::Point>& gridPoints);


/*! \brief Return the total number of vertices across all rings of a polygon path.
 *  \param[in] polygonPath  Multi-ring polygon.
 *  \return Total vertex count. */
std::size_t getPolygonPathLength(T::Polygon_vec& polygonPath);

/*! \brief Flatten a multi-ring polygon path into a single coordinate vector.
 *  \param[in]  polygonPath    Multi-ring polygon.
 *  \param[out] polygonPoints  Receives all vertices concatenated. */
void convertToPointVector(
    T::Polygon_vec& polygonPath,
    T::Coordinate_vec& polygonPoints);

/*! \brief Convert an NFmiSvgPath to a multi-ring T::Polygon_vec.
 *  \param[in]  svgPath     Source SVG path.
 *  \param[out] polygonPath Receives the converted polygon rings. */
void convertSvgPathToPolygonPath(
    NFmiSvgPath& svgPath,
    T::Polygon_vec& polygonPath);

/*! \brief Convert a WKT MULTIPOLYGON string to an SVG path string.
 *  \param[in] wktString  WKT MULTIPOLYGON geometry.
 *  \return SVG path string. */
std::string convertWktMultiPolygonToSvgString(
    const std::string& wktString);

/*! \brief Convert a WKT MULTIPOLYGON string to an NFmiSvgPath.
 *  \param[in]  wktString  WKT MULTIPOLYGON geometry.
 *  \param[out] svgPath    Receives the converted path. */
void convertWktMultipolygonToSvgPath(
    const std::string& wktString,
    NFmiSvgPath& svgPath);

/*! \brief Convert a WKT MULTIPOLYGON string to a T::Polygon_vec.
 *  \param[in]  wktString   WKT MULTIPOLYGON geometry.
 *  \param[out] polygonPath Receives the converted rings. */
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
    T::ByteData_vec& contours,
    int subdivide = 0,
    const Trax::SmoothOptions& smoothOptions = Trax::SmoothOptions());

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
    T::ByteData_vec& contours,
    int subdivide = 0,
    const Trax::SmoothOptions& smoothOptions = Trax::SmoothOptions());

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

int findPath(
    std::vector<float>& direction,
    uint *image,
    int width,
    int height,
    int maxLength,
    uint backColor,
    double x1, double y1,
    int level,
    uint cellCount,
    std::vector<T::Coordinate> &coordinates);

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

void getStreamlineImage(
    std::vector<float>& direction,
    float *value,
    uint *image,
    int width,
    int height,
    int xStep,
    int yStep,
    int minLength,
    int maxLength);



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

#pragma once

/*! \file InterpolationFunctions.h
 *  \brief Grid value interpolation functions for linear, logarithmic, landscape,
 *  level, and time interpolation methods.  All declarations are in `SmartMet`. */

#include "Typedefs.h"
#include "../grid/Typedefs.h"
#include "../grid/GridValueList.h"

namespace SmartMet
{

/*! \brief Linear interpolation of a scalar value along one axis.
 *  \param[in] wantedPosition  Target position.
 *  \param[in] position1       Position of value1.
 *  \param[in] position2       Position of value2.
 *  \param[in] value1          Value at position1.
 *  \param[in] value2          Value at position2.
 *  \return Interpolated value at wantedPosition. */
double linearInterpolation(double wantedPosition, double position1, double position2, double value1, double value2);

/*! \brief Bilinear interpolation at a point within a 2-D grid cell.
 *  \param[in] x  Target x coordinate.
 *  \param[in] y  Target y coordinate.
 *  \param[in] x1,y1  Bottom-left cell corner.
 *  \param[in] x2,y2  Top-right cell corner.
 *  \param[in] val_q11  Value at (x1,y1).
 *  \param[in] val_q21  Value at (x2,y1).
 *  \param[in] val_q22  Value at (x2,y2).
 *  \param[in] val_q12  Value at (x1,y2).
 *  \return Bilinearly interpolated value. */
double linearInterpolation(double x,double y,double x1,double y1,double x2,double y2,double val_q11,double val_q21,double val_q22,double val_q12);

/*! \brief Logarithmic interpolation of a scalar value along one axis (for pressure levels).
 *  \param[in] wantedPosition  Target position.
 *  \param[in] position1       Position of value1.
 *  \param[in] position2       Position of value2.
 *  \param[in] value1          Value at position1.
 *  \param[in] value2          Value at position2.
 *  \return Logarithmically interpolated value. */
double logarithmicInterpolation(double wantedPosition, double position1, double position2, double value1, double value2);


/*! \brief Interpolate a single value between two vertical levels.
 *  \param[in] value1  Value at level1.
 *  \param[in] value2  Value at level2.
 *  \param[in] level1  First level coordinate.
 *  \param[in] level2  Second level coordinate.
 *  \param[in] newLevel  Target level.
 *  \param[in] levelInterpolationMethod  LevelInterpolationMethod constant.
 *  \return Interpolated value. */
T::ParamValue levelInterpolation(T::ParamValue value1,T::ParamValue value2,double level1,double level2,double newLevel,short levelInterpolationMethod);

/*! \brief Interpolate a full grid value vector between two vertical levels.
 *  \param[in]  values1  Values at level1.
 *  \param[in]  values2  Values at level2.
 *  \param[in]  level1   First level coordinate.
 *  \param[in]  level2   Second level coordinate.
 *  \param[in]  newLevel Target level.
 *  \param[in]  levelInterpolationMethod  LevelInterpolationMethod constant.
 *  \param[out] values   Receives the interpolated values. */
void levelInterpolation(T::ParamValue_vec& values1,T::ParamValue_vec& values2,double level1,double level2,double newLevel,short levelInterpolationMethod,T::ParamValue_vec& values);

//! \overload (operates on GridValueList instead of ParamValue_vec)
void levelInterpolation(T::GridValueList& values1,T::GridValueList& values2,double level1,double level2,double newLevel,short levelInterpolationMethod,T::GridValueList& valueList);

/*! \brief Interpolate a single value between two time steps.
 *  \param[in] value1  Value at time t1.
 *  \param[in] value2  Value at time t2.
 *  \param[in] t1      First time as Unix timestamp.
 *  \param[in] t2      Second time as Unix timestamp.
 *  \param[in] newTime Target time.
 *  \param[in] timeInterpolationMethod  TimeInterpolationMethod constant.
 *  \return Interpolated value. */
T::ParamValue timeInterpolation(T::ParamValue value1,T::ParamValue& value2,time_t t1,time_t t2,time_t newTime,short timeInterpolationMethod);

//! \overload (times given as ISO-8601 strings)
T::ParamValue timeInterpolation(T::ParamValue value1,T::ParamValue& value2,std::string time1,std::string time2,std::string newTime,short timeInterpolationMethod);

/*! \brief Interpolate a full grid (w×h values) between two time steps.
 *  \param[in]  values1  Grid values at t1.
 *  \param[in]  values2  Grid values at t2.
 *  \param[in]  width    Grid width.
 *  \param[in]  height   Grid height.
 *  \param[in]  t1       First time as Unix timestamp.
 *  \param[in]  t2       Second time as Unix timestamp.
 *  \param[in]  newTime  Target time.
 *  \param[in]  timeInterpolationMethod  TimeInterpolationMethod constant.
 *  \param[out] newValues  Receives the interpolated grid. */
void timeInterpolation(T::ParamValue_vec& values1,T::ParamValue_vec& values2,int width,int height,time_t t1,time_t t2,time_t newTime,short timeInterpolationMethod,T::ParamValue_vec& newValues);

//! \overload (times given as ISO-8601 strings)
void timeInterpolation(T::ParamValue_vec& values1,T::ParamValue_vec& values2,int width,int height,std::string time1,std::string time2,std::string newTime,short timeInterpolationMethod,T::ParamValue_vec& newValues);

//! \overload (operates on GridValueList instead of ParamValue_vec)
void timeInterpolation(T::GridValueList& values1,T::GridValueList& values2,time_t t1,time_t t2,time_t newTime,short timeInterpolationMethod,T::GridValueList& valueList);

//! \overload (times as strings, GridValueList)
void timeInterpolation(T::GridValueList& values1,T::GridValueList& values2,std::string time1,std::string time2,std::string newTime,short timeInterpolationMethod,T::GridValueList& valueList);


/*! \brief Landscape-aware spatial interpolation accounting for elevation and land/sea cover.
 *  \param[in] height        Target point elevation.
 *  \param[in] coverType     Land cover type code.
 *  \param[in] x             Fractional x position within the grid cell [0,1].
 *  \param[in] y             Fractional y position within the grid cell [0,1].
 *  \param[in] val_bl        Grid value at bottom-left corner.
 *  \param[in] val_br        Grid value at bottom-right corner.
 *  \param[in] val_tr        Grid value at top-right corner.
 *  \param[in] val_tl        Grid value at top-left corner.
 *  \param[in] height_bl     Elevation at bottom-left corner.
 *  \param[in] height_br     Elevation at bottom-right corner.
 *  \param[in] height_tr     Elevation at top-right corner.
 *  \param[in] height_tl     Elevation at top-left corner.
 *  \param[in] lapserate_bl  Temperature lapse rate at bottom-left corner.
 *  \param[in] lapserate_br  Temperature lapse rate at bottom-right corner.
 *  \param[in] lapserate_tr  Temperature lapse rate at top-right corner.
 *  \param[in] lapserate_tl  Temperature lapse rate at top-left corner.
 *  \param[in] land_bl       Land fraction at bottom-left corner.
 *  \param[in] land_br       Land fraction at bottom-right corner.
 *  \param[in] land_tr       Land fraction at top-right corner.
 *  \param[in] land_tl       Land fraction at top-left corner.
 *  \return Landscape-corrected interpolated value. */
double landscapeInterpolation(
    double height,
    int coverType,
    double x,
    double y,
    double val_bl,
    double val_br,
    double val_tr,
    double val_tl,
    double height_bl,
    double height_br,
    double height_tr,
    double height_tl,
    double lapserate_bl,
    double lapserate_br,
    double lapserate_tr,
    double lapserate_tl,
    double land_bl,
    double land_br,
    double land_tr,
    double land_tl);

}


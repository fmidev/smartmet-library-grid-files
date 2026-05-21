#pragma once

#include "Coordinate.h"

#include <vector>
#include <optional>
#include <ogr_spatialref.h>

/*! \brief Transform an array of coordinates between two OGR spatial references.
 *  \param[in]     sr_from  Source spatial reference.
 *  \param[in]     sr_to    Target spatial reference.
 *  \param[in]     nCount   Number of coordinate pairs.
 *  \param[in,out] x        X (longitude/easting) values in degrees or metres; overwritten.
 *  \param[in,out] y        Y (latitude/northing) values; overwritten.
 *  \return True on success. */
bool convert(const std::shared_ptr<OGRSpatialReference> sr_from,const std::shared_ptr<OGRSpatialReference> sr_to,int nCount,double *x,double *y);


/*! \brief Convert geographic (lat/lon) coordinates to rotated latitude/longitude.
 *  \param[in]  lat          Geographic latitude in degrees.
 *  \param[in]  lon          Geographic longitude in degrees.
 *  \param[in]  southPoleLat Rotated-grid south-pole latitude in degrees.
 *  \param[in]  southPoleLon Rotated-grid south-pole longitude in degrees.
 *  \param[out] rotLat       Rotated latitude in degrees.
 *  \param[out] rotLon       Rotated longitude in degrees. */
void latlon_to_rotatedLatlon(
    double lat,
    double lon,
    double southPoleLat,
    double southPoleLon,
    double& rotLat,
    double& rotLon);


/*! \brief Convert rotated latitude/longitude coordinates to geographic (lat/lon).
 *  \param[in]  rotLat       Rotated latitude in degrees.
 *  \param[in]  rotLon       Rotated longitude in degrees.
 *  \param[in]  southPoleLat Rotated-grid south-pole latitude in degrees.
 *  \param[in]  southPoleLon Rotated-grid south-pole longitude in degrees.
 *  \param[out] lat          Geographic latitude in degrees.
 *  \param[out] lon          Geographic longitude in degrees. */
void rotatedLatlon_to_latlon(
    double rotLat,
    double rotLon,
    double southPoleLat,
    double southPoleLon,
    double& lat,
    double& lon);


/*! \brief Compute the great-circle distance between two geographic points in metres.
 *  \param[in] lat1  Latitude of the first point in degrees.
 *  \param[in] lon1  Longitude of the first point in degrees.
 *  \param[in] lat2  Latitude of the second point in degrees.
 *  \param[in] lon2  Longitude of the second point in degrees.
 *  \return Distance in metres. */
double latlon_distance(double lat1, double lon1, double lat2, double lon2);

/*! \brief Compute the metric width of one degree of longitude at a given latitude.
 *  \param[in] lat         Latitude in degrees.
 *  \param[in] longitudes  Number of longitude degrees.
 *  \return Width in metres. */
double latlon_width(double lat, double longitudes);

/*! \brief Compute the metric height of one degree of latitude.
 *  \param[in] lon        Longitude in degrees (unused for spherical Earth).
 *  \param[in] latitudes  Number of latitude degrees.
 *  \return Height in metres. */
double latlon_height(double lon, double latitudes);


/*! \brief Compute a geographic bounding box centred at (\p centerX, \p centerY) with metric dimensions.
 *  \param[in]  centerX       Centre longitude in degrees.
 *  \param[in]  centerY       Centre latitude in degrees.
 *  \param[in]  metricWidth   Total width in metres.
 *  \param[in]  metricHeight  Total height in metres.
 *  \param[out] lon1          West longitude in degrees.
 *  \param[out] lat1          South latitude in degrees.
 *  \param[out] lon2          East longitude in degrees.
 *  \param[out] lat2          North latitude in degrees. */
void latLon_bboxByCenter(double centerX,double centerY,double metricWidth,double metricHeight,double& lon1,double& lat1,double& lon2,double& lat2);

/*! \brief Compute a geographic bounding box using asymmetric metric offsets from a centre point.
 *  \param[in]  centerX               Centre longitude in degrees.
 *  \param[in]  centerY               Centre latitude in degrees.
 *  \param[in]  metricDistanceLeft    Distance west from centre in metres.
 *  \param[in]  metricDistanceBottom  Distance south from centre in metres.
 *  \param[in]  metricDistanceRight   Distance east from centre in metres.
 *  \param[in]  metricDistanceTop     Distance north from centre in metres.
 *  \param[out] lon1  West longitude in degrees.
 *  \param[out] lat1  South latitude in degrees.
 *  \param[out] lon2  East longitude in degrees.
 *  \param[out] lat2  North latitude in degrees. */
void latLon_bboxByCenter(double centerX,double centerY,double metricDistanceLeft,double metricDistanceBottom,double metricDistanceRight,double metricDistanceTop,double& lon1,double& lat1,double& lon2,double& lat2);

/*! \brief Generate evenly-spaced great-circle arc sample points between two geographic locations.
 *  \param[in] lon1   Start longitude in degrees.
 *  \param[in] lat1   Start latitude in degrees.
 *  \param[in] lon2   End longitude in degrees.
 *  \param[in] lat2   End latitude in degrees.
 *  \param[in] steps  Number of sample points.
 *  \return Pair of (coordinate list, cumulative distance list). */
std::pair<std::vector<SmartMet::T::Coordinate>, std::vector<double>> getIsocirclePoints(double lon1, double lat1, double lon2, double lat2, std::size_t steps);


/*! \brief Normalise a longitude value into the range [-180, 180].
 *  \param[in] lon  Input longitude (may be outside [-180, 180]).
 *  \return Equivalent longitude in [-180, 180]. */
inline double getLongitude(double lon)
{
  if (lon >= -180  &&  lon <= 180)
    return lon;

  // The longitude value is out the acceptable range.
  if (lon < -1000  ||  lon > 1000)
    return lon;

  lon = lon + 180;
  while (lon > 360)
    lon = lon-360;

  lon = lon - 180;
  return lon;
}


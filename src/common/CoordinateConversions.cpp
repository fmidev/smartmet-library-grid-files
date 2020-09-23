#include "CoordinateConversions.h"
#include "GeneralFunctions.h"
#include "GeneralDefinitions.h"

#include <macgyver/Exception.h>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/make_shared.hpp>
#include <gdal/ogr_geometry.h>
#include <gdal/ogr_spatialref.h>

#include <newbase/NFmiLocation.h>



double getValue(double theAngle)
{
  try
  {
    if (::fabs(theAngle - 180) < 0.0000001)
      return 180;
    else if (::fabs(theAngle + 180) < 0.0000001)
      return -180;
    else if (theAngle > 180)
      return getValue(theAngle - 360);
    else if (theAngle < -180)
      return getValue(theAngle + 360);

    return theAngle;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void latlon_to_rotatedLatlon(double lat,double lon,double southPoleLat,double southPoleLon,double& rotLat,double& rotLon)
{
  try
  {
    if (southPoleLat == -90)
    {
      rotLat = lat;
      rotLon = lon;
      return;
    }

    double SinYPole = sin((southPoleLat + 90) * kDegToRad);
    double CosYPole = cos((southPoleLat + 90) * kDegToRad);

    double SinXReg = sin((lon - southPoleLon) * kDegToRad);
    double CosXReg = cos((lon - southPoleLon) * kDegToRad);
    double SinYReg = sin(lat * kDegToRad);
    double CosYReg = cos(lat * kDegToRad);
    double SinYRot = CosYPole * SinYReg - SinYPole * CosYReg * CosXReg;
    SinYRot = std::min(std::max(SinYRot, -1.), 1.);
    double YRot = asin(SinYRot) * kOneRad;

    double CosYRot = cos(YRot * kDegToRad);
    double CosXRot = (CosYPole * CosYReg * CosXReg + SinYPole * SinYReg) / CosYRot;
    CosXRot = std::min(std::max(CosXRot, -1.), 1.);
    double SinXRot = CosYReg * SinXReg / CosYRot;
    double XRot = acos(CosXRot) * kOneRad;
    if (SinXRot < 0.)
      XRot = getValue(-XRot);
    else
      XRot = getValue(XRot);

    rotLon = XRot;
    rotLat = YRot;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void rotatedLatlon_to_latlon(double rotLat,double rotLon,double southPoleLat,double southPoleLon,double& lat,double& lon)
{
  try
  {
    if (southPoleLat == -90)
    {
      lat = rotLat;
      lon = rotLon;
      return;
    }

    double SinYPole = sin((southPoleLat + 90) * kDegToRad);
    double CosYPole = cos((southPoleLat + 90) * kDegToRad);

    double SinXRot = sin(rotLon * kDegToRad);
    double CosXRot = cos(rotLon * kDegToRad);
    double SinYRot = sin(rotLat * kDegToRad);
    double CosYRot = cos(rotLat * kDegToRad);
    double SinYReg = CosYPole * SinYRot + SinYPole * CosYRot * CosXRot;
    SinYReg = std::min(std::max(SinYReg, -1.0), 1.0);

    double YReg = asin(SinYReg) * kOneRad;

    double CosYReg = cos(YReg * kDegToRad);
    double CosXReg = (CosYPole * CosYRot * CosXRot - SinYPole * SinYRot) / CosYReg;
    CosXReg = std::min(std::max(CosXReg, -1.0), 1.0);
    double SinXReg = CosYRot * SinXRot / CosYReg;

    double XRegVal = acos(CosXReg) * kOneRad;
    if (SinXReg < 0.)
      XRegVal = -XRegVal;

    XRegVal = XRegVal + southPoleLon;
    double XReg = XRegVal;

    lat = YReg;
    lon = XReg;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




double latlon_distance(double lat1, double lon1, double lat2, double lon2)
{
  double p = 0.017453292519943295;    // Math.PI / 180
  double a = 0.5 - cos((lat2 - lat1) * p)/2 +
          cos(lat1 * p) * cos(lat2 * p) *
          (1 - cos((lon2 - lon1) * p))/2;

  return 12742 * asin(sqrt(a)); // 2 * R; R = 6371 km
}



std::pair<std::vector<SmartMet::T::Coordinate>, std::vector<double>> getIsocirclePoints(double lon1, double lat1, double lon2, double lat2, std::size_t steps)
{
  try
  {
    // Sanity checks
    if (lon1 == lon2 && lat1 == lat2)
      throw Fmi::Exception(BCP, "Ill-defined isocircle: start and end points are equal");

    if (std::abs(lon1 - lon2) == 180 && std::abs(lat1 - (90 - lat2)) == 90)
      throw Fmi::Exception(BCP, "Ill-defined isocircle: points at opposing ends of the earth");

    if (steps < 1 || steps > 10000)
      throw Fmi::Exception(BCP,"Number of points on isocircle must be 1-10000, not " + boost::lexical_cast<std::string>(steps));

    // Calculate bearing and distance to be travelled

    NFmiLocation startpoint(lon1, lat1);
    NFmiLocation endpoint(lon2, lat2);

    double bearing = startpoint.Direction(endpoint);
    double distance = startpoint.Distance(endpoint);

    std::vector<SmartMet::T::Coordinate> coordinates;
    auto cc = startpoint.GetLocation();
    coordinates.push_back(SmartMet::T::Coordinate(cc.X(),cc.Y()));

    std::vector<double> distances;
    distances.push_back(0);

    for (std::size_t i = 1; i < steps; i++)
    {
      // Should this be fixed? Probably not - the coordinates should behave the same
      const bool pacific_view = false;
      double dist = i * distance / steps;
      auto loc = startpoint.GetLocation(bearing, dist, pacific_view);
      auto cc = loc.GetLocation();
      coordinates.push_back(SmartMet::T::Coordinate(cc.X(),cc.Y()));
      distances.push_back(dist / 1000.0);
    }
    cc = endpoint.GetLocation();
    coordinates.push_back(SmartMet::T::Coordinate(cc.X(),cc.Y()));
    distances.push_back(distance / 1000.0);

    return std::make_pair(coordinates, distances);
  }
  catch (...)
  {
    throw Fmi::Exception::Trace(BCP, "Operation failed!");
  }
}




void latLon_bboxByCenter(double centerX,double centerY,double metricWidth,double metricHeight,double& lon1,double& lat1,double& lon2,double& lat2)
{
  try
  {
    OGRSpatialReference sr_latlon;
    sr_latlon.importFromEPSG(4326);

    OGRSpatialReference sr_wgs84_world_mercator;
    sr_wgs84_world_mercator.importFromEPSG(3395);

    OGRCoordinateTransformation *transformation = OGRCreateCoordinateTransformation(&sr_latlon,&sr_wgs84_world_mercator);
    OGRCoordinateTransformation *reverseTransformation = OGRCreateCoordinateTransformation(&sr_wgs84_world_mercator,&sr_latlon);

    transformation->Transform(1,&centerX,&centerY);

    double xx1 = centerX - metricWidth/2;
    double yy1 = centerY - metricHeight/2;
    double xx2 = centerX + metricWidth/2;
    double yy2 = centerY + metricHeight/2;

    // Converting metric coordinates to latlon coordinates.

    reverseTransformation->Transform(1,&xx1,&yy1);
    reverseTransformation->Transform(1,&xx2,&yy2);

    if (transformation != nullptr)
      OCTDestroyCoordinateTransformation(transformation);

    if (reverseTransformation != nullptr)
      OCTDestroyCoordinateTransformation(reverseTransformation);

    lon1 = xx1;
    lat1 = yy1;
    lon2 = xx2;
    lat2 = yy2;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






#if 0
void getBoundingBox(
    boost::optional<std::string> crs,
    boost::optional<std::string> bboxcrs,
    boost::optional<int> xsize,
    boost::optional<int> ysize,
    boost::optional<double> x1,
    boost::optional<double> y1,
    boost::optional<double> x2,
    boost::optional<double> y2,
    boost::optional<double> cx,
    boost::optional<double> cy,
    boost::optional<double> resolution,
    bool latlon_center,
    double& xx1,
    double& yy1,
    double& yy2,
    double& xx2)
{
  try
  {
    boost::shared_ptr<OGRSpatialReference> ogr_crs;

    if (!crs)
      throw Fmi::Exception(BCP, "CRS not set, unable to create projection");

    if (!xsize && !ysize)
      throw Fmi::Exception(BCP, "CRS xsize and ysize are both missing");

    // Are subdefinitions complete?
    bool full_rect_bbox = (x1 && y1 && x2 && y2);
    bool full_center_bbox = (cx && cy && resolution);

    // Are they partial?
    bool partial_rect_bbox = !full_rect_bbox && (x1 || y1 || x2 || y2);
    bool partial_center_bbox = !full_center_bbox && (cx || cy || resolution);

    // Disallow partial definitions
    if (partial_rect_bbox)
      throw Fmi::Exception(BCP, "Partial CRS bounding box given: x1,y1,x2,y2 are needed");

    if (partial_center_bbox)
      throw Fmi::Exception(BCP, "Partial CRS bounding box given: cx,cy,resolution are needed");

    // bbox definition missing completely?
    if (!full_rect_bbox && !full_center_bbox)
      throw Fmi::Exception(BCP, "CRS bounding box missing: x1,y2,x2,y2 or cx,cy,resolution are needed");

    // must give both width and height if centered bbox is given
    if (!full_rect_bbox && full_center_bbox && (!xsize || !ysize))
      throw Fmi::Exception(BCP, "CRS xsize and ysize are required when a centered bounding box is used");

    // Create the CRS
    ogr_crs = boost::make_shared<OGRSpatialReference>();
    OGRErr err = ogr_crs->SetFromUserInput(crs->c_str());

    if (err != OGRERR_NONE)
      throw Fmi::Exception(BCP, "Unknown CRS: '" + *crs + "'");

    if (xsize && *xsize <= 0)
      throw Fmi::Exception(BCP, "Projection xsize must be positive");

    if (ysize && *ysize <= 0)
      throw Fmi::Exception(BCP, "Projection ysize must be positive");

    // World XY bounding box will be calculated during the process

    double XMIN, YMIN, XMAX, YMAX;

    // Create the Contour::Area object

    if (full_rect_bbox)
    {
      // rect bounding box

      XMIN = *x1;
      YMIN = *y1;
      XMAX = *x2;
      YMAX = *y2;

      if (bboxcrs)
      {
        // Reproject corners coordinates from bboxcrs to crs
        OGRSpatialReference ogr_crs2;
        err = ogr_crs2.SetFromUserInput(bboxcrs->c_str());
        if (err != OGRERR_NONE)
          throw Fmi::Exception(BCP, "Unknown CRS: '" + *bboxcrs + "'");

        boost::shared_ptr<OGRCoordinateTransformation> transformation(OGRCreateCoordinateTransformation(&ogr_crs2, ogr_crs.get()));
        transformation->Transform(1, &XMIN, &YMIN);
        transformation->Transform(1, &XMAX, &YMAX);
      }

      if (XMIN == XMAX || YMIN == YMAX)
        throw Fmi::Exception(BCP, "Bounding box size is zero!");

      if (!xsize)
      {
        // Preserve aspect by calculating xsize
        int w = boost::numeric_cast<int>((*ysize) * (XMAX - XMIN) / (YMAX - YMIN));
        xx1 = XMIN; yy1 = YMIN; xx2 = XMAX; yy2 = YMAX;
        //box = Fmi::Box(XMIN, YMIN, XMAX, YMAX, w, *ysize);
      }
      else if (!ysize)
      {
        // Preserve aspect by calculating ysize
        int h = boost::numeric_cast<int>((*xsize) * (YMAX - YMIN) / (XMAX - XMIN));
        xx1 = XMIN; yy1 = YMIN; xx2 = XMAX; yy2 = YMAX;
        //box = Fmi::Box(XMIN, YMIN, XMAX, YMAX, *xsize, h);
      }
      else
      {
        xx1 = XMIN; yy1 = YMIN; xx2 = XMAX; yy2 = YMAX;
        // box = Fmi::Box(XMIN, YMIN, XMAX, YMAX, *xsize, *ysize);
      }

      if (ogr_crs->IsGeographic() != 0)
      {
        // Substract equations 5 and 4, subsititute equation 3 and solve resolution
        double pi = boost::math::constants::pi<double>();
        double circumference = 2 * pi * 6371.220;
        resolution = (YMAX - YMIN) * circumference / (360 * (*ysize));
        ;
      }
      else
      {
        // Substract equations 1 and 2 to eliminate and solve resolution
        resolution = (XMAX - XMIN) / ((*xsize) * 1000);
      }
    }

    else
    {
      // centered bounding box
      if (!xsize || !ysize)
        throw Fmi::Exception(BCP, "xsize and ysize are required when a centered bounding box is used");

      double CX = *cx, CY = *cy;

      if (latlon_center || (bboxcrs && *crs != *bboxcrs))
      {
        // Reproject center coordinates from latlon/bboxcrs to crs
        OGRSpatialReference ogr_crs2;
        if (latlon_center)
          err = ogr_crs2.SetFromUserInput("WGS84");
        else
          err = ogr_crs2.SetFromUserInput(bboxcrs->c_str());

        if (err != OGRERR_NONE)
          throw Fmi::Exception(BCP, "Unknown CRS: '" + *bboxcrs + "'");

        boost::shared_ptr<OGRCoordinateTransformation> transformation(OGRCreateCoordinateTransformation(&ogr_crs2, ogr_crs.get()));
        transformation->Transform(1, &CX, &CY);
      }

      if (ogr_crs->IsGeographic() != 0)
      {
        double pi = boost::math::constants::pi<double>();
        double circumference = 2 * pi * 6371.220;

        // This will work well, since we move along an isocircle
        double dy = 360 * (*ysize) / 2.0 * (*resolution) / circumference;  // Equation 3.
        YMIN = CY - dy;                                                    // Equation 4.
        YMAX = CY + dy;                                                    // Equation 5

        // Distances will become distorted the further away we are from the equator
        double dx = 360 * (*xsize) / 2.0 * (*resolution) / circumference / cos(CX * pi / 180.0);
        XMIN = CX - dx;
        XMAX = CX + dx;

        xx1 = XMIN; yy1 = YMIN; xx2 = XMAX; yy2 = YMAX;
      }
      else
      {
        XMIN = CX - (*xsize) / 2.0 * (*resolution) * 1000;  // Equation 1.
        XMAX = CX + (*xsize) / 2.0 * (*resolution) * 1000;  // Equation 2.
        YMIN = CY - (*ysize) / 2.0 * (*resolution) * 1000;
        YMAX = CY + (*ysize) / 2.0 * (*resolution) * 1000;

        xx1 = XMIN; yy1 = YMIN; xx2 = XMAX; yy2 = YMAX;
      }
    }

    // newbase corners calculated from world xy coordinates

    const char* fmiwkt = R"xxx(GEOGCS["FMI_Sphere",DATUM["FMI_2007",SPHEROID["FMI_Sphere",)xxx"
                         R"xxx(6371220,0]],PRIMEM["Greenwich",0],UNIT["Degree",0.)xxx"
                         R"xxx(0174532925199433]])xxx";
    OGRSpatialReference fmi;
    err = fmi.SetFromUserInput(fmiwkt);

    if (err != OGRERR_NONE)
      throw Fmi::Exception(BCP, "Unable to parse FMI WKT");

    boost::shared_ptr<OGRCoordinateTransformation> transformation(OGRCreateCoordinateTransformation(ogr_crs.get(), &fmi));

    // Calculate bottom left and top right coordinates

    printf("*** BOX %f,%f,%f,%f\n",XMIN,YMIN,XMAX,YMAX);

    transformation->Transform(1, &XMIN, &YMIN);
    transformation->Transform(1, &XMAX, &YMAX);

    xx1 = XMIN; yy1 = YMIN; xx2 = XMAX; yy2 = YMAX;

    printf("BOX %f,%f,%f,%f\n",XMIN,YMIN,XMAX,YMAX);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}
#endif

#include "CoordinateConversions.h"
#include "GeneralFunctions.h"
#include "GeneralDefinitions.h"
#include "Exception.h"




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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





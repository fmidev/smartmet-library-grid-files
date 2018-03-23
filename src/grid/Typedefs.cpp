#include "Typedefs.h"
#include "common/Exception.h"


namespace SmartMet
{
namespace T
{


std::string get_fileTypeString(FileType fileType)
{
  try
  {
    switch (fileType)
    {
      case FileType::Unknown:
        return "Unknown";

      case FileType::Grib1:
        return "GRIB 1";

      case FileType::Grib2:
        return "GRIB 2";

      case FileType::Virtual:
        return "Virtual";
    }
    return "Undefined";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string get_gridLayoutString(GridLayout layout)
{
  try
  {
    switch (layout)
    {
      case GridLayout::Regular:
        return "Reqular";

      case GridLayout::Irregular:
        return "Irregular";

      case GridLayout::Points:
        return "Points";

      case GridLayout::Data:
        return "Data";
    }
    return "Undefined";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string get_areaInterpolationMethodString(short interpolationMethod)
{
  try
  {
    switch (interpolationMethod)
    {
      case AreaInterpolationMethod::None:
        return "None";

      case AreaInterpolationMethod::Linear:
        return "Linear";

      case AreaInterpolationMethod::Nearest:
        return "Nearest";

      case AreaInterpolationMethod::External:
        return "External";

      case AreaInterpolationMethod::Undefined:
        return "Undefined";
    }
    return "Undefined";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string get_timeInterpolationMethodString(short interpolationMethod)
{
  try
  {
    switch (interpolationMethod)
    {
      case TimeInterpolationMethod::None:
        return "None";

      case TimeInterpolationMethod::Linear:
        return "Linear";

      case TimeInterpolationMethod::Nearest:
        return "Nearest";

      case TimeInterpolationMethod::External:
        return "External";

      case TimeInterpolationMethod::Undefined:
        return "Undefined";
    }
    return "Undefined";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string get_levelInterpolationMethodString(short interpolationMethod)
{
  try
  {
    switch (interpolationMethod)
    {
      case LevelInterpolationMethod::None:
        return "None";

      case LevelInterpolationMethod::Linear:
        return "Linear";

      case LevelInterpolationMethod::Nearest:
        return "Nearest";

      case LevelInterpolationMethod::Logarithmic:
        return "Logarithmic";

      case LevelInterpolationMethod::External:
        return "External";

      case LevelInterpolationMethod::Undefined:
        return "Undefined";
    }
    return "Undefined";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string get_gridProjectionString(GridProjection gridType)
{
  try
  {
    switch (gridType)
    {
      case GridProjection::Unknown:
        return "Unknown";
      case GridProjection::LatLon:
        return "LatLon";
      case GridProjection::RotatedLatLon:
        return "RotatedLatLon";
      case GridProjection::StretchedLatLon:
        return "StretchedLatLon";
      case GridProjection::StretchedRotatedLatLon:
        return "StretchedRotatedLatLon";
      case GridProjection::VariableResolutionLatLon:
        return "VariableResolutionLatLon";
      case GridProjection::VariableResolutionRotatedLatLon:
        return "VariableResolutionRotatedLatLon";
      case GridProjection::Mercator:
        return "Mercator";
      case GridProjection::TransverseMercator:
        return "TransverseMercator";
      case GridProjection::PolarStereographic:
        return "PolarStereographic";
      case GridProjection::LambertConformal:
        return "LambertConformal";
      case GridProjection::ObliqueLambertConformal:
        return "ObliqueLambertConformal";
      case GridProjection::Albers:
        return "Albers";
      case GridProjection::Gaussian:
        return "Gaussian";
      case GridProjection::RotatedGaussian:
        return "RotatedGaussian";
      case GridProjection::StretchedGaussian:
        return "StretchedGaussian";
      case GridProjection::StretchedRotatedGaussian:
        return "StretchedRotatedGaussian";
      case GridProjection::SphericalHarmonic:
        return "SphericalHarmonic";
      case GridProjection::RotatedSphericalHarmonic:
        return "RotatedSphericalHarmonic";
      case GridProjection::StretchedSphericalHarmonic:
        return "StretchedSphericalHarmonic";
      case GridProjection::StretchedRotatedSphericalHarmonic:
        return "StretchedRotatedSphericalHarmonic";
      case GridProjection::SpaceView:
        return "SpaceView";
      case GridProjection::Triangular:
        return "Triangular";
      case GridProjection::Unstructured:
        return "Unstructured";
      case GridProjection::EquatorialAzimuthalEquidistant:
        return "EquatorialAzimuthalEquidistant";
      case GridProjection::AzimuthRange:
        return "AzimuthRange";
      case GridProjection::IrregularLatLon:
        return "IrregularLatLon";
      case GridProjection::LambertAzimuthalEqualArea:
        return "LambertAzimuthalEqualArea";
      case GridProjection::CrossSection:
        return "CrossSection";
      case GridProjection::Hovmoller:
        return "Hovmoller";
      case GridProjection::TimeSection:
        return "TimeSection";
      case GridProjection::GnomonicProjection:
        return "GnomonicProjection";
      case GridProjection::SimplePolyconicProjection:
        return "SimplePolyconicProjection";
      case GridProjection::MillersCylindricalProjection:
        return "MillersCylindricalProjection";
    }

    return "Undefined";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}

}
}

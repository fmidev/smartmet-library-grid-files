#include "Typedefs.h"
#include "../common/Exception.h"


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
      case FileTypeValue::Unknown:
        return "Unknown";

      case FileTypeValue::Grib1:
        return "GRIB 1";

      case FileTypeValue::Grib2:
        return "GRIB 2";

      case FileTypeValue::Virtual:
        return "Virtual";
    }
    return "Undefined";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string get_gridLayoutString(GridLayout layout)
{
  try
  {
    switch (layout)
    {
      case GridLayoutValue::Unknown:
        return "Unknown";

      case GridLayoutValue::Regular:
        return "Reqular";

      case GridLayoutValue::Irregular:
        return "Irregular";

      case GridLayoutValue::Points:
        return "Points";

      case GridLayoutValue::Data:
        return "Data";
    }
    return "Undefined";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

      case AreaInterpolationMethod::Min:
        return "Min";

      case AreaInterpolationMethod::Max:
        return "Max";

      case AreaInterpolationMethod::External:
        return "External";

      case AreaInterpolationMethod::Undefined:
        return "Undefined";
    }
    return "Undefined";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

      case TimeInterpolationMethod::Min:
        return "Min";

      case TimeInterpolationMethod::Max:
        return "Max";

      case TimeInterpolationMethod::External:
        return "External";

      case TimeInterpolationMethod::Undefined:
        return "Undefined";
    }
    return "Undefined";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

      case LevelInterpolationMethod::Min:
        return "Min";

      case LevelInterpolationMethod::Max:
        return "Max";

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string get_gridProjectionString(GridProjection projection)
{
  try
  {
    switch (projection)
    {
      case GridProjectionValue::Unknown:
        return "Unknown";
      case GridProjectionValue::LatLon:
        return "LatLon";
      case GridProjectionValue::RotatedLatLon:
        return "RotatedLatLon";
      case GridProjectionValue::StretchedLatLon:
        return "StretchedLatLon";
      case GridProjectionValue::StretchedRotatedLatLon:
        return "StretchedRotatedLatLon";
      case GridProjectionValue::VariableResolutionLatLon:
        return "VariableResolutionLatLon";
      case GridProjectionValue::VariableResolutionRotatedLatLon:
        return "VariableResolutionRotatedLatLon";
      case GridProjectionValue::Mercator:
        return "Mercator";
      case GridProjectionValue::TransverseMercator:
        return "TransverseMercator";
      case GridProjectionValue::PolarStereographic:
        return "PolarStereographic";
      case GridProjectionValue::LambertConformal:
        return "LambertConformal";
      case GridProjectionValue::ObliqueLambertConformal:
        return "ObliqueLambertConformal";
      case GridProjectionValue::Albers:
        return "Albers";
      case GridProjectionValue::Gaussian:
        return "Gaussian";
      case GridProjectionValue::RotatedGaussian:
        return "RotatedGaussian";
      case GridProjectionValue::StretchedGaussian:
        return "StretchedGaussian";
      case GridProjectionValue::StretchedRotatedGaussian:
        return "StretchedRotatedGaussian";
      case GridProjectionValue::SphericalHarmonic:
        return "SphericalHarmonic";
      case GridProjectionValue::RotatedSphericalHarmonic:
        return "RotatedSphericalHarmonic";
      case GridProjectionValue::StretchedSphericalHarmonic:
        return "StretchedSphericalHarmonic";
      case GridProjectionValue::StretchedRotatedSphericalHarmonic:
        return "StretchedRotatedSphericalHarmonic";
      case GridProjectionValue::SpaceView:
        return "SpaceView";
      case GridProjectionValue::Triangular:
        return "Triangular";
      case GridProjectionValue::Unstructured:
        return "Unstructured";
      case GridProjectionValue::EquatorialAzimuthalEquidistant:
        return "EquatorialAzimuthalEquidistant";
      case GridProjectionValue::AzimuthRange:
        return "AzimuthRange";
      case GridProjectionValue::IrregularLatLon:
        return "IrregularLatLon";
      case GridProjectionValue::LambertAzimuthalEqualArea:
        return "LambertAzimuthalEqualArea";
      case GridProjectionValue::CrossSection:
        return "CrossSection";
      case GridProjectionValue::Hovmoller:
        return "Hovmoller";
      case GridProjectionValue::TimeSection:
        return "TimeSection";
      case GridProjectionValue::GnomonicProjection:
        return "GnomonicProjection";
      case GridProjectionValue::SimplePolyconicProjection:
        return "SimplePolyconicProjection";
      case GridProjectionValue::MillersCylindricalProjection:
        return "MillersCylindricalProjection";
    }

    return "Undefined";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}

}
}

#include "Properties.h"
#include "../common/Exception.h"


namespace SmartMet
{
namespace GRIB1
{

Property gribProperty;



Property::Property()
{
  try
  {
    addProperty("Grib1.IndicatorSection.EditionNumber",IndicatorSection::EditionNumber);

    addProperty("Grib1.ProductSection.TableVersion",ProductSection::TableVersion);
    addProperty("Grib1.ProductSection.Centre",ProductSection::Centre);
    addProperty("Grib1.ProductSection.GeneratingProcessIdentifier",ProductSection::GeneratingProcessIdentifier);
    addProperty("Grib1.ProductSection.GridDefinitionNumber",ProductSection::GridDefinitionNumber);
    addProperty("Grib1.ProductSection.SectionFlags",ProductSection::SectionFlags);
    addProperty("Grib1.ProductSection.IndicatorOfParameter",ProductSection::IndicatorOfParameter);
    addProperty("Grib1.ProductSection.IndicatorOfTypeOfLevel",ProductSection::IndicatorOfTypeOfLevel);
    addProperty("Grib1.ProductSection.Level",ProductSection::Level);
    addProperty("Grib1.ProductSection.YearOfCentury",ProductSection::YearOfCentury);
    addProperty("Grib1.ProductSection.Month",ProductSection::Month);
    addProperty("Grib1.ProductSection.Day",ProductSection::Day);
    addProperty("Grib1.ProductSection.Hour",ProductSection::Hour);
    addProperty("Grib1.ProductSection.Minute",ProductSection::Minute);
    addProperty("Grib1.ProductSection.UnitOfTimeRange",ProductSection::UnitOfTimeRange);
    addProperty("Grib1.ProductSection.P1",ProductSection::P1);
    addProperty("Grib1.ProductSection.P2",ProductSection::P2);
    addProperty("Grib1.ProductSection.TimeRangeIndicator",ProductSection::TimeRangeIndicator);
    addProperty("Grib1.ProductSection.NumberIncludedInAverage",ProductSection::NumberIncludedInAverage);
    addProperty("Grib1.ProductSection.NumberMissingFromAveragesOrAccumulations",ProductSection::NumberMissingFromAveragesOrAccumulations);
    addProperty("Grib1.ProductSection.CenturyOfReferenceTimeOfData",ProductSection::CenturyOfReferenceTimeOfData);
    addProperty("Grib1.ProductSection.SubCentre",ProductSection::SubCentre);
    addProperty("Grib1.ProductSection.DecimalScaleFactor",ProductSection::DecimalScaleFactor);
    addProperty("Grib1.ProductSection.ForecastType",ProductSection::ForecastType);
    addProperty("Grib1.ProductSection.ForecastNumber",ProductSection::ForecastNumber);

    addProperty("Grib1.DataSection.Flags",DataSection::Flags);
    addProperty("Grib1.DataSection.BinaryScaleFactor",DataSection::BinaryScaleFactor);
    addProperty("Grib1.DataSection.ReferenceValue",DataSection::ReferenceValue);
    addProperty("Grib1.DataSection.BitsPerValue",DataSection::BitsPerValue);
    addProperty("Grib1.DataSection.PackingMethod",DataSection::PackingMethod);

    addProperty("Grib1.GridSection.NumberOfVerticalCoordinateValues",GridSection::NumberOfVerticalCoordinateValues);
    addProperty("Grib1.GridSection.PvlLocation",GridSection::PvlLocation);
    addProperty("Grib1.GridSection.DataRepresentationType",GridSection::DataRepresentationType);

    addProperty("Grib1.GridSection.LatLon.Ni",GridSection::LatLon::Ni);
    addProperty("Grib1.GridSection.LatLon.Nj",GridSection::LatLon::Nj);
    addProperty("Grib1.GridSection.LatLon.IDirectionIncrement",GridSection::LatLon::IDirectionIncrement);
    addProperty("Grib1.GridSection.LatLon.JDirectionIncrement",GridSection::LatLon::JDirectionIncrement);

    addProperty("Grib1.GridSection.RotatedLatLon.Ni",GridSection::RotatedLatLon::Ni);
    addProperty("Grib1.GridSection.RotatedLatLon.Nj",GridSection::RotatedLatLon::Nj);
    addProperty("Grib1.GridSection.RotatedLatLon.IDirectionIncrement",GridSection::RotatedLatLon::IDirectionIncrement);
    addProperty("Grib1.GridSection.RotatedLatLon.JDirectionIncrement",GridSection::RotatedLatLon::JDirectionIncrement);

    addProperty("Grib1.GridSection.PolarStereographic.Nx",GridSection::PolarStereographic::Nx);
    addProperty("Grib1.GridSection.PolarStereographic.Ny",GridSection::PolarStereographic::Ny);
    addProperty("Grib1.GridSection.PolarStereographic.LatitudeOfFirstGridPoint",GridSection::PolarStereographic::LatitudeOfFirstGridPoint);
    addProperty("Grib1.GridSection.PolarStereographic.LongitudeOfFirstGridPoint",GridSection::PolarStereographic::LongitudeOfFirstGridPoint);
    addProperty("Grib1.GridSection.PolarStereographic.OrientationOfTheGrid",GridSection::PolarStereographic::OrientationOfTheGrid);
    addProperty("Grib1.GridSection.PolarStereographic.DxInMetres",GridSection::PolarStereographic::DxInMetres);
    addProperty("Grib1.GridSection.PolarStereographic.DyInMetres",GridSection::PolarStereographic::DyInMetres);
    addProperty("Grib1.GridSection.PolarStereographic.ProjectionCentreFlag",GridSection::PolarStereographic::ProjectionCentreFlag);

    addProperty("Grib1.GridSection.LambertConformal.Nx",GridSection::LambertConformal::Nx);
    addProperty("Grib1.GridSection.LambertConformal.Ny",GridSection::LambertConformal::Ny);
    addProperty("Grib1.GridSection.LambertConformal.LatitudeOfFirstGridPoint",GridSection::LambertConformal::LatitudeOfFirstGridPoint);
    addProperty("Grib1.GridSection.LambertConformal.LongitudeOfFirstGridPoint",GridSection::LambertConformal::LongitudeOfFirstGridPoint);
    addProperty("Grib1.GridSection.LambertConformal.LoV",GridSection::LambertConformal::LoV);
    addProperty("Grib1.GridSection.LambertConformal.DxInMetres",GridSection::LambertConformal::DxInMetres);
    addProperty("Grib1.GridSection.LambertConformal.DyInMetres",GridSection::LambertConformal::DyInMetres);
    addProperty("Grib1.GridSection.LambertConformal.ProjectionCentreFlag",GridSection::LambertConformal::ProjectionCentreFlag);
    addProperty("Grib1.GridSection.LambertConformal.Latin1",GridSection::LambertConformal::Latin1);
    addProperty("Grib1.GridSection.LambertConformal.Latin2",GridSection::LambertConformal::Latin2);
    addProperty("Grib1.GridSection.LambertConformal.LatitudeOfSouthernPole",GridSection::LambertConformal::LatitudeOfSouthernPole);
    addProperty("Grib1.GridSection.LambertConformal.LongitudeOfSouthernPole",GridSection::LambertConformal::LongitudeOfSouthernPole);

    addProperty("Grib1.GridSection.Mercator.Ni",GridSection::Mercator::Ni);
    addProperty("Grib1.GridSection.Mercator.Nj",GridSection::Mercator::Nj);
    addProperty("Grib1.GridSection.Mercator.Latin",GridSection::Mercator::Latin);
    addProperty("Grib1.GridSection.Mercator.DiInMetres",GridSection::Mercator::DiInMetres);
    addProperty("Grib1.GridSection.Mercator.DjInMetres",GridSection::Mercator::DjInMetres);

    addProperty("Grib1.GridSection.GridArea.LatitudeOfFirstGridPoint",GridSection::GridArea::LatitudeOfFirstGridPoint);
    addProperty("Grib1.GridSection.GridArea.LongitudeOfFirstGridPoint",GridSection::GridArea::LongitudeOfFirstGridPoint);
    addProperty("Grib1.GridSection.GridArea.LatitudeOfLastGridPoint",GridSection::GridArea::LatitudeOfLastGridPoint);
    addProperty("Grib1.GridSection.GridArea.LongitudeOfLastGridPoint",GridSection::GridArea::LongitudeOfLastGridPoint);

    addProperty("Grib1.GridSection.ResolutionFlags.ResolutionAndComponentFlags",GridSection::ResolutionFlags::ResolutionAndComponentFlags);

    addProperty("Grib1.GridSection.ScanningMode.ScanMode",GridSection::ScanningMode::ScanMode);

    addProperty("Grib1.GridSection.Rotation.LatitudeOfSouthernPole",GridSection::Rotation::LatitudeOfSouthernPole);
    addProperty("Grib1.GridSection.Rotation.LongitudeOfSouthernPole",GridSection::Rotation::LongitudeOfSouthernPole);
    addProperty("Grib1.GridSection.Rotation.AngleOfRotationInDegrees",GridSection::Rotation::AngleOfRotationInDegrees);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",nullptr);
  }
}





Property::~Property()
{
  try
  {
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Operation failed!",nullptr);
    exception.printError();
  }
}




void Property::addProperty(const char *name,uint id)
{
  try
  {
    propertyMap.insert(std::pair<std::string,uint>(name,id));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",nullptr);
  }
}





uint Property::getPropertyId(const char *name)
{
  try
  {
    auto it = propertyMap.find(name);
    if (it != propertyMap.end())
      return it->second;

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string Property::getPropertyName(uint id)
{
  try
  {
    for (auto it = propertyMap.begin(); it != propertyMap.end(); ++it)
    {
      if (it->second == id)
        return it->first;
    }

    return "";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}

#include "MercatorImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"
#include "../../common/GeneralDefinitions.h"
#include "../../grid/PrintOptions.h"
#include "../Properties.h"

#include <iostream>

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

MercatorImpl::MercatorImpl()
{
  try
  {
    mGridProjection = T::GridProjectionValue::Mercator;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

MercatorImpl::MercatorImpl(const MercatorImpl& other)
:Mercator(other)
{
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

MercatorImpl::~MercatorImpl()
{
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* MercatorImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new MercatorImpl(*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method reads and initializes all data related to the current object.
    The purpose of this method is to get access to the read operation that takes place
    in the parent class (which is automatically generated). This means in practice that
    we first call the read operation in the parent class. After that we can ensure that
    the result of the read operation was correct (i.e. attribute values are valid, etc).
    We can also modify or update some attribute values if needed.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void MercatorImpl::read(MemoryReader& memoryReader)
{
  try
  {
    Mercator::read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns the grid geometry string. This string can be used for comparing
    geometries in different grid files. For example, is is possible that a GRIB 1 message has
    the same geometry string as a GRIB 2 message, which means that they have same geometries.
    This comparison is more reliable than the hash comparison.

        \return   The grid geometry string.
*/

std::string MercatorImpl::getGridGeometryString() const
{
  try
  {
    char buf[1000];

    double x = getLongitude(C_DOUBLE(*mLongitudeOfFirstGridPoint) / 1000000);
    double y = C_DOUBLE(*mLatitudeOfFirstGridPoint) / 1000000;

    double dx = C_DOUBLE(*mDi) / 1000;
    double dy = C_DOUBLE(*mDj) / 1000;
    double latin = C_DOUBLE(*mLaD) / 1000000;

    unsigned char scanningMode = mScanningMode.getScanningMode();

    char sm[100];
    char *p = sm;
    if ((scanningMode & 0x80) != 0)
    {
      dx = -dx;
      p += sprintf(p,"-x");
    }
    else
    {
      p += sprintf(p,"+x");
    }

    if ((scanningMode & 0x40) == 0)
    {
      dy = -dy;
      p += sprintf(p,"-y");
    }
    else
    {
      p += sprintf(p,"+y");
    }

    sprintf(buf,"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;description",
        T::GridProjectionValue::Mercator,*mNi,*mNj,x,y,fabs(dx),fabs(dy),sm,latin);

    return std::string(buf);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

         \return   The grid coordinates.
*/

T::Coordinate_svec MercatorImpl::getGridOriginalCoordinatesNoCache() const
{
  try
  {
    T::Coordinate_svec coordinateList(new T::Coordinate_vec());

    if (!mNi || !mNj)
      return coordinateList;

    uint ni = (*mNi);
    uint nj = (*mNj);

    double latitudeOfFirstGridPoint = C_DOUBLE(*mLatitudeOfFirstGridPoint) / 1000000;
    double longitudeOfFirstGridPoint = C_DOUBLE(*mLongitudeOfFirstGridPoint) / 1000000;

    double di = C_DOUBLE(*mDi) / 1000;
    double dj = C_DOUBLE(*mDj) / 1000;

    unsigned char scanningMode = mScanningMode.getScanningMode();
    if ((scanningMode & 0x80) != 0)
      di = -di;

    if ((scanningMode & 0x40) == 0)
      dj = -dj;

    convert(latlonSpatialReference,mSpatialReference,1,&longitudeOfFirstGridPoint,&latitudeOfFirstGridPoint);

    coordinateList->reserve(ni*nj);

    double y = latitudeOfFirstGridPoint;
    for (uint j=0; j < nj; j++)
    {
      double x = longitudeOfFirstGridPoint;

      for (uint i=0; i < ni; i++)
      {
        coordinateList->emplace_back(x,y);
        x += di;
      }
      y += dj;
    }

    return coordinateList;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions MercatorImpl::getGridDimensions() const
{
  try
  {
    if (!mNi || !mNj)
      return T::Dimensions();

    return T::Dimensions(*mNi, *mNj);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




bool MercatorImpl::getGridMetricCellSize(double& width,double& height) const
{
  try
  {
    width = C_DOUBLE(*mDi) / 1000000;
    height = C_DOUBLE(*mDj) / 1000000;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief This method calculates the estimated grid position by using the original coordinates.
    The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.

      \param x       The original x-coordinate.
      \param y       The original y-coordinate.
      \param grid_i  The returned grid i-position.
      \param grid_j  The returned grid j-position.
      \return        Returns 'false' if the given coordinates are outside of the grid.
*/

bool MercatorImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    if (!mNi || !mNj)
      return false;

    uint ni = (*mNi);
    uint nj = (*mNj);

    double latitudeOfFirstGridPoint = C_DOUBLE(*mLatitudeOfFirstGridPoint) / 1000000;
    double longitudeOfFirstGridPoint = C_DOUBLE(*mLongitudeOfFirstGridPoint) / 1000000;

    double di = C_DOUBLE(*mDi) / 1000;
    double dj = C_DOUBLE(*mDj) / 1000;

    unsigned char scanningMode = mScanningMode.getScanningMode();
    if ((scanningMode & 0x80) != 0)
      di = -di;

    if ((scanningMode & 0x40) == 0)
      dj = -dj;

    double fX = longitudeOfFirstGridPoint;
    double fY = latitudeOfFirstGridPoint;

    convert(latlonSpatialReference,mSpatialReference,1,&fX,&fY);

    double xDiff = x - fX;
    double yDiff = y - fY;

    double i = xDiff / di;
    double j = yDiff / dj;

    grid_i = i;
    grid_j = j;

    if (i < 0 ||  j < 0  ||  i >= C_DOUBLE(ni) ||  j > C_DOUBLE(nj))
      return false;

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MercatorImpl::getProperties(T::PropertySettingVec& properties)
{
  try
  {
    Mercator::getProperties(properties);

    if (getNi())
      properties.emplace_back((uint)Property::GridSection::Mercator::Ni,*getNi());

    if (getNj())
      properties.emplace_back((uint)Property::GridSection::Mercator::Nj,*getNj());

    if (getLatitudeOfFirstGridPoint())
      properties.emplace_back((uint)Property::GridSection::Mercator::LatitudeOfFirstGridPoint,*getLatitudeOfFirstGridPoint());


    if (getLongitudeOfFirstGridPoint())
      properties.emplace_back((uint)Property::GridSection::Mercator::LongitudeOfFirstGridPoint,*getLongitudeOfFirstGridPoint());

    if (getLaD())
      properties.emplace_back((uint)Property::GridSection::Mercator::LaD,*getLaD());

    if (getLatitudeOfLastGridPoint())
      properties.emplace_back((uint)Property::GridSection::Mercator::LatitudeOfLastGridPoint,*getLatitudeOfLastGridPoint());

    if (getLongitudeOfLastGridPoint())
      properties.emplace_back((uint)Property::GridSection::Mercator::LongitudeOfLastGridPoint,*getLongitudeOfLastGridPoint());

    if (getOrientationOfTheGrid())
      properties.emplace_back((uint)Property::GridSection::Mercator::OrientationOfTheGrid,*getOrientationOfTheGrid());

    if (getDi())
      properties.emplace_back((uint)Property::GridSection::Mercator::Di,*getDi());

    if (getDj())
      properties.emplace_back((uint)Property::GridSection::Mercator::Dj,*getDj());

    properties.emplace_back((uint)Property::GridSection::Mercator::ResolutionAndComponentFlags,mResolution.getResolutionAndComponentFlags());
    properties.emplace_back((uint)Property::GridSection::Mercator::ScanningMode,mScanningMode.getScanningMode());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method is used for setting a (long long) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool MercatorImpl::setProperty(uint propertyId,long long value)
{
  try
  {
    switch (propertyId)
    {
      case Property::GridSection::Mercator::Ni:
        setNi(value);
        return true;

      case Property::GridSection::Mercator::Nj:
        setNj(value);
        return true;

      case Property::GridSection::Mercator::LatitudeOfFirstGridPoint:
        setLatitudeOfFirstGridPoint(value);
        return true;

      case Property::GridSection::Mercator::LongitudeOfFirstGridPoint:
        setLongitudeOfFirstGridPoint(value);
        return true;

      case Property::GridSection::Mercator::LaD:
        setLaD(value);
        return true;

      case Property::GridSection::Mercator::LatitudeOfLastGridPoint:
        setLatitudeOfLastGridPoint(value);
        return true;

      case Property::GridSection::Mercator::LongitudeOfLastGridPoint:
        setLongitudeOfLastGridPoint(value);
        return true;

      case Property::GridSection::Mercator::OrientationOfTheGrid:
        setOrientationOfTheGrid(value);
        return true;

      case Property::GridSection::Mercator::Di:
        setDi(value);
        return true;

      case Property::GridSection::Mercator::Dj:
        setDj(value);
        return true;

      case Property::GridSection::Mercator::ResolutionAndComponentFlags:
        mResolution.setResolutionAndComponentFlags(value);
        return true;

      case Property::GridSection::Mercator::ScanningMode:
        mScanningMode.setScanningMode(value);
        return true;
    }

    return GridDefinition::setProperty(propertyId,value);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void MercatorImpl::initSpatialReference()
{
  try
  {
    //print(std::cout,0,0);
    // ### Check that we have all necessary values needed by this method.

    mSpatialReference = getSpatialReference();
    if (!mSpatialReference)
    {
      mSpatialReference.reset(new T::SpatialRef());
      addSpatialReference(mSpatialReference);

      auto dfCenterLat = mLatitudeOfFirstGridPoint;
      if (!dfCenterLat)
        throw Fmi::Exception(BCP,"The 'latitudetudeOfFirstGridPoint' value is missing!");


      auto dfCenterLong = mLongitudeOfFirstGridPoint;
      if (!dfCenterLong)
        throw Fmi::Exception(BCP,"The 'longitudeOfFirstGridPoint' value is missing!");

      // ### Set geographic coordinate system.

      const char *pszGeogName = "UNKNOWN";
      const char *pszDatumName = "UNKNOWN";
      const char *pszSpheroidName = "UNKNOWN";
      double dfSemiMajor = getMajorAxis(mEarthShape);
      double dfFlattening = getFlattening(mEarthShape);
      double dfInvFlattening = 0;
      if (dfFlattening != 0)
        dfInvFlattening = 1/dfFlattening;

      mSpatialReference->SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);


      // ### Set the projection and the linear units for the projection.

      double centerLat = C_DOUBLE(*dfCenterLat) / 1000000;
      double centerLon = C_DOUBLE(*dfCenterLong) / 1000000;
      double latin = C_DOUBLE(*mLaD) / 1000000;
      double dfFalseEasting = 0.0;
      double dfFalseNorthing = 0.0;

      //mSpatialReference->SetMercator(centerLat,centerLon,1.0,dfFalseEasting,dfFalseNorthing);
      mSpatialReference->SetMercator2SP(latin,centerLat,centerLon,dfFalseEasting,dfFalseNorthing);
      mSpatialReference->SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);
      mSpatialReference->SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);


      //mSpatialReference->importFromEPSG(3395);

      // ### Validate the spatial reference.
  /*
      auto errorCode = mSpatialReference->Validate();
      if (errorCode != OGRERR_NONE)
      {
        Fmi::Exception exception(BCP,"The spatial reference is not valid!");
        exception.addParameter("ErrorCode",std::to_string(errorCode));
        throw exception;
      }
  */
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void MercatorImpl::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    Mercator::print(stream,level,optionFlags);

    stream << space(level+1) << "MercatorImpl\n";

    if (optionFlags & GRID::PrintFlag::coordinates)
    {
      stream << space(level+1) << "- Coordinates (of the grid corners):\n";
      T::Coordinate_svec coordinateList = getGridOriginalCoordinates();

      // ### Printing coordinates close to the grid corners.

      if (!mNi || !mNj)
        return;

      int nx = C_INT(*mNi);
      int ny = C_INT(*mNj);

      char str[200];
      uint c = 0;
      for (int y=0; y < ny; y++)
      {
        for (int x=0; x < nx; x++)
        {
          if ((y < 3  ||  y >= ny-3)  &&  (x < 3  ||  x >= nx-3))
          {
            T::Coordinate coord = coordinateList->at(c);

            double lon = coord.x();
            double lat = coord.y();
            if (convert(mSpatialReference,latlonSpatialReference,1,&lon,&lat))
            {
              sprintf(str,"* [%03d,%03d] %f,%f => %f,%f",x,y,coord.x(),coord.y(),lon,lat);
              stream << space(level+2) << str << "\n";
            }
          }
          c++;
        }
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}

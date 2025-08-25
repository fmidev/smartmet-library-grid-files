#include "TransverseMercatorImpl.h"
#include <macgyver/Exception.h>

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

TransverseMercatorImpl::TransverseMercatorImpl()
{
  mGridProjection = T::GridProjectionValue::TransverseMercator;
}





/*! \brief The copy constructor of the class. */

TransverseMercatorImpl::TransverseMercatorImpl(const TransverseMercatorImpl& other)
:TransverseMercator(other)
{
}





/*! \brief The destructor of the class. */

TransverseMercatorImpl::~TransverseMercatorImpl()
{
}





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* TransverseMercatorImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new TransverseMercatorImpl(*this);
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

void TransverseMercatorImpl::read(MemoryReader& memoryReader)
{
  try
  {
    TransverseMercator::read(memoryReader);
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


T::Coordinate_svec TransverseMercatorImpl::getGridOriginalCoordinatesNoCache() const
{
  try
  {
    T::Coordinate_svec coordinateList(new T::Coordinate_vec());

    uint ni = *mNi;
    uint nj = *mNj;

    double di = C_DOUBLE(*mDi) / 100.0;
    double dj = C_DOUBLE(*mDj) / 100.0;

    unsigned char scanningMode = mScanningMode.getScanningMode();
    if ((scanningMode & 0x80) != 0)
      di = -di;

    if ((scanningMode & 0x40) == 0)
      dj = -dj;

    coordinateList->reserve(ni*nj);

    double y = (*mY1) / 100.0;
    for (uint j=0; j < nj; j++)
    {
      double x = (*mX1) / 100.0;

      for (uint i=0; i < ni; i++)
      {
        T::Coordinate coord(x,y);
        coordinateList->emplace_back(coord);
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

T::Dimensions TransverseMercatorImpl::getGridDimensions() const
{
  try
  {
    if (!mNi || !mNj)
      return T::Dimensions();

    return T::Dimensions(*mNi, *mNj);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}




bool TransverseMercatorImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    if (!mNi || !mNj)
      return false;

    uint ni = (*mNi);
    uint nj = (*mNj);

    double di = C_DOUBLE(*mDi) / 100.0;
    double dj = C_DOUBLE(*mDj) / 100.0;

    unsigned char scanningMode = mScanningMode.getScanningMode();
    if ((scanningMode & 0x80) != 0)
      di = -di;

    if ((scanningMode & 0x40) == 0)
      dj = -dj;

    double fX = (*mX1) / 100.0;
    double fY = (*mY1) / 100.0;

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




/*! \brief This method calculates the estimated grid position by using the latlon coordinates.
    The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.

        \param lat     The latitude.
        \param lon     The longitude.
        \param grid_i  The returned grid i-position.
        \param grid_j  The returned grid j-position.
        \return        Returns 'false' if the given coordinates are outside of the grid.
*/

bool TransverseMercatorImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    // TODO: We should probably do our own implementation instead of using the parent implementation,
    // which might be slow or does not even work if the spatial reference is not correctly initialized.

    return GridDefinition::getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



/*! \brief The method returns 'true' if the grid horizontal values are in the reverse order.

        \return   The method returns 'true' if the grid horizontal values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool TransverseMercatorImpl::reverseXDirection() const
{
  try
  {
    unsigned char scanMode = mScanningMode.getScanningMode();

    if ((scanMode & 0x80) != 0)
      return true;

    return false;
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

std::string TransverseMercatorImpl::getGridGeometryString() const
{
  try
  {
    char buf[1000];

    double rx = getLongitude(C_DOUBLE(*mLongitudeOfReferencePoint) / 1000000);
    double ry = C_DOUBLE(*mLatitudeOfReferencePoint) / 1000000;

    double dx = C_DOUBLE(*mDi) / 100;
    double dy = C_DOUBLE(*mDj) / 100;

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

    sprintf(buf,"%d;id;name;%d;%d;firstLon;firstLat;%.6f;%.6f;%s;%.6f;%.6f;description",
        T::GridProjectionValue::TransverseMercator,*mNi,*mNj,fabs(dx),fabs(dy),sm,rx,ry);

    return std::string(buf);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool TransverseMercatorImpl::reverseYDirection() const
{
  try
  {
    unsigned char scanMode = mScanningMode.getScanningMode();

    if ((scanMode & 0x40) == 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void TransverseMercatorImpl::initSpatialReference()
{
  try
  {
    mSpatialReference = getSpatialReference();
    if (!mSpatialReference)
    {
      mSpatialReference.reset(new T::SpatialRef());

      // ### Check that we have all necessary values needed by this method.

      auto dfCenterLat = mLatitudeOfReferencePoint;
      if (!dfCenterLat)
        throw Fmi::Exception(BCP, "The 'latitudeOfReferencePoint' value is missing!");

      auto dfCenterLong = mLongitudeOfReferencePoint;
      if (!dfCenterLong)
        throw Fmi::Exception(BCP, "The 'longitudeOfReferencePoint' value is missing!");

      // auto dfScale = mScaleFactorAtReferencePoint;


      auto dfFalseEasting = mXR;
      if (!dfFalseEasting)
        throw Fmi::Exception(BCP, "The 'xR' value is missing!");

      auto dfFalseNorthing = mYR;
      if (!dfFalseNorthing)
        throw Fmi::Exception(BCP, "The 'yR' value is missing!");


      // ### Set geographic coordinate system.

      const char *pszGeogName = "UNKNOWN";
      const char *pszDatumName = "UNKNOWN";
      const char *pszSpheroidName = "UNKNOWN";
      double dfSemiMajor = getMajorAxis(mEarthShape);
      double dfFlattening = getFlattening(mEarthShape);
      double dfInvFlattening = 0;
      if (dfFlattening != 0)
        dfInvFlattening = 1/dfFlattening;

      mSpatialReference->SetGeogCS(pszGeogName, pszDatumName, pszSpheroidName, dfSemiMajor,
                                  dfInvFlattening);

      // ### Set the projection and the linear units for the projection.

      double centerLat = C_DOUBLE(*dfCenterLat) / 1000000;
      double centerLon = C_DOUBLE(*dfCenterLong) / 1000000;
      double falseEasting = C_DOUBLE(*dfFalseEasting) / 100;
      double falseNorthing = C_DOUBLE(*dfFalseNorthing) / 100;
      //double scale = C_DOUBLE(dfScale);
      double scale = 0.9996;

      mSpatialReference->SetTM(centerLat, centerLon, scale, falseEasting,
                              falseNorthing);
      mSpatialReference->SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);
      mSpatialReference->SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

      // ### Validate the spatial reference.

      auto errorCode = mSpatialReference->Validate();
      if (errorCode != OGRERR_NONE)
      {
        Fmi::Exception exception(BCP, "The spatial reference is not valid!");
        exception.addParameter("ErrorCode", std::to_string(errorCode));
        throw exception;
      }
      addSpatialReference(mSpatialReference);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}


}
}

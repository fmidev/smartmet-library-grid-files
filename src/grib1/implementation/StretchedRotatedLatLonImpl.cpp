#include "StretchedRotatedLatLonImpl.h"
#include <macgyver/Exception.h>
#include "../../common/CoordinateConversions.h"

namespace SmartMet
{
namespace GRIB1
{

/*! \brief The constructor of the class. */

StretchedRotatedLatLonImpl::StretchedRotatedLatLonImpl()
{
  mGridProjection = T::GridProjectionValue::StretchedRotatedLatLon;
}





/*! \brief The copy constructor of the class. */

StretchedRotatedLatLonImpl::StretchedRotatedLatLonImpl(const StretchedRotatedLatLonImpl& other)
:StretchedRotatedLatLon(other)
{
}





/*! \brief The destructor of the class. */

StretchedRotatedLatLonImpl::~StretchedRotatedLatLonImpl()
{
}





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* StretchedRotatedLatLonImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new StretchedRotatedLatLonImpl(*this);
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

void StretchedRotatedLatLonImpl::read(MemoryReader& memoryReader)
{
  try
  {
    StretchedRotatedLatLon::read(memoryReader);

    if (mNi == 0xFFFF)
      mNi = 0; // ni missing

    if (mNj == 0xFFFF)
      mNj = 0; // nj missing
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

T::Coordinate_svec StretchedRotatedLatLonImpl::getGridOriginalCoordinatesNoCache() const
{
  try
  {
    T::Coordinate_svec coordinateList(new T::Coordinate_vec());

    uint ni = mNi;
    uint nj = mNj;

    double latitudeOfFirstGridPoint = C_DOUBLE(mGridArea.getLatitudeOfFirstGridPoint());
    double longitudeOfFirstGridPoint = C_DOUBLE(mGridArea.getLongitudeOfFirstGridPoint());
    double iDirectionIncrement = C_DOUBLE(mIDirectionIncrement);
    double jDirectionIncrement = C_DOUBLE(mJDirectionIncrement);

    unsigned char scanMode = mScanningMode.getScanningMode();

    if ((scanMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    if ((scanMode & 0x40) == 0)
      jDirectionIncrement = -jDirectionIncrement;

    coordinateList->reserve(ni*nj);

    double y = latitudeOfFirstGridPoint;
    for (uint j=0; j < nj; j++)
    {
      double x = longitudeOfFirstGridPoint;
      //if (longitudeOfFirstGridPoint >= 180000)
      //  x = longitudeOfFirstGridPoint - 360000;

      for (uint i=0; i < ni; i++)
      {
        double cx = getLongitude(x/1000);
        double cy = y/1000;
        T::Coordinate coord(cx,cy);
        coordinateList->emplace_back(coord);
        x += iDirectionIncrement;
      }
      y += jDirectionIncrement;
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

T::Dimensions StretchedRotatedLatLonImpl::getGridDimensions() const
{
  try
  {
    return T::Dimensions(mNi, mNj);
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

bool StretchedRotatedLatLonImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    uint ni = mNi;
    uint nj = mNj;

    double latitudeOfFirstGridPoint = C_DOUBLE(mGridArea.getLatitudeOfFirstGridPoint()) / 1000 + 90;
    double longitudeOfFirstGridPoint = C_DOUBLE(mGridArea.getLongitudeOfFirstGridPoint()) / 1000;
    double iDirectionIncrement = C_DOUBLE(mIDirectionIncrement) / 1000;
    double jDirectionIncrement = C_DOUBLE(mJDirectionIncrement) / 1000;

    unsigned char scanMode = mScanningMode.getScanningMode();

    if ((scanMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    if ((scanMode & 0x40) == 0)
      jDirectionIncrement = -jDirectionIncrement;

    if (longitudeOfFirstGridPoint > 180)
      longitudeOfFirstGridPoint -= 360;

    longitudeOfFirstGridPoint += 360;

    double aLat = lat + 90;
    double aLon = lon;

    if (aLon > 180)
      aLon -= 360;

    aLon += 360;

    double latDiff = aLat - latitudeOfFirstGridPoint;
    double lonDiff = aLon - longitudeOfFirstGridPoint;

    double i = lonDiff / iDirectionIncrement;
    double j = latDiff / jDirectionIncrement;

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





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void StretchedRotatedLatLonImpl::initSpatialReference()
{
  try
  {
    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor =  6367470;
    double dfInvFlattening = 0.0;

    ResolutionFlagsSettings *rflags = mGridArea.getResolutionFlags();
    if (rflags != nullptr)
    {
      dfSemiMajor = getMajorAxis(rflags->getResolutionAndComponentFlags());
      double dfFlattening = getFlattening(rflags->getResolutionAndComponentFlags());
      if (dfFlattening != 0)
        dfInvFlattening = 1/dfFlattening;
    }

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);

    mSpatialReference.SetProjParm("latitude_of_origin",(C_DOUBLE(mRotation.getLatitudeOfSouthernPole())/1000));
    mSpatialReference.SetProjParm("central_meridian",(C_DOUBLE(mRotation.getLongitudeOfSouthernPole())/1000));
    mSpatialReference.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

    // ### Validate the spatial reference.

    auto errorCode = mSpatialReference.Validate();
    if (errorCode != OGRERR_NONE)
    {
      Fmi::Exception exception(BCP,"The spatial reference is not valid!");
      exception.addParameter("ErrorCode",std::to_string(errorCode));
      throw exception;
    }

    // ### Test if the grid is global

    uint ni = mNi;
    double iDirectionIncrement = C_DOUBLE(mIDirectionIncrement) / 1000;
    double len = (ni+1)* iDirectionIncrement;

    if (len >= 360)
      mGlobal = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet

#include "LambertConformalImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/CoordinateConversions.h"
#include "../../grid/PrintOptions.h"
#include "../Properties.h"

#include <iostream>


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

LambertConformalImpl::LambertConformalImpl()
{
  try
  {
    mGridProjection = T::GridProjectionValue::LambertConformal;
    mDxx = 0;
    mDyy = 0;
    mStartX = 0;
    mStartY = 0;
    mInitialized = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

LambertConformalImpl::LambertConformalImpl(const LambertConformalImpl& other):LambertConformal(other)
{
  try
  {
    mDxx = other.mDxx;
    mDyy = other.mDyy;
    mStartX = other.mStartX;
    mStartY = other.mStartY;
    mInitialized = other.mInitialized;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

LambertConformalImpl::~LambertConformalImpl()
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





void LambertConformalImpl::init() const
{
  try
  {
    if (!mNx || !mNy)
      return;

    if (mInitialized)
      return;

    double latitudeOfFirstGridPoint = C_DOUBLE(*mLatitudeOfFirstGridPoint) / 1000000;
    double longitudeOfFirstGridPoint = getLongitude(C_DOUBLE(*mLongitudeOfFirstGridPoint) / 1000000);

    double dxx = C_DOUBLE(*mDx) / 1000;
    double dyy = C_DOUBLE(*mDy) / 1000;

    mDxx = dxx;
    mDyy = dyy;

    unsigned char scanningMode = mScanningMode.getScanningMode();
    if ((scanningMode & 0x80) != 0)
      mDxx = -dxx;

    if ((scanningMode & 0x40) == 0)
      mDyy = -dyy;

    double startX = longitudeOfFirstGridPoint;
    double startY = latitudeOfFirstGridPoint;

    auto hash = getGridHash();
    if (hash == 0 || !getTransformFromCache(hash,latitudeOfFirstGridPoint,longitudeOfFirstGridPoint,startX,startY))
    {
      convert(&mLatlonSpatialReference,&mSpatialReference,1,&startX,&startY);
      if (hash != 0)
        insertTranformIntoCache(mHash,latitudeOfFirstGridPoint,longitudeOfFirstGridPoint,startX,startY);
    }

    mStartX = startX;
    mStartY = startY;

    mInitialized = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns a duplicate of the current object. */

GridDefinition* LambertConformalImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new LambertConformalImpl(*this);
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

void LambertConformalImpl::read(MemoryReader& memoryReader)
{
  try
  {
    LambertConformal::read(memoryReader);
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

bool LambertConformalImpl::setProperty(uint propertyId,long long value)
{
  try
  {
    switch (propertyId)
    {
      case Property::GridSection::LambertConformal::Nx:
        setNx(value);
        return true;

      case Property::GridSection::LambertConformal::Ny:
        setNy(value);
        return true;

      case Property::GridSection::LambertConformal::LatitudeOfFirstGridPoint:
        setLatitudeOfFirstGridPoint(value);
        return true;

      case Property::GridSection::LambertConformal::LongitudeOfFirstGridPoint:
        setLongitudeOfFirstGridPoint(value);
        return true;

      case Property::GridSection::LambertConformal::ResolutionAndComponentFlags:
      {
        ResolutionSettings *resolution = getResolution();
        if (resolution != nullptr)
        {
          resolution->setResolutionAndComponentFlags(value);
          return true;
        }
        return false;
      }

      case Property::GridSection::LambertConformal::LaD:
        setLaD(value);
        return true;

      case Property::GridSection::LambertConformal::LoV:
        setLoV(value);
        return true;

      case Property::GridSection::LambertConformal::Dx:
        setDx(value);
        return true;

      case Property::GridSection::LambertConformal::Dy:
        setDy(value);
        return true;

      case Property::GridSection::LambertConformal::ProjectionCentreFlag:
        setProjectionCentreFlag(value);
        return true;

      case Property::GridSection::LambertConformal::Latin1:
        setLatin1(value);
        return true;

      case Property::GridSection::LambertConformal::Latin2:
        setLatin2(value);
        return true;

      case Property::GridSection::LambertConformal::LatitudeOfSouthernPole:
        setLatitudeOfSouthernPole(value);
        return true;

      case Property::GridSection::LambertConformal::LongitudeOfSouthernPole:
        setLongitudeOfSouthernPole(value);
        return true;


      case Property::GridSection::LambertConformal::ScanningMode:
      {
        ScanningModeSettings *scanningMode = getScanningMode() ;
        if (scanningMode != nullptr)
        {
          scanningMode->setScanningMode(value);
          return true;
        }
        return false;
      }
    }
    return GridDefinition::setProperty(propertyId,value);
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

T::Coordinate_svec LambertConformalImpl::getGridOriginalCoordinates() const
{
  try
  {
    T::Coordinate_svec coordinateList(new T::Coordinate_vec());

    if (!mNx || !mNy)
      return coordinateList;

    uint nx = (*mNx);
    uint ny = (*mNy);

    coordinateList->reserve(nx*ny);

    double y = mStartY;
    for (uint j=0; j < ny; j++)
    {
      double x = mStartX;

      for (uint i=0; i < nx; i++)
      {
        T::Coordinate coord(x,y);
        coordinateList->emplace_back(coord);
        x += mDxx;
      }
      y += mDyy;
    }

    return coordinateList;
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

std::string LambertConformalImpl::getGridGeometryString() const
{
  try
  {
    char buf[1000];

    double y = C_DOUBLE(*mLatitudeOfFirstGridPoint) / 1000000;
    double x = getLongitude(C_DOUBLE(*mLongitudeOfFirstGridPoint) / 1000000);
    double dx = C_DOUBLE(*mDx) / 1000;
    double dy = C_DOUBLE(*mDy) / 1000;
    double loV = C_DOUBLE(*mLoV) / 1000000;
    double latin1 = C_DOUBLE(*mLatin1) / 1000000;
    double latin2 = C_DOUBLE(*mLatin2) / 1000000;
    //double laD = C_DOUBLE(*mLaD)/1000000;
    double laD = latin1;
    double sx = getLongitude(C_DOUBLE(*mLongitudeOfSouthernPole) / 1000000);
    double sy = C_DOUBLE(*mLatitudeOfSouthernPole) / 1000000;

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


    sprintf(buf,"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;%.6f;%.6f;%.6f;%.6f;description",
      T::GridProjectionValue::LambertConformal,*mNx,*mNy,x,y,fabs(dx),fabs(dy),sm,loV,latin1,latin2,sx,sy,laD);

    return std::string(buf);
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

T::Dimensions LambertConformalImpl::getGridDimensions() const
{
  try
  {
    if (!mNx || !mNy)
      return T::Dimensions();

    return T::Dimensions(*mNx, *mNy);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::size_t LambertConformalImpl::getGridColumnCount() const
{
  try
  {
    return *mNx;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




std::size_t LambertConformalImpl::getGridRowCount() const
{
  try
  {
    return *mNy;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool LambertConformalImpl::getGridMetricCellSize(double& width,double& height) const
{
  try
  {
    width = C_DOUBLE(*mDx) / 1000000;
    height = C_DOUBLE(*mDy) / 1000000;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool LambertConformalImpl::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  try
  {
    if (!mNx || !mNy)
      return false;

    if (grid_i < 0  ||  grid_j < 0  ||  grid_i >= (*mNx)  ||  grid_j >= (*mNy))
      return false;

    y = mStartY + grid_j * mDyy;
    x = mStartX + grid_i * mDxx;

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

bool LambertConformalImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    if (!mNx || !mNy)
      return false;

    double xDiff = (round(x*100) - round(mStartX*100)) / 100;
    double yDiff = (round(y*100) - round(mStartY*100)) / 100;

    double i = xDiff / mDxx;
    double j = yDiff / mDyy;

    grid_i = i;
    grid_j = j;

    if (i < 0 ||  j < 0  ||  i >= C_DOUBLE(*mNx) ||  j > C_DOUBLE(*mNy))
      return false;

    return true;
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

bool LambertConformalImpl::reverseXDirection() const
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





/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool LambertConformalImpl::reverseYDirection() const
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

void LambertConformalImpl::initSpatialReference()
{
  try
  {
    // ### Check that we have all necessary values needed by this method.

    auto dfStdP1 = mLatin1;
    if (!dfStdP1)
      throw Fmi::Exception(BCP,"The 'latin1' value is missing!");

    auto dfStdP2 = mLatin2;
    if (!dfStdP2)
      throw Fmi::Exception(BCP,"The 'latin2' value is missing!");

    auto dfCenterLat = mLaD;
    if (!dfCenterLat)
      throw Fmi::Exception(BCP,"The 'laD' value is missing!");

    auto dfCenterLong = mLoV;
    if (!dfCenterLong)
      throw Fmi::Exception(BCP,"The 'loV' value is missing!");

    auto southPoleLon = mLongitudeOfSouthernPole;
    auto southPoleLat = mLatitudeOfSouthernPole;

    if (!southPoleLon)
      southPoleLon = 0;

    if (!southPoleLat)
      southPoleLat = -90 * 1000000;

    //if ((*southPoleLon != 0) || (*southPoleLat != (-90 * 1000000)))
    //  throw Fmi::Exception(BCP,"A projection with a rotated pole is not supported!");


    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor = getMajorAxis(mEarthShape);
    double dfFlattening = getFlattening(mEarthShape);
    double dfInvFlattening = 0;
    if (dfFlattening != 0)
      dfInvFlattening = 1/dfFlattening;

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);


    // ### Set the projection and the linear units for the projection.

    double stdP1 = C_DOUBLE(*dfStdP1)/ 1000000;
    double stdP2 = C_DOUBLE(*dfStdP2)/ 1000000;
    double centerLat = C_DOUBLE(*dfCenterLat) / 1000000;
    double centerLon = C_DOUBLE(*dfCenterLong) / 1000000;
    double dfFalseEasting = 0.0;
    double dfFalseNorthing = 0.0;

    mSpatialReference.SetLCC(stdP1,stdP2,centerLat,centerLon,dfFalseEasting,dfFalseNorthing);
    mSpatialReference.SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);
    mSpatialReference.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);


    // ### Validate the spatial reference.

    auto errorCode = mSpatialReference.Validate();
    if (errorCode != OGRERR_NONE)
    {
      Fmi::Exception exception(BCP,"The spatial reference is not valid!");
      exception.addParameter("ErrorCode",std::to_string(errorCode));
      throw exception;
    }

    init();
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

void LambertConformalImpl::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    LambertConformal::print(stream,level,optionFlags);

    stream << space(level+1) << "LambertConformalImpl\n";

    if (optionFlags & GRID::PrintFlag::coordinates)
    {
      stream << space(level+1) << "- Coordinates (of the grid corners):\n";
      T::Coordinate_svec coordinateList = getGridOriginalCoordinates();

      // ### Printing coordinates close to the grid corners.

      int nx = C_INT(*mNx);
      int ny = C_INT(*mNy);

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
            if (convert(&mLatlonSpatialReference,&mSpatialReference,1,&lon,&lat))
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

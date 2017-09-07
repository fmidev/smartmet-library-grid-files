#include "GridSection.h"
#include "Message.h"
#include "grid/Dimensions.h"
#include "identification/GribDef.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"

#include "grib1/implementation/LatLonImpl.h"
#include "grib1/implementation/MercatorImpl.h"
#include "grib1/implementation/LambertConformalImpl.h"
#include "grib1/implementation/GaussianImpl.h"
#include "grib1/implementation/PolarStereographicImpl.h"
#include "grib1/implementation/AlbersImpl.h"
#include "grib1/implementation/RotatedLatLonImpl.h"
#include "grib1/implementation/ObliqueLambertConformalImpl.h"
#include "grib1/implementation/RotatedGaussianImpl.h"
#include "grib1/implementation/StretchedLatLonImpl.h"
#include "grib1/implementation/StretchedGaussianImpl.h"
#include "grib1/implementation/StretchedRotatedLatLonImpl.h"
#include "grib1/implementation/StretchedRotatedGaussianImpl.h"
#include "grib1/implementation/SphericalHarmonicImpl.h"
#include "grib1/implementation/RotatedSphericalHarmonicImpl.h"
#include "grib1/implementation/StretchedSphericalHarmonicImpl.h"
#include "grib1/implementation/StretchedRotatedSphericalHarmonicImpl.h"
#include "grib1/implementation/SpaceViewImpl.h"


namespace SmartMet
{
namespace GRIB1
{



/*! \brief The constructor of the class.

        \param message  A pointer to the message object.
*/

GridSection::GridSection(Message *message)
{
  try
  {
    mMessage = message;
    mFilePosition = 0;
    mNumberOfPoints = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The destructor of the class. */

GridSection::~GridSection()
{
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current section.
*/

void GridSection::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  try
  {
    char name[300];

    sprintf(name,"%sgrid.numberOfVerticalCoordinateValues",prefix.c_str());
    attributeList.addAttribute(name,toString(mNumberOfVerticalCoordinateValues));

    sprintf(name,"%sgrid.pvlLocation",prefix.c_str());
    attributeList.addAttribute(name,toString(mPvlLocation));

    sprintf(name,"%sgrid.dataRepresentationType",prefix.c_str());
    attributeList.addAttribute(name,toString(mDataRepresentationType));

    sprintf(name,"%sgrid.dataRepresentationString",prefix.c_str());
    attributeList.addAttribute(name,getGridProjectionString());

    sprintf(name,"%sgrid.numberOfValues",prefix.c_str());
    attributeList.addAttribute(name,toString(getGridOriginalValueCount()));

    sprintf(name,"%sgrid.def.",prefix.c_str());
    if (mGridDefinition)
      mGridDefinition->getAttributeList(name,attributeList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GridSection::read(MemoryReader& memoryReader)
{
  try
  {
    mFilePosition = memoryReader.getGlobalReadPosition();

    auto rPos = memoryReader.getReadPosition();

    mSectionLength = memoryReader.read_uint24();
    memoryReader >> mNumberOfVerticalCoordinateValues;
    memoryReader >> mPvlLocation;
    memoryReader >> mDataRepresentationType;

    auto gridDefinition = createGridDefinition(mDataRepresentationType);
    mGridDefinition.reset(gridDefinition);
    gridDefinition->read(memoryReader);

    memoryReader.setReadPosition(rPos + mSectionLength);

    if (mNumberOfVerticalCoordinateValues == 0  &&  mPvlLocation != 255)
    {
      memoryReader.setReadPosition(rPos + mPvlLocation - 1);
      std::vector<std::uint32_t> rowPositions;
      rowPositions.push_back(0);

      auto d = getGridDimensions();
      uint rows = 0;
      if (d)
        rows = d->ny();

      for (uint y=0; y<rows; y++)
      {
        std::uint16_t len = 0;
        memoryReader >> len;
        //printf("ROW %u  %u\n",rows,len);
        mNumberOfPoints += len;
        rowPositions.push_back(mNumberOfPoints);
      }

      mGridDefinition->initRowPositions(rowPositions);
    }

    try
    {
      if (mGridDefinition != NULL)
        mGridDefinition->initSpatialReference();
    }
    catch (...)
    {
      SmartMet::Spine::Exception exception(BCP,"Operation failed!",NULL);
      exception.printError();
    }

    // Initializing the hash.

    getGridHash();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the section start position in the grib file.

        \return  The section's start position in the grib file.
*/

T::FilePosition GridSection::getFilePosition() const
{
  try
  {
    return mFilePosition;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the length of the section (in the grib file).

        \return  The length of the section expressed in bytes.
*/

std::uint32_t GridSection::getSectionLength() const
{
  try
  {
    return mSectionLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the name of the section. */

std::string GridSection::getSectionName() const
{
  try
  {
    return std::string("Grid");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the section number. */

std::uint8_t GridSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::grid_section;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string GridSection::getGridProjectionString() const
{
  try
  {
    return Identification::gribDef.getTableValue(1,0,"6",mDataRepresentationType);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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

bool GridSection::getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridPointByLatLon(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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

bool GridSection::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridPointByOriginalCoordinates(x,y,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns. In this case we can find out the grid
    dimensions by using the "getGridOriginalRowCount()" and "getGridOriginalColumnCount()"
    methods.

        \return   The grid dimensions.
*/

T::Dimensions_opt GridSection::getGridDimensions() const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridDimensions();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the number of rows used in the original grid.

        \return   The number of the grid rows.
*/

std::size_t GridSection::getGridOriginalRowCount() const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridOriginalRowCount();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the number of columns used in the given original grid row.

        \param row    The grid row index (= j-position).
        \return       The number of columns in the given grid row.
*/

std::size_t GridSection::getGridOriginalColumnCount(std::size_t row) const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridOriginalColumnCount(row);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the maximum number of the columns used in the original grid.
    If the grid is irregular, this method returns the length of the longest row.

        \return   The maximum number of the columns in the grid.
*/

std::size_t GridSection::getGridOriginalColumnCount() const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridOriginalColumnCount();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the number of original values defined in the original grid.

        \return   The number of the values in the original grid.
*/

std::size_t GridSection::getGridOriginalValueCount() const
{
  try
  {
    if (mNumberOfPoints > 0)
      return mNumberOfPoints;

    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridOriginalValueCount();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the index of given grid position in the original grid data.
    In the case of irregular grid the grid rows might contain different number of
    columns. If the given grid position is outside of the grid data then the method
    returns -1. This is the case when the grid column (grid_i) is bigger than
    the length of the given grid row (grid_j), or if the given grid row (grid_j)
    is bigger than the actual number of grid rows.

        \param grid_i    The grid i-position.
        \param grid_j    The grid j-position.
        \return          The index of the original data position. If the position
                         is outside of the grid data then the method return -1.
*/

int GridSection::getGridOriginalValueIndex(uint grid_i,uint grid_j) const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridOriginalValueIndex(grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the first and the last latlon coordinates used in the grid.

        \param firstLat   The returned latitude of the top-left corner.
        \param firstLon   The returned longitude of the top-left corner.
        \param lastLat    The returned latitude of the bottom-right corner.
        \param lastLon    The returned longitude of the bottom-right corner.
*/

void GridSection::getGridLatlonAreaCoordinates(double& firstLat,double& firstLon,double& lastLat,double& lastLon) const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridLatlonAreaCoordinates(firstLat,firstLon,lastLat,lastLon);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the first and the last original coordinates used in the grid.

        \param x1    The returned x-coordinate of the top-left corner.
        \param y1    The returned y-coordinate of the top-left corner.
        \param x2    The returned x-coordinate of the bottom-right corner.
        \param y2    The returned y-coordinate of the bottom-right corner.
*/

void GridSection::getGridOriginalAreaCoordinates(double& x1,double& y1,double& x2,double& y2) const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridOriginalAreaCoordinates(x1,y1,x2,y2);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





uint GridSection::getGridGeometryId() const
{
  try
  {
    if (mGridDefinition != NULL)
      return mGridDefinition->getGridGeometryId();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





void GridSection::setGridGeometryId(uint geometryId)
{
  try
  {
    if (mGridDefinition)
      return mGridDefinition->setGridGeometryId(geometryId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

        \return   The grid coordinates.
*/

T::Coordinate_vec GridSection::getGridCoordinates() const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridCoordinates();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::Hash GridSection::getGridHash() const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridHash();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief This method can be used for finding out if the grid is global (i.e. goes
    around the globe).
    If the grid is global then we should be able to interpolate over the grid borders.

        \return   The method returns 'true' if the grid data is global. Otherwise
                  it returns 'false'.
*/

bool GridSection::isGridGlobal() const
{
  try
  {
    if (!mGridDefinition)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->isGridGlobal();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief This method can be used for finding out the grid type.

        \return   The type of the grid (expressed as an enum value).
*/

T::GridProjection GridSection::getGridProjection() const
{
  try
  {
    if (mGridDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridProjection();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief This method can be used for finding out the grid layout.

        \return   The layout of the grid (expressed as an enum value).
*/

T::GridLayout GridSection::getGridLayout() const
{
  try
  {
    if (mGridDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridLayout();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::SpatialReference* GridSection::getSpatialReference() const
{
  try
  {
    if (mGridDefinition != NULL)
      return mGridDefinition->getSpatialReference();

    return NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}



/*! \brief This method creates a GridDefinition object according to the given
    data representation type.

        \param dataRepresentationType   The type of the GridDefinition object.
        \return                         The pointer to the new GridDefinition object.
*/

GridDefinition* GridSection::createGridDefinition(std::uint8_t  dataRepresentationType)
{
  try
  {
    switch (dataRepresentationType)
    {
      case 0: // Latitude/longitude grid - equidistant cylindrical or Plate Carrée projection
        return new LatLonImpl();

      case 1: // Mercator projection
        return new MercatorImpl();

      case 2: // Gnomonic projection
        throw SmartMet::Spine::Exception(BCP,"'Gnomonic projection' not implemented!");

      case 3: // Lambert conformal, secant or tangent, conic or bi-polar, projection
        return new LambertConformalImpl();

      case 4: // Gaussian latitude/longitude grid
        return new GaussianImpl();

      case 5: // Polar stereographic projection
        return new PolarStereographicImpl();

      case 6: // Fmi Transverse Mercator (UTM) projection
        throw SmartMet::Spine::Exception(BCP,"'Fmi Transverse Mercator' not implemented!");

      case 7: // Simple polyconic projection
        throw SmartMet::Spine::Exception(BCP,"'Simple polyconic' not implemented!");

      case 8: // Albers equal-area, secant or tangent, conic or bi-polar, projection
        return new AlbersImpl();

      case 9: // Miller's cylindrical projection
        throw SmartMet::Spine::Exception(BCP,"'Miller's cylindrical' Not implemented!");

      case 10: // Rotated latitude/longitude grid
        return new RotatedLatLonImpl();

      case 13: // Oblique Lambert conformal, secant or tangent, conic or bi-polar, projection
        return new ObliqueLambertConformalImpl();

      case 14: // Rotated Gaussian latitude/longitude grid
        return new RotatedGaussianImpl();

      case 20: // Stretched latitude/longitude grid
        return new StretchedLatLonImpl();

      case 24: // Stretched Gaussian latitude/longitude grid
        return new StretchedGaussianImpl();

      case 30: // Stretched and rotated latitude/longitude grids
        return new StretchedRotatedLatLonImpl();

      case 34: // Stretched and rotated Gaussian latitude/longitude grids
        return new StretchedRotatedGaussianImpl();

      case 50: // Spherical harmonic coefficients
        return new SphericalHarmonicImpl();

      case 60: // Rotated spherical harmonic coefficients
        return new RotatedSphericalHarmonicImpl();

      case 70: // Stretched spherical harmonics
        return new StretchedSphericalHarmonicImpl();

      case 80: // Stretched and rotated spherical harmonic coefficients
        return new StretchedRotatedSphericalHarmonicImpl();

      case 90: // Space view, perspective orthographic
        return new SpaceViewImpl();

      default:
        throw SmartMet::Spine::Exception(BCP,"Unsupported grid definition!");
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GridSection::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition                     = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- sectionLength                    = " << toString(mSectionLength) << "\n";
    stream << space(level) << "- numberOfVerticalCoordinateValues = " << toString(mNumberOfVerticalCoordinateValues) << "\n";
    stream << space(level) << "- pvlLocation                      = " << toString(mPvlLocation) << "\n";
    stream << space(level) << "- dataRepresentationType           = " << toString(mDataRepresentationType) << "\n";
    stream << space(level) << "- dataRepresentationString         = " << getGridProjectionString() << "\n";
    stream << space(level) << "- numberOfValues                   = " << toString(getGridOriginalValueCount()) << "\n";

    if (mGridDefinition)
      mGridDefinition->print(stream,level+1,optionFlags);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet

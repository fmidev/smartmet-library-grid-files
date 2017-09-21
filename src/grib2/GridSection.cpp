#include "grib2/GridSection.h"
#include "grid/Dimensions.h"
#include "identification/GribDef.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "Message.h"

#include "grib2/implementation/LatLonImpl.h"                             //  "3.0"
#include "grib2/implementation/RotatedLatLonImpl.h"                      //  "3.1"
#include "grib2/implementation/StretchedLatLonImpl.h"                    //  "3.2"
#include "grib2/implementation/StretchedRotatedLatLonImpl.h"             //  "3.3"
#include "grib2/implementation/VariableResolutionLatLonImpl.h"           //  "3.4"
#include "grib2/implementation/VariableResolutionRotatedLatLonImpl.h"    //  "3.5"
#include "grib2/implementation/MercatorImpl.h"                           //  "3.10"
#include "grib2/implementation/TransverseMercatorImpl.h"                 //  "3.12"
#include "grib2/implementation/PolarStereographicImpl.h"                 //  "3.20"
#include "grib2/implementation/LambertConformalImpl.h"                   //  "3.30"
#include "grib2/implementation/AlbersImpl.h"                             //  "3.31"
#include "grib2/implementation/GaussianImpl.h"                           //  "3.40"
#include "grib2/implementation/RotatedGaussianImpl.h"                    //  "3.41"
#include "grib2/implementation/StretchedGaussianImpl.h"                  //  "3.42"
#include "grib2/implementation/StretchedRotatedGaussianImpl.h"           //  "3.43"
#include "grib2/implementation/SphericalHarmonicImpl.h"                  //  "3.50"
#include "grib2/implementation/RotatedSphericalHarmonicImpl.h"           //  "3.51"
#include "grib2/implementation/StretchedSphericalHarmonicImpl.h"         //  "3.52"
#include "grib2/implementation/StretchedRotatedSphericalHarmonicImpl.h"  //  "3.53"
#include "grib2/implementation/SpaceViewImpl.h"                          //  "3.90"
#include "grib2/implementation/TriangularImpl.h"                         //  "3.100"
#include "grib2/implementation/UnstructuredImpl.h"                       //  "3.101"
#include "grib2/implementation/EquatorialAzimuthalEquidistantImpl.h"     //  "3.110"
#include "grib2/implementation/AzimuthRangeImpl.h"                       //  "3.120"
#include "grib2/implementation/IrregularLatLonImpl.h"                    //  "3.130"
#include "grib2/implementation/LambertAzimuthalEqualAreaImpl.h"          //  "3.140"
#include "grib2/implementation/CrossSectionImpl.h"                       //  "3.1000"
#include "grib2/implementation/HovmollerImpl.h"                          //  "3.1100"
#include "grib2/implementation/TimeSectionImpl.h"                        //  "3.1200"

#include <iostream>

namespace SmartMet
{
namespace GRIB2
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
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed failed!",NULL);
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
    std::uint8_t tablesVersion = mMessage->getTablesVersion();

    sprintf(name,"%sgrid.sourceOfGridDefinition",prefix.c_str());
    attributeList.addAttribute(name,toString(getSourceOfGridDefinition()));

    sprintf(name,"%sgrid.sourceStringOfGridDefinition",prefix.c_str());
    attributeList.addAttribute(name,Identification::gribDef.getTableValue(2,tablesVersion,"3.0",getSourceOfGridDefinition()));

    sprintf(name,"%sgrid.numberOfGridPoints",prefix.c_str());
    attributeList.addAttribute(name,toString(getNumberOfGridPoints()));

    sprintf(name,"%sgrid.numberOfOctetsForNumberOfPoints",prefix.c_str());
    attributeList.addAttribute(name,toString(getNumberOfOctetsForNumberOfPoints()));

    sprintf(name,"%sgrid.interpretationOfNumberOfPoints",prefix.c_str());
    attributeList.addAttribute(name,toString(getInterpretationOfNumberOfPoints()));

    sprintf(name,"%sgrid.interpretationStringOfNumberOfPoints",prefix.c_str());
    attributeList.addAttribute(name,Identification::gribDef.getTableValue(2,tablesVersion,"3.11",getInterpretationOfNumberOfPoints()));

    sprintf(name,"%sgrid.gridDefinitionTemplateNumber",prefix.c_str());
    attributeList.addAttribute(name,toString(getGridDefinitionTemplateNumber()));

    sprintf(name,"%sgrid.gridDefinitionString",prefix.c_str());
    attributeList.addAttribute(name,getGridProjectionString());

    sprintf(name,"%sgrid.def.",prefix.c_str());
    if (mGridDefinition)
      mGridDefinition->getAttributeList(name,attributeList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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

    memoryReader >> mSectionLength;
    if (missing(mSectionLength))
    {
      SmartMet::Spine::Exception exception(BCP,"Section length cannot be MISSING!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-4));
      throw exception;
    }

    memoryReader >> mNumberOfSection;
    memoryReader >> mSourceOfGridDefinition;

    memoryReader >> mNumberOfGridPoints;
    if (missing(mNumberOfGridPoints))
    {
      SmartMet::Spine::Exception exception(BCP,"Section number of grid points cannot be MISSING");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-4));
      throw exception;
    }

    memoryReader >> mNumberOfOctetsForNumberOfPoints;
    if (missing(mNumberOfOctetsForNumberOfPoints))
    {
      SmartMet::Spine::Exception exception(BCP,"Section number of octets for number of points cannot be MISSING");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mInterpretationOfNumberOfPoints;

    if (missing(mInterpretationOfNumberOfPoints))
    {
      // A missing value makes no sense, the value should be zero if there are no points
      SmartMet::Spine::Exception exception(BCP,"Section 3 interpretation of number of points cannot be missing");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    auto rPos = memoryReader.getGlobalReadPosition();

    memoryReader >> mGridDefinitionTemplateNumber;

    try
    {
      auto gridDefinition = createGridDefinition(mGridDefinitionTemplateNumber);
      mGridDefinition.reset(gridDefinition);
      gridDefinition->read(memoryReader);
    }
    catch (...)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot create a grid definition!",NULL);
      exception.addParameter("Read position",uint64_toHex(rPos));
      throw exception;
    }

    if (*mNumberOfOctetsForNumberOfPoints != 0)
    {
      SmartMet::Spine::Exception exception(BCP,"GridSection does not support reading optional numbers yet!");
      throw exception;
      //      exception.printError();;

      // TODO: Read the datapoints
    }

    if (mGridDefinition != NULL)
      mGridDefinition->initSpatialReference();

    getGridHash();

    //if (memoryReader.getDataSize() < (mFilePosition + *mSectionLength))
    //  memoryReader.setReadPosition(mFilePosition + *mSectionLength);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the length of the section (in the grib file).

         \return  The length of the section expressed in bytes.
*/

std::uint32_t GridSection::getSectionLength() const
{
  try
  {
    return *mSectionLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the default section number. */

std::uint8_t GridSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::grid_section;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the section number that was read from the grib file. */

std::uint8_t GridSection::getNumberOfSection() const
{
  try
  {
    return *mNumberOfSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the source of the grid definition (see Code Table 3.0). */

T::UInt8_opt GridSection::getSourceOfGridDefinition() const
{
  try
  {
    return mSourceOfGridDefinition;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the number of the grid points.

      \return   The number of the grid points.
*/

std::uint32_t GridSection::getNumberOfGridPoints() const
{
  try
  {
    return *mNumberOfGridPoints;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the number of octets for an optional list of numbers defining number of points.

      \return   The number of octets for an optional list of numbers defining number of points.
*/

std::uint8_t GridSection::getNumberOfOctetsForNumberOfPoints() const
{
  try
  {
    return *mNumberOfOctetsForNumberOfPoints;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the interpretation of list of numbers defining number
    of points (see Code Table 3.11).

      \return   The interpretation of list of numbers defining number of points.
*/

std::uint8_t GridSection::getInterpretationOfNumberOfPoints() const
{
  try
  {
    return *mInterpretationOfNumberOfPoints;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the grid definition template number (see Code Table 3.1).

       \return   The grid definition template number.
*/

T::UInt16_opt GridSection::getGridDefinitionTemplateNumber() const
{
  try
  {
    return mGridDefinitionTemplateNumber;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    const auto source = getSourceOfGridDefinition();
    const auto noctets = getNumberOfOctetsForNumberOfPoints();
    const auto interpretation = getInterpretationOfNumberOfPoints();

    // We can handle only normal grids for which source==0

    if (!mGridDefinition)
      return {};

    if (missing(source) || *source != 0)
      return {};

    // Cannot handle irregular grids. Note that if interpretation=3, there is a separate list
    // of latitudes and hence it might be possible that the grid is regular, not just using
    // any of the standard projections. TODO: Handle it if an example is found.
    if (noctets != 0 || interpretation)
      return {};

    // Unknown grid?
    if (!mGridDefinition)
      return {};

    return mGridDefinition->getGridDimensions();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    if (mGridDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridLatlonAreaCoordinates(firstLat,firstLon,lastLat,lastLon);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GridSection::getGridGeometryId() const
{
  try
  {
    if (mGridDefinition)
      return mGridDefinition->getGridGeometryId();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    if (mGridDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridCoordinates();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::Coordinate_vec GridSection::getGridLatLonCoordinates() const
{
  try
  {
    if (mGridDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridLatLonCoordinates();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the hash value that was calculated over the grid
    attributes.

       \return   The hash value of the grid attributes.
*/

T::Hash GridSection::getGridHash() const
{
  try
  {
    if (mGridDefinition != NULL)
      return mGridDefinition->getGridHash();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    if (mGridDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridPointByLatLon(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    if (mGridDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->getGridPointByOriginalCoordinates(x,y,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the grid definition string, which is a textual description
    of the grid definition template.

      \return        The grid definition string.
*/

std::string GridSection::getGridProjectionString() const
{
  try
  {
    std::uint8_t tablesVersion = mMessage->getTablesVersion();
    return Identification::gribDef.getTableValue(2,tablesVersion,"3.1",getGridDefinitionTemplateNumber());
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the type of the grid layout.

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the type of the grid.

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the number of rows used in the original grid.

     \return   The number of the grid rows.
*/

std::size_t GridSection::getGridOriginalRowCount() const
{
  try
  {
    auto d = getGridDimensions();
    if (d)
      return d->ny();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    auto d = getGridDimensions();
    if (d)
      return d->nx();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    auto d = getGridDimensions();
    if (d)
      return d->nx();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the number of original values defined in the original grid.

      \return   The number of the values in the original grid.
*/

std::size_t GridSection::getGridOriginalValueCount() const
{
  try
  {
    auto d = getGridDimensions();
    if (d)
      return d->ny() * d->nx();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    auto d = getGridDimensions();
    if (d)
    {
      if (grid_j >= d->ny())
        return -1;

      if (grid_i >= d->nx() &&  !isGridGlobal())
        return -1;

      return (grid_j * d->nx() + (grid_i % d->nx()));
    }
    return -1;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns 'true' if the grid is global (i.e. goes around the globe).
    If the grid is global then we should be able to interpolate over the grid borders.

      \return   The method returns 'true' if the grid data is global. Otherwise
                it returns 'false'
*/

bool GridSection::isGridGlobal() const
{
  try
  {
    if (mGridDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridDefinition' attribute points to NULL!");

    return mGridDefinition->isGridGlobal();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method create a GridDefinition object accorind to the given
    grid defintion template number.

      \return   The pointer to the created GridDefinition object.
*/

GridDefinition* GridSection::createGridDefinition(T::UInt16_opt(number))
{
  try
  {
    // Unknown grid?
    if (missing(number))
      return nullptr;

    switch (*number)
    {
      case 0:
        return new LatLonImpl();
      case 1:
        return new RotatedLatLonImpl();
      case 2:
        return new StretchedLatLonImpl();
      case 3:
        return new StretchedRotatedLatLonImpl();
      case 4:
        return new VariableResolutionLatLonImpl();
      case 5:
        return new VariableResolutionRotatedLatLonImpl();
      case 10:
        return new MercatorImpl();
      case 12:
        return new TransverseMercatorImpl();
      case 20:
        return new PolarStereographicImpl();
      case 30:
        return new LambertConformalImpl();
      case 31:
        return new AlbersImpl();
      case 40:
        return new GaussianImpl();
      case 41:
        return new RotatedGaussianImpl();
      case 42:
        return new StretchedGaussianImpl();
      case 43:
        return new StretchedRotatedGaussianImpl();
      case 50:
        return new SphericalHarmonicImpl();
      case 51:
        return new RotatedSphericalHarmonicImpl();
      case 52:
        return new StretchedSphericalHarmonicImpl();
      case 53:
        return new StretchedRotatedSphericalHarmonicImpl();
      case 90:
        return new SpaceViewImpl();
      case 100:
        return new TriangularImpl();
      case 101:
        return new UnstructuredImpl();
      case 110:
        return new EquatorialAzimuthalEquidistantImpl();
      case 120:
        return new AzimuthRangeImpl();
      case 130:
        return new IrregularLatLonImpl();
      case 140:
        return new LambertAzimuthalEqualAreaImpl();
      case 1000:
        return new CrossSectionImpl();
      case 1100:
        return new HovmollerImpl();
      case 1200:
        return new TimeSectionImpl();
      default:
        throw SmartMet::Spine::Exception(BCP,"Unknown grid definition template number '" +
                                 std::to_string(static_cast<int>(*number)) + "'!");
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Creation of a grid definition failed!",NULL);
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
    std::uint8_t tablesVersion = mMessage->getTablesVersion();

    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition                    = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- sectionLength                   = " << toString(mSectionLength) << "\n";
    stream << space(level) << "- numberOfSection                 = " << toString(mNumberOfSection) << "\n";
    stream << space(level) << "- sourceOfGridDefinition          = " << Identification::gribDef.getTableValue(2,tablesVersion,"3.0",getSourceOfGridDefinition()) << "\n";
    stream << space(level) << "- numberOfGridPoints              = " << toString(getNumberOfGridPoints()) << "\n";
    stream << space(level) << "- numberOfOctetsForNumberOfPoints = " << toString(getNumberOfOctetsForNumberOfPoints()) << "\n";
    stream << space(level) << "- interpretationOfNumberOfPoints  = " << Identification::gribDef.getTableValue(2,tablesVersion,"3.11",getInterpretationOfNumberOfPoints()) << "\n";
    stream << space(level) << "- gridDefinitionTemplateNumber    = " << toString(getGridDefinitionTemplateNumber()) << "\n";
    stream << space(level) << "- gridDefinitionString            = " << getGridProjectionString() << "\n";

    // Dump the projection details: code table 3.1
    auto gridnumber = getGridDefinitionTemplateNumber();

    if (missing(gridnumber))
    {
      auto source = getSourceOfGridDefinition();
      if (missing(source))
        stream << space(level) << "!!! A grid definition does not apply to this product !!!\n";
      else if (*source == 1)
        stream << space(level) << "!!! Grid is predetermined by the originating center !!!\n";
      else
        stream << space(level) << "!!! Unknown Grid Definition Template Number !!!\n";
    }

    if (mGridDefinition)
      mGridDefinition->print(stream,level+1,optionFlags);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}  // namespace GRIB2
}  // namespace SmartMet

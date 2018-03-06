#include "Message.h"
#include "GribFile.h"
#include "BitmapSection.h"
#include "DataSection.h"
#include "common/Dimensions.h"
#include "grid/PrintOptions.h"
#include "GridSection.h"
#include "IndicatorSection.h"
#include "ProductSection.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include "identification/GridDef.h"
#include "grid/ValueCache.h"
#include "grid/IndexCache.h"
#include "common/ShowFunction.h"
#include <iostream>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF

namespace SmartMet
{
namespace GRIB1
{


#define POINT_CACHE_SIZE 400


/*! \brief The constructor of the class. */

Message::Message()
{
  FUNCTION_TRACE
  try
  {
    mGribFile = NULL;
    mFilePosition = 0;
    mGrib1ParameterLevelId = 0;
    mGrib2ParameterLevelId = 0;
    mFmiParameterLevelId = 0;
    mCacheKey = 0;
    mOrigCacheKey = 0;
    mValueDecodingFailed = false;
    mPointCachePosition = 0;
    mPointCacheCoordinate = new uint[POINT_CACHE_SIZE];
    mPointCacheValue = new T::ParamValue[POINT_CACHE_SIZE];

    for (uint t=0; t<POINT_CACHE_SIZE; t++)
    {
      mPointCacheCoordinate[t] = 0xFFFFFFFF;
      mPointCacheValue[t] = 0;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The constructor of the class. */

Message::Message(GribFile *gribFile)
{
  FUNCTION_TRACE
  try
  {
    mGribFile = gribFile;
    mFilePosition = 0;
    mGrib1ParameterLevelId = 0;
    mGrib2ParameterLevelId = 0;
    mFmiParameterLevelId = 0;
    mCacheKey = 0;
    mOrigCacheKey = 0;
    mValueDecodingFailed = false;
    mPointCachePosition = 0;
    mPointCacheCoordinate = new uint[POINT_CACHE_SIZE];
    mPointCacheValue = new T::ParamValue[POINT_CACHE_SIZE];

    for (uint t=0; t<POINT_CACHE_SIZE; t++)
    {
      mPointCacheCoordinate[t] = 0xFFFFFFFF;
      mPointCacheValue[t] = 0;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The destructor of the class. */

Message::~Message()
{
  FUNCTION_TRACE
  try
  {
    delete mPointCacheCoordinate;
    delete mPointCacheValue;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current message.
*/

void Message::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  FUNCTION_TRACE
  try
  {
    char name[300];

    //const GRID::ParameterDefinition *paramDef = SmartMet::GRID::gridDef.getParameterDefById(getGribParameterId());

    sprintf(name,"%smessage[%u].fmiProducerName",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(mFmiProducerName));

    sprintf(name,"%smessage[%u].gribParameterId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(getGribParameterId()));

    sprintf(name,"%smessage[%u].grib1ParameterLevelId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(getGrib1ParameterLevelId()));

    sprintf(name,"%smessage[%u].grib2ParameterLevelId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(getGrib2ParameterLevelId()));

    sprintf(name,"%smessage[%u].gribParameterName",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mGribParameterName);

    sprintf(name,"%smessage[%u].gribParameterDescription",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mGribParameterDescription);

    sprintf(name,"%smessage[%u].gribParameterUnits",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mGribParameterUnits);

    sprintf(name,"%smessage[%u].fmiParameterId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(mFmiParameterId));

    sprintf(name,"%smessage[%u].fmiParameterLevelId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(mFmiParameterLevelId));

    sprintf(name,"%smessage[%u].fmiParameterName",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mFmiParameterName);

    sprintf(name,"%smessage[%u].fmiParameterDescription",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mFmiParameterDescription);

    sprintf(name,"%smessage[%u].fmiParameterUnits",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mFmiParameterUnits);

    sprintf(name,"%smessage[%u].newbaseParameterId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(mNewbaseParameterId));

    sprintf(name,"%smessage[%u].newbaseParameterName",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(mNewbaseParameterName));

    sprintf(name,"%smessage[%u].cdmParameterId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mCdmParameterId);

    sprintf(name,"%smessage[%u].cdmParameterName",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mCdmParameterName);

    sprintf(name,"%smessage[%u].parameterLevel",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(getGridParameterLevel()));

    sprintf(name,"%smessage[%u].parameterLevelId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(getGridParameterLevelId()));

    sprintf(name,"%smessage[%u].parameterLevelIdString",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,getGridParameterLevelIdString());

    sprintf(name,"%smessage[%u].foracastTime",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,getForecastTime());

    //sprintf(name,"%smessage[%u].referenceTime",prefix.c_str(),(uint)mMessageIndex);
    //attributeList.addAttribute(name,getReferenceTime());

    sprintf(name,"%smessage[%u].gridGeometryId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(getGridGeometryId()));

    sprintf(name,"%smessage[%u].gridType",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString((uint)getGridProjection()));

    sprintf(name,"%smessage[%u].gridTypeString",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,getGridProjectionString());

    sprintf(name,"%smessage[%u].gridLayout",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString((uint)getGridLayout()));

    sprintf(name,"%smessage[%u].gridLayoutString",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,get_gridLayoutString(getGridLayout()));

    sprintf(name,"%smessage[%u].gridRows",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString((uint)getGridOriginalRowCount()));

    sprintf(name,"%smessage[%u].gridColumns",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString((uint)getGridOriginalColumnCount()));


    sprintf(name,"%smessage[%u].",prefix.c_str(),(uint)mMessageIndex);

    if (mIndicatorSection)
      mIndicatorSection->getAttributeList(name,attributeList);

    if (mGridSection)
      mGridSection->getAttributeList(name,attributeList);

    if (mProductSection)
      mProductSection->getAttributeList(name,attributeList);

    if (mBitmapSection)
      mBitmapSection->getAttributeList(name,attributeList);

    if (mDataSection)
      mDataSection->getAttributeList(name,attributeList);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method reads and initializes all data related to the current message object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void Message::read(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
    mFilePosition = memoryReader.getGlobalReadPosition();

    auto rPos = memoryReader.getGlobalReadPosition();
    try
    {
      IndicatorSection *section = new IndicatorSection(this);
      mIndicatorSection.reset(section);
      section->read(memoryReader);
    }
    catch (...)
    {
      SmartMet::Spine::Exception exception(BCP,"Indicator section creation failed!",NULL);
      exception.addParameter("Section start position",uint64_toHex(rPos));
      throw exception;
    }

    rPos = memoryReader.getGlobalReadPosition();
    try
    {
      ProductSection *section = new ProductSection(this);
      mProductSection.reset(section);
      section->read(memoryReader);
    }
    catch (...)
    {
      SmartMet::Spine::Exception exception(BCP,"Product section creation failed!",NULL);
      exception.addParameter("Section start position",uint64_toHex(rPos));
      throw exception;
    }

    if (mProductSection->getSectionFlags() & 0x80)
    {
      rPos = memoryReader.getGlobalReadPosition();
      try
      {
        GridSection *section = new GridSection(this);
        mGridSection.reset(section);
        section->read(memoryReader);
      }
      catch (...)
      {
        SmartMet::Spine::Exception exception(BCP,"Grid section creation failed!",NULL);
        exception.addParameter("Section start position",uint64_toHex(rPos));
        throw exception;
      }
    }

    if (mProductSection->getSectionFlags() & 0x40)
    {
      rPos = memoryReader.getGlobalReadPosition();
      try
      {
        BitmapSection *section = new BitmapSection(this);
        mBitmapSection.reset(section);
        section->read(memoryReader);
      }
      catch (...)
      {
        SmartMet::Spine::Exception exception(BCP,"Bitmap section creation failed!",NULL);
        exception.addParameter("Section start position",uint64_toHex(rPos));
        throw exception;
      }
    }

    rPos = memoryReader.getGlobalReadPosition();
    try
    {
      DataSection *section = new DataSection(this);
      mDataSection.reset(section);
      section->read(memoryReader);
    }
    catch (...)
    {
      SmartMet::Spine::Exception exception(BCP,"Data section creation failed!",NULL);
      exception.addParameter("Section start position",uint64_toHex(rPos));
      throw exception;
    }

    mGribParameterId = Identification::gridDef.getGribParameterId(*this);
    mGribParameterName = Identification::gridDef.getGribParameterName(*this);
    mGribParameterDescription = Identification::gridDef.getGribParameterDescription(*this);
    mGribParameterUnits = Identification::gridDef.getGribParameterUnits(*this);
    mGrib1ParameterLevelId = Identification::gridDef.getGrib1LevelId(*this);

    mGrib2ParameterLevelId = Identification::gridDef.getGrib2LevelId(*this);

    //mFmiProducerName = Identification::gridDef.mMessageIdentifier_fmi.getProducerName(*this);

    mFmiParameterId = Identification::gridDef.getFmiParameterId(*this);
    mFmiParameterName = Identification::gridDef.getFmiParameterName(*this);
    mFmiParameterDescription = Identification::gridDef.getFmiParameterDescription(*this);
    mFmiParameterUnits = Identification::gridDef.getFmiParameterUnits(*this);
    mFmiParameterLevelId = Identification::gridDef.getFmiLevelId(*this);

    mNewbaseParameterId = Identification::gridDef.getNewbaseParameterId(*this);
    mNewbaseParameterName = Identification::gridDef.getNewbaseParameterName(*this);

    mCdmParameterId = Identification::gridDef.getCdmParameterId(*this);
    mCdmParameterName = Identification::gridDef.getCdmParameterName(*this);

    mDefaultInterpolationMethod = Identification::gridDef.getFmiParameterInterpolationMethod(*this);

    if (getGridGeometryId() == 0)
    {
      T::Hash hash = getGridHash();
      if (hash != 0)
      {
        int geometryId = Identification::gridDef.getGrib1GeometryIdByHash(hash);
        if (geometryId != 0)
          setGridGeometryId(geometryId);
        else
          printf("** Geometry not found %llu (file = %s)\n",(unsigned long long)hash,mGribFile->getFileName().c_str());
      }
      else
      {
        printf("** Hash is zero!\n");
      }
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    exception.addParameter("Message start position",uint64_toHex(memoryReader.getStartPtr()-memoryReader.getParentPtr()));
    throw exception;
  }
}





GribFile* Message::getGribFile() const
{
  FUNCTION_TRACE
  try
  {
    return mGribFile;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the reference time of the current message. The forecast
    times are calculated from this.

        \return   The reference time of the current message.
*/

T::TimeString Message::getReferenceTime() const
{
  FUNCTION_TRACE
  try
  {
    return mProductSection->getReferenceTime();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the forecast start time. This is calculated from the reference
    time and other time parameters (=> NormalProduct->parameter()).

        \return   The forecast start time of the current message.
*/

T::TimeString Message::getForecastTime() const
{
  FUNCTION_TRACE
  try
  {
    return mProductSection->getForecastTime();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





T::Hash Message::getGridHash() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != NULL)
      return mGridSection->getGridHash();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





T::GeometryId Message::getGridGeometryId() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != NULL)
      return mGridSection->getGridGeometryId();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}






void Message::setGridGeometryId(T::GeometryId geometryId)
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != NULL)
      return mGridSection->setGridGeometryId(geometryId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the type of the grid.

        \return   The type of the grid (expressed as an enum value).
*/

T::GridProjection Message::getGridProjection() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridProjection();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the type of the grid layout.

        \return   The layout of the grid (expressed as an enum value).
*/

T::GridLayout Message::getGridLayout() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridLayout();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
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

T::Dimensions_opt Message::getGridDimensions() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridDimensions();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridLatLonCoordinatesByGridPoint(grid_i,grid_j,lat,lon);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}






bool Message::getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridLatLonCoordinatesByGridPosition(grid_i,grid_j,lat,lon);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridLatLonCoordinatesByOriginalCoordinates(x,y,lat,lon);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridOriginalCoordinatesByGridPoint(grid_i,grid_j,x,y);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridOriginalCoordinatesByGridPosition(grid_i,grid_j,x,y);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

        \return   The grid coordinates.
*/

T::Coordinate_vec Message::getGridCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridCoordinates();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





T::Coordinate_vec Message::getGridLatLonCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridLatLonCoordinates();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridOriginalCoordinatesByLatLonCoordinates(lat,lon,x,y);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





void Message::getGridProjectionAttributes(std::string prefix,T::AttributeList& attributeList) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    mGridSection->getAttributeList(prefix,attributeList);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





uint Message::getFileId() const
{
  {
    try
    {
      if (mGribFile != NULL)
        return mGribFile->getFileId();

      return 0;
    }
    catch (...)
    {
      throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
    }
  }
}





/*! \brief The method can be used in order to find out the message's start
    position in the grib file.

        \return  The messages's start position in the grib file.
*/

T::FilePosition Message::getFilePosition() const
{
  FUNCTION_TRACE
  try
  {
    return mFilePosition;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns a shared pointer to the BitmapSection object. */

BitmapSection_sptr Message::getBitmapSection() const
{
  FUNCTION_TRACE
  try
  {
    return mBitmapSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns a shared pointer to the GridSection object. */

GridSection_sptr Message::getGridSection() const
{
  FUNCTION_TRACE
  try
  {
    return mGridSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns a shared pointer to the IndicatorSection object. */

IndicatorSection_sptr Message::getIndicatorSection() const
{
  FUNCTION_TRACE
  try
  {
    return mIndicatorSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns a pointer to the ProductSection object. */

const ProductSection* Message::getProductSection() const
{
  FUNCTION_TRACE
  try
  {
    return mProductSection.get();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns a pointer to the DataSection object. */

const DataSection* Message::getDataSection() const
{
  FUNCTION_TRACE
  try
  {
    return mDataSection.get();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the grid definition string (=> Projection name).

        \return   The projection used in the current grid (LatLon, Mercator, etc.)
*/

std::string Message::getGridProjectionString() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridProjectionString();
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

bool Message::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief This method calculates the estimated grid position of the the given original
    coordinates. The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.

        \param x       The original x-coordinate.
        \param y       The original y-coordinate.
        \param grid_i  The returned grid i-position.
        \param grid_j  The returned grid j-position.
        \return        The method returns 'false' if the given coordinates are
                       outside of the grid.
*/

bool Message::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridPointByOriginalCoordinates(x,y,grid_i,grid_j);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the number of rows used in the original grid.

        \return   The number of the grid rows.
*/

std::size_t Message::getGridOriginalRowCount() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridOriginalRowCount();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the number of columns used in the given original grid row.

        \param row    The grid row index (= j-position).
        \return       The number of columns in the given grid row.
*/

std::size_t Message::getGridOriginalColumnCount(std::size_t row) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridOriginalColumnCount(row);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the maximum number of the columns used in the original grid.
    If the grid is irregular, this method returns the length of the longest row.

        \return   The maximum number of the columns in the grid.
*/

std::size_t Message::getGridOriginalColumnCount() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridOriginalColumnCount();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the number of original values defined in the original grid.

        \return   The number of the values in the original grid.
*/

std::size_t Message::getGridOriginalValueCount() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    //printf("COUNT %llu\n",(unsigned long long)mGridSection->getGridOriginalValueCount());
    return mGridSection->getGridOriginalValueCount();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
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

int Message::getGridOriginalValueIndex(uint grid_i,uint grid_j) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->getGridOriginalValueIndex(grid_i,grid_j);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the minimum and maximum value used in the current grid.
    This functionality might help to visualize the grid data.

        \param minValue   The returned minimum parameter value in the grid.
        \param maxValue   The returned maximum parameter value in the grid.
*/

void Message::getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const
{
  FUNCTION_TRACE
  try
  {
    T::ParamValue_vec values;
    if (mCacheKey == 0)
      getGridValueVector(values);

    if (!GRID::valueCache.getMinAndMaxValues(mCacheKey,minValue,maxValue))
    {
      getGridValueVector(values);
      GRID::valueCache.getMinAndMaxValues(mCacheKey,minValue,maxValue);
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid value in the given (exact) point.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The parameter value of the given grid point.
*/

T::ParamValue Message::getGridValueByGridPoint(uint grid_i,uint grid_j) const
{
  FUNCTION_TRACE
  try
  {
    if (mDataSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mDataSection' attribute points to NULL!");


    if (mValueDecodingFailed)
    {
      // We have failed to decode parameter values
      return ParamValueMissing;
    }

    int idx = 0; //getGridOriginalValueIndex(grid_i,grid_j);

    auto rows = getGridOriginalRowCount();
    auto cols = getGridOriginalColumnCount();

    if (grid_j >= rows)
      return ParamValueMissing;

    if (grid_i >= cols &&  !isGridGlobal())
      return ParamValueMissing;

    idx = (int)((grid_j * cols) + (grid_i % cols));

    if (idx < 0)
      return ParamValueMissing;

    T::ParamValue value = 0;
    if (mBitmapSection == NULL  ||  mBitmapSection->getBitmapDataSizeInBytes() == 0)
    {
      if (mDataSection->getValueByIndex(idx,value))
        return value;
    }
    else
    {

      long long hash = mBitmapSection->getHash();
      int index = 0;
      if (GRID::indexCache.getIndex(hash,idx,index))
      {
        if (index < 0)
          return ParamValueMissing;

        if (mDataSection->getValueByIndex(index,value))
          return value;
      }
      else
      {
        T::IndexVector indexVector;
        mBitmapSection->getIndexVector((uint)(rows*cols),indexVector);
        GRID::indexCache.addIndexVector(hash,indexVector);
        if (indexVector[idx] < 0)
          return ParamValueMissing;

        if (mDataSection->getValueByIndex(indexVector[idx],value))
          return value;
      }
    }

    if (mCacheKey > 0)
    {
      // Trying to get a memory cached value.

      if (GRID::valueCache.getValue(mCacheKey,(uint)idx,value))
      {
        mPointCacheCoordinate[mPointCachePosition % POINT_CACHE_SIZE] = idx;
        mPointCacheValue[mPointCachePosition % POINT_CACHE_SIZE] = value;
        mPointCachePosition++;

        return value;
      }
    }

    // Trying to find a value from the point cache.

    uint endp = mPointCachePosition;
    if (endp >= POINT_CACHE_SIZE)
      endp = POINT_CACHE_SIZE;

    for (uint t=0; t<endp; t++)
    {
      if (mPointCacheCoordinate[t] == (uint)idx)
        return mPointCacheValue[t];
    }


    if (mCacheKey > 0)
    {
      // Trying to get a compressed cache value.

      if (GRID::valueCache.getCompressedCacheValue(mCacheKey,(uint)idx,value))
      {
        mPointCacheCoordinate[mPointCachePosition % POINT_CACHE_SIZE] = idx;
        mPointCacheValue[mPointCachePosition % POINT_CACHE_SIZE] = value;
        mPointCachePosition++;

        return value;
      }
    }


    T::ParamValue_vec values;
    getGridValueVector(values);
    if ((std::size_t)idx >= values.size())
      return ParamValueMissing;

    mPointCacheCoordinate[mPointCachePosition % POINT_CACHE_SIZE] = idx;
    mPointCacheValue[mPointCachePosition % POINT_CACHE_SIZE] = values[idx];
    mPointCachePosition++;

    return values[idx];
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid value in the given original grid point.

        \param grid_i   The grid i-position.
        \param grid_j   The grid j-position.
        \return         The parameter value of the given grid point.
*/

T::ParamValue Message::getGridValueByOriginalGridPoint(uint grid_i,uint grid_j) const
{
  FUNCTION_TRACE
  try
  {
    if (mValueDecodingFailed)
    {
      // We have failed to decode parameter values
      return ParamValueMissing;
    }

    int idx = getGridOriginalValueIndex(grid_i,grid_j);
    if (idx < 0)
      return ParamValueMissing;

    if (mOrigCacheKey > 0)
    {
      T::ParamValue value = 0;
      if (GRID::valueCache.getValue(mOrigCacheKey,(uint)idx,value))
        return value;
    }

    T::ParamValue_vec values;
    getGridOriginalValueVector(values);
    if ((std::size_t)idx >= values.size())
      return ParamValueMissing;

    return values[idx];
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns all grid data values (also missing values) as the grid
    would be regular. in the case of an irregular grid, the grid rows are filled so that
    the grid looks like a regular grid.

        \param values   The returned grid values.
*/

void Message::getGridValueVector(T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    if (mDataSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mDataSection' attribute points to NULL!");

    values.clear();
    if (mValueDecodingFailed)
    {
      // We have tried to decode parameter values, but failed. It does not make
      // sense to try again.
      return;
    }


    if (mCacheKey > 0)
    {
      if (GRID::valueCache.getValues(mCacheKey,values))
        return;
    }

    auto n = mGridSection->getGridOriginalValueCount();
    auto d = getGridDimensions();

    try
    {
      mDataSection->decodeValues(values);

      if (mDataSection->getPackingMethod() != PackingMethod::SIMPLE_PACKING)
        mOrigCacheKey = GRID::valueCache.addValues(values);

      if (d  &&  n != (d->nx() * d->ny()))
      {
        // Grid rows have different number of columns. Let's fill the rows so that they all have the same
        // number of columns.

        // TODO: We should interpolate between the columns. Now we just repeat the same value.

        auto maxCols = getGridOriginalColumnCount();

        T::ParamValue_vec valVector;
        std::size_t rows = d->ny();

        for (std::size_t r=0; r<rows; r++)
        {
          std::size_t cols = getGridOriginalColumnCount(r);
          double step = (double)maxCols / (double)cols;

          for (std::size_t c=0; c<maxCols; c++)
          {
            uint cc = (uint)((double)c / step);
            int idx = (int)getGridOriginalValueIndex((uint)cc,(uint)r);
            T::ParamValue val = values[idx];
            valVector.push_back(val);
          }
        }
        values = valVector;

        if (mDataSection->getPackingMethod() != PackingMethod::SIMPLE_PACKING)
          mCacheKey = GRID::valueCache.addValues(values);
      }
      else
      {
        mCacheKey = mOrigCacheKey;
      }
    }
    catch (...)
    {
      SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
      exception.addParameter("Message index",std::to_string(mMessageIndex));
      exception.printError();
      mValueDecodingFailed = true;
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the original grid data values. If the grid
    is regular then the 'getGridValueVector()' method returns the same
    result as this method. However, if the grid is irregular then the grid rows
    might contain different number of columns. In this case the data should be
    processed row-by-row and the 'getGridOriginalColumnCount()' method should be
    used in order to find out the number of the columns used in each row. Also
    the 'getGridOriginalValueIndex()' method can be used in order to locate values
    in the returned vector.

        \param values   The returned grid values (original).
*/

void Message::getGridOriginalValueVector(T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    if (mDataSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mDataSection' attribute points to NULL!");

    values.clear();
    if (mValueDecodingFailed)
    {
      // We have tried to decode parameter values, but failed. It does not make
      // sense to try again.
      return;
    }

    if (mOrigCacheKey > 0)
    {
      if (GRID::valueCache.getValues(mOrigCacheKey,values))
        return;
    }

    auto d = getGridDimensions();
    try
    {
      mDataSection->decodeValues(values);
      if (mDataSection->getPackingMethod() != PackingMethod::SIMPLE_PACKING)
        mOrigCacheKey = GRID::valueCache.addValues(values);

      if (getGridLayout() == T::GridLayout::Regular)
      {
        mCacheKey = mOrigCacheKey;
        return;
      }

      if (getGridLayout() == T::GridLayout::Irregular)
      {
        // The grid layout is irregular, which means that grid rows can contain different number of columns.
        // Let's fill the rows so that they all have the same number of columns. I.e. let's create a regular grid.

        // TODO: We should interpolate between the columns. Now we just repeat the same value.

        auto maxCols = getGridOriginalColumnCount();

        T::ParamValue_vec valVector;
        std::size_t rows = 0;
        if (d)
          rows = d->ny();

        for (std::size_t r=0; r<rows; r++)
        {
          std::size_t cols = getGridOriginalColumnCount(r);
          double step = (double)maxCols / (double)cols;

          for (std::size_t c=0; c<maxCols; c++)
          {
            uint cc = (uint)((double)c / step);
            int idx = (int)getGridOriginalValueIndex((uint)cc,(uint)r);
            T::ParamValue val = values[idx];
            valVector.push_back(val);
          }
        }
        if (mDataSection->getPackingMethod() != PackingMethod::SIMPLE_PACKING)
          mCacheKey = GRID::valueCache.addValues(valVector);
      }
    }
    catch (...)
    {
      SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
      exception.addParameter("Message index",std::to_string(mMessageIndex));
      exception.printError();
      mValueDecodingFailed = true;
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the parameter level.

    Sometime the parameter level is "included" in the parameter definition. I.e. there
    might be different parameterId for "temperature-2m" and "temperature-10m". On the other
    hand, there might be only one parameterId for "temperature" but several levels (2m, 10m, etc.).
    So, the same data can be defined in multiple ways.

        \return   The parameter level.
*/

T::ParamLevel Message::getGridParameterLevel() const
{
  FUNCTION_TRACE
  try
  {
    return static_cast<T::ParamLevel>(mProductSection->getLevel());
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the type of the parameter level.

         \return   The parameter level type (= enum value).
*/

T::ParamLevelId Message::getGridParameterLevelId() const
{
  FUNCTION_TRACE
  try
  {
    return (T::ParamLevelId)mProductSection->getIndicatorOfTypeOfLevel();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the parameter level type string (define in Table 4.5).

        \return   The parameter level type (expressed in a string).
*/

std::string Message::getGridParameterLevelIdString() const
{
  FUNCTION_TRACE
  try
  {
    return Identification::gridDef.getGribTableValue(1,0,"3",getGridParameterLevelId());
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





T::SpatialReference* Message::getSpatialReference() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != NULL)
      return mGridSection->getSpatialReference();

    return NULL;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the WKT (Well-Known-Text) of the current grid.

        \return   The WKT of the current grid.
*/

std::string Message::getWKT() const
{
  FUNCTION_TRACE
  try
  {
    std::string wkt;
/*
    T::SpatialReference *sr = getSpatialReference();
    if (sr != NULL)
    {
      char *res = NULL;
      if (sr->exportToWkt((char**)&res))
      {
        wkt = res;
        CPLFree(res);
      }
    }
*/
    return wkt;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





short Message::getForecastType() const
{
  FUNCTION_TRACE
  try
  {
    if (mProductSection)
      return mProductSection->getForecastType();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





short Message::getForecastNumber() const
{
  FUNCTION_TRACE
  try
  {
    if (mProductSection)
      return mProductSection->getForecastNumber();

    return -1;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns 'true' if the grid is global (i.e. goes around the globe).
    If the grid is global then we should be able to interpolate over the grid borders.

        \return   The method returns 'true' if the grid data is global. Otherwise
                  it returns 'false'
*/

bool Message::isGridGlobal() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->isGridGlobal();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}




bool Message::reverseXDirection() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->reverseXDirection();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::reverseYDirection() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to NULL!");

    return mGridSection->reverseYDirection();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns a data pointer to the bitmap. */

T::Data_ptr Message::getBitmapDataPtr() const
{
  FUNCTION_TRACE
  try
  {
    if (mBitmapSection)
      return mBitmapSection->getBitmapDataPtr();

    return NULL;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the size of the bitmap data expressed in bytes. */

std::size_t Message::getBitmapDataSizeInBytes() const
{
  FUNCTION_TRACE
  try
  {
    if (mBitmapSection)
      return mBitmapSection->getBitmapDataSizeInBytes();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns a data pointer to the grid data. */

T::Data_ptr Message::getDataPtr() const
{
  FUNCTION_TRACE
  try
  {
    if (mDataSection)
      return mDataSection->getDataPtr();

    return NULL;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the size of the grid data expressed in bytes. */

std::size_t Message::getDataSize() const
{
  FUNCTION_TRACE
  try
  {
    if (mDataSection)
      return mDataSection->getDataSize();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the max size of the grid data expressed in bytes.
 * This value is used if the original data size is too small (because of the
 * error in the grib file */

std::size_t Message::getDataSizeMax() const
{
  FUNCTION_TRACE
  try
  {
    if (mDataSection)
      return mDataSection->getDataSizeMax();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the value of the binary scale factor. */

std::int16_t Message::getBinaryScaleFactor() const
{
  FUNCTION_TRACE
  try
  {
    if (mDataSection)
      return mDataSection->getBinaryScaleFactor();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the value of the decimal scale factor. */

std::uint16_t Message::getDecimalScaleFactor() const
{
  FUNCTION_TRACE
  try
  {
    if (mProductSection)
      return mProductSection->getDecimalScaleFactor();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the reference value of the grid data. */

std::float_t Message::getReferenceValue() const
{
  FUNCTION_TRACE
  try
  {
    if (mDataSection)
      return mDataSection->getReferenceValue();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the number of bits used per grid value. */

std::uint8_t Message::getBitsPerValue() const
{
  FUNCTION_TRACE
  try
  {
    if (mDataSection)
      return mDataSection->getBitsPerValue();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid decoding flags. */

std::uint8_t Message::getFlags() const
{
  FUNCTION_TRACE
  try
  {
    if (mDataSection)
      return mDataSection->getFlags();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void Message::print(std::ostream& stream,uint level,uint optionFlags) const
{
  FUNCTION_TRACE
  try
  {
    stream << "\n" << space(level) << "########## MESSAGE [" << mMessageIndex << "] ##########\n\n";
    stream << space(level) << "- filePosition            = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- gribParameterId         = " << toString(mGribParameterId) << "\n";
    stream << space(level) << "- gribParameterName       = " << mGribParameterName << "\n";
    stream << space(level) << "- gribPrameterDescription = " << mGribParameterDescription << "\n";
    stream << space(level) << "- gribParameterUnits      = " << mGribParameterUnits << "\n";
    stream << space(level) << "- parameterLevel          = " << toString(getGridParameterLevel()) << "\n";
    stream << space(level) << "- parameterLevelId        = " << toString(getGridParameterLevelId()) << "\n";
    stream << space(level) << "- parameterLevelIdString  = " << getGridParameterLevelIdString() << "\n";
    stream << space(level) << "- fmiProducerName         = " << mFmiProducerName << "\n";
    stream << space(level) << "- fmiParameterId          = " << toString(mFmiParameterId) << "\n";
    stream << space(level) << "- fmiParameterLevelId     = " << toString(mFmiParameterLevelId) << "\n";
    stream << space(level) << "- fmiParameterName        = " << mFmiParameterName << "\n";
    stream << space(level) << "- fmiParameterDescription = " << mFmiParameterDescription << "\n";
    stream << space(level) << "- fmiParameterUnits       = " << mFmiParameterUnits << "\n";
    stream << space(level) << "- newbaseParameterId      = " << mNewbaseParameterId << "\n";
    stream << space(level) << "- newbaseParameterName    = " << mNewbaseParameterName << "\n";
    stream << space(level) << "- cdmParameterId          = " << mCdmParameterId << "\n";
    stream << space(level) << "- cdmParameterName        = " << mCdmParameterName << "\n";
    stream << space(level) << "- newbaseParameterId      = " << mNewbaseParameterId << "\n";
    stream << space(level) << "- newbaseParameterName    = " << mNewbaseParameterName << "\n";
    stream << space(level) << "- referenceTime           = " << getReferenceTime() << "\n";
    stream << space(level) << "- forecastTime            = " << getForecastTime() << "\n";
    stream << space(level) << "- gridGeometryId          = " << getGridGeometryId() << "\n";
    stream << space(level) << "- gridHash                = " << getGridHash() << "\n";
    stream << space(level) << "- gridProjection          = " << T::get_gridProjectionString(getGridProjection()) << "\n";
    stream << space(level) << "- gridLayout              = " << T::get_gridLayoutString(getGridLayout()) << "\n";
    stream << space(level) << "- gridOriginalRowCount    = " << toString(getGridOriginalRowCount()) << "\n";
    stream << space(level) << "- gridOriginalColumnCount = " << toString(getGridOriginalColumnCount()) << "\n";

    if (mIndicatorSection)
      mIndicatorSection->print(stream,level+1,optionFlags);

    if (mProductSection)
      mProductSection->print(stream,level+1,optionFlags);

    if (mGridSection)
      mGridSection->print(stream,level+1,optionFlags);

    if (mBitmapSection)
      mBitmapSection->print(stream,level+1,optionFlags);

    if (mDataSection)
    {
      mDataSection->print(stream,level+1,optionFlags);

      if (optionFlags &  GRID::PrintFlag::data)
      {
        T::ParamValue_vec values;
        getGridValueVector(values);

        stream << space(level+1) << "- data (from the grid corners):\n";

        char st[1000];
        uint ny = (uint)mGridSection->getGridOriginalRowCount();
        uint nx = (uint)mGridSection->getGridOriginalColumnCount();
        uint c = 0;
        std::size_t sz = values.size();

        for (uint y=0; y < ny; y++)
        {
          for (uint x=0; x < nx; x++)
          {
            if ((y < 3  ||  y >= ny-3)  &&  (x < 3  ||  x >= nx-3))
            {
              if (c < sz)
              {
                auto val = values[c];
                if (val != ParamValueMissing)
                  sprintf(st,"[%u,%u] %f",y+1,x+1,(double)(val));
                else
                  sprintf(st,"[%u,%u] NA",y+1,x+1);
                stream << space(level+3) << st << "\n";
              }
            }
            c++;
          }
        }
      }
    }

  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}


}  // namespace GRIB1
}  // namespace SmartMet

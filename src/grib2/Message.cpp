#include "Message.h"
#include "GribFile.h"
#include "BitmapSection.h"
#include "DataSection.h"
#include "GridSection.h"
#include "IdentificationSection.h"
#include "IndicatorSection.h"
#include "LocalSection.h"
#include "ProductSection.h"
#include "RepresentationSection.h"
#include "../grid/PrintOptions.h"
#include "../grid/ValueCache.h"
#include "../grid/IndexCache.h"
#include "../grid/Typedefs.h"
#include "../common/Dimensions.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"
#include "../identification/GridDef.h"
#include "../common/ShowFunction.h"
#include <iostream>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace GRIB2
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
    attributeList.addAttribute(name,mFmiProducerName);

    sprintf(name,"%smessage[%u].gribParameterId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(getGribParameterId()));

    sprintf(name,"%smessage[%u].gribParameterName",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mGribParameterName);

    sprintf(name,"%smessage[%u].gribParameterDescription",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mGribParameterDescription);

    sprintf(name,"%smessage[%u].gribParameterUnits",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mGribParameterUnits);

    sprintf(name,"%smessage[%u].grib1ParameterLevelId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(getGrib1ParameterLevelId()));

    sprintf(name,"%smessage[%u].grib2ParameterLevelId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(getGrib2ParameterLevelId()));

    sprintf(name,"%smessage[%u].fmiParameterId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString(getFmiParameterId()));

    sprintf(name,"%smessage[%u].fmiParameterLevelId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,toString((uint)getFmiParameterLevelId()));

    sprintf(name,"%smessage[%u].fmiParameterName",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mFmiParameterName);

    sprintf(name,"%smessage[%u].fmiParameterDescription",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mFmiParameterDescription);

    sprintf(name,"%smessage[%u].fmiParameterUnits",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mFmiParameterUnits);

    sprintf(name,"%smessage[%u].newbaseParameterId",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mNewbaseParameterId);

    sprintf(name,"%smessage[%u].newbaseParameterName",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,mNewbaseParameterName);

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

    sprintf(name,"%smessage[%u].referenceTime",prefix.c_str(),(uint)mMessageIndex);
    attributeList.addAttribute(name,getReferenceTime());

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

    if (mIdentificationSection)
      mIdentificationSection->getAttributeList(name,attributeList);

    if (mLocalSection)
      mLocalSection->getAttributeList(name,attributeList);

    if (mGridSection)
      mGridSection->getAttributeList(name,attributeList);

    if (mProductSection)
      mProductSection->getAttributeList(name,attributeList);

    if (mRepresentationSection)
      mRepresentationSection->getAttributeList(name,attributeList);

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

    // Index of the section processed last (=none)
    std::uint8_t last_idx = 0u;

    //std::uint8_t tablesVersion = 0;

    while (true)
    {
      if ((memoryReader.getReadPtr()+4) > memoryReader.getEndPtr())
      {
        std::cout << CODE_LOCATION << ": Memory area end reached!\n";
        break;
      }

      if (memoryReader.peek_string("GRIB"))
      {
        IndicatorSection *section = new IndicatorSection(this);
        mIndicatorSection.reset(section);
        section->read(memoryReader);
      }
      else
      if (memoryReader.peek_string("7777"))
      {
        break;  // NOTE: Leave the ptr pointing at the end section so that the external parser can
                // quit
      }
      else
      {
        std::uint8_t idx = memoryReader.getByte(memoryReader.getReadPosition() + 4);


        // A message ends if an earlier section is encountered
        if (idx < last_idx)
          break;

        if (idx == last_idx)
          throw SmartMet::Spine::Exception(BCP,"Cannot repeat the same section twice (message '" + std::to_string(mMessageIndex) + "')!");

        // Update for the next iteration
        last_idx = idx;

        unsigned long long rPos = memoryReader.getGlobalReadPosition();

        try
        {
          // Create the corresponding section from the pointer & advance the pointer to next section

          switch (idx)
          {
            case SectionNumber::identification_section:
            {
              IdentificationSection *section = new IdentificationSection(this);
              mIdentificationSection.reset(section);
              section->read(memoryReader);
            }
            break;

            case SectionNumber::local_section:
            {
              LocalSection *section = new LocalSection(this);
              mLocalSection.reset(section);
              section->read(memoryReader);
            }
            break;

            case SectionNumber::grid_section:
            {
              GridSection *section = new GridSection(this);
              mGridSection.reset(section);
              section->read(memoryReader);
            }
            break;

            case SectionNumber::product_section:
            {
              ProductSection *section = new ProductSection(this);
              mProductSection.reset(section);
              section->read(memoryReader);
            }
            break;

            case SectionNumber::representation_section:
            {
              RepresentationSection *section = new RepresentationSection(this);
              mRepresentationSection.reset(section);
              section->read(memoryReader);
            }
            break;

            case SectionNumber::bitmap_section:
            {
              BitmapSection *section = new BitmapSection(this);
              mBitmapSection.reset(section);
              section->read(memoryReader);
            }
            break;

            case SectionNumber::data_section:
            {
              DataSection *section = new DataSection(this);
              mDataSection.reset(section);
              section->read(memoryReader);
            }
            break;

            default:
            {
              SmartMet::Spine::Exception exception(BCP,"Invalid GRIB section number '" + std::to_string(static_cast<int>(idx)) + "'!");
              exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()+4));
              throw exception;
             }
          }
        }
        catch (...)
        {
          SmartMet::Spine::Exception exception(BCP,"Section creation failed!",NULL);
          exception.addParameter("Section number",std::to_string(static_cast<int>(idx)));
          exception.addParameter("Section start position",uint64_toHex(rPos));
          throw exception;
        }
      }
    }

    // All messages must define sections 4-7

    if (!mProductSection)
      throw SmartMet::Spine::Exception(BCP,"The product section is missing!");

    if (!mRepresentationSection)
      throw SmartMet::Spine::Exception(BCP,"The representation section is missing!");

    if (!mBitmapSection)
      throw SmartMet::Spine::Exception(BCP,"The bitmap section is missing!");

    if (!mDataSection)
      throw SmartMet::Spine::Exception(BCP,"The data section is missing!");
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Message read failed!",NULL);
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





/*! \brief The method return the version number of the used GRIB tables. */

std::uint8_t Message::getTablesVersion() const
{
  FUNCTION_TRACE
  try
  {
    std::uint8_t tablesVersion = 0;
    if (mIdentificationSection)
      tablesVersion = *mIdentificationSection->getTablesVersion();

    return tablesVersion;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method completes the message structure by using the previous message. */

void Message::copyMissingSections(const Message &other)
{
  FUNCTION_TRACE
  try
  {
    if (!mIndicatorSection)
      mIndicatorSection = other.mIndicatorSection;

    if (!mIdentificationSection)
      mIdentificationSection = other.mIdentificationSection;

    if (!mLocalSection)
      mLocalSection = other.mLocalSection;

    if (!mGridSection)
      mGridSection = other.mGridSection;

    if (other.mPreviousBitmapSection)
    {
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method tries to find an unique parameterId for the grid content. */

void Message::initParameterInfo()
{
  FUNCTION_TRACE
  try
  {
    mGribParameterId  = Identification::gridDef.getGribParameterId(*this);
    mGribParameterName  = Identification::gridDef.getGribParameterName(*this);
    mGribParameterDescription  = Identification::gridDef.getGribParameterDescription(*this);
    mGribParameterUnits  = Identification::gridDef.getGribParameterUnits(*this);
    mGrib2ParameterLevelId = Identification::gridDef.getGrib2LevelId(*this);

    mGrib1ParameterLevelId = Identification::gridDef.getGrib1LevelId(*this);

    //mFmiProducerName = Identification::gridDef.getProducerName(*this);

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
        int geometryId = Identification::gridDef.getGrib2GeometryIdByHash(hash);
        if (geometryId != 0)
          setGridGeometryId(geometryId);
        else
        {
          std::cout << "\n** Geometry not configured : " << hash << " (" << mGribFile->getFileName() << ")\n";
          std::cout << "** Add the following line into the geometry definition file (=> fill id,name and desciption fields) :\n\n";
          std::cout << getGridGeometryString() << "\n\n";
          //SmartMet::Spine::Exception exception(BCP,"Geometry not found");
          //throw exception;
        }
      }
      else
      {
        printf("Hash is zero!\n");
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





/*! \brief Set the previous bitmap section to be used instead if necessary. */

void Message::setPreviousBitmapSection(boost::shared_ptr<BitmapSection> previousBitmapSection)
{
  FUNCTION_TRACE
  try
  {
    const int refers_to_earlier_bitmap = 254;

    if (mBitmapSection)
    {
      auto indicator = mBitmapSection->getBitMapIndicator();
      if (!missing(indicator))
      {
        if (*indicator == refers_to_earlier_bitmap)
        {
          mPreviousBitmapSection = previousBitmapSection;
        }
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





 /*! \brief The method returns 'true' if all sections are defined. */

bool Message::hasRequiredSections() const
{
  FUNCTION_TRACE
  try
  {
    // Note: LocalSection can be missing

    return (!!mIndicatorSection && !!mIdentificationSection && !!mGridSection && !!mProductSection && !!mRepresentationSection &&
            !!mBitmapSection && !!mDataSection);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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





std::string Message::getGridGeometryString() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != NULL)
      return mGridSection->getGridGeometryString();

    std::string str;
    return str;
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
  FUNCTION_TRACE
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





/*! \brief The method can be used in order to find out the message's start
    position in the grib file.

        \return  The message's start position in the grib file.
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
  // FUNCTION_TRACE
  try
  {
    return mBitmapSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns a shared pointer to the previous BitmapSection object. */

BitmapSection_sptr Message::getPreviousBitmapSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mPreviousBitmapSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns a shared pointer to the GridSection object. */

GridSection_sptr Message::getGridSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mGridSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns a pointer to the RepresentationSection object. */

RepresentSection_cptr Message::getRepresentationSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mRepresentationSection.get();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




/*! \brief The method returns a shared pointer to the IdentificationSection object. */

IdentificSection_sptr Message::getIdentificationSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mIdentificationSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns a shared pointer to the IndicatorSection object. */

IndicatorSection_sptr Message::getIndicatorSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mIndicatorSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns a shared pointer to the LocalSection object. */

LocalSection_sptr Message::getLocalSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mLocalSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns a pointer to the ProductSection object. */

ProductSection_cptr Message::getProductSection() const
{
  // FUNCTION_TRACE
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

DataSection_cptr Message::getDataSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mDataSection.get();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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





/*! \brief The method returns all grid data values (also missing values) as
    the grid would be regular.

    In the case of an irregular grid, the grid rows are filled so that
    the grid looks like a regular grid.

        \param values   The returned grid values.
*/

void Message::getGridValueVector(T::ParamValue_vec& values) const
{
  FUNCTION_TRACE
  try
  {
    if (mRepresentationSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mRepresentationSection' attribute points to NULL!");

    values.clear();

    if (mValueDecodingFailed)
    {
      // We have tried earlier to decode parameter values and failed. So, it
      // does not make sense to try again.
      return;
    }

    if (mCacheKey > 0)
    {
      if (GRID::valueCache.getValues(mCacheKey,values))
        return;
    }

    try
    {
      mRepresentationSection->decodeValues(values);
      mCacheKey = GRID::valueCache.addValues(values);
    }
    catch (...)
    {
      SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
      exception.addParameter("Message index",std::to_string(mMessageIndex));
      exception.addParameter("Filename",mGribFile->getFileName());
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





/*! \brief The method returns the original grid data values.

   If the grid is regular then the 'getGridValueVector()' method returns the same
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
    if (mRepresentationSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mRepresentationSection' attribute points to NULL!");

    values.clear();

    if (mValueDecodingFailed)
    {
      // We have tried earlier to decode parameter values and failed. So, it
      // does not make sense to try again.
      return;
    }

    if (mOrigCacheKey > 0)
    {
      if (GRID::valueCache.getValues(mOrigCacheKey,values))
        return;
    }

    try
    {
      mRepresentationSection->decodeValues(values);
      mCacheKey = GRID::valueCache.addValues(values);
      mOrigCacheKey = mCacheKey;
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
    if (mProductSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mProductSection' attribute points to NULL!");

    return mProductSection->getGribParameterLevel();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the parameter level id (define in Table 4.5).

        \return   The parameter level id (expressed as a number).
*/

T::ParamLevelId Message::getGridParameterLevelId() const
{
  FUNCTION_TRACE
  try
  {
    if (mProductSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mProductSection' attribute points to NULL!");

    return mProductSection->getGribParameterLevelId();
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
    if (mProductSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mProductSection' attribute points to NULL!");

    return mProductSection->getForecastType();
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
    if (mProductSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mProductSection' attribute points to NULL!");

    return mProductSection->getForecastNumber();
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
    std::uint8_t tablesVersion = getTablesVersion();
    return Identification::gridDef.getGribTableValue(2,tablesVersion,"4.5",getGridParameterLevelId());
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





T::TimeString Message::getReferenceTime() const
{
  FUNCTION_TRACE
  try
  {
    if (mIdentificationSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mIdentificationSection' attribute points to NULL!");

    return mIdentificationSection->getReferenceTime();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





T::TimeString Message::getForecastTime() const
{
  FUNCTION_TRACE
  try
  {
    if (mIdentificationSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mIdentificationSection' attribute points to NULL!");

    if (mProductSection == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mProductSection' attribute points to NULL!");

    return mProductSection->getForecastTime(mIdentificationSection->getReferenceTime());
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
    //printf("getGridValueByGridPoint(%u,%u)\n",grid_i,grid_j);
    if (mValueDecodingFailed)
    {
      // We have failed to decode parameter values
      return ParamValueMissing;
    }

    auto d = getGridDimensions();
    if (!d)
      return ParamValueMissing;

    if (grid_j >= d->ny())
      return ParamValueMissing;

    if (grid_i >= d->nx() &&  !isGridGlobal())
      return ParamValueMissing;

    uint idx = grid_j * d->nx() + (grid_i % d->nx());


    T::ParamValue value = 0;
    if (mBitmapSection == NULL  ||  mBitmapSection->getBitmapDataSizeInBytes() == 0)
    {
      if (mRepresentationSection->getValueByIndex(idx,value))
      {
        // printf("Value %u,%u : %f\n",grid_i,grid_j,value);
        return value;
      }
    }
    else
    {

      long long hash = mBitmapSection->getHash();

      int index = 0;
      if (GRID::indexCache.getIndex(hash,idx,index))
      {
        if (index < 0)
          return ParamValueMissing;

        if (mRepresentationSection->getValueByIndex(index,value))
        {
          // printf("Value %u,%u : %f\n",grid_i,grid_j,value);
          return value;
        }
      }
      else
      {
        T::IndexVector indexVector;
        mBitmapSection->getIndexVector((uint)(d->nx()*d->ny()),indexVector);
        GRID::indexCache.addIndexVector(hash,indexVector);
        if (indexVector[idx] < 0)
          return ParamValueMissing;

        if (mRepresentationSection->getValueByIndex(indexVector[idx],value))
        {
          // printf("Value %u,%u : %f\n",grid_i,grid_j,value);
          return value;
        }
      }
    }

    if (mCacheKey > 0)
    {
      // Trying to get a memory cache value.

      if (GRID::valueCache.getValue(mCacheKey,idx,value))
      {
        mPointCacheCoordinate[mPointCachePosition % POINT_CACHE_SIZE] = idx;
        mPointCacheValue[mPointCachePosition % POINT_CACHE_SIZE] = value;
        mPointCachePosition++;

        // printf("Value %u,%u : %f\n",grid_i,grid_j,value);
        return value;
      }
    }


    // Trying to find the value from the point cache.

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

      if (GRID::valueCache.getCompressedCacheValue(mCacheKey,idx,value))
      {
        mPointCacheCoordinate[mPointCachePosition % POINT_CACHE_SIZE] = idx;
        mPointCacheValue[mPointCachePosition % POINT_CACHE_SIZE] = value;
        mPointCachePosition++;

        // printf("Value %u,%u : %f\n",grid_i,grid_j,value);
        return value;
      }
    }


    T::ParamValue_vec values;
    getGridValueVector(values);
    if (idx >= values.size())
      return ParamValueMissing;

    mPointCacheCoordinate[mPointCachePosition % POINT_CACHE_SIZE] = idx;
    mPointCacheValue[mPointCachePosition % POINT_CACHE_SIZE] = values[idx];
    mPointCachePosition++;

    // printf("Value %u,%u : %f\n",grid_i,grid_j,values[idx]);
    return values[idx];
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
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

    bool res = mGridSection->getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j);
    //printf("LATLON %f,%f => %f,%f  => %u,%u\n",lat,lon,grid_i,grid_j,(uint)grid_i,(uint)grid_j);

    //std::cout << getForecastTime() << " VALUE " << getGridValueByGridPoint((uint)grid_i,(uint)grid_j) << "\n";
    return res;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
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
    stream << space(level) << "- filePosition             = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- gribParameterId          = " << toString(mGribParameterId) << "\n";
    stream << space(level) << "- gribParameterName        = " << mGribParameterName << "\n";
    stream << space(level) << "- gribParameterDescription = " << mGribParameterDescription << "\n";
    stream << space(level) << "- gribParameterUnits       = " << mGribParameterUnits << "\n";
    stream << space(level) << "- parameterLevel           = " << toString(getGridParameterLevel()) << "\n";
    stream << space(level) << "- parameterLevelId         = " << toString(getGridParameterLevelId()) << "\n";
    stream << space(level) << "- parameterLevelIdString   = " << getGridParameterLevelIdString() << "\n";
    stream << space(level) << "- fmiProducerName          = " << mFmiProducerName << "\n";
    stream << space(level) << "- fmiParameterId           = " << toString(mFmiParameterId) << "\n";
    stream << space(level) << "- fmiParameterLevelId      = " << toString((uint)mFmiParameterLevelId) << "\n";
    stream << space(level) << "- fmiParameterName         = " << mFmiParameterName << "\n";
    stream << space(level) << "- fmiParameterDescription  = " << mFmiParameterDescription << "\n";
    stream << space(level) << "- fmiParameterUnits        = " << mFmiParameterUnits << "\n";
    stream << space(level) << "- newbaseParameterId       = " << toString(mNewbaseParameterId) << "\n";
    stream << space(level) << "- cdmParameterId           = " << mCdmParameterId << "\n";
    stream << space(level) << "- cdmParameterName         = " << mCdmParameterName << "\n";
    stream << space(level) << "- newbaseParameterId       = " << mNewbaseParameterId << "\n";
    stream << space(level) << "- newbaseParameterName     = " << mNewbaseParameterName << "\n";
    stream << space(level) << "- referenceTime            = " << getReferenceTime() << "\n";
    stream << space(level) << "- forecastTime             = " << getForecastTime() << "\n";
    stream << space(level) << "- gridGeometryId           = " << getGridGeometryId() << "\n";
    stream << space(level) << "- gridHash                 = " << getGridHash() << "\n";
    stream << space(level) << "- gridProjection           = " << T::get_gridProjectionString(getGridProjection()) << "\n";
    stream << space(level) << "- gridLayout               = " << T::get_gridLayoutString(getGridLayout()) << "\n";
    stream << space(level) << "- gridOriginalRowCount     = " << toString(getGridOriginalRowCount()) << "\n";
    stream << space(level) << "- gridOriginalColumnCount  = " << toString(getGridOriginalColumnCount()) << "\n";

    if (mIndicatorSection)
      mIndicatorSection->print(stream,level+1,optionFlags);

    if (mIdentificationSection)
      mIdentificationSection->print(stream,level+1,optionFlags);

    if (mLocalSection)
      mLocalSection->print(stream,level+1,optionFlags);

    if (mGridSection)
      mGridSection->print(stream,level+1,optionFlags);

    if (mProductSection)
      mProductSection->print(stream,level+1,optionFlags);

    if (mRepresentationSection)
      mRepresentationSection->print(stream,level+1,optionFlags);

    if (mBitmapSection  ||  mPreviousBitmapSection)
    {
      T::Data_ptr bitmap = NULL;
      if (mPreviousBitmapSection)
      {
        mPreviousBitmapSection->print(stream,level+1,optionFlags);
        bitmap = mPreviousBitmapSection->getBitmapDataPtr();
      }
      else
      {
        mBitmapSection->print(stream,level+1,optionFlags);
        bitmap = mBitmapSection->getBitmapDataPtr();
      }

      if ((optionFlags &  GRID::PrintFlag::bitmap) != 0  &&  mGridSection  &&  bitmap)
      {
        auto dimensions = mGridSection->getGridDimensions();
        if (dimensions)
        {
          uint ny = dimensions->ny();
          uint nx = dimensions->nx();

          const int bitmask[] = {128, 64, 32, 16, 8, 4, 2, 1};
          uint c = 0;

          for (uint y=0; y < ny; y++)
          {
            for (uint x=0; x < nx; x++)
            {

              if ((bitmap[c / 8] & bitmask[c % 8]) == 0)
                stream << "0";
              else
                stream << "1";
              c++;
            }
            stream << "\n";
          }
        }
      }
    }

    if (mDataSection)
    {
      mDataSection->print(stream,level+1,optionFlags);

      if ((optionFlags &  GRID::PrintFlag::data) != 0  &&  mGridSection)
      {
        auto dimensions = mGridSection->getGridDimensions();
        if (dimensions)
        {
          T::ParamValue_vec values;
          mRepresentationSection->decodeValues(values);

          stream << space(level+1) << "- data (from the grid corners):\n";

          char st[1000];
          uint c = 0;
          uint ny = dimensions->ny();
          uint nx = dimensions->nx();
          std::size_t sz = values.size();

          for (uint y=0; y < ny; y++)
          {
            for (uint x=0; x < nx; x++)
            {
              if (c < sz  &&  (y < 3  ||  y >= ny-3)  &&  (x < 3  ||  x >= nx-3))
              {
                auto val = values[c];
                if (val != ParamValueMissing)
                  sprintf(st,"[%u,%u] %f",y+1,x+1,(double)(val));
                else
                  sprintf(st,"[%u,%u] NA",y+1,x+1);

                stream << space(level+3) << st << "\n";
              }
              c++;
            }
          }
        }
      }
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.printError();
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}


}  // namespace GRIB2
}  // namespace SmartMet

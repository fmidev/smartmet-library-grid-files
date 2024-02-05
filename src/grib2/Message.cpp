#include "Message.h"
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
#include "../grid/GridFile.h"
#include "../common/BitArrayWriter.h"
#include "../common/Dimensions.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"
#include "../common/MemoryMapper.h"
#include "../identification/GridDef.h"
#include "../common/ShowFunction.h"
#include <iostream>
#include <sys/mman.h>
#include <macgyver/StringConversion.h>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

Message::Message()
{
  FUNCTION_TRACE
  try
  {
    mFilePosition = 0;
    mGeometryId = 0;
    mFmiParameterLevelId = 0;
    mCacheKey = 0;
    mOrigCacheKey = 0;
    mValueDecodingFailed = false;
    mIsRead = false;
    mMessageSize = 0;
    mDataLocked = false;
    mFileType = T::FileTypeValue::Grib2;
    mForecastTimeT = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Message::Message(GRID::GridFile *gridFile,uint messageIndex,GRID::MessageInfo& messageInfo)
{
  FUNCTION_TRACE
  try
  {
    mGridFilePtr = gridFile;
    mMessageIndex = messageIndex;
    mFilePosition = messageInfo.mFilePosition;
    mMessageSize = messageInfo.mMessageSize;
    mFmiParameterId = messageInfo.mFmiParameterId;
    mFmiParameterName = messageInfo.mFmiParameterName;
    mFmiParameterLevelId = messageInfo.mFmiParameterLevelId;
    mParameterLevel = messageInfo.mParameterLevel;
    mGeometryId = messageInfo.mGeometryId;
    mCacheKey = 0;
    mOrigCacheKey = 0;
    mValueDecodingFailed = false;
    mIsRead = false;
    mDataLocked = false;
    mFileType = T::FileTypeValue::Grib2;
    mForecastTimeT = messageInfo.mForecastTime;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

Message::Message(const Message& other)
:GRID::Message(other)
{
  FUNCTION_TRACE
  try
  {
    mGridFilePtr = nullptr;
    mFilePosition = other.mFilePosition;
    mMessageSize = other.mMessageSize;
    mIsRead = true;
    //mForecastTime = other.mForecastTime;
    mForecastTimeT = other.mForecastTimeT;

    if (other.mIndicatorSection)
    {
      mIndicatorSection.reset(new IndicatorSection(*(other.mIndicatorSection.get())));
      mIndicatorSection->setMessagePtr(this);
    }

    if (other.mIdentificationSection)
    {
      mIdentificationSection.reset(new IdentificationSection(*(other.mIdentificationSection.get())));
      mIdentificationSection->setMessagePtr(this);
    }

    if (other.mLocalSection)
    {
      mLocalSection.reset(new LocalSection(*(other.mLocalSection.get())));
      mLocalSection->setMessagePtr(this);
    }

    if (other.mGridSection)
    {
      mGridSection.reset(new GridSection(*(other.mGridSection.get())));
      mGridSection->setMessagePtr(this);
    }

    if (other.mProductSection)
    {
      mProductSection.reset(new ProductSection(*(other.mProductSection.get())));
      mProductSection->setMessagePtr(this);
    }

    if (other.mRepresentationSection)
    {
      mRepresentationSection.reset(new RepresentationSection(*(other.mRepresentationSection.get())));
      mRepresentationSection->setMessagePtr(this);
    }

    if (other.mBitmapSection)
    {
      mBitmapSection.reset(new BitmapSection(*(other.mBitmapSection.get())));
      mBitmapSection->setMessagePtr(this);
    }

    if (other.mDataSection)
    {
      mDataSection.reset(new DataSection(*(other.mDataSection.get())));
      mDataSection->setMessagePtr(this);
    }

    if (other.mPreviousBitmapSection)
    {
      mPreviousBitmapSection.reset(new BitmapSection(*(other.mPreviousBitmapSection.get())));
      mPreviousBitmapSection->setMessagePtr(this);
    }

    mCacheKey = 0;
    mOrigCacheKey = 0;
    mValueDecodingFailed = other.mValueDecodingFailed;
    mDataLocked = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

Message::~Message()
{
  FUNCTION_TRACE
  try
  {
    if (mCacheKey)
      GRID::valueCache.deleteValues(mCacheKey);

    if (mOrigCacheKey)
      GRID::valueCache.deleteValues(mOrigCacheKey);

    if (mDataLocked)
    {
      auto addr = getDataPtr();
      auto len = getDataSize();

      if (addr != nullptr &&  len > 0)
      {
        munlock(addr,len);
        mDataLocked = false;
      }
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





void Message::premap() const
{
  FUNCTION_TRACE
  try
  {
    if (mPremapped)
      return;

    mPremapped = true;

    if (mDataSection)
    {
      auto addr = mDataSection->getDataPtr();
      auto sz = mDataSection->getDataSize();

      if (addr && sz > 0)
      {
        memoryMapper.premap((char*)addr,(char*)addr+sz-1);
      }
    }

    if (mBitmapSection)
    {
      auto bitmap = mBitmapSection->getBitmapDataPtr();
      auto sz = mBitmapSection->getBitmapDataSizeInBytes();

      if (bitmap && sz > 0)
        memoryMapper.premap((char*)bitmap,(char*)bitmap+sz-1);
    }
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

bool Message::setProperty(uint propertyId,long long value)
{
  FUNCTION_TRACE
  try
  {
    if (propertyId >= Property::IndicatorSection::FirstProperty  &&  propertyId <= Property::IndicatorSection::LastProperty)
    {
      initIndicatorSection();
      return mIndicatorSection->setProperty(propertyId,value);
    }

    if (propertyId >= Property::IdentificationSection::FirstProperty  &&  propertyId <= Property::IdentificationSection::LastProperty)
    {
      initIdentificationSection();
      return mIdentificationSection->setProperty(propertyId,value);
    }

    if (propertyId >= Property::LocalSection::FirstProperty  &&  propertyId <= Property::LocalSection::LastProperty)
    {
      initLocalSection();
      return mLocalSection->setProperty(propertyId,value);
    }

    if (propertyId >= Property::GridSection::FirstProperty  &&  propertyId <= Property::GridSection::LastProperty)
    {
      initGridSection();
      return mGridSection->setProperty(propertyId,value);
    }

    if (propertyId >= Property::ProductSection::FirstProperty  &&  propertyId <= Property::ProductSection::LastProperty)
    {
      initProductSection();
      return mProductSection->setProperty(propertyId,value);
    }

    if (propertyId >= Property::RepresentationSection::FirstProperty  &&  propertyId <= Property::RepresentationSection::LastProperty)
    {
      initRepresentationSection();
      return mRepresentationSection->setProperty(propertyId,value);
    }

    if (propertyId >= Property::BitmapSection::FirstProperty  &&  propertyId <= Property::BitmapSection::LastProperty)
    {
      initBitmapSection();
      return mBitmapSection->setProperty(propertyId,value);
    }

    if (propertyId >= Property::DataSection::FirstProperty  &&  propertyId <= Property::DataSection::LastProperty)
    {
      initDataSection();
      return mDataSection->setProperty(propertyId,value);
    }

    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("propertyId",Fmi::to_string(propertyId));
    exception.addParameter("value",std::to_string(value));
    throw exception;
  }
}





/*! \brief The method is used for setting a (double) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(uint propertyId,double value)
{
  FUNCTION_TRACE
  try
  {
    return setProperty(propertyId,C_INT64(value));
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("propertyId",Fmi::to_string(propertyId));
    exception.addParameter("value",Fmi::to_string(value));
    throw exception;
  }
}





/*! \brief The method is used for setting a (long long) value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the property to be set.
        \return              The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(const char *propertyName,long long value)
{
  FUNCTION_TRACE
  try
  {
    uint id = gribProperty.getPropertyId(propertyName);
    if (id == 0)
    {
      Fmi::Exception exception(BCP,"Unknow property name!");
      exception.addParameter("propertyName",propertyName);
    }

    return setProperty(id,value);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("propertyName",propertyName);
    exception.addParameter("value",std::to_string(value));
    throw exception;
  }
}





/*! \brief The method is used for setting a (double) value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the property to be set.
        \return              The method returns true if the value of the requested property was set.
*/

bool Message::setProperty(const char *propertyName,double value)
{
  FUNCTION_TRACE
  try
  {
    uint id = gribProperty.getPropertyId(propertyName);
    if (id == 0)
    {
      Fmi::Exception exception(BCP,"Unknow property name!");
      exception.addParameter("propertyName",propertyName);
    }

    return setProperty(id,value);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("propertyName",propertyName);
    exception.addParameter("value",Fmi::to_string(value));
    throw exception;
  }
}





/*! \brief The method is used for fetching a (long long ) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool Message::getProperty(uint propertyId,long long& value)
{
  FUNCTION_TRACE
  try
  {
    if (propertyId >= Property::IndicatorSection::FirstProperty  &&  propertyId <= Property::IndicatorSection::LastProperty)
    {
      if (mIndicatorSection)
        return mIndicatorSection->getProperty(propertyId,value);
    }

    if (propertyId >= Property::IdentificationSection::FirstProperty  &&  propertyId <= Property::IdentificationSection::LastProperty)
    {
      if (mIdentificationSection)
        return mIdentificationSection->getProperty(propertyId,value);
    }

    if (propertyId >= Property::LocalSection::FirstProperty  &&  propertyId <= Property::LocalSection::LastProperty)
    {
      if (mLocalSection)
        return mLocalSection->getProperty(propertyId,value);
    }

    if (propertyId >= Property::GridSection::FirstProperty  &&  propertyId <= Property::GridSection::LastProperty)
    {
      if (mGridSection)
        return mGridSection->getProperty(propertyId,value);
    }

    if (propertyId >= Property::ProductSection::FirstProperty  &&  propertyId <= Property::ProductSection::LastProperty)
    {
      if (mProductSection)
        return mProductSection->getProperty(propertyId,value);
    }

    if (propertyId >= Property::RepresentationSection::FirstProperty  &&  propertyId <= Property::RepresentationSection::LastProperty)
    {
      if (mRepresentationSection)
        return mRepresentationSection->getProperty(propertyId,value);
    }

    if (propertyId >= Property::BitmapSection::FirstProperty  &&  propertyId <= Property::BitmapSection::LastProperty)
    {
      if (mBitmapSection)
        return mBitmapSection->getProperty(propertyId,value);
    }

    if (propertyId >= Property::DataSection::FirstProperty  &&  propertyId <= Property::DataSection::LastProperty)
    {
      if (mDataSection)
        return mDataSection->getProperty(propertyId,value);
    }

    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("propertyId",std::to_string(propertyId));
    exception.addParameter("value",std::to_string(value));
    throw exception;
  }
}





/*! \brief The method is used for fetching a (long long) value for the property according to the property name.

        \param propertyName  The unique name of the requested property.
        \param value         The value of the requested property is returned in this parameter.
        \return              The method returns true if the value of the requested property was found.
*/

bool Message::getProperty(const char *propertyName,long long& value)
{
  FUNCTION_TRACE
  try
  {
    uint id = gribProperty.getPropertyId(propertyName);
    if (id == 0)
    {
      Fmi::Exception exception(BCP,"Unknow property name!");
      exception.addParameter("propertyName",propertyName);
    }

    return getProperty(id,value);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("propertyName",propertyName);
    exception.addParameter("value",std::to_string(value));
    throw exception;
  }
}





void Message::getProperties(T::PropertySettingVec& properties)
{
  FUNCTION_TRACE
  try
  {
    if (mIndicatorSection)
      mIndicatorSection->getProperties(properties);

    if (mIdentificationSection)
      mIdentificationSection->getProperties(properties);

    if (mLocalSection)
      mLocalSection->getProperties(properties);

    if (mGridSection)
      mGridSection->getProperties(properties);

    if (mProductSection)
      mProductSection->getProperties(properties);

    if (mRepresentationSection)
      mRepresentationSection->getProperties(properties);

    if (mBitmapSection)
      mBitmapSection->getProperties(properties);

    if (mDataSection)
      mDataSection->getProperties(properties);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current message.
*/

void Message::getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const
{
  FUNCTION_TRACE
  try
  {
    char name[300];

    sprintf(name,"%smessage[%u].gribParameterId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGribParameterId()));

    sprintf(name,"%smessage[%u].gribParameterName",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getGribParameterName());

    sprintf(name,"%smessage[%u].fmiParameterId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getFmiParameterId()));

    sprintf(name,"%smessage[%u].fmiParameterLevelId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getFmiParameterLevelId()));

    sprintf(name,"%smessage[%u].fmiParameterName",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getFmiParameterName());

    sprintf(name,"%smessage[%u].fmiParameterUnits",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getFmiParameterUnits());

    sprintf(name,"%smessage[%u].newbaseParameterId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,std::to_string(mNewbaseParameterId));

    sprintf(name,"%smessage[%u].newbaseParameterName",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getNewbaseParameterName());

    sprintf(name,"%smessage[%u].parameterLevel",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridParameterLevel()));

    sprintf(name,"%smessage[%u].parameterLevelId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridParameterLevelId()));

    sprintf(name,"%smessage[%u].foracastTime",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getForecastTime());

    sprintf(name,"%smessage[%u].referenceTime",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getReferenceTime());

    sprintf(name,"%smessage[%u].gridGeometryId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridGeometryId()));

    sprintf(name,"%smessage[%u].gridType",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridProjection()));

    sprintf(name,"%smessage[%u].gridRows",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridRowCount()));

    sprintf(name,"%smessage[%u].gridColumns",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridColumnCount()));

    sprintf(name,"%smessage[%u].WKT",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getWKT());

    sprintf(name,"%smessage[%u].",prefix.c_str(),mMessageIndex);


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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool Message::getAttributeValue(const char *attributeName, std::string& attributeValue) const
{
  FUNCTION_TRACE
  try
  {
    if (mIndicatorSection)
    {
      if (mIndicatorSection->getAttributeValue(attributeName,attributeValue))
        return true;
    }

    if (mIdentificationSection)
    {
      if (mIdentificationSection->getAttributeValue(attributeName,attributeValue))
        return true;
    }

    if (mProductSection)
    {
      if (mProductSection->getAttributeValue(attributeName,attributeValue))
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



bool Message::hasAttributeValue(const char *attributeName, const char *attributeValue) const
{
  FUNCTION_TRACE
  try
  {
    if (mIndicatorSection)
    {
      if (mIndicatorSection->hasAttributeValue(attributeName,attributeValue))
        return true;
    }

    if (mIdentificationSection)
    {
      if (mIdentificationSection->hasAttributeValue(attributeName,attributeValue))
        return true;
    }

    if (mProductSection)
    {
      if (mProductSection->hasAttributeValue(attributeName,attributeValue))
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



T::FileType Message::getMessageType() const
{
  return T::FileTypeValue::Grib2;
}





void Message::getSectionPositions(std::set<T::FilePosition>& positions)
{
  FUNCTION_TRACE
  try
  {
    if (mIndicatorSection)
      positions.insert(mIndicatorSection->getFilePosition());

    if (mIdentificationSection)
      positions.insert(mIdentificationSection->getFilePosition());

    if (mLocalSection)
      positions.insert(mLocalSection->getFilePosition());

    if (mGridSection)
      positions.insert(mGridSection->getFilePosition());

    if (mProductSection)
      positions.insert(mProductSection->getFilePosition());

    if (mRepresentationSection)
      positions.insert(mRepresentationSection->getFilePosition());

    if (mBitmapSection)
      positions.insert(mBitmapSection->getFilePosition());

    if (mDataSection)
      positions.insert(mDataSection->getFilePosition());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method creates the IndicatorSection object if it does not exist. */

void Message::initIndicatorSection()
{
  FUNCTION_TRACE
  try
  {
    if (mIndicatorSection == nullptr)
    {
      IndicatorSection *section = new IndicatorSection();
      section->setMessagePtr(this);
      mIndicatorSection.reset(section);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method creates the IdentificationSection object if it does not exist. */

void Message::initIdentificationSection()
{
  FUNCTION_TRACE
  try
  {
    if (mIdentificationSection == nullptr)
    {
      IdentificationSection *section = new IdentificationSection();
      section->setMessagePtr(this);
      mIdentificationSection.reset(section);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method creates the LocalSection object if it does not exist. */

void Message::initLocalSection()
{
  FUNCTION_TRACE
  try
  {
    if (mLocalSection == nullptr)
    {
      LocalSection *section = new LocalSection();
      section->setMessagePtr(this);
      mLocalSection.reset(section);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method creates the GridSection object if it does not exist. */

void Message::initGridSection()
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
    {
      GridSection *section = new GridSection();
      section->setMessagePtr(this);
      mGridSection.reset(section);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method creates the ProductSection object if it does not exist. */

void Message::initProductSection()
{
  FUNCTION_TRACE
  try
  {
    if (mProductSection == nullptr)
    {
      ProductSection *section = new ProductSection();
      section->setMessagePtr(this);
      mProductSection.reset(section);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method creates the RepresentationSection object if it does not exist. */

void Message::initRepresentationSection()
{
  FUNCTION_TRACE
  try
  {
    if (mRepresentationSection == nullptr)
    {
      RepresentationSection *section = new RepresentationSection();
      section->setMessagePtr(this);
      mRepresentationSection.reset(section);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method creates the BitmapSection object if it does not exist. */

void Message::initBitmapSection()
{
  FUNCTION_TRACE
  try
  {
    if (mBitmapSection == nullptr)
    {
      BitmapSection *section = new BitmapSection();
      section->setMessagePtr(this);
      mBitmapSection.reset(section);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method creates the DataSection object if it does not exist. */

void Message::initDataSection()
{
  FUNCTION_TRACE
  try
  {
    if (mDataSection == nullptr)
    {
      DataSection *section = new DataSection();
      section->setMessagePtr(this);
      mDataSection.reset(section);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void Message::lockData()
{
  FUNCTION_TRACE
  try
  {
    if (mDataLocked)
      return;

    auto addr = getDataPtr();
    auto len = getDataSize();

    if (addr != nullptr &&  len > 0)
    {
      mlock(addr,len);
      mDataLocked = true;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void Message::unlockData()
{
  FUNCTION_TRACE
  try
  {
    if (!mDataLocked)
      return;

    auto addr = getDataPtr();
    auto len = getDataSize();

    if (addr != nullptr &&  len > 0)
    {
      munlock(addr,len);
      mDataLocked = false;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method set the grid geometry identifer.

   This identifier can be used for identifying different geometries. Usually geometry identifiers are defined
   in a configuration file and when a grid file read the geometry is automatically identified. However, there might
   be cases that the geometry cannot be automatically identified (because it is not defined in the configuration file).
   It is also possible that we might want to use our own geometry identifiers and this method allows us to set it
   in place.

        \param   The grid geometry identifier.
*/

void Message::setGridGeometryId(T::GeometryId geometryId)
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    mGridSection->setGridGeometryId(geometryId);

    mGeometryId = geometryId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting grid values. The basic assumption is that
    all necessary attributes/parameters (like dimensions, packing method, etc)
    are already initialized before calling this function.

        \param values  The vector of grid values.
*/

void Message::setGridValues(T::ParamValue_vec& values)
{
  FUNCTION_TRACE
  try
  {
    initRepresentationSection();

    uint size = values.size();

    uint cnt = size;
    for (uint t=0; t<size; t++)
    {
      if (values[t] == ParamValueMissing)
      {
        initBitmapSection();

        uint bmSize = size /  8 + 1;
        uchar *bm = new uchar[bmSize];

        BitArrayWriter bmWriter(bm,size);
        for (uint a=0; a<size; a++)
        {
          if (values[a] == ParamValueMissing)
          {
            bmWriter.writeBit(false);
            cnt--;
          }
          else
          {
            bmWriter.writeBit(true);
          }
        }

        mBitmapSection->setBitmapData(bm,bmSize);
        mBitmapSection->setBitMapIndicator(0);
        t = size;
      }
    }

    initDataSection();

    mRepresentationSection->encodeValues(this,values);
    mRepresentationSection->setNumberOfValues(cnt);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::isRead()
{
  try
  {
    return mIsRead;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





void Message::read()
{
  FUNCTION_TRACE
  try
  {
    if (mIsRead)
      return;

    if (mGridFilePtr == nullptr)
    {
      Fmi::Exception exception(BCP,"No pointer to the grid file!");
      throw exception;
    }

    long s = mGridFilePtr->getSize();
    uchar *d = (uchar*)mGridFilePtr->getMemoryPtr();
    uchar *e = d + s;

    MemoryReader memoryReader(d,e);
    memoryReader.setReadPosition(mFilePosition);
    read(memoryReader);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Message read failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    exception.addParameter("Message start position",uint64_toHex(mFilePosition));
    exception.addParameter("Message size",Fmi::to_string(mMessageSize));
    throw exception;
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
    AutoThreadLock lock(&mThreadLock);

    if (mIsRead)
      return;

    mFilePosition = memoryReader.getGlobalReadPosition();

    // Index of the section processed last (=none)
    std::uint8_t last_idx = 0u;
    bool begin = false;

    while (true)
    {
      auto prevPos = memoryReader.getReadPosition();
      if ((memoryReader.getReadPtr()+4) > memoryReader.getEndPtr())
      {
        // std::cout << CODE_LOCATION << ": Memory area end reached!\n";
        break;
      }

      if (!begin)
      {
        int spos = memoryReader.search_string("GRIB");
        if (spos >= 0)
        {
          memoryReader.setReadPosition(memoryReader.getReadPosition()+spos);
          IndicatorSection *section = new IndicatorSection();
          section->setMessagePtr(this);
          mIndicatorSection.reset(section);
          section->read(memoryReader);
          begin = true;
        }
      }
      else
      if (memoryReader.peek_string("7777"))
      {
        break;
      }
      else
      {
        std::uint8_t idx = memoryReader.getByte(memoryReader.getReadPosition() + 4);

        // A message ends if an earlier section is encountered
        if (idx < last_idx)
          break;

        if (idx == last_idx)
          throw Fmi::Exception(BCP,"Cannot repeat the same section twice (message '" + Fmi::to_string(mMessageIndex) + "')!");

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
              IdentificationSection *section = new IdentificationSection();
              section->setMessagePtr(this);
              mIdentificationSection.reset(section);
              auto p1 = memoryReader.getReadPosition();
              section->read(memoryReader);
              auto p2 = memoryReader.getReadPosition();
              auto len = section->getSectionLength();

              if (len > 0  &&  (p1+len) != p2)
                memoryReader.setReadPosition(p1+len);
            }
            break;

            case SectionNumber::local_section:
            {
              LocalSection *section = new LocalSection();
              section->setMessagePtr(this);
              mLocalSection.reset(section);
              auto p1 = memoryReader.getReadPosition();
              section->read(memoryReader);
              auto p2 = memoryReader.getReadPosition();
              auto len = section->getSectionLength();

              if (len > 0  &&  (p1+len) != p2)
                memoryReader.setReadPosition(p1+len);
            }
            break;

            case SectionNumber::grid_section:
            {
              GridSection *section = new GridSection();
              section->setMessagePtr(this);
              mGridSection.reset(section);
              auto p1 = memoryReader.getReadPosition();
              section->read(memoryReader);
              auto p2 = memoryReader.getReadPosition();
              auto len = section->getSectionLength();

              if (len > 0  &&  (p1+len) != p2)
                memoryReader.setReadPosition(p1+len);
            }
            break;

            case SectionNumber::product_section:
            {
              ProductSection *section = new ProductSection();
              section->setMessagePtr(this);
              mProductSection.reset(section);
              auto p1 = memoryReader.getReadPosition();
              section->read(memoryReader);
              auto p2 = memoryReader.getReadPosition();
              auto len = section->getSectionLength();

              if (len > 0  &&  (p1+len) != p2)
                memoryReader.setReadPosition(p1+len);
            }
            break;

            case SectionNumber::representation_section:
            {
              RepresentationSection *section = new RepresentationSection();
              section->setMessagePtr(this);
              mRepresentationSection.reset(section);
              auto p1 = memoryReader.getReadPosition();
              section->read(memoryReader);
              auto p2 = memoryReader.getReadPosition();
              auto len = section->getSectionLength();
            }
            break;

            case SectionNumber::bitmap_section:
            {
              BitmapSection *section = new BitmapSection();
              section->setMessagePtr(this);
              mBitmapSection.reset(section);
              auto p1 = memoryReader.getReadPosition();
              section->read(memoryReader);
              /*
              if (section->getBitmapDataSizeInBytes() > 0)
              {
                auto numOfValues = getGridOriginalValueCount();
                auto hash = section->getHash();
                T::IndexVector indexVector;
                if (!GRID::indexCache.findIndexVector(hash))
                {
                  section->getIndexVector(numOfValues,indexVector);
                  GRID::indexCache.addIndexVector(hash,indexVector);
                }
              }
              */

              auto p2 = memoryReader.getReadPosition();
              auto len = section->getSectionLength();

              if (len > 0  &&  (p1+len) != p2)
                memoryReader.setReadPosition(p1+len);
            }
            break;

            case SectionNumber::data_section:
            {
              DataSection *section = new DataSection();
              section->setMessagePtr(this);
              mDataSection.reset(section);
              auto p1 = memoryReader.getReadPosition();
              section->read(memoryReader);
              auto p2 = memoryReader.getReadPosition();
              auto len = section->getSectionLength();

              if (len > 0  &&  (p1+len) != p2)
                memoryReader.setReadPosition(p1+len);
            }
            break;

            default:
            {
              Fmi::Exception exception(BCP,"Invalid GRIB section number '" + Fmi::to_string(static_cast<int>(idx)) + "'!");
              exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()+4));
              throw exception;
             }
          }
        }
        catch (...)
        {
          Fmi::Exception exception(BCP,"Section creation failed!",nullptr);
          exception.addParameter("Section number",Fmi::to_string(static_cast<int>(idx)));
          exception.addParameter("Section start position",uint64_toHex(rPos));
          throw exception;
        }
      }

      if (prevPos == memoryReader.getReadPosition())
      {
        // No data read in this cycle. Ending the loop
        break;
      }

    }

    // All messages must define sections 4-7

    if (!mProductSection)
      throw Fmi::Exception(BCP,"The product section is missing!");

    if (!mRepresentationSection)
      throw Fmi::Exception(BCP,"The representation section is missing!");

    if (!mBitmapSection)
      throw Fmi::Exception(BCP,"The bitmap section is missing!");

    if (!mDataSection)
      throw Fmi::Exception(BCP,"The data section is missing!");

    if (mMessageSize == 0)
      mMessageSize = (memoryReader.getGlobalReadPosition() - mFilePosition);

    if (mIdentificationSection != nullptr &&  mProductSection != nullptr  &&  mForecastTimeT == 0)
    {
      std::string fTime = mProductSection->getForecastTime(mIdentificationSection->getReferenceTime());
      mForecastTimeT = utcTimeToTimeT(fTime);
    }

    mIsRead = true;
    mRowCount = getGridRowCount();
    mColumnCount = getGridColumnCount();
    setGridGeometryId(mGeometryId);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Message read failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    exception.addParameter("Message size",Fmi::to_string(mMessageSize));
    exception.addParameter("MessageReader read position",uint64_toHex(memoryReader.getReadPosition()));
    throw exception;
  }
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void Message::write(DataWriter& dataWriter)
{
  FUNCTION_TRACE
  try
  {
    if (mIndicatorSection)
      mIndicatorSection->write(dataWriter);

    if (mIdentificationSection)
      mIdentificationSection->write(dataWriter);

    if (mLocalSection)
      mLocalSection->write(dataWriter);

    if (mGridSection)
      mGridSection->write(dataWriter);

    if (mProductSection)
      mProductSection->write(dataWriter);

    if (mRepresentationSection)
      mRepresentationSection->write(dataWriter);

    if (mBitmapSection)
      mBitmapSection->write(dataWriter);

    if (mDataSection)
      mDataSection->write(dataWriter);

    dataWriter.write_nTimes('7',4);

    if (mIndicatorSection)
    {
      // ### Updating indicator section

      ulonglong fpos1 = mIndicatorSection->getFilePosition();
      ulonglong fpos2 = dataWriter.getWritePosition();
      mIndicatorSection->setTotalLength(fpos2-fpos1);
      dataWriter.setWritePosition(fpos1);
      mIndicatorSection->write(dataWriter);
      dataWriter.setWritePosition(fpos2);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the GRIB 2 centre identifer.

        \return   The GRIB 2 centre identifier.
*/

uint Message::getGribCentre() const
{
  FUNCTION_TRACE
  try
  {
    if (mIdentificationSection)
    {
      auto centre = mIdentificationSection->getCentre();
      if (centre)
        return *centre;
    }

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the GRIB version number.

        \return   The GRIB version number.
*/

uint Message::getGribVersion() const
{
  FUNCTION_TRACE
  try
  {
    return 2;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the GRIB 2 sub-centre identifer.

        \return   The GRIB 2 sub-centre identifier.
*/

uint Message::getGribSubCentre() const
{
  FUNCTION_TRACE
  try
  {
    if (mIdentificationSection)
    {
      auto centre = mIdentificationSection->getSubCentre();
      if (centre)
        return *centre;
    }

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the GRIB 2 generating process identifer.

        \return   The GRIB 2 generating process identifier.
*/

uint Message::getGribGeneratingProcessIdentifier() const
{
  FUNCTION_TRACE
  try
  {
    if (mProductSection)
      return *mProductSection->getGeneratingProcessIdentifier();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the GRIB 2 table identifer.

        \return   The GRIB 2 table identifier.
*/

uint Message::getGribTableVersion() const
{
  FUNCTION_TRACE
  try
  {
    if (mIdentificationSection)
      return *mIdentificationSection->getTablesVersion();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method tries to find an unique parameterId for the grid content. */

void Message::initParameterInfo()
{
  FUNCTION_TRACE
  try
  {
    if (mFmiParameterId != 0)
    {
      // We have fmi-id, which means that we can use parameter mappings;

      Identification::Grib2ParameterDef def;
      if (Identification::gridDef.getGrib2ParameterDefByFmiId(mFmiParameterId,def))
        mGribParameterId = def.mGribParameterId;
    }

    if (mGribParameterId == 0)
      mGribParameterId = Identification::gridDef.getGribParameterId(*this);

    if (mGribParameterId != 0)
    {
      Identification::GribParameterDef def;
      if (Identification::gridDef.getGribParameterDefById(mGribParameterId,def))
      {
        mGribParameterName = stringFactory.create(def.mParameterName);
        mGribParameterUnits  = stringFactory.create(def.mParameterUnits);
      }

      if (mFmiParameterId == 0)
      {
        Identification::FmiParameterDef def;
        if (Identification::gridDef.getFmiParameterDefByGribId(mGribParameterId,def))
        {
          mFmiParameterId = def.mFmiParameterId;
        }
      }
    }

    if (mFmiParameterId != 0)
    {
      Identification::FmiParameterDef def;
      if (Identification::gridDef.getFmiParameterDefById(mFmiParameterId,def))
      {
        mFmiParameterName = stringFactory.create(def.mParameterName);
        mFmiParameterUnits = stringFactory.create(def.mParameterUnits);
        mDefaultInterpolationMethod = def.mAreaInterpolationMethod;
      }
      mFmiParameterLevelId = Identification::gridDef.getFmiLevelId(*this);

      mNewbaseParameterId = Identification::gridDef.getNewbaseParameterId(*this);
      mNewbaseParameterName = stringFactory.create(Identification::gridDef.getNewbaseParameterName(*this));

      mNetCdfParameterName = stringFactory.create(Identification::gridDef.getNetCdfParameterName(*this));
    }

    if (getGridGeometryId() == 0)
    {
      int geometryId = Identification::gridDef.getGrib2GeometryId(*this);
      if (geometryId != 0)
      {
        setGridGeometryId(geometryId);
      }
      else
      {
        std::cout << "\n** GRIB2 Geometry not configured : " << mGridFilePtr->getFileName() << "\n";
        std::cout << "** Add the following line into the geometry definition file (=> fill id,name and description fields) :\n\n";
        std::cout << getGridGeometryLine() << "\n\n";
          //Fmi::Exception exception(BCP,"Geometry not found");
          //throw exception;
      }
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method sets the shared pointer of the BitmapSection object.

        \param bitmapSection  The shared pointer of the section object.
*/

void Message::setBitmapSection(BitmapSect_sptr bitmapSection)
{
  FUNCTION_TRACE
  try
  {
    mBitmapSection = bitmapSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the pointer of the BitmapSection object.

        \param bitmapSection  The pointer of the section object.
*/

void Message::setBitmapSection(BitmapSection *bitmapSection)
{
  FUNCTION_TRACE
  try
  {
    if (bitmapSection == nullptr)
      throw Fmi::Exception(BCP,"The 'bitmapSection' parameter points to nullptr!");

    bitmapSection->setMessagePtr(this);
    mBitmapSection.reset(bitmapSection);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the shared pointer of the IdentificationSection object.

        \param identifcationSection   The shared pointer of the section object.
*/

void Message::setIdentificationSection(IdentifSect_sptr identificationSection)
{
  FUNCTION_TRACE
  try
  {
    mIdentificationSection = identificationSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the pointer of the IdentificationSection object.

        \param identifcationSection   The pointer of the section object.
*/

void Message::setIdentificationSection(IdentificationSection *identificationSection)
{
  FUNCTION_TRACE
  try
  {
    if (identificationSection == nullptr)
      throw Fmi::Exception(BCP,"The 'identificationSection' parameter points to nullptr!");

    identificationSection->setMessagePtr(this);
    mIdentificationSection.reset(identificationSection);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the shared pointer of the GridSection object.

        \param gridSection   The shared pointer of the section object.
*/

void Message::setGridSection(GridSect_sptr gridSection)
{
  FUNCTION_TRACE
  try
  {
    mGridSection = gridSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the pointer of the GridSection object.

        \param gridSection   The pointer of the section object.
*/

void Message::setGridSection(GridSection *gridSection)
{
  FUNCTION_TRACE
  try
  {
    if (gridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'bitmapSection' parameter points to nullptr!");

    gridSection->setMessagePtr(this);
    mGridSection.reset(gridSection);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the shared pointer of the RepresentationSection object.

        \param representationSection   The shared pointer of the section object.
*/

void Message::setRepresentationSection(RepresentSect_sptr representationSection)
{
  FUNCTION_TRACE
  try
  {
    mRepresentationSection = representationSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the pointer of the RepresentationSection object.

        \param representationSection   The pointer of the section object.
*/

void Message::setRepresentationSection(RepresentationSection *representationSection)
{
  FUNCTION_TRACE
  try
  {
    if (representationSection == nullptr)
      throw Fmi::Exception(BCP,"The 'representationSection' parameter points to nullptr!");

    representationSection->setMessagePtr(this);
    mRepresentationSection.reset(representationSection);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the shared pointer of the IndicatorSection object.

        \param indicatorSection   The shared pointer of the section object.
*/

void Message::setIndicatorSection(IndicatorSect_sptr indicatorSection)
{
  FUNCTION_TRACE
  try
  {
    mIndicatorSection = indicatorSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the pointer of the IndicatorSection object.

        \param indicatorSection   The pointer of the section object.
*/

void Message::setIndicatorSection(IndicatorSection *indicatorSection)
{
  FUNCTION_TRACE
  try
  {
    if (indicatorSection == nullptr)
      throw Fmi::Exception(BCP,"The 'indicatorSection' parameter points to nullptr!");

    indicatorSection->setMessagePtr(this);
    mIndicatorSection.reset(indicatorSection);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the shared pointer of the LocalSection object.

        \param localSection   The shared pointer of the section object.
*/

void Message::setLocalSection(LocalSect_sptr localSection)
{
  FUNCTION_TRACE
  try
  {
    mLocalSection = localSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the pointer of the LocalSection object.

        \param localSection   The pointer of the section object.
*/

void Message::setLocalSection(LocalSection *localSection)
{
  FUNCTION_TRACE
  try
  {
    if (localSection == nullptr)
      throw Fmi::Exception(BCP,"The 'localSection' parameter points to nullptr!");

    localSection->setMessagePtr(this);
    mLocalSection.reset(localSection);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the shared pointer of the ProductSection object.

        \param productSection   The shared pointer of the section object.
*/

void Message::setProductSection(ProductSect_sptr productSection)
{
  FUNCTION_TRACE
  try
  {
    mProductSection = productSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the pointer of the ProductSection object.

        \param productSection   The pointer of the section object.
*/

void Message::setProductSection(ProductSection *productSection)
{
  FUNCTION_TRACE
  try
  {
    if (productSection == nullptr)
      throw Fmi::Exception(BCP,"The 'productSection' parameter points to nullptr!");

    productSection->setMessagePtr(this);
    mProductSection.reset(productSection);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the shared pointer of the DataSection object.

        \param dataSection   The shared pointer of the section object.
*/

void Message::setDataSection(DataSect_sptr dataSection)
{
  FUNCTION_TRACE
  try
  {
    mDataSection = dataSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the pointer of the DataSection object.

        \param dataSection   The pointer of the section object.
*/

void Message::setDataSection(DataSection *dataSection)
{
  FUNCTION_TRACE
  try
  {
    if (dataSection == nullptr)
      throw Fmi::Exception(BCP,"The 'dataSection' parameter points to nullptr!");

    dataSection->setMessagePtr(this);
    mDataSection.reset(dataSection);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Set the previous bitmap section to be used instead if necessary.

        \param previousBitmapSection   The shared pointer of the section object.
 */

void Message::setPreviousBitmapSection(BitmapSect_sptr previousBitmapSection)
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid hash value.

        \return   The grid hash value.
*/

T::Hash Message::getGridHash() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != nullptr)
      return mGridSection->getGridHash();

    return 0;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid geometry identifer.

        \return   The grid geometry identifier.
*/

T::GeometryId Message::getGridGeometryId() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != nullptr)
    {
      T::GeometryId gid = mGridSection->getGridGeometryId();
      if (gid != 0)
        return gid;
    }

    return mGeometryId;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





void Message::getGridCellAverageSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    width = 0;
    height = 0;
    if (mGridSection != nullptr)
      mGridSection->getGridCellAverageSize(width,height);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridMetricCellSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != nullptr)
      return mGridSection->getGridMetricCellSize(width,height);

    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridMetricSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != nullptr)
      return mGridSection->getGridMetricSize(width,height);

    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != nullptr)
      return mGridSection->getGridMetricArea(topLeft,topRight,bottomLeft,bottomRight);

    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != nullptr)
      return mGridSection->getGridLatLonArea(topLeft,topRight,bottomLeft,bottomRight);

    return false;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}




/*! \brief The method returns the grid geometry string. This string can be used for comparing
    geometries in different grid files. For example, is is possible that a GRIB 1 message has
    the same geometry string as a GRIB 2 message, which means that they have same geometries.
    This comparison is more reliable than the hash comparison.

        \return   The grid geometry string.
*/

std::string Message::getGridGeometryString() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != nullptr)
      return mGridSection->getGridGeometryString();

    std::string str;
    return str;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns. In this case we can find out the grid
    dimensions by using the "getGridRowCount()" and "getGridColumnCount()"
    methods.

        \return   The grid dimensions.
*/

T::Dimensions Message::getGridDimensions() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridDimensions();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid latlon coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return   The method return true if the latlon values were succesfully returned.
*/

bool Message::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridLatLonCoordinatesByGridPoint(grid_i,grid_j,lat,lon);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid latlon coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

bool Message::getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridLatLonCoordinatesByGridPosition(grid_i,grid_j,lat,lon);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid latlon coordinates according the grid original (projection) coordinates.

        \param x       The x-coordinate in the original projection.
        \param y       The y-coordinate in the original projection.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

bool Message::getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridLatLonCoordinatesByOriginalCoordinates(x,y,lat,lon);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool Message::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalCoordinatesByGridPoint(grid_i,grid_j,x,y);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool Message::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalCoordinatesByGridPosition(grid_i,grid_j,x,y);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

        \return   The grid coordinates.
*/

T::Coordinate_svec Message::getGridOriginalCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalCoordinates();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns all grid coordinates as a latlon coordinate vector. If the grid
    original coordiantes were not latlon coordinates then the original coordinates are converted
    to the latlon coordinates.

        \return   The grid latlon coordinates.
*/

T::Coordinate_svec Message::getGridLatLonCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridLatLonCoordinates();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid original (projection) coordinates by the given latlon position.

        \param lat  The latitude value.
        \param lon  The longitude value.
        \param x    The x-coordinate in the original projection is returned in this parameter.
        \param y    The y-coordinate in the original projection is returned in this parameter.
        \return     The method return true if the original coordinates were succesfully returned.
*/

bool Message::getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalCoordinatesByLatLonCoordinates(lat,lon,x,y);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns a list of grid projection attributes.

        \param prefix         The prefix that is added in the front of each attribute name.
        \param attributeList  The projection attributes are returned in this parameter.
*/

void Message::getGridProjectionAttributes(const std::string& prefix,T::AttributeList& attributeList) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    mGridSection->getAttributeList(prefix,attributeList);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the file identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid file identifier.
*/

uint Message::getFileId() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridFilePtr != nullptr)
      return mGridFilePtr->getFileId();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the producer identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid producer identifier.
*/

uint Message::getProducerId() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridFilePtr != nullptr)
      return mGridFilePtr->getProducerId();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the generation identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid generation identifier.
*/

uint Message::getGenerationId() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridFilePtr != nullptr)
      return mGridFilePtr->getGenerationId();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns a shared pointer to the BitmapSection object. */

BitmapSect_sptr Message::getBitmapSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mBitmapSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns a shared pointer to the previous BitmapSection object. */

BitmapSect_sptr Message::getPreviousBitmapSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mPreviousBitmapSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns a shared pointer to the GridSection object. */

GridSect_sptr Message::getGridSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mGridSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns a pointer to the RepresentationSection object. */

RepresentSect_sptr Message::getRepresentationSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mRepresentationSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns a shared pointer to the IdentificationSection object. */

IdentifSect_sptr Message::getIdentificationSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mIdentificationSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns a shared pointer to the IndicatorSection object. */

IndicatorSect_sptr Message::getIndicatorSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mIndicatorSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns a shared pointer to the LocalSection object. */

LocalSect_sptr Message::getLocalSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mLocalSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns a pointer to the ProductSection object. */

ProductSect_sptr Message::getProductSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mProductSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns a pointer to the DataSection object. */

DataSect_sptr Message::getDataSection() const
{
  // FUNCTION_TRACE
  try
  {
    return mDataSection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    if (mCacheKey != 0  &&  GRID::valueCache.getMinAndMaxValues(mCacheKey,minValue,maxValue))
      return;

    T::ParamValue_vec values;
    getGridValueVector(values);

    minValue = 1000000000;
    maxValue = -1000000000;

    for (auto it = values.begin(); it != values.end(); ++it)
    {
      if (*it != ParamValueMissing)
      {
        if (*it < minValue)
          minValue = *it;

        if (*it > maxValue)
          maxValue = *it;
      }
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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
    if (mRepresentationSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mRepresentationSection' attribute points to nullptr!");

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
      premap();
      mRepresentationSection->decodeValues(values);

      if (mRepresentationSection->getDataRepresentationTemplateNumber() != RepresentationSection::Template::GridDataRepresentation || (mBitmapSection != nullptr  &&  mBitmapSection->getBitmapDataSizeInBytes() > 0))
        mCacheKey = GRID::valueCache.addValues(values);
    }
    catch (...)
    {
      Fmi::Exception exception(BCP,"Operation failed!",nullptr);
      exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
      exception.addParameter("Filename",mGridFilePtr->getFileName());
      exception.printError();
      mValueDecodingFailed = true;
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the original grid data values.

   If the grid is regular then the 'getGridValueVector()' method returns the same
    result as this method. However, if the grid is irregular then the grid rows
    might contain different number of columns. In this case the data should be
    processed row-by-row and the 'getGridColumnCount()' method should be
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
    if (mRepresentationSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mRepresentationSection' attribute points to nullptr!");

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
      premap();
      mRepresentationSection->decodeValues(values);
      mCacheKey = GRID::valueCache.addValues(values);
      mOrigCacheKey = mCacheKey;
    }
    catch (...)
    {
      Fmi::Exception exception(BCP,"Operation failed!",nullptr);
      exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
      exception.printError();
      mValueDecodingFailed = true;
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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
    if (mGridSection != nullptr)
      return mGridSection->getWKT();

    std::string wkt;
    T::SpatialRef *sr = getSpatialReference();
    if (sr != nullptr)
    {
      char *out = nullptr;
      sr->exportToWkt(&out);
      wkt = out;
      CPLFree(out);
    }
    return wkt;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





std::string Message::getProj4() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != nullptr)
      return mGridSection->getProj4();

    std::string proj4;
    T::SpatialRef *sr = getSpatialReference();
    if (sr != nullptr)
    {
      char *out = nullptr;
      sr->exportToProj4(&out);
      proj4 = out;
      CPLFree(out);
    }
    return proj4;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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
    if (mProductSection)
      return mProductSection->getGribParameterLevel();

    return mParameterLevel;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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
    if (mProductSection)
      return mProductSection->getGribParameterLevelId();

    return 0;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the forecast type of the current grid.

        \return   The forecast type.
*/

short Message::getForecastType() const
{
  FUNCTION_TRACE
  try
  {
    /*
    if (mProductSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mProductSection' attribute points to nullptr!");

    short ft = mProductSection->getForecastType();
    if (ft > 0)
      return ft;
    */

    if (mIdentificationSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mIdentificationSection' attribute points to nullptr!");

    T::UInt8_opt pd = mIdentificationSection->getTypeOfProcessedData();
    switch (*pd)
    {
      //case 0: // Analysis products
      //case 1: // Forecast products
      //case 2: // Analysis and forecast products

      case 3: // Control forecast products
        return 4;

      case 4: // Perturbed forecast products
        return 3;

      //case 5: // Control and perturbed forecast products
      //case 6: // Processed satellite observations
      //case 7: // Processed radar observations
      //case 8: // Event probability
    }

    return 0;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the forecast number of the current grid.

        \return   The forecast number.
*/

short Message::getForecastNumber() const
{
  FUNCTION_TRACE
  try
  {
    if (mProductSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mProductSection' attribute points to nullptr!");

    return mProductSection->getForecastNumber();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the reference time of the current grid. The forecast
    times are calculated from this.

        \return   The reference time of the current grid.
*/

T::TimeString Message::getReferenceTime() const
{
  FUNCTION_TRACE
  try
  {
    if (mIdentificationSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mIdentificationSection' attribute points to nullptr!");

    return mIdentificationSection->getReferenceTime();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the forecast time of the current grid.

        \return   The forecast time.
*/

T::TimeString Message::getForecastTime() const
{
  FUNCTION_TRACE
  try
  {
    return utcTimeFromTimeT(mForecastTimeT);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the forecast time of the current grid.

        \return   The forecast time.
*/

time_t Message::getForecastTimeT() const
{
  FUNCTION_TRACE
  try
  {
    return mForecastTimeT;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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
    if (mValueDecodingFailed)
    {
      // We have failed to decode parameter values
      return ParamValueMissing;
    }

    if (grid_j >= mRowCount)
      return ParamValueMissing;

    if (grid_i >= mColumnCount &&  !isGridGlobal())
      return ParamValueMissing;

    uint idx = grid_j * mColumnCount + (grid_i % mColumnCount);

    // Trying to find the value from the point cache.

    T::ParamValue value = 0;
    if (mBitmapSection == nullptr  ||  mBitmapSection->getBitmapDataSizeInBytes() == 0)
    {
      if (mRepresentationSection->getDataRepresentationTemplateNumber() == RepresentationSection::Template::GridDataRepresentation)
      {
        mRequestCounter++;
        if (!mPremapped  &&  memoryMapper.isPremapEnabled())
          premap();

        if (mRepresentationSection->getValueByIndex(idx,value))
        {
          return value;
        }
      }
    }
    /*
    else
    {
      if (mRepresentationSection->getDataRepresentationTemplateNumber() == RepresentationSection::Template::GridDataRepresentation)
      {
        auto hash = mBitmapSection->getHash();
        int newidx = 0;
        if (GRID::indexCache.getIndex(hash,idx,newidx) &&  newidx >= 0)
        {
          if (mRepresentationSection->getValueByIndex(newidx,value))
            return value;
          else
            return ParamValueMissing;
        }
      }
    }
    */
    if (mCacheKey > 0)
    {
      // Trying to get a memory cache value.

      if (GRID::valueCache.getValue(mCacheKey,idx,value))
      {
        return value;
      }
    }

    T::ParamValue_vec values;
    getGridValueVector(values);
    if (idx >= values.size())
      return ParamValueMissing;

    return values[idx];
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





void Message::getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const
{
  {
    FUNCTION_TRACE
    try
    {
      if (mGridSection == nullptr)
        throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

      return mGridSection->getGridPointListByLatLonCoordinates(latlon,points);
    }
    catch (...)
    {
      Fmi::Exception exception(BCP,"Operation failed!",nullptr);
      exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
      throw exception;
    }
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
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridPointByLatLonCoordinatesNoCache(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridPointByOriginalCoordinates(x,y,grid_i,grid_j);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief This method can be used for finding out the grid projection type (Mercator, LatLon, PolarStereographic, etc.).

        \return   The type of the grid projection (expressed as an enum value).
*/

T::GridProjection Message::getGridProjection() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridProjection();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the number of rows used in the grid.

        \return   The number of the grid rows.
*/

std::size_t Message::getGridRowCount() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridRowCount();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the number of columns used in the grid.

        \return       The number of columns in the given grid row.
*/

std::size_t Message::getGridColumnCount() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridColumnCount();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalValueCount();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalValueIndex(grid_i,grid_j);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void Message::initSpatialReference()
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != nullptr)
      mGridSection->initSpatialReference();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the pointer to the spatial reference of the current grid.

        \return   The pointer to the spatial reference.
*/

T::SpatialRef* Message::getSpatialReference() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != nullptr)
      return mGridSection->getSpatialReference();

    return nullptr;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->isGridGlobal();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::isRelativeUV() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->isRelativeUV();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns 'true' if the grid horizontal values are in the reverse order.

        \return   The method returns 'true' if the grid horizontal values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool Message::reverseXDirection() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->reverseXDirection();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool Message::reverseYDirection() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw Fmi::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->reverseYDirection();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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

    return nullptr;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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

    return nullptr;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
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
    stream << space(level) << "- fileType                 = " << toString(mFileType) << "\n";
    stream << space(level) << "- referenceTime            = " << getReferenceTime() << "\n";
    stream << space(level) << "- forecastTime             = " << getForecastTime() << "\n";
    stream << space(level) << "- gridProjection           = " << T::get_gridProjectionString(getGridProjection()) << "\n";
    stream << space(level) << "- gridGeometryId           = " << getGridGeometryId() << "\n";
    stream << space(level) << "- gridRowCount             = " << toString(getGridRowCount()) << "\n";
    stream << space(level) << "- gridColumnCount          = " << toString(getGridColumnCount()) << "\n";

    stream << space(level) << "- fmiParameterId           = " << toString(mFmiParameterId) << "\n";
    stream << space(level) << "- fmiParameterName         = " << getFmiParameterName() << "\n";
    stream << space(level) << "- fmiParameterUnits        = " << getFmiParameterUnits() << "\n";
    stream << space(level) << "- fmiParameterLevelId      = " << toString(mFmiParameterLevelId) << "\n";
    stream << space(level) << "- parameterLevel           = " << toString(getGridParameterLevel()) << "\n";

    stream << space(level) << "- gribParameterId          = " << toString(mGribParameterId) << "\n";
    if (mGribParameterId != 0)
    {
      Identification::GribParameterDef def;
      if (Identification::gridDef.getGribParameterDefById(mGribParameterId,def))
      {
        stream << space(level) << "- gribParameterName        = " << def.mParameterName << "\n";
        stream << space(level) << "- gribParameterUnits       = " << def.mParameterUnits << "\n";
        stream << space(level) << "- gribParameterDescription = " << def.mParameterDescription << "\n";
      }
    }

    stream << space(level) << "- newbaseParameterId       = " << mNewbaseParameterId << "\n";
    stream << space(level) << "- newbaseParameterName     = " << getNewbaseParameterName() << "\n";

    stream << space(level) << "- netCdfParameterName      = " << getNetCdfParameterName() << "\n";

    stream << space(level) << "- gridHash                 = " << getGridHash() << "\n";
    stream << space(level) << "- WKT                      = " << getWKT() << "\n";

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
      T::Data_ptr bitmap = nullptr;
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
        auto d = mGridSection->getGridDimensions();
        if (d.getDimensions() == 2)
        {
          uint ny = d.ny();
          uint nx = d.nx();

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
        auto d = mGridSection->getGridDimensions();
        d.print(stream,0,0);
        if (d.getDimensions() == 2)
        {
          T::ParamValue_vec values;
          mRepresentationSection->decodeValues(values);

          stream << space(level+1) << "- data (from the grid corners):\n";

          char st[1000];
          uint c = 0;
          uint ny = d.ny();
          uint nx = d.nx();
          std::size_t sz = values.size();

          for (uint y=0; y < ny; y++)
          {
            for (uint x=0; x < nx; x++)
            {
              if (c < sz  &&  (y < 3  ||  y >= ny-3)  &&  (x < 3  ||  x >= nx-3))
              {
                auto val = values[c];
                if (val != ParamValueMissing)
                  sprintf(st,"[%u,%u] %f",y+1,x+1,val);
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
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.printError();
    exception.addParameter("Message index",Fmi::to_string(mMessageIndex));
    throw exception;
  }
}


}  // namespace GRIB2
}  // namespace SmartMet

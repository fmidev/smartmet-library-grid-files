#include "Message.h"
#include "GribFile.h"
#include "BitmapSection.h"
#include "DataSection.h"
#include "../common/Dimensions.h"
#include "../grid/PrintOptions.h"
#include "GridSection.h"
#include "IndicatorSection.h"
#include "ProductSection.h"
#include "../common/Exception.h"
#include "../common/AutoThreadLock.h"
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"
#include "../common/BitArrayWriter.h"
#include "../identification/GridDef.h"
#include "../grid/ValueCache.h"
#include "../grid/IndexCache.h"
#include "../common/ShowFunction.h"
#include <iostream>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF

namespace SmartMet
{
namespace GRIB1
{



/*! \brief The constructor of the class. */

Message::Message()
{
  FUNCTION_TRACE
  try
  {
    mGribFile = nullptr;
    mFilePosition = 0;
    mMessageSize = 0;
    mGrib1ParameterLevelId = 0;
    mGrib2ParameterLevelId = 0;
    mFmiParameterLevelId = 0;
    mCacheKey = 0;
    mOrigCacheKey = 0;
    mValueDecodingFailed = false;
    mPointCacheEnabled = false;
    mIsRead = false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Message::Message(GribFile *gribFile,uint messageIndex,ulonglong position,ulong size)
{
  FUNCTION_TRACE
  try
  {
    mGribFile = gribFile;
    mMessageIndex = messageIndex;
    mFilePosition = position;
    mMessageSize = size;
    mGrib1ParameterLevelId = 0;
    mGrib2ParameterLevelId = 0;
    mFmiParameterLevelId = 0;
    mCacheKey = 0;
    mOrigCacheKey = 0;
    mValueDecodingFailed = false;
    mPointCacheEnabled = false;
    mIsRead = false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The copy-constructor of the class. */

Message::Message(const Message& other)
:GRID::Message(other)
{
  FUNCTION_TRACE
  try
  {
    mGribFile = nullptr;
    mIsRead = true;
    mFilePosition = other.mFilePosition;
    mMessageSize = other.mMessageSize;

    if (other.mIndicatorSection)
    {
      mIndicatorSection.reset(new IndicatorSection(*(other.mIndicatorSection.get())));
      mIndicatorSection->setMessagePtr(this);
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


    mCacheKey = 0;
    mOrigCacheKey = 0;
    mPointCacheEnabled = false;
    mValueDecodingFailed = other.mValueDecodingFailed;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




/*! \brief The destructor of the class. */

Message::~Message()
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
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

    sprintf(name,"%smessage[%u].fmiProducerName",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(mFmiProducerName));

    sprintf(name,"%smessage[%u].gribParameterId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGribParameterId()));

    sprintf(name,"%smessage[%u].grib1ParameterLevelId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGrib1ParameterLevelId()));

    sprintf(name,"%smessage[%u].grib2ParameterLevelId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGrib2ParameterLevelId()));

    sprintf(name,"%smessage[%u].gribParameterName",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,mGribParameterName);

    sprintf(name,"%smessage[%u].gribParameterUnits",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,mGribParameterUnits);

    sprintf(name,"%smessage[%u].fmiParameterId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(mFmiParameterId));

    sprintf(name,"%smessage[%u].fmiParameterLevelId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(mFmiParameterLevelId));

    sprintf(name,"%smessage[%u].fmiParameterName",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,mFmiParameterName);

    sprintf(name,"%smessage[%u].fmiParameterUnits",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,mFmiParameterUnits);

    sprintf(name,"%smessage[%u].newbaseParameterId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(mNewbaseParameterId));

    sprintf(name,"%smessage[%u].newbaseParameterName",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(mNewbaseParameterName));

    sprintf(name,"%smessage[%u].cdmParameterId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,mCdmParameterId);

    sprintf(name,"%smessage[%u].cdmParameterName",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,mCdmParameterName);

    sprintf(name,"%smessage[%u].parameterLevel",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridParameterLevel()));

    sprintf(name,"%smessage[%u].parameterLevelId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridParameterLevelId()));

    sprintf(name,"%smessage[%u].parameterLevelIdString",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getGridParameterLevelIdString());

    sprintf(name,"%smessage[%u].foracastTime",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getForecastTime());

    //sprintf(name,"%smessage[%u].referenceTime",prefix.c_str(),mMessageIndex);
    //attributeList.addAttribute(name,getReferenceTime());

    sprintf(name,"%smessage[%u].gridGeometryId",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridGeometryId()));

    sprintf(name,"%smessage[%u].gridType",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridProjection()));

    sprintf(name,"%smessage[%u].gridTypeString",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getGridProjectionString());

    sprintf(name,"%smessage[%u].gridLayout",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridLayout()));

    sprintf(name,"%smessage[%u].gridLayoutString",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,T::get_gridLayoutString(getGridLayout()));

    sprintf(name,"%smessage[%u].gridRows",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridOriginalRowCount()));

    sprintf(name,"%smessage[%u].gridColumns",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,toString(getGridOriginalColumnCount()));

    sprintf(name,"%smessage[%u].WKT",prefix.c_str(),mMessageIndex);
    attributeList.addAttribute(name,getWKT());


    sprintf(name,"%smessage[%u].",prefix.c_str(),mMessageIndex);

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method sets the GribFile pointer for the current message object. This allows
     the message object to access information in the current grib file.

        \param gribFile  The pointer to the GribFile object.
*/

void Message::setGribFilePtr(GribFile *gribFile)
{
  FUNCTION_TRACE
  try
  {
    mGribFile = gribFile;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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

    if (mGribFile == nullptr)
      SmartMet::Spine::Exception exception(BCP,"No pointer to the grib file!");

    long long s = mGribFile->getSize();
    uchar *d = (uchar*)mGribFile->getMemoryPtr();
    uchar *e = d + s;

    MemoryReader memoryReader(d,e);
    memoryReader.setReadPosition(mFilePosition);
    read(memoryReader);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Message read failed!",nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    exception.addParameter("Message start position",uint64_toHex(mFilePosition));
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

    auto rPos = memoryReader.getGlobalReadPosition();
    try
    {
      IndicatorSection *section = new IndicatorSection();
      section->setMessagePtr(this);
      mIndicatorSection.reset(section);
      section->read(memoryReader);
    }
    catch (...)
    {
      SmartMet::Spine::Exception exception(BCP,"Indicator section creation failed!",nullptr);
      exception.addParameter("Section start position",uint64_toHex(rPos));
      throw exception;
    }

    rPos = memoryReader.getGlobalReadPosition();
    try
    {
      ProductSection *section = new ProductSection();
      section->setMessagePtr(this);
      mProductSection.reset(section);
      section->read(memoryReader);
    }
    catch (...)
    {
      SmartMet::Spine::Exception exception(BCP,"Product section creation failed!",nullptr);
      exception.addParameter("Section start position",uint64_toHex(rPos));
      throw exception;
    }

    if (mProductSection->getSectionFlags() & 0x80)
    {
      rPos = memoryReader.getGlobalReadPosition();
      try
      {
        GridSection *section = new GridSection();
        section->setMessagePtr(this);
        mGridSection.reset(section);
        section->read(memoryReader);
      }
      catch (...)
      {
        SmartMet::Spine::Exception exception(BCP,"Grid section creation failed!",nullptr);
        exception.addParameter("Section start position",uint64_toHex(rPos));
        throw exception;
      }
    }

    if (mProductSection->getSectionFlags() & 0x40)
    {
      rPos = memoryReader.getGlobalReadPosition();
      try
      {
        BitmapSection *section = new BitmapSection();
        section->setMessagePtr(this);
        mBitmapSection.reset(section);
        section->read(memoryReader);
      }
      catch (...)
      {
        SmartMet::Spine::Exception exception(BCP,"Bitmap section creation failed!",nullptr);
        exception.addParameter("Section start position",uint64_toHex(rPos));
        throw exception;
      }
    }

    rPos = memoryReader.getGlobalReadPosition();
    try
    {
      DataSection *section = new DataSection();
      section->setMessagePtr(this);
      mDataSection.reset(section);
      section->read(memoryReader);
    }
    catch (...)
    {
      SmartMet::Spine::Exception exception(BCP,"Data section creation failed!",nullptr);
      exception.addParameter("Section start position",uint64_toHex(rPos));
      throw exception;
    }

    mGribParameterId = Identification::gridDef.getGribParameterId(*this);
    mGribParameterName = Identification::gridDef.getGribParameterName(*this);
    mGribParameterUnits = Identification::gridDef.getGribParameterUnits(*this);
    mGrib1ParameterLevelId = Identification::gridDef.getGrib1LevelId(*this);

    mGrib2ParameterLevelId = Identification::gridDef.getGrib2LevelId(*this);

    //mFmiProducerName = Identification::gridDef.mMessageIdentifier_fmi.getProducerName(*this);

    mFmiParameterId = Identification::gridDef.getFmiParameterId(*this);
    mFmiParameterName = Identification::gridDef.getFmiParameterName(*this);
    mFmiParameterUnits = Identification::gridDef.getFmiParameterUnits(*this);
    mFmiParameterLevelId = Identification::gridDef.getFmiLevelId(*this);

    mNewbaseParameterId = Identification::gridDef.getNewbaseParameterId(*this);
    mNewbaseParameterName = Identification::gridDef.getNewbaseParameterName(*this);

    mCdmParameterId = Identification::gridDef.getCdmParameterId(*this);
    mCdmParameterName = Identification::gridDef.getCdmParameterName(*this);

    mDefaultInterpolationMethod = Identification::gridDef.getFmiParameterInterpolationMethod(*this);

    if (getGridGeometryId() == 0)
    {
      int geometryId = Identification::gridDef.getGrib1GeometryId(*this);
      if (geometryId != 0)
      {
        setGridGeometryId(geometryId);
      }
      else
      {
        std::cout << "\n** GRIB1 Geometry not configured : " << mGribFile->getFileName() << "\n";
        std::cout << "** Add the following line into the geometry definition file (=> fill id,name and desciption fields) :\n\n";
        std::cout << getGridGeometryString() << "\n\n";
      }
    }

    if (mMessageSize == 0)
      mMessageSize = (memoryReader.getGlobalReadPosition() - mFilePosition);

    mIsRead = true;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    exception.addParameter("Message start position",uint64_toHex(memoryReader.getStartPtr()-memoryReader.getParentPtr()));
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
    if (!mIndicatorSection)
      throw SmartMet::Spine::Exception(BCP,"The indicator section is missing!");

    if (!mProductSection)
      throw SmartMet::Spine::Exception(BCP,"The product section is missing!");

    if (!mGridSection)
      throw SmartMet::Spine::Exception(BCP,"The grid section is missing!");

    if (!mDataSection)
      throw SmartMet::Spine::Exception(BCP,"The data section is missing!");


    mFilePosition = dataWriter.getWritePosition();

    mIndicatorSection->write(dataWriter);
    mProductSection->write(dataWriter);
    mGridSection->write(dataWriter);

    if (mBitmapSection)
      mBitmapSection->write(dataWriter);  // ToDo: Set product section flags 0x40 to indicate that the bitmap is present

    mDataSection->write(dataWriter);

    dataWriter.write_nTimes('7',4);

    // Updating the size of the message

    ulonglong fPos = dataWriter.getWritePosition();
    mIndicatorSection->setTotalLength((fPos-mFilePosition));
    dataWriter.setWritePosition(mFilePosition);
    mIndicatorSection->write(dataWriter);
    dataWriter.setWritePosition(fPos);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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

    if (propertyId >= Property::ProductSection::FirstProperty  &&  propertyId <= Property::ProductSection::LastProperty)
    {
      if (mProductSection)
        return mProductSection->getProperty(propertyId,value);
    }

    if (propertyId >= Property::DataSection::FirstProperty  &&  propertyId <= Property::DataSection::LastProperty)
    {
      if (mDataSection)
        return mDataSection->getProperty(propertyId,value);
    }

    if (propertyId >= Property::GridSection::FirstProperty  &&  propertyId <= Property::GridSection::LastProperty)
    {
      if (mGridSection)
        return mGridSection->getProperty(propertyId,value);
    }

    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
      SmartMet::Spine::Exception exception(BCP,"Unknow property name!");
      exception.addParameter("propertyName",propertyName);
    }

    return getProperty(id,value);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("propertyName",propertyName);
    exception.addParameter("value",std::to_string(value));
    throw exception;
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

    if (propertyId >= Property::ProductSection::FirstProperty  &&  propertyId <= Property::ProductSection::LastProperty)
    {
      initProductSection();
      return mProductSection->setProperty(propertyId,value);
    }

    if (propertyId >= Property::DataSection::FirstProperty  &&  propertyId <= Property::DataSection::LastProperty)
    {
      initDataSection();
      return mDataSection->setProperty(propertyId,value);
    }

    if (propertyId >= Property::GridSection::FirstProperty  &&  propertyId <= Property::GridSection::LastProperty)
    {
      initGridSection();
      return mGridSection->setProperty(propertyId,value);
    }

    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("propertyId",std::to_string(propertyId));
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
    if (propertyId >= Property::IndicatorSection::FirstProperty  &&  propertyId <= Property::IndicatorSection::LastProperty)
    {
      initIndicatorSection();
      return mIndicatorSection->setProperty(propertyId,value);
    }

    if (propertyId >= Property::ProductSection::FirstProperty  &&  propertyId <= Property::ProductSection::LastProperty)
    {
      initProductSection();
      return mProductSection->setProperty(propertyId,value);
    }

    if (propertyId >= Property::DataSection::FirstProperty  &&  propertyId <= Property::DataSection::LastProperty)
    {
      initDataSection();
      return mDataSection->setProperty(propertyId,value);
    }

    if (propertyId >= Property::GridSection::FirstProperty  &&  propertyId <= Property::GridSection::LastProperty)
    {
      initGridSection();
      return mGridSection->setProperty(propertyId,value);
    }

    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("propertyId",std::to_string(propertyId));
    exception.addParameter("value",std::to_string(value));
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
      SmartMet::Spine::Exception exception(BCP,"Unknow property name!");
      exception.addParameter("propertyName",propertyName);
    }

    return setProperty(id,value);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
      SmartMet::Spine::Exception exception(BCP,"Unknow property name!");
      exception.addParameter("propertyName",propertyName);
    }

    return setProperty(id,value);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("propertyName",propertyName);
    exception.addParameter("value",std::to_string(value));
    throw exception;
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
    // If the grid values contains "ParamValueMissing" values then we should use bitmap
    // in ordert to indicate which values are in place.

    uint size = values.size();

    for (uint t=0; t<size; t++)
    {
      if (values[t] == ParamValueMissing)
      {
        // We found a missing value. Let's create a bitmap.

        initBitmapSection();

        // Defining the bitmap for the current values.

        uint bmSize = size /  8 + 1;
        uchar *bm = new uchar[bmSize];

        BitArrayWriter bmWriter(bm,size);
        for (uint a=0; a<size; a++)
        {
          if (values[a] == ParamValueMissing)
            bmWriter.writeBit(false);
          else
            bmWriter.writeBit(true);
        }

        // Setting the bitmap data into the BitmapSection. Notice that the this object will release
        // the data that we just allocated.

        mBitmapSection->setBitmapData(bm,bmSize);

        // We should set a flag that indicates that the bitmap is in use.

        mProductSection->setSectionFlags(mProductSection->getSectionFlags() | 0x40);

        // Ending the for -loop

        t = size;
      }
    }

    // Creating the DataSection object if it does not exists.

    initDataSection();

    // Setting the values for the DataSection object.

    if (mDataSection)
      mDataSection->encodeValues(values);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the pointer to the GribFile object.

        \return   The pointer of the GribFile object.
*/

GribFile* Message::getGribFile() const
{
  FUNCTION_TRACE
  try
  {
    return mGribFile;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    if (mProductSection)
      return mProductSection->getReferenceTime();

    return "";
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mProductSection)
      return mProductSection->getForecastTime();

    return "";
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the GRIB version number of the current message.

        \return   The GRIB version number.
*/


uint Message::getGribVersion() const
{
  FUNCTION_TRACE
  try
  {
    return 1;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the GRIB 1 centre identifer.

        \return   The GRIB 1 centre identifier.
*/

uint Message::getGribCentre() const
{
  FUNCTION_TRACE
  try
  {
    if (mProductSection)
      return mProductSection->getCentre();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the GRIB 1 sub-centre identifer.

        \return   The GRIB 1 sub-centre identifier.
*/

uint Message::getGribSubCentre() const
{
  FUNCTION_TRACE
  try
  {
    if (mProductSection)
      return mProductSection->getSubCentre();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the GRIB 1 processing identifer.

        \return   The GRIB 1 processing identifier.
*/

uint Message::getGribGeneratingProcessIdentifier() const
{
  FUNCTION_TRACE
  try
  {
    if (mProductSection)
      return mProductSection->getGeneratingProcessIdentifier();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the GRIB 1 table version.

        \return   The GRIB 1 table version.
*/

uint Message::getGribTableVersion() const
{
  FUNCTION_TRACE
  try
  {
    if (mProductSection)
      return mProductSection->getTableVersion();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
      return mGridSection->getGridGeometryId();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}






bool Message::getGridCellSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection != nullptr)
      return mGridSection->getGridCellSize(width,height);

    return false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
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
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    mGridSection->setGridGeometryId(geometryId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method set the data compression method that is used when new grid values are set into
    the place. In other words, the method does not change the compression method of the existing grid values.

        \param   The grid value compression method.
*/

void Message::setGridValueCompressionMethod(ushort compressionMethod)
{
  FUNCTION_TRACE
  try
  {
    initDataSection();
    if (mDataSection)
      mDataSection->setDataDefinition(compressionMethod);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridProjection();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridLayout();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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

T::Dimensions Message::getGridDimensions() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridDimensions();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid latlon coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

bool Message::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridLatLonCoordinatesByGridPoint(grid_i,grid_j,lat,lon);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridLatLonCoordinatesByGridPosition(grid_i,grid_j,lat,lon);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridLatLonCoordinatesByOriginalCoordinates(x,y,lat,lon);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalCoordinatesByGridPoint(grid_i,grid_j,x,y);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalCoordinatesByGridPosition(grid_i,grid_j,x,y);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector (in original projection).
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
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridCoordinates();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns all grid coordinates as a latlon coordinate vector. If the grid
    original coordiantes were not latlon coordinates then the original coordinates are converted
    to the latlon coordinates.

        \return   The grid latlon coordinates.
*/

T::Coordinate_vec Message::getGridLatLonCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridLatLonCoordinates();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the grid original (projection) coordinates by the given grid position.

        \param grid_i  The grid i-position.
        \param grid_j  The grid j-position.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/
/*

bool Message::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalCoordinatesByGridPosition(grid_i,grid_j,x,y);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}
*/




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
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalCoordinatesByLatLonCoordinates(lat,lon,x,y);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns a list of grid projection attributes.

        \param prefix         The prefix that is added in the front of each attribute name.
        \param attributeList  The projection attributes are returned in this parameter.
*/

void Message::getGridProjectionAttributes(std::string prefix,T::AttributeList& attributeList) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    mGridSection->getAttributeList(prefix,attributeList);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method returns the file identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid file identifier.
*/

uint Message::getFileId() const
{
  {
    try
    {
      if (mGribFile != nullptr)
        return mGribFile->getFileId();

      return 0;
    }
    catch (...)
    {
      throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
    }
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
    if (mGribFile != nullptr)
      return mGribFile->getProducerId();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    if (mGribFile != nullptr)
      return mGribFile->getGenerationId();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns a shared pointer to the BitmapSection object. */

BitmapSect_sptr Message::getBitmapSection() const
{
  FUNCTION_TRACE
  try
  {
    return mBitmapSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns a shared pointer to the GridSection object. */

GridSect_sptr Message::getGridSection() const
{
  FUNCTION_TRACE
  try
  {
    return mGridSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns a shared pointer to the IndicatorSection object. */

IndicatorSect_sptr Message::getIndicatorSection() const
{
  FUNCTION_TRACE
  try
  {
    return mIndicatorSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns a pointer to the ProductSection object. */

ProductSect_sptr Message::getProductSection() const
{
  FUNCTION_TRACE
  try
  {
    return mProductSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns a pointer to the DataSection object. */

DataSect_sptr Message::getDataSection() const
{
  FUNCTION_TRACE
  try
  {
    return mDataSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridProjectionString();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridPointByOriginalCoordinates(x,y,grid_i,grid_j);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalRowCount();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalColumnCount(row);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalColumnCount();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    //printf("COUNT %llu\n",(unsigned long long)mGridSection->getGridOriginalValueCount());
    return mGridSection->getGridOriginalValueCount();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->getGridOriginalValueIndex(grid_i,grid_j);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mDataSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mDataSection' attribute points to nullptr!");


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

    idx = C_INT((grid_j * cols) + (grid_i % cols));

    if (idx < 0)
      return ParamValueMissing;

    T::ParamValue value = 0;

    incRequestCounter(idx);

    // Trying to find a value from the point cache.

    if (getCachedValue(idx,value))
      return value;

    if (mBitmapSection == nullptr  ||  mBitmapSection->getBitmapDataSizeInBytes() == 0)
    {
      if (mDataSection->getPackingMethod() == PackingMethod::SIMPLE_PACKING)
      {
        if (mDataSection->getValueByIndex(idx,value))
        {
          addCachedValue(idx,value);
          //printf("--- getValueByIndex %u,%u  %u  %f\n",grid_i,grid_j,idx,value);
          return value;
        }
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

        if (mDataSection->getValueByIndex(index,value))
        {
          addCachedValue(idx,value);
          //printf("--- getValueFromIndexCache %u,%u  %u  %f\n",grid_i,grid_j,idx,value);
          return value;
        }
      }
      else
      {
        T::IndexVector indexVector;
        mBitmapSection->getIndexVector((rows*cols),indexVector);
        GRID::indexCache.addIndexVector(hash,indexVector);
        if (indexVector[idx] < 0)
          return ParamValueMissing;

        if (mDataSection->getValueByIndex(indexVector[idx],value))
        {
          addCachedValue(idx,value);
          //printf("--- getValueByIndexVector %u,%u  %u  %f\n",grid_i,grid_j,idx,value);
          return value;
        }
      }
    }

    if (mCacheKey > 0)
    {
      // Trying to get a memory cached value.

      if (GRID::valueCache.getValue(mCacheKey,idx,value))
      {
        addCachedValue(idx,value);
        //printf("--- getValueFromValueCache %u,%u  %u  %f\n",grid_i,grid_j,idx,value);
        return value;
      }
    }


    T::ParamValue_vec values;
    getGridValueVector(values);
    if ((std::size_t)idx >= values.size())
      return ParamValueMissing;

    addCachedValue(idx,values[idx]);
    // printf("--- getValueFromVector %u,%u  %u  %f\n",grid_i,grid_j,idx,value);
    return values[idx];
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
      if (GRID::valueCache.getValue(mOrigCacheKey,idx,value))
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mDataSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mDataSection' attribute points to nullptr!");

    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

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

      //printf("FILE (1) %u\n",getFileId());
      if (mDataSection->getPackingMethod() != PackingMethod::SIMPLE_PACKING)
        mOrigCacheKey = GRID::valueCache.addValues(values);

      if (d.getDimensions() == 2  &&  n != (d.nx() * d.ny()))
      {
        // Grid rows have different number of columns. Let's fill the rows so that they all have the same
        // number of columns.

        // TODO: We should interpolate between the columns. Now we just repeat the same value.

        auto maxCols = getGridOriginalColumnCount();

        T::ParamValue_vec valVector;
        uint rows = d.ny();

        for (uint r=0; r<rows; r++)
        {
          uint cols = getGridOriginalColumnCount(r);
          double step = C_DOUBLE(maxCols) / C_DOUBLE(cols);

          for (std::size_t c=0; c<maxCols; c++)
          {
            uint cc = C_UINT(C_DOUBLE(c) / step);
            int idx = C_INT(getGridOriginalValueIndex(cc,r));
            T::ParamValue val = values[idx];
            valVector.push_back(val);
          }
        }
        values = valVector;

        //  printf("FILE (2) %u\n",getFileId());
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
      SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
      exception.addParameter("Message index",std::to_string(mMessageIndex));
      exception.printError();
      mValueDecodingFailed = true;
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mDataSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mDataSection' attribute points to nullptr!");

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
      //printf("FILE (3) %u\n",getFileId());
      if (mDataSection->getPackingMethod() != PackingMethod::SIMPLE_PACKING)
        mOrigCacheKey = GRID::valueCache.addValues(values);

      if (getGridLayout() == T::GridLayoutValue::Regular)
      {
        mCacheKey = mOrigCacheKey;
        return;
      }

      if (getGridLayout() == T::GridLayoutValue::Irregular)
      {
        // The grid layout is irregular, which means that grid rows can contain different number of columns.
        // Let's fill the rows so that they all have the same number of columns. I.e. let's create a regular grid.

        // TODO: We should interpolate between the columns. Now we just repeat the same value.

        uint maxCols = getGridOriginalColumnCount();

        T::ParamValue_vec valVector;
        uint rows = 0;
        if (d.getDimensions() == 2)
          rows = d.ny();

        for (uint r=0; r<rows; r++)
        {
          std::size_t cols = getGridOriginalColumnCount(r);
          double step = C_DOUBLE(maxCols) / C_DOUBLE(cols);

          for (uint c=0; c<maxCols; c++)
          {
            uint cc = C_UINT(C_DOUBLE(c) / step);
            int idx = C_INT(getGridOriginalValueIndex(cc,r));
            T::ParamValue val = values[idx];
            valVector.push_back(val);
          }
        }
        //printf("FILE (4) %u\n",getFileId());
        if (mDataSection->getPackingMethod() != PackingMethod::SIMPLE_PACKING)
          mCacheKey = GRID::valueCache.addValues(valVector);
      }
    }
    catch (...)
    {
      SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
      exception.addParameter("Message index",std::to_string(mMessageIndex));
      exception.printError();
      mValueDecodingFailed = true;
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mProductSection != nullptr)
      return static_cast<T::ParamLevel>(mProductSection->getLevel());

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mProductSection != nullptr)
      return mProductSection->getIndicatorOfTypeOfLevel();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





/*! \brief The method intializes the grid's spatial reference that is used for coordinate conversions. */

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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    T::SpatialRef *sr = getSpatialReference();
    if (sr != nullptr)
    {
      char *out = nullptr;
      sr->exportToWkt(&out);
      wkt = out;
      OGRFree(out);
    }
    return wkt;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
    if (mProductSection)
      return mProductSection->getForecastType();

    return 0;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
    if (mProductSection)
      return mProductSection->getForecastNumber();

    return -1;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->isGridGlobal();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}





bool Message::isRelativeUV() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridSection == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->isRelativeUV();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->reverseXDirection();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
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
      throw SmartMet::Spine::Exception(BCP,"The 'mGridSection' attribute points to nullptr!");

    return mGridSection->reverseYDirection();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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

    return nullptr;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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

    return nullptr;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
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
    stream << space(level) << "- gribParameterUnits      = " << mGribParameterUnits << "\n";
    stream << space(level) << "- parameterLevel          = " << toString(getGridParameterLevel()) << "\n";
    stream << space(level) << "- parameterLevelId        = " << toString(getGridParameterLevelId()) << "\n";
    stream << space(level) << "- parameterLevelIdString  = " << getGridParameterLevelIdString() << "\n";
    stream << space(level) << "- fmiProducerName         = " << mFmiProducerName << "\n";
    stream << space(level) << "- fmiParameterId          = " << toString(mFmiParameterId) << "\n";
    stream << space(level) << "- fmiParameterLevelId     = " << toString(mFmiParameterLevelId) << "\n";
    stream << space(level) << "- fmiParameterName        = " << mFmiParameterName << "\n";
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
    stream << space(level) << "- WKT                     = " << getWKT() << "\n";

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
        uint ny = mGridSection->getGridOriginalRowCount();
        uint nx = mGridSection->getGridOriginalColumnCount();
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
                  sprintf(st,"[%u,%u] %f",y+1,x+1,val);
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
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("Message index",std::to_string(mMessageIndex));
    throw exception;
  }
}


}  // namespace GRIB1
}  // namespace SmartMet

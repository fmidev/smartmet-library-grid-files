#include "GridFile.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include "identification/GribDef.h"
#include "identification/MessageIdentifier_grib1.h"
#include "identification/MessageIdentifier_grib2.h"
#include "identification/MessageIdentifier_fmi.h"
#include "grib1/GribFile.h"
#include "grib2/GribFile.h"

namespace SmartMet
{
namespace GRID
{


/*! \brief The constructor of the class. */

GridFile::GridFile()
{
  try
  {
    mIsMemoryMapped = false;
    mCheckTime = 0;
    mFileId = 0;
    mGroupFlags = 0;
    mProducerId = 0;
    mGenerationId = 0;
    mCheckTime = 0;
    mSourceId = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",NULL);
  }
}





/*! \brief The destructor of the class. */

GridFile::~GridFile()
{
  try
  {
    if (mMappedFile  &&  mIsMemoryMapped)
      mMappedFile->close();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GridFile::getFileId() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getFileId();

    return mFileId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GridFile::getGroupFlags() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getGroupFlags();

    return mGroupFlags;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GridFile::getProducerId() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getProducerId();

    return mProducerId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GridFile::getGenerationId() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getGenerationId();

    return mGenerationId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




std::shared_ptr<GridFile> GridFile::getGridFile()
{
  try
  {
    return mGridFile;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




time_t GridFile::getCheckTime() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getCheckTime();

    return mCheckTime;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





time_t GridFile::getModificationTime() const
{
  try
  {
    return mFileModificationTime;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GridFile::getSourceId() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getSourceId();

    return mSourceId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridFile::isMemoryMapped()
{
  try
  {
    if (mGridFile)
      return mGridFile->isMemoryMapped();

    return mIsMemoryMapped;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}



void GridFile::setCheckTime(time_t checkTime)
{
  try
  {
    mCheckTime = checkTime;
    if (mGridFile)
      mGridFile->setCheckTime(checkTime);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridFile::setFileId(uint fileId)
{
  try
  {
    mFileId = fileId;
    if (mGridFile)
      mGridFile->setFileId(fileId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridFile::setGroupFlags(uint groupFlags)
{
  try
  {
    mGroupFlags = groupFlags;
    if (mGridFile)
      mGridFile->setGroupFlags(groupFlags);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridFile::setProducerId(uint producerId)
{
  try
  {
    mProducerId = producerId;
    if (mGridFile)
      mGridFile->setProducerId(producerId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






void GridFile::setGenerationId(uint generationId)
{
  try
  {
    mGenerationId = generationId;
    if (mGridFile)
      mGridFile->setGenerationId(generationId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridFile::setFileName(std::string fileName)
{
  try
  {
    mFileName = fileName;
    mFileModificationTime = time(0); //getFileModificationTime(fileName.c_str());
    if (mGridFile)
      mGridFile->setFileName(fileName);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridFile::setSourceId(uint sourceId)
{
  try
  {
    mSourceId = sourceId;
    if (mGridFile)
      mGridFile->setSourceId(sourceId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method memory maps the given file and after that it tries to
    recognize the type of the file. It creates and initializes GRIB1::GridFile
    or GRIB2::GridFile object according to the file type. This object represents
    the actual content of the current file.

       \param path  The grib filename with a possible directory path.
*/

void GridFile::read(const bf::path& path)
{
  try
  {
    // Safety checks
    if (!bf::exists(path))
      throw SmartMet::Spine::Exception(BCP,"The file '" + path.string() + "' does not exist!");

    if (!bf::is_regular(path))
      throw SmartMet::Spine::Exception(BCP,"The file '" + path.string() + "' is not regular!");

    auto fsize = bf::file_size(path);
    mPath = path;
    setFileName(mPath.string());

    // Map the entire file

    MappedFileParams params(path.c_str());
    params.flags = boost::iostreams::mapped_file::readonly;
    params.length = fsize;
    mMappedFile.reset(new MappedFile(params));
    mIsMemoryMapped = true;
    mFileModificationTime = getFileModificationTime(mFileName.c_str());

    //mMapping.reset(new bi::file_mapping(path.c_str(), bi::read_only));
    // mRegion.reset(new bi::mapped_region(*mMapping, bi::read_only, 0, fsize));

    auto startAddr = const_cast<char*>(mMappedFile->const_data());
    auto endAddr = startAddr + fsize;

    MemoryReader memoryReader((unsigned char*)startAddr,(unsigned char*)endAddr);

    T::FileType fileType = getFileType(memoryReader);

    switch (fileType)
    {
      case T::FileType::Grib1:
      {
        auto file = new GRIB1::GribFile();
        file->setFileName(mPath.string());
        file->setFileId(mFileId);
        file->setGroupFlags(mGroupFlags);
        file->setProducerId(mProducerId);
        file->setGenerationId(mGenerationId);
        file->setCheckTime(mCheckTime);
        mGridFile.reset(file);
        file->read(memoryReader);
      }
      break;

      case T::FileType::Grib2:
      {
        auto file = new GRIB2::GribFile();
        file->setFileName(mPath.string());
        file->setFileId(mFileId);
        file->setGroupFlags(mGroupFlags);
        file->setProducerId(mProducerId);
        file->setGenerationId(mGenerationId);
        file->setCheckTime(mCheckTime);
        mGridFile.reset(file);
        file->read(memoryReader);
      }
      break;

      default:
        throw SmartMet::Spine::Exception(BCP,"Unknown file type!");
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Read failed!",NULL);
    exception.addParameter("File name ",path.string());
    throw exception;
  }
}





/*! \brief The method returns the name and the path of the file.

       \return  The method returns the name and the path of the file.
*/

std::string GridFile::getFileName() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getFileName();

    return mFileName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method can be used in order to find out the number
    of the message in the current file.

       \return  The number of the messages in current the file.
*/

std::size_t GridFile::getNumberOfMessages() const
{
  try
  {
    if (!mGridFile)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridFile' attribute points to NULL!");

    return mGridFile->getNumberOfMessages();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method can be used in order to count messages which parameterId and level
    match the given parameterId and the level.

       \param parameterId  The requested parameterId.
       \param level        The requested level.
       \return             The number of matching messages.
*/

std::size_t GridFile::getNumberOfMessagesByParameterIdAndLevel(
    T::ParamId parameterId,
    T::ParamLevel level) const
{
  try
  {
    if (!mGridFile)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridFile' attribute points to NULL!");

    std::size_t count = 0;
    std::size_t messageCount = getNumberOfMessages();
    for (std::size_t t=0; t<messageCount; t++)
    {
      auto message = getMessageByIndex(t);
      if (message != NULL  &&  message->getGribParameterId() == parameterId  &&  message->getGridParameterLevel() == level)
        count++;
    }
    return count;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method can be used for identifying messages, which parameterId match to
    the given parameterId. The method returns a vector of message indexes, which point
    to the messages that contain the requested data.

       \param parameterId  The requested parameterId.
       \return             A vector of message indexes.
*/

T::Index_vec GridFile::getMessagesIndexListByParameterId(T::ParamId parameterId) const
{
  try
  {
    if (!mGridFile)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridFile' attribute points to NULL!");

    T::Index_vec indexList;
    std::size_t messageCount = getNumberOfMessages();
    for (std::size_t t=0; t<messageCount; t++)
    {
      auto message = getMessageByIndex(t);
      if (message != NULL  &&  message->getGribParameterId() == parameterId)
      {
        indexList.push_back(t);
      }
    }
    return indexList;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method can be used for identifying messages, which parameterId and level
    match to the given parameterId and the level. The method returns a vector of message
    indexes, which point to the messages that contain the requested data.

       \param parameterId  The requested parameterId.
       \param level        The requested level.
       \return             A vector of message indexes.
*/

T::Index_vec GridFile::getMessagesIndexListByParameterIdAndLevel(T::ParamId parameterId,T::ParamLevel level) const
{
  try
  {
    if (!mGridFile)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridFile' attribute points to NULL!");

    T::Index_vec indexList;
    std::size_t messageCount = getNumberOfMessages();
    for (std::size_t t=0; t<messageCount; t++)
    {
      auto message = getMessageByIndex(t);
      if (message != NULL  &&  message->getGribParameterId() == parameterId  &&  message->getGridParameterLevel() == level)
      {
        indexList.push_back(t);
      }
    }
    return indexList;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




/*! \brief The method searches messages which parameterId and level match the given parameterId
    and the level, and returns the first and the last forecast time of these messages.

       \param parameterId   The parameter identifier
       \param level         The requested level.
       \param startTime     The start time of the time interval.
       \param endTime       The end time of the time interval.
       \param messages      The returned number of the matching messages.
*/

void GridFile::getTimeRangeByParameterIdAndLevel(
    T::ParamId parameterId,
    T::ParamLevel level,
    T::TimeString& startTime,
    T::TimeString& endTime,
    std::size_t& messages) const
{
  try
  {
    if (!mGridFile)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridFile' attribute points to NULL!");

    messages = 0;
    std::size_t messageCount = getNumberOfMessages();
    for (std::size_t t=0; t<messageCount; t++)
    {
      auto message = getMessageByIndex(t);
      if (message != NULL  &&  message->getGribParameterId() == parameterId  &&  message->getGridParameterLevel() == level)
      {
        auto forecastTime = message->getForecastTime();
        if (messages == 0)
        {
          startTime = forecastTime;
          endTime = forecastTime;
        }
        else
        {
          if (forecastTime < startTime)
            startTime = forecastTime;

          if (forecastTime > endTime)
            endTime = forecastTime;
        }
        messages++;
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method can be used in order to find out parameterIds used in the current
    grib file. The method returns a vector of parameterIds that can be found from the file.
    Each parameter identifier is returned only once.

        \return  A vector of parameter identifiers.
*/

T::ParamId_vec GridFile::getParameterIdentifiers() const
{
  try
  {
    T::ParamId_vec parameterIdList;

    T::ParamId prevParamId;
    std::size_t messageCount = getNumberOfMessages();
    for (std::size_t t=0; t<messageCount; t++)
    {
      auto message = getMessageByIndex(t);
      if (message != NULL)
      {
        auto paramId = message->getGribParameterId();
        if (paramId != prevParamId)
        {
          auto paramIdCount = parameterIdList.size();
          bool idExists = false;
          for (std::size_t p = 0; p <paramIdCount && !idExists; p++)
          {
            if (parameterIdList[p] == paramId)
              idExists = true;
          }
          if (!idExists)
            parameterIdList.push_back(paramId);
        }
        prevParamId = paramId;
      }
    }
    return parameterIdList;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns a vector of levels according to the given parameterId.

        \param parameterId  The parameter identifier.
        \return             A vector of level values.
*/

T::ParamLevel_vec GridFile::getLevelsByParameterId(T::ParamId parameterId) const
{
  try
  {
    T::ParamLevel_vec levelList;
    std::size_t messageCount = getNumberOfMessages();
    for (std::size_t t=0; t<messageCount; t++)
    {
      auto message = getMessageByIndex(t);
      if (message != NULL  &&  message->getGribParameterId() == parameterId)
      {
        auto level = message->getGridParameterLevel();
        auto levelCount = levelList.size();
        bool levelExists = false;
        for (std::size_t l=0; l<levelCount && !levelExists; l++)
        {
          if (levelList[l] == level)
            levelExists = true;
        }
        if (!levelExists)
          levelList.push_back(level);
      }
    }
    return levelList;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method can be used in order to find out the value range used
    by the given parameter.

        \param parameterId  The parameter identifier.
        \param minValue     The returned minimum parameter value.
        \param maxValue     The returned maximum parameter value.
*/

void GridFile::getGridMinAndMaxValues(T::ParamId parameterId,T::ParamValue& minValue,T::ParamValue& maxValue) const
{
  try
  {
    minValue = 1000000000;
    maxValue = -1000000000;

    std::size_t messageCount = getNumberOfMessages();
    for (std::size_t t=0; t<messageCount; t++)
    {
      auto message = getMessageByIndex(t);
      if (message != NULL  &&  message->getGribParameterId() == parameterId)
      {
        T::ParamValue min = 1000000000;
        T::ParamValue max = -1000000000;
        message->getGridMinAndMaxValues(min,max);

        if (min != 1000000000  &&  max != -1000000000)
        {
          if (min < minValue)
            minValue = min;

          if (max > maxValue)
            maxValue = max;
        }
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method can be used in order to get pointer to the message object
    according to its index. The current message pointer can be used for accessing
    data inside the current message.

        \param index  The message index (0..N).
*/

GRID::Message* GridFile::getMessageByIndex(std::size_t index) const
{
  try
  {
    if (!mGridFile)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridFile' attribute points to NULL!");

    return mGridFile->getMessageByIndex(index);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method can be used for finding out the type of the file. The child classes
    should override this method.

        \return   The type of the file (expressed as an enum value).
*/

T::FileType GridFile::getFileType() const
{
  try
  {
    if (!mGridFile)
      return T::FileType::Unknown;

    return mGridFile->getFileType();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the type of the file expressed as a string. The child
    classes should override this method.

        \return   The type of the file (expressed as a string).
*/

std::string GridFile::getFileTypeString() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getFileTypeString();

    return std::string("Unknown");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method is used in order to detect the type of the current file. Technically
    the method reads few bytes from the beginning of the file and tries to recognize
    the used file type

        \param memoryReader  This object controls the access to the memory mapped file.
*/

T::FileType GridFile::getFileType(MemoryReader& memoryReader)
{
  try
  {
    memoryReader.setReadPosition(0);

    unsigned long long pos = searchFileStartPosition(memoryReader);
    memoryReader.setReadPosition(pos);

    unsigned char d[8];
    memoryReader.read_data(d,8);
    memoryReader.setReadPosition(0);

    if (d[0] == 'G'  &&  d[1] == 'R'  &&  d[2] == 'I'  &&  d[3] == 'B')
    {
      // This is a grib file.

      if (d[7] == 1)
        return T::FileType::Grib1;

      if (d[7] == 2)
        return T::FileType::Grib2;

    }
    return T::FileType::Unknown;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




/*! \brief  The method returns values in the given latlon point in the given time interval.
    The level value is not specified, so all levels are accepted.

        \param parameterId          The parameter identifier
        \param startTime            The start time of the time interval.
        \param endTime              The end time of the time interval.
        \param lat                  The latitude.
        \param lon                  The longitude.
        \param interpolationMethod  The requested interpolation method.
        \return                     The grid values as a vector of objects.
*/

T::GridPointValue_vec GridFile::getParameterValuesByLatLon(
    T::ParamId parameterId,
    T::TimeString startTime,
    T::TimeString endTime,
    double lat,
    double lon,
    T::InterpolationMethod interpolationMethod) const
{
  try
  {
    T::GridPointValue_vec gridPointValues;

    uint messageCount = (uint)getNumberOfMessages();
    const Message *prevMessage = NULL;

    for (uint t=0; t<messageCount; t++)
    {
      const Message *message = getMessageByIndex(t);
      if (message->getGribParameterId() == parameterId)
      {
        auto forecastTime = message->getForecastTime();
        if (forecastTime >= startTime  &&  forecastTime <= endTime)
        {
          if (prevMessage != NULL  &&  gridPointValues.size() == 0)
          {
            // Adding the previous value before the actual start time. This
            // helps the interpolation over time. The assumption is that
            // messages are ordered by the forecast time.

            T::GridPointValue point;
            point.mFileId = getFileId();
            point.mMessageIndex = t;
            point.mX = lon;
            point.mY = lat;
            point.mTime = prevMessage->getForecastTime();
            point.mValue = prevMessage->getGridValueByLatLonCoordinate(lat,lon,interpolationMethod);
            gridPointValues.push_back(point);
          }

          T::GridPointValue point;
          point.mFileId = getFileId();
          point.mMessageIndex = t;
          point.mX = lon;
          point.mY = lat;
          point.mTime = forecastTime;
          point.mValue = message->getGridValueByLatLonCoordinate(lat,lon,interpolationMethod);
          gridPointValues.push_back(point);
        }
        prevMessage = message;

        if (forecastTime > endTime)
        {
          // Adding the next value after the actual end time. This
          // helps the interpolation over time. The assumption is that
          // messages are ordered by the forecast time.

          T::GridPointValue point;
          point.mFileId = getFileId();
          point.mMessageIndex = t;
          point.mX = lon;
          point.mY = lat;
          point.mTime = message->getForecastTime();
          point.mValue = message->getGridValueByLatLonCoordinate(lat,lon,interpolationMethod);
          gridPointValues.push_back(point);

          // We can end the search.
          return gridPointValues;
        }
      }
    }
    return gridPointValues;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Message addition failed!",NULL);
  }
}





/*! \brief The method returns values in the given latlon point in the given time
    interval on the given level.

        \param parameterId          The parameter identifier
        \param level                The requested level.
        \param startTime            The start time of the time interval.
        \param endTime              The end time of the time interval.
        \param lat                  The latitude.
        \param lon                  The longitude.
        \param interpolationMethod  The requested interpolation method.
        \return                     The grid values as a vector of objects.
*/

T::GridPointValue_vec GridFile::getParameterValuesByLatLon(
    T::ParamId parameterId,
    T::ParamLevel level,
    T::TimeString startTime,
    T::TimeString endTime,
    double lat,
    double lon,
    T::InterpolationMethod interpolationMethod) const
{
  try
  {
    T::GridPointValue_vec gridPointValues;

    uint messageCount = (uint)getNumberOfMessages();
    const Message *prevMessage = NULL;

    for (uint t=0; t<messageCount; t++)
    {
      const Message *message = getMessageByIndex(t);
      if (message->getGribParameterId() == parameterId  &&  message->getGridParameterLevel() == level)
      {
        auto forecastTime = message->getForecastTime();
        if (forecastTime >= startTime  &&  forecastTime <= endTime)
        {
          if (prevMessage != NULL &&  gridPointValues.size() == 0)
          {
            // Adding the previous value before the actual start time. This
            // helps the interpolation over time. The assumption is that
            // messages are ordered by the forecast time.

            T::GridPointValue point;
            point.mFileId = getFileId();
            point.mMessageIndex = t;
            point.mX = lon;
            point.mY = lat;
            point.mTime = prevMessage->getForecastTime();
            point.mValue = prevMessage->getGridValueByLatLonCoordinate(lat,lon,interpolationMethod);
            gridPointValues.push_back(point);
          }

          T::GridPointValue point;
          point.mFileId = getFileId();
          point.mMessageIndex = t;
          point.mX = lon;
          point.mY = lat;
          point.mTime = forecastTime;
          point.mValue = message->getGridValueByLatLonCoordinate(lat,lon,interpolationMethod);
          gridPointValues.push_back(point);
        }
        prevMessage = message;

        if (forecastTime > endTime)
        {
          // Adding the next value after the actual end time. This
          // helps the interpolation over time. The assumption is that
          // messages are ordered by the forecast time.

          T::GridPointValue point;
          point.mFileId = getFileId();
          point.mMessageIndex = t;
          point.mX = lon;
          point.mY = lat;
          point.mTime = message->getForecastTime();
          point.mValue = message->getGridValueByLatLonCoordinate(lat,lon,interpolationMethod);
          gridPointValues.push_back(point);

          // We can end the search.
          return gridPointValues;
        }
      }
    }
    return gridPointValues;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Message addition failed!",NULL);
  }
}





/*! \brief The method returns values in the given latlon point in the given
    time interval. The level value is not specified, so all levels are accepted.
    The method uses a default interpolation method (based on the units of
    the current parameter).

        \param parameterId   The parameter identifier
        \param startTime     The start time of the time interval.
        \param endTime       The end time of the time interval.
        \param lat           The latitude.
        \param lon           The longitude.
        \return              The grid values as a vector of objects.
*/

T::GridPointValue_vec GridFile::getParameterValuesByLatLon(
    T::ParamId parameterId,
    T::TimeString startTime,
    T::TimeString endTime,
    double lat,
    double lon) const
{
  try
  {
    auto interpolationMethod = T::InterpolationMethod::Linear;
    Identification::ParameterDefinition_cptr def = Identification::gribDef.getGribParamDefById(parameterId);
    if (def != NULL)
      interpolationMethod = Identification::gribDef.getPreferredInterpolationMethodByUnits(def->mParameterUnits);

    return getParameterValuesByLatLon(parameterId,startTime,endTime,lat,lon,interpolationMethod);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns values in the given latlon point in the given
    time interval on the given level. The method uses a default interpolation
    method (based on the units of the current parameter).

        \param parameterId   The parameter identifier
        \param level         The requested level.
        \param startTime     The start time of the time interval.
        \param endTime       The end time of the time interval.
        \param lat           The latitude.
        \param lon           The longitude.
        \return              The grid values as a vector of objects.
*/

T::GridPointValue_vec GridFile::getParameterValuesByLatLon(
    T::ParamId parameterId,
    T::ParamLevel level,
    T::TimeString startTime,
    T::TimeString endTime,
    double lat,
    double lon) const
{
  try
  {
    auto interpolationMethod = T::InterpolationMethod::Linear;
    Identification::ParameterDefinition_cptr def = Identification::gribDef.getGribParamDefById(parameterId);
    if (def != NULL)
      interpolationMethod = Identification::gribDef.getPreferredInterpolationMethodByUnits(def->mParameterUnits);

    return getParameterValuesByLatLon(parameterId,level,startTime,endTime,lat,lon,interpolationMethod);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





unsigned long long GridFile::searchFileStartPosition(MemoryReader& memoryReader)
{
  try
  {
    std::vector<unsigned char*> gribs;

    // A complete indicator section takes 16 bytes, hence we can stop the loop earlier
    // thus making sure all reads inside the loop succeed.

    while (memoryReader.getReadPtr() < memoryReader.getEndPtr())
    {
      // Usually GRIB2 messages do not have any extra garbage between them, several GRIB1 messages do
      // seem to have it. Most likely it's not worth optimizing this search, we'll just skip one byte
      // at a time.

      long long pos = memoryReader.getReadPosition();

      if (!memoryReader.peek_string("GRIB"))
      {
        memoryReader.read_null(1);
      }
      else
      {
        return pos;
      }
    }
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Message search failed!",NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GridFile::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    if (!mGridFile)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridFile' attribute points to NULL!");

    mGridFile->print(stream,level,optionFlags);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




}  // namespace GRID
}  // namespace SmartMet

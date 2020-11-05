#pragma once

#include "BitmapSection.h"
#include "DataSection.h"
#include "GridSection.h"
#include "ProductSection.h"
#include "IndicatorSection.h"
#include "Properties.h"
#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/GeneralDefinitions.h"
#include "../grid/Message.h"
#include "../grid/ValueCache.h"
#include "../grid/Typedefs.h"

#include <boost/filesystem.hpp>
#include <boost/optional.hpp>


namespace SmartMet
{
namespace GRIB1
{


/*
  --------------------------------------------------------------------------------------
  GRIB 1 Message
  --------------------------------------------------------------------------------------
  Section Name
  --------------------------------------------------------------------------------------
  0       Indicator section
  1       Product definition section
  2       Grid description section (optional)
  3       Bit-map section
  4       Binary data section
  5       End section
  --------------------------------------------------------------------------------------
 */

class Message : public GRID::Message
{
  public:
                        Message();
                        Message(GRID::GridFile *gridFile,uint messageIndex,GRID::MessageInfo& messageInfo);
                        Message(const Message& other);
    virtual             ~Message();

    // ### Common methods for all message types

    void                getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    uint                getFileId() const;
    uint                getProducerId() const;
    uint                getGenerationId() const;
    T::FilePosition     getFilePosition() const;
    T::TimeString       getForecastTime() const;
    time_t              getForecastTimeT() const;
    short               getForecastType() const;
    short               getForecastNumber() const;

    uint                getGribVersion() const;
    uint                getGribCentre() const;
    uint                getGribSubCentre() const;
    uint                getGribGeneratingProcessIdentifier() const;
    uint                getGribTableVersion() const;
    void                getSectionPositions(std::set<T::FilePosition>& positions);

    T::GeometryId       getGridGeometryId() const;
    std::string         getGridGeometryString() const;
    T::Dimensions       getGridDimensions() const;
    T::Hash             getGridHash() const;
    bool                getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    T::Coordinate_svec  getGridLatLonCoordinates() const;
    bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    T::GridLayout       getGridLayout() const;
    bool                getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    bool                getGridMetricCellSize(double& width,double& height) const;
    bool                getGridMetricSize(double& width,double& height) const;
    T::Coordinate_svec  getGridOriginalCoordinates() const;
    bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    std::size_t         getGridOriginalColumnCount() const;
    std::size_t         getGridOriginalColumnCount(std::size_t row) const;
    std::size_t         getGridOriginalRowCount() const;
    std::size_t         getGridOriginalValueCount() const;
    int                 getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    void                getGridOriginalValueVector(T::ParamValue_vec& values) const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    T::GridProjection   getGridProjection() const;
    void                getGridProjectionAttributes(std::string prefix,T::AttributeList& attributeList) const;
    std::string         getGridProjectionString() const;
    T::ParamLevel       getGridParameterLevel() const;
    T::ParamLevelId     getGridParameterLevelId() const;
    std::string         getGridParameterLevelIdString() const;
    void                getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const;
    std::size_t         getGridColumnCount() const;
    std::size_t         getGridRowCount() const;
    T::ParamValue       getGridValueByGridPoint(uint grid_i,uint grid_j) const;
    T::ParamValue       getGridValueByOriginalGridPoint(uint grid_i,uint grid_j) const;
    void                getGridValueVector(T::ParamValue_vec& values) const;
    T::TimeString       getReferenceTime() const;
    T::SpatialRef*      getSpatialReference() const;
    std::string         getWKT() const;
    bool                isGridGlobal() const;
    bool                isRelativeUV() const;
    void                initSpatialReference();
    bool                reverseXDirection() const;
    bool                reverseYDirection() const;

    bool                getProperty(uint propertyId,long long& value);
    bool                getProperty(const char *propertyName,long long& value);

    bool                setProperty(uint propertyId,long long value);
    bool                setProperty(uint propertyId,double value);
    bool                setProperty(const char *propertyName,long long value);
    bool                setProperty(const char *propertyName,double value);

    void                setGridGeometryId(T::GeometryId geometryId);
    void                setGridValues(T::ParamValue_vec& values);
    void                setGridValueCompressionMethod(ushort compressionMethod);

    // ### Message/file type specific methods

    BitmapSect_sptr     getBitmapSection() const;
    GridSect_sptr       getGridSection() const;
    IndicatorSect_sptr  getIndicatorSection() const;
    ProductSect_sptr    getProductSection() const;
    DataSect_sptr       getDataSection() const;

    // Fast access to substructures

    T::Data_ptr         getBitmapDataPtr() const;
    std::size_t         getBitmapDataSizeInBytes() const;
    std::int16_t        getBinaryScaleFactor() const;
    std::uint16_t       getDecimalScaleFactor() const;
    std::float_t        getReferenceValue() const;
    std::uint8_t        getBitsPerValue() const;
    std::uint8_t        getFlags() const;
    T::Data_ptr         getDataPtr() const;
    std::size_t         getDataSize() const;
    std::size_t         getDataSizeMax() const;

    void                initBitmapSection();
    void                initIndicatorSection();
    void                initDataSection();
    void                initGridSection();
    void                initProductSection();

    void                lockData();
    void                unlockData();

    bool                isRead();
    void                read();
    void                read(MemoryReader& memoryReader);
    void                write(DataWriter& dataWriter);
    void                print(std::ostream& stream,uint level,uint optionFlags) const;


  private:

    /*! \brief The message start position in the file. */
    T::FilePosition     mFilePosition;

    /*! \brief Indicates if the message is already read. */
    bool                mIsRead;

    /*! \brief  A shared pointer to the IndicatorSection object. */
    IndicatorSect_sptr  mIndicatorSection;

    /*! \brief  A shared pointer to the GridSection object. */
    GridSect_sptr       mGridSection;

    /*! \brief  An unique pointer to the ProductSection object. */
    ProductSect_sptr    mProductSection;

    /*! \brief  A shared pointer to the BitmapSection object. */
    BitmapSect_sptr     mBitmapSection;

    /*! \brief  An unique pointer to the DataSection object. */
    DataSect_sptr       mDataSection;

    /*! \brief  A cache key that was used for caching the grid data (that might be modified). */
    mutable uint        mCacheKey;

    /*! \brief  A cache key that was used for caching the original grid data. */
    mutable uint        mOrigCacheKey;

    /*! \brief  A flag that indicates that the data decoding is impossible. */
    mutable bool        mValueDecodingFailed;

    mutable bool        mDataLocked;

    T::TimeString       mForecastTime;
    time_t              mForecastTimeT;

  public:

    class SectionNumber
    {
      public:
        static const uchar indicator_section = 0;
        static const uchar product_section   = 1;
        static const uchar grid_section      = 2;
        static const uchar bitmap_section    = 3;
        static const uchar data_section      = 4;
        static const uchar end_section       = 5;
    };
};


typedef std::shared_ptr<Message> Message_sptr;




}  // namespace GRIB1
}  // namespace SmartMet

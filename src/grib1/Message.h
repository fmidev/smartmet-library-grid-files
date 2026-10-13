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

#include <filesystem>
#include <optional>


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

// ====================================================================================
/*! \brief GRIB edition 1 message — the main entry point for accessing GRIB 1 data.
 *
 *  Wraps the five GRIB 1 sections (Indicator, Product, Grid, Bitmap, Data) and
 *  implements the full GRID::Message virtual interface: coordinate conversions, grid
 *  metadata, parameter/level identification, and value decoding.
 *
 *  Sections are parsed lazily on first access via read(MemoryReader&) and cached
 *  in shared_ptr members.  Grid value decode results are cached via GRID::ValueCache
 *  keyed on mCacheKey / mOrigCacheKey. */
// ====================================================================================

class Message : public GRID::Message
{
  public:
                        Message();
                        Message(GRID::GridFile *gridFile,T::MessageIndex messageIndex,const GRID::MessageInfo& messageInfo);
                        Message(const Message& other);
    ~Message() override;

    // ### Common methods for all message types

    void                getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const override;
    bool                getAttributeValue(const char *attributeName, std::string& attributeValue) const override;
    bool                hasAttributeValue(const char *attributeName, const char *attributeValue) const override;
    T::FileId           getFileId() const override;
    T::FileType         getMessageType() const override;
    char*               getMemoryPtr() const override;
    T::ProducerId       getProducerId() const override;
    T::GenerationId     getGenerationId() const override;
    T::FilePosition     getFilePosition() const override;
    T::TimeString       getForecastTime() const override;
    time_t              getForecastTimeT() const override;
    T::ForecastType     getForecastType() const override;
    T::ForecastNumber   getForecastNumber() const override;

    uint                getGribVersion() const override;
    uint                getGribCentre() const override;
    uint                getGribSubCentre() const override;
    uint                getGribGeneratingProcessIdentifier() const override;
    uint                getGribTableVersion() const override;
    void                getSectionPositions(std::set<T::FilePosition>& positions) override;

    T::GeometryId       getGridGeometryId() const override;
    std::string         getGridGeometryString() const override;
    void                getGridCellAverageSize(double& width,double& height) const override;
    T::Dimensions       getGridDimensions() const override;
    T::Hash             getGridHash() const override;
    bool                getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight) override;
    T::Coordinate_svec  getGridLatLonCoordinates() const override;
    bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const override;
    bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const override;
    bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const override;
    bool                getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight) override;
    bool                getGridMetricCellSize(double& width,double& height) const override;
    bool                getGridMetricSize(double& width,double& height) const override;
    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const override;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const override;
    bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const override;
    std::size_t         getGridOriginalValueCount() const override;
    int                 getGridOriginalValueIndex(uint grid_i,uint grid_j) const override;
    void                getGridOriginalValueVector(T::ParamValue_vec& values) const override;
    void                getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;
    bool                getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const override;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const override;
    T::GridProjection   getGridProjection() const override;
    void                getGridProjectionAttributes(const std::string& prefix,T::AttributeList& attributeList) const override;
    T::ParamLevel       getGridParameterLevel() const override;
    T::ParamLevelId     getGridParameterLevelId() const override;
    void                getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const override;
    std::size_t         getGridColumnCount() const override;
    std::size_t         getGridRowCount() const override;
    T::ParamValue       getGridValueByGridPoint(uint grid_i,uint grid_j) const override;
    void                getGridValueVector(T::ParamValue_vec& values) const override;
    void                getGridValuesByPointList(std::vector<T::Point>& gridPoints,T::ParamValue_vec& values) const override;
    T::TimeString       getReferenceTime() const override;
    T::SpatialRef_sptr  getSpatialReference() const override;
    std::string         getWKT() const override;
    std::string         getProj4() const override;
    bool                isGridGlobal() const override;
    bool                isRelativeUV() const override;
    void                initSpatialReference() override;
    bool                reverseXDirection() const override;
    bool                reverseYDirection() const override;

    bool                getProperty(uint propertyId,Int64& value) override;
    bool                getProperty(const char *propertyName,Int64& value) override;
    void                getProperties(T::PropertySettingVec& properties) override;

    bool                setProperty(uint propertyId,Int64 value) override;
    bool                setProperty(uint propertyId,double value) override;
    bool                setProperty(const char *propertyName,Int64 value) override;
    bool                setProperty(const char *propertyName,double value) override;

    void                setGridGeometryId(T::GeometryId geometryId) override;
    void                setGridValues(T::ParamValue_vec& values) override;
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

    void                lockData() override;
    void                unlockData() override;

    bool                isRead() override;
    void                read() override;
    void                read(MemoryReader& memoryReader) override;
    void                write(DataWriter& dataWriter) override;
    void                print(std::ostream& stream,uint level,uint optionFlags) const override;
    void                premap() const override;


  private:

    /*! \brief The message start position in the file. */
    T::FilePosition     mFilePosition;

    T::FilePosition     mOriginalFilePosition;  //!< File position before any in-place modifications.

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

    time_t              mForecastTimeT;     //!< Cached forecast time as a Unix timestamp.

    /*! \brief Indicates if the message is already read. */
    bool                mIsRead;

    /*! \brief  The time of the latest failed value decoding (0 = none). Decoding
                is not retried for a while after a failure. */
    mutable time_t      mValueDecodingFailedTime;

    mutable bool        mDataLocked;        //!< True while a concurrent thread holds the data for read.

  public:

    /*! \brief GRIB 1 section numbers used to identify each section in a message. */
    class SectionNumber
    {
      public:
        static const uchar indicator_section = 0;  //!< Section 0 — Indicator Section.
        static const uchar product_section   = 1;  //!< Section 1 — Product Definition Section.
        static const uchar grid_section      = 2;  //!< Section 2 — Grid Description Section.
        static const uchar bitmap_section    = 3;  //!< Section 3 — Bitmap Section.
        static const uchar data_section      = 4;  //!< Section 4 — Binary Data Section.
        static const uchar end_section       = 5;  //!< Section 5 — End Section.
    };
};


using Message_sptr = std::shared_ptr<Message>;  //!< Shared ownership pointer to a GRIB 1 Message.




}  // namespace GRIB1
}  // namespace SmartMet

#pragma once

#include "BitmapSection.h"
#include "DataSection.h"
#include "GridSection.h"
#include "ProductSection.h"
#include "LocalSection.h"
#include "IndicatorSection.h"
#include "IdentificationSection.h"
#include "RepresentationSection.h"
#include "Properties.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/GeneralDefinitions.h"
#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../grid/Message.h"
#include "../grid/ValueCache.h"


namespace SmartMet
{
namespace GRIB2
{

//class GridFile;




class Message : public GRID::Message
{
  public:

                        Message();
                        Message(GRID::GridFile *gridFile,uint messageIndex,GRID::MessageInfo& messageInfo);
                        Message(const Message& other);
    virtual             ~Message();

    // ### Common methods for all message types

    void                getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    bool                getAttributeValue(const char *attributeName, std::string& attributeValue) const;
    bool                hasAttributeValue(const char *attributeName, const char *attributeValue) const;
    uint                getFileId() const;
    T::FileType         getMessageType() const;
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

    void                getGridCellAverageSize(double& width,double& height) const;
    T::Dimensions       getGridDimensions() const;
    T::GeometryId       getGridGeometryId() const;
    std::string         getGridGeometryString() const;
    T::Hash             getGridHash() const;
    bool                getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    T::Coordinate_svec  getGridLatLonCoordinates() const;
    bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    bool                getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    bool                getGridMetricCellSize(double& width,double& height) const;
    bool                getGridMetricSize(double& width,double& height) const;
    T::Coordinate_svec  getGridOriginalCoordinates() const;
    bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    std::size_t         getGridOriginalValueCount() const;
    int                 getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    void                getGridOriginalValueVector(T::ParamValue_vec& values) const;
    void                getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    T::GridProjection   getGridProjection() const;
    void                getGridProjectionAttributes(const std::string& prefix,T::AttributeList& attributeList) const;
    T::ParamLevel       getGridParameterLevel() const;
    T::ParamLevelId     getGridParameterLevelId() const;
    void                getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const;
    std::size_t         getGridColumnCount() const;
    std::size_t         getGridRowCount() const;
    T::ParamValue       getGridValueByGridPoint(uint grid_i,uint grid_j) const;
    void                getGridValueVector(T::ParamValue_vec& values) const;
    T::TimeString       getReferenceTime() const;
    T::SpatialRef*      getSpatialReference() const;
    std::string         getWKT() const;
    std::string         getProj4() const;
    void                initSpatialReference();
    bool                isGridGlobal() const;
    bool                isRelativeUV() const;
    bool                reverseXDirection() const;
    bool                reverseYDirection() const;

    bool                getProperty(uint propertyId,long long& value);
    bool                getProperty(const char *propertyName,long long& value);

    void                getProperties(T::PropertySettingVec& properties);

    bool                setProperty(uint propertyId,long long value);
    bool                setProperty(uint propertyId,double value);
    bool                setProperty(const char *propertyName,long long value);
    bool                setProperty(const char *propertyName,double value);

    void                setGridGeometryId(T::GeometryId geometryId);
    void                setGridValues(T::ParamValue_vec& values);


    // ### Message/file type specific methods

    BitmapSect_sptr     getBitmapSection() const;
    IdentifSect_sptr    getIdentificationSection() const;
    GridSect_sptr       getGridSection() const;
    RepresentSect_sptr  getRepresentationSection() const;
    IndicatorSect_sptr  getIndicatorSection() const;
    LocalSect_sptr      getLocalSection() const;
    ProductSect_sptr    getProductSection() const;
    DataSect_sptr       getDataSection() const;
    BitmapSect_sptr     getPreviousBitmapSection() const;
    std::uint8_t        getTablesVersion() const;

    bool                hasRequiredSections() const;
    void                copyMissingSections(const Message& other);
    void                initParameterInfo();

    void                initIndicatorSection();
    void                initIdentificationSection();
    void                initLocalSection();
    void                initGridSection();
    void                initProductSection();
    void                initRepresentationSection();
    void                initBitmapSection();
    void                initDataSection();

    void                lockData();
    void                unlockData();

    void                setBitmapSection(BitmapSect_sptr bitmapSection);
    void                setBitmapSection(BitmapSection *bitmapSection);
    void                setIdentificationSection(IdentifSect_sptr identificationSection);
    void                setIdentificationSection(IdentificationSection *identificationSection);
    void                setGridSection(GridSect_sptr gridSection);
    void                setGridSection(GridSection *gridSection);
    void                setRepresentationSection(RepresentSect_sptr representationSection);
    void                setRepresentationSection(RepresentationSection *representationSection);
    void                setIndicatorSection(IndicatorSect_sptr indicatorSection);
    void                setIndicatorSection(IndicatorSection *indicatorSection);
    void                setLocalSection(LocalSect_sptr localSection);
    void                setLocalSection(LocalSection *localSection);
    void                setProductSection(ProductSect_sptr productSection);
    void                setProductSection(ProductSection *productSection);
    void                setDataSection(DataSect_sptr dataSection);
    void                setDataSection(DataSection *dataSection);
    void                setPreviousBitmapSection(BitmapSect_sptr previousBitmapSection);

    // Fast access to substructures

    T::Data_ptr         getBitmapDataPtr() const;
    std::size_t         getBitmapDataSizeInBytes() const;
    T::Data_ptr         getDataPtr() const;
    std::size_t         getDataSize() const;

    bool                isRead();
    void                read();
    void                read(MemoryReader& memoryReader);
    void                write(DataWriter& dataWriter);
    void                print(std::ostream& stream,uint level,uint optionFlags) const;
    void                premap() const;


  private:

    /*! \brief  The message start position in the file. */
    T::FilePosition     mFilePosition;

    /*! \brief  A shared pointer to the IndicatorSection object. */
    IndicatorSect_sptr  mIndicatorSection;

    /*! \brief  A shared pointer to the IdentificationSection object. */
    IdentifSect_sptr    mIdentificationSection;

    /*! \brief  A shared pointer to the LocalSection object. */
    LocalSect_sptr      mLocalSection;

    /*! \brief  A shared pointer to the GridSection object. */
    GridSect_sptr       mGridSection;

    /*! \brief  An unique pointer to the ProductSection object. */
    ProductSect_sptr    mProductSection;

    /*! \brief  An unique pointer to the RepresentationSection object. */
    RepresentSect_sptr  mRepresentationSection;

    /*! \brief  A shared pointer to the BitmapSection object. */
    BitmapSect_sptr     mBitmapSection;

    /*! \brief  An unique pointer to the DataSection object. */
    DataSect_sptr       mDataSection;

    /*! \brief  Reference to an earlier bitmap */
    BitmapSect_sptr     mPreviousBitmapSection;

    /*! \brief  A cache key that was used for caching the grid data (that might be modified). */
    mutable uint        mCacheKey;

    /*! \brief  A cache key that was used for caching the original grid data. */
    mutable uint        mOrigCacheKey;

    time_t              mForecastTimeT;

    /*! \brief Indicates if the message is already read. */
    bool                mIsRead;

    /*! \brief  A flag that indicates that the data decoding is impossible. */
    mutable bool        mValueDecodingFailed;

    mutable bool        mDataLocked;



  public:

    class SectionNumber
    {
      public:
        enum
	  {
	   indicator_section       = 0,
	   identification_section  = 1,
	   local_section           = 2,
	   grid_section            = 3,
	   product_section         = 4,
	   representation_section  = 5,
	   bitmap_section          = 6,
	   data_section            = 7,
	   end_section             = 8
	  };
    };
};





}  // namespace GRIB2
}  // namespace SmartMet

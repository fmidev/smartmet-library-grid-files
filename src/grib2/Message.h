#pragma once

#include "grid/Message.h"
#include "common/MemoryReader.h"
#include "common/GeneralDefinitions.h"
#include "BitmapSection.h"
#include "DataSection.h"
#include "GridSection.h"
#include "ProductSection.h"
#include "LocalSection.h"
#include "IndicatorSection.h"
#include "IdentificationSection.h"
#include "RepresentationSection.h"
#include "common/Coordinate.h"
#include "common/Dimensions.h"
#include "grid/ValueCache.h"


namespace SmartMet
{
namespace GRIB2
{

class GribFile;


class Message : public GRID::Message
{
  public:

                            Message();
                            Message(GribFile *gribFile);
    virtual                 ~Message();

    // ### Common methods for all message types

    void                    getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    uint                    getFileId() const;
    T::FilePosition         getFilePosition() const;
    T::TimeString           getForecastTime() const;
    short                   getForecastType() const;
    short                   getForecastNumber() const;
    GribFile*               getGribFile() const;

    T::GeometryId           getGridGeometryId() const;
    T::Coordinate_vec       getGridCoordinates() const;
    T::Coordinate_vec       getGridLatLonCoordinates() const;
    T::Dimensions_opt       getGridDimensions() const;
    T::Hash                 getGridHash() const;
    bool                    getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    bool                    getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    bool                    getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    bool                    getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;
    bool                    getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;
    bool                    getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;
    T::GridLayout           getGridLayout() const;
    std::size_t             getGridOriginalColumnCount() const;
    std::size_t             getGridOriginalColumnCount(std::size_t row) const;
    std::size_t             getGridOriginalRowCount() const;
    std::size_t             getGridOriginalValueCount() const;
    int                     getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    bool                    getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                    getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    T::GridProjection       getGridProjection() const;
    void                    getGridProjectionAttributes(std::string prefix,T::AttributeList& attributeList) const;
    std::string             getGridProjectionString() const;
    T::ParamLevel           getGridParameterLevel() const;
    T::ParamLevelId         getGridParameterLevelId() const;
    std::string             getGridParameterLevelIdString() const;
    void                    getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const;
    void                    getGridOriginalValueVector(T::ParamValue_vec& values) const;
    T::ParamValue           getGridValueByGridPoint(uint grid_i,uint grid_j) const;
    void                    getGridValueVector(T::ParamValue_vec& values) const;
    T::TimeString           getReferenceTime() const;
    T::SpatialReference*    getSpatialReference() const;
    std::string             getWKT() const;
    bool                    isGridGlobal() const;
    bool                    reverseXDirection() const;
    bool                    reverseYDirection() const;
    void                    print(std::ostream& stream,uint level,uint optionFlags) const;

    // ### Message/file type specific methods

    BitmapSection_sptr      getBitmapSection() const;
    IdentificSection_sptr   getIdentificationSection() const;
    GridSection_sptr        getGridSection() const;
    RepresentSection_cptr   getRepresentationSection() const;
    IndicatorSection_sptr   getIndicatorSection() const;
    LocalSection_sptr       getLocalSection() const;
    ProductSection_cptr     getProductSection() const;
    DataSection_cptr        getDataSection() const;
    BitmapSection_sptr      getPreviousBitmapSection() const;
    std::uint8_t            getTablesVersion() const;

    bool                    hasRequiredSections() const;
    void                    copyMissingSections(const Message& other);
    void                    initParameterInfo();
    void                    setPreviousBitmapSection(boost::shared_ptr<BitmapSection> previousBitmapSection);

    void                    read(MemoryReader& memoryReader);
    void                    setGridGeometryId(T::GeometryId geometryId);

    // Fast access to substructures

    T::Data_ptr             getBitmapDataPtr() const;
    std::size_t             getBitmapDataSizeInBytes() const;
    T::Data_ptr             getDataPtr() const;
    std::size_t             getDataSize() const;


  private:

    GribFile*             mGribFile;

    /*! \brief  The message start position in the file. */
    T::FilePosition       mFilePosition;

    /*! \brief  A shared pointer to the IndicatorSection object. */
    IndicatorSection_sptr mIndicatorSection;

    /*! \brief  A shared pointer to the IdentificationSection object. */
    IdentificSection_sptr mIdentificationSection;

    /*! \brief  A shared pointer to the LocalSection object. */
    LocalSection_sptr     mLocalSection;

    /*! \brief  A shared pointer to the GridSection object. */
    GridSection_sptr      mGridSection;

    /*! \brief  An unique pointer to the ProductSection object. */
    ProductSection_uptr   mProductSection;

    /*! \brief  An unique pointer to the RepresentationSection object. */
    RepresentSection_uptr mRepresentationSection;

    /*! \brief  A shared pointer to the BitmapSection object. */
    BitmapSection_sptr    mBitmapSection;

    /*! \brief  An unique pointer to the DataSection object. */
    DataSection_uptr      mDataSection;

    /*! \brief  Reference to an earlier bitmap */
    BitmapSection_sptr    mPreviousBitmapSection;

    /*! \brief  A cache key that was used for caching the grid data (that might be modified). */
    mutable uint          mCacheKey;

    /*! \brief  A cache key that was used for caching the original grid data. */
    mutable uint          mOrigCacheKey;

    /*! \brief  A flag that indicates that the data decoding is impossible. */
    mutable bool          mValueDecodingFailed;

    mutable uint*          mPointCacheCoordinate;
    mutable T::ParamValue* mPointCacheValue;
    mutable uint           mPointCachePosition;

  public:

    enum SectionNumber
    {
      indicator_section = 0,
      identification_section = 1,
      local_section = 2,
      grid_section = 3,
      product_section = 4,
      representation_section = 5,
      bitmap_section = 6,
      data_section = 7,
      end_section = 8
    };
};





}  // namespace GRIB2
}  // namespace SmartMet

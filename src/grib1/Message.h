#pragma once

#include "grid/Message.h"
#include "grid/Coordinate.h"
#include "grid/Dimensions.h"
#include "grid/ValueCache.h"
#include "grid/Typedefs.h"
#include "common/MemoryReader.h"
#include "common/GeneralDefinitions.h"
#include "BitmapSection.h"
#include "DataSection.h"
#include "GridSection.h"
#include "ProductSection.h"
#include "IndicatorSection.h"

#include <boost/filesystem.hpp>
#include <boost/optional.hpp>


namespace SmartMet
{
namespace GRIB1
{

class GribFile;

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
                          Message(GribFile *gribFile);
    virtual               ~Message();

    // ### Common methods for all message types

    void                  getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    uint                  getFileId() const;
    T::FilePosition       getFilePosition() const;
    T::TimeString         getForecastStartTime() const;
    T::TimeString         getForecastEndTime() const;
    GribFile*             getGribFile() const;

    T::Coordinate_vec     getGridCoordinates() const;
    T::Dimensions_opt     getGridDimensions() const;
    void                  getGridLatlonAreaCoordinates(double& firstLat,double& firstLon,double& lastLat,double& lastLon) const;
    T::GridLayout         getGridLayout() const;
    std::size_t           getGridOriginalColumnCount() const;
    std::size_t           getGridOriginalColumnCount(std::size_t row) const;
    std::size_t           getGridOriginalRowCount() const;
    std::size_t           getGridOriginalValueCount() const;
    int                   getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    void                  getGridOriginalAreaCoordinates(double& x1,double& y1,double& x2,double& y2) const;
    bool                  getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                  getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    T::GridProjection     getGridProjection() const;
    void                  getGridProjectionAttributes(std::string prefix,T::AttributeList& attributeList) const;
    std::string           getGridProjectionString() const;
    T::ParamLevel         getParameterLevel() const;
    T::ParamLevelId       getParameterLevelId() const;
    std::string           getParameterLevelIdString() const;
    void                  getParameterMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const;
    void                  getParameterOriginalValues(T::ParamValue_vec& values) const;
    T::ParamValue         getParameterValueByGridPoint(uint grid_i,uint grid_j) const;
    T::ParamValue         getParameterValueByOriginalGridPoint(uint grid_i,uint grid_j) const;
    void                  getParameterValues(T::ParamValue_vec& values) const;
    T::TimeString         getReferenceTime() const;
    T::SpatialReference*  getSpatialReference() const;
    T::UInt8_opt          getTypeOfEnsembleForecast() const;
    T::UInt8_opt          getPerturbationNumber() const;
    std::string           getWKT() const;
    bool                  isGridGlobal() const;
    void                  print(std::ostream& stream,uint level,uint optionFlags) const;

    // ### Message/file type specific methods

    BitmapSection_sptr    getBitmapSection() const;
    GridSection_sptr      getGridSection() const;
    IndicatorSection_sptr getIndicatorSection() const;
    const ProductSection* getProductSection() const;
    const DataSection*    getDataSection() const;

    void                  read(MemoryReader& memoryReader);

    // Fast access to substructures

    T::Data_ptr           getBitmapDataPtr() const;
    std::size_t           getBitmapDataSizeInBytes() const;
    std::int16_t          getBinaryScaleFactor() const;
    std::uint16_t         getDecimalScaleFactor() const;
    std::float_t          getReferenceValue() const;
    std::uint8_t          getBitsPerValue() const;
    std::uint8_t          getFlags() const;
    T::Data_ptr           getDataPtr() const;
    std::size_t           getDataSize() const;
    std::size_t           getDataSizeMax() const;

  private:

    GribFile*             mGribFile;

    /*! \brief The message start position in the file. */
    T::FilePosition       mFilePosition;

    /*! \brief  A shared pointer to the IndicatorSection object. */
    IndicatorSection_sptr mIndicatorSection;

    /*! \brief  A shared pointer to the GridSection object. */
    GridSection_sptr      mGridSection;

    /*! \brief  An unique pointer to the ProductSection object. */
    ProductSection_uptr   mProductSection;

    /*! \brief  A shared pointer to the BitmapSection object. */
    BitmapSection_sptr    mBitmapSection;

    /*! \brief  An unique pointer to the DataSection object. */
    DataSection_uptr      mDataSection;

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
      product_section   = 1,
      grid_section      = 2,
      bitmap_section    = 3,
      data_section      = 4,
      end_section       = 5
    };
};


typedef std::shared_ptr<Message> Message_sptr;




}  // namespace GRIB1
}  // namespace SmartMet

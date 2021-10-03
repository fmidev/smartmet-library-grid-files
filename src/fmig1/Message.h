#pragma once

#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/GeneralDefinitions.h"
#include "../grid/Message.h"
#include "../grid/ValueCache.h"
#include "../grid/Typedefs.h"
#include "../grib1/Message.h"

#include <boost/filesystem.hpp>
#include <boost/optional.hpp>


namespace SmartMet
{
namespace FMIG1
{


/*
  --------------------------------------------------------------------------------------
  FMIG 1 Message
  --------------------------------------------------------------------------------------
  --------------------------------------------------------------------------------------
 */

class Message : public GRID::Message
{
  public:
                        Message();
                        Message(GRID::GridFile *gridFile,uint messageIndex,GRID::MessageInfo& messageInfo);
                        Message(const Message& other);
                ~Message() override;

    // ### Common methods for all message types

    void                getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const override;
    uint                getFileId() const override;
    uint                getProducerId() const override;
    uint                getGenerationId() const override;
    T::FilePosition     getFilePosition() const override;
    T::TimeString       getForecastTime() const override;
    time_t              getForecastTimeT() const override;
    short               getForecastType() const override;
    short               getForecastNumber() const override;

    uint                getTimeStepCount();
    uint                getGribVersion() const override;
    uint                getGribCentre() const override;
    uint                getGribSubCentre() const override;
    uint                getGribGeneratingProcessIdentifier() const override;
    uint                getGribTableVersion() const override;

    T::GeometryId       getGridGeometryId() const override;
    std::string         getGridGeometryString() const override;
    T::Dimensions       getGridDimensions() const override;
    T::Hash             getGridHash() const override;
    bool                getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight) override;
    T::Coordinate_svec  getGridLatLonCoordinates() const override;
    bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const override;
    bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const override;
    bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const override;
    T::GridLayout       getGridLayout() const override;
    bool                getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight) override;
    bool                getGridMetricCellSize(double& width,double& height) const override;
    bool                getGridMetricSize(double& width,double& height) const override;
    T::Coordinate_svec  getGridOriginalCoordinates() const override;
    bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const override;
    bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const override;
    bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const override;
    std::size_t         getGridOriginalColumnCount() const override;
    std::size_t         getGridOriginalColumnCount(std::size_t row) const override;
    std::size_t         getGridOriginalRowCount() const override;
    std::size_t         getGridOriginalValueCount() const override;
    int                 getGridOriginalValueIndex(uint grid_i,uint grid_j) const override;
    void                getGridOriginalValueVector(T::ParamValue_vec& values) const override;
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const override;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const override;
    T::GridProjection   getGridProjection() const override;
    std::string         getGridProjectionString() const override;
    T::ParamLevel       getGridParameterLevel() const override;
    T::ParamLevelId     getGridParameterLevelId() const override;
    std::string         getGridParameterLevelIdString() const override;
    void                getGridProjectionAttributes(const std::string& prefix,T::AttributeList& attributeList) const override;
    void                getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const override;
    T::ParamValue       getGridValueByGridPoint(uint grid_i,uint grid_j) const override;
    T::ParamValue       getGridValueByOriginalGridPoint(uint grid_i,uint grid_j) const override;
    void                getGridValueVector(T::ParamValue_vec& values) const override;
    T::TimeString       getReferenceTime() const override;
    T::SpatialRef*      getSpatialReference() const override;
    std::string         getWKT() const override;
    std::string         getProj4() const override;
    bool                isGridGlobal() const override;
    bool                isRelativeUV() const override;
    void                initSpatialReference() override;
    bool                reverseXDirection() const override;
    bool                reverseYDirection() const override;
    bool                isRead() override;
    void                read() override;
    void                read(MemoryReader& memoryReader) override;
    void                print(std::ostream& stream,uint level,uint optionFlags) const override;

  private:

    bool                getValueByIndex(uint index,T::ParamValue& value) const;

    /*! \brief Indicates if the message is already read. */
    bool                mIsRead;

    std::string         mReferenceTime;
    std::string         mForecastTime;
    time_t              mForecastTimeT;
    uint                mPixelCount;
    uint                mWidth;
    uint                mHeight;
    ushort              mForecastNumbers;
    uint                mTableIndex;
    uint                mValueIndex;
    short               mForecastType;
    short               mForecastNumber;
    uint                mTimeStepCount;
    T::AttributeList    mAttributeList;
    uint                mDataPosition;
    uint                mPixelSize;
    uint                mDataSize;
    uchar*              mDataStartPtr;
    uchar*              mDataEndPtr;

    GRIB1::GridDef_ptr  mGeometryDef;
};


using Message_sptr = std::shared_ptr<Message>;




}  // namespace GRIB1
}  // namespace SmartMet

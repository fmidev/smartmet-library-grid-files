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
    virtual             ~Message();

    // ### Common methods for all message types

    void                getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    uint                getFileId() const;
    uint                getProducerId() const;
    uint                getGenerationId() const;
    T::FilePosition     getFilePosition() const;
    T::TimeString       getForecastTime() const;
    time_t              getForecastTimeT() const;
    short               getForecastType() const;
    short               getForecastNumber() const;

    uint                getTimeStepCount();
    uint                getGribVersion() const;
    uint                getGribCentre() const;
    uint                getGribSubCentre() const;
    uint                getGribGeneratingProcessIdentifier() const;
    uint                getGribTableVersion() const;

    T::GeometryId       getGridGeometryId() const;
    std::string         getGridGeometryString() const;
    T::Dimensions       getGridDimensions() const;
    T::Hash             getGridHash() const;
    bool                getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    T::Coordinate_svec  getGridLatLonCoordinates() const;
    bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;
    bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;
    bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;
    //T::GridLayout       getGridLayout() const;
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
    bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;
    bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    T::GridProjection   getGridProjection() const;
    T::ParamLevel       getGridParameterLevel() const;
    T::ParamLevelId     getGridParameterLevelId() const;
    void                getGridProjectionAttributes(const std::string& prefix,T::AttributeList& attributeList) const;
    void                getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const;
    T::ParamValue       getGridValueByGridPoint(uint grid_i,uint grid_j) const;
    T::ParamValue       getGridValueByOriginalGridPoint(uint grid_i,uint grid_j) const;
    void                getGridValueVector(T::ParamValue_vec& values) const;
    T::TimeString       getReferenceTime() const;
    T::SpatialRef*      getSpatialReference() const;
    std::string         getWKT() const;
    std::string         getProj4() const;
    bool                isGridGlobal() const;
    bool                isRelativeUV() const;
    void                initSpatialReference();
    bool                reverseXDirection() const;
    bool                reverseYDirection() const;
    bool                isRead();
    void                read();
    void                read(MemoryReader& memoryReader);
    void                print(std::ostream& stream,uint level,uint optionFlags) const;

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


typedef std::shared_ptr<Message> Message_sptr;




}  // namespace GRIB1
}  // namespace SmartMet

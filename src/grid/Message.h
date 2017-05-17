#pragma once

#include "common/AttributeList.h"
#include "Coordinate.h"
#include "Dimensions.h"
#include "MessageSection.h"
#include "Typedefs.h"
#include "GridPointValue.h"
#include "GridPointValueList.h"

#include <vector>
#include <string>
#include <memory>


namespace SmartMet
{
namespace GRID
{


// ====================================================================================
/*!
  \brief This class is a parent class for all messages in different grid files. It
  defines the basic methods that all its child classes should implement.

  The basic idea is that we should be able to access all grid related data and
  information through this class (i.e. applications should not need to know any
  implementation details that are behind this interface).
*/
// ====================================================================================

class Message
{
  public:

                                  Message();
                                  Message(const Message& message);
    virtual                       ~Message();

    virtual void                  getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    virtual uint                  getFileId() const;
    virtual uint                  getMessageIndex() const;
    virtual T::FilePosition       getFilePosition() const;
    virtual T::TimeString         getForecastStartTime() const;
    virtual T::TimeString         getForecastEndTime() const;
    virtual void                  setMessageIndex(uint index);

    virtual T::ParamId            getFmiParameterId() const;
    virtual T::ParamLevelId       getFmiParameterLevelId() const;
    virtual std::string           getFmiParameterName() const;
    virtual std::string           getFmiParameterDescription() const;
    virtual std::string           getFmiParameterUnits() const;
    virtual T::ParamId            getGribParameterId() const;
    virtual std::string           getGribParameterName() const;
    virtual std::string           getGribParameterDescription() const;
    virtual std::string           getGribParameterUnits() const;
    virtual T::ParamLevelId       getGrib1ParameterLevelId() const;
    virtual T::ParamLevelId       getGrib2ParameterLevelId() const;
    virtual std::string           getCdmParameterId() const;
    virtual std::string           getCdmParameterName() const;
    virtual std::string           getNewbaseParameterId() const;
    virtual std::string           getNewbaseParameterName() const;

    virtual T::Coordinate_vec     getGridCoordinates() const;
    virtual T::Dimensions_opt     getGridDimensions() const;
    virtual void                  getGridLatlonAreaCoordinates(double& firstLat,double& firstLon,double& lastLat,double& lastLon) const;
    virtual T::GridLayout         getGridLayout() const;
    virtual std::size_t           getGridOriginalColumnCount(std::size_t row) const;
    virtual std::size_t           getGridOriginalColumnCount() const;
    virtual std::size_t           getGridOriginalRowCount() const;
    virtual std::size_t           getGridOriginalValueCount() const;
    virtual int                   getGridOriginalValueIndex(uint grid_i,uint grid_j) const;
    virtual void                  getGridOriginalAreaCoordinates(double& x1,double& y1,double& x2,double& y2) const;
    virtual bool                  getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const;
    virtual bool                  getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;
    virtual T::GridProjection     getGridProjection() const;
    virtual void                  getGridProjectionAttributes(std::string prefix,T::AttributeList& attributeList) const;
    virtual std::string           getGridProjectionString() const;
    virtual T::ParamLevel         getParameterLevel() const;
    virtual T::ParamLevelId       getParameterLevelId() const;
    virtual std::string           getParameterLevelIdString() const;
    virtual void                  getParameterMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const;
    virtual void                  getParameterOriginalValues(T::ParamValue_vec& values) const;
    virtual T::ParamValue         getParameterValueByGridPoint(uint grid_i,uint grid_j) const;
    virtual T::ParamValue         getParameterValueByOriginalGridPoint(uint grid_i,uint grid_j) const;
    virtual void                  getParameterValues(T::ParamValue_vec& values) const;
    T::ParamValue                 getParameterValueByGridPosition(double grid_i,double grid_j,T::InterpolationMethod interpolationMethod) const;
    T::ParamValue                 getParameterValueByGridPosition_nearest(double grid_i,double grid_j) const;
    T::ParamValue                 getParameterValueByGridPosition_linearInterpolation(double grid_i,double grid_j) const;
    T::ParamValue                 getParameterValueByLatLon(double lat,double lon,T::InterpolationMethod interpolationMethod) const;
    virtual void                  getParameterValuesByGridArea(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValue_vec& gridPointValues) const;
    virtual void                  getParameterValuesByGridArea(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValueList& gridPointValues) const;
    virtual T::TimeString         getReferenceTime() const;
    virtual T::SpatialReference*  getSpatialReference() const;
    virtual std::string           getWKT() const;
    virtual bool                  isGridGlobal() const;
    virtual void                  print(std::ostream& stream,uint level,uint optionFlags) const;

protected:

    /*! \brief  The index of the message in the file. */
    uint                  mMessageIndex;

    /*! \brief The grib parameter identifier. */
    T::ParamId            mGribParameterId;

    /*! \brief  The grib1 parameter level identifier. */
    T::ParamLevelId       mGrib1ParameterLevelId;

    /*! \brief  The grib2 parameter level identifier. */
    T::ParamLevelId       mGrib2ParameterLevelId;

    /*! \brief  The grib parameter name. */
    std::string           mGribParameterName;

    /*! \brief  The grib parameter description. */
    std::string           mGribParameterDescription;

    /*! \brief  The grib parameter units. */
    std::string           mGribParameterUnits;

    /*! \brief  The fmi parameter identifier.*/
    T::ParamId            mFmiParameterId;

    /*! \brief  The fmi parameter level identifier. */
    T::ParamLevelId       mFmiParameterLevelId;

    /*! \brief  The fmi parameter name. */
    std::string           mFmiParameterName;

    /*! \brief  The fmi parameter description. */
    std::string           mFmiParameterDescription;

    /*! \brief  The fmi parameter units. */
    std::string           mFmiParameterUnits;

    /*! \brief  The cdm parameter id string. */
    std::string           mCdmParameterId;

    /*! \brief  The cdm parameter name. */
    std::string           mCdmParameterName;

    /*! \brief  The newbase parameter id string. */
    std::string           mNewbaseParameterId;

    /*! \brief  The newbase parameter name. */
    std::string           mNewbaseParameterName;
};

}  // namespace GRID
}  // namespace SmartMet


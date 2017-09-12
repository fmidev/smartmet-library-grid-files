#pragma once

#include "common/MemoryReader.h"
#include "common/AttributeList.h"
#include "grib2/definition/ParameterSettings.h"
#include "grib2/definition/HorizontalSettings.h"
#include "grib2/definition/StatisticalSettings.h"
#include "grib2/definition/EpsSettings.h"


namespace SmartMet
{
namespace GRIB2
{

// Base class for product definitions

class ProductDefinition
{
  public:

                                        ProductDefinition();
    virtual                             ~ProductDefinition();

    virtual void                        getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    virtual T::TimeString               getForecastTime(T::TimeString referenceTime) const;
    virtual T::ParamLevel               getGribParameterLevel() const;
    virtual T::ParamLevelId             getGribParameterLevelId() const;
    virtual const T::UInt8_opt          getGribParameterCategory() const;
    virtual const T::UInt8_opt          getGribParameterNumber() const;
    virtual T::UInt8_opt                getGeneratingProcessIdentifier() const;
    virtual void                        print(std::ostream& stream,uint level,uint optionFlags) const;
    virtual void                        read(MemoryReader& memoryReader) {}

    // These methods are used for fetching information that is needed for the parameter
    // identification. The point is that we do not know which child classes contains this
    // information, so if the information is not present then we get NULL pointer.

    virtual const HorizontalSettings*   getHorizontal() const;
    virtual const ParameterSettings*    getParameter() const;
    virtual const StatisticalSettings*  getStatistical() const;
    virtual const EpsSettings*          getEps() const;

  protected:

    // These are helper methods used in child classes. The point is that there are
    // several child classes that need to do the same calculations.

    T::TimeString                       countForecastStartTime(T::TimeString referenceTime,const ParameterSettings& parameter) const;
    T::TimeString                       countForecastEndTime(const StatisticalSettings& stat) const;
};


typedef std::unique_ptr<ProductDefinition> ProductDefinition_uptr;

}  // namespace GRIB2
}  // namespace SmartMet

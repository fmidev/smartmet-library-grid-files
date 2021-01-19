#pragma once

#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/AttributeList.h"
#include "../grib2/definition/ParameterSettings.h"
#include "../grib2/definition/PostprocSettings.h"
#include "../grib2/definition/HorizontalSettings.h"
#include "../grib2/definition/StatisticalSettings.h"
#include "../grib2/definition/EpsSettings.h"
#include "../grib2/definition/DerivedSettings.h"
#include "../grib2/definition/RectangularClusterSettings.h"
#include "../grib2/definition/ProbabilitySettings.h"
#include "../grib2/definition/PercentileSettings.h"
#include "../grib2/definition/CategoricalSettings.h"

namespace SmartMet
{
namespace GRIB2
{

// Base class for product definitions

class ProductDefinition
{
  public:

                                        ProductDefinition();
                                        //ProductDefinition(const ProductDefinition& other);
    virtual                             ~ProductDefinition();

    virtual ProductDefinition*          createProductDefinition() const;

    virtual void                        getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    virtual T::TimeString               getForecastTime(T::TimeString referenceTime) const;
    virtual T::ParamLevel               getGribParameterLevel() const;
    virtual T::ParamLevelId             getGribParameterLevelId() const;
    virtual const T::UInt8_opt          getGribParameterCategory() const;
    virtual const T::UInt8_opt          getGribParameterNumber() const;
    virtual T::UInt8_opt                getGeneratingProcessIdentifier() const;
    virtual uint                        getTemplateNumber() const;

    virtual bool                        getProperty(uint propertyId,long long& value);
    virtual bool                        setProperty(uint propertyId,long long value);
    virtual void                        read(MemoryReader& memoryReader) {}
    virtual void                        write(DataWriter& dataWriter) {}
    virtual void                        print(std::ostream& stream,uint level,uint optionFlags) const;

    virtual HorizontalSettings*         getHorizontal() const;
    virtual ParameterSettings*          getParameter() const;
    virtual StatisticalSettings*        getStatistical() const;
    virtual EpsSettings*                getEps() const;
    virtual DerivedSettings*            getDerived() const;
    virtual RectangularClusterSettings* getRectangularCluster() const;
    virtual ProbabilitySettings*        getProbability() const;
    virtual PercentileSettings*         getPercentile() const;
    virtual CategoricalSettings*        getCategorical() const;
    virtual PostprocSettings*           getPostproc() const;


  protected:

    // These are helper methods used in child classes. The point is that there are
    // several child classes that need to do the same calculations.

    T::TimeString                       countForecastStartTime(T::TimeString referenceTime,const ParameterSettings& parameter) const;
    T::TimeString                       countForecastStartTime(T::TimeString referenceTime,const PostprocSettings& parameter) const;
    T::TimeString                       countForecastEndTime(const StatisticalSettings& stat) const;

    virtual bool                        getProperty_ParameterSettings(uint propertyId,long long& value);
    virtual bool                        getProperty_HorizontalSettings(uint propertyId,long long& value);
    virtual bool                        getProperty_StatisticalSettings(uint propertyId,long long& value);
    virtual bool                        getProperty_EpsSettings(uint propertyId,long long& value);
    virtual bool                        getProperty_DerivedSettings(uint propertyId,long long& value);
    virtual bool                        getProperty_RectangularClusterSettings(uint propertyId,long long& value);
    virtual bool                        getProperty_ProbabilitySettings(uint propertyId,long long& value);
    virtual bool                        getProperty_PercentileSettings(uint propertyId,long long& value);
    virtual bool                        getProperty_CategoricalSettings(uint propertyId,long long& value);

    virtual bool                        setProperty_ParameterSettings(uint propertyId,long long value);
    virtual bool                        setProperty_HorizontalSettings(uint propertyId,long long value);
    virtual bool                        setProperty_StatisticalSettings(uint propertyId,long long value);
    virtual bool                        setProperty_EpsSettings(uint propertyId,long long value);
    virtual bool                        setProperty_DerivedSettings(uint propertyId,long long value);
    virtual bool                        setProperty_RectangularClusterSettings(uint propertyId,long long value);
    virtual bool                        setProperty_ProbabilitySettings(uint propertyId,long long value);
    virtual bool                        setProperty_PercentileSettings(uint propertyId,long long value);
    virtual bool                        setProperty_CategoricalSettings(uint propertyId,long long value);

};


typedef std::shared_ptr<ProductDefinition> ProductDefinition_sptr;



}  // namespace GRIB2
}  // namespace SmartMet

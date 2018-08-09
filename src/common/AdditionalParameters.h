// ======================================================================
/*!
 * \brief Additional parameters
 */
// ======================================================================

#pragma once

#include <macgyver/TimeZones.h>
#include <macgyver/TimeFormatter.h>
#include <macgyver/TimeZoneFactory.h>
#include <spine/TimeSeriesGenerator.h>
#include <spine/ValueFormatter.h>
#include <spine/Location.h>



namespace SmartMet
{

class AdditionalParameters
{
  public:
                AdditionalParameters(
                    const Fmi::TimeZones& timezones,
                    const std::locale& locale,
                    const Fmi::TimeFormatter& timeFormatter,
                    const Spine::ValueFormatter& valueFormatter);

    virtual     ~AdditionalParameters();

    bool        isAdditionalParameter(const char *parameterName);

    bool        getParameterValueByLocation(
                    std::string parameterName,
                    std::string tag,
                    Spine::LocationPtr loc,
                    std::string country,
                    int precision,
                    std::string& value);

    bool        getParameterValueByLocationAndTime(
                    std::string parameterName,
                    std::string tag,
                    Spine::LocationPtr loc,
                    boost::local_time::local_date_time localTime,
                    boost::local_time::time_zone_ptr tz,
                    int precision,
                    std::string& value);

  private:

    std::string formatDate(
                    boost::local_time::local_date_time& ldt,
                    std::locale& llocale,
                    const char *fmt);

    std::string formatDate(
                    boost::local_time::local_date_time& ldt,
                    std::locale& llocale,
                    std::string fmt);

    const Fmi::TimeZones&         mTimezones;
    std::locale                   mLocale;
    const Fmi::TimeFormatter&     mTimeFormatter;
    const Spine::ValueFormatter&  mValueFormatter;

};

}  // namespace SmartMet

// ======================================================================

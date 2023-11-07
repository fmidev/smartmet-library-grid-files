// ======================================================================
/*!
 * \brief Additional parameters
 */
// ======================================================================

#pragma once

#include <macgyver/TimeZones.h>
#include <macgyver/TimeFormatter.h>
#include <macgyver/TimeZoneFactory.h>
#include <macgyver/ValueFormatter.h>
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
                    const Fmi::ValueFormatter& valueFormatter);

    virtual     ~AdditionalParameters();

    static bool isAdditionalParameter(const char *parameterName);

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
                    Fmi::LocalDateTime localTime,
                    Fmi::TimeZonePtr tz,
                    int precision,
                    std::string& value);

  private:

    std::string formatDate(
                    Fmi::LocalDateTime& ldt,
                    std::locale& llocale,
                    const char *fmt);

    std::string formatDate(
                    Fmi::LocalDateTime& ldt,
                    std::locale& llocale,
                    std::string fmt);

    const Fmi::TimeZones&         mTimezones;
    std::locale                   mLocale;
    const Fmi::TimeFormatter&     mTimeFormatter;
    const Fmi::ValueFormatter&  mValueFormatter;

};

}  // namespace SmartMet

// ======================================================================

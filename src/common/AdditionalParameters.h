// ======================================================================
/*! \brief Resolver for location- and time-based derived parameters.
 *
 *  Computes values such as formatted time strings, locale-aware date
 *  representations, and country names that depend on a geographic location
 *  and/or a timestamp rather than grid data. */
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
    /*! \brief Construct with the locale and formatting helpers needed to compute derived parameters.
     *  \param[in] timezones      Available time zone data.
     *  \param[in] locale         Locale for date/number formatting.
     *  \param[in] timeFormatter  Formats time values as strings.
     *  \param[in] valueFormatter Formats numeric values as strings. */
                AdditionalParameters(
                    const Fmi::TimeZones& timezones,
                    const std::locale& locale,
                    const Fmi::TimeFormatter& timeFormatter,
                    const Fmi::ValueFormatter& valueFormatter);

    virtual     ~AdditionalParameters();

    /*! \brief Return true if \p parameterName is handled by this class.
     *  \param[in] parameterName  Parameter name to test. */
    static bool isAdditionalParameter(const char *parameterName);

    /*! \brief Compute a location-based derived parameter value.
     *  \param[in]  parameterName  Name of the parameter to compute.
     *  \param[in]  tag            Output tag or unit modifier.
     *  \param[in]  loc            Geographic location.
     *  \param[in]  country        ISO country code for country-name parameters.
     *  \param[in]  precision      Decimal precision for formatted numbers.
     *  \param[out] value          Receives the computed value string.
     *  \return True if the parameter was computed successfully. */
    bool        getParameterValueByLocation(
                    std::string parameterName,
                    std::string tag,
                    Spine::LocationPtr loc,
                    std::string country,
                    int precision,
                    std::string& value);

    /*! \brief Compute a location- and time-based derived parameter value.
     *  \param[in]  parameterName  Name of the parameter to compute.
     *  \param[in]  tag            Output tag or unit modifier.
     *  \param[in]  loc            Geographic location.
     *  \param[in]  localTime      Local time at the location.
     *  \param[in]  tz             Time zone for the location.
     *  \param[in]  precision      Decimal precision for formatted numbers.
     *  \param[out] value          Receives the computed value string.
     *  \return True if the parameter was computed successfully. */
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

    const Fmi::TimeZones&         mTimezones;      //!< Available time zone data
    std::locale                   mLocale;          //!< Locale for formatting
    const Fmi::TimeFormatter&     mTimeFormatter;   //!< Time-to-string formatter
    const Fmi::ValueFormatter&    mValueFormatter;  //!< Number-to-string formatter

};

}  // namespace SmartMet

// ======================================================================

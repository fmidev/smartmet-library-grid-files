#include "AdditionalParameters.h"
#include "GeneralFunctions.h"
#include "ShowFunction.h"

#include <macgyver/StringConversion.h>
#include <macgyver/TimeParser.h>
#include <macgyver/Astronomy.h>
#include <macgyver/CharsetTools.h>

#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{


AdditionalParameters::AdditionalParameters(
    const Fmi::TimeZones& timezones,
    const std::locale& locale,
    const Fmi::TimeFormatter& timeFormatter,
    const Spine::ValueFormatter& valueFormatter
):
    mTimezones(timezones),
    mLocale(locale),
    mTimeFormatter(timeFormatter),
    mValueFormatter(valueFormatter)
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





AdditionalParameters::~AdditionalParameters()
{
  FUNCTION_TRACE
}





bool AdditionalParameters::isAdditionalParameter(const char *parameterName)
{
  const char *buildInParameter[] = {
    "place",
    "name",
    "iso2",
    "geoid",
    "country",
    "countryname",
    "feature",
    "latitude",
    "lat",
    "longitude",
    "lon",
    "latlon",
    "lonlat",
    "population",
    "elevation",
    "dem",
    "region",
    "time",
    "utctime",
    "tz",
    "localtz",
    "localtime",
    "isotime",
    "xmltime",
    "epochtime",
    "sunelevation",
    "sundeclination",
    "sunatzimuth",
    "dark",
    "moonphase",
    "moonrise",
    "moonrise2",
    "moonset",
    "moonset2",
    "moonrisetoday",
    "moonrise2today",
    "moonsettoday",
    "moonset2today",
    "moonup24h",
    "moondown24h",
    "sunrise",
    "sunset",
    "noon",
    "sunrisetoday",
    "sunsettoday",
    "daylength",
    "wday",
    "weekday",
    "mon",
    "month",
    "hour",
    "level",
    "model",
    "producer",
    "covertype",
    nullptr
  };

  uint c = 0;
  while (buildInParameter[c] != nullptr)
  {
    if (strcasecmp(buildInParameter[c],parameterName) == 0)
      return true;

    c++;
  }
  return false;
}





bool AdditionalParameters::getParameterValueByLocation(
    std::string parameterName,
    std::string tag,
    Spine::LocationPtr loc,
    std::string country,
    int precision,
    std::string& value)
{
  FUNCTION_TRACE
  try
  {
    int def_coordinatePrecision = 6;
    std::string param = toLowerString(parameterName);

    if (param == "place")
    {
      value = tag;
      //value = loc->name;
      return true;
    }

    if (param == "name")
    {
      value = loc->name;
      return true;
    }

    if (param == "iso2")
    {
      value = loc->iso2;
      return true;
    }

    if (param == "geoid")
    {
      value = Fmi::to_string(loc->geoid);
      return true;
    }

    if (param == "country")
    {
      if (country > " ")
        value = country;
      else
        value = loc->country;
      return true;
    }

    if (param == "countryname")
    {
      value = loc->country;
      return true;
    }

    if (param == "feature")
    {
      value = loc->feature;
      return true;
    }

    if (param == "latitude" || param == "lat")
    {
      if (precision >= 0)
        value = mValueFormatter.format(loc->latitude, precision);
      else
        value = mValueFormatter.format(loc->latitude, def_coordinatePrecision);
      return true;
    }

    if (param == "longitude" || param == "lon")
    {
      if (precision >= 0)
        value = mValueFormatter.format(loc->longitude, precision);
      else
        value = mValueFormatter.format(loc->longitude, def_coordinatePrecision);
      return true;
    }

    if (param == "latlon")
    {
      if (precision >= 0)
        value = mValueFormatter.format(loc->latitude, precision) + ", " + mValueFormatter.format(loc->longitude, precision);
      else
        value = mValueFormatter.format(loc->latitude, precision) + ", " + mValueFormatter.format(loc->longitude, def_coordinatePrecision);
      return true;
    }

    if (param == "lonlat")
    {
      if (precision >= 0)
        value = mValueFormatter.format(loc->longitude, precision) + ", " + mValueFormatter.format(loc->latitude, precision);
      else
        value = mValueFormatter.format(loc->longitude, precision) + ", " + mValueFormatter.format(loc->latitude, def_coordinatePrecision);
      return true;
    }

    if (param == "population")
    {
      value = Fmi::to_string(loc->population);
      return true;
    }

    if (param == "covertype")
    {
      value = Fmi::to_string(loc->covertype);
      return true;
    }

    if (param == "elevation")
    {
      //value = mValueFormatter.format(loc->elevation,precision);
      if (std::isnan(loc->elevation))
        value = "nan";
      else
        value = Fmi::to_string(loc->elevation);
      return true;
    }

    if (param == "dem")
    {
      value = mValueFormatter.format(loc->dem, precision);
      return true;
    }

    if (param == "region")
    {
      if (loc->area.empty())
      {
        if (loc->name.empty())
        {
          value = mValueFormatter.missing();
          return true;
        }
        else
        {
          value = loc->name;
          return true;
        }
      }
      else
      {
        value = loc->area;
        return true;
      }
      return false;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





bool AdditionalParameters::getParameterValueByLocationAndTime(
    std::string parameterName,
    std::string tag,
    Spine::LocationPtr loc,
    boost::local_time::local_date_time queryTime,
    boost::local_time::time_zone_ptr tz,
    int precision,
    std::string& value)
{
  FUNCTION_TRACE
  try
  {
    std::string param = toLowerString(parameterName);

    if (param == "time")
    {
      value = mTimeFormatter.format(queryTime);
      return true;
    }

    if (param == "utctime")
    {
      value = mTimeFormatter.format(queryTime.utc_time());
      return true;
    }

    if (param == "tz")
    {
      value = tz->std_zone_abbrev();
      return true;
    }

    if (param == "localtz")
    {
      value = loc->timezone;
      return true;
    }

    if (param == "localtime")
    {
      boost::local_time::time_zone_ptr localtz = mTimezones.time_zone_from_string(loc->timezone);
      boost::local_time::local_date_time lTime(queryTime.utc_time(),localtz);
      value = mTimeFormatter.format(lTime);
      return true;
    }

    if (param == "isotime")
    {
      value = Fmi::to_iso_string(queryTime.local_time());
      return true;
    }

    if (param == "xmltime")
    {
      value = Fmi::to_iso_extended_string(queryTime.local_time());
      return true;
    }

    if (param == "epochtime")
    {
      boost::posix_time::ptime time_t_epoch(boost::gregorian::date(1970, 1, 1));
      boost::posix_time::time_duration diff = queryTime.utc_time() - time_t_epoch;
      value = Fmi::to_string(diff.total_seconds());
      return true;
    }

    if (param == "sunelevation")
    {
      Fmi::Astronomy::solar_position_t sp = Fmi::Astronomy::solar_position(queryTime,loc->longitude, loc->latitude);
      value = mValueFormatter.format(sp.elevation,precision);
      return true;
    }

    if (param == "sundeclination")
    {
      Fmi::Astronomy::solar_position_t sp = Fmi::Astronomy::solar_position(queryTime, loc->longitude, loc->latitude);
      value = mValueFormatter.format(sp.declination,precision);
      return true;
    }

    if (param == "sunatzimuth")
    {
      Fmi::Astronomy::solar_position_t sp = Fmi::Astronomy::solar_position(queryTime, loc->longitude, loc->latitude);
      value = mValueFormatter.format(sp.azimuth,precision);
      return true;
    }

    if (param == "dark")
    {
      Fmi::Astronomy::solar_position_t sp = Fmi::Astronomy::solar_position(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_string(sp.dark());
      return true;
    }

    if (param == "moonphase")
    {
      value = mValueFormatter.format(Fmi::Astronomy::moonphase(queryTime.utc_time()),precision);
      return true;
    }

    if (param == "moonrise")
    {
      Fmi::Astronomy::lunar_time_t lt = Fmi::Astronomy::lunar_time(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_iso_string(lt.moonrise.local_time());
      return true;
    }

    if (param == "moonrise2")
    {
      Fmi::Astronomy::lunar_time_t lt = Fmi::Astronomy::lunar_time(queryTime, loc->longitude, loc->latitude);

      if (lt.moonrise2_today())
        value = Fmi::to_iso_string(lt.moonrise2.local_time());
      else
        value = std::string("");

      return true;
    }

    if (param == "moonset")
    {
      Fmi::Astronomy::lunar_time_t lt = Fmi::Astronomy::lunar_time(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_iso_string(lt.moonset.local_time());
      return true;
    }

    if (param == "moonset2")
    {
      Fmi::Astronomy::lunar_time_t lt = Fmi::Astronomy::lunar_time(queryTime, loc->longitude, loc->latitude);

      if (lt.moonset2_today())
        value = Fmi::to_iso_string(lt.moonset2.local_time());
      else
        value = std::string("");

      return true;
    }

    if (param == "moonrisetoday")
    {
      Fmi::Astronomy::lunar_time_t lt = Fmi::Astronomy::lunar_time(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_string(lt.moonrise_today());
      return true;
    }

    if (param == "moonrise2today")
    {
      Fmi::Astronomy::lunar_time_t lt = Fmi::Astronomy::lunar_time(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_string(lt.moonrise2_today());
      return true;
    }

    if (param == "moonsettoday")
    {
      Fmi::Astronomy::lunar_time_t lt = Fmi::Astronomy::lunar_time(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_string(lt.moonset_today());
      return true;
    }

    if (param == "moonset2today")
    {
      Fmi::Astronomy::lunar_time_t lt = Fmi::Astronomy::lunar_time(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_string(lt.moonset2_today());
      return true;
    }

    if (param == "moonup24h")
    {
      Fmi::Astronomy::lunar_time_t lt = Fmi::Astronomy::lunar_time(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_string(lt.above_horizont_24h());
      return true;
    }

    if (param == "moondown24h")
    {
      Fmi::Astronomy::lunar_time_t lt = Fmi::Astronomy::lunar_time(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_string(!lt.moonrise_today() && !lt.moonset_today() && !lt.above_horizont_24h());
      return true;
    }

    if (param == "sunrise")
    {
      Fmi::Astronomy::solar_time_t st = Fmi::Astronomy::solar_time(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_iso_string(st.sunrise.local_time());
      return true;
    }

    if (param == "sunset")
    {
      Fmi::Astronomy::solar_time_t st = Fmi::Astronomy::solar_time(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_iso_string(st.sunset.local_time());
      return true;
    }

    if (param == "noon")
    {
      Fmi::Astronomy::solar_time_t st = Fmi::Astronomy::solar_time(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_iso_string(st.noon.local_time());
      return true;
    }

    if (param == "sunrisetoday")
    {
      Fmi::Astronomy::solar_time_t st = Fmi::Astronomy::solar_time(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_string(st.sunrise_today());
      return true;
    }

    if (param == "sunsettoday")
    {
      Fmi::Astronomy::solar_time_t st = Fmi::Astronomy::solar_time(queryTime, loc->longitude, loc->latitude);
      value = Fmi::to_string(st.sunset_today());
      return true;
    }

    if (param == "daylength")
    {
      Fmi::Astronomy::solar_time_t st = Fmi::Astronomy::solar_time(queryTime, loc->longitude, loc->latitude);
      auto seconds = st.daylength().total_seconds();
      auto minutes = boost::numeric_cast<long>(round(seconds / 60.0));
      value = Fmi::to_string(minutes);
      return true;
    }

    if (param == "wday")
    {
      value = formatDate(queryTime, mLocale, "%a");
      return true;
    }

    if (param == "weekday")
    {
      value = formatDate(queryTime, mLocale, "%A");
      return true;
    }

    if (param == "mon")
    {
      value = formatDate(queryTime, mLocale, "%b");
      return true;
    }

    if (param == "month")
    {
      value = formatDate(queryTime, mLocale, "%B");
      return true;
    }

    if (param == "hour")
    {
      value = Fmi::to_string(queryTime.local_time().time_of_day().hours());
      return true;
    }

    if (param.substr(0, 5) == "date(" && param[param.size() - 1] == ')')
    {
      value = formatDate(queryTime, mLocale, parameterName.substr(5, param.size() - 6));
      return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





std::string AdditionalParameters::formatDate(
    boost::local_time::local_date_time& ldt,
    std::locale& llocale,
    const char *fmt)
{
  FUNCTION_TRACE
  try
  {
    typedef boost::date_time::time_facet<boost::local_time::local_date_time, char> tfacet;
    std::ostringstream os;
    os.imbue(std::locale(llocale, new tfacet(fmt)));
    os << ldt;
    return Fmi::latin1_to_utf8(os.str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}





std::string AdditionalParameters::formatDate(
    boost::local_time::local_date_time& ldt,
    std::locale& llocale,
    std::string fmt)
{
  FUNCTION_TRACE
  try
  {
    return formatDate(ldt,llocale,fmt.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

}  // namespace SmartMet







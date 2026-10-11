// The toInt32/toUInt32/toDouble etc. conversions behave like atoi/atof:
// leading whitespace is skipped, the numeric prefix is used and the rest of
// the string is ignored. Grid code relies on this, for example "2500.000000"
// read as an integer, "4CloudType" giving 4 and the first element of a comma
// separated list. These tests pin that behaviour.

#define BOOST_TEST_MODULE NumberConversionTest
#include <boost/test/included/unit_test.hpp>

#include "../src/common/GeneralFunctions.h"

#include <limits>

using namespace SmartMet;

BOOST_AUTO_TEST_CASE(integers)
{
  BOOST_CHECK_EQUAL(toInt32("42"), 42);
  BOOST_CHECK_EQUAL(toInt32("-42"), -42);
  BOOST_CHECK_EQUAL(toInt32("+7"), 7);
  BOOST_CHECK_EQUAL(toInt32("  12"), 12);
  BOOST_CHECK_EQUAL(toInt64("9007199254740993"), 9007199254740993LL);
  BOOST_CHECK_EQUAL(toUInt64("18446744073709551615"), std::numeric_limits<UInt64>::max());
  BOOST_CHECK_EQUAL(toInt16("-32768"), -32768);
  BOOST_CHECK_EQUAL(toUInt8("255"), 255);
}

BOOST_AUTO_TEST_CASE(numeric_prefix)
{
  BOOST_CHECK_EQUAL(toInt32("2500.000000"), 2500);
  BOOST_CHECK_EQUAL(toInt32("4CloudType"), 4);
  BOOST_CHECK_EQUAL(toInt32("5,1125,1080"), 5);
  BOOST_CHECK_EQUAL(toInt32("RRC-KGM2"), 0);
  BOOST_CHECK_CLOSE(toDouble("1.5x"), 1.5, 1e-12);
  BOOST_CHECK_EQUAL(toDouble("description"), 0.0);
}

BOOST_AUTO_TEST_CASE(blank_is_zero)
{
  BOOST_CHECK_EQUAL(toInt32(""), 0);
  BOOST_CHECK_EQUAL(toInt32("   "), 0);
  BOOST_CHECK_EQUAL(toInt32(static_cast<const char *>(nullptr)), 0);
  BOOST_CHECK_EQUAL(toUInt32(""), 0U);
  BOOST_CHECK_EQUAL(toDouble(""), 0.0);
}

BOOST_AUTO_TEST_CASE(negative_wraps_into_unsigned_sentinel)
{
  BOOST_CHECK_EQUAL(toUInt32("-1"), 0xFFFFFFFFU);
  BOOST_CHECK_EQUAL(toUInt8("-1"), 255);
}

BOOST_AUTO_TEST_CASE(floating_point)
{
  BOOST_CHECK_CLOSE(toDouble("1.25"), 1.25, 1e-12);
  BOOST_CHECK_CLOSE(toDouble(" -3e2"), -300.0, 1e-12);
  BOOST_CHECK_CLOSE(toFloat("0.5"), 0.5F, 1e-6);
}

BOOST_AUTO_TEST_CASE(time_periods)
{
  BOOST_CHECK_EQUAL(timePeriodToSeconds("30s"), 30);
  BOOST_CHECK_EQUAL(timePeriodToSeconds("5m"), 300);
  BOOST_CHECK_EQUAL(timePeriodToSeconds("2h"), 7200);
  BOOST_CHECK_EQUAL(timePeriodToSeconds("1d"), 86400);
  BOOST_CHECK_EQUAL(timePeriodToSeconds("10"), 600);
}

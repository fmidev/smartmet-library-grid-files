// getIsolines/getIsobands contour in grid coordinates when no coordinate vector is given
// (contour.coordinateType = GRID_COORDINATES), and refuse a coordinate vector whose size
// does not match the grid.

#define BOOST_TEST_MODULE ContourTest
#include <boost/test/included/unit_test.hpp>
#include <cstddef>
#include <vector>
#include "../src/common/GraphFunctions.h"
#include "../src/common/Coordinate.h"
#include "../src/common/Typedefs.h"

using namespace SmartMet;

namespace
{
const int width = 6;
const int height = 5;

// Values increase from 0 to 10 along the x axis
std::vector<float> gradient()
{
  std::vector<float> values;
  for (int j = 0; j < height; j++)
    for (int i = 0; i < width; i++)
      values.push_back(2.0F * static_cast<float>(i));
  return values;
}

std::vector<T::Coordinate> lonlats(std::size_t count)
{
  std::vector<T::Coordinate> coordinates;
  for (std::size_t n = 0; n < count; n++)
  {
    std::size_t row = n / width;
    coordinates.emplace_back(20.0 + static_cast<double>(n % width), 60.0 + static_cast<double>(row));
  }
  return coordinates;
}

std::size_t nonEmpty(const T::ByteData_vec& contours)
{
  std::size_t count = 0;
  for (const auto& contour : contours)
    if (!contour.empty())
      count++;
  return count;
}

T::ByteData_vec isolines(std::vector<T::Coordinate>* coordinates)
{
  auto values = gradient();
  std::vector<float> limits{3, 5, 7};
  T::ByteData_vec contours;
  getIsolines(values, coordinates, width, height, limits, 0, 0, 0, contours);
  return contours;
}

T::ByteData_vec isobands(std::vector<T::Coordinate>* coordinates)
{
  auto values = gradient();
  std::vector<float> low{0, 4};
  std::vector<float> high{4, 8};
  T::ByteData_vec contours;
  getIsobands(values, coordinates, width, height, low, high, 0, 0, 0, contours);
  return contours;
}
}  // namespace

BOOST_AUTO_TEST_CASE(isolines_in_grid_coordinates)
{
  BOOST_CHECK_EQUAL(nonEmpty(isolines(nullptr)), 3U);
}

BOOST_AUTO_TEST_CASE(isobands_in_grid_coordinates)
{
  BOOST_CHECK_EQUAL(nonEmpty(isobands(nullptr)), 2U);
}

BOOST_AUTO_TEST_CASE(contours_with_coordinates)
{
  auto coordinates = lonlats(width * height);
  BOOST_CHECK_EQUAL(nonEmpty(isolines(&coordinates)), 3U);
  BOOST_CHECK_EQUAL(nonEmpty(isobands(&coordinates)), 2U);
}

BOOST_AUTO_TEST_CASE(coordinate_count_mismatch)
{
  auto coordinates = lonlats(width * height - 1);
  BOOST_CHECK(isolines(&coordinates).empty());
  BOOST_CHECK(isobands(&coordinates).empty());
}

// With closedRange the last isoband includes its upper limit: a field at the limit is inside
BOOST_AUTO_TEST_CASE(isobands_closed_range)
{
  std::vector<float> values(width * height, 10.0F);
  std::vector<float> low{8};
  std::vector<float> high{10};
  T::ByteData_vec open;
  getIsobands(values, nullptr, width, height, low, high, 0, 0, 0, open);
  BOOST_CHECK_EQUAL(nonEmpty(open), 0U);

  T::ByteData_vec closed;
  ContourOptions options;
  options.closedRange = true;
  getIsobands(values, nullptr, width, height, low, high, 0, closed, options);
  BOOST_CHECK_EQUAL(nonEmpty(closed), 1U);
}

BOOST_AUTO_TEST_CASE(contour_options_from_attributes)
{
  T::AttributeList attributes;
  attributes.addAttribute("contour.subdivide", "4");
  attributes.addAttribute("contour.threads", "2");
  attributes.addAttribute("contour.extrapolation", "3");
  attributes.addAttribute("contour.closedRange", "1");
  attributes.addAttribute("contour.strict", "1");
  attributes.addAttribute("contour.validate", "1");
  attributes.addAttribute("contour.desliver", "1");
  attributes.addAttribute("contour.smooth.method", "box");
  attributes.addAttribute("contour.smooth.radius", "2");
  auto options = getContourOptions(attributes);
  BOOST_CHECK_EQUAL(options.subdivide, 4);
  BOOST_CHECK_EQUAL(options.threads, 2);
  BOOST_CHECK_EQUAL(options.extrapolation, 3);
  BOOST_CHECK(options.closedRange && options.strict && options.validate && options.desliver);
  BOOST_CHECK(options.smoothOptions.active());

  auto defaults = getContourOptions(T::AttributeList());
  BOOST_CHECK_EQUAL(defaults.subdivide, 0);
  BOOST_CHECK_EQUAL(defaults.threads, 1);
  BOOST_CHECK_EQUAL(defaults.extrapolation, 0);
  BOOST_CHECK(!defaults.closedRange && !defaults.strict && !defaults.validate && !defaults.desliver);
  BOOST_CHECK(!defaults.smoothOptions.active());
}

// Extrapolation fills missing cells next to the data: the band reaches into the missing column
BOOST_AUTO_TEST_CASE(isobands_extrapolation)
{
  auto values = gradient();  // 0 2 4 6 8 10 per row
  for (int j = 0; j < height; j++)
    values[j * width + width - 1] = ParamValueMissing;
  const auto original = values;
  std::vector<float> low{7};
  std::vector<float> high{100};

  ContourOptions options;
  T::ByteData_vec plain;
  getIsobands(values, nullptr, width, height, low, high, 0, plain, options);

  options.extrapolation = 1;
  T::ByteData_vec extrapolated;
  getIsobands(values, nullptr, width, height, low, high, 0, extrapolated, options);

  BOOST_REQUIRE_EQUAL(nonEmpty(plain), 1U);
  BOOST_REQUIRE_EQUAL(nonEmpty(extrapolated), 1U);
  BOOST_CHECK(plain[0] != extrapolated[0]);
  BOOST_CHECK(values == original);  // the caller's data is not modified
}

// The contour checks are passed to Trax without changing a simple result
BOOST_AUTO_TEST_CASE(contour_checks)
{
  auto values = gradient();
  std::vector<float> low{0, 4};
  std::vector<float> high{4, 8};
  ContourOptions options;
  options.strict = true;
  options.validate = true;
  options.desliver = true;
  T::ByteData_vec contours;
  getIsobands(values, nullptr, width, height, low, high, 0, contours, options);
  BOOST_CHECK_EQUAL(nonEmpty(contours), 2U);
}

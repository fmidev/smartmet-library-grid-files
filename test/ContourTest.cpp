// getIsolines/getIsobands contour in grid coordinates when no coordinate vector is given
// (contour.coordinateType = GRID_COORDINATES), and refuse a coordinate vector whose size
// does not match the grid.

#define BOOST_TEST_MODULE ContourTest
#include <boost/test/included/unit_test.hpp>

#include "../src/common/GraphFunctions.h"

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

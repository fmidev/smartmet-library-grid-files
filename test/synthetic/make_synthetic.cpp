// Generator for the synthetic GRIB fixtures in this directory.
//
// Each case is a tiny single-message GRIB file built from an ecCodes sample, covering the grid
// types and packing methods grid-files supports. Next to every NAME.grib the generator writes
// NAME.ref, the field decoded by ecCodes itself:
//
//   # key=value             metadata lines (gridType, Ni, Nj, packingType, ...)
//   index lat lon value     one line per grid point in storage order (value "nan" = missing)
//
// GribDecodeTest compares grid-files against these files, so the reference is an independent
// decoder and not grid-files checking itself.
//
// The generated files are committed; the generator is only needed when adding cases. It needs
// eccodes-devel, which is why it is not built by "make test":
//
//   make -C test synthetic

#include <eccodes.h>
#include <fmt/format.h>

#include <cmath>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace
{
using Value = std::variant<long, double, std::string, std::vector<long>>;

struct Key
{
  std::string name;
  Value value;
};

struct Case
{
  std::string name;
  std::string sample;
  std::vector<Key> keys;     // set in order, before the values
  std::string packingType;   // empty = keep the sample packing
  long bitsPerValue = 16;
  bool bitmap = false;       // set every 7th value missing
};

void check(int err, const std::string &what)
{
  if (err != 0)
    throw std::runtime_error(fmt::format("{}: {}", what, codes_get_error_message(err)));
}

void set(codes_handle *h, const Key &k)
{
  const char *n = k.name.c_str();
  if (const auto *l = std::get_if<long>(&k.value))
    check(codes_set_long(h, n, *l), k.name);
  else if (const auto *d = std::get_if<double>(&k.value))
    check(codes_set_double(h, n, *d), k.name);
  else if (const auto *s = std::get_if<std::string>(&k.value))
  {
    size_t len = s->size();
    check(codes_set_string(h, n, s->c_str(), &len), k.name);
  }
  else
  {
    const auto &v = std::get<std::vector<long>>(k.value);
    check(codes_set_long_array(h, n, v.data(), v.size()), k.name);
  }
}

std::string getString(codes_handle *h, const char *key)
{
  char buf[256];
  size_t len = sizeof(buf);
  if (codes_get_string(h, key, buf, &len) != 0)
    return "";
  return buf;
}

// Smooth but non-symmetric test field, so that flipped or transposed decoding shows up
double field(size_t i, size_t n)
{
  const double x = static_cast<double>(i) / static_cast<double>(n);
  return 250.0 + 40.0 * x + 7.5 * std::sin(0.37 * static_cast<double>(i)) +
         0.01 * static_cast<double>(i % 13);
}

void generate(const Case &c, const std::string &dir)
{
  codes_handle *h = codes_grib_handle_new_from_samples(nullptr, c.sample.c_str());
  if (h == nullptr)
    throw std::runtime_error("no ecCodes sample " + c.sample);

  long nx = 0;
  long ny = 0;
  for (const auto &k : c.keys)
  {
    set(h, k);
    if (k.name == "Ni" || k.name == "Nx" || k.name == "numberOfPointsAlongXAxis")
      nx = std::get<long>(k.value);
    if (k.name == "Nj" || k.name == "Ny" || k.name == "numberOfPointsAlongYAxis")
      ny = std::get<long>(k.value);
    if (k.name == "pl")
    {
      nx = 0;
      for (long count : std::get<std::vector<long>>(k.value))
        nx += count;
      ny = 1;
    }
  }

  // GRIB2 does not derive the point count from the grid dimensions
  long edition = 0;
  check(codes_get_long(h, "edition", &edition), "edition");
  if (edition == 2 && nx > 0 && ny > 0)
    check(codes_set_long(h, "numberOfDataPoints", nx * ny), "numberOfDataPoints");

  // The coded value count still describes the sample grid, use the new grid size
  long points = 0;
  check(codes_get_long(h, "numberOfDataPoints", &points), "numberOfDataPoints");
  const auto n = static_cast<size_t>(points);

  std::vector<double> values(n);
  for (size_t i = 0; i < n; i++)
    values[i] = field(i, n);

  if (c.bitmap)
  {
    const double missing = 9999;
    check(codes_set_double(h, "missingValue", missing), "missingValue");
    check(codes_set_long(h, "bitmapPresent", 1), "bitmapPresent");
    for (size_t i = 0; i < n; i += 7)
      values[i] = missing;
  }

  // Set the values with the sample packing first, then repack: changing the packing of a
  // constant sample field makes the JPEG packer assert on an empty buffer.
  check(codes_set_double_array(h, "values", values.data(), n), "values");
  if (!c.packingType.empty())
  {
    size_t len = c.packingType.size();
    check(codes_set_string(h, "packingType", c.packingType.c_str(), &len), "packingType");
  }
  check(codes_set_long(h, "bitsPerValue", c.bitsPerValue), "bitsPerValue");
  check(codes_set_double_array(h, "values", values.data(), n), "values after repacking");

  const std::string gribfile = dir + "/" + c.name + ".grib";
  check(codes_write_message(h, gribfile.c_str(), "w"), "write " + gribfile);
  codes_handle_delete(h);

  // Decode the written file back with ecCodes for the reference

  FILE *in = fopen(gribfile.c_str(), "rb");
  if (in == nullptr)
    throw std::runtime_error("cannot reopen " + gribfile);
  int err = 0;
  h = codes_handle_new_from_file(nullptr, in, PRODUCT_GRIB, &err);
  check(err, "reopen " + gribfile);

  std::string out;
  for (const char *key : {"edition", "gridType", "packingType", "Ni", "Nj", "numberOfDataPoints",
                          "iScansNegatively", "jScansPositively", "jPointsAreConsecutive",
                          "paramId", "shortName", "typeOfLevel", "level", "dataDate", "dataTime",
                          "stepRange", "bitmapPresent"})
    out += fmt::format("# {}={}\n", key, getString(h, key));

  double missing = 0;
  check(codes_get_double(h, "missingValue", &missing), "missingValue");

  codes_iterator *it = codes_grib_iterator_new(h, 0, &err);
  check(err, "iterator " + c.name);
  double lat = 0;
  double lon = 0;
  double value = 0;
  size_t index = 0;
  while (codes_grib_iterator_next(it, &lat, &lon, &value) != 0)
  {
    if (value == missing && c.bitmap)
      out += fmt::format("{} {:.9f} {:.9f} nan\n", index, lat, lon);
    else
      out += fmt::format("{} {:.9f} {:.9f} {:.9g}\n", index, lat, lon, value);
    index++;
  }
  codes_grib_iterator_delete(it);
  codes_handle_delete(h);
  fclose(in);

  const std::string reffile = dir + "/" + c.name + ".ref";
  FILE *ref = fopen(reffile.c_str(), "w");
  if (ref == nullptr)
    throw std::runtime_error("cannot write " + reffile);
  fputs(out.c_str(), ref);
  fclose(ref);

  fmt::print("{:<36} {:>6} points\n", c.name, index);
  fflush(stdout);
}

// Keys shared by the small limited-area latlon-style grids
std::vector<Key> latlon(long ni, long nj, double lat1, double lon1, double lat2, double lon2)
{
  return {{"Ni", ni},
          {"Nj", nj},
          {"latitudeOfFirstGridPointInDegrees", lat1},
          {"longitudeOfFirstGridPointInDegrees", lon1},
          {"latitudeOfLastGridPointInDegrees", lat2},
          {"longitudeOfLastGridPointInDegrees", lon2},
          {"iDirectionIncrementInDegrees", (lon2 - lon1) / static_cast<double>(ni - 1)},
          {"jDirectionIncrementInDegrees", std::fabs(lat2 - lat1) / static_cast<double>(nj - 1)}};
}

std::vector<Key> operator+(std::vector<Key> a, const std::vector<Key> &b)
{
  a.insert(a.end(), b.begin(), b.end());
  return a;
}

// Temperature at 2 metres so that the FMI parameter mapping finds the field
const std::vector<Key> T2_GRIB2 = {{"discipline", 0L},
                                   {"parameterCategory", 0L},
                                   {"parameterNumber", 0L},
                                   {"typeOfFirstFixedSurface", 103L},
                                   {"scaledValueOfFirstFixedSurface", 2L},
                                   {"scaleFactorOfFirstFixedSurface", 0L},
                                   {"dataDate", 20260101L},
                                   {"dataTime", 1200L},
                                   {"stepRange", std::string("6")}};

const std::vector<Key> T2_GRIB1 = {{"table2Version", 1L},
                                   {"indicatorOfParameter", 11L},
                                   {"indicatorOfTypeOfLevel", 105L},
                                   {"level", 2L},
                                   {"dataDate", 20260101L},
                                   {"dataTime", 1200L},
                                   {"stepRange", std::string("6")}};

std::vector<Case> cases()
{
  // A small Finland-sized area used by most limited-area cases
  const auto ll = latlon(16, 12, 58.0, 18.0, 69.0, 33.0);
  const auto llNS = latlon(16, 12, 69.0, 18.0, 58.0, 33.0) + std::vector<Key>{{"jScansPositively", 0L}};
  const auto ll_jpos = std::vector<Key>{{"jScansPositively", 1L}};

  // Gaussian N=8 (16 latitudes); 81.650591 is the northernmost Gaussian latitude for N=8
  const double gglat = 81.650591;
  const std::vector<Key> regular_gg = {{"N", 8L},
                                       {"Ni", 32L},
                                       {"Nj", 16L},
                                       {"iDirectionIncrementInDegrees", 11.25},
                                       {"latitudeOfFirstGridPointInDegrees", gglat},
                                       {"longitudeOfFirstGridPointInDegrees", 0.0},
                                       {"latitudeOfLastGridPointInDegrees", -gglat},
                                       {"longitudeOfLastGridPointInDegrees", 348.75}};

  // Octahedral reduced Gaussian: 20 points at the poles, 4 more per latitude towards the equator
  std::vector<long> pl;
  for (long j = 0; j < 8; j++)
    pl.push_back(20 + 4 * j);
  for (long j = 7; j >= 0; j--)
    pl.push_back(20 + 4 * j);
  const std::vector<Key> reduced_gg = {{"N", 8L},
                                       {"Nj", 16L},
                                       {"pl", pl},
                                       {"latitudeOfFirstGridPointInDegrees", gglat},
                                       {"longitudeOfFirstGridPointInDegrees", 0.0},
                                       {"latitudeOfLastGridPointInDegrees", -gglat},
                                       {"longitudeOfLastGridPointInDegrees", 352.5}};

  std::vector<Case> ret;

  // ---- GRIB2 regular_ll with every supported packing ----
  // grid_png is missing: the FMI ecCodes build has no PNG support
  for (const auto &packing : {"grid_simple", "grid_jpeg", "grid_ccsds",
                              "grid_complex", "grid_complex_spatial_differencing", "grid_ieee"})
  {
    Case c{std::string("grib2_regular_ll_") + (packing + 5), "regular_ll_sfc_grib2",
           T2_GRIB2 + ll_jpos + ll, packing};
    if (std::string(packing) == "grid_ieee")
      c.bitsPerValue = 32;
    ret.push_back(c);
  }

  // Scanning modes and bitmap
  ret.push_back({"grib2_regular_ll_north_to_south", "regular_ll_sfc_grib2", T2_GRIB2 + llNS,
                 "grid_simple"});
  ret.push_back({"grib2_regular_ll_bitmap", "regular_ll_sfc_grib2", T2_GRIB2 + ll_jpos + ll,
                 "grid_simple", 16, true});
  ret.push_back({"grib2_regular_ll_bitmap_jpeg", "regular_ll_sfc_grib2", T2_GRIB2 + ll_jpos + ll,
                 "grid_jpeg", 16, true});

  // Global grid crossing the date line / Greenwich
  ret.push_back({"grib2_regular_ll_global", "regular_ll_sfc_grib2",
                 T2_GRIB2 + std::vector<Key>{{"jScansPositively", 0L}} +
                     latlon(36, 19, 90.0, 0.0, -90.0, 350.0),
                 "grid_simple"});

  // ---- GRIB2 rotated latlon ----
  ret.push_back({"grib2_rotated_ll", "rotated_ll_sfc_grib2",
                 T2_GRIB2 + ll_jpos + latlon(16, 12, -10.0, -8.0, 1.0, 7.0) +
                     std::vector<Key>{{"latitudeOfSouthernPoleInDegrees", -30.0},
                                      {"longitudeOfSouthernPoleInDegrees", 0.0}},
                 "grid_simple"});

  // ---- GRIB2 polar stereographic ----
  ret.push_back({"grib2_polar_stereographic", "polar_stereographic_sfc_grib2",
                 T2_GRIB2 + std::vector<Key>{{"Nx", 14L},
                                             {"Ny", 10L},
                                             {"latitudeOfFirstGridPointInDegrees", 55.0},
                                             {"longitudeOfFirstGridPointInDegrees", 10.0},
                                             {"LaDInDegrees", 60.0},
                                             {"orientationOfTheGridInDegrees", 20.0},
                                             {"DxInMetres", 50000.0},
                                             {"DyInMetres", 50000.0},
                                             {"jScansPositively", 1L}},
                 "grid_simple"});

  // ---- GRIB2 lambert conformal (template 3.30) ----
  ret.push_back({"grib2_lambert", "GRIB2",
                 std::vector<Key>{{"gridDefinitionTemplateNumber", 30L},
                                  {"Nx", 14L},
                                  {"Ny", 10L},
                                  {"latitudeOfFirstGridPointInDegrees", 55.0},
                                  {"longitudeOfFirstGridPointInDegrees", 10.0},
                                  {"LaDInDegrees", 63.3},
                                  {"LoVInDegrees", 15.0},
                                  {"Latin1InDegrees", 63.3},
                                  {"Latin2InDegrees", 63.3},
                                  {"DxInMetres", 50000.0},
                                  {"DyInMetres", 50000.0},
                                  {"jScansPositively", 1L}} +
                     T2_GRIB2,
                 "grid_simple"});

  // ---- GRIB2 mercator (template 3.10) ----
  ret.push_back({"grib2_mercator", "GRIB2",
                 std::vector<Key>{{"gridDefinitionTemplateNumber", 10L},
                                  {"Ni", 14L},
                                  {"Nj", 10L},
                                  {"latitudeOfFirstGridPointInDegrees", 50.0},
                                  {"longitudeOfFirstGridPointInDegrees", 10.0},
                                  {"latitudeOfLastGridPointInDegrees", 65.0},
                                  {"longitudeOfLastGridPointInDegrees", 36.0},
                                  {"LaDInDegrees", 60.0},
                                  {"DiInMetres", 100000.0},
                                  {"DjInMetres", 100000.0},
                                  {"jScansPositively", 1L}} +
                     T2_GRIB2,
                 "grid_simple"});

  // ---- GRIB2 lambert azimuthal equal area (template 3.140) ----
  ret.push_back({"grib2_lambert_azimuthal_equal_area", "GRIB2",
                 std::vector<Key>{{"gridDefinitionTemplateNumber", 140L},
                                  {"numberOfPointsAlongXAxis", 14L},
                                  {"numberOfPointsAlongYAxis", 10L},
                                  {"latitudeOfFirstGridPointInDegrees", 50.0},
                                  {"longitudeOfFirstGridPointInDegrees", 0.0},
                                  {"standardParallelInDegrees", 52.0},
                                  {"centralLongitudeInDegrees", 10.0},
                                  {"xDirectionGridLengthInMillimetres", 100000000L},
                                  {"yDirectionGridLengthInMillimetres", 100000000L},
                                  {"jScansPositively", 1L}} +
                     T2_GRIB2,
                 "grid_simple"});

  // ---- GRIB2 Gaussian ----
  ret.push_back({"grib2_regular_gg", "regular_gg_sfc_grib2", T2_GRIB2 + regular_gg, "grid_simple"});
  ret.push_back({"grib2_reduced_gg", "reduced_gg_sfc_grib2", T2_GRIB2 + reduced_gg, "grid_simple"});

  // ---- GRIB1 ----
  ret.push_back({"grib1_regular_ll", "regular_ll_sfc_grib1", T2_GRIB1 + ll_jpos + ll, "grid_simple"});
  ret.push_back({"grib1_regular_ll_north_to_south", "regular_ll_sfc_grib1", T2_GRIB1 + llNS,
                 "grid_simple"});
  ret.push_back({"grib1_regular_ll_bitmap", "regular_ll_sfc_grib1", T2_GRIB1 + ll_jpos + ll,
                 "grid_simple", 16, true});
  ret.push_back({"grib1_regular_ll_second_order", "regular_ll_sfc_grib1",
                 T2_GRIB1 + ll_jpos + ll, "grid_second_order"});
  ret.push_back({"grib1_rotated_ll", "rotated_ll_sfc_grib1",
                 T2_GRIB1 + ll_jpos + latlon(16, 12, -10.0, -8.0, 1.0, 7.0) +
                     std::vector<Key>{{"latitudeOfSouthernPoleInDegrees", -30.0},
                                      {"longitudeOfSouthernPoleInDegrees", 0.0}},
                 "grid_simple"});
  ret.push_back({"grib1_polar_stereographic", "polar_stereographic_sfc_grib1",
                 T2_GRIB1 + std::vector<Key>{{"Nx", 14L},
                                             {"Ny", 10L},
                                             {"latitudeOfFirstGridPointInDegrees", 55.0},
                                             {"longitudeOfFirstGridPointInDegrees", 10.0},
                                             {"orientationOfTheGridInDegrees", 20.0},
                                             {"DxInMetres", 50000.0},
                                             {"DyInMetres", 50000.0},
                                             {"jScansPositively", 1L}},
                 "grid_simple"});
  ret.push_back({"grib1_lambert", "GRIB1",
                 std::vector<Key>{{"dataRepresentationType", 3L},
                                  {"Nx", 14L},
                                  {"Ny", 10L},
                                  {"latitudeOfFirstGridPointInDegrees", 55.0},
                                  {"longitudeOfFirstGridPointInDegrees", 10.0},
                                  {"LoVInDegrees", 15.0},
                                  {"Latin1InDegrees", 63.0},
                                  {"Latin2InDegrees", 63.0},
                                  {"DxInMetres", 50000.0},
                                  {"DyInMetres", 50000.0},
                                  {"jScansPositively", 1L}} +
                     T2_GRIB1,
                 "grid_simple"});
  ret.push_back({"grib1_regular_gg", "regular_gg_sfc_grib1", T2_GRIB1 + regular_gg, "grid_simple"});
  ret.push_back({"grib1_reduced_gg", "reduced_gg_sfc_grib1", T2_GRIB1 + reduced_gg, "grid_simple"});

  return ret;
}

}  // namespace

int main(int argc, char **argv)
{
  const std::string dir = (argc > 1 ? argv[1] : ".");
  int failures = 0;
  for (const auto &c : cases())
  {
    try
    {
      generate(c, dir);
    }
    catch (const std::exception &e)
    {
      fmt::print(stderr, "{:<36} FAILED: {}\n", c.name, e.what());
      failures++;
    }
  }
  return failures == 0 ? 0 : 1;
}

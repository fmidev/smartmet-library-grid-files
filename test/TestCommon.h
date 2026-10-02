// Common helpers for the grid-files Boost.Test programs.
//
// Tests needing installed fixtures (smartmet-test-data) use the
// fixtures() precondition. A missing fixture is a test FAILURE unless the environment variable
// GRID_TEST_ALLOW_SKIP is set, in which case the test is reported as skipped. This keeps CI
// honest (the fixtures are TestRequires) while still allowing quick local runs without them.

#pragma once

#include <boost/test/unit_test.hpp>
#include <macgyver/Exception.h>

#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <initializer_list>
#include <string>

namespace GridTest
{
// FMI geometry/parameter definitions of this repository (relative to the test directory)
inline const char *const CONFIG = "../cfg/grid-files.conf";

// Root of the grid data installed by smartmet-test-data
inline const char *const TEST_DATA = "/usr/share/smartmet/test/data";

inline std::string testData(const std::string &relpath)
{
  return std::string(TEST_DATA) + "/" + relpath;
}

inline bool exists(const std::string &path)
{
  struct stat st = {};
  return stat(path.c_str(), &st) == 0 && st.st_size > 0;
}

inline bool skippingAllowed()
{
  return std::getenv("GRID_TEST_ALLOW_SKIP") != nullptr;
}

// Boost.Test precondition: skip the test only if fixtures are missing AND skipping is allowed.
// Otherwise the test runs and fails on the missing file with a clear message.
inline boost::unit_test::precondition fixtures(std::initializer_list<std::string> paths)
{
  std::vector<std::string> p(paths);
  return boost::unit_test::precondition(
      [p](boost::unit_test::test_unit_id) -> boost::test_tools::assertion_result
      {
        for (const auto &path : p)
        {
          if (!exists(path))
          {
            if (!skippingAllowed())
              return true;  // run and fail loudly in requireFixture
            boost::test_tools::assertion_result ret(false);
            ret.message() << "fixture " << path << " is not installed";
            return ret;
          }
        }
        return true;
      });
}

inline void requireFixture(const std::string &path)
{
  BOOST_TEST_REQUIRE(exists(path),
                     "test fixture " << path
                                     << " is missing: install smartmet-test-data, or set "
                                        "GRID_TEST_ALLOW_SKIP");
}

// A temporary file removed when the object goes out of scope
class TempFile
{
 public:
  explicit TempFile(const std::string &contents, const std::string &prefix = "gridtest")
  {
    std::string tmpl = "/tmp/" + prefix + "-XXXXXX";
    std::vector<char> name(tmpl.begin(), tmpl.end());
    name.push_back('\0');
    int fd = mkstemp(name.data());
    BOOST_TEST_REQUIRE(fd >= 0, "cannot create a temporary file");
    itsName = name.data();
    const auto n = write(fd, contents.data(), contents.size());
    close(fd);
    BOOST_TEST_REQUIRE(n == static_cast<ssize_t>(contents.size()), "cannot write " << itsName);
  }
  ~TempFile() { unlink(itsName.c_str()); }
  TempFile(const TempFile &) = delete;
  TempFile &operator=(const TempFile &) = delete;
  const std::string &name() const { return itsName; }

 private:
  std::string itsName;
};

// Run a block and report Fmi::Exception details (the what() text alone is often not enough)
template <typename F>
void withFmiErrors(F &&f)
{
  try
  {
    f();
  }
  catch (Fmi::Exception &e)
  {
    e.printError();
    BOOST_FAIL("Fmi::Exception: " << e.what());
  }
}

}  // namespace GridTest

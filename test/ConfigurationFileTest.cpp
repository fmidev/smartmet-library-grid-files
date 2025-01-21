#include <boost/test/included/unit_test.hpp>
#include "ConfigurationFile.h"
#include <string>

using namespace std::string_literals;
using namespace boost::unit_test;

test_suite* init_unit_test_suite(int argc, char* argv[])
{
    const char* name = "ConfigurationFile tester";
    unit_test_log.set_threshold_level(log_messages);
    framework::master_test_suite().p_name.value = name;
    BOOST_TEST_MESSAGE("");
    BOOST_TEST_MESSAGE(name);
    BOOST_TEST_MESSAGE(std::string(std::strlen(name), '='));
    return nullptr;
}

// Currently only test for parsing references values with provided default values is present
BOOST_AUTO_TEST_CASE(test_parseValueWithDefault)
{
    SmartMet::ConfigurationFile config;
    BOOST_REQUIRE_NO_THROW(config.readFile("data/test-config.conf"));
    putenv((char*)"test_var_1");
    putenv((char*)"test_var_2");

    bool ok;
    std::string value;
    bool value2 = false;
    BOOST_REQUIRE_NO_THROW(ok = config.getAttributeValue("test1", value));
    BOOST_CHECK(ok);
    BOOST_CHECK_EQUAL(value, "default_value"s);

    BOOST_REQUIRE_NO_THROW(ok = config.getAttributeValue("test2", value2));
    BOOST_CHECK(ok);
    BOOST_CHECK(value2);
}

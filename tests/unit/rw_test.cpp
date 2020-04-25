#include "catch2/catch.hpp"

#include "sample_reader.h"
#include "sample_writer.h"

TEST_CASE("RW_TEST_CASE") {
  using namespace sample;

  const std::string open_string = ":memory:";
  const std::string key = "test_key";
  const std::string value = "test_value";

  SampleWriter writer(open_string);
  auto write_result = writer.WriteString(key, value);

  REQUIRE_FALSE( std::get<op::status>(write_result));

  SampleReader reader(open_string);
  auto read_result = reader.ReadString(key);

  REQUIRE_FALSE( std::get<op::status>(write_result));
}
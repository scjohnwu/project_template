#include "catch2/catch.hpp"
#include "sample_reader.h"
#include "sample_writer.h"

TEST_CASE("RW_TEST_CASE") {
  using namespace sample;

  const std::string open_string = ":memory:";
  const std::string key = "test_key";
  const std::string value = "test_value";

  auto sql_wrapper = make_sqlite3(open_string);

  SampleWriter writer{sql_wrapper};
  writer.CreateSchema();

  auto write_result = writer.WriteString(key, value);

  REQUIRE_FALSE(std::get<op::status>(write_result));

  SampleReader reader{sql_wrapper};
  auto read_result = reader.ReadString(key);

  REQUIRE(std::get<op::status>(read_result));
  REQUIRE(std::get<op::value>(read_result) == value);
}
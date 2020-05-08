#include "catch2/catch.hpp"
#include "sample_reader.h"
#include "sample_writer.h"

TEST_CASE("RW_TEST_CASE") {
  using namespace sample;

  const std::string open_string = ":memory:";
  const std::string key = "test_key";
  const std::string string_value = "test_value";
  const std::int64_t integer_value = 0xDEAD;

  auto sql_wrapper = make_sqlite3(open_string);

  SampleWriter writer{sql_wrapper};
  writer.CreateSchema();

  auto write_result = writer.WriteString(key, string_value);
  REQUIRE(std::get<op::status>(write_result));

  write_result = writer.WriteInt64(key, integer_value);
  REQUIRE(std::get<op::status>(write_result));

  SampleReader reader{sql_wrapper};
  auto string_result = reader.ReadString(key);

  REQUIRE(std::get<op::status>(string_result));
  REQUIRE(std::get<op::value>(string_result) == string_value);

  auto integer_result = reader.ReadInt64(key);
  REQUIRE(std::get<op::status>(integer_result));
  REQUIRE(std::get<op::value>(integer_result) == integer_value);
}
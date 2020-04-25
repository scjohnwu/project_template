#include "catch2/catch.hpp"

#include "sqlite3_wrapper.h"

TEST_CASE("simple sqlite3 wrapper case") {
  auto wrapper = sample::make_sqlite3(":memory:");

  auto response = wrapper->Execute("SELECT SQLITE_VERSION()");

  REQUIRE( response.size() > 0 );
}
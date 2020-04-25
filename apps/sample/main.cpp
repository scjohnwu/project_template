#include <iostream>

#include "sqlite3_wrapper.h"

#include "fmt/format.h"

int main(int argc, char** argv) {
  auto wrapper = sample::make_sqlite3(":memory:");

  auto response = wrapper->Execute("SELECT SQLITE_VERSION()");
  if( response.empty() || response[0].cols.empty() ) {
    return -1;
  }

  std::cout << fmt::format("Supported sqlite3 version: {0}\n", response[0].cols[0]); 
  return 0;
}
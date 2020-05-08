#pragma once

#include <memory>
#include <string>
#include <vector>

#include "sqlite3.h"

namespace sample {
struct RespRow {
  std::vector<std::string> cols;
};

class SQLite3Wrapper {
 public:
  SQLite3Wrapper(const SQLite3Wrapper&) = delete;
  SQLite3Wrapper(SQLite3Wrapper&&) = delete;

  SQLite3Wrapper& operator=(const SQLite3Wrapper&) = delete;
  SQLite3Wrapper& operator=(SQLite3Wrapper&&) = delete;

  void Connect(std::string connection_string);
  std::vector<RespRow> Execute(std::string query);

  friend std::shared_ptr<SQLite3Wrapper> make_sqlite3(std::string connection_string);

  ~SQLite3Wrapper();

 private:
  SQLite3Wrapper() = default;

  sqlite3* m_DB{nullptr};
};
using SQLite3WrapperPtr = std::shared_ptr<SQLite3Wrapper>;

SQLite3WrapperPtr make_sqlite3(std::string connection_string);

}  // namespace sample
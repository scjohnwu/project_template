#include "sqlite3_wrapper.h"

#include <exception>

namespace sample {
void SQLite3Wrapper::Connect(std::string connection_string) {
  auto res = sqlite3_open(connection_string.c_str(), &m_DB);
  if (res != SQLITE_OK) {
    sqlite3_close(m_DB);

    throw std::logic_error("Could not connecto to the database");
  }
}

std::vector<RespRow> SQLite3Wrapper::Execute(std::string query) {
  if (!m_DB) {
    throw std::logic_error("Attempt to execute query before connection");
  }

  sqlite3_stmt* statement = nullptr;
  auto res = sqlite3_prepare_v2(m_DB, query.c_str(), -1, &statement, nullptr);
  if (res != SQLITE_OK) {
    throw std::logic_error("Could not compile query");
  }

  auto step = sqlite3_step(statement);
  if (step == SQLITE_ERROR) {
    throw std::logic_error("Error on statement execution step");
  }

  std::vector<RespRow> result;
  while (step != SQLITE_DONE) {
    RespRow row;

    auto count = sqlite3_column_count(statement);
    for (decltype(count) i = 0; i < count; ++i) {
      auto ch_str =
          reinterpret_cast<const char*>(sqlite3_column_text(statement, i));
      row.cols.push_back(ch_str);
    }

    result.push_back(std::move(row));

    step = sqlite3_step(statement);
    if (step == SQLITE_ERROR) {
      throw std::logic_error("Error on statement execution step");
    }
  }

  sqlite3_finalize(statement);

  return result;
}

SQLite3WrapperPtr make_sqlite3(std::string connection_string) {
  SQLite3WrapperPtr result{new SQLite3Wrapper()};

  result->Connect(connection_string);

  return result;
}

SQLite3Wrapper::~SQLite3Wrapper() { sqlite3_close(m_DB); }
}  // namespace sample
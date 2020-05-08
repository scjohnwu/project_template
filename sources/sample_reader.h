#pragma once

#include "common_types.h"
#include "sqlite3_wrapper.h"


namespace sample {
class SampleReader {
 public:
  SampleReader(SQLite3WrapperPtr wrapper);

  SampleReader(const SampleReader&) = delete;
  SampleReader(SampleReader&&) = delete;

  SampleReader& operator=(const SampleReader&) = delete;
  SampleReader& operator=(SampleReader&&) = delete;

  op_result<std::string> ReadString(std::string key);
  op_result<std::int64_t> ReadInt64(std::string key);

 private:
  SQLite3WrapperPtr m_SQL;
};
}  // namespace sample
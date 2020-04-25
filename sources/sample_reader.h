#pragma once

#include "sqlite3_wrapper.h"
#include "common_types.h"

namespace sample {
class SampleReader {
 public:
  SampleReader(std::string connection_string);

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
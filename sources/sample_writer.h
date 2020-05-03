#pragma once

#include "common_types.h"
#include "sqlite3_wrapper.h"

namespace sample {
struct WriteStatus {
  bool is_ok{true};
  std::string desc;

  operator bool() const { return is_ok; }
};

class SampleWriter {
 public:
  SampleWriter(SQLite3WrapperPtr wrapper);

  SampleWriter(const SampleWriter&) = delete;
  SampleWriter(SampleWriter&&) = delete;

  SampleWriter& operator=(const SampleWriter&) = delete;
  SampleWriter& operator=(SampleWriter&&) = delete;

  void CreateSchema();

  op_result<WriteStatus> WriteString(std::string key, std::string value);
  op_result<WriteStatus> WriteInt64(std::string key, std::int64_t value);

 private:
  SQLite3WrapperPtr m_SQL;
};
}  // namespace sample
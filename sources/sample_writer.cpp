#include "sample_writer.h"

#include "fmt/format.h"

namespace sample {
SampleWriter::SampleWriter(SQLite3WrapperPtr wrapper) : m_SQL{wrapper} {}

op_result<WriteStatus> SampleWriter::WriteString(std::string key,
                                                 std::string value) {
  m_SQL->Execute(fmt::format(
      "INSERT INTO Strings(Key, Value) VALUES('{0}', '{1}'", key, value));
  return std::make_tuple(true, WriteStatus{});
}

op_result<WriteStatus> SampleWriter::WriteInt64(std::string key,
                                                std::int64_t value) {
  m_SQL->Execute(fmt::format(
      "INSERT INTO Integers(Key, Value) VALUES('{0}', {1}", key, value));
  return std::make_tuple(true, WriteStatus{});
}

void SampleWriter::CreateSchema() {
  m_SQL->Execute("DROP TABLE IF EXISTS STR_VALS;");
  m_SQL->Execute("DROP TABLE IF EXISTS INT_VALS;");
  m_SQL->Execute(
      "CREATE TABLE Strings(Id INTEGER PRIMARY KEY, Key TEXT, Value TEXT)");
  m_SQL->Execute(
      "CREATE TABLE Integers(Id INTEGER PRIMARY KEY, Key TEXT, Value INT)");
}
}  // namespace sample
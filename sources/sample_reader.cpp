#include "sample_reader.h"

namespace sample {
SampleReader::SampleReader(SQLite3WrapperPtr wrapper) : m_SQL{wrapper} {}

op_result<std::string> SampleReader::ReadString(std::string key) {
  auto result = m_SQL->Execute("SELECT Value FROM Strings");

  if (result.empty() || result[0].cols.empty()) {
    return std::make_tuple(false, std::string{"empty"});
  }

  return std::make_tuple(true, result[0].cols[0]);
}

op_result<std::int64_t> SampleReader::ReadInt64(std::string key) {
  auto result = m_SQL->Execute("SELECT Value FROM Integers");

  if (result.empty() || result[0].cols.empty()) {
    return std::make_tuple(false, std::int64_t{0});
  }

  std::size_t pos_tmp_value = 0;
  return std::make_tuple(true, std::stoll(result[0].cols[0], &pos_tmp_value));
}
}  // namespace sample

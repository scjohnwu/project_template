#include "sample_reader.h"

namespace sample {
SampleReader::SampleReader(SQLite3WrapperPtr wrapper) : m_SQL{wrapper} {}

op_result<std::string> SampleReader::ReadString(std::string key) {
  return std::make_tuple(false, std::string(""));
}

op_result<std::int64_t> SampleReader::ReadInt64(std::string key) {
  return std::make_tuple(false, std::int64_t(0));
}
}  // namespace sample

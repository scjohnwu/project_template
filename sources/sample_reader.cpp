#include "sample_reader.h"

namespace sample {
SampleReader::SampleReader(std::string connection_string)
    : m_SQL{make_sqlite3(connection_string)} {}

op_result<std::string> SampleReader::ReadString(std::string key) {
  return std::make_tuple(false, std::string(""));
}

op_result<std::int64_t> SampleReader::ReadInt64(std::string key) {
  return std::make_tuple(false, std::int64_t(0));
}
}  // namespace sample

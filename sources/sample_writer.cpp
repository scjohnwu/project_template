#include "sample_writer.h"

namespace sample {
SampleWriter::SampleWriter(std::string connection_string)
    : m_SQL{make_sqlite3(connection_string)} {}

op_result<WriteStatus> SampleWriter::WriteString(std::string key,
                                                 std::string value) {
  return std::make_tuple(false, WriteStatus{});
}

op_result<WriteStatus> SampleWriter::WriteInt64(std::string key,
                                                std::int64_t value) {
  return std::make_tuple(false, WriteStatus{});
}
}  // namespace sample

#pragma once

#include <tuple>

namespace sample {
template <typename T>
using op_result = std::tuple<bool, T>;

namespace op {
enum { status = 0, value = 1 };
}
}  // namespace sample
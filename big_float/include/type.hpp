#pragma once

#include <cstdint>

namespace big_float {

enum class Type : uint8_t { DEFAULT = 0, ZERO = 1, INF = 2, NAN = 3 };

}

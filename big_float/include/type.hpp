#pragma once

#include <cstdint>

namespace big_float {

enum class Type : uint8_t { kDefault = 0, kZero = 1, kInf = 2, kNan = 3 };

}

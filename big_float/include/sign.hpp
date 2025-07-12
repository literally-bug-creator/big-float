#pragma once

namespace big_float {

using Sign = bool;

Sign
GetPositive() noexcept;

Sign
GetNegative() noexcept;

bool
IsPositive(const Sign& sign) noexcept;

bool
IsNegative(const Sign& sign) noexcept;

Sign
Invert(const Sign& sign) noexcept;

bool
IsEqual(const Sign& lhs, const Sign& rhs) noexcept;

}  // namespace big_float

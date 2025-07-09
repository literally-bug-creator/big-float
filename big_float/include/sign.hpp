#pragma once

namespace big_float {

using Sign = bool;

Sign getPositive() noexcept;

Sign getNegative() noexcept;

bool isPositive(const Sign& sign) noexcept;

bool isNegative(const Sign& sign) noexcept;

Sign invert(const Sign& sign) noexcept;

}  // namespace big_float

#pragma once

#include <cstddef>
#include <cstdint>

#include "big_float.hpp"
#include "big_uint.hpp"
#include "exponent.hpp"
#include "type.hpp"

namespace big_float {

Type
GetType(const BigFloat& number) noexcept;

bool
IsSpecial(const BigFloat& number) noexcept;

bool
GetSign(const BigFloat& number) noexcept;

bool
IsNegative(const BigFloat& number) noexcept;

const big_uint::BigUInt&
GetMantissa(const BigFloat& number) noexcept;

Exponent
GetExponent(const BigFloat& number) noexcept;

size_t
GetSize(const BigFloat& number) noexcept;

int64_t
CountPower(const BigFloat& number) noexcept;

}  // namespace big_float

#pragma once

#include <cstddef>
#include <cstdint>

#include "big_float.hpp"
#include "exponent.hpp"
#include "type.hpp"

namespace big_float {

Type getType(const BigFloat& number) noexcept;

bool getSign(const BigFloat& number) noexcept;

bool isNegative(const BigFloat& number) noexcept;

const BigUInt& getMantissa(const BigFloat& number) noexcept;

Exponent getExponent(const BigFloat& number) noexcept;

size_t getSize(const BigFloat& number) noexcept;

int64_t countPower(const BigFloat& number) noexcept;

}  // namespace big_float

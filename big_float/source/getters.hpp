#pragma once

#include <cstdint>

#include "big_float.hpp"

namespace big_float {

const BigUInt& getMantissa(const BigFloat& number);

Exponent getExponent(const BigFloat& number);

BigFloatType getType(const BigFloat& number);

bool getSign(const BigFloat& number);

bool isNegative(const BigFloat& number);

size_t getSize(const BigFloat& number);

int64_t countPower(const BigFloat& number);

}  // namespace big_float

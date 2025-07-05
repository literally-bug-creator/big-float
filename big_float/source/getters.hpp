#pragma once

#include "big_float.hpp"

namespace big_float {

const BigUInt& getMantissa(const BigFloat& number);

Exponent getExponent(const BigFloat& number);

BigFloatType getType(const BigFloat& number);

bool getSign(const BigFloat& number);

}  // namespace big_float

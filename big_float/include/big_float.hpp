#pragma once

#include <string>

#include "big_uint.hpp"
#include "error.hpp"
#include "exponent.hpp"
#include "sign.hpp"
#include "type.hpp"

using namespace big_uint;

namespace big_float {

struct BigFloat {  // NOLINT
    BigUInt number;
    Exponent exp;
    Type type;
    Sign sign;
    Error error;
};

BigFloat makeBigFloat(BigUInt number, Exponent exp, Sign sign, Type type, Error error) noexcept;

BigFloat makeZero(Sign sign = getPositive(), const Error& error = getDefaultError()) noexcept;

BigFloat makeInf(Sign sign = getPositive(), const Error& error = getDefaultError()) noexcept;

BigFloat makeNan(Sign sign = getPositive(), const Error& error = getDefaultError()) noexcept;

bool isZero(const BigFloat& number) noexcept;

bool isInf(const BigFloat& number) noexcept;

bool isNan(const BigFloat& number) noexcept;

const Error& getError(const BigFloat& number) noexcept;

std::string toString(const BigFloat& number) noexcept;

bool isEqual(const BigFloat& left, const BigFloat& right) noexcept;

bool isGreater(const BigFloat& left, const BigFloat& right) noexcept;

bool isLower(const BigFloat& left, const BigFloat& right) noexcept;

BigFloat abs(const BigFloat& number) noexcept;

BigFloat neg(const BigFloat& number) noexcept;

BigFloat add(const BigFloat& augend, const BigFloat& addend) noexcept;

BigFloat sub(const BigFloat& minuend, const BigFloat& subtrahend) noexcept;

BigFloat mul(const BigFloat& multiplicand, const BigFloat& multiplier) noexcept;

BigFloat div(const BigFloat& dividend, const BigFloat& divisor) noexcept;

BigFloat sqrt(const BigFloat& operand) noexcept;

}  // namespace big_float

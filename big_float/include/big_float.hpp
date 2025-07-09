#pragma once

#include <cstdint>
#include <string>

#include "big_uint.hpp"
#include "error.hpp"

using namespace big_uint;

namespace big_float {

enum class BigFloatType : uint8_t { DEFAULT = 0, ZERO = 1, INF = 2, NAN = 3 };

using Exponent = int64_t;

struct BigFloat {  // NOLINT
    BigUInt mantissa;
    Exponent exp;
    BigFloatType type;
    bool isNegative;
    Error error;
};

BigFloat makeBigFloat(BigUInt mantissa, Exponent exp, bool isNeg, BigFloatType type,
                      Error error) noexcept;

BigFloat makeZero(bool isNegative = false, const Error& error = getDefaultError()) noexcept;

BigFloat makeInf(bool isNegative = false, const Error& error = getDefaultError()) noexcept;

BigFloat makeNan(bool isNegative = false, const Error& error = getDefaultError()) noexcept;

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

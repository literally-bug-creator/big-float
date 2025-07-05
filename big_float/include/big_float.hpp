#pragma once

#include <cstdint>
#include <string>

#include "big_uint.hpp"
#include "error.hpp"

using namespace big_uint;

namespace big_float {

enum class BigFloatType : uint8_t { DEFAULT = 0, ZERO = 1, INF = 2, NAN = 3 };

using Exponent = uint64_t;

struct BigFloat {  // NOLINT
    BigUInt mantissa;
    Exponent exp;
    BigFloatType type;
    bool isNegative;
    Error error;
};

BigFloat makeBigFloat(BigUInt mantissa, Exponent exp, bool isNeg, BigFloatType type, Error error);

BigFloat makeZero(const Error& error, bool isNegative = false);

BigFloat makeNan(const Error& error, bool isNegative = false);

BigFloat makeInf(const Error& error, bool isNegative);

const Error& getError(const BigFloat& number);

BigFloat abs(const BigFloat& number);

BigFloat neg(const BigFloat& number);

BigFloat add(const BigFloat& augend, const BigFloat& addend);

BigFloat sub(const BigFloat& minuend, const BigFloat& subtrahend);

BigFloat mul(const BigFloat& multiplicand, const BigFloat& multiplier);

BigFloat sqrt(const BigFloat& operand);

bool isEqual(const BigFloat& left, const BigFloat& right);

bool isGreater(const BigFloat& left, const BigFloat& right);

bool isLower(const BigFloat& left, const BigFloat& right);

std::string toString(const BigFloat& number);

}  // namespace big_float

#pragma once

#include <string>

#include "big_uint.hpp"
#include "error.hpp"
#include "exponent.hpp"
#include "sign.hpp"
#include "type.hpp"

namespace big_float {

struct BigFloat {  // NOLINT
  big_uint::BigUInt number;
  Exponent exp;
  Type type;
  Sign sign;
  Error error;
};

BigFloat
MakeBigFloat(big_uint::BigUInt number, Exponent exp, Sign sign, Type type,
             Error error) noexcept;

BigFloat
MakeZero(Sign sign = GetPositive(),
         const Error& error = GetDefaultError()) noexcept;

BigFloat
MakeInf(Sign sign = GetPositive(),
        const Error& error = GetDefaultError()) noexcept;

BigFloat
MakeNan(Sign sign = GetPositive(),
        const Error& error = GetDefaultError()) noexcept;

bool
IsZero(const BigFloat& number) noexcept;

bool
IsInf(const BigFloat& number) noexcept;

bool
IsNan(const BigFloat& number) noexcept;

const Error&
GetError(const BigFloat& number) noexcept;

std::string
ToString(const BigFloat& number) noexcept;

bool
IsEqual(const BigFloat& left, const BigFloat& right) noexcept;

bool
IsGreater(const BigFloat& left, const BigFloat& right) noexcept;

bool
IsLower(const BigFloat& left, const BigFloat& right) noexcept;

BigFloat
Abs(const BigFloat& number) noexcept;

BigFloat
Neg(const BigFloat& number) noexcept;

BigFloat
Add(const BigFloat& augend, const BigFloat& addend) noexcept;

BigFloat
Sub(const BigFloat& minuend, const BigFloat& subtrahend) noexcept;

BigFloat
Mul(const BigFloat& multiplicand, const BigFloat& multiplier) noexcept;

BigFloat
Div(const BigFloat& dividend, const BigFloat& divisor) noexcept;

BigFloat
Sqrt(const BigFloat& operand) noexcept;

}  // namespace big_float

#include <cstddef>
#include <cstdlib>

#include "big_float.hpp"
#include "big_uint.hpp"
#include "error.hpp"
#include "exponent.hpp"
#include "getters.hpp"
#include "sign.hpp"
#include "type.hpp"

using big_uint::BigUInt;

namespace big_float {
namespace {

BigFloat
SubNonSpecial(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  if (!IsEqual(GetSign(lhs), GetSign(rhs))) {
    return Add(lhs, Neg(rhs));
  }

  const Exponent kLhsExp = GetExponent(lhs);
  const Exponent kRhsExp = GetExponent(rhs);
  const BigUInt& lhs_mantissa = GetMantissa(lhs);
  const BigUInt& rhs_mantissa = GetMantissa(rhs);

  BigUInt result_mantissa;
  Exponent result_exponent = kLhsExp;  // NOLINT
  Sign result_sign = GetSign(lhs);

  if (kLhsExp == kRhsExp) {
    if (big_uint::isEqual(lhs_mantissa, rhs_mantissa)) {
      return MakeZero();
    }
    if (big_uint::isGreater(lhs_mantissa, rhs_mantissa)) {
      result_mantissa = big_uint::sub(lhs_mantissa, rhs_mantissa);
    } else {
      result_mantissa = big_uint::sub(rhs_mantissa, lhs_mantissa);
      result_sign = Invert(result_sign);
    }
    result_exponent = kLhsExp;
  } else if (kLhsExp > kRhsExp) {
    const auto kShift = static_cast<size_t>(kLhsExp - kRhsExp);
    if (big_uint::isGreater(lhs_mantissa, rhs_mantissa) ||
        big_uint::isEqual(lhs_mantissa, rhs_mantissa)) {
      result_mantissa = big_uint::sub(lhs_mantissa, rhs_mantissa, kShift);
    } else {
      result_mantissa = big_uint::sub(rhs_mantissa, lhs_mantissa, kShift);
      result_sign = Invert(result_sign);
    }
    result_exponent = kRhsExp;
  } else {
    const auto kShift = static_cast<size_t>(kRhsExp - kLhsExp);
    if (big_uint::isGreater(rhs_mantissa, lhs_mantissa) ||
        big_uint::isEqual(rhs_mantissa, lhs_mantissa)) {
      result_mantissa = big_uint::sub(rhs_mantissa, lhs_mantissa, kShift);
      result_sign = Invert(result_sign);
    } else {
      result_mantissa = big_uint::sub(lhs_mantissa, rhs_mantissa, kShift);
    }
    result_exponent = kLhsExp;
  }

  if (big_uint::isZero(result_mantissa)) {
    return MakeZero();
  }

  return MakeBigFloat(result_mantissa, result_exponent, result_sign,
                      Type::kDefault, GetDefaultError());
}

BigFloat
SubSpecialFromNonSpecial(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  switch (GetType(rhs)) {
    case Type::kNan:
      return rhs;
    case Type::kInf:
      return Neg(rhs);
    case Type::kZero:
      return lhs;
    case Type::kDefault:
      return SubNonSpecial(lhs, rhs);
  }
}

BigFloat
SubFromInf(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  switch (GetType(rhs)) {
    case Type::kNan:
      return rhs;
    case Type::kZero:
    case Type::kDefault:
      return lhs;
    case Type::kInf:
      const bool kIsEqualBySign = IsEqual(GetSign(lhs), GetSign(rhs));
      return kIsEqualBySign ? MakeNan() : lhs;
  }
}

BigFloat
SubSpecial(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  switch (GetType(lhs)) {
    case Type::kNan:
      return lhs;
    case Type::kInf:
      return SubFromInf(lhs, rhs);
    case Type::kZero:
      return Neg(rhs);
    case Type::kDefault:
      return SubSpecialFromNonSpecial(lhs, rhs);
  }
}

}  // namespace

BigFloat
Sub(const BigFloat& minuend, const BigFloat& subtrahend) noexcept {
  if (IsSpecial(minuend) || IsSpecial(subtrahend)) {
    return SubSpecial(minuend, subtrahend);
  }
  return SubNonSpecial(minuend, subtrahend);
}

}  // namespace big_float

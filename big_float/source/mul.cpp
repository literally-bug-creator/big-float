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

Sign
GetResultSign(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  const bool kHasSameSign = IsEqual(GetSign(lhs), GetSign(rhs));
  return kHasSameSign ? GetPositive() : GetNegative();
}

BigFloat
MulNonSpecial(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  const BigUInt& lhs_mantissa = GetMantissa(lhs);
  const BigUInt& rhs_mantissa = GetMantissa(rhs);
  const Exponent kLhsExp = GetExponent(lhs);
  const Exponent kRhsExp = GetExponent(rhs);

  const BigUInt kResultMantissa = big_uint::mul(lhs_mantissa, rhs_mantissa);
  const Exponent kResultExponent = kLhsExp + kRhsExp;
  const Sign kResultSign = GetResultSign(lhs, rhs);
  if (big_uint::isZero(kResultMantissa)) {
    return MakeZero(kResultSign);
  }
  return MakeBigFloat(kResultMantissa, kResultExponent, kResultSign,
                      Type::kDefault, GetDefaultError());
}

BigFloat
MulSpecialFromNonSpecial(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  switch (GetType(rhs)) {
    case Type::kNan:
      return rhs;
    case Type::kZero:
      return MakeZero(GetResultSign(lhs, rhs));
    case Type::kInf:
      return MakeInf(GetResultSign(lhs, rhs));
    case Type::kDefault:
      return MulNonSpecial(lhs, rhs);
  }
}

BigFloat
MulFromZero(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  switch (GetType(rhs)) {
    case Type::kNan:
      return rhs;
    case Type::kInf:
      return MakeNan();
    case Type::kZero:
    case Type::kDefault:
      return MakeZero(GetResultSign(lhs, rhs));
  }
}

BigFloat
MulFromInf(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  switch (GetType(rhs)) {
    case Type::kNan:
      return rhs;
    case Type::kZero:
      return MakeNan();
    case Type::kInf:
    case Type::kDefault:
      return MakeInf(GetResultSign(lhs, rhs));
  }
}

BigFloat
MulSpecial(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  switch (GetType(lhs)) {
    case Type::kNan:
      return lhs;
    case Type::kZero:
      return MulFromZero(lhs, rhs);
    case Type::kInf:
      return MulFromInf(lhs, rhs);
    case Type::kDefault:
      return MulSpecialFromNonSpecial(lhs, rhs);
  }
}

}  // namespace

BigFloat
Mul(const BigFloat& multiplicand, const BigFloat& multiplier) noexcept {
  if (IsSpecial(multiplicand) || IsSpecial(multiplier)) {
    return MulSpecial(multiplicand, multiplier);
  }
  return MulNonSpecial(multiplicand, multiplier);
}

}  // namespace big_float

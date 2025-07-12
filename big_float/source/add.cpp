#include <cstddef>
#include <cstdlib>

#include "big_float.hpp"
#include "big_uint.hpp"
#include "error.hpp"
#include "getters.hpp"
#include "sign.hpp"

using big_uint::BigUInt;

namespace big_float {
namespace {

BigFloat
AddNonSpecial(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  if (!IsEqual(GetSign(lhs), GetSign(rhs))) {
    return Sub(lhs, Neg(rhs));
  }

  const Exponent kLhsExp = GetExponent(lhs);
  const Exponent kRhsExp = GetExponent(rhs);
  const BigUInt& lhs_mantissa = GetMantissa(lhs);
  const BigUInt& rhs_mantissa = GetMantissa(rhs);

  BigUInt result_mantissa;
  Exponent result_exponent = kLhsExp;
  Sign result_sign = GetSign(lhs);

  if (kLhsExp == kRhsExp) {
    result_mantissa = big_uint::add(lhs_mantissa, rhs_mantissa);
    result_exponent = kLhsExp;
  } else if (kLhsExp > kRhsExp) {
    const auto kShift = static_cast<size_t>(kLhsExp - kRhsExp);
    result_mantissa = big_uint::add(lhs_mantissa, rhs_mantissa, kShift);
    result_exponent = kRhsExp;
  } else {
    const auto kShift = static_cast<size_t>(kRhsExp - kLhsExp);
    result_mantissa = big_uint::add(rhs_mantissa, lhs_mantissa, kShift);
    result_exponent = kLhsExp;
  }

  if (big_uint::isZero(result_mantissa)) {
    return MakeZero();
  }

  return MakeBigFloat(result_mantissa, result_exponent, result_sign,
                      Type::kDefault, GetDefaultError());
}

BigFloat
AddNonSpecialToSpecial(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  switch (GetType(rhs)) {
    case Type::kNan:
    case Type::kInf:
      return rhs;
    case Type::kZero:
      return lhs;
    case Type::kDefault:
      return AddNonSpecial(lhs, rhs);
  }
}

BigFloat
AddFromInf(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  switch (GetType(rhs)) {
    case Type::kNan:
      return rhs;
    case Type::kZero:
    case Type::kDefault:
      return lhs;
    case Type::kInf:
      bool is_equal_by_sign = IsEqual(GetSign(lhs), GetSign(rhs));
      return is_equal_by_sign ? lhs : MakeNan();
  }
}

BigFloat
AddSpecial(const BigFloat& lhs, const BigFloat& rhs) noexcept {
  switch (GetType(lhs)) {
    case Type::kNan:
      return lhs;
    case Type::kInf:
      return AddFromInf(lhs, rhs);
    case Type::kZero:
      return rhs;
    case Type::kDefault:
      return AddNonSpecialToSpecial(lhs, rhs);
  }
}

}  // namespace

BigFloat
Add(const BigFloat& augend, const BigFloat& addend) noexcept {
  if (IsSpecial(augend) || IsSpecial(addend)) {
    return AddSpecial(augend, addend);
  }
  return AddNonSpecial(augend, addend);
}

}  // namespace big_float

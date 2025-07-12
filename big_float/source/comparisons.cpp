#include <cstdint>

#include "big_float.hpp"
#include "big_uint.hpp"
#include "getters.hpp"
#include "sign.hpp"

using big_uint::BigUInt;

namespace big_float {
namespace {

enum class Comparison : int8_t {
  kGreater = 2,
  kEqual = 1,
  kNotEqual = -1,
  kLower = -2,
};

Comparison
Neg(Comparison value) {
  return Comparison(-static_cast<int8_t>(value));
}

Comparison
CompareBySign(const BigFloat& lhs, const BigFloat& rhs) {
  const Sign kLhsSign = GetSign(lhs);
  const Sign kRhsSign = GetSign(rhs);
  if (IsEqual(kLhsSign, kRhsSign)) {
    return Comparison::kEqual;
  }
  if (IsNegative(kRhsSign)) {
    return Comparison::kGreater;
  }
  return Comparison::kLower;
}

Comparison
CompareByLength(const BigFloat& lhs, const BigFloat& rhs) {
  const int64_t kLhsPower = CountPower(lhs);
  const int64_t kRhsPower = CountPower(rhs);
  if (kLhsPower == kRhsPower) {
    return Comparison::kEqual;
  }
  if (kLhsPower > kRhsPower) {
    return Comparison::kGreater;
  }
  return Comparison::kLower;
}

Comparison
CompareByValue(const BigFloat& lhs, const BigFloat& rhs) {
  const BigUInt kLhsMantissa = GetMantissa(lhs);
  const BigUInt kRhsMantissa = GetMantissa(rhs);
  if (isEqual(kLhsMantissa, kRhsMantissa)) {
    return Comparison::kEqual;
  }
  if (isGreater(kLhsMantissa, kRhsMantissa)) {
    return Comparison::kGreater;
  }
  return Comparison::kLower;
}

Comparison
CompareNonSpecial(const BigFloat& lhs, const BigFloat& rhs) {
  const Comparison kBySign = CompareBySign(lhs, rhs);
  if (kBySign != Comparison::kEqual) {
    return kBySign;
  }
  const Comparison kByLength = CompareByLength(lhs, rhs);
  if (kByLength != Comparison::kEqual) {
    return (IsNegative(lhs)) ? Neg(kByLength) : kByLength;
  }
  const Comparison kByValue = CompareByValue(lhs, rhs);
  return (IsNegative(lhs)) ? Neg(kByValue) : kByValue;
}

Comparison
CompareNonSpecialWithSpecial(const BigFloat& lhs, const BigFloat& rhs) {
  switch (GetType(rhs)) {
    case Type::kNan:
      return Comparison::kNotEqual;
    case Type::kZero:
      return IsNegative(lhs) ? Comparison::kLower : Comparison::kGreater;
    case Type::kInf:
      return IsNegative(rhs) ? Comparison::kGreater : Comparison::kLower;
    case Type::kDefault:
      return CompareNonSpecial(lhs, rhs);
  }
}

Comparison
CompareZero(const BigFloat& rhs) {
  switch (GetType(rhs)) {
    case Type::kNan:
      return Comparison::kNotEqual;
    case Type::kZero:
      return Comparison::kEqual;
    case Type::kInf:
    case Type::kDefault:
      return IsNegative(rhs) ? Comparison::kGreater : Comparison::kLower;
  }
}

Comparison
CompareInf(const BigFloat& lhs, const BigFloat& rhs) {
  switch (GetType(rhs)) {
    case Type::kNan:
      return Comparison::kNotEqual;
    case Type::kZero:
    case Type::kDefault:
      return IsNegative(lhs) ? Comparison::kLower : Comparison::kGreater;
    case Type::kInf:
      if (IsEqual(GetSign(lhs), GetSign(rhs))) {
        return Comparison::kEqual;
      }
      return IsNegative(lhs) ? Comparison::kLower : Comparison::kGreater;
  }
}

Comparison
CompareSpecial(const BigFloat& lhs, const BigFloat& rhs) {
  switch (GetType(lhs)) {
    case Type::kNan:
      return Comparison::kNotEqual;
    case Type::kInf:
      return CompareInf(lhs, rhs);
    case Type::kZero:
      return CompareZero(rhs);
    default:
      return CompareNonSpecialWithSpecial(lhs, rhs);
  }
}

Comparison
Compare(const BigFloat& lhs, const BigFloat& rhs) {
  if (IsSpecial(lhs) || IsSpecial(rhs)) {
    return CompareSpecial(lhs, rhs);
  }
  return CompareNonSpecial(lhs, rhs);
}

}  // namespace

bool
IsEqual(const BigFloat& left, const BigFloat& right) noexcept {
  return Compare(left, right) == Comparison::kEqual;
}

bool
IsGreater(const BigFloat& left, const BigFloat& right) noexcept {
  return Compare(left, right) == Comparison::kGreater;
}

bool
IsLower(const BigFloat& left, const BigFloat& right) noexcept {
  return Compare(left, right) == Comparison::kLower;
}

}  // namespace big_float

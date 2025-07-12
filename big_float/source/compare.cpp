#include <cstdint>

#include "big_float.hpp"
#include "big_uint.hpp"
#include "getters.hpp"

using big_uint::BigUInt;

namespace big_float {
namespace {

enum class Comparison : int8_t {
  kGreater = 1,
  kEqual = 0,
  kLower = -1,
};

Comparison
Neg(Comparison value) {
  return Comparison(-static_cast<int8_t>(value));
}

Comparison
CompareBySign(const BigFloat& lhs, const BigFloat& rhs) {
  const bool kLhsSign = GetSign(lhs);
  const bool kRhsSign = GetSign(rhs);
  if (kLhsSign == kRhsSign) {
    return Comparison::kEqual;
  }
  if (static_cast<int>(kLhsSign) < static_cast<int>(kRhsSign)) {
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
Compare(const BigFloat& lhs, const BigFloat& rhs) {
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

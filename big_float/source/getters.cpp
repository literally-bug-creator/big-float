#include "getters.hpp"

#include <cstddef>
#include <cstdint>

#include "big_float.hpp"
#include "big_uint.hpp"
#include "error.hpp"
#include "exponent.hpp"
#include "sign.hpp"
#include "type.hpp"

using big_uint::BigUInt;

namespace big_float {

Type
GetType(const BigFloat& number) noexcept {
  return number.type;
}

bool
IsZero(const BigFloat& number) noexcept {
  return GetType(number) == Type::kZero;
}

bool
IsInf(const BigFloat& number) noexcept {
  return GetType(number) == Type::kInf;
}

bool
IsNan(const BigFloat& number) noexcept {
  return GetType(number) == Type::kNan;
}

bool
IsSpecial(const BigFloat& number) noexcept {
  return GetType(number) != Type::kDefault;
}

Sign
GetSign(const BigFloat& number) noexcept {
  return number.sign;
}

bool
IsNegative(const BigFloat& number) noexcept {
  return GetSign(number) == GetNegative();
}

const BigUInt&
GetMantissa(const BigFloat& number) noexcept {
  return number.number;
}

Exponent
GetExponent(const BigFloat& number) noexcept {
  return number.exp;
}

const Error&
GetError(const BigFloat& number) noexcept {
  return number.error;
}

size_t
GetSize(const BigFloat& number) noexcept {
  return big_uint::getSize(GetMantissa(number));
}

int64_t
CountPower(const BigFloat& number) noexcept {
  return GetExponent(number) + static_cast<int64_t>(GetSize(number));
}

}  // namespace big_float

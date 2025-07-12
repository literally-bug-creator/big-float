#include <utility>

#include "big_float.hpp"
#include "big_uint.hpp"
#include "error.hpp"
#include "exponent.hpp"
#include "sign.hpp"
#include "type.hpp"

using big_uint::BigUInt;
using big_uint::makeZero;

namespace big_float {
namespace {

const BigUInt kZeroNumber = makeZero();
const BigUInt kInfNumber = makeZero();
const BigUInt kNanNumber = makeZero();

constexpr Exponent kZeroExp = 0;
constexpr Exponent kInfExp = 0;
constexpr Exponent kNanExp = 0;

}  // namespace

BigFloat
MakeBigFloat(BigUInt number, Exponent exp, Sign sign, Type type,
             Error error) noexcept {
  return {.number = std::move(number),
          .exp = exp,
          .type = type,
          .sign = sign,
          .error = error};
}

BigFloat
MakeZero(Sign sign, const Error& error) noexcept {
  return MakeBigFloat(kZeroNumber, kZeroExp, sign, Type::kZero, error);
}

BigFloat
MakeInf(Sign sign, const Error& error) noexcept {
  return MakeBigFloat(kInfNumber, kInfExp, sign, Type::kInf, error);
}

BigFloat
MakeNan(Sign sign, const Error& error) noexcept {
  return MakeBigFloat(kNanNumber, kNanExp, sign, Type::kNan, error);
}

}  // namespace big_float

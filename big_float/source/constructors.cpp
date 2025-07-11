#include <utility>

#include "big_float.hpp"
#include "big_uint.hpp"
#include "error.hpp"
#include "exponent.hpp"
#include "sign.hpp"
#include "type.hpp"

namespace big_float {
namespace {

const BigUInt ZERO_NUMBER = big_uint::makeZero();
const BigUInt INF_NUMBER = big_uint::makeZero();
const BigUInt NAN_NUMBER = big_uint::makeZero();

constexpr Exponent ZERO_EXP = 0;
constexpr Exponent INF_EXP = 0;
constexpr Exponent NAN_EXP = 0;

}  // namespace

BigFloat makeBigFloat(BigUInt number, Exponent exp, Sign sign, Type type, Error error) noexcept {
    return {.number = std::move(number), .exp = exp, .type = type, .sign = sign, .error = error};
}

BigFloat makeZero(Sign sign, const Error& error) noexcept {
    return makeBigFloat(ZERO_NUMBER, ZERO_EXP, sign, Type::ZERO, error);
}

BigFloat makeInf(Sign sign, const Error& error) noexcept {
    return makeBigFloat(INF_NUMBER, INF_EXP, sign, Type::INF, error);
}

BigFloat makeNan(Sign sign, const Error& error) noexcept {
    return makeBigFloat(NAN_NUMBER, NAN_EXP, sign, Type::NAN, error);
}

}  // namespace big_float

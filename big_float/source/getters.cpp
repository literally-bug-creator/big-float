#include "getters.hpp"

#include <cstdint>

#include "big_float.hpp"
#include "sign.hpp"

namespace big_float {

Type getType(const BigFloat& number) noexcept {
    return number.type;
}

bool isZero(const BigFloat& number) noexcept {
    return getType(number) == Type::ZERO;
}

bool isInf(const BigFloat& number) noexcept {
    return getType(number) == Type::INF;
}

bool isNan(const BigFloat& number) noexcept {
    return getType(number) == Type::NAN;
}

bool getSign(const BigFloat& number) noexcept {
    return number.sign;
}

bool isNegative(const BigFloat& number) noexcept {
    return getSign(number) == getNegative();
}

const BigUInt& getMantissa(const BigFloat& number) noexcept {
    return number.number;
}

Exponent getExponent(const BigFloat& number) noexcept {
    return number.exp;
}

size_t getSize(const BigFloat& number) noexcept {
    return getMantissa(number).limbs.size();  // TODO: Replace by public function of `BigUInt`
}

int64_t countPower(const BigFloat& number) noexcept {
    return getExponent(number) + static_cast<int64_t>(getSize(number));
}

}  // namespace big_float

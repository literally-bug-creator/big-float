#include "getters.hpp"

#include <cstdint>

namespace big_float {

const BigUInt& getMantissa(const BigFloat& number) {
    return number.mantissa;
}

Exponent getExponent(const BigFloat& number) {
    return number.exp;
}

BigFloatType getType(const BigFloat& number) {
    return number.type;
}

bool getSign(const BigFloat& number) {
    return number.isNegative;
}

bool isNegative(const BigFloat& number) {
    return getSign(number);
}

size_t getSize(const BigFloat& number) {
    return getMantissa(number).limbs.size();
}

int64_t countPower(const BigFloat& number) {
    return getExponent(number) + static_cast<int64_t>(getSize(number));
}

}  // namespace big_float

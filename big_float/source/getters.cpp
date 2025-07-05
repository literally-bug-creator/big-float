#include "getters.hpp"

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

}  // namespace big_float

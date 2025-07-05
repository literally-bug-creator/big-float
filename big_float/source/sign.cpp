#include "big_float.hpp"
#include "getters.hpp"

namespace big_float {
BigFloat abs(const BigFloat& number) {
    BigUInt mantissa = getMantissa(number);
    Exponent exp = getExponent(number);
    BigFloatType type = getType(number);
    Error error = getError(number);
    return makeBigFloat(std::move(mantissa), exp, false, type, error);
}

BigFloat neg(const BigFloat& number) {
    BigUInt mantissa = getMantissa(number);
    Exponent exp = getExponent(number);
    BigFloatType type = getType(number);
    Error error = getError(number);
    bool sign = !getSign(number);
    return makeBigFloat(std::move(mantissa), exp, sign, type, error);
}
}  // namespace big_float

#include <cstdint>

#include "big_float.hpp"
#include "big_uint.hpp"
#include "getters.hpp"

namespace big_float {
namespace {
enum class Comparison : int8_t {
    GREATER = 1,
    EQUAL = 0,
    LOWER = -1,
};

Comparison neg(Comparison value) {
    return Comparison(-int8_t(value));
}

Comparison compareBySign(const BigFloat& lhs, const BigFloat& rhs) {
    const bool LHS_SIGN = getSign(lhs);
    const bool RHS_SIGN = getSign(rhs);
    if (LHS_SIGN == RHS_SIGN) {
        return Comparison::EQUAL;
    }
    if (static_cast<int>(LHS_SIGN) < static_cast<int>(RHS_SIGN)) {
        return Comparison::GREATER;
    }
    return Comparison::LOWER;
}

Comparison compareByLength(const BigFloat& lhs, const BigFloat& rhs) {
    const int64_t LHS_POWER = countPower(lhs);
    const int64_t RHS_POWER = countPower(rhs);
    if (LHS_POWER == RHS_POWER) {
        return Comparison::EQUAL;
    }
    if (LHS_POWER > RHS_POWER) {
        return Comparison::GREATER;
    }
    return Comparison::LOWER;
}

Comparison compareByValue(const BigFloat& lhs, const BigFloat& rhs) {
    const BigUInt LHS_MANTISSA = getMantissa(lhs);
    const BigUInt RHS_MANTISSA = getMantissa(rhs);
    if (isEqual(LHS_MANTISSA, RHS_MANTISSA)) {
        return Comparison::EQUAL;
    }
    if (isGreater(LHS_MANTISSA, RHS_MANTISSA)) {
        return Comparison::GREATER;
    }
    return Comparison::LOWER;
}

Comparison compare(const BigFloat& lhs, const BigFloat& rhs) {
    const Comparison BY_SIGN = compareBySign(lhs, rhs);
    if (BY_SIGN != Comparison::EQUAL) {
        return BY_SIGN;
    }
    const Comparison BY_LENGTH = compareByLength(lhs, rhs);
    if (BY_LENGTH != Comparison::EQUAL) {
        return (isNegative(lhs)) ? neg(BY_LENGTH) : BY_LENGTH;
    }
    const Comparison BY_VALUE = compareByValue(lhs, rhs);
    return (isNegative(lhs)) ? neg(BY_VALUE) : BY_VALUE;
}

}  // namespace

bool isEqual(const BigFloat& left, const BigFloat& right) noexcept {
    return compare(left, right) == Comparison::EQUAL;
}

bool isGreater(const BigFloat& left, const BigFloat& right) noexcept {
    return compare(left, right) == Comparison::GREATER;
}

bool isLower(const BigFloat& left, const BigFloat& right) noexcept {
    return compare(left, right) == Comparison::LOWER;
}

}  // namespace big_float

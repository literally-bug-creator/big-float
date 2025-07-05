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
    bool lhsSign = getSign(lhs);
    bool rhsSign = getSign(rhs);
    if (lhsSign == rhsSign) {
        return Comparison::EQUAL;
    }
    if (static_cast<int>(lhsSign) < static_cast<int>(rhsSign)) {
        return Comparison::GREATER;
    }
    return Comparison::LOWER;
}

Comparison compareByLength(const BigFloat& lhs, const BigFloat& rhs) {
    int64_t lhsPower = countPower(lhs);
    int64_t rhsPower = countPower(rhs);
    if (lhsPower == rhsPower) {
        return Comparison::EQUAL;
    }
    if (lhsPower > rhsPower) {
        return Comparison::GREATER;
    }
    return Comparison::LOWER;
}

Comparison compareByValue(const BigFloat& lhs, const BigFloat& rhs) {
    BigUInt lhsMantissa = getMantissa(lhs);
    BigUInt rhsMantissa = getMantissa(rhs);
    if (isEqual(lhsMantissa, rhsMantissa)) {
        return Comparison::EQUAL;
    }
    if (isGreater(lhsMantissa, rhsMantissa)) {
        return Comparison::GREATER;
    }
    return Comparison::LOWER;
}

Comparison compare(const BigFloat& lhs, const BigFloat& rhs) {
    Comparison bySign = compareBySign(lhs, rhs);
    if (bySign != Comparison::EQUAL) {
        return bySign;
    }
    Comparison byLength = compareByLength(lhs, rhs);
    if (byLength != Comparison::EQUAL) {
        return (isNegative(lhs)) ? neg(byLength) : byLength;
    }
    Comparison byValue = compareByValue(lhs, rhs);
    return (isNegative(lhs)) ? neg(byValue) : byValue;
}
}  // namespace

bool isEqual(const BigFloat& left, const BigFloat& right) {
    return compare(left, right) == Comparison::EQUAL;
}

bool isGreater(const BigFloat& left, const BigFloat& right) {
    return compare(left, right) == Comparison::GREATER;
}

bool isLower(const BigFloat& left, const BigFloat& right) {
    return compare(left, right) == Comparison::LOWER;
}
}  // namespace big_float

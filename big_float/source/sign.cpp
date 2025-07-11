#include "sign.hpp"

namespace big_float {
namespace {
constexpr Sign POSITIVE = false;
constexpr Sign NEGATIVE = true;
}  // namespace

Sign getPositive() noexcept {
    return POSITIVE;
}

Sign getNegative() noexcept {
    return NEGATIVE;
}

bool isPositive(const Sign& sign) noexcept {
    return sign == POSITIVE;
}

bool isNegative(const Sign& sign) noexcept {
    return sign == NEGATIVE;
}

Sign invert(const Sign& sign) noexcept {
    return isPositive(sign) ? getNegative() : getPositive();
}

}  // namespace big_float

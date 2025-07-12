#include "sign.hpp"

namespace big_float {
namespace {

constexpr Sign kPositive = false;
constexpr Sign kNegative = true;

}  // namespace

Sign
GetPositive() noexcept {
  return kPositive;
}

Sign
GetNegative() noexcept {
  return kNegative;
}

bool
IsPositive(const Sign& sign) noexcept {
  return sign == kPositive;
}

bool
IsNegative(const Sign& sign) noexcept {
  return sign == kNegative;
}

Sign
Invert(const Sign& sign) noexcept {
  return IsPositive(sign) ? GetNegative() : GetPositive();
}

}  // namespace big_float

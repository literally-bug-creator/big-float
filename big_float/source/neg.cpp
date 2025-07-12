#include "big_float.hpp"
#include "getters.hpp"
#include "sign.hpp"

namespace big_float {

BigFloat
Neg(const BigFloat& number) noexcept {
  Sign sign = Invert(GetSign(number));
  return MakeBigFloat(GetMantissa(number), GetExponent(number), sign,
                      GetType(number), GetError(number));
}

}  // namespace big_float

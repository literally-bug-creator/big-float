#include "big_float.hpp"
#include "error.hpp"
#include "getters.hpp"
#include "sign.hpp"

namespace big_float {

BigFloat
Neg(const BigFloat& number) noexcept {
  const Sign kSign = Invert(GetSign(number));
  return MakeBigFloat(GetMantissa(number), GetExponent(number), kSign,
                      GetType(number), GetError(number));
}

}  // namespace big_float

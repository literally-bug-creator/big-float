#include "error.hpp"

namespace big_float {
namespace {
const Error kDefaultError = MakeError(ErrorCode::kOk);
}

Error
MakeError(ErrorCode code) noexcept {
  return Error{code};
}

const ErrorCode&
GetErrorCode(const Error& error) noexcept {
  return error.code;
}

bool
IsOk(const Error& error) noexcept {
  return GetErrorCode(error) == ErrorCode::kOk;
}

Error
GetDefaultError() noexcept {
  return kDefaultError;
}
}  // namespace big_float

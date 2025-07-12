#pragma once

#include <cstdint>

namespace big_float {
enum class ErrorCode : uint8_t {
  kOk,
  kError,
};

struct Error {
  ErrorCode code;
};

Error
MakeError(ErrorCode code) noexcept;

const ErrorCode&
GetErrorCode(const Error& error) noexcept;

bool
IsOk(const Error& error) noexcept;

Error
GetDefaultError() noexcept;
}  // namespace big_float

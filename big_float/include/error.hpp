#pragma once

#include <cstdint>

namespace big_float {
enum class ErrorCode : uint8_t {
    OK,
    ERROR,
};

struct Error {
    ErrorCode code;
};

Error makeError(ErrorCode code) noexcept;

const ErrorCode& getErrorCode(const Error& error) noexcept;

bool isOk(const Error& error) noexcept;

Error getDefaultError() noexcept;
}  // namespace big_float

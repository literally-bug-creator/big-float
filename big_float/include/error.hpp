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

Error makeError(ErrorCode code);

const ErrorCode& getErrorCode(const Error& error);

bool isOk(const Error& error);

Error getDefaultError();
}  // namespace big_number

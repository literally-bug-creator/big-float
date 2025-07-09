#include "error.hpp"

namespace big_float {
namespace {
const Error DEFAULT_ERROR = makeError(ErrorCode::OK);
}

Error makeError(ErrorCode code) noexcept {
    return Error{code};
}

const ErrorCode& getErrorCode(const Error& error) noexcept {
    return error.code;
}

bool isOk(const Error& error) noexcept {
    ErrorCode code = getErrorCode(error);
    return code == ErrorCode::OK;
}

Error getDefaultError() noexcept {
    return DEFAULT_ERROR;
}
}  // namespace big_float

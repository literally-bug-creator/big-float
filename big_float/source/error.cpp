#include "error.hpp"

namespace big_float {
Error makeError(ErrorCode code) {
    return Error{code};
}

const ErrorCode& getErrorCode(const Error& error) {
    return error.code;
}

bool isOk(const Error& error) {
    ErrorCode code = getErrorCode(error);
    return code == ErrorCode::OK;
}

Error getDefaultError() {
    return Error{ErrorCode::OK};
}
}  // namespace big_float

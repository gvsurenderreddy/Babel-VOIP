#include "ErrorStatus.hpp"

ErrorStatus::ErrorStatus(void) {
}

ErrorStatus::~ErrorStatus(void) {
}

bool	ErrorStatus::errorOccurred(void) const {
	return mErrorOccurred;
}

ErrorStatus::ErrorCode	ErrorStatus::getErrorCode(void) const {
	return mErrorCode;
}

void	ErrorStatus::setErrorOccurred(bool errorOccurred) {
	mErrorOccurred = errorOccurred;
}

void	ErrorStatus::setErrorCode(ErrorStatus::ErrorCode errorCode) {
	mErrorCode = errorCode;
}

#pragma once

class ErrorStatus {

	// error codes
	public:
		enum ErrorCode {
			OK = 0x01,
			THE_IMPOSSIBLE_HAPPENED = 0x02
		};

	// ctor dtor
	public:
		ErrorStatus(void);
		~ErrorStatus(void);

	// coplien form
	private:
		ErrorStatus(const ErrorStatus &) {}
		const ErrorStatus &operator=(const ErrorStatus &) { return *this; }

	// getters - setters
	public:
		bool					errorOccurred(void) const;
		ErrorStatus::ErrorCode	getErrorCode(void) const;

		void	setErrorOccurred(bool errorOccurred);
		void	setErrorCode(ErrorStatus::ErrorCode errorCode);

	// attributes
	private:
		bool					mErrorOccurred;
		ErrorStatus::ErrorCode	mErrorCode;

};

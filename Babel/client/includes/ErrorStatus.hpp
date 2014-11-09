#pragma once

class ErrorStatus {

	// error codes
	public:
		enum ErrorCode {
            OK                                          = 0x00,
            THE_IMPOSSIBLE_HAPPENED                     = 0x01,
            FAIL_INIT_SOCKET                            = 0x02,
            FAIL_INIT_AUDIO                             = 0x03,
            WRONG_PACKET_STRUCT                         = 0x04,
            REGISTER_ACC_ALREADY_USED                   = 0x05,
            LOGIN_WRONG_PASSWORD                        = 0x06,
            UNKNOWN_ACCOUNT                             = 0x07,
            ACTIONS_TO_OFFLINE_ACCOUNT                  = 0x08,
            CANNOT_DO_CALL_MULTIPLE                     = 0x09,
            CANNOT_ACCEPT_CALL_FROM_NOT_A_CALLER        = 0x0A,
            CANNOT_CLOSE_CALL_WHEN_YOU_ARENT_CALLING    = 0x0B,
            LOGIN_ON_ALREADY_LOGGED_ACCOUNT             = 0x0C,
            CANNOT_ADD_YOURSELF                         = 0x0D,
            CANNOT_CALL_YOURSELF                        = 0x0E,
            YOU_ARE_NOT_LOGGED                          = 0x0F,
            ALREADY_CONNECTED                           = 0x10,
            ALREADY_IN_YOUR_CONTACT_LIST                = 0x11,
            NOT_IN_YOUR_CONTACT_LIST                    = 0x12,
            BUSY_CONTACT_CANNOT_REPLY                   = 0x13,
            NOT_IN_COMMUNICATION_WITH_HIM               = 0x14,
            CANNOT_LOAD_DATA                            = 0x15,
            CANNOT_SAVE_DATA                            = 0x16,
            YOU_CANNOT_UPDATE_OTHER_ACCOUNT             = 0x17,
            INVALID_STATUS_ID                           = 0x18
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

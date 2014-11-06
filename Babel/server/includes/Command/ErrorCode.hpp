#pragma once

#include <string>

namespace ErrorCode {
	enum 
	{
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
            CANNOT_ACCEPT_CALL_FROM_NOT_A_CALLER        = 0x10,
            CANNOT_CLOSE_CALL_WHEN_YOU_ARENT_CALLING    = 0x11,
            LOGIN_ON_ALREADY_LOGGED_ACCOUNT             = 0x12,
            CANNOT_ADD_YOURSELF                         = 0x13,
            CANNOT_CALL_YOURSELF                        = 0x14,
            YOU_ARE_NOT_LOGGED	                        = 0x15,
            ALREADY_CONNECTED                           = 0x16,
            ALREADY_IN_YOUR_CONTACT_LIST                = 0x17,
            NOT_IN_YOUR_CONTACT_LIST                    = 0x18,
            BUSY_CONTACT_CANNOT_REPLY                   = 0x19,
            NOT_IN_COMMUNICATION_WITH_HIM               = 0x20
	};
    std::string getName(int errorCode);
}

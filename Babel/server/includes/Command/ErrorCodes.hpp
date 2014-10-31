namespace ErrorCode {
	enum 
	{
			OK						                    = 0x0000,
            THE_IMPOSSIBLE_HAPPENED                     = 0x0001,
            WRONG_PACKET_STRUCT                         = 0x0002,
            REGISTER_ACC_ALREADY_USED                   = 0x0003,
            LOGIN_WRONG_PASSWORD                        = 0x0004,
            UNKNOWN_ACCOUNT                             = 0x0005,
            ACTIONS_TO_OFFLINE_ACCOUNT                  = 0x0006,
            CANNOT_DO_CALL_MULTIPLE                     = 0x0007,
            CANNOT_ACCEPT_CALL_FROM_NOT_A_CALLER        = 0x0008,
            CANNOT_CLOSE_CALL_WHEN_YOU_ARENT_CALLING    = 0x0009,
            LOGIN_ON_ALREADY_LOGGED_ACCOUNT             = 0x0010,
            CANNOT_ADD_YOURSELF                         = 0x0011,
            CANNOT_CALL_YOURSELF                        = 0x0012
	};
}
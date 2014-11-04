#include "ErrorCode.hpp"

#include <string>

std::string ErrorCode::getName(int errorCode)
{
    switch (errorCode)
    {
    case ErrorCode::OK:
        return "OK";
    case ErrorCode::THE_IMPOSSIBLE_HAPPENED:
        return "THE_IMPOSSIBLE_HAPPENED";
    case ErrorCode::FAIL_INIT_SOCKET:
        return "FAIL_INIT_SOCKET";
    case ErrorCode::FAIL_INIT_AUDIO:
        return "FAIL_INIT_AUDIO";
    case ErrorCode::WRONG_PACKET_STRUCT:
        return "WRONG_PACKET_STRUCT";
    case ErrorCode::REGISTER_ACC_ALREADY_USED:
        return "REGISTER_ACC_ALREADY_USED";
    case ErrorCode::LOGIN_WRONG_PASSWORD:
        return "LOGIN_WRONG_PASSWORD";
    case ErrorCode::UNKNOWN_ACCOUNT:
        return "UNKNOWN_ACCOUNT";
    case ErrorCode::ACTIONS_TO_OFFLINE_ACCOUNT:
        return "ACTIONS_TO_OFFLINE_ACCOUNT";
    case ErrorCode::CANNOT_DO_CALL_MULTIPLE:
        return "CANNOT_DO_CALL_MULTIPLE";
    case ErrorCode::CANNOT_ACCEPT_CALL_FROM_NOT_A_CALLER:
        return "CANNOT_ACCEPT_CALL_FROM_NOT_A_CALLER";
    case ErrorCode::CANNOT_CLOSE_CALL_WHEN_YOU_ARENT_CALLING:
        return "CANNOT_CLOSE_CALL_WHEN_YOU_ARENT_CALLING";
    case ErrorCode::LOGIN_ON_ALREADY_LOGGED_ACCOUNT:
        return "LOGIN_ON_ALREADY_LOGGED_ACCOUNT";
    case ErrorCode::CANNOT_ADD_YOURSELF:
        return "CANNOT_ADD_YOURSELF";
    case ErrorCode::CANNOT_CALL_YOURSELF:
        return "CANNOT_CALL_YOURSELF";
    case ErrorCode::YOU_ARE_NOT_LOGGED:
        return "YOU_ARE_NOT_LOGGED";
    case ErrorCode::ALREADY_CONNECTED:
        return "ALREADY_CONNECTED";
    case ErrorCode::ALREADY_IN_YOUR_CONTACT_LIST:
        return "ALREADY_IN_YOUR_CONTACT_LIST";
    case ErrorCode::NOT_IN_YOUR_CONTACT_LIST:
        return "NOT_IN_YOUR_CONTACT_LIST";
    case ErrorCode::BUSY_CONTACT_CANNOT_REPLY:
        return "BUSY_CONTACT_CANNOT_REPLY";
    case ErrorCode::NOT_IN_COMMUNICATION_WITH_HIM:
        return "NOT_IN_COMMUNICATION_WITH_HIM";
    default:
        return "UNKNOWN";
    }
}
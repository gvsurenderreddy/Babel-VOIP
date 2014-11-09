#include "Command/CommandHandshake.hpp"

std::vector<std::string>		*CommandHandshake::getParam(IClientSocket *){
    return new std::vector<std::string>;
}

IClientSocket::Message			*CommandHandshake::setParam(const std::vector<std::string> &param){

    CommandHandshake::BodySend		*bodySend = new CommandHandshake::BodySend;
    IClientSocket::Message		*msg = new IClientSocket::Message;

    std::memset(bodySend, 0, sizeof(CommandHandshake::BodySend));
    bodySend->header.instructionCode = ICommand::HANDSHAKE;
    bodySend->header.magicCode = ICommand::MAGIC_CODE;

    msg->msgSize = sizeof(CommandHandshake::BodySend);
    msg->msg = reinterpret_cast<char *>(bodySend);

    return (msg);
}

unsigned int					CommandHandshake::getSizeBody(void){
	return 0;
}
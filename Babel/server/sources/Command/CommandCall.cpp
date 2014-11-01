#include "Command/CommandCall.hpp"

CommandCall::CommandCall(){

}
CommandCall::~CommandCall(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandCall::getParam(IClientSocket *socket){

	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandCall::Body			*body = NULL;
	IClientSocket::Message		data;

    std::memset(body, 0, this->getSizeBody());
	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandCall::Body *>(data.msg);

	t->push_back(body->accountName);

	return t;
}

IClientSocket::Message		    *CommandCall::setParam(std::vector<std::string> *param){

    CommandCall::BodySend       *bodySend = new CommandCall::BodySend;
    IClientSocket::Message		*msg = new IClientSocket::Message;

    std::memset(bodySend, 0, sizeof(CommandCall::BodySend));
    bodySend->header.instructionCode = ICommand::CALL;
    bodySend->header.magicCode = ICommand::MAGIC_CODE;
    std::memcpy(bodySend->accountName, (*param)[0].c_str(), MIN((*param)[0].size(), sizeof(bodySend->accountName) - 1));

    msg->msgSize = sizeof(CommandCall::BodySend);
    msg->msg = reinterpret_cast<char *>(bodySend);

    return (msg);
}

unsigned int				    CommandCall::getSizeBody(void){
	return sizeof(CommandCall::Body);
}
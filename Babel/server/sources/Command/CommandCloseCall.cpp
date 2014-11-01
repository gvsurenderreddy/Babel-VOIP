#include "Command/CommandCloseCall.hpp"

CommandCloseCall::CommandCloseCall(){

}
CommandCloseCall::~CommandCloseCall(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandCloseCall::getParam(IClientSocket *socket){

	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandCloseCall::Body		*body = NULL;
	IClientSocket::Message		data;

	std::memset(body, 0, this->getSizeBody());
	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandCloseCall::Body *>(data.msg);

	t->push_back(body->accountName);

	return t;
}

IClientSocket::Message			*CommandCloseCall::setParam(std::vector<std::string> *param){

	IClientSocket::Message		*msg = new IClientSocket::Message;
	CommandCloseCall::BodySend	*bodySend = new CommandCloseCall::BodySend;

	std::memset(bodySend, 0, sizeof(CommandCloseCall::BodySend));
	bodySend->header.instructionCode = ICommand::CLOSE_CALL;
	bodySend->header.magicCode = ICommand::MAGIC_CODE;
	std::memcpy(bodySend->accountName, (*param)[0].c_str(), MIN((*param)[0].size(), sizeof(bodySend->accountName) - 1));

	msg->msgSize = sizeof(CommandCloseCall::BodySend);
	msg->msg = reinterpret_cast<char *>(bodySend);

	return (msg);
}

unsigned int					CommandCloseCall::getSizeBody(void){
	return sizeof(CommandCloseCall::Body);
}
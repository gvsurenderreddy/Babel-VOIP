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
	CommandCloseCall::Body			*body;
	IClientSocket::Message		data;

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandCloseCall::Body *>(data.msg);
	t->push_back(body->accountName);
	return t;
}

IClientSocket::Message		*CommandCloseCall::setParam(std::vector<std::string> *param){
	IClientSocket::Message		*msg = new IClientSocket::Message;
	CommandCloseCall::BodySend	*body = new CommandCloseCall::BodySend;

	std::memset(body, 0, sizeof(*body));
	body->header.instructionCode = ICommand::CLOSE_CALL;
	body->header.magicCode = ICommand::MAGIC_CODE;
	std::memcpy(body->accountName, (*param)[0].c_str(), (*param)[0].size());

	msg->msgSize = sizeof(*body);
	msg->msg = reinterpret_cast<char *>(body);
	return (msg);
}

unsigned int				CommandCloseCall::getSizeBody(void){
	return sizeof CommandCloseCall::Body;
}
#include "Command/CommandAcceptCall.hpp"

CommandAcceptCall::CommandAcceptCall(){

}
CommandAcceptCall::~CommandAcceptCall(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandAcceptCall::getParam(IClientSocket *socket){

	std::vector<std::string>	*t = new std::vector<std::string>;
    CommandAcceptCall::Body 	*body = new CommandAcceptCall::Body;
	IClientSocket::Message		data;
	std::string					status = "";

	std::memset(body, 0, this->getSizeBody());
	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandAcceptCall::Body *>(data.msg);

	t->push_back(body->accountName);
	status += body->hasAccepted;
	t->push_back(status);

	return t;
}

IClientSocket::Message			*CommandAcceptCall::setParam(const std::vector<std::string> &param){

	CommandAcceptCall::BodySend	*bodySend = new CommandAcceptCall::BodySend;
	IClientSocket::Message		*msg = new IClientSocket::Message;

	std::memset(bodySend, 0, sizeof(CommandAcceptCall::BodySend));
	bodySend->header.instructionCode = ICommand::ACCEPT_CALL;
	bodySend->header.magicCode = ICommand::MAGIC_CODE;
	std::memcpy(bodySend->accountName, param[0].c_str(), MIN(param[0].size(), sizeof(bodySend->accountName) - 1));
	std::memcpy(bodySend->host, param[1].c_str(), MIN(param[1].size(), sizeof(bodySend->host) - 1));
	bodySend->hasAccepted = param[2][0];

	msg->msgSize = sizeof(CommandAcceptCall::BodySend);
	msg->msg = reinterpret_cast<char *>(bodySend);

	return (msg);
}

unsigned int					CommandAcceptCall::getSizeBody(void){
	return sizeof(CommandAcceptCall::Body);
}
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
	CommandAcceptCall::Body			*body;
	IClientSocket::Message		data;
	std::string					status = "";

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandAcceptCall::Body *>(data.msg);
	t->push_back(body->accountName);
	status += body->hasAccepted;
	t->push_back(status);
	return t;
}

IClientSocket::Message		*CommandAcceptCall::setParam(std::vector<std::string> *param){
	CommandAcceptCall::BodySend	*body = new CommandAcceptCall::BodySend;
	IClientSocket::Message		*msg = new IClientSocket::Message;

	std::memset(body, 0, sizeof(*body));
	body->header.instructionCode = ICommand::ACCEPT_CALL;
	body->header.magicCode = ICommand::MAGIC_CODE;

	std::memcpy(body->accountName, (*param)[0].c_str(), (*param)[0].size());
	std::memcpy(body->host, (*param)[1].c_str(), (*param)[1].size());
	body->hasAccepted = (*param)[2][0];

	msg->msgSize = sizeof(*body);
	msg->msg = reinterpret_cast<char *>(body);
	return (msg);
}

unsigned int				CommandAcceptCall::getSizeBody(void){
	return sizeof CommandAcceptCall::Body;
}
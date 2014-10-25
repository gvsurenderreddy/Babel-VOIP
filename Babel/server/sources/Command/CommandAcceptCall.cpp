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
	param;
	return NULL;
}

int							CommandAcceptCall::getSizeBody(void){
	return sizeof CommandAcceptCall::Body;
}
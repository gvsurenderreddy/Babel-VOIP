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
	param;
	return NULL;
}

int							CommandCloseCall::getSizeBody(void){
	return sizeof CommandCloseCall::Body;
}
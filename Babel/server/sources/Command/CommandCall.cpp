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
	CommandCall::Body			*body;
	IClientSocket::Message		data;

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandCall::Body *>(data.msg);
	t->push_back(body->accountName);
	return t;
}

IClientSocket::Message		*CommandCall::setParam(std::vector<std::string> *param){
	param;
	return NULL;
}

int							CommandCall::getSizeBody(void){
	return sizeof CommandCall::Body;
}
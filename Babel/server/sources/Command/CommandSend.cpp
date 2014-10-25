#include "Command/CommandSend.hpp"

CommandSend::CommandSend(){

}
CommandSend::~CommandSend(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandSend::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandSend::Body			*body;
	IClientSocket::Message		data;

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandSend::Body *>(data.msg);
	t->push_back(body->accountName);
	t->push_back(body->accountName);
	return t;
}

IClientSocket::Message		*CommandSend::setParam(std::vector<std::string> *param){
	param;
	return NULL;
}

int							CommandSend::getSizeBody(void){
	return sizeof CommandSend::Body;
}
#include "Command/CommandDel.hpp"

CommandDel::CommandDel(){

}
CommandDel::~CommandDel(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandDel::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandDel::Body			*body;
	IClientSocket::Message		data;

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandDel::Body *>(data.msg);
	t->push_back(body->accountName);
	return t;
}

IClientSocket::Message			*CommandDel::setParam(std::vector<std::string> *param){
	param;
	return NULL;
}

int							CommandDel::getSizeBody(void){
	return sizeof CommandDel::Body;
}
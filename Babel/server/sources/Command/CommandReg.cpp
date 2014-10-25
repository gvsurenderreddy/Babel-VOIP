#include "Command/CommandReg.hpp"

CommandReg::CommandReg(){

}
CommandReg::~CommandReg(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandReg::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandReg::Body			*body;
	IClientSocket::Message		data;

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandReg::Body *>(data.msg);
	t->push_back(body->accountName);
	t->push_back(body->pseudo);
	t->push_back(body->password);
	return t;
}

IClientSocket::Message		*CommandReg::setParam(std::vector<std::string> *param){
	param;
	return NULL;
}

int							CommandReg::getSizeBody(void){
	return sizeof CommandReg::Body;
}
#include "Command/CommandReg.hpp"

std::vector<std::string>		*CommandReg::getParam(IClientSocket *socket){

    CommandReg::Body			*body = new CommandReg::Body;
	std::vector<std::string>	*t = new std::vector<std::string>;
	IClientSocket::Message		data;

	std::memset(body, 0, this->getSizeBody());
	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandReg::Body *>(data.msg);

	t->push_back(body->accountName);
	t->push_back(body->pseudo);
	t->push_back(body->password);

	return t;
}

IClientSocket::Message			*CommandReg::setParam(const std::vector<std::string> &){
	return NULL;
}

unsigned int					CommandReg::getSizeBody(void){
	return sizeof(CommandReg::Body);
}
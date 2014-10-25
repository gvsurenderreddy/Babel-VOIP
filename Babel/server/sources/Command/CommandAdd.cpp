#include "../../includes/Command/CommandAdd.hpp"

CommandAdd::CommandAdd(){

}
CommandAdd::~CommandAdd(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>	*CommandAdd::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandAdd::Body			*body;
	IClientSocket::Message		data;

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandAdd::Body *>(data.msg);
	t->push_back(body->accountName);
	return t;
}

IClientSocket::Message		*CommandAdd::setParam(std::vector<std::string> *param){
	param;
	return NULL;
}

int							CommandAdd::getSizeBody(void){
	return sizeof CommandAdd::Body;
}
#include "Command/CommandUpdate.hpp"

CommandUpdate::CommandUpdate(){

}
CommandUpdate::~CommandUpdate(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandUpdate::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandUpdate::Body			*body;
	IClientSocket::Message		data;
	std::string					status = "";

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandUpdate::Body *>(data.msg);
	t->push_back(body->accountName);
	t->push_back(body->pseudo);
	t->push_back(body->password);
	status += body->status;
	t->push_back(status);
	return t;
}

IClientSocket::Message		*CommandUpdate::setParam(std::vector<std::string> *param){
	param;
	return NULL;
}

unsigned int    			CommandUpdate::getSizeBody(void){
	return sizeof CommandUpdate::Body;
}
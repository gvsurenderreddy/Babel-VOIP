#include "Command/CommandAcceptAdd.hpp"

CommandAcceptAdd::CommandAcceptAdd(){

}
CommandAcceptAdd::~CommandAcceptAdd(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandAcceptAdd::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandAcceptAdd::Body		*body;
	IClientSocket::Message		data;
	std::string					status = "";

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandAcceptAdd::Body *>(data.msg);
	t->push_back(body->accountName);
	status += body->hasAccepted;
	t->push_back(status);
	return t;
}

IClientSocket::Message		*CommandAcceptAdd::setParam(std::vector<std::string> *param){
	param;
	return NULL;
}

unsigned int				CommandAcceptAdd::getSizeBody(void){
	return sizeof CommandAcceptAdd::Body;
}
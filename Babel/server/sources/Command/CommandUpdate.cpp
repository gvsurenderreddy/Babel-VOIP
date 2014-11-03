#include "Command/CommandUpdate.hpp"

CommandUpdate::CommandUpdate(){

}
CommandUpdate::~CommandUpdate(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandUpdate::getParam(IClientSocket *socket){

    CommandUpdate::Body			*body = new CommandUpdate::Body;
	std::vector<std::string>	*t = new std::vector<std::string>;
	IClientSocket::Message		data;
	std::string					status = "";

	std::memset(body, 0, this->getSizeBody());
	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandUpdate::Body *>(data.msg);

	t->push_back(body->accountName);
	t->push_back(body->pseudo);
	t->push_back(body->password);
	status += body->status;
	t->push_back(status);

	return t;
}

IClientSocket::Message			*CommandUpdate::setParam(const std::vector<std::string> &){
	return NULL;
}

unsigned int    				CommandUpdate::getSizeBody(void){
	return sizeof(CommandUpdate::Body);
}
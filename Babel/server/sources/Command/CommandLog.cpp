#include "Command/CommandLog.hpp"

CommandLog::CommandLog(){

}
CommandLog::~CommandLog(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandLog::getParam(IClientSocket *socket){

    CommandLog::Body            *body = new CommandLog::Body;
	std::vector<std::string>	*t = new std::vector<std::string>;
	IClientSocket::Message		data;

	std::memset(body, 0, this->getSizeBody());
	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandLog::Body*>(data.msg);

	t->push_back(body->accountName);
	t->push_back(body->password);

	return t;
}

IClientSocket::Message			*CommandLog::setParam(const std::vector<std::string> &){
	return NULL;
}

unsigned int					CommandLog::getSizeBody(void){
	return sizeof(CommandLog::Body);
}
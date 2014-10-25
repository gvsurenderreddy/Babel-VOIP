#include "Command/CommandLog.hpp"

CommandLog::CommandLog(){

}
CommandLog::~CommandLog(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandLog::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandLog::Body			*body;
	IClientSocket::Message		data;

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandLog::Body *>(data.msg);
	t->push_back(body->accountName);
	t->push_back(body->password);
	return t;
}

IClientSocket::Message		*CommandLog::setParam(std::vector<std::string> *param){
	param;
	return NULL;
}

int							CommandLog::getSizeBody(void){
	return sizeof CommandLog::Body;
}
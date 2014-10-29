#include "Command/CommandShow.hpp"
#include <cstring>

CommandShow::CommandShow(){

}
CommandShow::~CommandShow(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandShow::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandShow::Body			*body;
	IClientSocket::Message		data;

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandShow::Body *>(data.msg);
	t->push_back(body->accountName);
	return t;
}

IClientSocket::Message			*CommandShow::setParam(std::vector<std::string> *param){
	IClientSocket::Message		*msg = new IClientSocket::Message;
	CommandShow::BodySend		*body = new CommandShow::BodySend;

	std::memset(body, 0, sizeof(*body));
	body->header.instructionCode = ICommand::SHOW;
	body->header.magicCode = ICommand::MAGIC_CODE;
	std::memcpy(body->accountName, (*param)[0].c_str(), (*param)[0].size());
	std::memcpy(body->pseudo, (*param)[1].c_str(), (*param)[1].size());
	body->status = (*param)[2][0];
	body->isConnected = (*param)[3][0];

	msg->msgSize = sizeof(*body);
	msg->msg = reinterpret_cast<char *>(body);
	return (msg);
}

unsigned int				CommandShow::getSizeBody(void){
	return sizeof CommandShow::Body;
}
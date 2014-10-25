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

	std::memset(body, 0, sizeof(body));
	param;
	body->header.instructionCode = ICommand::ERR;
	body->header.magicCode = ICommand::MAGIC_CODE;
	std::memcpy(body->accountName, "Zer", 3);
	body->isConnected = 1;
	std::memcpy(body->pseudo, "yolo", 4);
	body->status = 9;

	msg->msgSize = sizeof(body);
	msg->msg = reinterpret_cast<char *>(body);
	return (msg);
}

int							CommandShow::getSizeBody(void){
	return sizeof CommandShow::Body;
}
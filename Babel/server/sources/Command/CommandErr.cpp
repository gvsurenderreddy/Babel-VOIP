#include "Command/CommandErr.hpp"

CommandErr::CommandErr(){

}
CommandErr::~CommandErr(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandErr::getParam(IClientSocket *socket){
	socket;
	return NULL;
}

IClientSocket::Message			*CommandErr::setParam(std::vector<std::string> *param){
	IClientSocket::Message		*msg = new IClientSocket::Message;
	CommandErr::Body			*body = new CommandErr::Body;

	param;
	body->header.instructionCode = ICommand::ERR;
	body->header.magicCode = ICommand::MAGIC_CODE;
	body->errorCode = 0;
	body->instructionCode = ICommand::UPDATE;

	msg->msgSize = sizeof(*body);
	msg->msg = reinterpret_cast<char *>(body);
	return (msg);
}

int								CommandErr::getSizeBody(void){
	return sizeof CommandErr::Body;
}
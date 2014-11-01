#include "Command/CommandErr.hpp"

CommandErr::CommandErr(){

}
CommandErr::~CommandErr(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandErr::getParam(IClientSocket *){
	return NULL;
}

IClientSocket::Message			*CommandErr::setParam(const std::vector<std::string> &param){

    CommandErr::Body			*body = new CommandErr::Body;
	IClientSocket::Message		*msg = new IClientSocket::Message;

    std::memset(body, 0, this->getSizeBody());

	body->header.instructionCode = ICommand::ERR;
	body->header.magicCode = ICommand::MAGIC_CODE;

	body->errorCode = param[0][0];
	body->instructionCode = param[1][0];

    std::cout << "  [ERR] [" << body->errorCode << "] body->instructionCode [" << body->instructionCode <<"]" << std::endl;

	msg->msgSize = this->getSizeBody();
	msg->msg = reinterpret_cast<char *>(body);

	return (msg);
}

unsigned int					CommandErr::getSizeBody(void){
	return sizeof(CommandErr::Body);
}
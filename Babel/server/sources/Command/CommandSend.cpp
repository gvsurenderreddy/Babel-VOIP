#include "Command/CommandSend.hpp"

CommandSend::CommandSend(){

}
CommandSend::~CommandSend(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandSend::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandSend::Body			*body;
	IClientSocket::Message		data;

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandSend::Body *>(data.msg);
	t->push_back(body->accountName);
    t->push_back(body->textMessage);
	return t;
}

IClientSocket::Message		*CommandSend::setParam(std::vector<std::string> *param){
    CommandSend::BodySend	*body = new CommandSend::BodySend;
    IClientSocket::Message	*msg = new IClientSocket::Message;

    std::memset(body, 0, sizeof(*body));
    body->header.instructionCode = ICommand::SEND;
    body->header.magicCode = ICommand::MAGIC_CODE;

    std::memcpy(body->accountName, (*param)[0].c_str(), (*param)[0].size());
    std::memcpy(body->textMessage, (*param)[1].c_str(), (*param)[1].size());

    msg->msgSize = sizeof(*body);
    msg->msg = reinterpret_cast<char *>(body);
    return (msg);
}

unsigned int				CommandSend::getSizeBody(void){
	return sizeof CommandSend::Body;
}
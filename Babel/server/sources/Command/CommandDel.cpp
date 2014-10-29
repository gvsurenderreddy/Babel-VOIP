#include "Command/CommandDel.hpp"

CommandDel::CommandDel(){

}
CommandDel::~CommandDel(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandDel::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandDel::Body			*body;
	IClientSocket::Message		data;

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandDel::Body *>(data.msg);
	t->push_back(body->accountName);
	return t;
}

IClientSocket::Message			*CommandDel::setParam(std::vector<std::string> *param){
	CommandDel::BodySend	*body = new CommandDel::BodySend;
	IClientSocket::Message	*msg = new IClientSocket::Message;

	std::memset(body, 0, sizeof(*body));
	body->header.instructionCode = ICommand::DEL;
	body->header.magicCode = ICommand::MAGIC_CODE;

	std::memcpy(body->accountName, (*param)[0].c_str(), (*param)[0].size());

	msg->msgSize = sizeof(*body);
	msg->msg = reinterpret_cast<char *>(body);
	return (msg);
}

unsigned int    				CommandDel::getSizeBody(void){
	return sizeof CommandDel::Body;
}
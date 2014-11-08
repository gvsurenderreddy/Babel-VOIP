#include "Command/CommandDel.hpp"

std::vector<std::string>		*CommandDel::getParam(IClientSocket *socket){

	std::vector<std::string>	*t = new std::vector<std::string>;
    CommandDel::Body			*body = new CommandDel::Body;
	IClientSocket::Message		data;

	std::memset(body, 0, this->getSizeBody());
	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandDel::Body *>(data.msg);

	t->push_back(body->accountName);

	return t;
}

IClientSocket::Message			*CommandDel::setParam(const std::vector<std::string> &param){

	CommandDel::BodySend		*bodySend = new CommandDel::BodySend;
	IClientSocket::Message		*msg = new IClientSocket::Message;

	std::memset(bodySend, 0, sizeof(CommandDel::BodySend));
	bodySend->header.instructionCode = ICommand::DEL;
	bodySend->header.magicCode = ICommand::MAGIC_CODE;
	std::memcpy(bodySend->accountName, param[0].c_str(), MIN(param[0].size(), sizeof(bodySend->accountName) - 1));

	msg->msgSize = sizeof(CommandDel::BodySend);
	msg->msg = reinterpret_cast<char *>(bodySend);

	return (msg);
}

unsigned int    				CommandDel::getSizeBody(void){
	return sizeof(CommandDel::Body);
}
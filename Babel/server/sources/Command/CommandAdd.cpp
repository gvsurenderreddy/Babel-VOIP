#include "Command/CommandAdd.hpp"

std::vector<std::string>		*CommandAdd::getParam(IClientSocket *socket){

	std::vector<std::string>	*t = new std::vector<std::string>;
    CommandAdd::Body			*body = new CommandAdd::Body;
	IClientSocket::Message		data;

	std::memset(body, 0, this->getSizeBody());
	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandAdd::Body*>(data.msg);

	t->push_back(body->accountName);

	return t;
}

IClientSocket::Message			*CommandAdd::setParam(const std::vector<std::string> &param){

	CommandAdd::BodySend		*bodySend = new CommandAdd::BodySend;
	IClientSocket::Message		*msg = new IClientSocket::Message;

	std::memset(bodySend, 0, sizeof(CommandAdd::BodySend));
	bodySend->header.instructionCode = ICommand::ADD;
	bodySend->header.magicCode = ICommand::MAGIC_CODE;
	std::memcpy(bodySend->accountName, param[0].c_str(), MIN(param[0].size(), sizeof(bodySend->accountName) - 1));

	msg->msgSize = sizeof(CommandAdd::BodySend);
	msg->msg = reinterpret_cast<char*>(bodySend);

	return (msg);
}

unsigned int    				CommandAdd::getSizeBody(void){
	return sizeof(CommandAdd::Body);
}
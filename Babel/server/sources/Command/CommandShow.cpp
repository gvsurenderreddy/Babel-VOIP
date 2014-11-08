#include "Command/CommandShow.hpp"
#include <cstring>

std::vector<std::string>		*CommandShow::getParam(IClientSocket *socket){

    CommandShow::Body			*body = new CommandShow::Body;
	std::vector<std::string>	*t = new std::vector<std::string>;
	IClientSocket::Message		data;

	std::memset(body, 0, this->getSizeBody());
	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandShow::Body *>(data.msg);

	t->push_back(body->accountName);

	return t;
}

IClientSocket::Message			*CommandShow::setParam(const std::vector<std::string> &param){

	IClientSocket::Message		*msg = new IClientSocket::Message;
	CommandShow::BodySend		*bodySend = new CommandShow::BodySend;

	std::memset(bodySend, 0, sizeof(CommandShow::BodySend));
	bodySend->header.instructionCode = ICommand::SHOW;
	bodySend->header.magicCode = ICommand::MAGIC_CODE;
	std::memcpy(bodySend->accountName, param[0].c_str(), MIN(param[0].size(), sizeof(bodySend->accountName) - 1));
	std::memcpy(bodySend->pseudo, param[1].c_str(), MIN(param[1].size(), sizeof(bodySend->pseudo) - 1));
	bodySend->status = param[2][0];
	bodySend->isConnected = param[3][0];

	msg->msgSize = sizeof(CommandShow::BodySend);
	msg->msg = reinterpret_cast<char *>(bodySend);

	return (msg);
}

unsigned int					CommandShow::getSizeBody(void){
	return sizeof(CommandShow::Body);
}
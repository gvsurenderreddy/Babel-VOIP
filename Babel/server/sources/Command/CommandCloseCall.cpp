#include "Command/CommandCloseCall.hpp"

std::vector<std::string>		*CommandCloseCall::getParam(IClientSocket *socket){

	std::vector<std::string>	*t = new std::vector<std::string>;
    CommandCloseCall::Body		*body = new CommandCloseCall::Body;
	IClientSocket::Message		data;

	std::memset(body, 0, this->getSizeBody());
	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandCloseCall::Body *>(data.msg);

	t->push_back(body->accountName);

	return t;
}

IClientSocket::Message			*CommandCloseCall::setParam(const std::vector<std::string> &param){

    CommandCloseCall::BodySend	*bodySend = new CommandCloseCall::BodySend;
	IClientSocket::Message		*msg = new IClientSocket::Message;

	std::memset(bodySend, 0, sizeof(CommandCloseCall::BodySend));
	bodySend->header.instructionCode = ICommand::CLOSE_CALL;
	bodySend->header.magicCode = ICommand::MAGIC_CODE;
	std::memcpy(bodySend->accountName, param[0].c_str(), MIN(param[0].size(), sizeof(bodySend->accountName) - 1));

	msg->msgSize = sizeof(CommandCloseCall::BodySend);
	msg->msg = reinterpret_cast<char *>(bodySend);

	return (msg);
}

unsigned int					CommandCloseCall::getSizeBody(void){
	return sizeof(CommandCloseCall::Body);
}
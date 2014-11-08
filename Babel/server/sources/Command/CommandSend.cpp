#include "Command/CommandSend.hpp"

std::vector<std::string>		*CommandSend::getParam(IClientSocket *socket){

    CommandSend::Body			*body = new CommandSend::Body;
	std::vector<std::string>	*t = new std::vector<std::string>;
	IClientSocket::Message		data;

    std::memset(body, 0, this->getSizeBody());
	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandSend::Body *>(data.msg);

	t->push_back(body->accountName);
    t->push_back(body->textMessage);

	return t;
}

IClientSocket::Message		    *CommandSend::setParam(const std::vector<std::string> &param){

    CommandSend::BodySend	    *bodySend = new CommandSend::BodySend;
    IClientSocket::Message	    *msg = new IClientSocket::Message;

    std::memset(bodySend, 0, sizeof(CommandSend::BodySend));
    bodySend->header.instructionCode = ICommand::SEND;
    bodySend->header.magicCode = ICommand::MAGIC_CODE;

    std::memcpy(bodySend->accountName, param[0].c_str(), MIN(param[0].size(), sizeof(bodySend->accountName) - 1));
    std::memcpy(bodySend->textMessage, param[1].c_str(), MIN(param[1].size(), sizeof(bodySend->textMessage) - 1));

    msg->msgSize = sizeof(CommandSend::BodySend);
    msg->msg = reinterpret_cast<char *>(bodySend);

    return (msg);
}

unsigned int				    CommandSend::getSizeBody(void){
	return sizeof(CommandSend::Body);
}
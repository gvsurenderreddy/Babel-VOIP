#include "Command/CommandAcceptAdd.hpp"

CommandAcceptAdd::CommandAcceptAdd(){

}
CommandAcceptAdd::~CommandAcceptAdd(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandAcceptAdd::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandAcceptAdd::Body		*body;
	IClientSocket::Message		data;
	std::string					status = "";

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandAcceptAdd::Body *>(data.msg);
	t->push_back(body->accountName);
	status += body->hasAccepted;
	t->push_back(status);
	return t;
}

IClientSocket::Message		*CommandAcceptAdd::setParam(std::vector<std::string> *param){
	CommandAcceptAdd::BodySend	*body = new CommandAcceptAdd::BodySend;
	IClientSocket::Message		*msg = new IClientSocket::Message;

	std::memset(body, 0, sizeof(*body));
	body->header.instructionCode = ICommand::ACCEPT_ADD;
	body->header.magicCode = ICommand::MAGIC_CODE;

	std::memcpy(body->accountName, (*param)[0].c_str(), (*param)[0].size());
	body->hasAccepted = (*param)[1][0];

	msg->msgSize = sizeof(*body);
	msg->msg = reinterpret_cast<char *>(body);
	return (msg);
}

unsigned int				CommandAcceptAdd::getSizeBody(void){
	return sizeof(CommandAcceptAdd::Body);
}
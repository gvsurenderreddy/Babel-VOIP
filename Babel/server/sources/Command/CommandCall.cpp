#include "Command/CommandCall.hpp"

CommandCall::CommandCall(){

}
CommandCall::~CommandCall(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandCall::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandCall::Body			*body;
	IClientSocket::Message		data;

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandCall::Body *>(data.msg);
	t->push_back(body->accountName);
	return t;
}

IClientSocket::Message		*CommandCall::setParam(std::vector<std::string> *param){
    IClientSocket::Message		*msg = new IClientSocket::Message;
    CommandCall::BodySend		*body = new CommandCall::BodySend;

    std::memset(body, 0, sizeof(*body));
    body->header.instructionCode = ICommand::CALL;
    body->header.magicCode = ICommand::MAGIC_CODE;
    std::memcpy(body->accountName, (*param)[0].c_str(), (*param)[0].size());

    msg->msgSize = sizeof(*body);
    msg->msg = reinterpret_cast<char *>(body);
    return (msg);
}

unsigned int				CommandCall::getSizeBody(void){
	return sizeof(CommandCall::Body);
}
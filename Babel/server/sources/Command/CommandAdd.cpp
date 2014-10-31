#include "Command/CommandAdd.hpp"

CommandAdd::CommandAdd(){

}
CommandAdd::~CommandAdd(){

}

/*
** Heritage from ICommand
*/
std::vector<std::string>	*CommandAdd::getParam(IClientSocket *socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandAdd::Body			*body;
	IClientSocket::Message		data;

    std::memset(body, 0, sizeof(*body));

	data = socket->receive(this->getSizeBody());
	body = reinterpret_cast<CommandAdd::Body *>(data.msg);
	t->push_back(body->accountName);
	return t;
}

IClientSocket::Message		*CommandAdd::setParam(std::vector<std::string> *param){

	CommandAdd::BodySend	*body = new CommandAdd::BodySend;
	IClientSocket::Message	*msg = new IClientSocket::Message;

	std::memset(body, 0, sizeof(*body));

	body->header.instructionCode = ICommand::ADD;
	body->header.magicCode = ICommand::MAGIC_CODE;

	std::memcpy(body->accountName, (*param)[0].c_str(), (*param)[0].size());

	msg->msgSize = sizeof(*body);
	msg->msg = reinterpret_cast<char *>(body);

	return (msg);
}

unsigned int    			CommandAdd::getSizeBody(void){
	return sizeof(CommandAdd::Body);
}
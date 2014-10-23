#include "../../includes/Command/CommandAdd.hpp"

/*
** Heritage from ICommand
*/
std::vector<std::string>	*CommandAdd::getParam(TcpClient &socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandAdd::Body			*body;
	IClientSocket::Message		data;

	data = socket.receive(this->getSizeBody());
	//body = reinterpret_cast<CommandAdd::Body *>(data.msg);
	body = (CommandAdd::Body *)data.msg;
	t->push_back(body->accountName);
	return t;
}

ICommand::Instruction		CommandAdd::getInstruction(void){
	ICommand::Instruction	t;
	return t;
}

int							CommandAdd::getSizeHeader(void){
	return ICommand::HEADER_SIZE;
}

int							CommandAdd::getSizeBody(void){
	return sizeof CommandAdd::Body;
}
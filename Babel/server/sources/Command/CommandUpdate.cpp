#include "Command/CommandUpdate.hpp"

/*
** Heritage from ICommand
*/
std::vector<std::string>		*CommandUpdate::getParam(TcpClient &socket){
	std::vector<std::string>	*t = new std::vector<std::string>;
	CommandUpdate::Body			*body;
	IClientSocket::Message		data;
	std::string					status = "";

	data = socket.receive(this->getSizeBody());
	//body = static_cast<CommandUpdate::Body *>(data.msg);
	body = (CommandUpdate::Body *)data.msg;
	t->push_back(body->accountName);
	t->push_back(body->pseudo);
	t->push_back(body->password);
	status += body->status;
	t->push_back(status);
	return t;
}

ICommand::Instruction		CommandUpdate::getInstruction(void){
	ICommand::Instruction	t;
	return t;
}

int							CommandUpdate::getSizeHeader(void){
	return ICommand::HEADER_SIZE;
}

int							CommandUpdate::getSizeBody(void){
	return sizeof CommandUpdate::Body;
}
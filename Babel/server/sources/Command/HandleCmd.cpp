#include "HandleCmd.hpp"
#include "Factory.hpp"

HandleCmd::HandleCmd(TcpClient &socket)
:socket(socket){
	this->header = NULL;
}

std::vector<std::string>		*HandleCmd::unPackCmd(void){
	IClientSocket::Message		data;
	std::vector<std::string>	*param;

	if (this->header == NULL){
		data = this->socket.receive(ICommand::HEADER_SIZE);
		//this->header = static_cast<ICommand::Header>(data);
		this->header = (ICommand::Header *)(data.msg);
		this->body = Factory::getCommand(this->getInstruction());
	}

	if (this->socket.nbBytesToRead() >= this->body->getSizeBody()){
		param = this->body->getParam(this->socket);
		delete this->body;
		this->header = NULL;
		return param;
	}
	return NULL;
}

ICommand::Instruction		HandleCmd::getInstruction(void){
	//return reinterpret_cast<ICommand::Instruction>(this->header->instructionCode);
	return (ICommand::Instruction)(this->header->instructionCode);
}
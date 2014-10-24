#include "HandleCmd.hpp"
#include "Factory.hpp"

HandleCmd::HandleCmd(TcpClient &socket)
:socket(socket){
	this->header = NULL;
}

HandleCmd::~HandleCmd(){
}

std::vector<std::string>		*HandleCmd::unPackCmd(void){
	IClientSocket::Message		data;
	std::vector<std::string>	*param;

	if (this->header == NULL){
		data = this->socket.receive(ICommand::HEADER_SIZE);
		this->header = reinterpret_cast<ICommand::Header *>(data.msg);
		this->instruction = (ICommand::Instruction)header->instructionCode;
		this->body = Factory::getCommand(this->getInstruction());
	}

	if (this->socket.nbBytesToRead() >= this->body->getSizeBody()){;
		param = this->body->getParam(this->socket);
		delete this->body;
		this->header = NULL;
		return param;
	}
	return NULL;
}

ICommand::Instruction		HandleCmd::getInstruction(void){
	return this->instruction;
}
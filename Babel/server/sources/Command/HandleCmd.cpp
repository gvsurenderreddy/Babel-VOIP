#include "HandleCmd.hpp"
#include "Factory.hpp"

HandleCmd::HandleCmd(IClientSocket *socket)
:socket(socket){
	this->header = NULL;
}

HandleCmd::~HandleCmd(){
}

std::vector<std::string>		*HandleCmd::unPackCmd(void){
	IClientSocket::Message		data;
	std::vector<std::string>	*param;

	if (this->header == NULL && this->socket->nbBytesToRead() >= ICommand::HEADER_SIZE){
		data = this->socket->receive(ICommand::HEADER_SIZE);
		this->header = reinterpret_cast<ICommand::Header *>(data.msg);
		this->instruction = (ICommand::Instruction)header->instructionCode;
		this->body = Factory::getCommand(this->getInstruction());
	}

	if (this->header != NULL && this->socket->nbBytesToRead() >= this->body->getSizeBody()){
		;
		param = this->body->getParam(this->socket);
		delete this->body;
        this->body = NULL;
		this->header = NULL;
		return param;
	}
	return NULL;
}

void						HandleCmd::packCmd(ICommand::Instruction instruction, std::vector<std::string> *param){
	ICommand				*cmd;

	cmd = Factory::getCommand(instruction);
	this->socket->send(*(cmd->setParam(param)));
}

ICommand::Instruction		HandleCmd::getInstruction(void){
	return this->instruction;
}
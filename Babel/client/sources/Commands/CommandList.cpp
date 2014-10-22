#include "CommandList.hpp"

CommandList::CommandList(void) {
}

CommandList::~CommandList(void) {
}

ICommand::Instruction	CommandList::getInstruction(void) const {
	return ICommand::LIST;
}

IClientSocket::Message	CommandList::getMessage(void) const {
	IClientSocket::Message message;
	// MESSAGE
	return message;
}

unsigned int	CommandList::getSizeToRead(void) const {
	// THROW EXCEPTION
	return 0;
}

void	CommandList::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

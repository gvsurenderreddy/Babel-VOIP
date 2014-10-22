#include "CommandExit.hpp"

CommandExit::CommandExit(void) {
}

CommandExit::~CommandExit(void) {
}

ICommand::Instruction	CommandExit::getInstruction(void) const {
	return ICommand::EXIT;
}

IClientSocket::Message	CommandExit::getMessage(void) const {
	IClientSocket::Message message;
	// MESSAGE
	return message;
}

unsigned int	CommandExit::getSizeToRead(void) const {
	// THROW EXCEPTION
	return 0;
}

void	CommandExit::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

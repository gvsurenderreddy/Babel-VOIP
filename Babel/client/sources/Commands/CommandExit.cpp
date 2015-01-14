#include "CommandExit.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandExit::CommandExit(void) {
}

CommandExit::~CommandExit(void) {
}

ICommand::Instruction	CommandExit::getInstruction(void) const {
	return ICommand::EXIT;
}

IClientSocket::Message	CommandExit::getMessage(void) const {
	IClientSocket::Message message;

	message.msgSize = 0;

	return message;
}

unsigned int	CommandExit::getSizeToRead(void) const {
	throw CommandException("No packet are sent from the server for this command");
}

void	CommandExit::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("No packet are sent from the server for this command");
}

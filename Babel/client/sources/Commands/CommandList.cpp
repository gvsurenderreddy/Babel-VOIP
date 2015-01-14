#include "CommandList.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandList::CommandList(void) {
}

CommandList::~CommandList(void) {
}

ICommand::Instruction	CommandList::getInstruction(void) const {
	return ICommand::LIST;
}

IClientSocket::Message	CommandList::getMessage(void) const {
	IClientSocket::Message message;

	message.msgSize = 0;

	return message;
}

unsigned int	CommandList::getSizeToRead(void) const {
	throw CommandException("No packet are sent from the server for this command");
}

void	CommandList::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("No packet are sent from the server for this command");
}

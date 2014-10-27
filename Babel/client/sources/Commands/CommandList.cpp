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
	CommandList::PacketFromClient *packet = new CommandList::PacketFromClient;

	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::EXIT;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof(CommandList::PacketFromClient);

	return message;
}

unsigned int	CommandList::getSizeToRead(void) const {
	throw CommandException("No packet are sent from the server for this command");
}

void	CommandList::initFromMessage(const IClientSocket::Message &) {
	throw CommandException("No packet are sent from the server for this command");
}

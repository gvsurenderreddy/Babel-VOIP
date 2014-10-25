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
	CommandExit::PacketFromClient *packet = new CommandExit::PacketFromClient;

	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::EXIT;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof(CommandExit::PacketFromClient);

	return message;
}

unsigned int	CommandExit::getSizeToRead(void) const {
	throw new CommandException("No packet are sent from the server for this command");
}

void	CommandExit::initFromMessage(const IClientSocket::Message &) {
	throw new CommandException("No packet are sent from the server for this command");
}

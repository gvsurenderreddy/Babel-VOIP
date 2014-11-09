#include "CommandHandshake.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandHandshake::CommandHandshake(void) {
}

CommandHandshake::~CommandHandshake(void) {
}

ICommand::Instruction	CommandHandshake::getInstruction(void) const {
	return ICommand::HANDSHAKE;
}

IClientSocket::Message	CommandHandshake::getMessage(void) const {
	IClientSocket::Message message;
	CommandHandshake::PacketFromClient *packet = new CommandHandshake::PacketFromClient;

	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::HANDSHAKE;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof(CommandHandshake::PacketFromClient);

	return message;
}

unsigned int	CommandHandshake::getSizeToRead(void) const {
    return 0;
}

void	CommandHandshake::initFromMessage(const IClientSocket::Message &) {
}

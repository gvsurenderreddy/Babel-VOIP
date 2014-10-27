#include "CommandCloseCall.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandCloseCall::CommandCloseCall(void)
	: mAccountName("") {}

CommandCloseCall::~CommandCloseCall(void) {
}

ICommand::Instruction	CommandCloseCall::getInstruction(void) const {
	return ICommand::CLOSE_CALL;
}

IClientSocket::Message	CommandCloseCall::getMessage(void) const {
	IClientSocket::Message message;
	CommandCloseCall::PacketFromClient *packet = new CommandCloseCall::PacketFromClient;

	std::memset(packet, 0, sizeof(CommandCloseCall::PacketFromClient));
	std::memcpy(packet->accountName, mAccountName.toStdString().c_str(), MIN(sizeof(packet->accountName) - 1, mAccountName.length()));
	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::CLOSE_CALL;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof(CommandCloseCall::PacketFromClient);

	return message;
}

unsigned int	CommandCloseCall::getSizeToRead(void) const {
  return sizeof(PacketFromServer);
}

void	CommandCloseCall::initFromMessage(const IClientSocket::Message &message) {
  if (message.msgSize != sizeof(CommandCloseCall::PacketFromServer))
		throw new CommandException("Message has an invalid size");

	CommandCloseCall::PacketFromServer *packet = reinterpret_cast<CommandCloseCall::PacketFromServer *>(message.msg);
	mAccountName = packet->accountName;
}

const QString	&CommandCloseCall::getAccountName(void) const {
	return mAccountName;
}

void	CommandCloseCall::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

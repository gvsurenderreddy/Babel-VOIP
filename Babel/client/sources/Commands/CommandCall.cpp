#include "CommandCall.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandCall::CommandCall(void)
	: mAccountName("") {}

CommandCall::~CommandCall(void) {
}

ICommand::Instruction	CommandCall::getInstruction(void) const {
	return ICommand::CALL;
}

IClientSocket::Message	CommandCall::getMessage(void) const {
	IClientSocket::Message message;
	CommandCall::PacketFromClient *packet = new CommandCall::PacketFromClient;

	std::memset(packet, 0, sizeof(CommandCall::PacketFromClient));
	std::memcpy(packet->accountName, mAccountName.toStdString().c_str(), MIN(sizeof(packet->accountName), mAccountName.length()));
	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::CALL;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof(CommandCall::PacketFromClient);

	return message;
}

unsigned int	CommandCall::getSizeToRead(void) const {
  return sizeof(PacketFromServer);
}

void	CommandCall::initFromMessage(const IClientSocket::Message &message) {
  if (message.msgSize != sizeof(CommandCall::PacketFromServer))
		throw new CommandException("Message has an invalid size");

	CommandCall::PacketFromServer *packet = reinterpret_cast<CommandCall::PacketFromServer *>(message.msg);
	mAccountName = packet->accountName;
}

const QString	&CommandCall::getAccountName(void) const {
	return mAccountName;
}

void	CommandCall::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

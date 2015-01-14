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
	CommandCloseCall::PacketFromClient packet;

	std::memset(&packet, 0, sizeof(CommandCloseCall::PacketFromClient));
	std::memcpy(packet.accountName, mAccountName.toStdString().c_str(), std::min(static_cast<int>(sizeof(packet.accountName) - 1), mAccountName.length()));

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandCloseCall::PacketFromClient);

	return message;
}

unsigned int	CommandCloseCall::getSizeToRead(void) const {
  return sizeof(PacketFromServer);
}

void	CommandCloseCall::initFromMessage(const IClientSocket::Message &message) {
  if (message.msgSize != sizeof(CommandCloseCall::PacketFromServer))
		throw CommandException("Message has an invalid size");

	CommandCloseCall::PacketFromServer packet = *reinterpret_cast<const CommandCloseCall::PacketFromServer *>(message.msg.data());

	packet.accountName[sizeof(packet.accountName) - 1] = 0;
	mAccountName = packet.accountName;
}

const QString	&CommandCloseCall::getAccountName(void) const {
	return mAccountName;
}

void	CommandCloseCall::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

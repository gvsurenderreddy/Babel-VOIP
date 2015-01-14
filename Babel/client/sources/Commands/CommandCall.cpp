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
	CommandCall::PacketFromClient packet;

	std::memset(&packet, 0, sizeof(CommandCall::PacketFromClient));
	std::memcpy(packet.accountName, mAccountName.toStdString().c_str(), std::min(static_cast<int>(sizeof(packet.accountName) - 1), mAccountName.length()));

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandCall::PacketFromClient);

	return message;
}

unsigned int	CommandCall::getSizeToRead(void) const {
  return sizeof(PacketFromServer);
}

void	CommandCall::initFromMessage(const IClientSocket::Message &message) {
  if (message.msgSize != sizeof(CommandCall::PacketFromServer))
		throw CommandException("Message has an invalid size");

	CommandCall::PacketFromServer packet = *reinterpret_cast<const CommandCall::PacketFromServer *>(message.msg.data());

	packet.accountName[sizeof(packet.accountName) - 1] = 0;
	mAccountName = packet.accountName;
}

const QString	&CommandCall::getAccountName(void) const {
	return mAccountName;
}

void	CommandCall::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

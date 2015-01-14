#include "CommandDel.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandDel::CommandDel(void)
	: mAccountName("") {}

CommandDel::~CommandDel(void) {
}

ICommand::Instruction	CommandDel::getInstruction(void) const {
	return ICommand::DEL;
}

IClientSocket::Message	CommandDel::getMessage(void) const {
	CommandDel::PacketFromClient packet;

	std::memset(&packet, 0, sizeof(CommandDel::PacketFromClient));
	std::memcpy(packet.accountName, mAccountName.toStdString().c_str(), std::min(static_cast<int>(sizeof(packet.accountName) - 1), mAccountName.length()));

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandDel::PacketFromClient);

	return message;
}

unsigned int	CommandDel::getSizeToRead(void) const {
  return sizeof(PacketFromServer);
}

void	CommandDel::initFromMessage(const IClientSocket::Message &message) {
  if (message.msgSize != sizeof(CommandDel::PacketFromServer))
		throw CommandException("Message has an invalid size");

	CommandDel::PacketFromServer packet = *reinterpret_cast<const CommandDel::PacketFromServer *>(message.msg.data());

	packet.accountName[sizeof(packet.accountName) - 1] = 0;
	mAccountName = packet.accountName;
}

const QString	&CommandDel::getAccountName(void) const {
	return mAccountName;
}

void	CommandDel::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

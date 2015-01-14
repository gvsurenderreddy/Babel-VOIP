#include "CommandAdd.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandAdd::CommandAdd(void)
	: mAccountName("") {}

CommandAdd::~CommandAdd(void) {
}

ICommand::Instruction	CommandAdd::getInstruction(void) const {
	return ICommand::ADD;
}

IClientSocket::Message	CommandAdd::getMessage(void) const {
	CommandAdd::PacketFromClient packet;

	std::memset(&packet, 0, sizeof(CommandAdd::PacketFromClient));
	std::memcpy(packet.accountName, mAccountName.toStdString().c_str(), std::min(static_cast<int>(sizeof(packet.accountName) - 1), mAccountName.length()));

	IClientSocket::Message message;
	message.msg.assign(reinterpret_cast<char *>(&packet), reinterpret_cast<char *>(&packet + 1));
	message.msgSize = sizeof(CommandAdd::PacketFromClient);

	return message;
}

unsigned int	CommandAdd::getSizeToRead(void) const {
  return sizeof(CommandAdd::PacketFromServer);
}

void	CommandAdd::initFromMessage(const IClientSocket::Message &message) {
  if (message.msgSize != sizeof(CommandAdd::PacketFromServer))
		throw CommandException("Message has an invalid size");

	CommandAdd::PacketFromServer packet = *reinterpret_cast<const CommandAdd::PacketFromServer *>(message.msg.data());

	packet.accountName[sizeof(packet.accountName) - 1] = 0;
	mAccountName = packet.accountName;
}

const QString	&CommandAdd::getAccountName(void) const {
	return mAccountName;
}

void	CommandAdd::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

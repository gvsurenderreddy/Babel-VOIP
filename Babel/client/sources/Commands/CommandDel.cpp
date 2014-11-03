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
	IClientSocket::Message message;
	CommandDel::PacketFromClient *packet = new CommandDel::PacketFromClient;

	std::memset(packet, 0, sizeof(CommandDel::PacketFromClient));
	std::memcpy(packet->accountName, mAccountName.toStdString().c_str(), MIN(sizeof(packet->accountName) - 1, mAccountName.length()));
	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::DEL;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof(CommandDel::PacketFromClient);

	return message;
}

unsigned int	CommandDel::getSizeToRead(void) const {
  return sizeof(PacketFromServer);
}

void	CommandDel::initFromMessage(const IClientSocket::Message &message) {
  if (message.msgSize != sizeof(CommandDel::PacketFromServer))
		throw CommandException("Message has an invalid size");

	CommandDel::PacketFromServer *packet = reinterpret_cast<CommandDel::PacketFromServer *>(message.msg);
	packet->accountName[sizeof(packet->accountName) - 1] = 0;
	mAccountName = packet->accountName;
}

const QString	&CommandDel::getAccountName(void) const {
	return mAccountName;
}

void	CommandDel::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

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
	IClientSocket::Message message;
	CommandAdd::PacketFromClient *packet = new CommandAdd::PacketFromClient;

	std::memset(packet, 0, sizeof(CommandAdd::PacketFromClient));
	std::memcpy(packet->accountName, mAccountName.toStdString().c_str(), MIN(sizeof(packet->accountName) - 1, mAccountName.length()));
	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::ADD;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof(CommandAdd::PacketFromClient);

	return message;
}

unsigned int	CommandAdd::getSizeToRead(void) const {
  return sizeof(CommandAdd::PacketFromServer);
}

#include <iostream>
void	CommandAdd::initFromMessage(const IClientSocket::Message &message) {
    std::cout << "INIT FROM MESSAGE ADD" << std::endl;
  if (message.msgSize != sizeof(CommandAdd::PacketFromServer))
		throw CommandException("Message has an invalid size");
  std::cout << "GOOD SIZE" << std::endl;
	CommandAdd::PacketFromServer *packet = reinterpret_cast<CommandAdd::PacketFromServer *>(message.msg);
	mAccountName = packet->accountName;
    std::cout << "ACCOUNT NAME" << std::endl;
}

const QString	&CommandAdd::getAccountName(void) const {
	return mAccountName;
}

void	CommandAdd::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

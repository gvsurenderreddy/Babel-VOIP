#include "CommandAdd.hpp"
#include "CommandException.hpp"

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

	std::memset(packet, 0, sizeof CommandAdd::PacketFromClient);
	std::memcpy(packet->accountName, mAccountName.toStdString().c_str(), MIN(sizeof packet->accountName, mAccountName.length()));
	packet->header.magicCode = ICommand::MAGIC_CODE;
	packet->header.instructionCode = ICommand::ADD;

	message.msg = reinterpret_cast<char *>(packet);
	message.msgSize = sizeof CommandAdd::PacketFromClient;

	return message;
}

unsigned int	CommandAdd::getSizeToRead(void) const {
	return sizeof CommandAdd::PacketFromServer;
}

void	CommandAdd::initFromMessage(const IClientSocket::Message &message) {
	if (message.msgSize != sizeof CommandAdd::PacketFromServer)
		throw new CommandException("Message has an invalid size");

	CommandAdd::PacketFromServer *packet = reinterpret_cast<CommandAdd::PacketFromServer *>(message.msg);
	mAccountName = packet->accountName;
}

const QString	&CommandAdd::getAccountName(void) const {
	return mAccountName;
}

void	CommandAdd::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

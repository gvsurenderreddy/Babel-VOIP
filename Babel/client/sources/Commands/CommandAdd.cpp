#include "CommandAdd.hpp"

CommandAdd::CommandAdd(void)
	: mAccountName("") {}

CommandAdd::~CommandAdd(void) {
}

ICommand::Instruction	CommandAdd::getInstruction(void) const {
	return ICommand::ADD;
}

IClientSocket::Message	CommandAdd::getMessage(void) const {
	IClientSocket::Message message;
	// MESSAGE
	return message;
}

unsigned int	CommandAdd::getSizeToRead(void) const {
	return sizeof CommandAdd::PacketFromClientAndServer;
}

void	CommandAdd::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

const QString	&CommandAdd::getAccountName(void) const {
	return mAccountName;
}

void	CommandAdd::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

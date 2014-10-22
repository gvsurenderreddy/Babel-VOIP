#include "CommandDel.hpp"

CommandDel::CommandDel(void)
	: mAccountName("") {}

CommandDel::~CommandDel(void) {
}

ICommand::Instruction	CommandDel::getInstruction(void) const {
	return ICommand::DEL;
}

IClientSocket::Message	CommandDel::getMessage(void) const {
	IClientSocket::Message message;
	// MESSAGE
	return message;
}

unsigned int	CommandDel::getSizeToRead(void) const {
	return sizeof PacketFromClientAndServer;
}

void	CommandDel::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

const QString	&CommandDel::getAccountName(void) const {
	return mAccountName;
}

void	CommandDel::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

#include "CommandCall.hpp"

CommandCall::CommandCall(void)
	: mAccountName("") {}

CommandCall::~CommandCall(void) {
}

ICommand::Instruction	CommandCall::getInstruction(void) const {
	return ICommand::CALL;
}

IClientSocket::Message	CommandCall::getMessage(void) const {
	IClientSocket::Message message;
	// MESSAGE
	return message;
}

unsigned int	CommandCall::getSizeToRead(void) const {
	return sizeof PacketFromClientAndServer;
}

void	CommandCall::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

const QString	&CommandCall::getAccountName(void) const {
	return mAccountName;
}

void	CommandCall::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

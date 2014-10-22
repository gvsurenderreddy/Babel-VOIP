#include "CommandCloseCall.hpp"

CommandCloseCall::CommandCloseCall(void)
	: mAccountName("") {}

CommandCloseCall::~CommandCloseCall(void) {
}

ICommand::Instruction	CommandCloseCall::getInstruction(void) const {
	return ICommand::CLOSE_CALL;
}

IClientSocket::Message	CommandCloseCall::getMessage(void) const {
	IClientSocket::Message message;
	// MESSAGE
	return message;
}

unsigned int	CommandCloseCall::getSizeToRead(void) const {
	return sizeof PacketFromClientAndServer;
}

void	CommandCloseCall::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

const QString	&CommandCloseCall::getAccountName(void) const {
	return mAccountName;
}

void	CommandCloseCall::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

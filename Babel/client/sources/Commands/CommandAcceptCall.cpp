#include "CommandAcceptCall.hpp"

CommandAcceptCall::CommandAcceptCall(void)
: mAccountName(""), mHost(""), mHasAccepted(false) {}

CommandAcceptCall::~CommandAcceptCall(void) {
}

ICommand::Instruction	CommandAcceptCall::getInstruction(void) const {
	return ICommand::ACCEPT_CALL;
}

IClientSocket::Message	CommandAcceptCall::getMessage(void) const {
	IClientSocket::Message message;
	//MESSAGE
	return message;
}

unsigned int	CommandAcceptCall::getSizeToRead(void) const {
	return sizeof CommandAcceptCall::PacketFromServer;
}

void	CommandAcceptCall::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

const QString	&CommandAcceptCall::getAccountName(void) const {
	return mAccountName;
}

const QString	&CommandAcceptCall::getHost(void) const {
	return mHost;
}

bool	CommandAcceptCall::hasAccepted(void) const {
	return mHasAccepted;
}

void	CommandAcceptCall::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandAcceptCall::setHost(const QString &host) {
	mHost = host;
}

void	CommandAcceptCall::setHasAccepted(bool hasAccepted) {
	mHasAccepted = hasAccepted;
}

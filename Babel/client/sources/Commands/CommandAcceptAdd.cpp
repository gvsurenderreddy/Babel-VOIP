#include "CommandAcceptAdd.hpp"

CommandAcceptAdd::CommandAcceptAdd(void)
	: mAccountName(""), mHasAccepted(false) {}

CommandAcceptAdd::~CommandAcceptAdd(void) {
}

ICommand::Instruction	CommandAcceptAdd::getInstruction(void) const {
	return ICommand::ACCEPT_ADD;
}

IClientSocket::Message	CommandAcceptAdd::getMessage(void) const {
	IClientSocket::Message	message;
	// MESSAGE
	return message;
}

unsigned int	CommandAcceptAdd::getSizeToRead(void) const {
	// THROW EXCEPTION - NO PACKET FROM SERVER
	return 0;
}

void	CommandAcceptAdd::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

const QString	&CommandAcceptAdd::getAccountName(void) const {
	return mAccountName;
}

bool	CommandAcceptAdd::hasAccepted(void) const {
	return mHasAccepted;
}

void	CommandAcceptAdd::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandAcceptAdd::setHasAccepted(bool hasAccepted) {
	mHasAccepted = hasAccepted;
}

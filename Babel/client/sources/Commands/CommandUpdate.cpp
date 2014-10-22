#include "CommandUpdate.hpp"

CommandUpdate::CommandUpdate(void)
: mAccountName(""), mPseudo(""), mPassword(""), mStatus(Contact::DISCONNECTED) {}

CommandUpdate::~CommandUpdate(void) {
}

ICommand::Instruction	CommandUpdate::getInstruction(void) const {
	return ICommand::UPDATE;
}

IClientSocket::Message	CommandUpdate::getMessage(void) const {
	IClientSocket::Message message;
	// MESSAGE
	return message;
}

unsigned int	CommandUpdate::getSizeToRead(void) const {
	// THROW
	return 0;
}

void	CommandUpdate::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

const QString	&CommandUpdate::getAccountName(void) const {
	return mAccountName;
}

const QString	&CommandUpdate::getPseudo(void) const {
	return mPseudo;
}

const QString	&CommandUpdate::getPassword(void) const {
	return mPassword;
}

Contact::Status	CommandUpdate::getStatus(void) const {
	return mStatus;
}

void	CommandUpdate::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandUpdate::setPseudo(const QString &pseudo) {
	mPseudo = pseudo;
}

void	CommandUpdate::setPassword(const QString &password) {
	mPassword = password;
}

void	CommandUpdate::setStatus(Contact::Status status) {
	mStatus = status;
}

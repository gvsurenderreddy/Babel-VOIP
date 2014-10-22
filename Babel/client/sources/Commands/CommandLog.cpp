#include "CommandLog.hpp"

CommandLog::CommandLog(void)
	: mAccountName(""), mPassword("") {}

CommandLog::~CommandLog(void) {
}

ICommand::Instruction	CommandLog::getInstruction(void) const {
	return ICommand::LOG;
}

IClientSocket::Message	CommandLog::getMessage(void) const {
	IClientSocket::Message message;
	// MESSAGE
	return message;
}

unsigned int	CommandLog::getSizeToRead(void) const {
	// THROW
	return 0;
}

void	CommandLog::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

const QString	&CommandLog::getAccountName(void) const {
	return mAccountName;
}

const QString	&CommandLog::getPassword(void) const {
	return mPassword;
}

void	CommandLog::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandLog::setPassword(const QString &password) {
	mPassword = password;
}

#include "CommandReg.hpp"

CommandReg::CommandReg(void)
	: mAccountName(""), mPseudo(""), mPassword("") {}

CommandReg::~CommandReg(void) {
}

ICommand::Instruction	CommandReg::getInstruction(void) const {
	return ICommand::REG;
}

IClientSocket::Message	CommandReg::getMessage(void) const {
	IClientSocket::Message message;
	// MESSAGE
	return message;
}

unsigned int	CommandReg::getSizeToRead(void) const {
	// THROW
	return 0;
}

void	CommandReg::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

const QString	&CommandReg::getAccountName(void) const {
	return mAccountName;
}

const QString	&CommandReg::getPseudo(void) const {
	return mPseudo;
}

const QString	&CommandReg::getPassword(void) const {
	return mPassword;
}

void	CommandReg::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandReg::setPseudo(const QString &pseudo) {
	mPseudo = pseudo;
}

void	CommandReg::setPassword(const QString &password) {
	mPassword = password;
}

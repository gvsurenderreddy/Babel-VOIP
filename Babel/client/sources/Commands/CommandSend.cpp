#include "CommandSend.hpp"

CommandSend::CommandSend(void)
	: mAccountName(""), mTextMessage("") {}

CommandSend::~CommandSend(void) {
}

ICommand::Instruction	CommandSend::getInstruction(void) const {
	return ICommand::SEND;
}

IClientSocket::Message	CommandSend::getMessage(void) const {
	IClientSocket::Message message;
	// MESSAGE
	return message;
}

unsigned int	CommandSend::getSizeToRead(void) const {
	return sizeof PacketFromClientAndServer;
}

void	CommandSend::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

const QString	&CommandSend::getAccountName(void) const {
	return mAccountName;
}

const QString	&CommandSend::getTextMessage(void) const {
	return mTextMessage;
}

void	CommandSend::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandSend::setTextMessage(const QString &textMessage) {
	mTextMessage = textMessage;
}

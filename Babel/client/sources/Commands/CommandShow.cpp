#include "CommandShow.hpp"

CommandShow::CommandShow(void)
: mAccountName(""), mPseudo(""), mStatus(Contact::DISCONNECTED), mIsConnected(false) {}

CommandShow::~CommandShow(void) {
}

ICommand::Instruction	CommandShow::getInstruction(void) const {
	return ICommand::SHOW;
}

IClientSocket::Message	CommandShow::getMessage(void) const {
	IClientSocket::Message message;
	// MESSAGE
	return message;
}

unsigned int	CommandShow::getSizeToRead(void) const {
	return sizeof PacketFromServer;
}

void	CommandShow::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

const QString	&CommandShow::getAccountName(void) const {
	return mAccountName;
}

const QString	&CommandShow::getPseudo(void) const {
	return mPseudo;
}

Contact::Status	CommandShow::getStatus(void) const {
	return mStatus;
}

bool	CommandShow::isConnected(void) const {
	return mIsConnected;
}

void	CommandShow::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	CommandShow::setPseudo(const QString &pseudo) {
	mPseudo = pseudo;
}

void	CommandShow::setStatus(Contact::Status status) {
	mStatus = status;
}

void	CommandShow::setIsConnected(bool isConnected) {
	mIsConnected = isConnected;
}

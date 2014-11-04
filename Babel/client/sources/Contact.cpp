#include "Contact.hpp"

Contact::Contact(void)
	: mAccountName(""), mPseudo(""), mStatus(Contact::DISCONNECTED), mHost(""), mPassword(""), mIsConnected(false) {}

const QString	&Contact::getAccountName(void) const {
	return mAccountName;
}

const QString	&Contact::getPseudo(void) const {
	return mPseudo;
}

Contact::Status	Contact::getStatus(void) const {
	return mStatus;
}

const QString	&Contact::getHost(void) const {
	return mHost;
}

const QString	&Contact::getPassword(void) const {
	return mPassword;
}

bool	Contact::isConnected(void) const {
	return mIsConnected;
}

MessageListModel::sMessage const	&Contact::getMessages() const
{
	return mMessages;
}

void	Contact::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	Contact::setPseudo(const QString &pseudo) {
	mPseudo = pseudo;
}

void	Contact::setStatus(Contact::Status status) {
	mStatus = status;
}

void	Contact::setHost(const QString &host) {
	mHost = host;
}

void	Contact::setPassword(const QString &password) {
	mPassword = password;
}

void	Contact::setIsConnected(bool isConnected) {
	mIsConnected = isConnected;
}

void	Contact::setMessages(const MessageListModel::sMessage &msg)
{
	mMessages = msg;
}
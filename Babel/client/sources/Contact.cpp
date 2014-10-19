#include "Contact.hpp"

Contact::Contact(void)
	: mAccountName(""), mPseudo(""), mHost(""), mPort(0), mIsConnected(false) {}

const QString	&Contact::getAccountName(void) const {
	return mAccountName;
}

const QString	&Contact::getPseudo(void) const {
	return mPseudo;
}

const QString	&Contact::getHost(void) const {
	return mHost;
}

int	Contact::getPort(void) const {
	return mPort;
}

bool	Contact::isConnected(void) const {
	return mIsConnected;
}

void	Contact::setAccountName(const QString &accountName) {
	mAccountName = accountName;
}

void	Contact::setPseudo(const QString &pseudo) {
	mPseudo = pseudo;
}

void	Contact::setHost(const QString &host) {
	mHost = host;
}

void	Contact::setPort(int port) {
	mPort = port;
}

void	Contact::setIsConnected(bool isConnected) {
	mIsConnected = isConnected;
}

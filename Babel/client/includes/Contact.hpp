#pragma once

#include <qstring.h>
#include "MessageListModel.hpp"

class Contact {

	// status
	public:
		enum Status {
			CONNECTED		= 0x00,
			DISCONNECTED	= 0x01,
			BUSY			= 0x02,
			AWAY			= 0x03,
			KIPOUR			= 0x04,
			SLEEPING		= 0x05,
			RAMADAN			= 0x06,
			SPORT			= 0x07,
			TOILET			= 0x08,
			YOLO			= 0x09,
			CRYING			= 0x0A
		};

	// ctor - dtor
	public:
		Contact(void);
		~Contact(void) {}

	// getters - setters
	public:
		const QString							&getAccountName(void) const;
		const QString							&getPseudo(void) const;
		Contact::Status							getStatus(void) const;
		const QString							&getHost(void) const;
		const QString							&getPassword(void) const;
		bool									isConnected(void) const;
		QList<MessageListModel::sMessage>		&getMessages(void);

		void	setAccountName(const QString &accountName);
		void	setPseudo(const QString &pseudo);
		void	setStatus(Contact::Status status);
		void	setHost(const QString &host);
		void	setPassword(const QString &password);
		void	setIsConnected(bool isConnected);
		void	setMessages(const QList<MessageListModel::sMessage> &msg);

	// attributes
	private:
		QString								mAccountName;
		QString								mPseudo;
		Contact::Status						mStatus;
		QString								mHost;
		QString								mPassword;
		bool								mIsConnected;
		QList<MessageListModel::sMessage>	mMessages;
};

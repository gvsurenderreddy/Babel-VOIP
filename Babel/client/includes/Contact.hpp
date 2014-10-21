#pragma once

#include <qstring.h>

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

	// coplien form
	private:
		Contact(const Contact &) {}
		const Contact &operator=(const Contact &) { return *this; }

	// getters - setters
	public:
		const QString	&getAccountName(void) const;
		const QString	&getPseudo(void) const;
		Contact::Status	getStatus(void) const;
		const QString	&getHost(void) const;
		int				getPort(void) const;
		bool			isConnected(void) const;

		void	setAccountName(const QString &accountName);
		void	setPseudo(const QString &pseudo);
		void	setStatus(Contact::Status status);
		void	setHost(const QString &host);
		void	setPort(int host);
		void	setIsConnected(bool isConnected);

	// attributes
	private:
		QString			mAccountName;
		QString			mPseudo;
		Contact::Status	mStatus;
		QString			mHost;
		int				mPort;
		bool			mIsConnected;

};

#pragma once

#include <qstring.h>

class Contact {

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
		const QString	&getHost(void) const;
		int				getPort(void) const;
		bool			isConnected(void) const;

		void	setAccountName(const QString &accountName);
		void	setPseudo(const QString &pseudo);
		void	setHost(const QString &host);
		void	setPort(int host);
		void	setIsConnected(bool isConnected);

	// attributes
	private:
		QString	mAccountName;
		QString	mPseudo;
		QString	mHost;
		int		mPort;
		bool	mIsConnected;

};

#pragma once

#include <qstring.h>
#include "ICommand.hpp"

class CommandAcceptCall : public ICommand {

	// packet
	private:
		struct PacketFromClient {
			char	accountName[256];
			char	hasAccepted;
		};

		struct PacketFromServer {
			char	accountName[256];
			char	host[15];
		};

	// ctor - dtor
	public:
		CommandAcceptCall(void);
		~CommandAcceptCall(void);

	// coplien form
	private:
		CommandAcceptCall(const CommandAcceptCall &) {}
		const CommandAcceptCall &operator=(const CommandAcceptCall &) { return *this; }

	// implementation
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// getters - setters
	public:
		const QString	&getAccountName(void) const;
		const QString	&getHost(void) const;
		void			setAccountName(const QString &accountName);
		void			setHost(const QString &host);

	// attributes
	private:
		QString	mAccountName;
		QString	mHost;

};

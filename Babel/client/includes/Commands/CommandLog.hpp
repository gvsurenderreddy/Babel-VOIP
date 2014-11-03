#pragma once

#include <qstring.h>
#include "ICommand.hpp"

class CommandLog : public ICommand {

	// packet
	private:
        #pragma pack(push, 1)
		struct PacketFromClient{
			ICommand::Header	header;
			char				accountName[256];
			char				password[256];
		};
        #pragma pack(pop)

	// ctor - dtor
	public:
		CommandLog(void);
		~CommandLog(void);

	// coplien form
	private:
		CommandLog(const CommandLog &) {}
		const CommandLog &operator=(const CommandLog &) { return *this; }

	// implementation
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// getters - setters
	public:
		const QString	&getAccountName(void) const;
		const QString	&getPassword(void) const;
		void			setAccountName(const QString &accountName);
		void			setPassword(const QString &password);

	// attributes
	private:
		QString	mAccountName;
		QString	mPassword;

};

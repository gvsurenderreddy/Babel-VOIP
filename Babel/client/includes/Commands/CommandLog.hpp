#pragma once

#include <qstring.h>
#include "ICommand.hpp"

class CommandLog : public ICommand {

	// packet
	private:
#ifdef WIN32
		struct __declspec(align(1)) PacketFromClient{
			ICommand::Header	header;
			char				accountName[256];
			char				password[256];
		};
#else
		struct __attribute__((packed)) PacketFromClient{
			ICommand::Header	header;
			char				accountName[256];
			char				password[256];
		};
#endif

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

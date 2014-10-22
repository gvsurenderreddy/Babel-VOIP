#pragma once

#include <qstring.h>
#include "ICommand.hpp"

class CommandDel : public ICommand {

	// packet
	private:
		struct PacketFromClientAndServer {
			char	accountName[256];
		};

	// ctor - dtor
	public:
		CommandDel(void);
		~CommandDel(void);

	// coplien form
	private:
		CommandDel(const CommandDel &) {}
		const CommandDel &operator=(const CommandDel &) { return *this; }

	// implementation
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// getters - setters
	public:
		const QString	&getAccountName(void) const;
		void			setAccountName(const QString &accountName);

	// attributes
	private:
		QString	mAccountName;

};

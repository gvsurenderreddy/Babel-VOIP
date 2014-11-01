#pragma once

#include <qstring.h>
#include "ICommand.hpp"

class CommandCall : public ICommand {

	// packet
	private:
		struct NO_PADDING PacketFromClient{
			ICommand::Header	header;
			char				accountName[256];
		};

		struct NO_PADDING PacketFromServer{
			char	accountName[256];
		};

	// ctor - dtor
	public:
		CommandCall(void);
		~CommandCall(void);

	// coplien form
	private:
		CommandCall(const CommandCall &) {}
		const CommandCall &operator=(const CommandCall &) { return *this; }

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

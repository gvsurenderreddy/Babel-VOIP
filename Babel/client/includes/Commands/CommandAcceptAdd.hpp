#pragma once

#include "ICommand.hpp"
#include <qstring.h>

class CommandAcceptAdd : public ICommand {

	// packet
	private:
		struct NO_PADDING PacketFromClient {
			ICommand::Header	header;
			char				accountName[256];
			char				hasAccepted;
		};

	// ctor - dtor
	public:
		CommandAcceptAdd(void);
		~CommandAcceptAdd(void);

	// coplien form
	private:
		CommandAcceptAdd(const CommandAcceptAdd &) {}
		const CommandAcceptAdd &operator=(const CommandAcceptAdd &) { return *this; }

	// implementation
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// getters - setters
	public:
		const QString	&getAccountName(void) const;
		bool			hasAccepted(void) const;
		void			setAccountName(const QString &accountName);
		void			setHasAccepted(bool hasAccepted);

	// attributes
	private:
		QString	mAccountName;
		bool	mHasAccepted;

};

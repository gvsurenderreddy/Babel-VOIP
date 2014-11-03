#pragma once

#include <qstring.h>
#include "ICommand.hpp"

class CommandSend : public ICommand {

	// packet
	private:
        #pragma pack(push, 1)
		struct PacketFromClient{
			ICommand::Header	header;
			char				accountName[256];
			char				textMessage[4096];
		};

		struct PacketFromServer{
			char	accountName[256];
			char	textMessage[4096];
		};
        #pragma pack(pop)

	// ctor - dtor
	public:
		CommandSend(void);
		~CommandSend(void);

	// coplien form
	private:
		CommandSend(const CommandSend &) {}
		const CommandSend &operator=(const CommandSend &) { return *this; }

	// implementation
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// getters - setters
	public:
		const QString	&getAccountName(void) const;
		const QString	&getTextMessage(void) const;
		void			setAccountName(const QString &accountName);
		void			setTextMessage(const QString &textMessage);

	// attributes
	private:
		QString	mAccountName;
		QString	mTextMessage;

};

#pragma once

#include <qstring.h>
#include "ICommand.hpp"

class CommandSend : public ICommand {

	// packet
	private:
#ifdef WIN32
		struct __declspec(align(1)) PacketFromClient{
			ICommand::Header	header;
			char				accountName[256];
			char				textMessage[4096];
		};

		struct __declspec(align(1)) PacketFromServer{
			char	accountName[256];
			char	textMessage[4096];
		};
#else
		struct __attribute__((packed)) PacketFromClient{
			ICommand::Header	header;
			char				accountName[256];
			char				textMessage[4096];
		};

		struct __attribute__((packed)) PacketFromServer{
			char	accountName[256];
			char	textMessage[4096];
		};
#endif

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

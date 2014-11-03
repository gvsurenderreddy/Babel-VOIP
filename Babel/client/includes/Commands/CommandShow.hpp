#pragma once

#include <qstring.h>
#include "ICommand.hpp"
#include "Contact.hpp"

class CommandShow : public ICommand {

	// packet
	private:
        #pragma pack(push, 1)
		struct PacketFromClient{
			ICommand::Header	header;
			char				accountName[256];
		};

		struct PacketFromServer{
			char	accountName[256];
			char	pseudo[256];
			char	status;
			char	isConnected;
		};
        #pragma pack(pop)

	// ctor - dtor
	public:
		CommandShow(void);
		~CommandShow(void);

	// coplien form
	private:
		CommandShow(const CommandShow &) {}
		const CommandShow &operator=(const CommandShow &) { return *this; }

	// implementation
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// getters - setters
	public:
		const QString	&getAccountName(void) const;
		const QString	&getPseudo(void) const;
		Contact::Status	getStatus(void) const;
		bool			isConnected(void) const;
		void			setAccountName(const QString &accountName);
		void			setPseudo(const QString &pseudo);
		void			setStatus(Contact::Status status);
		void			setIsConnected(bool isConnected);

	// attributes
	private:
		QString			mAccountName;
		QString			mPseudo;
		Contact::Status	mStatus;
		bool			mIsConnected;

};

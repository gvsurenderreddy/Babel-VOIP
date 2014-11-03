#pragma once

#include <qstring.h>
#include "Contact.hpp"
#include "ICommand.hpp"

class CommandUpdate : public ICommand {

	// packet
	private:
        #pragma pack(push, 1)
		struct PacketFromClient{
			ICommand::Header	header;
			char				accountName[256];
			char				pseudo[256];
			char				password[256];
			char				status;
		};
		#pragma pack(pop)

	// ctor - dtor
	public:
		CommandUpdate(void);
		~CommandUpdate(void);

	// coplien form
	private:
		CommandUpdate(const CommandUpdate &) {}
		const CommandUpdate &operator=(const CommandUpdate &) { return *this; }

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
		const QString	&getPassword(void) const;
		Contact::Status	getStatus(void) const;
		void			setAccountName(const QString &accountName);
		void			setPseudo(const QString &pseudo);
		void			setPassword(const QString &password);
		void			setStatus(Contact::Status status);

	// attributes
	private:
		QString			mAccountName;
		QString			mPseudo;
		QString			mPassword;
		Contact::Status	mStatus;

};

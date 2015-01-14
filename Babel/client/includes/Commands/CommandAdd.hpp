#pragma once

#include <qstring.h>
#include "ICommand.hpp"

class CommandAdd : public ICommand {

	// packet
	private:
		#pragma pack(push, 1)
		struct PacketFromClient {
			char	accountName[256];
		};

		struct PacketFromServer {
			char	accountName[256];
		};
		#pragma pack(pop)

	// ctor - dtor
	public:
		CommandAdd(void);
		~CommandAdd(void);

	// coplien form
	private:
		CommandAdd(const CommandAdd &) {}
		const CommandAdd &operator=(const CommandAdd &) { return *this; }

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

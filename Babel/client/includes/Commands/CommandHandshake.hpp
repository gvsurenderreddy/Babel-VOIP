#pragma once

#include "ICommand.hpp"

class CommandHandshake : public ICommand {

	// ctor - dtor
	public:
		CommandHandshake(void);
		~CommandHandshake(void);

	// coplien form
	private:
		CommandHandshake(const CommandHandshake &) {}
		const CommandHandshake &operator=(const CommandHandshake &) { return *this; }

	// implementation
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

};

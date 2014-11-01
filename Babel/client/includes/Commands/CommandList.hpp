#pragma once

#include "ICommand.hpp"

class CommandList : public ICommand {

	// packet
	private:
		struct NO_PADDING PacketFromClient{
			ICommand::Header	header;
		};

	// ctor - dtor
	public:
		CommandList(void);
		~CommandList(void);

	// coplien form
	private:
		CommandList(const CommandList &) {}
		const CommandList &operator=(const CommandList &) { return *this; }

	// implementation
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

};

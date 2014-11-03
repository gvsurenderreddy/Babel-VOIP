#pragma once

#include "ICommand.hpp"

class CommandExit : public ICommand {

	// packet
	private:
        #pragma pack(push, 1)
		struct PacketFromClient{
			ICommand::Header	header;
		};
        #pragma pack(pop)

	// ctor - dtor
	public:
		CommandExit(void);
		~CommandExit(void);

	// coplien form
	private:
		CommandExit(const CommandExit &) {}
		const CommandExit &operator=(const CommandExit &) { return *this; }

	// implementation
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

};

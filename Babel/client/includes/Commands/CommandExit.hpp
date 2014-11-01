#pragma once

#include "ICommand.hpp"

class CommandExit : public ICommand {

	// packet
	private:
#ifdef WIN32
		struct __declspec(align(1)) PacketFromClient{
			ICommand::Header	header;
		};
#else
		struct __attribute__((packed)) PacketFromClient{
			ICommand::Header	header;
		};
#endif

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

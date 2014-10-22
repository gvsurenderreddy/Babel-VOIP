#pragma once

#include "iClientSocket.hpp"

class ICommand {

	// Instructions
	public:
		enum Instruction {
			REG,
			LOG,
			LIST,
			SHOW,
			ADD,
			ACCEPT_ADD,
			DEL,
			EXIT,
			UPDATE,
			SEND,
			CALL,
			ACCEPT_CALL,
			CLOSE_CALL,
			ERR
		};

	// virtual destructor
	public:
		virtual ~ICommand(void) {}

	// public pure methods
	public:
		virtual ICommand::Instruction	getInstruction(void) const = 0;
		virtual	IClientSocket::Message	getMessage(void) const = 0;
		virtual unsigned int			getSizeToRead(void) const = 0;
		virtual void					initFromMessage(const IClientSocket::Message &message) = 0;

};

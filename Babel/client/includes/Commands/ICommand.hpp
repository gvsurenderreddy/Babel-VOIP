#pragma once

#include "IClientSocket.hpp"

#define MIN(x, y) (static_cast<int>(x) < static_cast<int>(y) ? (x) : (y))

class ICommand {

	// Instructions
	public:
		enum Instruction {
			REG			= 0x01,
			LOG			= 0x02,
			LIST		= 0x03,
			SHOW		= 0x04,
			ADD			= 0x05,
			ACCEPT_ADD	= 0x06,
			DEL			= 0x07,
			EXIT		= 0x08,
			UPDATE		= 0x09,
			SEND		= 0x0A,
			CALL		= 0x0B,
			ACCEPT_CALL	= 0x0C,
			CLOSE_CALL	= 0x0D,
			ERR			= 0x0E,
			UNKNOWN_INSTRUCTION
		};

	// header
	public:
		static const int		MAGIC_CODE;
		static const unsigned int	HEADER_SIZE;

		struct Header {
			int	magicCode;
			int	instructionCode;
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

	// getCommand
	public:
		static ICommand	*getCommand(ICommand::Instruction instructionCode);

};

#pragma once

#include "ICommand.hpp"

class CommandErr : public ICommand {

	// packet
	private:
		struct PacketFromServer {
			int	instructionCode;
			int	errorCode;
		};

	// error codes
	public:
		enum ErrorCode {
			OK = 0x01,
			THE_IMPOSSIBLE_HAPPENED = 0x02
		};

	// ctor - dtor
	public:
		CommandErr(void);
		~CommandErr(void);

	// coplien form
	private:
		CommandErr(const CommandErr &) {}
		const CommandErr &operator=(const CommandErr &) { return *this; }

	// implementation
	public:
		ICommand::Instruction	getInstruction(void) const;
		IClientSocket::Message	getMessage(void) const;
		unsigned int			getSizeToRead(void) const;
		void					initFromMessage(const IClientSocket::Message &message);

	// getters - setters
	public:
		ICommand::Instruction	getInstructionCode(void) const;
		CommandErr::ErrorCode	getErrorCode(void) const;
		void					setInstructionCode(ICommand::Instruction instructionCode);
		void					setErrorCode(CommandErr::ErrorCode errorCode);

	// attributes
	private:
		ICommand::Instruction	mInstructionCode;
		CommandErr::ErrorCode	mErrorCode;

};

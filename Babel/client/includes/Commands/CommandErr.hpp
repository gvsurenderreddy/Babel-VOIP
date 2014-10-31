#pragma once

#include "ErrorStatus.hpp"
#include "ICommand.hpp"

class CommandErr : public ICommand {

	// packet
	private:
		struct __attribute__ ((packed)) PacketFromServer {
			int	instructionCode;
			int	errorCode;
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
		ErrorStatus::ErrorCode	getErrorCode(void) const;
		void					setInstructionCode(ICommand::Instruction instructionCode);
		void					setErrorCode(ErrorStatus::ErrorCode errorCode);

	// attributes
	private:
		ICommand::Instruction	mInstructionCode;
		ErrorStatus::ErrorCode	mErrorCode;

};

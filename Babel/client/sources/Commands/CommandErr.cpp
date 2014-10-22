#include "CommandErr.hpp"

CommandErr::CommandErr(void)
	: mInstructionCode(ICommand::EXIT), mErrorCode(CommandErr::OK) {}

CommandErr::~CommandErr(void) {
}

ICommand::Instruction	CommandErr::getInstruction(void) const {
	return ICommand::ERR;
}

IClientSocket::Message	CommandErr::getMessage(void) const {
	IClientSocket::Message message;
	// MESSAGE
	return message;
}

unsigned int	CommandErr::getSizeToRead(void) const {
	return sizeof PacketFromServer;
}

void	CommandErr::initFromMessage(const IClientSocket::Message &message) {
	// INIT
}

ICommand::Instruction	CommandErr::getInstructionCode(void) const {
	return mInstructionCode;
}

CommandErr::ErrorCode	CommandErr::getErrorCode(void) const {
	return mErrorCode;
}

void	CommandErr::setInstructionCode(ICommand::Instruction instructionCode) {
	mInstructionCode = instructionCode;
}

void	CommandErr::setErrorCode(CommandErr::ErrorCode errorCode) {
	mErrorCode = errorCode;
}

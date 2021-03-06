#include "CommandErr.hpp"
#include "CommandException.hpp"
#include <cstring>

CommandErr::CommandErr(void)
	: mInstructionCode(ICommand::EXIT), mErrorCode(ErrorStatus::OK) {}

CommandErr::~CommandErr(void) {
}

ICommand::Instruction	CommandErr::getInstruction(void) const {
	return ICommand::ERR;
}

IClientSocket::Message	CommandErr::getMessage(void) const {
	throw CommandException("No packet can be sent from the client for this command");
}

unsigned int	CommandErr::getSizeToRead(void) const {
  return sizeof(PacketFromServer);
}

void	CommandErr::initFromMessage(const IClientSocket::Message &message) {
  if (message.msgSize != sizeof(CommandErr::PacketFromServer))
		throw CommandException("Message has an invalid size");

	CommandErr::PacketFromServer packet = *reinterpret_cast<const CommandErr::PacketFromServer *>(message.msg.data());

	mInstructionCode = static_cast<ICommand::Instruction>(packet.instructionCode);
	mErrorCode = static_cast<ErrorStatus::ErrorCode>(packet.errorCode);
}

ICommand::Instruction	CommandErr::getInstructionCode(void) const {
	return mInstructionCode;
}

ErrorStatus::ErrorCode	CommandErr::getErrorCode(void) const {
	return mErrorCode;
}

void	CommandErr::setInstructionCode(ICommand::Instruction instructionCode) {
	mInstructionCode = instructionCode;
}

void	CommandErr::setErrorCode(ErrorStatus::ErrorCode errorCode) {
	mErrorCode = errorCode;
}

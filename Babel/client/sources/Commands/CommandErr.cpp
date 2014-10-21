#include "CommandErr.hpp"

CommandErr::CommandErr(void) {
}

CommandErr::~CommandErr(void) {
}

ICommand::Instruction	CommandErr::getInstruction(void) const {
}

IClientSocket::Message	CommandErr::getMessage(void) const {
}

unsigned int	CommandErr::getSizeToRead(void) const {
}

void	CommandErr::initFromMessage(const IClientSocket::Message &message) {
}

ICommand::Instruction	CommandErr::getInstructionCode(void) const {
}

CommandErr::ErrorCode	CommandErr::getErrorCode(void) const {
}

void	CommandErr::setInstructionCode(ICommand::Instruction instructionCode) {
}

void	CommandErr::setErrorCode(CommandErr::ErrorCode errorCode) {
}

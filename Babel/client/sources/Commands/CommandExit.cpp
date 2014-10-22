#include "CommandExit.hpp"

CommandExit::CommandExit(void) {
}

CommandExit::~CommandExit(void) {
}

ICommand::Instruction	CommandExit::getInstruction(void) const {
}

IClientSocket::Message	CommandExit::getMessage(void) const {
}

unsigned int	CommandExit::getSizeToRead(void) const {
}

void	CommandExit::initFromMessage(const IClientSocket::Message &message) {
}

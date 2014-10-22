#include "CommandCall.hpp"

CommandCall::CommandCall(void) {
}

CommandCall::~CommandCall(void) {
}

ICommand::Instruction	CommandCall::getInstruction(void) const {
}

IClientSocket::Message	CommandCall::getMessage(void) const {
}

unsigned int	CommandCall::getSizeToRead(void) const {
}

void	CommandCall::initFromMessage(const IClientSocket::Message &message) {
}

const QString	&CommandCall::getAccountName(void) const {
}

void	CommandCall::setAccountName(const QString &accountName) {
}

#include "CommandCloseCall.hpp"

CommandCloseCall::CommandCloseCall(void) {
}

CommandCloseCall::~CommandCloseCall(void) {
}

ICommand::Instruction	CommandCloseCall::getInstruction(void) const {
}

IClientSocket::Message	CommandCloseCall::getMessage(void) const {
}

unsigned int	CommandCloseCall::getSizeToRead(void) const {
}

void	CommandCloseCall::initFromMessage(const IClientSocket::Message &message) {
}

const QString	&CommandCloseCall::getAccountName(void) const {
}

void	CommandCloseCall::setAccountName(const QString &accountName) {
}

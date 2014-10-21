#include "CommandAcceptCall.hpp"

CommandAcceptCall::CommandAcceptCall(void) {
}

CommandAcceptCall::~CommandAcceptCall(void) {
}

ICommand::Instruction	CommandAcceptCall::getInstruction(void) const {
}

IClientSocket::Message	CommandAcceptCall::getMessage(void) const {
}

unsigned int	CommandAcceptCall::getSizeToRead(void) const {
}

void	CommandAcceptCall::initFromMessage(const IClientSocket::Message &message) {
}

const QString	&CommandAcceptCall::getAccountName(void) const {
}

const QString	&CommandAcceptCall::getHost(void) const {
}

void	CommandAcceptCall::setAccountName(const QString &accountName) {
}

void	CommandAcceptCall::setHost(const QString &host) {
}

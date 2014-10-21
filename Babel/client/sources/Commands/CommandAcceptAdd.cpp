#include "CommandAcceptAdd.hpp"

CommandAcceptAdd::CommandAcceptAdd(void) {
}

CommandAcceptAdd::~CommandAcceptAdd(void) {
}

ICommand::Instruction	CommandAcceptAdd::getInstruction(void) const {
}

IClientSocket::Message	CommandAcceptAdd::getMessage(void) const {
}

unsigned int	CommandAcceptAdd::getSizeToRead(void) const {
}

void	CommandAcceptAdd::initFromMessage(const IClientSocket::Message &message) {
}

const QString	&CommandAcceptAdd::getAccountName(void) const {
}

bool	CommandAcceptAdd::hasAccepted(void) const {
}

void	CommandAcceptAdd::setAccountName(const QString &accountName) {
}

void	CommandAcceptAdd::setHasAccepted(bool hasAccepted) {
}

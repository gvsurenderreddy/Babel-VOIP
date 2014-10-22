#include "CommandDel.hpp"

CommandDel::CommandDel(void) {
}

CommandDel::~CommandDel(void) {
}

ICommand::Instruction	CommandDel::getInstruction(void) const {
}

IClientSocket::Message	CommandDel::getMessage(void) const {
}

unsigned int	CommandDel::getSizeToRead(void) const {
}

void	CommandDel::initFromMessage(const IClientSocket::Message &message) {
}

const QString	&CommandDel::getAccountName(void) const {
}

void	CommandDel::setAccountName(const QString &accountName) {
}

#include "CommandAdd.hpp"

CommandAdd::CommandAdd(void) {
}

CommandAdd::~CommandAdd(void) {
}

ICommand::Instruction	CommandAdd::getInstruction(void) const {
}

IClientSocket::Message	CommandAdd::getMessage(void) const {
}

unsigned int	CommandAdd::getSizeToRead(void) const {
}

void	CommandAdd::initFromMessage(const IClientSocket::Message &message) {
}

const QString	&CommandAdd::getAccountName(void) const {
}

void	CommandAdd::setAccountName(const QString &accountName) {
}

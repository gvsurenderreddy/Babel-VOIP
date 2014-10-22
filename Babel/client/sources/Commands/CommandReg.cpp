#include "CommandReg.hpp"

CommandReg::CommandReg(void) {
}

CommandReg::~CommandReg(void) {
}

ICommand::Instruction	CommandReg::getInstruction(void) const {
}

IClientSocket::Message	CommandReg::getMessage(void) const {
}

unsigned int	CommandReg::getSizeToRead(void) const {
}

void	CommandReg::initFromMessage(const IClientSocket::Message &message) {
}

const QString	&CommandReg::getAccountName(void) const {
}

const QString	&CommandReg::getPseudo(void) const {
}

const QString	&CommandReg::getPassword(void) const {
}

void	CommandReg::setAccountName(const QString &accountName) {
}

void	CommandReg::setPseudo(const QString &pseudo) {
}

void	CommandReg::setPassword(const QString &password) {
}

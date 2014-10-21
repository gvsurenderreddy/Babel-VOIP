#include "CommandSend.hpp"

CommandSend::CommandSend(void) {
}

CommandSend::~CommandSend(void) {
}

ICommand::Instruction	CommandSend::getInstruction(void) const {
}

IClientSocket::Message	CommandSend::getMessage(void) const {
}

unsigned int	CommandSend::getSizeToRead(void) const {
}

void	CommandSend::initFromMessage(const IClientSocket::Message &message) {
}

const QString	&CommandSend::getAccountName(void) const {
}

const QString	&CommandSend::getTextMessage(void) const {
}

void	CommandSend::setAccountName(const QString &accountName) {
}

void	CommandSend::setTextMessage(const QString &textMessage) {
}

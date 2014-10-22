#include "CommandLog.hpp"

CommandLog::CommandLog(void) {
}

CommandLog::~CommandLog(void) {
}

ICommand::Instruction	CommandLog::getInstruction(void) const {
}

IClientSocket::Message	CommandLog::getMessage(void) const {
}

unsigned int	CommandLog::getSizeToRead(void) const {
}

void	CommandLog::initFromMessage(const IClientSocket::Message &message) {
}

const QString	&CommandLog::getAccountName(void) const {
}

const QString	&CommandLog::getPassword(void) const {
}

void	CommandLog::setAccountName(const QString &accountName) {
}

void	CommandLog::setPassword(const QString &password) {
}

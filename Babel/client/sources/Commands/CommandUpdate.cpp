#include "CommandUpdate.hpp"

CommandUpdate::CommandUpdate(void) {
}

CommandUpdate::~CommandUpdate(void) {
}

ICommand::Instruction	CommandUpdate::getInstruction(void) const {
}

IClientSocket::Message	CommandUpdate::getMessage(void) const {
}

unsigned int	CommandUpdate::getSizeToRead(void) const {
}

void	CommandUpdate::initFromMessage(const IClientSocket::Message &message) {
}

const QString	&CommandUpdate::getAccountName(void) const {
}

const QString	&CommandUpdate::getPseudo(void) const {
}

const QString	&CommandUpdate::getPassword(void) const {
}

Contact::Status	CommandUpdate::getStatus(void) const {
}

void	CommandUpdate::setAccountName(const QString &accountName) {
}

void	CommandUpdate::setPseudo(const QString &pseudo) {
}

void	CommandUpdate::setPassword(const QString &password) {
}

void	CommandUpdate::setStatus(Contact::Status status) {
}

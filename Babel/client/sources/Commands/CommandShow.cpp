#include "CommandShow.hpp"

CommandShow::CommandShow(void) {
}

CommandShow::~CommandShow(void) {
}

ICommand::Instruction	CommandShow::getInstruction(void) const {
}

IClientSocket::Message	CommandShow::getMessage(void) const {
}

unsigned int	CommandShow::getSizeToRead(void) const {
}

void	CommandShow::initFromMessage(const IClientSocket::Message &message) {
}

const QString	&CommandShow::getAccountName(void) const {
}

const QString	&CommandShow::getPseudo(void) const {
}

Contact::Status	CommandShow::getStatus(void) const {
}

bool	CommandShow::isConnected(void) const {
}

void	CommandShow::setAccountName(const QString &accountName) {
}

void	CommandShow::setPseudo(const QString &pseudo) {
}

void	CommandShow::setStatus(Contact::Status status) {
}

void	CommandShow::setIsConnected(bool isConnected) {
}

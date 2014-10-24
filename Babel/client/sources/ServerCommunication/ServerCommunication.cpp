#include "ServerCommunication.hpp"

const ServerCommunication::HandleCommand	ServerCommunication::handleCommandsTab[] = {
	{ ICommand::REG, &ServerCommunication::handleRegCommand },
	{ ICommand::LOG, &ServerCommunication::handleLogCommand },
	{ ICommand::LIST, &ServerCommunication::handleListCommand },
	{ ICommand::SHOW, &ServerCommunication::handleShowCommand },
	{ ICommand::ADD, &ServerCommunication::handleAddCommand },
	{ ICommand::ACCEPT_ADD, &ServerCommunication::handleAcceptAddCommand },
	{ ICommand::DEL, &ServerCommunication::handleDelCommand },
	{ ICommand::EXIT, &ServerCommunication::handleExitCommand },
	{ ICommand::UPDATE, &ServerCommunication::handeUpdateCommand },
	{ ICommand::SEND, &ServerCommunication::handleSendCommand },
	{ ICommand::CALL, &ServerCommunication::handleCallCommand },
	{ ICommand::ACCEPT_CALL, &ServerCommunication::handleAcceptCallCommand },
	{ ICommand::CLOSE_CALL, &ServerCommunication::handleCloseCallCommand },
	{ ICommand::ERR, &ServerCommunication::handleErrCommand }
};

ServerCommunication::ServerCommunication(void) {
	connect(&mCommandPacketBuilder, SIGNAL(receiveCommand(const ICommand *)), this, SLOT(treatCommand(const ICommand *)));
}

ServerCommunication::~ServerCommunication(void) {
}

void	ServerCommunication::treatCommand(const ICommand *) {
}

void	ServerCommunication::connectToServer(const QString &addr, int port) {
	mCommandPacketBuilder.connectToServer(addr, port);
}

void	ServerCommunication::handleRegCommand(const ICommand *command) {
}

void	ServerCommunication::handleLogCommand(const ICommand *command) {
}

void	ServerCommunication::handleListCommand(const ICommand *command) {
}

void	ServerCommunication::handleShowCommand(const ICommand *command) {
}

void	ServerCommunication::handleAddCommand(const ICommand *command) {
}

void	ServerCommunication::handleAcceptAddCommand(const ICommand *command) {
}

void	ServerCommunication::handleDelCommand(const ICommand *command) {
}

void	ServerCommunication::handleExitCommand(const ICommand *command) {
}

void	ServerCommunication::handeUpdateCommand(const ICommand *command) {
}

void	ServerCommunication::handleSendCommand(const ICommand *command) {
}

void	ServerCommunication::handleCallCommand(const ICommand *command) {
}

void	ServerCommunication::handleAcceptCallCommand(const ICommand *command) {
}

void	ServerCommunication::handleCloseCallCommand(const ICommand *command) {
}

void	ServerCommunication::handleErrCommand(const ICommand *command) {
}

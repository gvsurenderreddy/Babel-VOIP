#include "ServerCommunication.hpp"

ServerCommunication::ServerCommunication(void) {
	connect(&mCommandPacketBuilder, SIGNAL(receiveCommand(const ICommand *)), this, SLOT(treatCommand(const ICommand *)));
}

ServerCommunication::~ServerCommunication(void) {
}

void	ServerCommunication::treatCommand(const ICommand *command) {
}

void	ServerCommunication::connectToServer(const QString &addr, int port) {
	mCommandPacketBuilder.connectToServer(addr, port);
}

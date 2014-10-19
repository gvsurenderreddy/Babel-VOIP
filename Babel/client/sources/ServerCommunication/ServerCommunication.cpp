#include "ServerCommunication.hpp"

ServerCommunication::ServerCommunication(void) {
}

ServerCommunication::~ServerCommunication(void) {
}

void	ServerCommunication::treatCommand(const CommandPacketBuilder::Command &command) {
}

void	ServerCommunication::connectToServer(const QString &addr, int port) {
	mCommandPacketBuilder.connectToServer(addr, port);
}

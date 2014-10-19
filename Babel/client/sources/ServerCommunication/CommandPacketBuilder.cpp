#include "CommandPacketBuilder.hpp"
#include "TcpClient.hpp"

CommandPacketBuilder::CommandPacketBuilder(void)
	: mClient(NULL), mCurrentState(CommandPacketBuilder::INSTRUCTION)
{
	mClient = new TcpClient;
	mClient->setOnSocketEventListener(this);
}

CommandPacketBuilder::~CommandPacketBuilder(void) {
	if (mClient)
		delete mClient;
}

void	CommandPacketBuilder::sendCommand(const CommandPacketBuilder::Command &command) {
}

void	CommandPacketBuilder::connectToServer(const QString &addr, int port) {
	mClient->connect(addr.toStdString(), port);
}

void	CommandPacketBuilder::onBytesWritten(IClientSocket *socket, unsigned int nbBytes) {
}

void	CommandPacketBuilder::onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead) {
}

void	CommandPacketBuilder::onSocketClosed(IClientSocket *socket) {
}

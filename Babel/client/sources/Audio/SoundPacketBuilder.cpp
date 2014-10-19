#include "SoundPacketBuilder.hpp"
#include "UdpClient.hpp"

const int SoundPacketBuilder::DEFAULT_BABEL_CALL_PORT = 4242;

SoundPacketBuilder::SoundPacketBuilder(void)
: mClient(NULL), mAcceptedHost(""), mAcceptedPort(0)
{
	mClient = new UdpClient;
	mClient->setOnSocketEventListener(this);
	mClient->connect("127.0.0.1", SoundPacketBuilder::DEFAULT_BABEL_CALL_PORT);
}

SoundPacketBuilder::~SoundPacketBuilder(void) {
}

void	SoundPacketBuilder::acceptPacketsFrom(const QString &addr, int port) {
}

void	SoundPacketBuilder::sendSound(const Sound::Encoded &command) {
}

void	SoundPacketBuilder::onBytesWritten(IClientSocket *socket, unsigned int nbBytes) {
}

void	SoundPacketBuilder::onSocketReadable(IClientSocket *socket, unsigned int nbBytesToRead) {
}

void	SoundPacketBuilder::onSocketClosed(IClientSocket *socket) {
}

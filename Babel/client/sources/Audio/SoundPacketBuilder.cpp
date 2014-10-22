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
	mAcceptedHost = addr;
	mAcceptedPort = port;
}

void	SoundPacketBuilder::sendSound(const Sound::Encoded &sound) {
	IClientSocket::Message msg;

	msg.msg = reinterpret_cast<char *>(sound.buffer);
	msg.msgSize = sound.size;
	msg.host = mAcceptedHost.toStdString();
	msg.port = mAcceptedPort;
	mClient->send(msg);
}

void	SoundPacketBuilder::onBytesWritten(IClientSocket *, unsigned int) {
}

void	SoundPacketBuilder::onSocketReadable(IClientSocket *, unsigned int) {
	Sound::Encoded sound;
	IClientSocket::Message msg;

	msg = mClient->receive(4096);
	sound.buffer = reinterpret_cast<unsigned char *>(msg.msg);
	sound.size = msg.msgSize;
	emit SoundPacketBuilder::receiveSound(sound);
}

void	SoundPacketBuilder::onSocketClosed(IClientSocket *) {
}

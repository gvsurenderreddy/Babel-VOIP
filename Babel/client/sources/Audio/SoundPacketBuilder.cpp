#include <QDate>
#include "SoundPacketBuilder.hpp"
#include "UdpClient.hpp"

const int SoundPacketBuilder::DEFAULT_BABEL_CALL_PORT = 4242

SoundPacketBuilder::SoundPacketBuilder(void)
: mClient(NULL), mAcceptedHost(""), mAcceptedPort(0)
{
	mClient = new UdpClient;
	mClient->setOnSocketEventListener(this);
	mClient->connect("127.0.0.1", SoundPacketBuilder::DEFAULT_BABEL_CALL_PORT);
	mTimestamp = 0;
}

SoundPacketBuilder::~SoundPacketBuilder(void) {
}

void	SoundPacketBuilder::acceptPacketsFrom(const QString &addr, int port) {
	mAcceptedHost = addr;
	mAcceptedPort = port;
}

void	SoundPacketBuilder::sendSound(const Sound::Encoded &sound) {
	IClientSocket::Message msg;
	SoundPacketBuilder::SoundPacket soundPacket;
	msg.msg = new char[sizeof(soundPacket)];

	soundPacket.magic_code = 0x150407CA;
	soundPacket.soundSize = sound.size;
	memcpy(soundPacket.sound, sound.buffer, sound.size);
	soundPacket.timestamp = QDateTime::currentDateTime().toTime_t();
	msg.msgSize = sizeof(soundPacket);
	memcpy(msg.msg, &soundPacket, msg.msgSize);
	msg.host = mAcceptedHost.toStdString();
	msg.port = mAcceptedPort;
	mClient->send(msg);
	}

void	SoundPacketBuilder::onBytesWritten(IClientSocket *, unsigned int) {
}

void	SoundPacketBuilder::onSocketReadable(IClientSocket *, unsigned int) {
	IClientSocket::Message msg;
	SoundPacketBuilder::SoundPacket soundPacket;
	Sound::Encoded sound;

	sound.buffer = new unsigned char[sizeof(soundPacket.sound)];
	msg = mClient->receive(sizeof(soundPacket));
	if (msg.host == mAcceptedHost.toStdString() && msg.port == mAcceptedPort) {
		memcpy(&soundPacket, msg.msg, msg.msgSize);
		memcpy(sound.buffer, soundPacket.sound, soundPacket.soundSize);
		sound.size = soundPacket.soundSize;
		if (soundPacket.timestamp >= mTimestamp)
			emit SoundPacketBuilder::receiveSound(sound);
	}
	mTimestamp = soundPacket.timestamp;
}

void	SoundPacketBuilder::onSocketClosed(IClientSocket *) {
}

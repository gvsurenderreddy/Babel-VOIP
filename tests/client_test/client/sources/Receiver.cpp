#include "Receiver.hpp"
#include "SoundOutputDevice.hpp"
#include "UdpClient.hpp"

Receiver::Receiver(void)
	: mClient(NULL), mOutput(NULL)
{
	mClient = new UdpClient;
	mOutput = new SoundOutputDevice;

	mClient->connect("127.0.0.1", 4243);
	mClient->setOnSocketEventListener(this);
}

Receiver::~Receiver(void) {
	if (mClient)
		delete mClient;

	if (mOutput)
		delete mOutput;
}

void	Receiver::start(void) {
	mOutput->startStream();
}

void	Receiver::onSocketReadable(IClientSocket *socket) {
	IClientSocket::Message message = mClient->receive(1024);

	Sound::Encoded sound;
	sound.buffer = reinterpret_cast<unsigned char *>(message.msg);
	sound.size = message.msgSize;

	*mOutput << mEncodeManager.decode(sound);
}
